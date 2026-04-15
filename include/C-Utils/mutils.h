/* Include guard: */
#ifndef C_UTILS_M_UTILS_H
#define C_UTILS_M_UTILS_H

/* Importations: */
#include "defs.h"


/* Import C to C++: */
#ifdef __cplusplus
extern "C"
{
#endif

/* Math utils functions prototypes: */
float c_utils_circumfer_f(const float radius_value);                  /* Function to calculate a circumference using a float value.              */
float c_utils_circle_area_f(const float radius_value);                /* Function to calculate the area of a circle using a float value.         */
float c_utils_sphere_volume_f(const float radius_value);              /* Function to calculate the volume of a sphere using a float value.       */
double c_utils_circumfer_d(const double radius_value);                /* Function to calculate a circumference using a double value.             */
double c_utils_circle_area_d(const double radius_value);              /* Function to calculate the area of a circle using a double value.        */
double c_utils_sphere_volume_d(const double radius_value);            /* Function to calculate the volume of a sphere using a double value.      */
long double c_utils_circumfer_ld(const long double radius_value);     /* Function to calculate a circumference using a long double value.        */
long double c_utils_circle_area_ld(const long double radius_value);   /* Function to calculate the area of a circle using a long double value.   */
long double c_utils_sphere_volume_ld(const long double radius_value); /* Function to calculate the volume of a sphere using a long double value. */

/* End importation: */
#ifdef __cplusplus
}
#endif

#endif
