/* Include guard: */
#ifndef C_UTILS_THREAD_UTILS_H
#define C_UTILS_THREAD_UTILS_H

/* Importations: */
#include "definitions.h"
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
#include <pthread.h>
#else
#error "FATAL ERROR: !defined(_WIN32) && !defined(_WIN64) && !defined(__linux__) && !defined(__ANDROID__) && !defined(__APPLE__)."
#endif


/* Thread types: */
#if defined(_WIN32) || defined(_WIN64)
#define C_UTILS_THREAD_FUNCTION DWORD WINAPI
#define C_UTILS_THREAD_FUNCTION_RETURN 0UL
typedef HANDLE c_utils_thread_t;
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
#define C_UTILS_THREAD_FUNCTION void *
#define C_UTILS_THREAD_FUNCTION_RETURN (void *)0
typedef pthread_t c_utils_thread_t;
#endif
#define c_utils_thread_function C_UTILS_THREAD_FUNCTION
#define c_utils_thread_function_return C_UTILS_THREAD_FUNCTION_RETURN

/* Import C to C++: */
#ifdef __cplusplus
extern "C"
{
#endif

c_utils_int16_t c_utils_thread_create(c_utils_thread_t *thread, C_UTILS_THREAD_FUNCTION (*f)(void *arguments), void *arguments); /* Thread create function.       */
c_utils_int16_t c_utils_thread_join(c_utils_thread_t thread);                                                                    /* Thread join function.         */
c_utils_int16_t c_utils_thread_detach(c_utils_thread_t thread);                                                                  /* Thread detach function.       */
c_utils_int32_t c_utils_get_maximum_threads(void);                                                                               /* Get maximum threads function. */

/* End C to C++ importation: */
#ifdef __cplusplus
}
#endif

/* End C_UTILS_THREAD_UTILS_H */
#endif
