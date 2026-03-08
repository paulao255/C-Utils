/* Importations: */
#include "mutils.h"


/* Import C to C++: */
#ifdef __cplusplus
extern "C"
{
#endif

float circumfer_f(const float radius_value)
{
	return 2.0f * PI_F * radius_value;
}

float circle_area_f(const float radius_value)
{
	return PI_F * (radius_value * radius_value);
}

float sphere_volume_f(const float radius_value)
{
	return (4.0f / 3.0f) * PI_F * (radius_value * radius_value * radius_value);
}

double circumfer_d(const double radius_value)
{
	return 2.0 * PI_D * radius_value;
}

double circle_area_d(const double radius_value)
{
	return PI_D * (radius_value * radius_value);
}

double sphere_volume_d(const double radius_value)
{
	return (4.0 / 3.0) * PI_D * (radius_value * radius_value * radius_value);
}

long double circumfer_ld(const long double radius_value)
{
	return 2.0L * PI_LD * radius_value;
}

long double circle_area_ld(const long double radius_value)
{
	return PI_LD * (radius_value * radius_value);
}

long double sphere_volume_ld(const long double radius_value)
{
	return (4.0L / 3.0L) * PI_LD * (radius_value * radius_value * radius_value);
}

#if !defined(__cplusplus) && !defined(__STDC_VERSION__)
float fabsf(const float x)
{
	return x < 0.0f ? -x : x;
}

long double fabsl(const long double x)
{
	return x < 0.0L ? -x : x;
}
#endif

/* End importation: */
#ifdef __cplusplus
}
#endif
