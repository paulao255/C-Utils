/* Include guard: */
#ifndef C_UTILS_M_UTILS_H
#define C_UTILS_M_UTILS_H

/* Importations: */
#include "defs.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* Math utils functions prototypes: */
static const float circumfer_f(const float radius_val);                  /* Function to calculate a circumference using a float value.              */
static const float circle_area_f(const float radius_val);                /* Function to calculate the area of a circle using a float value.         */
static const float sphere_volume_f(const float radius_val);              /* Function to calculate the volume of a sphere using a float value.       */
static const double circumfer_d(const double radius_val);                /* Function to calculate a circumference using a double value.             */
static const double circle_area_d(const double radius_val);              /* Function to calculate the area of a circle using a double value.        */
static const double sphere_volume_d(const double radius_val);            /* Function to calculate the volume of a sphere using a double value.      */
static const long double circumfer_ld(const long double radius_val);     /* Function to calculate a circumference using a long double value.        */
static const long double circle_area_ld(const long double radius_val);   /* Function to calculate the area of a circle using a long double value.   */
static const long double sphere_volume_ld(const long double radius_val); /* Function to calculate the volume of a sphere using a long double value. */

static const float circumfer_f(const float radius_val)
{
	return 2.0f * PI_F * radius_val;
}

static const float circle_area_f(const float radius_val)
{
	return PI_F * (radius_val * radius_val);
}

static const float sphere_volume_f(const float radius_val)
{
	return (4.0f / 3.0f) * PI_F * (radius_val * radius_val * radius_val);
}

static const double circumfer_d(const double radius_val)
{
	return 2.0 * PI_D * radius_val;
}

static const double circle_area_d(const double radius_val)
{
	return PI_D * (radius_val * radius_val);
}

static const double sphere_volume_d(const double radius_val)
{
	return (4.0 / 3.0) * PI_D * (radius_val * radius_val * radius_val);
}

static const long double circumfer_ld(const long double radius_val)
{
	return 2.0L * PI_LD * radius_val;
}

static const long double circle_area_ld(const long double radius_val)
{
	return PI_LD * (radius_val * radius_val);
}

static const long double sphere_volume_ld(const long double radius_val)
{
	return (4.0L / 3.0L) * PI_LD * (radius_val * radius_val * radius_val);
}

#ifdef __cplusplus
}
#endif

#endif
