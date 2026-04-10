/* Include guard: */
#ifndef C_UTILS_C_UTILS_H
#define C_UTILS_C_UTILS_H

/* Importations: */
#include "defs.h"
#include <time.h>


/* Import C to C++: */
#ifdef __cplusplus
extern "C"
{
#endif

/* Main struct prototypes: */
struct tm c_utils_get_current_time(void);                                                                                  /* Get current time struct.                            */
struct tm *c_utils_current_time(void);                                                                                     /* Current time struct.                                */

/* Main functions prototypes: */
int c_utils_clear_stdout(void);                                                                                            /* Function to clear the terminal.                     */
int c_utils_clear_stdin(void);                                                                                             /* Function to clear the standard input.               */
int c_utils_scan_enter(void);                                                                                              /* Press enter to continue function.                   */
int c_utils_enable_virtual_terminal_and_utf8(void);                                                                        /* Function to solve encoding in the Windows terminal. */
int c_utils_scan_char(void);                                                                                               /* Press any key to continue function.                 */
int c_utils_rlf(void);                                                                                                     /* Read "LICENSE" function.                            */
int c_utils_rrmf(void);                                                                                                    /* Read "READ-ME" function.                            */
int c_utils_url_opener(const char *const url);                                                                             /* URL opener function.                                */
int c_utils_ssleep(const unsigned int time);                                                                               /* Seconds sleep function.                             */
int c_utils_mssleep(const unsigned int time);                                                                              /* Milliseconds sleep function.                        */
int c_utils_validate_date(const int year, const int month, const int day);                                                 /* Validate date function.                             */
int c_utils_validate_date_future(const int year, const int month, const int day);                                          /* Validate all time date function.                    */
int c_utils_make_directory(const char *const path, unsigned int mode);                                                     /* Function to create a directory.                     */
int c_utils_linear_char_search(const char *const array, const size_t count, const char target);                            /* Linear char search function.                        */
int c_utils_linear_short_int_search(const short int *const array, const size_t count, const short int target);             /* Linear short int search function.                   */
int c_utils_linear_int_search(const int *const array, const size_t count, const int target);                               /* Linear int search function.                         */
int c_utils_linear_long_int_search(const long int *const array, const size_t count, const long int target);                /* Linear long int search function.                    */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
int c_utils_linear_long_long_int_search(const long long int *const array, const size_t count, const long long int target); /* Linear long long int search function.               */
#endif
int c_utils_linear_float_search(const float *const array, const size_t count, const float target);                         /* Linear float search function.                       */
int c_utils_linear_double_search(const double *const array, const size_t count, const double target);                      /* Linear double search function.                      */
int c_utils_linear_long_double_search(const long double *const array, const size_t count, const long double target);       /* Linear long double search function.                 */
int c_utils_linear_array_search(const char *const *const array, const size_t count, const char *const target);             /* Linear array search function.                       */
const char *c_utils_verify_os(void);                                                                                       /* Function to verify the operating system.            */

/* End importation: */
#ifdef __cplusplus
}
#endif

/* End code: */
#endif
