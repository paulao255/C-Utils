/* Include guard: */
#ifndef C_UTILS_MATH_UTILS_H
#define C_UTILS_MATH_UTILS_H

/* Importations: */
#include "definitions.h"


/* Import C to C++: */
#ifdef __cplusplus
extern "C"
{
#endif

/* Pi constants: */
extern const c_utils_float32_t C_UTILS_MATH_PI_FLOAT32;                                                                                                   /* Pi const using float32_t value.                                         */
extern const c_utils_float64_t C_UTILS_MATH_PI_FLOAT64;                                                                                                   /* Pi const using float64_t value.                                         */

/* Math utils functions prototypes: */
c_utils_float32_t c_utils_circumfer_float32(const c_utils_float32_t radius_value);                                                                        /* Function to calculate a circumference using a float value.              */
c_utils_float32_t c_utils_circle_area_float32(const c_utils_float32_t radius_value);                                                                      /* Function to calculate the area of a circle using a float value.         */
c_utils_float32_t c_utils_sphere_volume_float32(const c_utils_float32_t radius_value);                                                                    /* Function to calculate the volume of a sphere using a float value.       */
c_utils_float32_t c_utils_summation_float32(c_utils_float32_t (*f)(c_utils_float32_t i), c_utils_int32_t lower_bound, const c_utils_int32_t upper_bound); /* Summation function using float values.                                  */
c_utils_float32_t c_utils_product_float32(c_utils_float32_t (*f)(c_utils_float32_t i), c_utils_int32_t lower_bound, const c_utils_int32_t upper_bound);   /* Product function using float values.                                    */
c_utils_float64_t c_utils_circumfer_float64(const c_utils_float64_t radius_value);                                                                        /* Function to calculate a circumference using a double value.             */
c_utils_float64_t c_utils_circle_area_float64(const c_utils_float64_t radius_value);                                                                      /* Function to calculate the area of a circle using a double value.        */
c_utils_float64_t c_utils_sphere_volume_float64(const c_utils_float64_t radius_value);                                                                    /* Function to calculate the volume of a sphere using a double value.      */
c_utils_float64_t c_utils_summation_float64(c_utils_float64_t (*f)(c_utils_float64_t i), c_utils_int32_t lower_bound, const c_utils_int32_t upper_bound); /* Summation function using double values.                                 */
c_utils_float64_t c_utils_product_float64(c_utils_float64_t (*f)(c_utils_float64_t i), c_utils_int32_t lower_bound, const c_utils_int32_t upper_bound);   /* Product function using double values.                                   */

/* End C to C++ importation: */
#ifdef __cplusplus
}
#endif

/* End C_UTILS_MATH_UTILS_H: */
#endif
