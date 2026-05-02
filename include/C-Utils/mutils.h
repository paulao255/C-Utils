/* Include guard: */
#if !defined(C_UTILS_M_UTILS_H)
#define C_UTILS_M_UTILS_H

/* Import C to C++: */
#if defined(__cplusplus)
extern "C"
{
#endif

/* Pi constants: */
extern const float       C_UTILS_M_PIf;                                                                              /* Pi const using float value.                                             */
extern const double      C_UTILS_M_PI ;                                                                              /* Pi const using double value.                                            */
extern const long double C_UTILS_M_PIl;                                                                              /* Pi const using long double value.                                       */

/* Math utils functions prototypes: */
float c_utils_circumfer_f(const float radius_value);                                                                 /* Function to calculate a circumference using a float value.              */
float c_utils_circle_area_f(const float radius_value);                                                               /* Function to calculate the area of a circle using a float value.         */
float c_utils_sphere_volume_f(const float radius_value);                                                             /* Function to calculate the volume of a sphere using a float value.       */
float c_utils_summation_f(float (*f)(float i), signed long int index, const signed long int end);                    /* Summation function using float values.                                  */
double c_utils_circumfer_d(const double radius_value);                                                               /* Function to calculate a circumference using a double value.             */
double c_utils_circle_area_d(const double radius_value);                                                             /* Function to calculate the area of a circle using a double value.        */
double c_utils_sphere_volume_d(const double radius_value);                                                           /* Function to calculate the volume of a sphere using a double value.      */
double c_utils_summation_d(double (*f)(double i), signed long int index, const signed long int end);                 /* Summation function using double values.                                 */
long double c_utils_circumfer_ld(const long double radius_value);                                                    /* Function to calculate a circumference using a long double value.        */
long double c_utils_circle_area_ld(const long double radius_value);                                                  /* Function to calculate the area of a circle using a long double value.   */
long double c_utils_sphere_volume_ld(const long double radius_value);                                                /* Function to calculate the volume of a sphere using a long double value. */
long double c_utils_summation_ld(long double (*f)(long double i), signed long int index, const signed long int end); /* Summation function using long double values.                            */

/* End importation: */
#if defined(__cplusplus)
}
#endif

/* End C_UTILS_M_UTILS_H: */
#endif
