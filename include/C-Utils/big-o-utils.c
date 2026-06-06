/* Importations: */
#include "big-o-utils.h"
#include <stdio.h>
#include <string.h>


/* Import C to C++: */
#ifdef __cplusplus
extern "C"
{
#endif

c_utils_int16_t c_utils_linear_char_t_search(const c_utils_char_t *const array, const size_t count, const c_utils_char_t target, size_t *const position)
{
	if(array == (const c_utils_char_t *)0)
	{
		fprintf(stderr, "Error in function c_utils_linear_char_t_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(position == (const size_t *)0)
	{
		fprintf(stderr, "Error in function c_utils_linear_char_t_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	else
	{
		size_t index;

		for(index = 0U; index < count; index++)
		{
			if(array[index] == target)
			{
				*position = index;

				return C_UTILS_SUCCESS;
			}
		}
	}

	return C_UTILS_FAILURE;
}

c_utils_int16_t c_utils_linear_int16_t_search(const c_utils_int16_t *const array, const size_t count, const c_utils_int16_t target, size_t *const position)
{
	if(array == (const c_utils_int16_t *)0)
	{
		fprintf(stderr, "Error in function c_utils_linear_int16_t_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(position == (const size_t *)0)
	{
		fprintf(stderr, "Error in function c_utils_linear_int16_t_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	else
	{
		size_t index;

		for(index = 0U; index < count; index++)
		{
			if(array[index] == target)
			{
				*position = index;

				return C_UTILS_SUCCESS;
			}
		}
	}

	return C_UTILS_FAILURE;
}

c_utils_int16_t c_utils_linear_int32_t_search(const c_utils_int32_t *const array, const size_t count, const c_utils_int32_t target, size_t *const position)
{
	if(array == (const c_utils_int32_t *)0)
	{
		fprintf(stderr, "Error in function c_utils_linear_int32_t_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(position == (const size_t *)0)
	{
		fprintf(stderr, "Error in function c_utils_linear_int32_t_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	else
	{
		size_t index;

		for(index = 0U; index < count; index++)
		{
			if(array[index] == target)
			{
				*position = index;

				return C_UTILS_SUCCESS;
			}
		}
	}

	return C_UTILS_FAILURE;
}

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L) || \
    defined(C_UTILS_ENABLE_LONG_LONG_INT) || defined(C_UTILS_ENABLE_ALL_EXTENSIONS)
c_utils_int16_t c_utils_linear_int64_t_search(const c_utils_int64_t *const array, const size_t count, const c_utils_int64_t target, size_t *const position)
{
	if(array == (const c_utils_int64_t *const)0)
	{
		fprintf(stderr, "Error in function c_utils_linear_int64_t_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(position == (size_t *const)0)
	{
		fprintf(stderr, "Error in function c_utils_linear_int64_t_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	else
	{
		size_t index;

		for(index = 0U; index < count; index++)
		{
			if(array[index] == target)
			{
				*position = index;

				return C_UTILS_SUCCESS;
			}
		}
	}

	return C_UTILS_FAILURE;
}
#endif

c_utils_int16_t c_utils_linear_float32_t_search(const c_utils_float32_t *const array, const size_t count, const c_utils_float32_t target, size_t *const position)
{
	if(array == (const c_utils_float32_t *)0)
	{
		fprintf(stderr, "Error in function c_utils_linear_float32_t_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(position == (const size_t *)0)
	{
		fprintf(stderr, "Error in function c_utils_linear_float32_t_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	else
	{
		size_t index;

		for(index = 0U; index < count; index++)
		{
			const c_utils_float32_t difference = array[index] - target;

			if((difference < 0.0f ? -difference : difference) < 10 * FLT_EPSILON)
			{
				*position = index;

				return C_UTILS_SUCCESS;
			}
		}
	}

	return C_UTILS_FAILURE;
}

c_utils_int16_t c_utils_linear_float64_t_search(const c_utils_float64_t *const array, const size_t count, const c_utils_float64_t target, size_t *const position)
{
	if(array == (const c_utils_float64_t *)0)
	{
		fprintf(stderr, "Error in function c_utils_linear_float64_t_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(position == (const size_t *)0)
	{
		fprintf(stderr, "Error in function c_utils_linear_float64_t_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	else
	{
		size_t index;

		for(index = 0U; index < count; index++)
		{
			const c_utils_float64_t difference = array[index] - target;

			if((difference < 0.0 ? -difference : difference) < 10 * DBL_EPSILON)
			{
				*position = index;

				return C_UTILS_SUCCESS;
			}
		}
	}

	return C_UTILS_FAILURE;
}

c_utils_int16_t c_utils_linear_char_t_array_search(const c_utils_char_t *const *const array, const size_t count, const c_utils_char_t *const target, size_t *const position)
{
	if(array == (const c_utils_char_t *const *)0)
	{
		fprintf(stderr, "Error in function c_utils_linear_char_t_array_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(target == (const c_utils_char_t *)0)
	{
		fprintf(stderr, "Error in function c_utils_linear_char_t_array_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(position == (size_t *)0)
	{
		fprintf(stderr, "Error in function c_utils_linear_char_t_array_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	else
	{
		size_t index;

		for(index = 0U; index < count; index++)
		{
			if(!strcmp(array[index], target))
			{
				*position = index;

				return C_UTILS_SUCCESS;
			}
		}
	}

	return C_UTILS_FAILURE;
}

/* End C to C++ importation: */
#ifdef __cplusplus
}
#endif
