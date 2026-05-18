/* Include guard: */
#ifndef C_UTILS_C_UTILS_H
#define C_UTILS_C_UTILS_H

/* Importations: */
#include "definitions.h"
#include <time.h>


/* Import C to C++: */
#ifdef __cplusplus
extern "C"
{
#endif

/* Functions prototypes: */
void c_utils_clear_standard_output(void);                                                                                                                                                             /* Clear the standard output.                          */
c_utils_int16_t c_utils_validate_date(const c_utils_int32_t year, const c_utils_int32_t month, const c_utils_int32_t day);                                                                            /* Validate date function.                             */
c_utils_int16_t c_utils_validate_date_future(const c_utils_int32_t year, const c_utils_int32_t month, const c_utils_int32_t day);                                                                     /* Validate all time date function.                    */
c_utils_int16_t c_utils_clear_standard_input(void);                                                                                                                                                   /* Clear the standard input.                           */
c_utils_int16_t c_utils_enable_virtual_terminal_and_utf8(void);                                                                                                                                       /* Function to solve encoding in the Windows terminal. */
c_utils_int16_t c_utils_initialize(void);                                                                                                                                                             /* Initialize many common functions of C-Utils.        */
c_utils_int16_t c_utils_scan_enter(void);                                                                                                                                                             /* Press enter to continue function.                   */
c_utils_int16_t c_utils_url_opener(const c_utils_char_t *const url);                                                                                                                                  /* URL opener function.                                */
c_utils_int16_t c_utils_ssleep(const c_utils_uint32_t time);                                                                                                                                          /* Seconds sleep function.                             */
c_utils_int16_t c_utils_mssleep(const c_utils_uint32_t time);                                                                                                                                         /* Milliseconds sleep function.                        */
c_utils_int16_t c_utils_make_directory(const c_utils_char_t *const path, c_utils_uint32_t mode);                                                                                                      /* Function to create a directory.                     */
signed int c_utils_scan_character(void);                                                                                                                                                              /* Scan character function.                            */
size_t c_utils_linear_char_t_search(const c_utils_char_t *const array, const size_t count, const c_utils_char_t target);                                                                              /* Linear char_t search function.                      */
size_t c_utils_linear_int16_t_search(const c_utils_int16_t *const array, const size_t count, const c_utils_int16_t target);                                                                           /* Linear int16_t search function.                     */
size_t c_utils_linear_int32_t_search(const c_utils_int32_t *const array, const size_t count, const c_utils_int32_t target);                                                                           /* Linear int32_t search function.                     */
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L) || defined(C_UTILS_ENABLE_LONG_LONG_INT) || defined(C_UTILS_ENABLE_ALL_EXTENSIONS)
size_t c_utils_linear_int64_t_search(const c_utils_int64_t *const array, const size_t count, const c_utils_int64_t target);                                                                           /* Linear int64_t search function.                     */
#endif
size_t c_utils_linear_float32_t_search(const c_utils_float32_t *const array, const size_t count, const c_utils_float32_t target);                                                                     /* Linear float32_t search function.                   */
size_t c_utils_linear_float64_t_search(const c_utils_float64_t *const array, const size_t count, const c_utils_float64_t target);                                                                     /* Linear float64_t search function.                   */
size_t c_utils_linear_char_t_array_search(const c_utils_char_t *const *const array, const size_t count, const c_utils_char_t *const target);                                                          /* Linear char_t array search function.                */
c_utils_char_t *c_utils_read_file(const c_utils_char_t *const path);                                                                                                                                  /* Function to read a file.                            */
const c_utils_char_t *c_utils_verify_os(void);                                                                                                                                                        /* Function to verify the operating system.            */
struct tm c_utils_current_time(void);                                                                                                                                                                 /* Get current time struct function.                   */

/* End C to C++ importation: */
#ifdef __cplusplus
}
#endif

/* End C_UTILS_C_UTILS_H: */
#endif
