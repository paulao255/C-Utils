/* Include guard: */
#ifndef C_UTILS_T_C_UTILS_H
#define C_UTILS_T_C_UTILS_H

/* Import C to C++: */
#ifdef __cplusplus
extern "C"
{
#endif

/* Temperature limits: */
extern const float C_UTILS_MINIMUM_CELSIUSf         ;                             /* Minimum Celsius temperature constant (in float).          */
extern const float C_UTILS_MINIMUM_FAHRENHEITf      ;                             /* Minimum Fahrenheit temperature constant (in float).       */
extern const float C_UTILS_MINIMUM_KELVINf          ;                             /* Minimum Kelvin temperature constant (in float).           */
extern const double C_UTILS_MINIMUM_CELSIUS         ;                             /* Minimum Celsius temperature constant (in double).         */
extern const double C_UTILS_MINIMUM_FAHRENHEIT      ;                             /* Minimum Fahrenheit temperature constant (in double).      */
extern const double C_UTILS_MINIMUM_KELVIN          ;                             /* Minimum Kelvin temperature constant (in double).          */
extern const long double C_UTILS_MINIMUM_CELSIUSl   ;                             /* Minimum Celsius temperature constant (in long double).    */
extern const long double C_UTILS_MINIMUM_FAHRENHEITl;                             /* Minimum Fahrenheit temperature constant (in long double). */
extern const long double C_UTILS_MINIMUM_KELVINl    ;                             /* Minimum Kelvin temperature constant (in long double).     */

/* Temperature conversion functions prototypes: */
float c_utils_kelvin_to_celsius_f(const float kelvin_value);                      /* Function to convert Kelvin to Celsius using a float value.           */
float c_utils_kelvin_to_fahrenheit_f(const float kelvin_value);                   /* Function to convert Kelvin to Fahrenheit using a float value.        */
float c_utils_celsius_to_kelvin_f(const float celsius_value);                     /* Function to convert Celsius to Kelvin using a float value.           */
float c_utils_celsius_to_fahrenheit_f(const float celsius_value);                 /* Function to convert Celsius to Fahrenheit using a float value.       */
float c_utils_fahrenheit_to_kelvin_f(const float fahrenheit_value);               /* Function to convert Fahrenheit to Kelvin using a float value.        */
float c_utils_fahrenheit_to_celsius_f(const float fahrenheit_value);              /* Function to convert Fahrenheit to Celsius using a float value.       */
double c_utils_kelvin_to_celsius_d(const double kelvin_value);                    /* Function to convert Kelvin to Celsius using a double value.          */
double c_utils_kelvin_to_fahrenheit_d(const double kelvin_value);                 /* Function to convert Kelvin to Fahrenheit using a double value.       */
double c_utils_celsius_to_kelvin_d(const double celsius_value);                   /* Function to convert Celsius to Kelvin using a double value.          */
double c_utils_celsius_to_fahrenheit_d(const double celsius_value);               /* Function to convert Celsius to Fahrenheit using a double value.      */
double c_utils_fahrenheit_to_kelvin_d(const double fahrenheit_value);             /* Function to convert Fahrenheit to Kelvin using a double value.       */
double c_utils_fahrenheit_to_celsius_d(const double fahrenheit_value);            /* Function to convert Fahrenheit to Celsius using a double value.      */
long double c_utils_kelvin_to_celsius_ld(const long double kelvin_value);         /* Function to convert Kelvin to Celsius using a long double value.     */
long double c_utils_kelvin_to_fahrenheit_ld(const long double kelvin_value);      /* Function to convert Kelvin to Fahrenheit using a long double value.  */
long double c_utils_celsius_to_kelvin_ld(const long double celsius_value);        /* Function to convert Celsius to Kelvin using a long double value.     */
long double c_utils_celsius_to_fahrenheit_ld(const long double celsius_value);    /* Function to convert Celsius to Fahrenheit using a long double value. */
long double c_utils_fahrenheit_to_kelvin_ld(const long double fahrenheit_value);  /* Function to convert Fahrenheit to Kelvin using a long double value.  */
long double c_utils_fahrenheit_to_celsius_ld(const long double fahrenheit_value); /* Function to convert Fahrenheit to Celsius using a long double value. */

/* End importation: */
#ifdef __cplusplus
}
#endif

#endif
