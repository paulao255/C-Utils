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

/* This function clears the standard output (like "clear" or "cls" but in a faster and simplified form). */
void c_utils_clear_standard_output(void);

/* This function free memory and unregister it from C-Utils addresses to free list. */
c_utils_int16_t c_utils_mem_free_and_unregist(void *const address);

/* This function gets current time (Operacional System time) and puts it into the first argument a time struct pointer. */
c_utils_int16_t c_utils_get_current_time(struct tm *const time);

/* Function to validate a future/present/past time date. */
c_utils_int16_t c_utils_validate_date(const c_utils_int32_t year, const c_utils_uint8_t month, const c_utils_uint8_t day, const c_utils_uint8_t is_future_date_valid);

/* A function to clear the standard input. */
c_utils_int16_t c_utils_clear_standard_input(void);

/* Initialize C-Utils. */
c_utils_int16_t c_utils_initialize(void);

/* Terminate C-Utils. */
c_utils_int16_t c_utils_terminate(void);

/* C-Utils memory register address to free function. */
c_utils_int16_t c_utils_mem_regist_to_free(void *const address);

/* Function to scan any caracter except enter, that when pressed it jumps back to the caller. */
c_utils_int16_t c_utils_scan_enter(void);

/* Function to open an URL in the default browser. */
c_utils_int16_t c_utils_url_opener(const c_utils_char_t *const url);

/* Function to sleep for seconds/milliseconds. */
c_utils_int16_t c_utils_sleep(const c_utils_uint32_t seconds, const c_utils_uint16_t milliseconds);

/* Function to create a directory in supported Operacional Systems. */
c_utils_int16_t c_utils_make_directory(const c_utils_char_t *const path, c_utils_uint32_t mode);

/* Function to scan a character from the standard input. */
signed int c_utils_scan_character(void);

/* Function to allocate/reallocate memory. */
void *c_utils_mem_allocate(void *const old_pointer, const size_t size);

/* Function to read a file from the Operational System and return it to the caller. */
const c_utils_char_t *c_utils_read_file(const c_utils_char_t *const path);

/* This function verifies the Operacional System and returns to the caller its name in a string. */
const c_utils_char_t *c_utils_verify_os(void);

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
