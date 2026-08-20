/******************/
/* Include guard: */
/******************/

#ifndef C_UTILS_C_UTILS_H
#define C_UTILS_C_UTILS_H

/*************************/
/* Library importations: */
/*************************/

#include "defs.h"
#include <time.h>

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

/* Initialize C-Utils. */
extern c_utils_result c_utils_initialize(c_utils_void_t);

/* Terminate C-Utils. */
extern c_utils_result c_utils_terminate(c_utils_void_t);

/* This function clears the standard output (like "clear" or "cls" but in a faster and simplified form). */
extern c_utils_void_t c_utils_clear_standard_output(c_utils_void_t);

/* This function gets current time (Operacional System time) and puts it into the first argument a time struct pointer. */
extern c_utils_result c_utils_get_current_time(struct tm *const time);

/* Function to validate a future/present/past time date. */
extern c_utils_result c_utils_validate_date(const c_utils_int32_t year, const c_utils_uint8_t month, const c_utils_uint8_t day, const c_utils_bool_t is_future_date_valid);

/* A function to clear the standard input. */
extern c_utils_result c_utils_clear_standard_input(c_utils_void_t);

/* Function to allocate/reallocate memory and register it to C-Utils addresses to free list. */
extern c_utils_result c_utils_mem_allocate(const c_utils_void_t **const address_pointer, const size_t size);

/* C-Utils memory register address to free function. */
extern c_utils_result c_utils_mem_regist_to_free(const c_utils_void_t *const address);

/* This function free memory and unregister it from C-Utils addresses to free list. */
extern c_utils_result c_utils_mem_free_and_unregist(const c_utils_void_t *const address);

/* Function to scan any caracter except enter, that when pressed it jumps back to the caller. */
extern c_utils_result c_utils_scan_enter(c_utils_void_t);

/* Function to open an URL in the default browser. */
extern c_utils_result c_utils_url_opener(const c_utils_char_t *const url);

/* Function to sleep for seconds/milliseconds. */
extern c_utils_result c_utils_sleep(const c_utils_uint32_t seconds, const c_utils_uint16_t milliseconds);

/* Function to create a directory in supported Operacional Systems. */
extern c_utils_result c_utils_make_directory(const c_utils_char_t *const path, c_utils_uint32_t mode);

/* Function to scan a character from the standard input. */
extern c_utils_result c_utils_scan_character(signed int *const character_output);

/* Function to get a random 32 bits signed integer based on the minimum and maximum values. */
extern c_utils_result c_utils_random_integer(c_utils_int32_t minimum, c_utils_int32_t maximum, c_utils_int32_t *const output);

/* Function to read a file from the Operational System and return it to the caller. */
extern c_utils_result c_utils_read_file(const c_utils_char_t *const path, const c_utils_char_t **const output);

/* This function verifies the Operacional System and returns to the caller its name in a string. */
extern c_utils_result c_utils_verify_os(const c_utils_char_t **const output);

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif

/**************************/
/* End C_UTILS_C_UTILS_H: */
/**************************/

#endif
