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

/* Pi values: */
#if defined(__STDC__) && !defined(__STDC_VERSION__)
#undef M_PIf                                                  /* Undefine M_PIf.                                                         */
#undef M_PI                                                   /* Undefine M_PI.                                                          */
#undef M_PIl                                                  /* Undefine M_PIl.                                                         */
#define M_PIf 3.141592653589793f                              /* Pi macro using float value.                                             */
#define M_PI  3.141592653589793                               /* Pi macro using double value.                                            */
#define M_PIl 3.141592653589793L                              /* Pi macro using long double value.                                       */
#endif

/* Math utils functions prototypes: */
float circumfer_f(const float radius_value);                  /* Function to calculate a circumference using a float value.              */
float circle_area_f(const float radius_value);                /* Function to calculate the area of a circle using a float value.         */
float sphere_volume_f(const float radius_value);              /* Function to calculate the volume of a sphere using a float value.       */
double circumfer_d(const double radius_value);                /* Function to calculate a circumference using a double value.             */
double circle_area_d(const double radius_value);              /* Function to calculate the area of a circle using a double value.        */
double sphere_volume_d(const double radius_value);            /* Function to calculate the volume of a sphere using a double value.      */
long double circumfer_ld(const long double radius_value);     /* Function to calculate a circumference using a long double value.        */
long double circle_area_ld(const long double radius_value);   /* Function to calculate the area of a circle using a long double value.   */
long double sphere_volume_ld(const long double radius_value); /* Function to calculate the volume of a sphere using a long double value. */

/* End importation: */
#ifdef __cplusplus
}
#endif

#endif
