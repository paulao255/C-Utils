/* Importations: */
#include "mutils.h"


/* Import C to C++: */
#ifdef __cplusplus
extern "C"
{
#endif

/* Pi constants: */
const float       C_UTILS_M_PIf = 3.141592653589793f; /* Pi const using float value.       */
const double      C_UTILS_M_PI  = 3.141592653589793 ; /* Pi const using double value.      */
const long double C_UTILS_M_PIl = 3.141592653589793L; /* Pi const using long double value. */

float c_utils_circumfer_f(const float radius_value)
{
	return 2.0f * C_UTILS_M_PIf * radius_value;
}

float c_utils_circle_area_f(const float radius_value)
{
	return C_UTILS_M_PIf * (radius_value * radius_value);
}

float c_utils_sphere_volume_f(const float radius_value)
{
	return (4.0f / 3.0f) * C_UTILS_M_PIf * (radius_value * radius_value * radius_value);
}

float c_utils_summation_f(float (*f)(float i), signed long int index, const signed long int end)
{
	float result = 0.0f;

	while(index <= end)
	{
		result = result + f((float)index);
		++index;
	}

	return result;
}

double c_utils_circumfer_d(const double radius_value)
{
	return 2.0 * C_UTILS_M_PI * radius_value;
}

double c_utils_circle_area_d(const double radius_value)
{
	return C_UTILS_M_PI * (radius_value * radius_value);
}

double c_utils_sphere_volume_d(const double radius_value)
{
	return (4.0 / 3.0) * C_UTILS_M_PI * (radius_value * radius_value * radius_value);
}

double c_utils_summation_d(double (*f)(double i), signed long int index, const signed long int end)
{
	double result = 0.0;

	while(index <= end)
	{
		result = result + f((double)index);
		++index;
	}

	return result;
}

long double c_utils_circumfer_ld(const long double radius_value)
{
	return 2.0L * C_UTILS_M_PIl * radius_value;
}

long double c_utils_circle_area_ld(const long double radius_value)
{
	return C_UTILS_M_PIl * (radius_value * radius_value);
}

long double c_utils_sphere_volume_ld(const long double radius_value)
{
	return (4.0L / 3.0L) * C_UTILS_M_PIl * (radius_value * radius_value * radius_value);
}

long double c_utils_summation_ld(long double (*f)(long double i), signed long int index, const signed long int end)
{
	long double result = 0.0;

	while(index <= end)
	{
		result = result + f((long double)index);
		++index;
	}

	return result;
}

/* End importation: */
#ifdef __cplusplus
}
#endif
