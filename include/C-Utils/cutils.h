/* Include guard: */
#if !defined(C_UTILS_C_UTILS_H)
#define C_UTILS_C_UTILS_H

/* Importations: */
#include "defs.h"
#include <time.h>


/* Import C to C++: */
#if defined(__cplusplus)
extern "C"
{
#endif

/* Functions prototypes: */
signed int c_utils_clear_standard_output(void);                                                                                                        /* Clear the standard output.                          */
signed int c_utils_clear_standard_input(void);                                                                                                         /* Clear the standard input.                           */
signed int c_utils_initialize(void);                                                                                                                   /* Initialize many common functions of C-Utils.        */
signed int c_utils_scan_enter(void);                                                                                                                   /* Press enter to continue function.                   */
signed int c_utils_enable_virtual_terminal_and_utf8(void);                                                                                             /* Function to solve encoding in the Windows terminal. */
signed int c_utils_scan_character(void);                                                                                                               /* Scan character function.                            */
signed int c_utils_rlf(void);                                                                                                                          /* Read "LICENSE" function.                            */
signed int c_utils_rrmf(void);                                                                                                                         /* Read "READ-ME" function.                            */
signed int c_utils_url_opener(const unsigned char *const url);                                                                                         /* URL opener function.                                */
signed int c_utils_ssleep(const unsigned int time);                                                                                                    /* Seconds sleep function.                             */
signed int c_utils_mssleep(const unsigned int time);                                                                                                   /* Milliseconds sleep function.                        */
signed int c_utils_validate_date(const int year, const int month, const int day);                                                                      /* Validate date function.                             */
signed int c_utils_validate_date_future(const int year, const int month, const int day);                                                               /* Validate all time date function.                    */
signed int c_utils_make_directory(const unsigned char *const path, unsigned int mode);                                                                 /* Function to create a directory.                     */
signed int c_utils_linear_unsigned_char_search(const unsigned char *const array, const size_t count, const unsigned char target);                      /* Linear unsigned char search function.               */
signed int c_utils_linear_signed_short_int_search(const signed short int *const array, const size_t count, const signed short int target);             /* Linear short int search function.                   */
signed int c_utils_linear_signed_int_search(const signed int *const array, const size_t count, const signed int target);                               /* Linear int search function.                         */
signed int c_utils_linear_signed_long_int_search(const signed long int *const array, const size_t count, const signed long int target);                /* Linear long int search function.                    */
#if defined(__STDC__) && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
signed int c_utils_linear_signed_long_long_int_search(const signed long long int *const array, const size_t count, const signed long long int target); /* Linear long long int search function.               */
#endif
signed int c_utils_linear_float_search(const float *const array, const size_t count, const float target);                                              /* Linear float search function.                       */
signed int c_utils_linear_double_search(const double *const array, const size_t count, const double target);                                           /* Linear double search function.                      */
signed int c_utils_linear_long_double_search(const long double *const array, const size_t count, const long double target);                            /* Linear long double search function.                 */
signed int c_utils_linear_unsigned_array_search(const unsigned char *const *const array, const size_t count, const unsigned char *const target);       /* Linear array search function.                       */
const unsigned char *c_utils_verify_os(void);                                                                                                          /* Function to verify the operating system.            */
struct tm c_utils_current_time(void);                                                                                                                  /* Get current time struct.                            */

/* End importation: */
#if defined(__cplusplus)
}
#endif

/* End C_UTILS_C_UTILS_H: */
#endif
