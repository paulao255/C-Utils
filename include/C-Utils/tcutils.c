/* Importations: */
#include "tcutils.h"


/* Import C to C++: */
#ifdef __cplusplus
extern "C"
{
#endif

float c_utils_kelvin_to_celsius_f(const float kelvin_value)
{
	return kelvin_value - 273.15f;
}

float c_utils_kelvin_to_fahrenheit_f(const float kelvin_value)
{
	return kelvin_value * (9.0f / 5.0f) - 459.67f;
}

float c_utils_celsius_to_kelvin_f(const float celsius_value)
{
	return celsius_value + 273.15f;
}

float c_utils_celsius_to_fahrenheit_f(const float celsius_value)
{
	return celsius_value * (9.0f / 5.0f) + 32.0f;
}

float c_utils_fahrenheit_to_kelvin_f(const float fahrenheit_value)
{
	return (fahrenheit_value + 459.67f) * (5.0f / 9.0f);
}

float c_utils_fahrenheit_to_celsius_f(const float fahrenheit_value)
{
	return (fahrenheit_value - 32.0f) * (5.0f / 9.0f);
}

double c_utils_kelvin_to_celsius_d(const double kelvin_value)
{
	return kelvin_value - 273.15;
}

double c_utils_kelvin_to_fahrenheit_d(const double kelvin_value)
{
	return kelvin_value * (9.0 / 5.0) - 459.67;
}

double c_utils_celsius_to_kelvin_d(const double celsius_value)
{
	return celsius_value + 273.15;
}

double c_utils_celsius_to_fahrenheit_d(const double celsius_value)
{
	return celsius_value * (9.0 / 5.0) + 32.0;
}

double c_utils_fahrenheit_to_kelvin_d(const double fahrenheit_value)
{
	return (fahrenheit_value + 459.67) * (5.0 / 9.0);
}

double c_utils_fahrenheit_to_celsius_d(const double fahrenheit_value)
{
	return (fahrenheit_value - 32.0) * (5.0 / 9.0);
}

long double c_utils_kelvin_to_celsius_ld(const long double kelvin_value)
{
	return kelvin_value - 273.15L;
}

long double c_utils_kelvin_to_fahrenheit_ld(const long double kelvin_value)
{
	return kelvin_value * (9.0L / 5.0L) - 459.67L;
}

long double c_utils_celsius_to_kelvin_ld(const long double celsius_value)
{
	return celsius_value + 273.15L;
}

long double c_utils_celsius_to_fahrenheit_ld(const long double celsius_value)
{
	return celsius_value * (9.0L / 5.0L) + 32.0L;
}

long double c_utils_fahrenheit_to_kelvin_ld(const long double fahrenheit_value)
{
	return (fahrenheit_value + 459.67L) * (5.0L / 9.0L);
}

long double c_utils_fahrenheit_to_celsius_ld(const long double fahrenheit_value)
{
	return (fahrenheit_value - 32.0L) * (5.0L / 9.0L);
}

/* End importation: */
#ifdef __cplusplus
}
#endif
