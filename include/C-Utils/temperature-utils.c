/* Importations: */
#include "temperature-utils.h"


/* Import C to C++: */
#ifdef __cplusplus
extern "C"
{
#endif

/* Temperature limits: */
const c_utils_float32_t C_UTILS_MIN_CELSIUS_FLOAT32    = -273.15f;
const c_utils_float32_t C_UTILS_MIN_FAHRENHEIT_FLOAT32 = -459.67f;
const c_utils_float32_t C_UTILS_MIN_KELVIN_FLOAT32     =    0.0f ;
const c_utils_float64_t C_UTILS_MIN_CELSIUS_FLOAT64    = -273.15 ;
const c_utils_float64_t C_UTILS_MIN_FAHRENHEIT_FLOAT64 = -459.67 ;
const c_utils_float64_t C_UTILS_MIN_KELVIN_FLOAT64     =    0.0  ;

c_utils_float32_t c_utils_kelvin_to_celsius_float(const c_utils_float32_t kelvin_value)
{
	return kelvin_value - 273.15f;
}

c_utils_float32_t c_utils_kelvin_to_fahrenheit_float(const c_utils_float32_t kelvin_value)
{
	return kelvin_value * (9.0f / 5.0f) - 459.67f;
}

c_utils_float32_t c_utils_celsius_to_kelvin_float(const c_utils_float32_t celsius_value)
{
	return celsius_value + 273.15f;
}

c_utils_float32_t c_utils_celsius_to_fahrenheit_float(const c_utils_float32_t celsius_value)
{
	return celsius_value * (9.0f / 5.0f) + 32.0f;
}

c_utils_float32_t c_utils_fahrenheit_to_kelvin_f(const c_utils_float32_t fahrenheit_value)
{
	return (fahrenheit_value + 459.67f) * (5.0f / 9.0f);
}

c_utils_float32_t c_utils_fahrenheit_to_celsius_f(const c_utils_float32_t fahrenheit_value)
{
	return (fahrenheit_value - 32.0f) * (5.0f / 9.0f);
}

c_utils_float64_t c_utils_kelvin_to_celsius_d(const c_utils_float64_t kelvin_value)
{
	return kelvin_value - 273.15;
}

c_utils_float64_t c_utils_kelvin_to_fahrenheit_d(const c_utils_float64_t kelvin_value)
{
	return kelvin_value * (9.0 / 5.0) - 459.67;
}

c_utils_float64_t c_utils_celsius_to_kelvin_d(const c_utils_float64_t celsius_value)
{
	return celsius_value + 273.15;
}

c_utils_float64_t c_utils_celsius_to_fahrenheit_d(const c_utils_float64_t celsius_value)
{
	return celsius_value * (9.0 / 5.0) + 32.0;
}

c_utils_float64_t c_utils_fahrenheit_to_kelvin_d(const c_utils_float64_t fahrenheit_value)
{
	return (fahrenheit_value + 459.67) * (5.0 / 9.0);
}

c_utils_float64_t c_utils_fahrenheit_to_celsius_d(const c_utils_float64_t fahrenheit_value)
{
	return (fahrenheit_value - 32.0) * (5.0 / 9.0);
}

/* End importation: */
#ifdef __cplusplus
}
#endif
