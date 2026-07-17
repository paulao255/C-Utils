/*************************/
/* Library importations: */
/*************************/

#include "tmp-utls.h"
#include <stdio.h>

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

const c_utils_float32_t C_UTILS_MIN_CELSIUS_FLOAT32    = -273.15f;
const c_utils_float32_t C_UTILS_MIN_FAHRENHEIT_FLOAT32 = -459.67f;
const c_utils_float32_t C_UTILS_MIN_KELVIN_FLOAT32     =    0.0f ;
const c_utils_float64_t C_UTILS_MIN_CELSIUS_FLOAT64    = -273.15 ;
const c_utils_float64_t C_UTILS_MIN_FAHRENHEIT_FLOAT64 = -459.67 ;
const c_utils_float64_t C_UTILS_MIN_KELVIN_FLOAT64     =    0.0  ;

/**************************/
/* Functions definitions: */
/**************************/

c_utils_int16_t c_utils_generic_kelvin_to_celsius(const void *const kelvin_value_pointer, void *const celsius_value_pointer, size_t size)
{
	if(kelvin_value_pointer == (void *)0)
	{
		fprintf(stderr, "Error in function c_utils_generic_kelvin_to_celsius (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(celsius_value_pointer == (void *)0)
	{
		fprintf(stderr, "Error in function c_utils_generic_kelvin_to_celsius (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(size == 4u)
	{
		c_utils_float32_t kelvin_value = *(c_utils_float32_t *)kelvin_value_pointer;
		*(c_utils_float32_t *)celsius_value_pointer = kelvin_value - 273.15f;
	}

	else if(size == 8u)
	{
		c_utils_float64_t kelvin_value = *(c_utils_float64_t *)kelvin_value_pointer;
		*(c_utils_float64_t *)celsius_value_pointer = kelvin_value - 273.15;
	}

	else
	{
		fprintf(stderr, "Error in function c_utils_generic_kelvin_to_celsius (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	return C_UTILS_SUCCESS;
}

c_utils_int16_t c_utils_generic_kelvin_to_fahrenheit(const void *const kelvin_value_pointer, void *const fahrenheit_value_pointer, size_t size)
{
	if(kelvin_value_pointer == (void *)0)
	{
		fprintf(stderr, "Error in function c_utils_generic_kelvin_to_fahrenheit (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(fahrenheit_value_pointer == (void *)0)
	{
		fprintf(stderr, "Error in function c_utils_generic_kelvin_to_fahrenheit (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(size == 4u)
	{
		c_utils_float32_t kelvin_value = *(c_utils_float32_t *)kelvin_value_pointer;
		*(c_utils_float32_t *)fahrenheit_value_pointer = kelvin_value * (9.0f / 5.0f) - 459.67f;
	}

	else if(size == 8u)
	{
		c_utils_float64_t kelvin_value = *(c_utils_float64_t *)kelvin_value_pointer;
		*(c_utils_float64_t *)fahrenheit_value_pointer = kelvin_value * (9.0 / 5.0) - 459.67;
	}

	else
	{
		fprintf(stderr, "Error in function c_utils_generic_kelvin_to_fahrenheit (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	return C_UTILS_SUCCESS;
}

c_utils_int16_t c_utils_generic_celsius_to_fahrenheit(const void *const celsius_value_pointer, void *const fahrenheit_value_pointer, size_t size)
{
	if(celsius_value_pointer == (void *)0)
	{
		fprintf(stderr, "Error in function c_utils_generic_celsius_to_fahrenheit (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(fahrenheit_value_pointer == (void *)0)
	{
		fprintf(stderr, "Error in function c_utils_generic_celsius_to_fahrenheit (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(size == 4u)
	{
		c_utils_float32_t celsius_value = *(c_utils_float32_t *)celsius_value_pointer;
		*(c_utils_float32_t *)fahrenheit_value_pointer = celsius_value * (9.0f / 5.0f) + 32.0f;
	}

	else if(size == 8u)
	{
		c_utils_float64_t celsius_value = *(c_utils_float64_t *)celsius_value_pointer;
		*(c_utils_float64_t *)fahrenheit_value_pointer = celsius_value * (9.0 / 5.0) + 32.0;
	}

	else
	{
		fprintf(stderr, "Error in function c_utils_generic_celsius_to_fahrenheit (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	return C_UTILS_SUCCESS;
}

c_utils_int16_t c_utils_generic_celsius_to_kelvin(const void *const celsius_value_pointer, void *const kelvin_value_pointer, size_t size)
{
	if(celsius_value_pointer == (void *)0)
	{
		fprintf(stderr, "Error in function c_utils_generic_celsius_to_kelvin (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(kelvin_value_pointer == (void *)0)
	{
		fprintf(stderr, "Error in function c_utils_generic_celsius_to_kelvin (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(size == 4u)
	{
		c_utils_float32_t celsius_value = *(c_utils_float32_t *)celsius_value_pointer;
		*(c_utils_float32_t *)kelvin_value_pointer = celsius_value + 273.15f;
	}

	else if(size == 8u)
	{
		c_utils_float64_t celsius_value = *(c_utils_float64_t *)celsius_value_pointer;
		*(c_utils_float64_t *)kelvin_value_pointer = celsius_value + 273.15;
	}

	else
	{
		fprintf(stderr, "Error in function c_utils_generic_celsius_to_kelvin (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	return C_UTILS_SUCCESS;
}

c_utils_int16_t c_utils_generic_fahrenheit_to_celsius(const void *const fahrenheit_value_pointer, void *const celsius_value_pointer, size_t size)
{
	if(fahrenheit_value_pointer == (void *)0)
	{
		fprintf(stderr, "Error in function c_utils_generic_fahrenheit_to_celsius (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(celsius_value_pointer == (void *)0)
	{
		fprintf(stderr, "Error in function c_utils_generic_fahrenheit_to_celsius (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(size == 4u)
	{
		c_utils_float32_t fahrenheit_value = *(c_utils_float32_t *)fahrenheit_value_pointer;
		*(c_utils_float32_t *)celsius_value_pointer = (fahrenheit_value - 32.0f) * (5.0f / 9.0f);
	}

	else if(size == 8u)
	{
		c_utils_float64_t fahrenheit_value = *(c_utils_float64_t *)fahrenheit_value_pointer;
		*(c_utils_float64_t *)celsius_value_pointer = (fahrenheit_value - 32.0) * (5.0 / 9.0);
	}

	else
	{	
		fprintf(stderr, "Error in function c_utils_generic_fahrenheit_to_celsius (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	return C_UTILS_SUCCESS;
}

c_utils_int16_t c_utils_generic_fahrenheit_to_kelvin(const void *const fahrenheit_value_pointer, void *const kelvin_value_pointer, size_t size)
{
	if(fahrenheit_value_pointer == (void *)0)
	{
		fprintf(stderr, "Error in function c_utils_generic_fahrenheit_to_kelvin (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(kelvin_value_pointer == (void *)0)
	{
		fprintf(stderr, "Error in function c_utils_generic_fahrenheit_to_kelvin (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(size == 4u)
	{
		c_utils_float32_t fahrenheit_value = *(c_utils_float32_t *)fahrenheit_value_pointer;
		*(c_utils_float32_t *)kelvin_value_pointer = (fahrenheit_value - 32.0f) * (5.0f / 9.0f) + 273.15f;
	}

	else if(size == 8u)
	{
		c_utils_float64_t fahrenheit_value = *(c_utils_float64_t *)fahrenheit_value_pointer;
		*(c_utils_float64_t *)kelvin_value_pointer = (fahrenheit_value - 32.0) * (5.0 / 9.0) + 273.15;
	}

	else
	{
		fprintf(stderr, "Error in function c_utils_generic_fahrenheit_to_kelvin (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	return C_UTILS_SUCCESS;
}

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif
