/* Include guard: */
#ifndef C_UTILS_T_C_UTILS_H
#define C_UTILS_T_C_UTILS_H

/* Importations: */
#include "defs.h"


/* Import C to C++: */
#ifdef __cplusplus
extern "C"
{
#endif

/* Temperature limits: */
#define MIN_CELSIUS_F            -273.15f                                 /* Minimum Celsius temperature (in float).                              */
#define MIN_CELSIUS_D            -273.15                                  /* Minimum Celsius temperature (in double).                             */
#define MIN_CELSIUS_L            -273.15L                                 /* Minimum Celsius temperature (in long double).                        */
#define MIN_FAHRENHEIT_F         -459.67f                                 /* Minimum Fahrenheit temperature (in float).                           */
#define MIN_FAHRENHEIT_D         -459.67                                  /* Minimum Fahrenheit temperature (in double).                          */
#define MIN_FAHRENHEIT_L         -459.67L                                 /* Minimum Fahrenheit temperature (in long double).                     */
#define MIN_KELVIN_F                0.0f                                  /* Minimum Kelvin temperature (in float).                               */
#define MIN_KELVIN_D                0.0                                   /* Minimum Kelvin temperature (in double).                              */
#define MIN_KELVIN_L                0.0L                                  /* Minimum Kelvin temperature (in long double).                         */

/* Temperature conversion functions prototypes: */
float kelvin_to_celsius_f(const float kelvin_value);                      /* Function to convert Kelvin to Celsius using a float value.           */
float kelvin_to_fahrenheit_f(const float kelvin_value);                   /* Function to convert Kelvin to Fahrenheit using a float value.        */
float celsius_to_kelvin_f(const float celsius_value);                     /* Function to convert Celsius to Kelvin using a float value.           */
float celsius_to_fahrenheit_f(const float celsius_value);                 /* Function to convert Celsius to Fahrenheit using a float value.       */
float fahrenheit_to_kelvin_f(const float fahrenheit_value);               /* Function to convert Fahrenheit to Kelvin using a float value.        */
float fahrenheit_to_celsius_f(const float fahrenheit_value);              /* Function to convert Fahrenheit to Celsius using a float value.       */
double kelvin_to_celsius_d(const double kelvin_value);                    /* Function to convert Kelvin to Celsius using a double value.          */
double kelvin_to_fahrenheit_d(const double kelvin_value);                 /* Function to convert Kelvin to Fahrenheit using a double value.       */
double celsius_to_kelvin_d(const double celsius_value);                   /* Function to convert Celsius to Kelvin using a double value.          */
double celsius_to_fahrenheit_d(const double celsius_value);               /* Function to convert Celsius to Fahrenheit using a double value.      */
double fahrenheit_to_kelvin_d(const double fahrenheit_value);             /* Function to convert Fahrenheit to Kelvin using a double value.       */
double fahrenheit_to_celsius_d(const double fahrenheit_value);            /* Function to convert Fahrenheit to Celsius using a double value.      */
long double kelvin_to_celsius_ld(const long double kelvin_value);         /* Function to convert Kelvin to Celsius using a long double value.     */
long double kelvin_to_fahrenheit_ld(const long double kelvin_value);      /* Function to convert Kelvin to Fahrenheit using a long double value.  */
long double celsius_to_kelvin_ld(const long double celsius_value);        /* Function to convert Celsius to Kelvin using a long double value.     */
long double celsius_to_fahrenheit_ld(const long double celsius_value);    /* Function to convert Celsius to Fahrenheit using a long double value. */
long double fahrenheit_to_kelvin_ld(const long double fahrenheit_value);  /* Function to convert Fahrenheit to Kelvin using a long double value.  */
long double fahrenheit_to_celsius_ld(const long double fahrenheit_value); /* Function to convert Fahrenheit to Celsius using a long double value. */

/* End importation: */
#ifdef __cplusplus
}
#endif

#endif
