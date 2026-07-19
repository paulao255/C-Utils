/*************************/
/* Library importations: */
/*************************/

#include "mth-utls.h"
#include <float.h>
#include <math.h>
#include <stdio.h>

/********************/
/* Import C to C++: */
/********************/

#ifdef __cplusplus
extern "C"
{
#endif

/**************/
/* Constants: */
/**************/

const c_utils_float32_t C_UTILS_MATH_PI_FLOAT32 = 3.141592653589793f;
const c_utils_float32_t C_UTILS_MATH_E_FLOAT32  = 2.718281828459045f;
const c_utils_float64_t C_UTILS_MATH_PI_FLOAT64 = 3.141592653589793;
const c_utils_float64_t C_UTILS_MATH_E_FLOAT64  = 2.718281828459045;

/**************************/
/* Functions definitions: */
/**************************/

c_utils_int16_t c_utils_generic_summation(const void *const lower_bound, const void *const upper_bound, const void *(*const f)(const void *const i, const size_t f_element_size), const size_t element_size, const void *const result)
{
	if(!lower_bound)
	{
		fprintf(stderr, "Error in function c_utils_generic_summation (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(!upper_bound)
	{
		fprintf(stderr, "Error in function c_utils_generic_summation (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(!f)
	{
		fprintf(stderr, "Error in function c_utils_generic_summation (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(!result)
	{
		fprintf(stderr, "Error in function c_utils_generic_summation (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(element_size == 4u)
	{
		c_utils_float32_t type_lower_bound = *(c_utils_float32_t *)lower_bound;
		c_utils_float32_t type_upper_bound = *(c_utils_float32_t *)upper_bound;
		c_utils_float32_t accumulator = 0.0f;
		c_utils_float32_t counter;

		if(type_lower_bound > type_upper_bound)
		{
			fprintf(stderr, "Error in function c_utils_generic_summation (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_FAILURE;
		}

		for(counter = type_lower_bound; counter <= type_upper_bound; counter++)
		{
			c_utils_float32_t current_value = counter;
			const void *const term_pointer = f((void *)&current_value, element_size);

			if(!term_pointer)
			{
				fprintf(stderr, "Error in function c_utils_generic_summation (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_FAILURE;
			}

			else
			{
				c_utils_float32_t type_term = *(c_utils_float32_t *)term_pointer;
				c_utils_float32_t previous_accumulator = accumulator;
				accumulator += type_term;

				if(accumulator > C_UTILS_FLOAT32_MAX)
				{
					fprintf(stderr, "Error in function c_utils_generic_summation (File: %s, Line: %d)...\n", __FILE__, __LINE__);

					return C_UTILS_FAILURE;
				}

				if(accumulator < -C_UTILS_FLOAT32_MAX)
				{
					fprintf(stderr, "Error in function c_utils_generic_summation (File: %s, Line: %d)...\n", __FILE__, __LINE__);

					return C_UTILS_FAILURE;
				}

				if(previous_accumulator != 0.0f && type_term != 0.0f && accumulator == previous_accumulator && (previous_accumulator > 0.0f ? type_term > 0.0f : type_term < 0.0f))
				{
					fprintf(stderr, "Error in function c_utils_generic_summation (File: %s, Line: %d)...\n", __FILE__, __LINE__);

					return C_UTILS_FAILURE;
				}
			}
		}

		*(c_utils_float32_t *)result = accumulator;
	}

	else if(element_size == 8u)
	{
		c_utils_float64_t type_lower_bound = *(c_utils_float64_t *)lower_bound;
		c_utils_float64_t type_upper_bound = *(c_utils_float64_t *)upper_bound;
		c_utils_float64_t accumulator = 0.0;
		c_utils_float64_t counter;

		if(type_lower_bound > type_upper_bound)
		{
			fprintf(stderr, "Error in function c_utils_generic_summation (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_FAILURE;
		}

		for(counter = type_lower_bound; counter <= type_upper_bound; counter++)
		{
			c_utils_float64_t current_value = counter;
			const void *const term_pointer = f((void *)&current_value, element_size);

			if(!term_pointer)
			{
				fprintf(stderr, "Error in function c_utils_generic_summation (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_FAILURE;
			}

			else
			{
				c_utils_float64_t type_term = *(c_utils_float64_t *)term_pointer;
				c_utils_float64_t previous_accumulator = accumulator;
				accumulator += type_term;

				if(accumulator > C_UTILS_FLOAT64_MAX)
				{
					fprintf(stderr, "Error in function c_utils_generic_summation (File: %s, Line: %d)...\n", __FILE__, __LINE__);

					return C_UTILS_FAILURE;
				}

				if(accumulator < -C_UTILS_FLOAT64_MAX)
				{
					fprintf(stderr, "Error in function c_utils_generic_summation (File: %s, Line: %d)...\n", __FILE__, __LINE__);

					return C_UTILS_FAILURE;
				}

				if(previous_accumulator != 0.0 && type_term != 0.0 && accumulator == previous_accumulator && (previous_accumulator > 0.0 ? type_term > 0.0 : type_term < 0.0))
				{
					fprintf(stderr, "Error in function c_utils_generic_summation (File: %s, Line: %d)...\n", __FILE__, __LINE__);

					return C_UTILS_FAILURE;
				}
			}
		}

		*(c_utils_float64_t *)result = accumulator;
	}

	else
	{
		fprintf(stderr, "Error in function c_utils_generic_summation (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	return C_UTILS_SUCCESS;
}

c_utils_int16_t c_utils_generic_product(const void *const lower_bound, const void *const upper_bound, const void *(*const f)(const void *const i, const size_t f_element_size), const size_t element_size, const void *const result)
{
	if(!lower_bound)
	{
		fprintf(stderr, "Error in function c_utils_generic_product (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(!upper_bound)
	{
		fprintf(stderr, "Error in function c_utils_generic_product (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(!f)
	{
		fprintf(stderr, "Error in function c_utils_generic_product (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(!result)
	{
		fprintf(stderr, "Error in function c_utils_generic_product (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(element_size == 4u)
	{
		c_utils_float32_t type_lower_bound = *(c_utils_float32_t *)lower_bound;
		c_utils_float32_t type_upper_bound = *(c_utils_float32_t *)upper_bound;
		c_utils_float32_t accumulator = 1.0f;
		c_utils_float32_t counter;

		if(type_lower_bound > type_upper_bound)
		{
			fprintf(stderr, "Error in function c_utils_generic_product (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_FAILURE;
		}

		for(counter = type_lower_bound; counter <= type_upper_bound; counter++)
		{
			c_utils_float32_t current_value = counter;
			const void *const term_pointer = f((void *)&current_value, element_size);

			if(!term_pointer)
			{
				fprintf(stderr, "Error in function c_utils_generic_product (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_FAILURE;
			}

			else
			{
				c_utils_float32_t type_term = *(c_utils_float32_t *)term_pointer;
				accumulator *= type_term;

				if(accumulator > C_UTILS_FLOAT32_MAX)
				{
					fprintf(stderr, "Error in function c_utils_generic_product (File: %s, Line: %d)...\n", __FILE__, __LINE__);

					return C_UTILS_FAILURE;
				}

				if(accumulator < -C_UTILS_FLOAT32_MAX)
				{
					fprintf(stderr, "Error in function c_utils_generic_product (File: %s, Line: %d)...\n", __FILE__, __LINE__);

					return C_UTILS_FAILURE;
				}

				if(type_term != 0.0f && accumulator == 0.0f)
				{
					fprintf(stderr, "Error in function c_utils_generic_product (File: %s, Line: %d)...\n", __FILE__, __LINE__);

					return C_UTILS_FAILURE;
				}
			}
		}

		*(c_utils_float32_t *)result = accumulator;
	}

	else if(element_size == 8u)
	{
		c_utils_float64_t type_lower_bound = *(c_utils_float64_t *)lower_bound;
		c_utils_float64_t type_upper_bound = *(c_utils_float64_t *)upper_bound;
		c_utils_float64_t accumulator = 1.0;
		c_utils_float64_t counter;

		if(type_lower_bound > type_upper_bound)
		{
			fprintf(stderr, "Error in function c_utils_generic_product (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_FAILURE;
		}

		for(counter = type_lower_bound; counter <= type_upper_bound; counter++)
		{
			c_utils_float64_t current_value = counter;
			const void *const term_pointer = f((void *)&current_value, element_size);

			if(!term_pointer)
			{
				fprintf(stderr, "Error in function c_utils_generic_product (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_FAILURE;
			}

			else
			{
				c_utils_float64_t type_term = *(c_utils_float64_t *)term_pointer;
				accumulator *= type_term;

				if(accumulator > C_UTILS_FLOAT64_MAX)
				{
					fprintf(stderr, "Error in function c_utils_generic_product (File: %s, Line: %d)...\n", __FILE__, __LINE__);

					return C_UTILS_FAILURE;
				}

				if(accumulator < -C_UTILS_FLOAT64_MAX)
				{
					fprintf(stderr, "Error in function c_utils_generic_product (File: %s, Line: %d)...\n", __FILE__, __LINE__);

					return C_UTILS_FAILURE;
				}

				if(type_term != 0.0 && accumulator == 0.0)
				{
					fprintf(stderr, "Error in function c_utils_generic_product (File: %s, Line: %d)...\n", __FILE__, __LINE__);

					return C_UTILS_FAILURE;
				}
			}
		}

		*(c_utils_float64_t *)result = accumulator;
	}

	else
	{
		fprintf(stderr, "Error in function c_utils_generic_product (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	return C_UTILS_SUCCESS;
}

c_utils_int16_t c_utils_factorial(const void *const value, const size_t element_size, const void *const result)
{
	if(!value)
	{
		fprintf(stderr, "Error in function c_utils_factorial (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(!result)
	{
		fprintf(stderr, "Error in function c_utils_factorial (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(element_size == 4u)
	{
		c_utils_float32_t type_value = *(c_utils_float32_t *)value;
		c_utils_float32_t accumulator = 1.0f;
		c_utils_float32_t counter;

		if(type_value < 0.0f)
		{
			fprintf(stderr, "Error in function c_utils_factorial (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_FAILURE;
		}

		for(counter = 2.0f; counter <= type_value; counter++)
		{
			accumulator *= counter;

			if(accumulator > C_UTILS_FLOAT32_MAX)
			{
				fprintf(stderr, "Error in function c_utils_factorial (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_FAILURE;
			}

			if(accumulator < -C_UTILS_FLOAT32_MAX)
			{
				fprintf(stderr, "Error in function c_utils_factorial (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_FAILURE;
			}

			if(accumulator == 0.0f)
			{
				fprintf(stderr, "Error in function c_utils_factorial (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_FAILURE;
			}
		}

		*(c_utils_float32_t *)result = accumulator;
	}

	else if(element_size == 8u)
	{
		c_utils_float64_t type_value = *(c_utils_float64_t *)value;
		c_utils_float64_t accumulator = 1.0;
		c_utils_float64_t counter;

		if(type_value < 0.0)
		{
			fprintf(stderr, "Error in function c_utils_factorial (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_FAILURE;
		}

		for(counter = 2.0; counter <= type_value; counter++)
		{
			accumulator *= counter;

			if(accumulator > C_UTILS_FLOAT64_MAX)
			{
				fprintf(stderr, "Error in function c_utils_factorial (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_FAILURE;
			}

			if(accumulator < -C_UTILS_FLOAT64_MAX)
			{
				fprintf(stderr, "Error in function c_utils_factorial (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_FAILURE;
			}

			if(accumulator == 0.0)
			{
				fprintf(stderr, "Error in function c_utils_factorial (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_FAILURE;
			}
		}

		*(c_utils_float64_t *)result = accumulator;
	}

	else
	{
		fprintf(stderr, "Error in function c_utils_factorial (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	return C_UTILS_SUCCESS;
}

c_utils_int16_t c_utils_generic_log_base(const void *const base, const void *const value, const size_t element_size, void *const result)
{
	if(!base)
	{
		fprintf(stderr, "Error in function c_utils_generic_log_base (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(!value)
	{
		fprintf(stderr, "Error in function c_utils_generic_log_base (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(!result)
	{
		fprintf(stderr, "Error in function c_utils_generic_log_base (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(element_size == 4u)
	{
		c_utils_float32_t type_base = *(c_utils_float32_t *)base;
		c_utils_float32_t type_value = *(c_utils_float32_t *)value;

		if(type_base <= 0.0f)
		{
			fprintf(stderr, "Error in function c_utils_generic_log_base (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_FAILURE;
		}

		if(type_base == 1.0f)
		{
			fprintf(stderr, "Error in function c_utils_generic_log_base (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_FAILURE;
		}

		if(type_value <= 0.0f)
		{
			fprintf(stderr, "Error in function c_utils_generic_log_base (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_FAILURE;
		}

		*(c_utils_float32_t *)result = (c_utils_float32_t)(log((c_utils_float64_t)type_value) / log((c_utils_float64_t)type_base));
	}

	else if(element_size == 8u)
	{
		c_utils_float64_t type_base = *(c_utils_float64_t *)base;
		c_utils_float64_t type_value = *(c_utils_float64_t *)value;

		if(type_base <= 0.0)
		{
			fprintf(stderr, "Error in function c_utils_generic_log_base (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_FAILURE;
		}

		if(type_base == 1.0)
		{
			fprintf(stderr, "Error in function c_utils_generic_log_base (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_FAILURE;
		}

		if(type_value <= 0.0)
		{
			fprintf(stderr, "Error in function c_utils_generic_log_base (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_FAILURE;
		}

		*(c_utils_float64_t *)result = log(type_value) / log(type_base);
	}

	else
	{
		fprintf(stderr, "Error in function c_utils_generic_log_base (File: %s, Line: %d)...\n", __FILE__, __LINE__);

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
