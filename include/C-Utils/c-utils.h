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
void c_utils_clear_standard_output(void);                                                                                                                                     /* Clear the standard output.                          */
c_utils_int16_t c_utils_get_current_time(struct tm *const time);                                                                                                              /* Get current time struct function.                   */
c_utils_int16_t c_utils_validate_date(const c_utils_int32_t year, const c_utils_int32_t month, const c_utils_int32_t day);                                                    /* Validate date function.                             */
c_utils_int16_t c_utils_validate_date_future(const c_utils_int32_t year, const c_utils_int32_t month, const c_utils_int32_t day);                                             /* Validate all time date function.                    */
c_utils_int16_t c_utils_clear_standard_input(void);                                                                                                                           /* Clear the standard input.                           */
c_utils_int16_t c_utils_initialize(void);                                                                                                                                     /* Initialize C-Utils.                                 */
c_utils_int16_t c_utils_terminate(void);                                                                                                                                      /* Terminate C-Utils.                                  */
c_utils_int16_t c_utils_regist_address_to_free(void *const address);                                                                                                          /* Register address to free function.                  */
c_utils_int16_t c_utils_scan_enter(void);                                                                                                                                     /* Press enter to continue function.                   */
c_utils_int16_t c_utils_url_opener(const c_utils_char_t *const url);                                                                                                          /* URL opener function.                                */
c_utils_int16_t c_utils_ssleep(const c_utils_uint32_t time);                                                                                                                  /* Seconds sleep function.                             */
c_utils_int16_t c_utils_mssleep(const c_utils_uint32_t time);                                                                                                                 /* Milliseconds sleep function.                        */
c_utils_int16_t c_utils_make_directory(const c_utils_char_t *const path, c_utils_uint32_t mode);                                                                              /* Function to create a directory.                     */
signed int c_utils_scan_character(void);                                                                                                                                      /* Scan character function.                            */
void *c_utils_memory_allocate(const size_t size);                                                                                                                             /* Function to allocate memory.                        */
void *c_utils_memory_reallocate(void *const old_pointer, const size_t size);                                                                                                  /* Function to reallocate memory.                      */
const c_utils_char_t *c_utils_read_file(const c_utils_char_t *const path);                                                                                                    /* Function to read a file.                            */
const c_utils_char_t *c_utils_verify_os(void);                                                                                                                                /* Function to verify the operating system.            */

/* End C to C++ importation: */
#ifdef __cplusplus
}
#endif

/* End C_UTILS_C_UTILS_H: */
#endif
