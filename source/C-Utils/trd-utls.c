/*************************/
/* Library importations: */
/*************************/
#ifndef C_UTILS_COMPILE
#include "../../include/C-Utils/trd-utls.h"
#include "../../include/C-Utils/err-utls.h"
#else
#include "C-Utils/trd-utls.h"
#include "C-Utils/err-utls.h"
#endif
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(_WIN32) || defined(_WIN64)
#include <process.h>
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
#include <unistd.h>
#include <sched.h>
#endif

/********************/
/* Import C to C++: */
/********************/

#ifdef __cplusplus
extern "C"
{
#endif

/**************************/
/* Functions definitions: */
/**************************/

static c_utils_thread_function_t c_utils_thread_pool_worker(c_utils_void_t *arguments)
{
	c_utils_thread_pool_t *const pool = (c_utils_thread_pool_t *)arguments;

	while(C_UTILS_TRUE)
	{
		if(c_utils_mutex_lock(&pool->mutex))
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_worker, function c_utils_mutex_lock failed");

			return c_utils_thread_function_return;
		}

		else
		{
			c_utils_task_node_t *task;

			while(!pool->head && !pool->stop)
			{
				if(c_utils_condition_variable_wait(&pool->condition_has_tasks, &pool->mutex))
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_worker, function c_utils_condition_variable_wait failed");

					if(c_utils_mutex_unlock(&pool->mutex))
					{
						C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_worker, function c_utils_mutex_unlock failed");
					}

					return c_utils_thread_function_return;
				}
			}

			if(pool->stop && !pool->head)
			{
				if(c_utils_mutex_unlock(&pool->mutex))
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_worker, function c_utils_mutex_unlock failed");
				}

				return c_utils_thread_function_return;
			}

			task = pool->head;
			pool->head = task->next;

			if(!pool->head)
			{
				pool->tail = C_UTILS_NULL_POINTER;
			}

			--pool->pending_tasks;
			++pool->active_tasks;

			if(c_utils_mutex_unlock(&pool->mutex))
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_worker, function c_utils_mutex_unlock failed");

				free((c_utils_void_t *)task);

				return c_utils_thread_function_return;
			}

			task->function(task->arguments);

			free((c_utils_void_t *)task);

			if(c_utils_mutex_lock(&pool->mutex))
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_worker, function c_utils_mutex_lock failed");

				return c_utils_thread_function_return;
			}

			--pool->active_tasks;

			if(pool->pending_tasks == 0 && pool->active_tasks == 0)
			{
				if(c_utils_condition_variable_broadcast(&pool->condition_idle))
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_worker, function c_utils_condition_variable_broadcast failed");
				}
			}

			if(c_utils_mutex_unlock(&pool->mutex))
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_worker, function c_utils_mutex_unlock failed");
			}
		}
	}

	return c_utils_thread_function_return;
}

