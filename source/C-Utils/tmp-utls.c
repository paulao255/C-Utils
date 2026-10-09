/*************************/
/* Library importations: */
/*************************/

#ifndef C_UTILS_COMPILE
#include "../../include/C-Utils/tmp-utls.h"
#include "../../include/C-Utils/err-utls.h"
#else
#include "C-Utils/tmp-utls.h"
#include "C-Utils/err-utls.h"
#endif
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

C_UTILS_API c_utils_result_t c_utils_generic_kelvin_to_celsius(const c_utils_void_t *const kelvin_value_pointer, c_utils_void_t *const celsius_value_pointer, size_t size)
{
	if(!kelvin_value_pointer)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_kelvin_to_celsius, the kelvin_value_pointer is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!celsius_value_pointer)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_kelvin_to_celsius, the celsius_value_pointer is a null pointer");

		return C_UTILS_RESULT_FAILURE;
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
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_kelvin_to_celsius, the size is invalid");

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_generic_kelvin_to_fahrenheit(const c_utils_void_t *const kelvin_value_pointer, c_utils_void_t *const fahrenheit_value_pointer, size_t size)
{
	if(!kelvin_value_pointer)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_kelvin_to_fahrenheit, the kelvin_value_pointer is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!fahrenheit_value_pointer)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_kelvin_to_fahrenheit, the fahrenheit_value_pointer is a null pointer");

		return C_UTILS_RESULT_FAILURE;
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
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_kelvin_to_fahrenheit, the size is invalid");

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_generic_celsius_to_fahrenheit(const c_utils_void_t *const celsius_value_pointer, c_utils_void_t *const fahrenheit_value_pointer, size_t size)
{
	if(!celsius_value_pointer)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_celsius_to_fahrenheit, the celsius_value_pointer is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!fahrenheit_value_pointer)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_celsius_to_fahrenheit, the fahrenheit_value_pointer is a null pointer");

		return C_UTILS_RESULT_FAILURE;
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
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_celsius_to_fahrenheit, the size is invalid");

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_generic_celsius_to_kelvin(const c_utils_void_t *const celsius_value_pointer, c_utils_void_t *const kelvin_value_pointer, size_t size)
{
	if(!celsius_value_pointer)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_celsius_to_kelvin, the celsius_value_pointer is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!kelvin_value_pointer)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_celsius_to_kelvin, the kelvin_value_pointer is a null pointer");

		return C_UTILS_RESULT_FAILURE;
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
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_celsius_to_kelvin, the size is invalid");

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_generic_fahrenheit_to_celsius(const c_utils_void_t *const fahrenheit_value_pointer, c_utils_void_t *const celsius_value_pointer, size_t size)
{
	if(!fahrenheit_value_pointer)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_fahrenheit_to_celsius, the fahrenheit_value_pointer is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!celsius_value_pointer)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_fahrenheit_to_celsius, the celsius_value_pointer is a null pointer");

		return C_UTILS_RESULT_FAILURE;
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
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_fahrenheit_to_celsius, the size is invalid");

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_generic_fahrenheit_to_kelvin(const c_utils_void_t *const fahrenheit_value_pointer, c_utils_void_t *const kelvin_value_pointer, size_t size)
{
	if(!fahrenheit_value_pointer)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_fahrenheit_to_kelvin, the fahrenheit_value_pointer is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!kelvin_value_pointer)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_fahrenheit_to_kelvin, the kelvin_value_pointer is a null pointer");

		return C_UTILS_RESULT_FAILURE;
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
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_fahrenheit_to_kelvin, the size is invalid");

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif
