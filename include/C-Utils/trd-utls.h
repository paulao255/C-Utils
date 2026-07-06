/******************/
/* Include guard: */
/******************/

#ifndef C_UTILS_TRD_UTLS_H
#define C_UTILS_TRD_UTLS_H

/*************************/
/* Library importations: */
/*************************/

#include "defs.h"
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
#include <pthread.h>
#else
#error "FATAL ERROR: !defined(_WIN32) && !defined(_WIN64) && !defined(__linux__) && !defined(__ANDROID__) && !defined(__APPLE__)."
#endif

/*****************/
/* Thread types: */
/*****************/

#if defined(_WIN32) || defined(_WIN64)
#define C_UTILS_THREAD_FUNCTION_T DWORD WINAPI
#define C_UTILS_THREAD_FUNCTION_RETURN 0UL
typedef HANDLE C_UTILS_THREAD_T;
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
#define C_UTILS_THREAD_FUNCTION_T void *
#define C_UTILS_THREAD_FUNCTION_RETURN (void *)0
typedef pthread_t C_UTILS_THREAD_T;
#endif

/* C-Utils thread function type: */
#define c_utils_thread_function_t C_UTILS_THREAD_FUNCTION_T

/* C-Utils thread function return value: */
#define c_utils_thread_function_return C_UTILS_THREAD_FUNCTION_RETURN

/* C-Utils thread type: */
typedef C_UTILS_THREAD_T c_utils_thread_t;

/********************/
/* Import C to C++: */
/********************/

#ifdef __cplusplus
extern "C"
{
#endif

/*************************/
/* Functions prototypes: */
/*************************/

/* Function to create a thread. */
c_utils_int16_t c_utils_thread_create(c_utils_thread_t *const thread, c_utils_thread_function_t (*f)(void *arguments), void *arguments);

/* Function to join a thread. */
c_utils_int16_t c_utils_thread_join(c_utils_thread_t thread);

/* Function to detach a thread. */
c_utils_int16_t c_utils_thread_detach(c_utils_thread_t thread);

/* Function to get the maximum number of threads and return it to the caller. */
c_utils_int32_t c_utils_get_maximum_threads(void);

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif

/**************************/
/* End C_UTILS_TRD_UTLS_H */
/**************************/

#endif
