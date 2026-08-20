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
extern c_utils_result c_utils_generic_summation(const c_utils_void_t *const lower_bound, const c_utils_void_t *const upper_bound, const c_utils_void_t *(*const f)(const c_utils_void_t *const i, const size_t f_element_size), const size_t element_size, const c_utils_void_t *const result);

/* Function to calculate the product of a sequence. */
extern c_utils_result c_utils_generic_product(const c_utils_void_t *const lower_bound, const c_utils_void_t *const upper_bound, const c_utils_void_t *(*const f)(const c_utils_void_t *const i, const size_t f_element_size), const size_t element_size, const c_utils_void_t *const result);

/* Function to calculate the termial of a number. */
extern c_utils_result c_utils_generic_termial(const c_utils_void_t *const value, const size_t element_size, const c_utils_void_t *const result);

/* Function to calculate the factorial of a number. */
extern c_utils_result c_utils_generic_factorial(const c_utils_void_t *const value, const size_t element_size, const c_utils_void_t *const result);

/* Function to calculate the logarithm of a number in a given base. */
extern c_utils_result c_utils_generic_log_base(const c_utils_void_t *const base, const c_utils_void_t *const value, const size_t element_size, c_utils_void_t *const result);

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