C_UTILS_API c_utils_result_t c_utils_get_processor_count(c_utils_int32_t *const output)
{
	if(!output)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_get_processor_count, the output is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		const DWORD count	= GetActiveProcessorCount(ALL_PROCESSOR_GROUPS);

		if(count == 0)
		{
			const DWORD error = GetLastError();
			DWORD value = error;
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_get_processor_count, function GetActiveProcessorCount failed, error code: ");
			c_utils_size_t error_size = 1u;

			while(value >= 10u)
			{
				value /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_get_processor_count, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_get_processor_count, function GetActiveProcessorCount failed, error code: %u", (c_utils_uint32_t)error);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}

		*output = (c_utils_int32_t)count;
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		const signed long int count = sysconf(_SC_NPROCESSORS_ONLN);

		if(count == -1)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_get_processor_count, function sysconf");

			return C_UTILS_RESULT_FAILURE;
		}

		*output = (c_utils_int32_t)count;
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_thread_create(c_utils_thread_t *const thread, c_utils_thread_function_t (*f)(c_utils_void_t *arguments), c_utils_void_t *arguments)
{
	if(!thread)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_create, the thread is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!f)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_create, the function is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		*thread = (HANDLE)_beginthreadex(C_UTILS_NULL_POINTER, 0U, (unsigned (__stdcall *)(void *))f, arguments, 0U, C_UTILS_NULL_POINTER);

		if(!*thread)
		{
			const DWORD error = GetLastError();
			DWORD value = error;
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_thread_create, function _beginthreadex failed, error code: ");
			c_utils_size_t error_size = 1u;

			while(value >= 10u)
			{
				value /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_thread_create, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_thread_create, function _beginthreadex failed, error code: %u", (c_utils_uint32_t)error);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		const signed int result = pthread_create(thread, C_UTILS_NULL_POINTER, f, arguments);

		if(result)
		{
			unsigned int value = (unsigned int)(result < 0 ? -result : result);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_thread_create, function pthread_create failed, error code: ");
			c_utils_size_t error_size = (result < 0) ? 2u : 1u;

			while(value >= 10u)
			{
				value /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_thread_create, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_thread_create, function pthread_create failed, error code: %d", result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_thread_join(c_utils_thread_t thread)
{
#if defined(_WIN32) || defined(_WIN64)
	if(WaitForSingleObject(thread, INFINITE) != WAIT_OBJECT_0)
	{
		DWORD error = GetLastError();
		DWORD value = error;
		c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
		c_utils_size_t prefix_size = strlen("Error in function c_utils_thread_join, function WaitForSingleObject failed, error code: ");
		c_utils_size_t error_size = 1u;

		while(value >= 10u)
		{
			value /= 10u;
			error_size++;
		}

		error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

		if(!error_buffer)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_thread_join, function malloc failed");

			return C_UTILS_RESULT_FAILURE;
		}

		sprintf(error_buffer, "Error in function c_utils_thread_join, function WaitForSingleObject failed, error code: %u", (c_utils_uint32_t)error);

		C_UTILS_REPORT_ERROR(error_buffer);

		free((c_utils_void_t *)error_buffer);

		if(!CloseHandle(thread))
		{
			error = GetLastError();
			value = error;
			error_buffer = C_UTILS_NULL_POINTER;
			prefix_size = strlen("Error in function c_utils_thread_join, function CloseHandle failed, error code: ");
			error_size = 1u;

			while(value >= 10u)
			{
				value /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_thread_join, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_thread_join, function CloseHandle failed, error code: %u", (c_utils_uint32_t)error);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);
		}

		return C_UTILS_RESULT_FAILURE;
	}

	if(!CloseHandle(thread))
	{
		const DWORD error = GetLastError();
		DWORD value = error;
		c_utils_size_t prefix_size = strlen("Error in function c_utils_thread_join, function CloseHandle failed, error code: ");
		c_utils_size_t error_size = 1u;
		c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

		while(value >= 10u)
		{
			value /= 10u;
			error_size++;
		}

		error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

		if(!error_buffer)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_thread_join, function malloc failed");

			return C_UTILS_RESULT_FAILURE;
		}

		sprintf(error_buffer, "Error in function c_utils_thread_join, function CloseHandle failed, error code: %u", (c_utils_uint32_t)error);

		C_UTILS_REPORT_ERROR(error_buffer);

		free((c_utils_void_t *)error_buffer);

		return C_UTILS_RESULT_FAILURE;
	}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	const signed int result = pthread_join(thread, C_UTILS_NULL_POINTER);

	if(result)
	{
		unsigned int value = (unsigned int)(result < 0 ? -result : result);
		c_utils_size_t prefix_size = strlen("Error in function c_utils_thread_join, function pthread_join failed, error code: ");
		c_utils_size_t error_size = (result < 0) ? 2u : 1u;
		c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

		while(value >= 10u)
		{
			value /= 10u;
			error_size++;
		}

		error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

		if(!error_buffer)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_thread_join, function malloc failed");

			return C_UTILS_RESULT_FAILURE;
		}

		sprintf(error_buffer, "Error in function c_utils_thread_join, function pthread_join failed, error code: %d", result);

		C_UTILS_REPORT_ERROR(error_buffer);

		free((c_utils_void_t *)error_buffer);

		return C_UTILS_RESULT_FAILURE;
	}
#endif

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_thread_detach(c_utils_thread_t thread)
{
#if defined(_WIN32) || defined(_WIN64)
	const BOOL result = CloseHandle(thread);

	if(!result)
	{
		const DWORD error = GetLastError();
		DWORD value = error;
		c_utils_size_t prefix_size = strlen("Error in function c_utils_thread_detach, function CloseHandle failed, error code: ");
		c_utils_size_t error_size = 1u;
		c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

		while(value >= 10u)
		{
			value /= 10u;
			error_size++;
		}

		error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

		if(!error_buffer)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_thread_detach, function malloc failed");

			return C_UTILS_RESULT_FAILURE;
		}

		sprintf(error_buffer, "Error in function c_utils_thread_detach, function CloseHandle failed, error code: %u", (c_utils_uint32_t)error);

		C_UTILS_REPORT_ERROR(error_buffer);

		free((c_utils_void_t *)error_buffer);

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	const signed int result = pthread_detach(thread);

	if(result)
	{
		unsigned int value = (unsigned int)(result < 0 ? -result : result);
		c_utils_size_t prefix_size = strlen("Error in function c_utils_thread_detach, function pthread_detach failed, error code: ");
		c_utils_size_t error_size = (result < 0) ? 2u : 1u;
		c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

		while(value >= 10u)
		{
			value /= 10u;
			error_size++;
		}

		error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

		if(!error_buffer)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_thread_detach, function malloc failed");

			return C_UTILS_RESULT_FAILURE;
		}

		sprintf(error_buffer, "Error in function c_utils_thread_detach, function pthread_detach failed, error code: %d", result);

		C_UTILS_REPORT_ERROR(error_buffer);

		free((c_utils_void_t *)error_buffer);

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
#endif
}

C_UTILS_API c_utils_result_t c_utils_thread_get_id(c_utils_thread_id_t *const thread_id)
{
	if(!thread_id)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_get_id, the thread_id is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

#if defined(_WIN32) || defined(_WIN64)
	*thread_id = GetCurrentThreadId();
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	*thread_id = pthread_self();
#endif

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_thread_yield(c_utils_void_t)
{
#if defined(_WIN32) || defined(_WIN64)
	SwitchToThread();
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	const signed int result = sched_yield();

	if(result)
	{
		unsigned int value = (unsigned int)(result < 0 ? -result : result);
		c_utils_size_t prefix_size = strlen("Error in function c_utils_thread_yield, function sched_yield failed, error code: ");
		c_utils_size_t error_size = (result < 0) ? 2u : 1u;
		c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

		while(value >= 10u)
		{
			value /= 10u;
			error_size++;
		}

		error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

		if(!error_buffer)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_thread_yield, function malloc failed");

			return C_UTILS_RESULT_FAILURE;
		}

		sprintf(error_buffer, "Error in function c_utils_thread_yield, function sched_yield failed, error code: %d", result);

		C_UTILS_REPORT_ERROR(error_buffer);

		free((c_utils_void_t *)error_buffer);

		return C_UTILS_RESULT_FAILURE;
	}
#endif

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_void_t c_utils_thread_exit(const c_utils_int32_t exit_code, c_utils_thread_arguments_t *const arguments)
{
	if(arguments)
	{
		arguments->exit_code = exit_code;
	}

#if defined(_WIN32) || defined(_WIN64)
	ExitThread
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	pthread_exit
#endif
	(
		c_utils_thread_function_return
	);

	return;
}

C_UTILS_API c_utils_result_t c_utils_mutex_create(c_utils_mutex_t *const mutex)
{
	if(!mutex)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_mutex_create, the mutex is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		InitializeCriticalSection(mutex);
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		const signed int result = pthread_mutex_init(mutex, C_UTILS_NULL_POINTER);

		if(result)
		{
			unsigned int value = (unsigned int)(result < 0 ? -result : result);
			c_utils_size_t prefix_size = strlen("Error in function c_utils_mutex_create, function pthread_mutex_init failed, error code: ");
			c_utils_size_t error_size = (result < 0) ? 2u : 1u;
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

			while(value >= 10u)
			{
				value /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_mutex_create, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_mutex_create, function pthread_mutex_init failed, error code: %d", result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_mutex_lock(c_utils_mutex_t *const mutex)
{
	if(!mutex)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_mutex_lock, the mutex is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		EnterCriticalSection(mutex);
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		const signed int result = pthread_mutex_lock(mutex);

		if(result)
		{
			unsigned int value = (unsigned int)(result < 0 ? -result : result);
			c_utils_size_t prefix_size = strlen("Error in function c_utils_mutex_lock, function pthread_mutex_lock failed, error code: ");
			c_utils_size_t error_size = (result < 0) ? 2u : 1u;
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

			while(value >= 10u)
			{
				value /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_mutex_lock, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_mutex_lock, function pthread_mutex_lock failed, error code: %d", result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_mutex_trylock(c_utils_mutex_t *const mutex, c_utils_bool_t *const is_locked)
{
	if(!mutex)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_mutex_trylock, the mutex is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!is_locked)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_mutex_trylock, the is_locked is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		const BOOL result = TryEnterCriticalSection(mutex);

		if(result)
		{
			*is_locked = C_UTILS_TRUE;
		}

		else
		{
			*is_locked = C_UTILS_FALSE;
		}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		const signed int result = pthread_mutex_trylock(mutex);

		if(result == 0)
		{
			*is_locked = C_UTILS_TRUE;
		}

		else if(result == EBUSY) /* EBUSY (16) */
		{
			*is_locked = C_UTILS_FALSE;
		}

		else
		{
			unsigned int value = (unsigned int)(result < 0 ? -result : result);
			c_utils_size_t prefix_size = strlen("Error in function c_utils_mutex_trylock, function pthread_mutex_trylock failed, error code: ");
			c_utils_size_t error_size = (result < 0) ? 2u : 1u;
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

			while(value >= 10u)
			{
				value /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_mutex_trylock, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_mutex_trylock, function pthread_mutex_trylock failed, error code: %d", result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_mutex_unlock(c_utils_mutex_t *const mutex)
{
	if(!mutex)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_mutex_unlock, the mutex is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		LeaveCriticalSection(mutex);
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		const signed int result = pthread_mutex_unlock(mutex);

		if(result)
		{
			unsigned int value = (unsigned int)(result < 0 ? -result : result);
			c_utils_size_t prefix_size = strlen("Error in function c_utils_mutex_unlock, function pthread_mutex_unlock failed, error code: ");
			c_utils_size_t error_size = (result < 0) ? 2u : 1u;
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

			while(value >= 10u)
			{
				value /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_mutex_unlock, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_mutex_unlock, function pthread_mutex_unlock failed, error code: %d", result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_mutex_destroy(c_utils_mutex_t *const mutex)
{
	if(!mutex)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_mutex_destroy, the mutex is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		DeleteCriticalSection(mutex);
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		const signed int result = pthread_mutex_destroy(mutex);

		if(result)
		{
			unsigned int value = (unsigned int)(result < 0 ? -result : result);
			c_utils_size_t prefix_size = strlen("Error in function c_utils_mutex_destroy, function pthread_mutex_destroy failed, error code: ");
			c_utils_size_t error_size = (result < 0) ? 2u : 1u;
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

			while(value >= 10u)
			{
				value /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_mutex_destroy, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_mutex_destroy, function pthread_mutex_destroy failed, error code: %d", result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_condition_variable_create(c_utils_condition_variable_t *const condition_variable)
{
	if(!condition_variable)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_condition_variable_create, the condition_variable is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		InitializeConditionVariable(condition_variable);
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		const signed int result = pthread_cond_init(condition_variable, C_UTILS_NULL_POINTER);

		if(result)
		{
			unsigned int value = (unsigned int)(result < 0 ? -result : result);
			c_utils_size_t prefix_size = strlen("Error in function c_utils_condition_variable_create, function pthread_cond_init failed, error code: ");
			c_utils_size_t error_size = (result < 0) ? 2u : 1u;
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

			while(value >= 10u)
			{
				value /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_condition_variable_create, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_condition_variable_create, function pthread_cond_init failed, error code: %d", result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_condition_variable_wait(c_utils_condition_variable_t *const condition_variable, c_utils_mutex_t *const mutex)
{
	if(!condition_variable)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_condition_variable_wait, the condition_variable is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!mutex)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_condition_variable_wait, the mutex is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		if(!SleepConditionVariableCS(condition_variable, mutex, INFINITE))
		{
			const DWORD error = GetLastError();
			DWORD value = error;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_condition_variable_wait, function SleepConditionVariableCS failed, error code: ");
			c_utils_size_t error_size = 1u;
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

			while(value >= 10u)
			{
				value /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_condition_variable_wait, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_condition_variable_wait, function SleepConditionVariableCS failed, error code: %u", (c_utils_uint32_t)error);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		const signed int result = pthread_cond_wait(condition_variable, mutex);

		if(result)
		{
			unsigned int value = (unsigned int)(result < 0 ? -result : result);
			c_utils_size_t prefix_size = strlen("Error in function c_utils_condition_variable_wait, function pthread_cond_wait failed, error code: ");
			c_utils_size_t error_size = (result < 0) ? 2u : 1u;
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

			while(value >= 10u)
			{
				value /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_condition_variable_wait, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_condition_variable_wait, function pthread_cond_wait failed, error code: %d", result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}
	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_condition_variable_signal(c_utils_condition_variable_t *const condition_variable)
{
	if(!condition_variable)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_condition_variable_signal, the condition_variable is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		WakeConditionVariable(condition_variable);
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		const signed int result = pthread_cond_signal(condition_variable);

		if(result)
		{
			unsigned int value = (unsigned int)(result < 0 ? -result : result);
			c_utils_size_t prefix_size = strlen("Error in function c_utils_condition_variable_signal, function pthread_cond_signal failed, error code: ");
			c_utils_size_t error_size = (result < 0) ? 2u : 1u;
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

			while(value >= 10u)
			{
				value /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_condition_variable_signal, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_condition_variable_signal, function pthread_cond_signal failed, error code: %d", result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_condition_variable_broadcast(c_utils_condition_variable_t *const condition_variable)
{
	if(!condition_variable)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_condition_variable_broadcast, the condition_variable is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		WakeAllConditionVariable(condition_variable);
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		const signed int result = pthread_cond_broadcast(condition_variable);

		if(result)
		{
			unsigned int value = (unsigned int)(result < 0 ? -result : result);
			c_utils_size_t prefix_size = strlen("Error in function c_utils_condition_variable_broadcast, function pthread_cond_broadcast failed, error code: ");
			c_utils_size_t error_size = (result < 0) ? 2u : 1u;
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

			while(value >= 10u)
			{
				value /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_condition_variable_broadcast, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_condition_variable_broadcast, function pthread_cond_broadcast failed, error code: %d", result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_condition_variable_destroy(c_utils_condition_variable_t *const condition_variable)
{
	if(!condition_variable)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_condition_variable_destroy, the condition_variable is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		(c_utils_void_t)condition_variable;
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		const signed int result = pthread_cond_destroy(condition_variable);

		if(result)
		{
			unsigned int value = (unsigned int)(result < 0 ? -result : result);
			c_utils_size_t prefix_size = strlen("Error in function c_utils_condition_variable_destroy, function pthread_cond_destroy failed, error code: ");
			c_utils_size_t error_size = (result < 0) ? 2u : 1u;
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

			while(value >= 10u)
			{
				value /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_condition_variable_destroy, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_condition_variable_destroy, function pthread_cond_destroy failed, error code: %d", result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_semaphore_create(c_utils_semaphore_t *const semaphore, c_utils_uint32_t initial_value)
{
	if(!semaphore)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_semaphore_create, the semaphore is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	semaphore->value = initial_value;

	if(c_utils_mutex_create(&semaphore->mutex))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_semaphore_create, function c_utils_mutex_create failed");

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_condition_variable_create(&semaphore->condition_variable))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_semaphore_create, function c_utils_condition_variable_create failed");

		if(c_utils_mutex_destroy(&semaphore->mutex))
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_semaphore_create, function c_utils_mutex_destroy failed");
		}

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_semaphore_wait(c_utils_semaphore_t *const semaphore)
{
	if(!semaphore)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_semaphore_wait, the semaphore is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_mutex_lock(&semaphore->mutex))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_semaphore_wait, function c_utils_mutex_lock failed");

		return C_UTILS_RESULT_FAILURE;
	}

	while(semaphore->value == 0)
	{
		if(c_utils_condition_variable_wait(&semaphore->condition_variable, &semaphore->mutex))
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_semaphore_wait, function c_utils_condition_variable_wait failed");

			if(c_utils_mutex_unlock(&semaphore->mutex))
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_semaphore_wait, function c_utils_mutex_unlock failed");
			}

			return C_UTILS_RESULT_FAILURE;
		}
	}

	--semaphore->value;

	if(c_utils_mutex_unlock(&semaphore->mutex))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_semaphore_wait, function c_utils_mutex_unlock failed");

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_semaphore_post(c_utils_semaphore_t *const semaphore)
{
	if(!semaphore)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_semaphore_post, the semaphore is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_mutex_lock(&semaphore->mutex))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_semaphore_post, function c_utils_mutex_lock failed");

		return C_UTILS_RESULT_FAILURE;
	}

	if(semaphore->value == 0xFFFFFFFFu)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_semaphore_post, the semaphore value is 0xFFFFFFFF");

		if(c_utils_mutex_unlock(&semaphore->mutex))
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_semaphore_post, function c_utils_mutex_unlock failed");
		}

		return C_UTILS_RESULT_FAILURE;
	}

	++semaphore->value;

	if(c_utils_condition_variable_signal(&semaphore->condition_variable))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_semaphore_post, function c_utils_condition_variable_signal failed");

		if(c_utils_mutex_unlock(&semaphore->mutex))
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_semaphore_post, function c_utils_mutex_unlock failed");
		}

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_mutex_unlock(&semaphore->mutex))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_semaphore_post, function c_utils_mutex_unlock failed");

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_semaphore_destroy(c_utils_semaphore_t *const semaphore)
{
	if(!semaphore)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_semaphore_destroy, the semaphore is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const c_utils_result_t mutex_result = c_utils_mutex_destroy(&semaphore->mutex);
		const c_utils_result_t condition_variable_result = c_utils_condition_variable_destroy(&semaphore->condition_variable);

		if(mutex_result)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_semaphore_destroy, function c_utils_mutex_destroy failed");
		}

		if(condition_variable_result)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_semaphore_destroy, function c_utils_condition_variable_destroy failed");
		}

		if(mutex_result || condition_variable_result)
		{
			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_rwlock_create(c_utils_rwlock_t *const rwlock)
{
	if(!rwlock)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_rwlock_create, the read-write lock is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		InitializeSRWLock(rwlock);
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		const signed int result = pthread_rwlock_init(rwlock, C_UTILS_NULL_POINTER);

		if(result)
		{
			unsigned int value = (unsigned int)(result < 0 ? -result : result);
			c_utils_size_t prefix_size = strlen("Error in function c_utils_rwlock_create, function pthread_rwlock_init failed, error code: ");
			c_utils_size_t error_size = (result < 0) ? 2u : 1u;
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

			while(value >= 10)
			{
				value /= 10;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_rwlock_create, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_rwlock_create, function pthread_rwlock_init failed, error code: %d", result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_rwlock_read_lock(c_utils_rwlock_t *const rwlock)
{
	if(!rwlock)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_rwlock_read_lock, the read-write lock is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		AcquireSRWLockShared(rwlock);
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		const signed int result = pthread_rwlock_rdlock(rwlock);

		if(result)
		{
			unsigned int value = (unsigned int)(result < 0 ? -result : result);
			c_utils_size_t prefix_size = strlen("Error in function c_utils_rwlock_read_lock, function pthread_rwlock_rdlock failed, error code: ");
			c_utils_size_t error_size = (result < 0) ? 2u : 1u;
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

			while(value >= 10)
			{
				value /= 10;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_rwlock_read_lock, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_rwlock_read_lock, function pthread_rwlock_rdlock failed, error code: %d", result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_rwlock_write_lock(c_utils_rwlock_t *const rwlock)
{
	if(!rwlock)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_rwlock_write_lock, the read-write lock is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		AcquireSRWLockExclusive(rwlock);
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		const signed int result = pthread_rwlock_wrlock(rwlock);

		if(result)
		{
			unsigned int value = (unsigned int)(result < 0 ? -result : result);
			c_utils_size_t prefix_size = strlen("Error in function c_utils_rwlock_write_lock, function pthread_rwlock_wrlock failed, error code: ");
			c_utils_size_t error_size = (result < 0) ? 2u : 1u;
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

			while(value >= 10)
			{
				value /= 10;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_rwlock_write_lock, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_rwlock_write_lock, function pthread_rwlock_wrlock failed, error code: %d", result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_rwlock_unlock(c_utils_rwlock_t *const rwlock, const c_utils_bool_t is_write_lock)
{
	if(!rwlock)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_rwlock_unlock, the read-write lock is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		if(is_write_lock)
		{
			ReleaseSRWLockExclusive(rwlock);
		}

		else
		{
			ReleaseSRWLockShared(rwlock);
		}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		const signed int result = pthread_rwlock_unlock(rwlock);
		(c_utils_void_t)is_write_lock;

		if(result)
		{
			unsigned int value = (unsigned int)(result < 0 ? -result : result);
			c_utils_size_t prefix_size = strlen("Error in function c_utils_rwlock_unlock, function pthread_rwlock_unlock failed, error code: ");
			c_utils_size_t error_size = (result < 0) ? 2u : 1u;
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

			while(value >= 10)
			{
				value /= 10;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_rwlock_unlock, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_rwlock_unlock, function pthread_rwlock_unlock failed, error code: %d", result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_rwlock_destroy(c_utils_rwlock_t *const rwlock)
{
	if(!rwlock)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_rwlock_destroy, the read-write lock is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		(c_utils_void_t)rwlock;
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		const signed int result = pthread_rwlock_destroy(rwlock);

		if(result)
		{
			unsigned int value = (unsigned int)(result < 0 ? -result : result);
			c_utils_size_t prefix_size = strlen("Error in function c_utils_rwlock_destroy, function pthread_rwlock_destroy failed, error code: ");
			c_utils_size_t error_size = (result < 0) ? 2u : 1u;
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

			while(value >= 10)
			{
				value /= 10;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_rwlock_destroy, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_rwlock_destroy, function pthread_rwlock_destroy failed, error code: %d", result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_tls_create(c_utils_tls_key_t *const key)
{
	if(!key)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_tls_create, the key is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		*key = TlsAlloc();

		if(*key == TLS_OUT_OF_INDEXES)
		{
			const DWORD error = GetLastError();
			DWORD value = error;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_tls_create, function TlsAlloc failed, error code: ");
			c_utils_size_t error_size = 1u;
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

			while(value >= 10)
			{
				value /= 10;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_tls_create, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_tls_create, function TlsAlloc failed, error code: %u", (c_utils_uint32_t)error);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		const signed int result = pthread_key_create(key, C_UTILS_NULL_POINTER);

		if(result)
		{
			unsigned int value = (unsigned int)(result < 0 ? -result : result);
			c_utils_size_t prefix_size = strlen("Error in function c_utils_tls_create, function pthread_key_create failed, error code: ");
			c_utils_size_t error_size = (result < 0) ? 2u : 1u;
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

			while(value >= 10)
			{
				value /= 10;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_tls_create, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_tls_create, function pthread_key_create failed, error code: %d", result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_tls_set(c_utils_tls_key_t key, c_utils_void_t *const input)
{
#if defined(_WIN32) || defined(_WIN64)
	if(!TlsSetValue(key, input))
	{
		const DWORD error = GetLastError();
		DWORD value = error;
		c_utils_size_t prefix_size = strlen("Error in function c_utils_tls_set, function TlsSetValue failed, error code: ");
		c_utils_size_t error_size = 1u;
		c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

		while(value >= 10u)
		{
			value /= 10u;
			error_size++;
		}

		error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

		if(!error_buffer)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_tls_set, function malloc failed");

			return C_UTILS_RESULT_FAILURE;
		}

		sprintf(error_buffer, "Error in function c_utils_tls_set, function TlsSetValue failed, error code: %u", (c_utils_uint32_t)error);

		C_UTILS_REPORT_ERROR(error_buffer);

		free((c_utils_void_t *)error_buffer);

		return C_UTILS_RESULT_FAILURE;
	}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	const signed int result = pthread_setspecific(key, input);

	if(result)
	{
		unsigned int value = (unsigned int)(result < 0 ? -result : result);
		c_utils_size_t prefix_size = strlen("Error in function c_utils_tls_set, function pthread_setspecific failed, error code: ");
		c_utils_size_t error_size = (result < 0) ? 2u : 1u;
		c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

		while(value >= 10u)
		{
			value /= 10u;
			error_size++;
		}

		error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

		if(!error_buffer)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_tls_set, function malloc failed");

			return C_UTILS_RESULT_FAILURE;
		}

		sprintf(error_buffer, "Error in function c_utils_tls_set, function pthread_setspecific failed, error code: %d", result);

		C_UTILS_REPORT_ERROR(error_buffer);

		free((c_utils_void_t *)error_buffer);

		return C_UTILS_RESULT_FAILURE;
	}
#endif

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_tls_get(c_utils_tls_key_t key, c_utils_void_t *const output)
{
	if(!output)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_tls_get, the output is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		c_utils_void_t **const type_output = (c_utils_void_t **const)output;
#if defined(_WIN32) || defined(_WIN64)
		c_utils_void_t *value;
		DWORD error;

		SetLastError(ERROR_SUCCESS);

		value = TlsGetValue(key);
		error = GetLastError();

		if(value == C_UTILS_NULL_POINTER && error != ERROR_SUCCESS)
		{
			DWORD value = error;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_tls_get, function TlsGetValue failed, error code: ");
			c_utils_size_t error_size = 1u;
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

			while(value >= 10u)
			{
				value /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_tls_get, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_tls_get, function TlsGetValue failed, error code: %u", (c_utils_uint32_t)error);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}

		*type_output = value;
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)

		*type_output = pthread_getspecific(key);
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_tls_destroy(c_utils_tls_key_t key)
{
#if defined(_WIN32) || defined(_WIN64)
	if(!TlsFree(key))
	{
		const DWORD error = GetLastError();
		DWORD value = error;
		c_utils_size_t prefix_size = strlen("Error in function c_utils_tls_destroy, function TlsFree failed, error code: ");
		c_utils_size_t error_size = 1u;
		c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

		while(value >= 10u)
		{
			value /= 10u;
			error_size++;
		}

		error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

		if(!error_buffer)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_tls_destroy, function malloc failed");

			return C_UTILS_RESULT_FAILURE;
		}

		sprintf(error_buffer, "Error in function c_utils_tls_destroy, function TlsFree failed, error code: %u", (c_utils_uint32_t)error);

		C_UTILS_REPORT_ERROR(error_buffer);

		free((c_utils_void_t *)error_buffer);

		return C_UTILS_RESULT_FAILURE;
	}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	const signed int result = pthread_key_delete(key);

	if(result)
	{
		unsigned int value = (unsigned int)(result < 0 ? -result : result);
		c_utils_size_t prefix_size = strlen("Error in function c_utils_tls_destroy, function pthread_key_delete failed, error code: ");
		c_utils_size_t error_size = (result < 0) ? 2u : 1u;
		c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;

		while(value >= 10u)
		{
			value /= 10u;
			error_size++;
		}

		error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

		if(!error_buffer)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_tls_destroy, function malloc failed");

			return C_UTILS_RESULT_FAILURE;
		}

		sprintf(error_buffer, "Error in function c_utils_tls_destroy, function pthread_key_delete failed, error code: %d", result);

		C_UTILS_REPORT_ERROR(error_buffer);

		free((c_utils_void_t *)error_buffer);

		return C_UTILS_RESULT_FAILURE;
	}
#endif

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_barrier_create(c_utils_barrier_t *const barrier, c_utils_uint32_t count)
{
	if(!barrier)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_barrier_create, the barrier is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(count == 0)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_barrier_create, the count is zero");

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_mutex_create(&barrier->mutex))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_barrier_create, function c_utils_mutex_create failed");

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_condition_variable_create(&barrier->condition_variable))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_barrier_create, function c_utils_condition_variable_create failed");

		if(c_utils_mutex_destroy(&barrier->mutex))
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_barrier_create, function c_utils_mutex_destroy failed");
		}

		return C_UTILS_RESULT_FAILURE;
	}

	barrier->total = count;
	barrier->count = count;
	barrier->cycle = 0;

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_barrier_wait(c_utils_barrier_t *const barrier)
{
	if(!barrier)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_barrier_wait, the barrier is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_mutex_lock(&barrier->mutex))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_barrier_wait, function c_utils_mutex_lock failed");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		c_utils_uint32_t cycle = barrier->cycle;

		if(--barrier->count == 0)
		{
			++barrier->cycle;
			barrier->count = barrier->total;

			if(c_utils_condition_variable_broadcast(&barrier->condition_variable))
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_barrier_wait, function c_utils_condition_variable_broadcast failed");

				if(c_utils_mutex_unlock(&barrier->mutex))
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_barrier_wait, function c_utils_mutex_unlock failed");
				}

				return C_UTILS_RESULT_FAILURE;
			}

			if(c_utils_mutex_unlock(&barrier->mutex))
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_barrier_wait, function c_utils_mutex_unlock failed");

				return C_UTILS_RESULT_FAILURE;
			}

			return C_UTILS_RESULT_SUCCESS;
		}

		while(barrier->cycle == cycle)
		{
			if(c_utils_condition_variable_wait(&barrier->condition_variable, &barrier->mutex))
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_barrier_wait, function c_utils_condition_variable_wait failed");

				if(c_utils_mutex_unlock(&barrier->mutex))
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_barrier_wait, function c_utils_mutex_unlock failed");
				}

				return C_UTILS_RESULT_FAILURE;
			}
		}

		if(c_utils_mutex_unlock(&barrier->mutex))
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_barrier_wait, function c_utils_mutex_unlock failed");

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_barrier_destroy(c_utils_barrier_t *const barrier)
{
	if(!barrier)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_barrier_destroy, the barrier is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_condition_variable_destroy(&barrier->condition_variable))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_barrier_destroy, function c_utils_condition_variable_destroy failed");

		if(c_utils_mutex_destroy(&barrier->mutex))
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_barrier_destroy, function c_utils_mutex_destroy failed");
		}

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_mutex_destroy(&barrier->mutex))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_barrier_destroy, function c_utils_mutex_destroy failed");

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_thread_pool_create(c_utils_thread_pool_t *const pool, c_utils_size_t thread_count)
{
	if(!pool)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_create, the thread pool is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!thread_count)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_create, the thread count is zero");

		return C_UTILS_RESULT_FAILURE;
	}

	if(thread_count > ((c_utils_size_t)-1) / sizeof(c_utils_thread_t))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_create, the thread count causes a size overflow");

		return C_UTILS_RESULT_FAILURE;
	}

	pool->thread_count = thread_count;
	pool->head = C_UTILS_NULL_POINTER;
	pool->tail = C_UTILS_NULL_POINTER;
	pool->pending_tasks = 0;
	pool->active_tasks = 0;
	pool->stop = C_UTILS_FALSE;

	if(c_utils_mutex_create(&pool->mutex))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_create, function c_utils_mutex_create failed");

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_condition_variable_create(&pool->condition_has_tasks))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_create, function c_utils_condition_variable_create failed");

		if(c_utils_mutex_destroy(&pool->mutex))
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_create, function c_utils_mutex_destroy failed");
		}

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_condition_variable_create(&pool->condition_idle))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_create, function c_utils_condition_variable_create failed");

		if(c_utils_condition_variable_destroy(&pool->condition_has_tasks))
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_create, function c_utils_condition_variable_destroy failed");
		}

		if(c_utils_mutex_destroy(&pool->mutex))
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_create, function c_utils_mutex_destroy failed");
		}

		return C_UTILS_RESULT_FAILURE;
	}

	pool->threads = (c_utils_thread_t *)malloc(sizeof(*pool->threads) * thread_count);

	if(!pool->threads)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_create, function malloc failed");

		if(c_utils_condition_variable_destroy(&pool->condition_idle))
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_create, function c_utils_condition_variable_destroy failed");
		}

		if(c_utils_condition_variable_destroy(&pool->condition_has_tasks))
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_create, function c_utils_condition_variable_destroy failed");
		}

		if(c_utils_mutex_destroy(&pool->mutex))
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_create, function c_utils_mutex_destroy failed");
		}

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		c_utils_size_t created_threads = 0u;
		c_utils_size_t i;
		c_utils_size_t j;

		for(i = 0u; i < thread_count; ++i)
		{
			if(c_utils_thread_create(&pool->threads[i], c_utils_thread_pool_worker, pool))
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_create, function c_utils_thread_create failed");

				if(!c_utils_mutex_lock(&pool->mutex))
				{
					pool->stop = C_UTILS_TRUE;

					if(c_utils_condition_variable_broadcast(&pool->condition_has_tasks))
					{
						C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_create, function c_utils_condition_variable_broadcast failed");
					}

					if(c_utils_mutex_unlock(&pool->mutex))
					{
						C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_create, function c_utils_mutex_unlock failed");
					}
				}
				else
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_create, function c_utils_mutex_lock failed");
				}

				for(j = 0u; j < created_threads; ++j)
				{
					if(c_utils_thread_join(pool->threads[j]))
					{
						C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_create, function c_utils_thread_join failed");
					}
				}

				free((c_utils_void_t *)pool->threads);

				if(c_utils_condition_variable_destroy(&pool->condition_idle))
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_create, function c_utils_condition_variable_destroy failed");
				}

				if(c_utils_condition_variable_destroy(&pool->condition_has_tasks))
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_create, function c_utils_condition_variable_destroy failed");
				}

				if(c_utils_mutex_destroy(&pool->mutex))
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_create, function c_utils_mutex_destroy failed");
				}

				return C_UTILS_RESULT_FAILURE;
			}

			++created_threads;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_thread_pool_add_task(c_utils_thread_pool_t *const pool, c_utils_task_function_pointer function, c_utils_void_t *arguments)
{
	if(!pool)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_add_task, the thread pool is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!function)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_add_task, the function is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		c_utils_task_node_t *node = (c_utils_task_node_t *)malloc(sizeof(*node));

		if(!node)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_add_task, function malloc failed");

			return C_UTILS_RESULT_FAILURE;
		}

		node->function = function;
		node->arguments = arguments;
		node->next = C_UTILS_NULL_POINTER;

		if(c_utils_mutex_lock(&pool->mutex))
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_add_task, function c_utils_mutex_lock failed");

			free((c_utils_void_t *)node);

			return C_UTILS_RESULT_FAILURE;
		}

		if(pool->stop)
		{
			if(c_utils_mutex_unlock(&pool->mutex))
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_add_task, function c_utils_mutex_unlock failed");
			}

			free((c_utils_void_t *)node);

			return C_UTILS_RESULT_FAILURE;
		}

		if(!pool->tail)
		{
			pool->head = node;
			pool->tail = node;
		}

		else
		{
			pool->tail->next = node;
			pool->tail = node;
		}

		++pool->pending_tasks;

		if(c_utils_condition_variable_signal(&pool->condition_has_tasks))
		{
			c_utils_task_node_t *current = pool->head;

			C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_add_task, function c_utils_condition_variable_signal failed");

			if(current == node)
			{
				pool->head = C_UTILS_NULL_POINTER;
				pool->tail = C_UTILS_NULL_POINTER;
			}

			else
			{
				while(current->next != node)
				{
					current = current->next;
				}

				current->next = C_UTILS_NULL_POINTER;
				pool->tail = current;
			}

			--pool->pending_tasks;

			if(c_utils_mutex_unlock(&pool->mutex))
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_add_task, function c_utils_mutex_unlock failed");
			}

			free((c_utils_void_t *)node);

			return C_UTILS_RESULT_FAILURE;
		}

		if(c_utils_mutex_unlock(&pool->mutex))
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_add_task, function c_utils_mutex_unlock failed");

			free((c_utils_void_t *)node);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_thread_pool_wait(c_utils_thread_pool_t *const pool)
{
	if(!pool)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_wait, the thread pool is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_mutex_lock(&pool->mutex))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_wait, function c_utils_mutex_lock failed");

		return C_UTILS_RESULT_FAILURE;
	}

	while((pool->pending_tasks > 0 || pool->active_tasks > 0) && !pool->stop)
	{
		if(c_utils_condition_variable_wait(&pool->condition_idle, &pool->mutex))
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_wait, function c_utils_condition_variable_wait failed");

			if(c_utils_mutex_unlock(&pool->mutex))
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_wait, function c_utils_mutex_unlock failed");
			}

			return C_UTILS_RESULT_FAILURE;
		}
	}

	if(c_utils_mutex_unlock(&pool->mutex))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_wait, function c_utils_mutex_unlock failed");

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_thread_pool_clear(c_utils_thread_pool_t *const pool)
{
	if(!pool)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_clear, the thread pool is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_mutex_lock(&pool->mutex))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_clear, function c_utils_mutex_lock failed");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		c_utils_task_node_t *current = pool->head;

		while(current)
		{
			c_utils_task_node_t *temporary = current;
			current = current->next;

			free((c_utils_void_t *)temporary);
		}

		pool->head = C_UTILS_NULL_POINTER;
		pool->tail = C_UTILS_NULL_POINTER;
		pool->pending_tasks = 0;

		if(pool->active_tasks == 0)
		{
			if(c_utils_condition_variable_broadcast(&pool->condition_idle))
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_clear, function c_utils_condition_variable_broadcast failed");

				if(c_utils_mutex_unlock(&pool->mutex))
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_clear, function c_utils_mutex_unlock failed");
				}

				return C_UTILS_RESULT_FAILURE;
			}
		}

		if(c_utils_mutex_unlock(&pool->mutex))
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_clear, function c_utils_mutex_unlock failed");

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_thread_pool_get_pending_tasks(c_utils_thread_pool_t *const pool, c_utils_size_t *const output)
{
	if(!pool)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_get_pending_tasks, the thread pool is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!output)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_get_pending_tasks, the output is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_mutex_lock(&pool->mutex))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_get_pending_tasks, function c_utils_mutex_lock failed");

		return C_UTILS_RESULT_FAILURE;
	}

	*output = pool->pending_tasks;

	if(c_utils_mutex_unlock(&pool->mutex))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_get_pending_tasks, function c_utils_mutex_unlock failed");

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_thread_pool_get_active_tasks(c_utils_thread_pool_t *const pool, c_utils_size_t *const output)
{
	if(!pool)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_get_active_tasks, the thread pool is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!output)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_get_active_tasks, the output is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_mutex_lock(&pool->mutex))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_get_active_tasks, function c_utils_mutex_lock failed");

		return C_UTILS_RESULT_FAILURE;
	}

	*output = pool->active_tasks;

	if(c_utils_mutex_unlock(&pool->mutex))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_get_active_tasks, function c_utils_mutex_unlock failed");

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_thread_pool_get_thread_count(c_utils_thread_pool_t *const pool, c_utils_size_t *const output)
{
	if(!pool)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_get_thread_count, the thread pool is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!output)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_get_thread_count, the output is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_mutex_lock(&pool->mutex))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_get_thread_count, function c_utils_mutex_lock failed");

		return C_UTILS_RESULT_FAILURE;
	}

	*output = pool->thread_count;

	if(c_utils_mutex_unlock(&pool->mutex))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_get_thread_count, function c_utils_mutex_unlock failed");

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_thread_pool_destroy(c_utils_thread_pool_t *const pool)
{
	if(!pool)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_destroy, the thread pool is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_mutex_lock(&pool->mutex))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_destroy, function c_utils_mutex_lock failed");

		return C_UTILS_RESULT_FAILURE;
	}

	pool->stop = C_UTILS_TRUE;

	if(c_utils_condition_variable_broadcast(&pool->condition_has_tasks))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_destroy, function c_utils_condition_variable_broadcast failed");

		if(c_utils_mutex_unlock(&pool->mutex))
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_destroy, function c_utils_mutex_unlock failed");
		}

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_mutex_unlock(&pool->mutex))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_destroy, function c_utils_mutex_unlock failed");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		c_utils_size_t i;
		c_utils_task_node_t *current;

		for(i = 0; i < pool->thread_count; ++i)
		{
			if(c_utils_thread_join(pool->threads[i]))
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_destroy, function c_utils_thread_join failed");
			}
		}

		free((c_utils_void_t *)pool->threads);

		pool->threads = C_UTILS_NULL_POINTER;
		current = pool->head;

		while(current)
		{
			c_utils_task_node_t *temporary = current;
			current = current->next;

			free((c_utils_void_t *)temporary);
		}

		pool->head = C_UTILS_NULL_POINTER;
		pool->tail = C_UTILS_NULL_POINTER;
		pool->pending_tasks = 0u;
		pool->active_tasks = 0u;

		if(c_utils_condition_variable_destroy(&pool->condition_idle))
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_destroy, function c_utils_condition_variable_destroy failed");

			return C_UTILS_RESULT_FAILURE;
		}

		if(c_utils_condition_variable_destroy(&pool->condition_has_tasks))
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_destroy, function c_utils_condition_variable_destroy failed");

			return C_UTILS_RESULT_FAILURE;
		}

		if(c_utils_mutex_destroy(&pool->mutex))
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_thread_pool_destroy, function c_utils_mutex_destroy failed");

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif
