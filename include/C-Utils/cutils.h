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
struct tm get_current_time(void);                                                                            /* Get current time struct.                            */
struct tm *current_time(void);                                                                               /* Current time struct.                                */

/* Main functions prototypes: */
int clear_stdout(void);                                                                                      /* Function to clear the terminal.                     */
int clear_stdin(void);                                                                                       /* Function to clear the standard input.               */
int scan_enter(void);                                                                                        /* Press enter to continue function.                   */
int easter_egg_function(void);                                                                               /* Easter egg function.                                */
int enable_virtual_terminal_and_utf8(void);                                                                  /* Function to solve encoding in the Windows terminal. */
int scan_char(void);                                                                                         /* Press any key to continue function.                 */
int rlf(void);                                                                                               /* Read "LICENSE" function.                            */
int rrmf(void);                                                                                              /* Read "READ-ME" function.                            */
int url_opener(const char *const url);                                                                       /* URL opener function.                                */
int ssleep(const unsigned int time);                                                                         /* Seconds sleep function.                             */
int mssleep(const unsigned int time);                                                                        /* Milliseconds sleep function.                        */
int validate_date(const int year, const int month, const int day);                                           /* Validate date function.                             */
int validate_date_future(const int year, const int month, const int day);                                    /* Validate all time date function.                    */
int make_directory(const char *const path, unsigned int mode);                                               /* Function to create a directory.                     */
int linear_char_search(const char *const array, size_t bytes, const char target);                            /* Linear char search function.                        */
int linear_short_int_search(const short int *const array, size_t bytes, const short int target);             /* Linear short int search function.                   */
int linear_int_search(const int *const array, size_t bytes, const int target);                               /* Linear int search function.                         */
int linear_long_int_search(const long int *const array, size_t bytes, const long int target);                /* Linear long int search function.                    */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
int linear_long_long_int_search(const long long int *const array, size_t bytes, const long long int target); /* Linear long long int search function.               */
#endif
int linear_float_search(const float *const array, size_t bytes, const float target);                         /* Linear float search function.                       */
int linear_double_search(const double *const array, size_t bytes, const double target);                      /* Linear double search function.                      */
int linear_long_double_search(const long double *const array, size_t bytes, const long double target);       /* Linear long double search function.                 */
int linear_array_search(const char *const *const array, size_t bytes, const char *const target);                   /* Linear array search function.                       */
const char *verify_os(void);                                                                                 /* Function to verify the operating system.            */

/* End importation: */
#ifdef __cplusplus
}
#endif

/* End code: */
#endif
