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
void c_utils_clear_standard_output(void);                                                                                                          /* Clear the standard output.                          */
signed short int c_utils_validate_date(const signed long int year, const signed long int month, const signed long int day);                        /* Validate date function.                             */
signed short int c_utils_validate_date_future(const signed long int year, const signed long int month, const signed long int day);                 /* Validate all time date function.                    */
signed short int c_utils_clear_standard_input(void);                                                                                               /* Clear the standard input.                           */
signed short int c_utils_enable_virtual_terminal_and_utf8(void);                                                                                   /* Function to solve encoding in the Windows terminal. */
signed short int c_utils_initialize(void);                                                                                                         /* Initialize many common functions of C-Utils.        */
signed short int c_utils_scan_enter(void);                                                                                                         /* Press enter to continue function.                   */
signed short int c_utils_url_opener(const char *const url);                                                                                        /* URL opener function.                                */
signed short int c_utils_ssleep(const unsigned int time);                                                                                          /* Seconds sleep function.                             */
signed short int c_utils_mssleep(const unsigned int time);                                                                                         /* Milliseconds sleep function.                        */
signed short int c_utils_make_directory(const char *const path, unsigned int mode);                                                                /* Function to create a directory.                     */
signed int c_utils_scan_character(void);                                                                                                           /* Scan character function.                            */
size_t c_utils_linear_char_search(const char *const array, const size_t count, const char target);                                                 /* Linear unsigned char search function.               */
size_t c_utils_linear_signed_short_int_search(const signed short int *const array, const size_t count, const signed short int target);             /* Linear short int search function.                   */
size_t c_utils_linear_signed_int_search(const signed int *const array, const size_t count, const signed int target);                               /* Linear int search function.                         */
size_t c_utils_linear_signed_long_int_search(const signed long int *const array, const size_t count, const signed long int target);                /* Linear long int search function.                    */
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L)
size_t c_utils_linear_signed_long_long_int_search(const signed long long int *const array, const size_t count, const signed long long int target); /* Linear long long int search function.               */
#endif
size_t c_utils_linear_float_search(const float *const array, const size_t count, const float target);                                              /* Linear float search function.                       */
size_t c_utils_linear_double_search(const double *const array, const size_t count, const double target);                                           /* Linear double search function.                      */
size_t c_utils_linear_long_double_search(const long double *const array, const size_t count, const long double target);                            /* Linear long double search function.                 */
size_t c_utils_linear_array_search(const char *const *const array, const size_t count, const char *const target);                                  /* Linear array search function.                       */
const char *c_utils_verify_os(void);                                                                                                               /* Function to verify the operating system.            */
struct tm c_utils_current_time(void);                                                                                                              /* Get current time struct.                            */

/* End C to C++ importation: */
#ifdef __cplusplus
}
#endif

/* End C_UTILS_C_UTILS_H: */
#endif
