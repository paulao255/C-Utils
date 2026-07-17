/******************/
/* Include guard: */
/******************/

#ifndef C_UTILS_MTH_UTLS_H
#define C_UTILS_MTH_UTLS_H

/*************************/
/* Library importations: */
/*************************/

#include "defs.h"
#include <stddef.h>

/********************/
/* Import C to C++: */
/********************/

#ifdef __cplusplus
extern "C"
{
#endif

/**************/
/* Constants: */
/**************/

/* C-Utils PI constant using a 32 bits float type. */
extern const c_utils_float32_t C_UTILS_MATH_PI_FLOAT32;

/* C-Utils Euler constant using a 32 bits float type. */
extern const c_utils_float32_t C_UTILS_MATH_E_FLOAT32;

/* C-Utils PI constant using a 64 bits float type. */
extern const c_utils_float64_t C_UTILS_MATH_PI_FLOAT64;

/* C-Utils Euler constant using a 64 bits float type. */
extern const c_utils_float64_t C_UTILS_MATH_E_FLOAT64;


/*************************/
/* Functions prototypes: */
/*************************/

/* Function to calculate the summation of a sequence. */
c_utils_int16_t c_utils_generic_summation(const void *const lower_bound, const void *const upper_bound, const void *(*const f)(const void *const i, const size_t f_element_size), const size_t element_size, const void *const result);

/* Function to calculate the product of a sequence. */
c_utils_int16_t c_utils_generic_product(const void *const lower_bound, const void *const upper_bound, const void *(*const f)(const void *const i, const size_t f_element_size), const size_t element_size, const void *const result);

/* Function to calculate the factorial of a number. */
c_utils_int16_t c_utils_factorial(const void *const value, const size_t element_size, const void *const result);

/* Function to calculate the logarithm of a number in a given base. */
c_utils_int16_t c_utils_generic_log_base(const void *const base, const void *const value, const size_t element_size, void *const result);

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif

/***************************/
/* End C_UTILS_MTH_UTLS_H: */
/***************************/

#endif
