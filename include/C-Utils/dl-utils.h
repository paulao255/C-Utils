/******************/
/* Include guard: */
/******************/

#ifndef C_UTILS_DL_UTILS_H
#define C_UTILS_DL_UTILS_H

/*************************/
/* Library importations: */
/*************************/

#include "defs.h"
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#if defined(_WIN32) || defined(_WIN64)
typedef HMODULE C_UTILS_DYNAMIC_LIBRARY_T;
typedef FARPROC C_UTILS_DYNAMIC_LIBRARY_FUNCTION_T;
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
typedef void *C_UTILS_DYNAMIC_LIBRARY_T;
typedef void *C_UTILS_DYNAMIC_LIBRARY_FUNCTION_T;
#endif

/*********************/
/* Type definitions: */
/*********************/

/* C-Utils dynamic library type: */
typedef C_UTILS_DYNAMIC_LIBRARY_T c_utils_dynamic_library_t;

/* C-Utils dynamic library function type: */
typedef C_UTILS_DYNAMIC_LIBRARY_FUNCTION_T c_utils_dynamic_library_function_t;

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

/* Function to open a dynamic library and return it to the output parameter. */
C_UTILS_API c_utils_result_t c_utils_dynamic_library_open(const c_utils_char_t *const path, c_utils_dynamic_library_t *const output);

/* Function to load a function from a dynamic library and return it to the output parameter. */
C_UTILS_API c_utils_result_t c_utils_dynamic_library_load_function(const c_utils_dynamic_library_t library, const c_utils_char_t *const name, c_utils_dynamic_library_function_t *const output);

/* Function to close a dynamic library. */
C_UTILS_API c_utils_result_t c_utils_dynamic_library_close(const c_utils_dynamic_library_t library);

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif

/***************************/
/* End C_UTILS_DL_UTILS_H: */
/***************************/

#endif
