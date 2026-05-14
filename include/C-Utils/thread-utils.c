/* Importations: */
#include "thread-utils.h"
#if defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
#include <unistd.h>
#endif


/* Import C to C++: */
#ifdef __cplusplus
extern "C"
{
#endif


signed short int c_utils_thread_create(c_utils_thread_t *thread, C_UTILS_THREAD_FUNCTION (*function)(void *arguments), void *arguments)
{
#if defined(_WIN32) || defined(_WIN64)
	return ((*thread = CreateThread((void *)0, 0, (LPTHREAD_START_ROUTINE)function, arguments, 0, (void *)0)) == (void *)0) ? C_UTILS_FAILURE : C_UTILS_SUCCESS;
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	return (pthread_create(thread, (void *)0, function, arguments) != 0) ? C_UTILS_FAILURE : C_UTILS_SUCCESS;
#endif
}

signed short int c_utils_thread_join(c_utils_thread_t thread)
{
#if defined(_WIN32) || defined(_WIN64)
	if(WaitForSingleObject(thread, INFINITE) != WAIT_OBJECT_0)
	{
		if(!CloseHandle(thread))
		{
			return C_UTILS_FAILURE;
		}

		return C_UTILS_FAILURE;
	}

	if(!CloseHandle(thread))
	{
		return C_UTILS_FAILURE;
	}

	return C_UTILS_SUCCESS;
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	return (pthread_join(thread, (void *)0) != 0) ? C_UTILS_FAILURE : C_UTILS_SUCCESS;
#endif
}

signed short int c_utils_thread_detach(c_utils_thread_t thread)
{
#if defined(_WIN32) || defined(_WIN64)
	return (CloseHandle(thread) == 0) ? C_UTILS_FAILURE : C_UTILS_SUCCESS;
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	return (pthread_detach(thread) != 0) ? C_UTILS_FAILURE : C_UTILS_SUCCESS;
#endif
}

signed long int c_utils_get_maximum_threads(void)
{
#if defined(_WIN32) || defined(_WIN64)
	return (signed long int)GetActiveProcessorCount(ALL_PROCESSOR_GROUPS);
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	return sysconf(_SC_NPROCESSORS_ONLN);
#endif
}

/* End C to C++ importation: */
#ifdef __cplusplus
}
#endif
