/*************************/
/* Library importations: */
/*************************/

#include "big-data.h"
#include <stdio.h>
#include <string.h>

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L) || \
     defined(C_UTILS_ENABLE_INT64) || defined(C_UTILS_ENABLE_ALL_EXTENSIONS)
#define C_UTILS_MAX_ELEMENT_SIZE 8U
#else
#define C_UTILS_MAX_ELEMENT_SIZE 4U
#endif

/********************/
/* Import C to C++: */
/********************/

#ifdef __cplusplus
extern "C"
{
#endif

/**************************/
/* Functions definitions: */
/**************************/

c_utils_int16_t c_utils_generic_linear_search(const void *const array, const void *const target, const size_t count, const size_t element_size, const c_utils_uint8_t type, size_t *const position)
{
	if(array == (const void *)0)
	{
		fprintf(stderr, "Error in function c_utils_generic_linear_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(target == (const void *)0)
	{
		fprintf(stderr, "Error in function c_utils_generic_linear_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(position == (const size_t *)0)
	{
		fprintf(stderr, "Error in function c_utils_generic_linear_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(element_size == 0U || element_size > C_UTILS_MAX_ELEMENT_SIZE)
	{
		fprintf(stderr, "Error in function c_utils_generic_linear_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(type == 0U)
	{
		const c_utils_char_t *const type_array = (const c_utils_char_t *)array;
		const c_utils_char_t type_target = *(const c_utils_char_t *)target;
		size_t index;

		for(index = 0U; index < count; index++)
		{
			if(type_array[index] == type_target)
			{
				*position = index;

				return C_UTILS_SUCCESS;
			}
		}
	}

	else if(type == 1U)
	{
		const c_utils_char_t *const *const type_array = (const c_utils_char_t *const *)array;
		const c_utils_char_t *const type_target = (const c_utils_char_t *)target;
		size_t index;

		for(index = 0U; index < count; index++)
		{
			if(strcmp(type_array[index], type_target) == 0)
			{
				*position = index;

				return C_UTILS_SUCCESS;
			}
		}
	}

	else if(type == 2U)
	{
		if(element_size == 1U)
		{
			const c_utils_uint8_t *const type_array = (const c_utils_uint8_t *)array;
			const c_utils_uint8_t type_target = *(const c_utils_uint8_t *)target;
			size_t index;

			for(index = 0U; index < count; index++)
			{
				if(type_array[index] == type_target)
				{
					*position = index;

					return C_UTILS_SUCCESS;
				}
			}
		}

		else if(element_size == 2U)
		{
			const c_utils_uint16_t *const type_array = (const c_utils_uint16_t *)array;
			const c_utils_uint16_t type_target = *(const c_utils_uint16_t *)target;
			size_t index;

			for(index = 0U; index < count; index++)
			{
				if(type_array[index] == type_target)
				{
					*position = index;

					return C_UTILS_SUCCESS;
				}
			}
		}

		else if(element_size == 4U)
		{
			const c_utils_uint32_t *const type_array = (const c_utils_uint32_t *)array;
			const c_utils_uint32_t type_target = *(const c_utils_uint32_t *)target;
			size_t index;

			for(index = 0U; index < count; index++)
			{
				if(type_array[index] == type_target)
				{
					*position = index;

					return C_UTILS_SUCCESS;
				}
			}
		}
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L) || \
defined(C_UTILS_ENABLE_INT64) || defined(C_UTILS_ENABLE_ALL_EXTENSIONS)

		else if(element_size == 8U)
		{
			const c_utils_uint64_t *const type_array = (const c_utils_uint64_t *)array;
			const c_utils_uint64_t type_target = *(const c_utils_uint64_t *)target;
			size_t index;

			for(index = 0U; index < count; index++)
			{
				if(type_array[index] == type_target)
				{
					*position = index;

					return C_UTILS_SUCCESS;
				}
			}
		}
#endif

		else
		{
			fprintf(stderr, "Error in function c_utils_generic_linear_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);
		}
	}

	else if(type == 3U)
	{
		if(element_size == 1U)
		{
			const c_utils_int8_t *const type_array = (const c_utils_int8_t *)array;
			const c_utils_int8_t type_target = *(const c_utils_int8_t *)target;
			size_t index;

			for(index = 0U; index < count; index++)
			{
				if(type_array[index] == type_target)
				{
					*position = index;

					return C_UTILS_SUCCESS;
				}
			}
		}

		else if(element_size == 2U)
		{
			const c_utils_int16_t *const type_array = (const c_utils_int16_t *)array;
			const c_utils_int16_t type_target = *(const c_utils_int16_t *)target;
			size_t index;

			for(index = 0U; index < count; index++)
			{
				if(type_array[index] == type_target)
				{
					*position = index;

					return C_UTILS_SUCCESS;
				}
			}
		}

		else if(element_size == 4U)
		{
			const c_utils_int32_t *const type_array = (const c_utils_int32_t *)array;
			const c_utils_int32_t type_target = *(const c_utils_int32_t *)target;
			size_t index;

			for(index = 0U; index < count; index++)
			{
				if(type_array[index] == type_target)
				{
					*position = index;

					return C_UTILS_SUCCESS;
				}
			}
		}
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L) || \
     defined(C_UTILS_ENABLE_INT64) || defined(C_UTILS_ENABLE_ALL_EXTENSIONS)

		else if(element_size == 8U)
		{
			const c_utils_int64_t *const type_array = (const c_utils_int64_t *)array;
			const c_utils_int64_t type_target = *(const c_utils_int64_t *)target;
			size_t index;

			for(index = 0U; index < count; index++)
			{
				if(type_array[index] == type_target)
				{
					*position = index;

					return C_UTILS_SUCCESS;
				}
			}
		}
#endif

		else
		{
			fprintf(stderr, "Error in function c_utils_generic_linear_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);
		}
	}

	else if(type == 4U)
	{
		if(element_size == 4U)
		{
			const c_utils_float32_t *const type_array = (const c_utils_float32_t *)array;
			const c_utils_float32_t type_target = *(const c_utils_float32_t *)target;
			size_t index;

			for(index = 0U; index < count; index++)
			{
				const c_utils_float32_t difference = type_array[index] - type_target;
				const c_utils_float32_t absolute_difference = difference < 0.0f ? -difference : difference;
				const c_utils_float32_t absolute_array = type_array[index] < 0.0f ? -type_array[index] : type_array[index];
				const c_utils_float32_t absolute_target = type_target < 0.0f ? -type_target : type_target;
				const c_utils_float32_t scale = absolute_array > absolute_target ? absolute_array : absolute_target;

				if(absolute_difference <= 10 * FLT_EPSILON * scale)
				{
					*position = index;

					return C_UTILS_SUCCESS;
				}
			}
		}

		else if(element_size == 8U)
		{
			const c_utils_float64_t *const type_array = (const c_utils_float64_t *)array;
			const c_utils_float64_t type_target = *(const c_utils_float64_t *)target;
			size_t index;

			for(index = 0U; index < count; index++)
			{
				const c_utils_float64_t difference = type_array[index] - type_target;
				const c_utils_float64_t absolute_difference = difference < 0.0 ? -difference : difference;
				const c_utils_float64_t absolute_array = type_array[index] < 0.0 ? -type_array[index] : type_array[index];
				const c_utils_float64_t absolute_target = type_target < 0.0 ? -type_target : type_target;
				const c_utils_float64_t scale = absolute_array > absolute_target ? absolute_array : absolute_target;

				if(absolute_difference <= 10 * DBL_EPSILON * scale)
				{
					*position = index;

					return C_UTILS_SUCCESS;
				}
			}
		}

		else
		{
			fprintf(stderr, "Error in function c_utils_generic_linear_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);
		}
	}

	else
	{
		fprintf(stderr, "Error in function c_utils_generic_linear_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);
	}

	return C_UTILS_FAILURE;
}

c_utils_int16_t c_utils_generic_binary_search(const void *const array, const void *const target, const size_t count, const size_t element_size, const c_utils_uint8_t type, size_t *const position)
{
	if(array == (const void *)0)
	{
		fprintf(stderr, "Error in function c_utils_generic_binary_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(target == (const void *)0)
	{
		fprintf(stderr, "Error in function c_utils_generic_binary_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(position == (const size_t *)0)
	{
		fprintf(stderr, "Error in function c_utils_generic_binary_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(element_size == 0U || element_size > C_UTILS_MAX_ELEMENT_SIZE)
	{
		fprintf(stderr, "Error in function c_utils_generic_binary_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(type == 0U)
	{
		const c_utils_char_t *const type_array = (const c_utils_char_t *)array;
		const c_utils_char_t type_target = *(const c_utils_char_t *)target;
		size_t low = 0U;
		size_t high = count;
		size_t middle;

		while(low < high)
		{
			middle = low + (high - low) / 2U;

			if(type_array[middle] == type_target)
			{
				*position = middle;

				return C_UTILS_SUCCESS;
			}

			else if(type_array[middle] < type_target)
			{
				low = middle + 1U;
			}

			else
			{
				high = middle;
			}
		}
	}

	else if(type == 1U)
	{
		const c_utils_char_t *const *const type_array = (const c_utils_char_t *const *)array;
		const c_utils_char_t *const type_target = (const c_utils_char_t *)target;
		size_t low = 0U;
		size_t high = count;
		size_t middle;

		while(low < high)
		{
			middle = low + (high - low) / 2U;
			const int cmp = strcmp(type_array[middle], type_target);

			if(cmp == 0)
			{
				*position = middle;

				return C_UTILS_SUCCESS;
			}

			else if(cmp < 0)
			{
				low = middle + 1U;
			}

			else
			{
				high = middle;
			}
		}
	}

	else if(type == 2U)
	{
		if(element_size == 1U)
		{
			const c_utils_uint8_t *const type_array = (const c_utils_uint8_t *)array;
			const c_utils_uint8_t type_target = *(const c_utils_uint8_t *)target;
			size_t low = 0U;
			size_t high = count;
			size_t middle;

			while(low < high)
			{
				middle = low + (high - low) / 2U;

				if(type_array[middle] == type_target)
				{
					*position = middle;

					return C_UTILS_SUCCESS;
				}

				else if(type_array[middle] < type_target)
				{
					low = middle + 1U;
				}

				else
				{
					high = middle;
				}
			}
		}

		else if(element_size == 2U)
		{
			const c_utils_uint16_t *const type_array = (const c_utils_uint16_t *)array;
			const c_utils_uint16_t type_target = *(const c_utils_uint16_t *)target;
			size_t low = 0U;
			size_t high = count;
			size_t middle;

			while(low < high)
			{
				middle = low + (high - low) / 2U;

				if(type_array[middle] == type_target)
				{
					*position = middle;

					return C_UTILS_SUCCESS;
				}

				else if(type_array[middle] < type_target)
				{
					low = middle + 1U;
				}

				else
				{
					high = middle;
				}
			}
		}

		else if(element_size == 4U)
		{
			const c_utils_uint32_t *const type_array = (const c_utils_uint32_t *)array;
			const c_utils_uint32_t type_target = *(const c_utils_uint32_t *)target;
			size_t low = 0U;
			size_t high = count;
			size_t middle;

			while(low < high)
			{
				middle = low + (high - low) / 2U;

				if(type_array[middle] == type_target)
				{
					*position = middle;

					return C_UTILS_SUCCESS;
				}

				else if(type_array[middle] < type_target)
				{
					low = middle + 1U;
				}

				else
				{
					high = middle;
				}
			}
		}
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L) || \
defined(C_UTILS_ENABLE_INT64) || defined(C_UTILS_ENABLE_ALL_EXTENSIONS)

		else if(element_size == 8U)
		{
			const c_utils_uint64_t *const type_array = (const c_utils_uint64_t *)array;
			const c_utils_uint64_t type_target = *(const c_utils_uint64_t *)target;
			size_t low = 0U;
			size_t high = count;
			size_t middle;

			while(low < high)
			{
				middle = low + (high - low) / 2U;

				if(type_array[middle] == type_target)
				{
					*position = middle;

					return C_UTILS_SUCCESS;
				}

				else if(type_array[middle] < type_target)
				{
					low = middle + 1U;
				}

				else
				{
					high = middle;
				}
			}
		}
#endif

		else
		{
			fprintf(stderr, "Error in function c_utils_generic_binary_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);
		}
	}

	else if(type == 3U)
	{
		if(element_size == 1U)
		{
			const c_utils_int8_t *const type_array = (const c_utils_int8_t *)array;
			const c_utils_int8_t type_target = *(const c_utils_int8_t *)target;
			size_t low = 0U;
			size_t high = count;
			size_t middle;

			while(low < high)
			{
				middle = low + (high - low) / 2U;

				if(type_array[middle] == type_target)
				{
					*position = middle;

					return C_UTILS_SUCCESS;
				}

				else if(type_array[middle] < type_target)
				{
					low = middle + 1U;
				}

				else
				{
					high = middle;
				}
			}
		}

		else if(element_size == 2U)
		{
			const c_utils_int16_t *const type_array = (const c_utils_int16_t *)array;
			const c_utils_int16_t type_target = *(const c_utils_int16_t *)target;
			size_t low = 0U;
			size_t high = count;
			size_t middle;

			while(low < high)
			{
				middle = low + (high - low) / 2U;

				if(type_array[middle] == type_target)
				{
					*position = middle;

					return C_UTILS_SUCCESS;
				}

				else if(type_array[middle] < type_target)
				{
					low = middle + 1U;
				}

				else
				{
					high = middle;
				}
			}
		}

		else if(element_size == 4U)
		{
			const c_utils_int32_t *const type_array = (const c_utils_int32_t *)array;
			const c_utils_int32_t type_target = *(const c_utils_int32_t *)target;
			size_t low = 0U;
			size_t high = count;
			size_t middle;

			while(low < high)
			{
				middle = low + (high - low) / 2U;

				if(type_array[middle] == type_target)
				{
					*position = middle;

					return C_UTILS_SUCCESS;
				}

				else if(type_array[middle] < type_target)
				{
					low = middle + 1U;
				}

				else
				{
					high = middle;
				}
			}
		}
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L) || \
     defined(C_UTILS_ENABLE_INT64) || defined(C_UTILS_ENABLE_ALL_EXTENSIONS)

		else if(element_size == 8U)
		{
			const c_utils_int64_t *const type_array = (const c_utils_int64_t *)array;
			const c_utils_int64_t type_target = *(const c_utils_int64_t *)target;
			size_t low = 0U;
			size_t high = count;
			size_t middle;

			while(low < high)
			{
				middle = low + (high - low) / 2U;

				if(type_array[middle] == type_target)
				{
					*position = middle;

					return C_UTILS_SUCCESS;
				}

				else if(type_array[middle] < type_target)
				{
					low = middle + 1U;
				}

				else
				{
					high = middle;
				}
			}
		}
#endif

		else
		{
			fprintf(stderr, "Error in function c_utils_generic_binary_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);
		}
	}

	else if(type == 4U)
	{
		if(element_size == 4U)
		{
			const c_utils_float32_t *const type_array = (const c_utils_float32_t *)array;
			const c_utils_float32_t type_target = *(const c_utils_float32_t *)target;
			c_utils_float32_t difference;
			c_utils_float32_t absolute_difference;
			c_utils_float32_t absolute_array;
			c_utils_float32_t absolute_target;
			c_utils_float32_t scale;
			size_t low = 0U;
			size_t high = count;
			size_t middle;

			while(low < high)
			{
				middle = low + (high - low) / 2U;
				difference = type_array[middle] - type_target;
				absolute_difference = difference < 0.0f ? -difference : difference;
				absolute_array = type_array[middle] < 0.0f ? -type_array[middle] : type_array[middle];
				absolute_target = type_target < 0.0f ? -type_target : type_target;
				scale = absolute_array > absolute_target ? absolute_array : absolute_target;

				if(absolute_difference <= 10 * FLT_EPSILON * scale)
				{
					*position = middle;

					return C_UTILS_SUCCESS;
				}

				else if(type_array[middle] < type_target)
				{
					low = middle + 1U;
				}

				else
				{
					high = middle;
				}
			}
		}

		else if(element_size == 8U)
		{
			const c_utils_float64_t *const type_array = (const c_utils_float64_t *)array;
			const c_utils_float64_t type_target = *(const c_utils_float64_t *)target;
			c_utils_float64_t difference;
			c_utils_float64_t absolute_difference;
			c_utils_float64_t absolute_array;
			c_utils_float64_t absolute_target;
			c_utils_float64_t scale;
			size_t low = 0U;
			size_t high = count;
			size_t middle;

			while(low < high)
			{
				middle = low + (high - low) / 2U;
				difference = type_array[middle] - type_target;
				absolute_difference = difference < 0.0 ? -difference : difference;
				absolute_array = type_array[middle] < 0.0 ? -type_array[middle] : type_array[middle];
				absolute_target = type_target < 0.0 ? -type_target : type_target;
				scale = absolute_array > absolute_target ? absolute_array : absolute_target;

				if(absolute_difference <= 10 * DBL_EPSILON * scale)
				{
					*position = middle;

					return C_UTILS_SUCCESS;
				}

				else if(type_array[middle] < type_target)
				{
					low = middle + 1U;
				}

				else
				{
					high = middle;
				}
			}
		}

		else
		{
			fprintf(stderr, "Error in function c_utils_generic_binary_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);
		}
	}

	else
	{
		fprintf(stderr, "Error in function c_utils_generic_binary_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);
	}

	return C_UTILS_FAILURE;
}

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif
