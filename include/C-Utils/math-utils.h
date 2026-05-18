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
extern const c_utils_float32_t C_UTILS_MATH_PI_FLOAT32;                                                                                    /* Pi const using float32_t value.                                             */
extern const c_utils_float64_t C_UTILS_MATH_PI_FLOAT64;                                                                                    /* Pi const using float64_t value.                                            */

/* Math utils functions prototypes: */
c_utils_float32_t c_utils_circumfer_float(const c_utils_float32_t radius_value);                                                           /* Function to calculate a circumference using a float value.              */
c_utils_float32_t c_utils_circle_area_float(const c_utils_float32_t radius_value);                                                         /* Function to calculate the area of a circle using a float value.         */
c_utils_float32_t c_utils_sphere_volume_float(const c_utils_float32_t radius_value);                                                       /* Function to calculate the volume of a sphere using a float value.       */
c_utils_float32_t c_utils_summation_float(c_utils_float32_t (*f)(c_utils_float32_t i), c_utils_int32_t index, const c_utils_int32_t end);  /* Summation function using float values.                                  */
c_utils_float64_t c_utils_circumfer_double(const c_utils_float64_t radius_value);                                                          /* Function to calculate a circumference using a double value.             */
c_utils_float64_t c_utils_circle_area_double(const c_utils_float64_t radius_value);                                                        /* Function to calculate the area of a circle using a double value.        */
c_utils_float64_t c_utils_sphere_volume_double(const c_utils_float64_t radius_value);                                                      /* Function to calculate the volume of a sphere using a double value.      */
c_utils_float64_t c_utils_summation_double(c_utils_float64_t (*f)(c_utils_float64_t i), c_utils_int32_t index, const c_utils_int32_t end); /* Summation function using double values.                                 */

/* End C to C++ importation: */
#ifdef __cplusplus
}
#endif

/* End C_UTILS_MATH_UTILS_H: */
#endif
