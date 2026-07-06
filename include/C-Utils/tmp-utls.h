/******************/
/* Include guard: */
/******************/

#ifndef C_UTILS_TMP_UTLS_H
#define C_UTILS_TMP_UTLS_H

/*************************/
/* Library importations: */
/*************************/

#include "defs.h"
#include <stddef.h>

/********************/
/* Import C to C++: */
/********************/

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************/
/* Temperature limits constants: */
/*********************************/

/* Minimum Celsius temperature constant (in float32_t). */
extern const c_utils_float32_t C_UTILS_MIN_CELSIUS_FLOAT32;

/* Minimum Fahrenheit temperature constant (in float32_t). */
extern const c_utils_float32_t C_UTILS_MIN_FAHRENHEIT_FLOAT32;

/* Minimum Kelvin temperature constant (in float32_t). */
extern const c_utils_float32_t C_UTILS_MIN_KELVIN_FLOAT32;

/* Minimum Celsius temperature constant (in float64_t). */
extern const c_utils_float64_t C_UTILS_MIN_CELSIUS_FLOAT64;

/* Minimum Fahrenheit temperature constant (in float64_t). */
extern const c_utils_float64_t C_UTILS_MIN_FAHRENHEIT_FLOAT64;

/* Minimum Kelvin temperature constant (in float64_t). */
extern const c_utils_float64_t C_UTILS_MIN_KELVIN_FLOAT64;

/*************************/
/* Functions prototypes: */
/*************************/

/* Generic Kelvin to Celsius conversion function. */
c_utils_int16_t c_utils_generic_kelvin_to_celsius(const void *const kelvin_value_pointer, void *const celsius_value_pointer, size_t size);

/* Generic Kelvin to Fahrenheit conversion function. */
c_utils_int16_t c_utils_generic_kelvin_to_fahrenheit(const void *const kelvin_value_pointer, void *const fahrenheit_value_pointer, size_t size);

/* Generic Celsius to Fahrenheit conversion function. */
c_utils_int16_t c_utils_generic_celsius_to_fahrenheit(const void *const celsius_value_pointer, void *const fahrenheit_value_pointer, size_t size);

/* Generic Celsius to Kelvin conversion function. */
c_utils_int16_t c_utils_generic_celsius_to_kelvin(const void *const celsius_value_pointer, void *const kelvin_value_pointer, size_t size);

/* Generic Fahrenheit to Celsius conversion function. */
c_utils_int16_t c_utils_generic_fahrenheit_to_celsius(const void *const fahrenheit_value_pointer, void *const celsius_value_pointer, size_t size);

/* Generic Fahrenheit to Kelvin conversion function. */
c_utils_int16_t c_utils_generic_fahrenheit_to_kelvin(const void *const fahrenheit_value_pointer, void *const kelvin_value_pointer, size_t size);

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif

/***************************/
/* End C_UTILS_TMP_UTLS_H: */
/***************************/

#endif
