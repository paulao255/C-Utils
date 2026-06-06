/* Include guard: */
#ifndef C_UTILS_BIG_O_UTILS_H
#define C_UTILS_BIG_O_UTILS_H

/* Importations: */
#include "definitions.h"
#include <stddef.h>

/* Import C to C++: */
#ifdef __cplusplus
extern "C"
{
#endif

/* Functions prototypes: */
c_utils_int16_t c_utils_linear_char_t_search(const c_utils_char_t *const array, const size_t count, const c_utils_char_t target, size_t *const position);                     /* Linear char_t search function.                      */
c_utils_int16_t c_utils_linear_int16_t_search(const c_utils_int16_t *const array, const size_t count, const c_utils_int16_t target, size_t *const position);                  /* Linear int16_t search function.                     */
c_utils_int16_t c_utils_linear_int32_t_search(const c_utils_int32_t *const array, const size_t count, const c_utils_int32_t target, size_t *const position);                  /* Linear int32_t search function.                     */
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L) || \
     defined(C_UTILS_ENABLE_LONG_LONG_INT) || defined(C_UTILS_ENABLE_ALL_EXTENSIONS)
c_utils_int16_t c_utils_linear_int64_t_search(const c_utils_int64_t *const array, const size_t count, const c_utils_int64_t target, size_t *const position);                  /* Linear int64_t search function.                     */
#endif
c_utils_int16_t c_utils_linear_float32_t_search(const c_utils_float32_t *const array, const size_t count, const c_utils_float32_t target, size_t *const position);            /* Linear float32_t search function.                   */
c_utils_int16_t c_utils_linear_float64_t_search(const c_utils_float64_t *const array, const size_t count, const c_utils_float64_t target, size_t *const position);            /* Linear float64_t search function.                   */
c_utils_int16_t c_utils_linear_char_t_array_search(const c_utils_char_t *const *const array, const size_t count, const c_utils_char_t *const target, size_t *const position); /* Linear char_t array search function.                */

/* End C to C++ importation: */
#ifdef __cplusplus
}
#endif

/* End C_UTILS_BIG_O_UTILS_H: */
#endif
