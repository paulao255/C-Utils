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

/******************/
/* C-Utils types: */
/******************/

/* C-Utils memory handle type. */
struct c_utils_memory_handle_t
{
	c_utils_void_t *pointer;
	c_utils_uint32_t location;
};

/* C-Utils typedef memory handle type: */
typedef struct c_utils_memory_handle_t c_utils_memory_handle_t;

/*************************/
/* Functions prototypes: */
/*************************/

/* Initialize C-Utils. */
C_UTILS_API c_utils_result_t c_utils_initialize(c_utils_void_t);

/* Terminate C-Utils. */
C_UTILS_API c_utils_result_t c_utils_terminate(c_utils_void_t);

/* This function clears the standard output (like "clear" or "cls" but in a faster and simplified form). */
C_UTILS_API c_utils_void_t c_utils_clear_standard_output(c_utils_void_t);

/* A function to clear the standard input. */
C_UTILS_API c_utils_void_t c_utils_clear_standard_input(c_utils_void_t);

/* This function gets current time (Operacional System time) and puts it into the first argument a time struct pointer. */
C_UTILS_API c_utils_result_t c_utils_get_current_time(struct tm *const time);

/* Function to validate a future/present/past time date. */
C_UTILS_API c_utils_result_t c_utils_validate_date(const c_utils_int32_t year, const c_utils_uint8_t month, const c_utils_uint8_t day, const c_utils_bool_t is_future_date_valid);

/* Function to allocate/reallocate memory and register it to C-Utils addresses to free list. */
C_UTILS_API c_utils_result_t c_utils_mem_allocate(c_utils_memory_handle_t *const handle, const c_utils_size_t size);

/* C-Utils memory register handle to free function. */
C_UTILS_API c_utils_result_t c_utils_mem_regist_to_free(c_utils_memory_handle_t *const handle);

/* This function free memory and unregister it from C-Utils addresses to free list. */
C_UTILS_API c_utils_result_t c_utils_mem_free_and_unregist(c_utils_memory_handle_t *const handle);

/* Function to scan any caracter except enter, that when pressed it jumps back to the caller. */
C_UTILS_API c_utils_result_t c_utils_scan_enter(c_utils_void_t);

/* Function to open an URL in the default browser. */
C_UTILS_API c_utils_result_t c_utils_url_open(const c_utils_char_t *const url);

/* Function to sleep for seconds/milliseconds. */
C_UTILS_API c_utils_result_t c_utils_sleep(const c_utils_uint32_t seconds, const c_utils_uint16_t milliseconds);

/* Function to create a directory in supported Operacional Systems. */
C_UTILS_API c_utils_result_t c_utils_make_directory(const c_utils_char_t *const path, c_utils_uint32_t mode);

/* Function to scan a character from the standard input. */
C_UTILS_API c_utils_result_t c_utils_scan_character(signed int *const character_output);

/* Function to read a file from the Operational System and return it to the caller. */
C_UTILS_API c_utils_result_t c_utils_read_file(const c_utils_char_t *const path, c_utils_memory_handle_t *const output);

/* This function verifies the Operacional System and returns to the caller its name in a string. */
C_UTILS_API c_utils_result_t c_utils_verify_os(const c_utils_char_t *const output);

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
