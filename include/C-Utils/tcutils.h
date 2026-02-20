/* Include guard: */
#ifndef C_UTILS_T_C_UTILS_H
#define C_UTILS_T_C_UTILS_H

/* Importations: */
#include "defs.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* Temperature conversion functions prototypes: */
static const float kelvin_to_celsius_f(const float kelvin_val);                      /* Function to convert Kelvin to Celsius using a float value.           */
static const float kelvin_to_fahrenheit_f(const float kelvin_val);                   /* Function to convert Kelvin to Fahrenheit using a float value.        */
static const float celsius_to_kelvin_f(const float celsius_val);                     /* Function to convert Celsius to Kelvin using a float value.           */
static const float celsius_to_fahrenheit_f(const float celsius_val);                 /* Function to convert Celsius to Fahrenheit using a float value.       */
static const float fahrenheit_to_kelvin_f(const float fahrenheit_val);               /* Function to convert Fahrenheit to Kelvin using a float value.        */
static const float fahrenheit_to_celsius_f(const float fahrenheit_val);              /* Function to convert Fahrenheit to Celsius using a float value.       */
static const double kelvin_to_celsius_d(const double kelvin_val);                    /* Function to convert Kelvin to Celsius using a double value.          */
static const double kelvin_to_fahrenheit_d(const double kelvin_val);                 /* Function to convert Kelvin to Fahrenheit using a double value.       */
static const double celsius_to_kelvin_d(const double celsius_val);                   /* Function to convert Celsius to Kelvin using a double value.          */
static const double celsius_to_fahrenheit_d(const double celsius_val);               /* Function to convert Celsius to Fahrenheit using a double value.      */
static const double fahrenheit_to_kelvin_d(const double fahrenheit_val);             /* Function to convert Fahrenheit to Kelvin using a double value.       */
static const double fahrenheit_to_celsius_d(const double fahrenheit_val);            /* Function to convert Fahrenheit to Celsius using a double value.      */
static const long double kelvin_to_celsius_ld(const long double kelvin_val);         /* Function to convert Kelvin to Celsius using a long double value.     */
static const long double kelvin_to_fahrenheit_ld(const long double kelvin_val);      /* Function to convert Kelvin to Fahrenheit using a long double value.  */
static const long double celsius_to_kelvin_ld(const long double celsius_val);        /* Function to convert Celsius to Kelvin using a long double value.     */
static const long double celsius_to_fahrenheit_ld(const long double celsius_val);    /* Function to convert Celsius to Fahrenheit using a long double value. */
static const long double fahrenheit_to_kelvin_ld(const long double fahrenheit_val);  /* Function to convert Fahrenheit to Kelvin using a long double value.  */
static const long double fahrenheit_to_celsius_ld(const long double fahrenheit_val); /* Function to convert Fahrenheit to Celsius using a long double value. */

static const float kelvin_to_celsius_f(const float kelvin_val)
{
	return kelvin_val - 273.15f;
}

static const float kelvin_to_fahrenheit_f(const float kelvin_val)
{
	return kelvin_val * (9.0f / 5.0f) - 459.67f;
}

static const float celsius_to_kelvin_f(const float celsius_val)
{
	return celsius_val + 273.15f;
}

static const float celsius_to_fahrenheit_f(const float celsius_val)
{
	return celsius_val * (9.0f / 5.0f) + 32.0f;
}

static const float fahrenheit_to_kelvin_f(const float fahrenheit_val)
{
	return (fahrenheit_val + 459.67f) * (5.0f / 9.0f);
}

static const float fahrenheit_to_celsius_f(const float fahrenheit_val)
{
	return (fahrenheit_val - 32.0f) * (5.0f / 9.0f);
}

static const double kelvin_to_celsius_d(const double kelvin_val)
{
	return kelvin_val - 273.15;
}

static const double kelvin_to_fahrenheit_d(const double kelvin_val)
{
	return kelvin_val * (9.0 / 5.0) - 459.67;
}

static const double celsius_to_kelvin_d(const double celsius_val)
{
	return celsius_val + 273.15;
}

static const double celsius_to_fahrenheit_d(const double celsius_val)
{
	return celsius_val * (9.0 / 5.0) + 32.0;
}

static const double fahrenheit_to_kelvin_d(const double fahrenheit_val)
{
	return (fahrenheit_val + 459.67) * (5.0 / 9.0);
}

static const double fahrenheit_to_celsius_d(const double fahrenheit_val)
{
	return (fahrenheit_val - 32.0) * (5.0 / 9.0);
}

static const long double kelvin_to_celsius_ld(const long double kelvin_val)
{
	return kelvin_val - 273.15L;
}

static const long double kelvin_to_fahrenheit_ld(const long double kelvin_val)
{
	return kelvin_val * (9.0L / 5.0L) - 459.67L;
}

static const long double celsius_to_kelvin_ld(const long double celsius_val)
{
	return celsius_val + 273.15L;
}

static const long double celsius_to_fahrenheit_ld(const long double celsius_val)
{
	return celsius_val * (9.0L / 5.0L) + 32.0L;
}

static const long double fahrenheit_to_kelvin_ld(const long double fahrenheit_val)
{
	return (fahrenheit_val + 459.67L) * (5.0L / 9.0L);
}

static const long double fahrenheit_to_celsius_ld(const long double fahrenheit_val)
{
	return (fahrenheit_val - 32.0L) * (5.0L / 9.0L);
}

#ifdef __cplusplus
}
#endif

#endif
