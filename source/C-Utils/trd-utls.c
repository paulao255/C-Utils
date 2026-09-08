/*************************/
/* Library importations: */
/*************************/

#include "C-Utils/trd-utls.h"
#include <errno.h>
#include <stdio.h>
#if defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
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

extern c_utils_result_t c_utils_get_processor_count(c_utils_int32_t *const output)
{
	if(!output)
	{
		fprintf(stderr, "Error in function c_utils_get_processor_count, the output is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);


		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		const DWORD count = GetActiveProcessorCount(ALL_PROCESSOR_GROUPS);

		if(count == 0)
		{
			const DWORD error = GetLastError();

			fprintf(stderr, "Error in function c_utils_get_processor_count, function GetActiveProcessorCount (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %u\n", (c_utils_uint32_t)error);

			return C_UTILS_RESULT_FAILURE;
		}

		*output = (c_utils_int32_t)count;
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		const signed long int count = sysconf(_SC_NPROCESSORS_ONLN);

		if(count == -1)
		{
			fprintf(stderr, "Error in function c_utils_get_processor_count, function sysconf (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_RESULT_FAILURE;
		}

		*output = (c_utils_int32_t)count;
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_thread_create(c_utils_thread_t *const thread, c_utils_thread_function_t (*f)(c_utils_void_t *arguments), c_utils_void_t *arguments)
{
	if(!thread)
	{
		fprintf(stderr, "Error in function c_utils_thread_create, the thread is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!f)
	{
		fprintf(stderr, "Error in function c_utils_thread_create, the function is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		*thread = CreateThread(C_UTILS_NULL_POINTER, 0UL, (LPTHREAD_START_ROUTINE)f, arguments, 0, C_UTILS_NULL_POINTER);

		if(!*thread)
		{
			const DWORD error = GetLastError();

			fprintf(stderr, "Error in function c_utils_thread_create, function CreateThread (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %u\n", (c_utils_uint32_t)error);

			return C_UTILS_RESULT_FAILURE;
		}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		const signed int result = pthread_create(thread, C_UTILS_NULL_POINTER, f, arguments);

		if(result)
		{
			fprintf(stderr, "Error in function c_utils_thread_create, function pthread_create (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %d\n", result);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_thread_join(c_utils_thread_t thread)
{
#if defined(_WIN32) || defined(_WIN64)
	if(WaitForSingleObject(thread, INFINITE) != WAIT_OBJECT_0)
	{
		DWORD error = GetLastError();

		fprintf(stderr, "Error in function c_utils_thread_join, function WaitForSingleObject (File: %s, Line: %d)...\n", __FILE__, __LINE__);
		fprintf(stderr, "Error code: %u\n", (c_utils_uint32_t)error);

		if(!CloseHandle(thread))
		{
			error = GetLastError();

			fprintf(stderr, "Error in function c_utils_thread_join, function CloseHandle (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %u\n", (c_utils_uint32_t)error);
		}

		return C_UTILS_RESULT_FAILURE;
	}

	if(!CloseHandle(thread))
	{
		const DWORD error = GetLastError();

		fprintf(stderr, "Error in function c_utils_thread_join, function CloseHandle (File: %s, Line: %d)...\n", __FILE__, __LINE__);
		fprintf(stderr, "Error code: %u\n", (c_utils_uint32_t)error);

		return C_UTILS_RESULT_FAILURE;
	}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	const signed int result = pthread_join(thread, C_UTILS_NULL_POINTER);

	if(result)
	{
		fprintf(stderr, "Error in function c_utils_thread_join, function pthread_join (File: %s, Line: %d)...\n", __FILE__, __LINE__);
		fprintf(stderr, "Error code: %d\n", result);

		return C_UTILS_RESULT_FAILURE;
	}
#endif

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_thread_detach(c_utils_thread_t thread)
{
#if defined(_WIN32) || defined(_WIN64)
	const BOOL result = CloseHandle(thread);

	if(!result)
	{
		const DWORD error = GetLastError();

		fprintf(stderr, "Error in function c_utils_thread_detach, function CloseHandle (File: %s, Line: %d)...\n", __FILE__, __LINE__);
		fprintf(stderr, "Error code: %u\n", (c_utils_uint32_t)error);

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	const signed int result = pthread_detach(thread);

	if(result)
	{
		fprintf(stderr, "Error in function c_utils_thread_detach, function pthread_detach (File: %s, Line: %d)...\n", __FILE__, __LINE__);
		fprintf(stderr, "Error code: %d\n", result);

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
#endif
}

extern c_utils_result_t c_utils_thread_get_id(c_utils_thread_id_t *const thread_id)
{
	if(!thread_id)
	{
		fprintf(stderr, "Error in function c_utils_thread_get_id, the thread is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

#if defined(_WIN32) || defined(_WIN64)
	*thread_id = GetCurrentThreadId();
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	*thread_id = pthread_self();
#endif

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_thread_yield(c_utils_void_t)
{
#if defined(_WIN32) || defined(_WIN64)
	SwitchToThread();
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	const signed int result = sched_yield();

	if(result)
	{
		fprintf(stderr, "Error in function c_utils_thread_yield, function sched_yield (File: %s, Line: %d)...\n", __FILE__, __LINE__);
		fprintf(stderr, "Error code: %d\n", result);

		return C_UTILS_RESULT_FAILURE;
	}
#endif

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_void_t c_utils_thread_exit(const c_utils_int32_t exit_code, c_utils_thread_arguments_t *const arguments)
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

extern c_utils_result_t c_utils_mutex_create(c_utils_mutex_t *const mutex)
{
	if(!mutex)
	{
		fprintf(stderr, "Error in function c_utils_mutex_create, the mutex is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

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
			fprintf(stderr, "Error in function c_utils_mutex_create, function pthread_mutex_init (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %d\n", result);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_mutex_lock(c_utils_mutex_t *const mutex)
{
	if(!mutex)
	{
		fprintf(stderr, "Error in function c_utils_mutex_lock, the mutex is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

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
			fprintf(stderr, "Error in function c_utils_mutex_lock, function pthread_mutex_lock (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %d\n", result);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_mutex_trylock(c_utils_mutex_t *const mutex, c_utils_bool_t *const is_locked)
{
	if(!mutex)
	{
		fprintf(stderr, "Error in function c_utils_mutex_trylock, the mutex is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!is_locked)
	{
		fprintf(stderr, "Error in function c_utils_mutex_trylock, the is_locked is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

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
			fprintf(stderr, "Error in function c_utils_mutex_trylock, function pthread_mutex_trylock (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %d\n", result);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_mutex_unlock(c_utils_mutex_t *const mutex)
{
	if(!mutex)
	{
		fprintf(stderr, "Error in function c_utils_mutex_unlock, the mutex is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

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
			fprintf(stderr, "Error in function c_utils_mutex_unlock, function pthread_mutex_unlock (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %d\n", result);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_mutex_destroy(c_utils_mutex_t *const mutex)
{
	if(!mutex)
	{
		fprintf(stderr, "Error in function c_utils_mutex_destroy, the mutex is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

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
			fprintf(stderr, "Error in function c_utils_mutex_destroy, function pthread_mutex_destroy (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %d\n", result);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_condition_variable_create(c_utils_condition_variable_t *const condition_variable)
{
	if(!condition_variable)
	{
		fprintf(stderr, "Error in function c_utils_condition_variable_create, the condition_variable is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

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
			fprintf(stderr, "Error in function c_utils_condition_variable_create, function pthread_cond_init (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %d\n", result);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_condition_variable_wait(c_utils_condition_variable_t *const condition_variable, c_utils_mutex_t *const mutex)
{
	if(!condition_variable)
	{
		fprintf(stderr, "Error in function c_utils_condition_variable_wait, the condition_variable is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!mutex)
	{
		fprintf(stderr, "Error in function c_utils_condition_variable_wait, the mutex is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		if(!SleepConditionVariableCS(condition_variable, mutex, INFINITE))
		{
			const DWORD error = GetLastError();

			fprintf(stderr, "Error in function c_utils_condition_variable_wait, function SleepConditionVariableCS (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %u\n", (c_utils_uint32_t)error);

			return C_UTILS_RESULT_FAILURE;
		}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		const signed int result = pthread_cond_wait(condition_variable, mutex);

		if(result)
		{
			fprintf(stderr, "Error in function c_utils_condition_variable_wait, function pthread_cond_wait (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %d\n", result);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}
	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_condition_variable_signal(c_utils_condition_variable_t *const condition_variable)
{
	if(!condition_variable)
	{
		fprintf(stderr, "Error in function c_utils_condition_variable_signal, the condition_variable is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

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
			fprintf(stderr, "Error in function c_utils_condition_variable_signal, function pthread_cond_signal (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %d\n", result);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_condition_variable_broadcast(c_utils_condition_variable_t *const condition_variable)
{
	if(!condition_variable)
	{
		fprintf(stderr, "Error in function c_utils_condition_variable_broadcast, the condition_variable is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

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
			fprintf(stderr, "Error in function c_utils_condition_variable_broadcast, function pthread_cond_broadcast (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %d\n", result);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_condition_variable_destroy(c_utils_condition_variable_t *const condition_variable)
{
	if(!condition_variable)
	{
		fprintf(stderr, "Error in function c_utils_condition_variable_destroy, the condition_variable is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

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
			fprintf(stderr, "Error in function c_utils_condition_variable_destroy, function pthread_cond_destroy (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %d\n", result);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_semaphore_create(c_utils_semaphore_t *const semaphore, c_utils_uint32_t initial_value)
{
	if(!semaphore)
	{
		fprintf(stderr, "Error in function c_utils_semaphore_create, the semaphore is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	semaphore->value = initial_value;

	if(c_utils_mutex_create(&semaphore->mutex))
	{
		fprintf(stderr, "Error in function c_utils_semaphore_create, function c_utils_mutex_create failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_condition_variable_create(&semaphore->condition_variable))
	{
		fprintf(stderr, "Error in function c_utils_semaphore_create, function c_utils_condition_variable_create failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		if(c_utils_mutex_destroy(&semaphore->mutex))
		{
			fprintf(stderr, "Error in function c_utils_semaphore_create, function c_utils_mutex_destroy failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);
		}

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_semaphore_wait(c_utils_semaphore_t *const semaphore)
{
	if(!semaphore)
	{
		fprintf(stderr, "Error in function c_utils_semaphore_wait, the semaphore is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_mutex_lock(&semaphore->mutex))
	{
		fprintf(stderr, "Error in function c_utils_semaphore_wait, function c_utils_mutex_lock failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	while(semaphore->value == 0)
	{
		if(c_utils_condition_variable_wait(&semaphore->condition_variable, &semaphore->mutex))
		{
			if(c_utils_mutex_unlock(&semaphore->mutex))
			{
				fprintf(stderr, "Error in function c_utils_semaphore_wait, function c_utils_mutex_unlock failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			}

			return C_UTILS_RESULT_FAILURE;
		}
	}

	--semaphore->value;

	if(c_utils_mutex_unlock(&semaphore->mutex))
	{
		fprintf(stderr, "Error in function c_utils_semaphore_wait, function c_utils_mutex_unlock failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_semaphore_post(c_utils_semaphore_t *const semaphore)
{
	if(!semaphore)
	{
		fprintf(stderr, "Error in function c_utils_semaphore_post, the semaphore is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_mutex_lock(&semaphore->mutex))
	{
		fprintf(stderr, "Error in function c_utils_semaphore_post, function c_utils_mutex_lock failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	++semaphore->value;

	if(c_utils_condition_variable_signal(&semaphore->condition_variable))
	{
		if(c_utils_mutex_unlock(&semaphore->mutex))
		{
			fprintf(stderr, "Error in function c_utils_semaphore_post, function c_utils_mutex_unlock failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);
		}

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_mutex_unlock(&semaphore->mutex))
	{
		fprintf(stderr, "Error in function c_utils_semaphore_post, function c_utils_mutex_unlock failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_semaphore_destroy(c_utils_semaphore_t *const semaphore)
{
	if(!semaphore)
	{
		fprintf(stderr, "Error in function c_utils_semaphore_destroy, the semaphore is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const c_utils_result_t mutex_result = c_utils_mutex_destroy(&semaphore->mutex);
		const c_utils_result_t condition_variable_result = c_utils_condition_variable_destroy(&semaphore->condition_variable);

		if(mutex_result)
		{
			fprintf(stderr, "Error in function c_utils_semaphore_destroy, function c_utils_mutex_destroy failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);
		}

		if(condition_variable_result)
		{
			fprintf(stderr, "Error in function c_utils_semaphore_destroy, function c_utils_condition_variable_destroy failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);
		}

		if(mutex_result || condition_variable_result)
		{
			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_rwlock_create(c_utils_rwlock_t *const rwlock)
{
	if(!rwlock)
	{
		fprintf(stderr, "Error in function c_utils_rwlock_create, the read-write lock is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

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
			fprintf(stderr, "Error in function c_utils_rwlock_create, function pthread_rwlock_init failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %d\n", result);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_rwlock_read_lock(c_utils_rwlock_t *const rwlock)
{
	if(!rwlock)
	{
		fprintf(stderr, "Error in function c_utils_rwlock_read_lock, the read-write lock is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

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
			fprintf(stderr, "Error in function c_utils_rwlock_read_lock, function pthread_rwlock_rdlock failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %d\n", result);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_rwlock_write_lock(c_utils_rwlock_t *const rwlock)
{
	if(!rwlock)
	{
		fprintf(stderr, "Error in function c_utils_rwlock_write_lock, the read-write lock is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

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
			fprintf(stderr, "Error in function c_utils_rwlock_write_lock, function pthread_rwlock_wrlock failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %d\n", result);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_rwlock_unlock(c_utils_rwlock_t *const rwlock, const c_utils_bool_t is_write_lock)
{
	if(!rwlock)
	{
		fprintf(stderr, "Error in function c_utils_rwlock_unlock, the read-write lock is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

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
			fprintf(stderr, "Error in function c_utils_rwlock_unlock, function pthread_rwlock_unlock failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %d\n", result);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_rwlock_destroy(c_utils_rwlock_t *const rwlock)
{
	if(!rwlock)
	{
		fprintf(stderr, "Error in function c_utils_rwlock_destroy, the read-write lock is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

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
			fprintf(stderr, "Error in function c_utils_rwlock_destroy, function pthread_rwlock_destroy failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %d\n", result);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_tls_create(c_utils_tls_key_t *const key)
{
	if(!key)
	{
		fprintf(stderr, "Error in function c_utils_tls_create, the key is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		*key = TlsAlloc();

		if(*key == TLS_OUT_OF_INDEXES)
		{
			const DWORD error = GetLastError();

			fprintf(stderr, "Error in function c_utils_tls_create, function TlsAlloc failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %u\n", (c_utils_uint32_t)error);

			return C_UTILS_RESULT_FAILURE;
		}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		const signed int result = pthread_key_create(key, C_UTILS_NULL_POINTER);

		if(result)
		{
			fprintf(stderr, "Error in function c_utils_tls_create, function pthread_key_create failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %d\n", result);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_tls_set(c_utils_tls_key_t key, c_utils_void_t *const value)
{
#if defined(_WIN32) || defined(_WIN64)
	if(!TlsSetValue(key, value))
	{
		const DWORD error = GetLastError();

		fprintf(stderr, "Error in function c_utils_tls_set, function TlsSetValue (File: %s, Line: %d)...\n", __FILE__, __LINE__);
		fprintf(stderr, "Error code: %u\n", (c_utils_uint32_t)error);

		return C_UTILS_RESULT_FAILURE;
	}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	const signed int result = pthread_setspecific(key, value);

	if(result)
	{
		fprintf(stderr, "Error in function c_utils_tls_set, function pthread_setspecific (File: %s, Line: %d)...\n", __FILE__, __LINE__);
		fprintf(stderr, "Error code: %d\n", result);

		return C_UTILS_RESULT_FAILURE;
	}
#endif

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_tls_get(c_utils_tls_key_t key, c_utils_void_t *const output)
{
	if(!output)
	{
		fprintf(stderr, "Error in function c_utils_tls_get, the output is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

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
			fprintf(stderr, "Error in function c_utils_tls_get, function TlsGetValue (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %u\n", (c_utils_uint32_t)error);

			return C_UTILS_RESULT_FAILURE;
		}

		*type_output = value;
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)

		*type_output = pthread_getspecific(key);
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_tls_destroy(c_utils_tls_key_t key)
{
#if defined(_WIN32) || defined(_WIN64)
	if(!TlsFree(key))
	{
		const DWORD error = GetLastError();

		fprintf(stderr, "Error in function c_utils_tls_destroy, function TlsFree (File: %s, Line: %d)...\n", __FILE__, __LINE__);
		fprintf(stderr, "Error code: %u\n", (c_utils_uint32_t)error);

		return C_UTILS_RESULT_FAILURE;
	}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	const signed int result = pthread_key_delete(key);

	if(result)
	{
		fprintf(stderr, "Error in function c_utils_tls_destroy, function pthread_key_delete (File: %s, Line: %d)...\n", __FILE__, __LINE__);
		fprintf(stderr, "Error code: %d\n", result);

		return C_UTILS_RESULT_FAILURE;
	}
#endif

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_barrier_create(c_utils_barrier_t *const barrier, c_utils_uint32_t count)
{
	if(!barrier)
	{
		fprintf(stderr, "Error in function c_utils_barrier_create, the barrier is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(count == 0)
	{
		fprintf(stderr, "Error in function c_utils_barrier_create, the count is zero (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_mutex_create(&barrier->mutex))
	{
		fprintf(stderr, "Error in function c_utils_barrier_create, function c_utils_mutex_create (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_condition_variable_create(&barrier->condition_variable))
	{
		fprintf(stderr, "Error in function c_utils_barrier_create, function c_utils_condition_variable_create (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		if(c_utils_mutex_destroy(&barrier->mutex))
		{
			fprintf(stderr, "Error in function c_utils_barrier_create, function c_utils_mutex_destroy (File: %s, Line: %d)...\n", __FILE__, __LINE__);
		}

		return C_UTILS_RESULT_FAILURE;
	}

	barrier->total = count;
	barrier->count = count;
	barrier->cycle = 0;

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_barrier_wait(c_utils_barrier_t *const barrier)
{
	if(!barrier)
	{
		fprintf(stderr, "Error in function c_utils_barrier_wait, the barrier is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_mutex_lock(&barrier->mutex))
	{
		fprintf(stderr, "Error in function c_utils_barrier_wait, function c_utils_mutex_lock (File: %s, Line: %d)...\n", __FILE__, __LINE__);

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
				fprintf(stderr, "Error in function c_utils_barrier_wait, function c_utils_condition_variable_broadcast (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				if(c_utils_mutex_unlock(&barrier->mutex))
				{
					fprintf(stderr, "Error in function c_utils_barrier_wait, function c_utils_mutex_unlock (File: %s, Line: %d)...\n", __FILE__, __LINE__);
				}

				return C_UTILS_RESULT_FAILURE;
			}

			if(c_utils_mutex_unlock(&barrier->mutex))
			{
				fprintf(stderr, "Error in function c_utils_barrier_wait, function c_utils_mutex_unlock (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_RESULT_FAILURE;
			}

			return C_UTILS_RESULT_SUCCESS;
		}

		while(barrier->cycle == cycle)
		{
			if(c_utils_condition_variable_wait(&barrier->condition_variable, &barrier->mutex))
			{
				fprintf(stderr, "Error in function c_utils_barrier_wait, function c_utils_condition_variable_wait (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				if(c_utils_mutex_unlock(&barrier->mutex))
				{
					fprintf(stderr, "Error in function c_utils_barrier_wait, function c_utils_mutex_unlock (File: %s, Line: %d)...\n", __FILE__, __LINE__);
				}

				return C_UTILS_RESULT_FAILURE;
			}
		}

		if(c_utils_mutex_unlock(&barrier->mutex))
		{
			fprintf(stderr, "Error in function c_utils_barrier_wait, function c_utils_mutex_unlock (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result_t c_utils_barrier_destroy(c_utils_barrier_t *const barrier)
{
	if(!barrier)
	{
		fprintf(stderr, "Error in function c_utils_barrier_destroy, the barrier is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_condition_variable_destroy(&barrier->condition_variable))
	{
		fprintf(stderr, "Error in function c_utils_barrier_destroy, function c_utils_condition_variable_destroy (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		if(c_utils_mutex_destroy(&barrier->mutex))
		{
			fprintf(stderr, "Error in function c_utils_barrier_destroy, function c_utils_mutex_destroy (File: %s, Line: %d)...\n", __FILE__, __LINE__);
		}

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_mutex_destroy(&barrier->mutex))
	{
		fprintf(stderr, "Error in function c_utils_barrier_destroy, function c_utils_mutex_destroy (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif
