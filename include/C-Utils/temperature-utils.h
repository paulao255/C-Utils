/* Include guard: */
#ifndef C_UTILS_TEMPERATURE_UTILS_H
#define C_UTILS_TEMPERATURE_UTILS_H

/* Importations: */
#include "definitions.h"


/* Import C to C++: */
#ifdef __cplusplus
extern "C"
{
#endif

/* Temperature limits: */
extern const c_utils_float32_t C_UTILS_MIN_CELSIUS_FLOAT32   ;                                    /* Minimum Celsius temperature constant (in float32_t).                 */
extern const c_utils_float32_t C_UTILS_MIN_FAHRENHEIT_FLOAT32;                                    /* Minimum Fahrenheit temperature constant (in float32_t).              */
extern const c_utils_float32_t C_UTILS_MIN_KELVIN_FLOAT32    ;                                    /* Minimum Kelvin temperature constant (in float32_t).                  */
extern const c_utils_float64_t C_UTILS_MIN_CELSIUS_FLOAT64   ;                                    /* Minimum Celsius temperature constant (in float64_t).                 */
extern const c_utils_float64_t C_UTILS_MIN_FAHRENHEIT_FLOAT64;                                    /* Minimum Fahrenheit temperature constant (in float64_t).              */
extern const c_utils_float64_t C_UTILS_MIN_KELVIN_FLOAT64    ;                                    /* Minimum Kelvin temperature constant (in float64_t).                  */

/* Temperature conversion functions prototypes: */
c_utils_float32_t c_utils_kelvin_to_celsius_float(const c_utils_float32_t kelvin_value);          /* Function to convert Kelvin to Celsius using a float value.           */
c_utils_float32_t c_utils_kelvin_to_fahrenheit_float(const c_utils_float32_t kelvin_value);       /* Function to convert Kelvin to Fahrenheit using a float value.        */
c_utils_float32_t c_utils_celsius_to_kelvin_float(const c_utils_float32_t celsius_value);         /* Function to convert Celsius to Kelvin using a float value.           */
c_utils_float32_t c_utils_celsius_to_fahrenheit_float(const c_utils_float32_t celsius_value);     /* Function to convert Celsius to Fahrenheit using a float value.       */
c_utils_float32_t c_utils_fahrenheit_to_kelvin_float(const c_utils_float32_t fahrenheit_value);   /* Function to convert Fahrenheit to Kelvin using a float value.        */
c_utils_float32_t c_utils_fahrenheit_to_celsius_float(const c_utils_float32_t fahrenheit_value);  /* Function to convert Fahrenheit to Celsius using a float value.       */
c_utils_float64_t c_utils_kelvin_to_celsius_double(const c_utils_float64_t kelvin_value);         /* Function to convert Kelvin to Celsius using a double value.          */
c_utils_float64_t c_utils_kelvin_to_fahrenheit_double(const c_utils_float64_t kelvin_value);      /* Function to convert Kelvin to Fahrenheit using a double value.       */
c_utils_float64_t c_utils_celsius_to_kelvin_double(const c_utils_float64_t celsius_value);        /* Function to convert Celsius to Kelvin using a double value.          */
c_utils_float64_t c_utils_celsius_to_fahrenheit_double(const c_utils_float64_t celsius_value);    /* Function to convert Celsius to Fahrenheit using a double value.      */
c_utils_float64_t c_utils_fahrenheit_to_kelvin_double(const c_utils_float64_t fahrenheit_value);  /* Function to convert Fahrenheit to Kelvin using a double value.       */
c_utils_float64_t c_utils_fahrenheit_to_celsius_double(const c_utils_float64_t fahrenheit_value); /* Function to convert Fahrenheit to Celsius using a double value.      */

/* End C to C++ importation: */
#ifdef __cplusplus
}
#endif

/* End C_UTILS_TEMPERATURE_UTILS_H: */
#endif
