/* Importations: */
#include "mutils.h"


/* Import C to C++: */
#ifdef __cplusplus
extern "C"
{
#endif

float c_utils_circumfer_f(const float radius_value)
{
	return 2.0f * M_PIf * radius_value;
}

float c_utils_circle_area_f(const float radius_value)
{
	return M_PIf * (radius_value * radius_value);
}

float c_utils_sphere_volume_f(const float radius_value)
{
	return (4.0f / 3.0f) * M_PIf * (radius_value * radius_value * radius_value);
}

double c_utils_circumfer_d(const double radius_value)
{
	return 2.0 * M_PI * radius_value;
}

double c_utils_circle_area_d(const double radius_value)
{
	return M_PI * (radius_value * radius_value);
}

double c_utils_sphere_volume_d(const double radius_value)
{
	return (4.0 / 3.0) * M_PI * (radius_value * radius_value * radius_value);
}

long double c_utils_circumfer_ld(const long double radius_value)
{
	return 2.0L * M_PIl * radius_value;
}

long double c_utils_circle_area_ld(const long double radius_value)
{
	return M_PIl * (radius_value * radius_value);
}

long double c_utils_sphere_volume_ld(const long double radius_value)
{
	return (4.0L / 3.0L) * M_PIl * (radius_value * radius_value * radius_value);
}

/* End importation: */
#ifdef __cplusplus
}
#endif
