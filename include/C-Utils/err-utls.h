/******************/
/* Include guard: */
/******************/

#ifndef C_UTILS_ERR_UTLS_H
#define C_UTILS_ERR_UTLS_H

/*************************/
/* Library importations: */
/*************************/

#include "defs.h"

/********************/
/* Import C to C++: */
/********************/

#ifdef __cplusplus
extern "C"
{
#endif

/*********************/
/* Type definitions: */
/*********************/

typedef c_utils_void_t (*c_utils_error_callback_t)(const c_utils_char_t *const error_string, const c_utils_char_t *const file, const c_utils_int32_t line);

/*************************/
/* Functions prototypes: */
/*************************/

C_UTILS_API c_utils_result_t c_utils_set_error_callback(const c_utils_error_callback_t callback_function);

C_UTILS_API c_utils_result_t c_utils_get_error_callback(c_utils_error_callback_t *const output);

C_UTILS_API c_utils_void_t c_utils_set_default_error_callback(c_utils_void_t);

C_UTILS_API c_utils_void_t c_utils_report_error(const c_utils_char_t *const error_string, const c_utils_char_t *const file, const c_utils_int32_t line);

/***********/
/* Macros: */
/***********/

#ifndef C_UTILS_REPORT_ERROR
#define C_UTILS_REPORT_ERROR(error_string) c_utils_report_error((error_string), __FILE__, (c_utils_int32_t)__LINE__)
#else
#error "C_UTILS_REPORT_ERROR macro already defined"
#endif

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif

/***************************/
/* End C_UTILS_ERR_UTLS_H: */
/***************************/

#endif
