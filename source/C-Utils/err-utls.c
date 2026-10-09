/*************************/
/* Library importations: */
/*************************/

#ifndef C_UTILS_COMPILE
#include "../../include/C-Utils/err-utls.h"
#else
#include "C-Utils/err-utls.h"
#endif
#include <stdio.h>

/********************/
/* Import C to C++: */
/********************/

#ifdef __cplusplus
extern "C"
{
#endif

/****************************/
/* Global static variables: */
/****************************/

static c_utils_void_t c_utils_default_error_callback(const c_utils_char_t *const error_string, const c_utils_char_t *const file, const c_utils_int32_t line);
static c_utils_error_callback_t c_utils_error_callback_function = c_utils_default_error_callback;

/**************************/
/* Functions definitions: */
/**************************/

static c_utils_void_t c_utils_default_error_callback(const c_utils_char_t *const error_string, const c_utils_char_t *const file, const c_utils_int32_t line)
{
	fprintf(stderr, "%s (File: %s, Line: %d)...\n", error_string, file, (signed int)line);

	return;
}

C_UTILS_API c_utils_result_t c_utils_set_error_callback(const c_utils_error_callback_t callback_function)
{
	if(!callback_function)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_set_error_callback, the callback_function is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	c_utils_error_callback_function = callback_function;

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_get_error_callback(c_utils_error_callback_t *const output)
{
	if(!output)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_get_error_callback, the output is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	*output = c_utils_error_callback_function;

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_void_t c_utils_set_default_error_callback(c_utils_void_t)
{
	c_utils_error_callback_function = c_utils_default_error_callback;

	return;
}

C_UTILS_API c_utils_void_t c_utils_report_error(const c_utils_char_t *const error_string, const c_utils_char_t *const file, const c_utils_int32_t line)
{
	c_utils_error_callback_function(error_string ? error_string : "Unknown error", file ? file : "Unknown file", line);

	return;
}

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif
