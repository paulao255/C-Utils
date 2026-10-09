/*************************/
/* Library importations: */
/*************************/

#ifndef C_UTILS_COMPILE
#include "../../include/C-Utils/big-data.h"
#include "../../include/C-Utils/err-utls.h"
#else
#include "C-Utils/big-data.h"
#include "C-Utils/err-utls.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

C_UTILS_API c_utils_result_t c_utils_generic_array_is_sorted(const c_utils_void_t *const array, const c_utils_size_t count, const c_utils_size_t element_size, const c_utils_uint8_t type)
{
	if(!array)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_array_is_sorted, the array is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(element_size == 0u || element_size > 8u)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_array_is_sorted, the element_size == 0u || element_size > 8u");

		return C_UTILS_RESULT_FAILURE;
	}

	if(type == 0u)
	{
		const c_utils_char_t *const type_array = (const c_utils_char_t *)array;
		c_utils_size_t index;

		for(index = 0u; index < count - 1u; index++)
		{
			if(type_array[index] > type_array[index + 1u])
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_generic_array_is_sorted, the array is not sorted");

				return C_UTILS_RESULT_FAILURE;
			}
		}
	}

	else if(type == 1u)
	{
		const c_utils_char_t *const *const type_array = (const c_utils_char_t *const *)array;
		c_utils_size_t index;

		for(index = 0u; index < count - 1u; index++)
		{
			if(strcmp(type_array[index], type_array[index + 1u]) > 0)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_generic_array_is_sorted, the array is not sorted");

				return C_UTILS_RESULT_FAILURE;
			}
		}
	}

	else if(type == 2u)
	{
		if(element_size == 1u)
		{
			const c_utils_uint8_t *const type_array = (const c_utils_uint8_t *)array;
			c_utils_size_t index;

			for(index = 0u; index < count - 1u; index++)
			{
				if(type_array[index] > type_array[index + 1u])
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_generic_array_is_sorted, the array is not sorted");

					return C_UTILS_RESULT_FAILURE;
				}
			}
		}

		else if(element_size == 2u)
		{
			const c_utils_uint16_t *const type_array = (const c_utils_uint16_t *)array;
			c_utils_size_t index;

			for(index = 0u; index < count - 1u; index++)
			{
				if(type_array[index] > type_array[index + 1u])
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_generic_array_is_sorted, the array is not sorted");

					return C_UTILS_RESULT_FAILURE;
				}
			}
		}

		else if(element_size == 4u)
		{
			const c_utils_uint32_t *const type_array = (const c_utils_uint32_t *)array;
			c_utils_size_t index;

			for(index = 0u; index < count - 1u; index++)
			{
				if(type_array[index] > type_array[index + 1u])
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_generic_array_is_sorted, the array is not sorted");

					return C_UTILS_RESULT_FAILURE;
				}
			}
		}
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L) || \
defined(C_UTILS_ENABLE_INT64) || defined(C_UTILS_ENABLE_ALL_EXTENSIONS)

		else if(element_size == 8u)
		{
			const c_utils_uint64_t *const type_array = (const c_utils_uint64_t *)array;
			c_utils_size_t index;

			for(index = 0u; index < count - 1u; index++)
			{
				if(type_array[index] > type_array[index + 1u])
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_generic_array_is_sorted, the array is not sorted");

					return C_UTILS_RESULT_FAILURE;
				}
			}
		}
#endif

		else
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_generic_array_is_sorted, the element_size is not supported");

			return C_UTILS_RESULT_FAILURE;
		}
	}

	else if(type == 3u)
	{
		if(element_size == 1u)
		{
			const c_utils_int8_t *const type_array = (const c_utils_int8_t *)array;
			c_utils_size_t index;

			for(index = 0u; index < count - 1u; index++)
			{
				if(type_array[index] > type_array[index + 1u])
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_generic_array_is_sorted, the array is not sorted");

					return C_UTILS_RESULT_FAILURE;
				}
			}
		}

		else if(element_size == 2u)
		{
			const c_utils_int16_t *const type_array = (const c_utils_int16_t *)array;
			c_utils_size_t index;

			for(index = 0u; index < count - 1u; index++)
			{
				if(type_array[index] > type_array[index + 1u])
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_generic_array_is_sorted, the array is not sorted");

					return C_UTILS_RESULT_FAILURE;
				}
			}
		}

		else if(element_size == 4u)
		{
			const c_utils_int32_t *const type_array = (const c_utils_int32_t *)array;
			c_utils_size_t index;

			for(index = 0u; index < count - 1u; index++)
			{
				if(type_array[index] > type_array[index + 1u])
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_generic_array_is_sorted, the array is not sorted");

					return C_UTILS_RESULT_FAILURE;
				}
			}
		}
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L) || \
defined(C_UTILS_ENABLE_INT64) || defined(C_UTILS_ENABLE_ALL_EXTENSIONS)

		else if(element_size == 8u)
		{
			const c_utils_int64_t *const type_array = (const c_utils_int64_t *)array;
			c_utils_size_t index;

			for(index = 0u; index < count - 1u; index++)
			{
				if(type_array[index] > type_array[index + 1u])
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_generic_array_is_sorted, the array is not sorted");

					return C_UTILS_RESULT_FAILURE;
				}
			}
		}
#endif

		else
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_generic_array_is_sorted, the element_size is not supported");

			return C_UTILS_RESULT_FAILURE;
		}

	}

	else if(type == 4u)
	{
		if(element_size == 4u)
		{
			const c_utils_float32_t *const type_array = (const c_utils_float32_t *)array;
			c_utils_size_t index;

			for(index = 0u; index < count - 1u; index++)
			{
				if(type_array[index] > type_array[index + 1u])
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_generic_array_is_sorted, the array is not sorted");

					return C_UTILS_RESULT_FAILURE;
				}
			}
		}

		else if(element_size == 8u)
		{
			const c_utils_float64_t *const type_array = (const c_utils_float64_t *)array;
			c_utils_size_t index;

			for(index = 0u; index < count - 1u; index++)
			{
				if(type_array[index] > type_array[index + 1u])
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_generic_array_is_sorted, the array is not sorted");

					return C_UTILS_RESULT_FAILURE;
				}
			}
		}

		else
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_generic_array_is_sorted, the element_size is not supported");

			return C_UTILS_RESULT_FAILURE;
		}
	}

	else
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_array_is_sorted, the type is not supported");

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_generic_insertion_sort(const c_utils_void_t *const array, const c_utils_size_t count, const c_utils_size_t element_size, const c_utils_uint8_t type)
{
	if(!array)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_insertion_sort, the array is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(element_size == 0u || element_size > 8u)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_insertion_sort, the element_size == 0u || element_size > 8u");

		return C_UTILS_RESULT_FAILURE;
	}

	if(type == 0u)
	{
		c_utils_char_t *const type_array = (c_utils_char_t *)array;
		c_utils_size_t index;

		for(index = 1u; index < count; index++)
		{
			c_utils_char_t key = type_array[index];
			c_utils_size_t j = index;

			while(j > 0u && type_array[j - 1u] > key)
			{
				type_array[j] = type_array[j - 1u];
				j--;
			}

			type_array[j] = key;
		}
	}

	else if(type == 1u)
	{
		c_utils_char_t **const type_array = (c_utils_char_t **)array;
		c_utils_size_t index;

		for(index = 1u; index < count; index++)
		{
			c_utils_char_t *const key = type_array[index];
			c_utils_size_t j = index;

			while(j > 0 && strcmp(type_array[j - 1u], key) > 0)
			{
				type_array[j] = type_array[j - 1u];
				j--;
			}

			type_array[j] = key;
		}
	}

	else if(type == 2u)
	{
		if(element_size == 1u)
		{
			c_utils_uint8_t *const type_array = (c_utils_uint8_t *)array;
			c_utils_size_t index;

			for(index = 1u; index < count; index++)
			{
				c_utils_uint8_t key = type_array[index];
				c_utils_size_t j = index;

				while(j > 0u && type_array[j - 1u] > key)
				{
					type_array[j] = type_array[j - 1u];
					j--;
				}

				type_array[j] = key;
			}
		}

		else if(element_size == 2u)
		{
			c_utils_uint16_t *const type_array = (c_utils_uint16_t *)array;
			c_utils_size_t index;

			for(index = 1u; index < count; index++)
			{
				c_utils_uint16_t key = type_array[index];
				c_utils_size_t j = index;

				while(j > 0u && type_array[j - 1u] > key)
				{
					type_array[j] = type_array[j - 1u];
					j--;
				}

				type_array[j] = key;
			}
		}

		else if(element_size == 4u)
		{
			c_utils_uint32_t *const type_array = (c_utils_uint32_t *)array;
			c_utils_size_t index;

			for(index = 1u; index < count; index++)
			{
				c_utils_uint32_t key = type_array[index];
				c_utils_size_t j = index;

				while(j > 0u && type_array[j - 1u] > key)
				{
					type_array[j] = type_array[j - 1u];
					j--;
				}

				type_array[j] = key;
			}
		}
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L) || \
     defined(C_UTILS_ENABLE_INT64) || defined(C_UTILS_ENABLE_ALL_EXTENSIONS)

		else if(element_size == 8u)
		{
			c_utils_uint64_t *const type_array = (c_utils_uint64_t *)array;
			c_utils_size_t index;

			for(index = 1u; index < count; index++)
			{
				c_utils_uint64_t key = type_array[index];
				c_utils_size_t j = index;

				while(j > 0u && type_array[j - 1u] > key)
				{
					type_array[j] = type_array[j - 1u];
					j--;
				}

				type_array[j] = key;
			}
		}
#endif

		else
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_generic_insertion_sort, the element_size is not supported");

			return C_UTILS_RESULT_FAILURE;
		}
	}

	else if(type == 3u)
	{
		if(element_size == 1u)
		{
			c_utils_int8_t *const type_array = (c_utils_int8_t *)array;
			c_utils_size_t index;

			for(index = 1u; index < count; index++)
			{
				c_utils_int8_t key = type_array[index];
				c_utils_size_t j = index;

				while(j > 0u && type_array[j - 1u] > key)
				{
					type_array[j] = type_array[j - 1u];
					j--;
				}

				type_array[j] = key;
			}
		}

		else if(element_size == 2u)
		{
			c_utils_int16_t *const type_array = (c_utils_int16_t *)array;
			c_utils_size_t index;

			for(index = 1u; index < count; index++)
			{
				c_utils_int16_t key = type_array[index];
				c_utils_size_t j = index;

				while(j > 0u && type_array[j - 1u] > key)
				{
					type_array[j] = type_array[j - 1u];
					j--;
				}

				type_array[j] = key;
			}
		}

		else if(element_size == 4u)
		{
			c_utils_int32_t *const type_array = (c_utils_int32_t *)array;
			c_utils_size_t index;

			for(index = 1u; index < count; index++)
			{
				c_utils_int32_t key = type_array[index];
				c_utils_size_t j = index;

				while(j > 0u && type_array[j - 1u] > key)
				{
					type_array[j] = type_array[j - 1u];
					j--;
				}

				type_array[j] = key;
			}
		}
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L) || \
     defined(C_UTILS_ENABLE_INT64) || defined(C_UTILS_ENABLE_ALL_EXTENSIONS)

		else if(element_size == 8u)
		{
			c_utils_int64_t *const type_array = (c_utils_int64_t *)array;
			c_utils_size_t index;

			for(index = 1u; index < count; index++)
			{
				c_utils_int64_t key = type_array[index];
				c_utils_size_t j = index;

				while(j > 0u && type_array[j - 1u] > key)
				{
					type_array[j] = type_array[j - 1u];
					j--;
				}

				type_array[j] = key;
			}
		}
#endif

		else
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_generic_insertion_sort, the element_size is not supported");

			return C_UTILS_RESULT_FAILURE;
		}
	}

	else if(type == 4u)
	{
		if(element_size == 4u)
		{
			c_utils_float32_t *const type_array = (c_utils_float32_t *)array;
			c_utils_size_t index;

			for(index = 1u; index < count; index++)
			{
				c_utils_float32_t key = type_array[index];
				c_utils_size_t j = index;

				while(j > 0u && type_array[j - 1u] > key)
				{
					type_array[j] = type_array[j - 1u];
					j--;
				}

				type_array[j] = key;
			}
		}

		else if(element_size == 8u)
		{
			c_utils_float64_t *const type_array = (c_utils_float64_t *)array;
			c_utils_size_t index;

			for(index = 1u; index < count; index++)
			{
				c_utils_float64_t key = type_array[index];
				c_utils_size_t j = index;

				while(j > 0u && type_array[j - 1u] > key)
				{
					type_array[j] = type_array[j - 1u];
					j--;
				}

				type_array[j] = key;
			}
		}

		else
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_generic_insertion_sort, the element_size is not supported");

			return C_UTILS_RESULT_FAILURE;
		}
	}

	else
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_insertion_sort, the type is not supported");

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_generic_merge_sort(const c_utils_void_t *const array, const c_utils_size_t count, const c_utils_size_t element_size, const c_utils_uint8_t type)
{
	if(!array)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_merge_sort, the array is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(element_size == 0u || element_size > 8u)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_merge_sort, the element_size == 0u || element_size > 8u");

		return C_UTILS_RESULT_FAILURE;
	}

	if(count > 1u)
	{
		if(type == 0u)
		{
			c_utils_char_t *const type_array = (c_utils_char_t *)array;
			c_utils_char_t *const temporary_array = (c_utils_char_t *)malloc(count * sizeof(*temporary_array));

			if(!temporary_array)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_generic_merge_sort, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			else
			{
				c_utils_size_t width;

				for(width = 1u; width < count; width *= 2u)
				{
					c_utils_size_t left;

					for(left = 0u; left < count; left += 2u * width)
					{
						c_utils_size_t middle = (left + width < count) ? (left + width) : count;
						c_utils_size_t right = (left + 2u * width < count) ? (left + 2u * width) : count;
						c_utils_size_t left_index = left;
						c_utils_size_t right_index = middle;
						c_utils_size_t merge_index = left;

						while(left_index < middle && right_index < right)
						{
							if(type_array[left_index] <= type_array[right_index])
							{
								temporary_array[merge_index++] = type_array[left_index++];
							}

							else
							{
								temporary_array[merge_index++] = type_array[right_index++];
							}
						}

						while(left_index < middle)
						{
							temporary_array[merge_index++] = type_array[left_index++];
						}

						while(right_index < right)
						{
							temporary_array[merge_index++] = type_array[right_index++];
						}

						memcpy(type_array + left, temporary_array + left, (right - left) * sizeof(c_utils_char_t));
					}
				}

				free((c_utils_void_t *)temporary_array);
			}
		}

		else if(type == 1u)
		{
			c_utils_char_t **const type_array = (c_utils_char_t **)array;
			c_utils_char_t **const temporary_array = (c_utils_char_t **)malloc(count * sizeof(*temporary_array));

			if(!temporary_array)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_generic_merge_sort, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			else
			{
				c_utils_size_t width;

				for(width = 1u; width < count; width *= 2u)
				{
					c_utils_size_t left;

					for(left = 0u; left < count; left += 2u * width)
					{
						c_utils_size_t middle = (left + width < count) ? (left + width) : count;
						c_utils_size_t right = (left + 2u * width < count) ? (left + 2u * width) : count;
						c_utils_size_t left_index = left;
						c_utils_size_t right_index = middle;
						c_utils_size_t merge_index = left;

						while(left_index < middle && right_index < right)
						{
							if(strcmp(type_array[left_index], type_array[right_index]) <= 0)
							{
								temporary_array[merge_index++] = type_array[left_index++];
							}

							else
							{
								temporary_array[merge_index++] = type_array[right_index++];
							}
						}

						while(left_index < middle)
						{
							temporary_array[merge_index++] = type_array[left_index++];
						}

						while(right_index < right)
						{
							temporary_array[merge_index++] = type_array[right_index++];
						}

						memcpy(type_array + left, temporary_array + left, (right - left) * sizeof(c_utils_char_t *));
					}
				}

				free((c_utils_void_t *)temporary_array);
			}
		}

		else if(type == 2u)
		{
			if(element_size == 1u)
			{
				c_utils_uint8_t *const type_array = (c_utils_uint8_t *)array;
				c_utils_uint8_t *const temporary_array = (c_utils_uint8_t *)malloc(count * sizeof(*temporary_array));

				if(!temporary_array)
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_generic_merge_sort, function malloc failed");

					return C_UTILS_RESULT_FAILURE;
				}

				else
				{
					c_utils_size_t width;

					for(width = 1u; width < count; width *= 2u)
					{
						c_utils_size_t left;

						for(left = 0u; left < count; left += 2u * width)
						{
							c_utils_size_t middle = (left + width < count) ? (left + width) : count;
							c_utils_size_t right = (left + 2u * width < count) ? (left + 2u * width) : count;
							c_utils_size_t left_index = left;
							c_utils_size_t right_index = middle;
							c_utils_size_t merge_index = left;

							while(left_index < middle && right_index < right)
							{
								if(type_array[left_index] <= type_array[right_index])
								{
									temporary_array[merge_index++] = type_array[left_index++];
								}

								else
								{
									temporary_array[merge_index++] = type_array[right_index++];
								}
							}

							while(left_index < middle)
							{
								temporary_array[merge_index++] = type_array[left_index++];
							}

							while(right_index < right)
							{
								temporary_array[merge_index++] = type_array[right_index++];
							}

							memcpy(type_array + left, temporary_array + left, (right - left) * sizeof(c_utils_uint8_t));
						}
					}

					free((c_utils_void_t *)temporary_array);
				}
			}

			else if(element_size == 2u)
			{
				c_utils_uint16_t *const type_array = (c_utils_uint16_t *)array;
				c_utils_uint16_t *const temporary_array = (c_utils_uint16_t *)malloc(count * sizeof(*temporary_array));

				if(!temporary_array)
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_generic_merge_sort, function malloc failed");

					return C_UTILS_RESULT_FAILURE;
				}

				else
				{
					c_utils_size_t width;

					for(width = 1u; width < count; width *= 2u)
					{
						c_utils_size_t left;

						for(left = 0u; left < count; left += 2u * width)
						{
							c_utils_size_t middle = (left + width < count) ? (left + width) : count;
							c_utils_size_t right = (left + 2u * width < count) ? (left + 2u * width) : count;
							c_utils_size_t left_index = left;
							c_utils_size_t right_index = middle;
							c_utils_size_t merge_index = left;

							while(left_index < middle && right_index < right)
							{
								if(type_array[left_index] <= type_array[right_index])
								{
									temporary_array[merge_index++] = type_array[left_index++];
								}

								else
								{
									temporary_array[merge_index++] = type_array[right_index++];
								}
							}

							while(left_index < middle)
							{
								temporary_array[merge_index++] = type_array[left_index++];
							}

							while(right_index < right)
							{
								temporary_array[merge_index++] = type_array[right_index++];
							}

							memcpy(type_array + left, temporary_array + left, (right - left) * sizeof(c_utils_uint16_t));
						}
					}

					free((c_utils_void_t *)temporary_array);
				}
			}

			else if(element_size == 4u)
			{
				c_utils_uint32_t *const type_array = (c_utils_uint32_t *)array;
				c_utils_uint32_t *const temporary_array = (c_utils_uint32_t *)malloc(count * sizeof(*temporary_array));

				if(!temporary_array)
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_generic_merge_sort, function malloc failed");

					return C_UTILS_RESULT_FAILURE;
				}

				else
				{
					c_utils_size_t width;

					for(width = 1u; width < count; width *= 2u)
					{
						c_utils_size_t left;

						for(left = 0u; left < count; left += 2u * width)
						{
							c_utils_size_t middle = (left + width < count) ? (left + width) : count;
							c_utils_size_t right = (left + 2u * width < count) ? (left + 2u * width) : count;
							c_utils_size_t left_index = left;
							c_utils_size_t right_index = middle;
							c_utils_size_t merge_index = left;

							while(left_index < middle && right_index < right)
							{
								if(type_array[left_index] <= type_array[right_index])
								{
									temporary_array[merge_index++] = type_array[left_index++];
								}

								else
								{
									temporary_array[merge_index++] = type_array[right_index++];
								}
							}

							while(left_index < middle)
							{
								temporary_array[merge_index++] = type_array[left_index++];
							}

							while(right_index < right)
							{
								temporary_array[merge_index++] = type_array[right_index++];
							}

							memcpy(type_array + left, temporary_array + left, (right - left) * sizeof(c_utils_uint32_t));
						}
					}

					free((c_utils_void_t *)temporary_array);
				}
			}
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L) || \
     defined(C_UTILS_ENABLE_INT64) || defined(C_UTILS_ENABLE_ALL_EXTENSIONS)

			else if(element_size == 8u)
			{
				c_utils_uint64_t *const type_array = (c_utils_uint64_t *)array;
				c_utils_uint64_t *const temporary_array = (c_utils_uint64_t *)malloc(count * sizeof(*temporary_array));

				if(!temporary_array)
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_generic_merge_sort, function malloc failed");

					return C_UTILS_RESULT_FAILURE;
				}

				else
				{
					c_utils_size_t width;

					for(width = 1u; width < count; width *= 2u)
					{
						c_utils_size_t left;

						for(left = 0u; left < count; left += 2u * width)
						{
							c_utils_size_t middle = (left + width < count) ? (left + width) : count;
							c_utils_size_t right = (left + 2u * width < count) ? (left + 2u * width) : count;
							c_utils_size_t left_index = left;
							c_utils_size_t right_index = middle;
							c_utils_size_t merge_index = left;

							while(left_index < middle && right_index < right)
							{
								if(type_array[left_index] <= type_array[right_index])
								{
									temporary_array[merge_index++] = type_array[left_index++];
								}

								else
								{
									temporary_array[merge_index++] = type_array[right_index++];
								}
							}

							while(left_index < middle)
							{
								temporary_array[merge_index++] = type_array[left_index++];
							}

							while(right_index < right)
							{
								temporary_array[merge_index++] = type_array[right_index++];
							}

							memcpy(type_array + left, temporary_array + left, (right - left) * sizeof(c_utils_uint64_t));
						}
					}

					free((c_utils_void_t *)temporary_array);
				}
			}
#endif

			else
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_generic_merge_sort, the element_size is not supported");

				return C_UTILS_RESULT_FAILURE;
			}
		}

		else if(type == 3u)
		{
			if(element_size == 1u)
			{
				c_utils_int8_t *const type_array = (c_utils_int8_t *)array;
				c_utils_int8_t *const temporary_array = (c_utils_int8_t *)malloc(count * sizeof(*temporary_array));

				if(!temporary_array)
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_generic_merge_sort, function malloc failed");

					return C_UTILS_RESULT_FAILURE;
				}

				else
				{
					c_utils_size_t width;

					for(width = 1u; width < count; width *= 2u)
					{
						c_utils_size_t left;

						for(left = 0u; left < count; left += 2u * width)
						{
							c_utils_size_t middle = (left + width < count) ? (left + width) : count;
							c_utils_size_t right = (left + 2u * width < count) ? (left + 2u * width) : count;
							c_utils_size_t left_index = left;
							c_utils_size_t right_index = middle;
							c_utils_size_t merge_index = left;

							while(left_index < middle && right_index < right)
							{
								if(type_array[left_index] <= type_array[right_index])
								{
									temporary_array[merge_index++] = type_array[left_index++];
								}

								else
								{
									temporary_array[merge_index++] = type_array[right_index++];
								}
							}

							while(left_index < middle)
							{
								temporary_array[merge_index++] = type_array[left_index++];
							}

							while(right_index < right)
							{
								temporary_array[merge_index++] = type_array[right_index++];
							}

							memcpy(type_array + left, temporary_array + left, (right - left) * sizeof(c_utils_int8_t));
						}
					}

					free((c_utils_void_t *)temporary_array);
				}
			}

			else if(element_size == 2u)
			{
				c_utils_int16_t *const type_array = (c_utils_int16_t *)array;
				c_utils_int16_t *const temporary_array = (c_utils_int16_t *)malloc(count * sizeof(*temporary_array));

				if(!temporary_array)
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_generic_merge_sort, function malloc failed");

					return C_UTILS_RESULT_FAILURE;
				}

				else
				{
					c_utils_size_t width;

					for(width = 1u; width < count; width *= 2u)
					{
						c_utils_size_t left;

						for(left = 0u; left < count; left += 2u * width)
						{
							c_utils_size_t middle = (left + width < count) ? (left + width) : count;
							c_utils_size_t right = (left + 2u * width < count) ? (left + 2u * width) : count;
							c_utils_size_t left_index = left;
							c_utils_size_t right_index = middle;
							c_utils_size_t merge_index = left;

							while(left_index < middle && right_index < right)
							{
								if(type_array[left_index] <= type_array[right_index])
								{
									temporary_array[merge_index++] = type_array[left_index++];
								}

								else
								{
									temporary_array[merge_index++] = type_array[right_index++];
								}
							}

							while(left_index < middle)
							{
								temporary_array[merge_index++] = type_array[left_index++];
							}

							while(right_index < right)
							{
								temporary_array[merge_index++] = type_array[right_index++];
							}

							memcpy(type_array + left, temporary_array + left, (right - left) * sizeof(c_utils_int16_t));
						}
					}

					free((c_utils_void_t *)temporary_array);
				}
			}

			else if(element_size == 4u)
			{
				c_utils_int32_t *const type_array = (c_utils_int32_t *)array;
				c_utils_int32_t *const temporary_array = (c_utils_int32_t *)malloc(count * sizeof(*temporary_array));

				if(!temporary_array)
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_generic_merge_sort, function malloc failed");

					return C_UTILS_RESULT_FAILURE;
				}

				else
				{
					c_utils_size_t width;

					for(width = 1u; width < count; width *= 2u)
					{
						c_utils_size_t left;

						for(left = 0u; left < count; left += 2u * width)
						{
							c_utils_size_t middle = (left + width < count) ? (left + width) : count;
							c_utils_size_t right = (left + 2u * width < count) ? (left + 2u * width) : count;
							c_utils_size_t left_index = left;
							c_utils_size_t right_index = middle;
							c_utils_size_t merge_index = left;

							while(left_index < middle && right_index < right)
							{
								if(type_array[left_index] <= type_array[right_index])
								{
									temporary_array[merge_index++] = type_array[left_index++];
								}

								else
								{
									temporary_array[merge_index++] = type_array[right_index++];
								}
							}

							while(left_index < middle)
							{
								temporary_array[merge_index++] = type_array[left_index++];
							}

							while(right_index < right)
							{
								temporary_array[merge_index++] = type_array[right_index++];
							}

							memcpy(type_array + left, temporary_array + left, (right - left) * sizeof(c_utils_int32_t));
						}
					}

					free((c_utils_void_t *)temporary_array);
				}
			}
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L) || \
     defined(C_UTILS_ENABLE_INT64) || defined(C_UTILS_ENABLE_ALL_EXTENSIONS)

			else if(element_size == 8u)
			{
				c_utils_int64_t *const type_array = (c_utils_int64_t *)array;
				c_utils_int64_t *const temporary_array = (c_utils_int64_t *)malloc(count * sizeof(*temporary_array));

				if(!temporary_array)
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_generic_merge_sort, function malloc failed");

					return C_UTILS_RESULT_FAILURE;
				}

				else
				{
					c_utils_size_t width;

					for(width = 1u; width < count; width *= 2u)
					{
						c_utils_size_t left;

						for(left = 0u; left < count; left += 2u * width)
						{
							c_utils_size_t middle = (left + width < count) ? (left + width) : count;
							c_utils_size_t right = (left + 2u * width < count) ? (left + 2u * width) : count;
							c_utils_size_t left_index = left;
							c_utils_size_t right_index = middle;
							c_utils_size_t merge_index = left;

							while(left_index < middle && right_index < right)
							{
								if(type_array[left_index] <= type_array[right_index])
								{
									temporary_array[merge_index++] = type_array[left_index++];
								}

								else
								{
									temporary_array[merge_index++] = type_array[right_index++];
								}
							}

							while(left_index < middle)
							{
								temporary_array[merge_index++] = type_array[left_index++];
							}

							while(right_index < right)
							{
								temporary_array[merge_index++] = type_array[right_index++];
							}

							memcpy(type_array + left, temporary_array + left, (right - left) * sizeof(c_utils_int64_t));
						}
					}

					free((c_utils_void_t *)temporary_array);
				}
			}
#endif

			else
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_generic_merge_sort, the element_size is not supported");

				return C_UTILS_RESULT_FAILURE;
			}
		}

		else if(type == 4u)
		{
			if(element_size == 4u)
			{
				c_utils_float32_t *const type_array = (c_utils_float32_t *)array;
				c_utils_float32_t *const temporary_array = (c_utils_float32_t *)malloc(count * sizeof(*temporary_array));

				if(!temporary_array)
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_generic_merge_sort, function malloc failed");

					return C_UTILS_RESULT_FAILURE;
				}

				else
				{
					c_utils_size_t width;

					for(width = 1u; width < count; width *= 2u)
					{
						c_utils_size_t left;

						for(left = 0u; left < count; left += 2u * width)
						{
							c_utils_size_t middle = (left + width < count) ? (left + width) : count;
							c_utils_size_t right = (left + 2u * width < count) ? (left + 2u * width) : count;
							c_utils_size_t left_index = left;
							c_utils_size_t right_index = middle;
							c_utils_size_t merge_index = left;

							while(left_index < middle && right_index < right)
							{
								if(type_array[left_index] <= type_array[right_index])
								{
									temporary_array[merge_index++] = type_array[left_index++];
								}

								else
								{
									temporary_array[merge_index++] = type_array[right_index++];
								}
							}

							while(left_index < middle)
							{
								temporary_array[merge_index++] = type_array[left_index++];
							}

							while(right_index < right)
							{
								temporary_array[merge_index++] = type_array[right_index++];
							}

							memcpy(type_array + left, temporary_array + left, (right - left) * sizeof(c_utils_float32_t));
						}
					}

					free((c_utils_void_t *)temporary_array);
				}
			}

			else if(element_size == 8u)
			{
				c_utils_float64_t *const type_array = (c_utils_float64_t *)array;
				c_utils_float64_t *const temporary_array = (c_utils_float64_t *)malloc(count * sizeof(*temporary_array));

				if(!temporary_array)
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_generic_merge_sort, function malloc failed");

					return C_UTILS_RESULT_FAILURE;
				}

				else
				{
					c_utils_size_t width;

					for(width = 1u; width < count; width *= 2u)
					{
						c_utils_size_t left;

						for(left = 0u; left < count; left += 2u * width)
						{
							c_utils_size_t middle = (left + width < count) ? (left + width) : count;
							c_utils_size_t right = (left + 2u * width < count) ? (left + 2u * width) : count;
							c_utils_size_t left_index = left;
							c_utils_size_t right_index = middle;
							c_utils_size_t merge_index = left;

							while(left_index < middle && right_index < right)
							{
								if(type_array[left_index] <= type_array[right_index])
								{
									temporary_array[merge_index++] = type_array[left_index++];
								}

								else
								{
									temporary_array[merge_index++] = type_array[right_index++];
								}
							}

							while(left_index < middle)
							{
								temporary_array[merge_index++] = type_array[left_index++];
							}

							while(right_index < right)
							{
								temporary_array[merge_index++] = type_array[right_index++];
							}

							memcpy(type_array + left, temporary_array + left, (right - left) * sizeof(c_utils_float64_t));
						}
					}

					free((c_utils_void_t *)temporary_array);
				}
			}

			else
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_generic_merge_sort, the element_size is not supported");

				return C_UTILS_RESULT_FAILURE;
			}
		}

		else
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_generic_merge_sort, the type is not supported");

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_generic_linear_search(const c_utils_void_t *const array, const c_utils_void_t *const target, const c_utils_size_t count, const c_utils_size_t element_size, const c_utils_uint8_t type, c_utils_size_t *const position)
{
	if(!array)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_linear_search, the array is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!target)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_linear_search, the target is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!position)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_linear_search, the position is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(element_size == 0u || element_size > 8u)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_linear_search, the element_size == 0u || element_size > 8u");

		return C_UTILS_RESULT_FAILURE;
	}

	if(type == 0u)
	{
		const c_utils_char_t *const type_array = (const c_utils_char_t *)array;
		const c_utils_char_t type_target = *(const c_utils_char_t *)target;
		c_utils_size_t index;

		for(index = 0u; index < count; index++)
		{
			if(type_array[index] == type_target)
			{
				*position = index;
			}
		}
	}

	else if(type == 1u)
	{
		const c_utils_char_t *const *const type_array = (const c_utils_char_t *const *)array;
		const c_utils_char_t *const type_target = (const c_utils_char_t *)target;
		c_utils_size_t index;

		for(index = 0u; index < count; index++)
		{
			if(strcmp(type_array[index], type_target) == 0)
			{
				*position = index;
			}
		}
	}

	else if(type == 2u)
	{
		if(element_size == 1u)
		{
			const c_utils_uint8_t *const type_array = (const c_utils_uint8_t *)array;
			const c_utils_uint8_t type_target = *(const c_utils_uint8_t *)target;
			c_utils_size_t index;

			for(index = 0u; index < count; index++)
			{
				if(type_array[index] == type_target)
				{
					*position = index;
				}
			}
		}

		else if(element_size == 2u)
		{
			const c_utils_uint16_t *const type_array = (const c_utils_uint16_t *)array;
			const c_utils_uint16_t type_target = *(const c_utils_uint16_t *)target;
			c_utils_size_t index;

			for(index = 0u; index < count; index++)
			{
				if(type_array[index] == type_target)
				{
					*position = index;
				}
			}
		}

		else if(element_size == 4u)
		{
			const c_utils_uint32_t *const type_array = (const c_utils_uint32_t *)array;
			const c_utils_uint32_t type_target = *(const c_utils_uint32_t *)target;
			c_utils_size_t index;

			for(index = 0u; index < count; index++)
			{
				if(type_array[index] == type_target)
				{
					*position = index;
				}
			}
		}
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L) || \
defined(C_UTILS_ENABLE_INT64) || defined(C_UTILS_ENABLE_ALL_EXTENSIONS)

		else if(element_size == 8u)
		{
			const c_utils_uint64_t *const type_array = (const c_utils_uint64_t *)array;
			const c_utils_uint64_t type_target = *(const c_utils_uint64_t *)target;
			c_utils_size_t index;

			for(index = 0u; index < count; index++)
			{
				if(type_array[index] == type_target)
				{
					*position = index;
				}
			}
		}
#endif

		else
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_generic_linear_search, the element_size is not supported");

			return C_UTILS_RESULT_FAILURE;
		}
	}

	else if(type == 3u)
	{
		if(element_size == 1u)
		{
			const c_utils_int8_t *const type_array = (const c_utils_int8_t *)array;
			const c_utils_int8_t type_target = *(const c_utils_int8_t *)target;
			c_utils_size_t index;

			for(index = 0u; index < count; index++)
			{
				if(type_array[index] == type_target)
				{
					*position = index;
				}
			}
		}

		else if(element_size == 2u)
		{
			const c_utils_int16_t *const type_array = (const c_utils_int16_t *)array;
			const c_utils_int16_t type_target = *(const c_utils_int16_t *)target;
			c_utils_size_t index;

			for(index = 0u; index < count; index++)
			{
				if(type_array[index] == type_target)
				{
					*position = index;
				}
			}
		}

		else if(element_size == 4u)
		{
			const c_utils_int32_t *const type_array = (const c_utils_int32_t *)array;
			const c_utils_int32_t type_target = *(const c_utils_int32_t *)target;
			c_utils_size_t index;

			for(index = 0u; index < count; index++)
			{
				if(type_array[index] == type_target)
				{
					*position = index;
				}
			}
		}
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L) || \
     defined(C_UTILS_ENABLE_INT64) || defined(C_UTILS_ENABLE_ALL_EXTENSIONS)

		else if(element_size == 8u)
		{
			const c_utils_int64_t *const type_array = (const c_utils_int64_t *)array;
			const c_utils_int64_t type_target = *(const c_utils_int64_t *)target;
			c_utils_size_t index;

			for(index = 0u; index < count; index++)
			{
				if(type_array[index] == type_target)
				{
					*position = index;
				}
			}
		}
#endif

		else
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_generic_linear_search, the element_size is not supported");

			return C_UTILS_RESULT_FAILURE;
		}
	}

	else if(type == 4u)
	{
		if(element_size == 4u)
		{
			const c_utils_float32_t *const type_array = (const c_utils_float32_t *)array;
			const c_utils_float32_t type_target = *(const c_utils_float32_t *)target;
			c_utils_size_t index;

			for(index = 0u; index < count; index++)
			{
				const c_utils_float32_t difference = type_array[index] - type_target;
				const c_utils_float32_t absolute_difference = difference < 0.0f ? -difference : difference;
				const c_utils_float32_t absolute_array = type_array[index] < 0.0f ? -type_array[index] : type_array[index];
				const c_utils_float32_t absolute_target = type_target < 0.0f ? -type_target : type_target;
				const c_utils_float32_t scale = absolute_array > absolute_target ? absolute_array : absolute_target;

				if(absolute_difference <= 10 * C_UTILS_FLOAT32_EPSILON * scale)
				{
					*position = index;
				}
			}
		}

		else if(element_size == 8u)
		{
			const c_utils_float64_t *const type_array = (const c_utils_float64_t *)array;
			const c_utils_float64_t type_target = *(const c_utils_float64_t *)target;
			c_utils_size_t index;

			for(index = 0u; index < count; index++)
			{
				const c_utils_float64_t difference = type_array[index] - type_target;
				const c_utils_float64_t absolute_difference = difference < 0.0 ? -difference : difference;
				const c_utils_float64_t absolute_array = type_array[index] < 0.0 ? -type_array[index] : type_array[index];
				const c_utils_float64_t absolute_target = type_target < 0.0 ? -type_target : type_target;
				const c_utils_float64_t scale = absolute_array > absolute_target ? absolute_array : absolute_target;

				if(absolute_difference <= 10 * C_UTILS_FLOAT64_EPSILON * scale)
				{
					*position = index;
				}
			}
		}

		else
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_generic_linear_search, the element_size is not supported");

			return C_UTILS_RESULT_FAILURE;
		}
	}

	else
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_linear_search, the type is not supported");

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_generic_binary_search(const c_utils_void_t *const array, const c_utils_void_t *const target, const c_utils_size_t count, const c_utils_size_t element_size, const c_utils_uint8_t type, c_utils_size_t *const position)
{
	if(!array)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_binary_search, the array is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!target)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_binary_search, the target is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!position)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_binary_search, the position is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(element_size == 0u || element_size > 8u)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_binary_search, the element_size == 0u || element_size > 8u");

		return C_UTILS_RESULT_FAILURE;
	}

	if(type == 0u)
	{
		const c_utils_char_t *const type_array = (const c_utils_char_t *)array;
		const c_utils_char_t type_target = *(const c_utils_char_t *)target;
		c_utils_size_t low = 0u;
		c_utils_size_t high = count;
		c_utils_size_t middle;

		while(low < high)
		{
			middle = low + (high - low) / 2u;

			if(type_array[middle] == type_target)
			{
				*position = middle;
			}

			else if(type_array[middle] < type_target)
			{
				low = middle + 1u;
			}

			else
			{
				high = middle;
			}
		}
	}

	else if(type == 1u)
	{
		const c_utils_char_t *const *const type_array = (const c_utils_char_t *const *)array;
		const c_utils_char_t *const type_target = (const c_utils_char_t *)target;
		c_utils_size_t low = 0u;
		c_utils_size_t high = count;
		c_utils_size_t middle;

		while(low < high)
		{
			int cmp;
			middle = low + (high - low) / 2u;
			cmp = strcmp(type_array[middle], type_target);

			if(cmp == 0)
			{
				*position = middle;
			}

			else if(cmp < 0)
			{
				low = middle + 1u;
			}

			else
			{
				high = middle;
			}
		}
	}

	else if(type == 2u)
	{
		if(element_size == 1u)
		{
			const c_utils_uint8_t *const type_array = (const c_utils_uint8_t *)array;
			const c_utils_uint8_t type_target = *(const c_utils_uint8_t *)target;
			c_utils_size_t low = 0u;
			c_utils_size_t high = count;
			c_utils_size_t middle;

			while(low < high)
			{
				middle = low + (high - low) / 2u;

				if(type_array[middle] == type_target)
				{
					*position = middle;
				}

				else if(type_array[middle] < type_target)
				{
					low = middle + 1u;
				}

				else
				{
					high = middle;
				}
			}
		}

		else if(element_size == 2u)
		{
			const c_utils_uint16_t *const type_array = (const c_utils_uint16_t *)array;
			const c_utils_uint16_t type_target = *(const c_utils_uint16_t *)target;
			c_utils_size_t low = 0u;
			c_utils_size_t high = count;
			c_utils_size_t middle;

			while(low < high)
			{
				middle = low + (high - low) / 2u;

				if(type_array[middle] == type_target)
				{
					*position = middle;
				}

				else if(type_array[middle] < type_target)
				{
					low = middle + 1u;
				}

				else
				{
					high = middle;
				}
			}
		}

		else if(element_size == 4u)
		{
			const c_utils_uint32_t *const type_array = (const c_utils_uint32_t *)array;
			const c_utils_uint32_t type_target = *(const c_utils_uint32_t *)target;
			c_utils_size_t low = 0u;
			c_utils_size_t high = count;
			c_utils_size_t middle;

			while(low < high)
			{
				middle = low + (high - low) / 2u;

				if(type_array[middle] == type_target)
				{
					*position = middle;
				}

				else if(type_array[middle] < type_target)
				{
					low = middle + 1u;
				}

				else
				{
					high = middle;
				}
			}
		}
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L) || \
defined(C_UTILS_ENABLE_INT64) || defined(C_UTILS_ENABLE_ALL_EXTENSIONS)

		else if(element_size == 8u)
		{
			const c_utils_uint64_t *const type_array = (const c_utils_uint64_t *)array;
			const c_utils_uint64_t type_target = *(const c_utils_uint64_t *)target;
			c_utils_size_t low = 0u;
			c_utils_size_t high = count;
			c_utils_size_t middle;

			while(low < high)
			{
				middle = low + (high - low) / 2u;

				if(type_array[middle] == type_target)
				{
					*position = middle;
				}

				else if(type_array[middle] < type_target)
				{
					low = middle + 1u;
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
			C_UTILS_REPORT_ERROR("Error in function c_utils_generic_binary_search, the element_size is not supported");

			return C_UTILS_RESULT_FAILURE;
		}
	}

	else if(type == 3u)
	{
		if(element_size == 1u)
		{
			const c_utils_int8_t *const type_array = (const c_utils_int8_t *)array;
			const c_utils_int8_t type_target = *(const c_utils_int8_t *)target;
			c_utils_size_t low = 0u;
			c_utils_size_t high = count;
			c_utils_size_t middle;

			while(low < high)
			{
				middle = low + (high - low) / 2u;

				if(type_array[middle] == type_target)
				{
					*position = middle;
				}

				else if(type_array[middle] < type_target)
				{
					low = middle + 1u;
				}

				else
				{
					high = middle;
				}
			}
		}

		else if(element_size == 2u)
		{
			const c_utils_int16_t *const type_array = (const c_utils_int16_t *)array;
			const c_utils_int16_t type_target = *(const c_utils_int16_t *)target;
			c_utils_size_t low = 0u;
			c_utils_size_t high = count;
			c_utils_size_t middle;

			while(low < high)
			{
				middle = low + (high - low) / 2u;

				if(type_array[middle] == type_target)
				{
					*position = middle;
				}

				else if(type_array[middle] < type_target)
				{
					low = middle + 1u;
				}

				else
				{
					high = middle;
				}
			}
		}

		else if(element_size == 4u)
		{
			const c_utils_int32_t *const type_array = (const c_utils_int32_t *)array;
			const c_utils_int32_t type_target = *(const c_utils_int32_t *)target;
			c_utils_size_t low = 0u;
			c_utils_size_t high = count;
			c_utils_size_t middle;

			while(low < high)
			{
				middle = low + (high - low) / 2u;

				if(type_array[middle] == type_target)
				{
					*position = middle;
				}

				else if(type_array[middle] < type_target)
				{
					low = middle + 1u;
				}

				else
				{
					high = middle;
				}
			}
		}
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L) || \
     defined(C_UTILS_ENABLE_INT64) || defined(C_UTILS_ENABLE_ALL_EXTENSIONS)

		else if(element_size == 8u)
		{
			const c_utils_int64_t *const type_array = (const c_utils_int64_t *)array;
			const c_utils_int64_t type_target = *(const c_utils_int64_t *)target;
			c_utils_size_t low = 0u;
			c_utils_size_t high = count;
			c_utils_size_t middle;

			while(low < high)
			{
				middle = low + (high - low) / 2u;

				if(type_array[middle] == type_target)
				{
					*position = middle;
				}

				else if(type_array[middle] < type_target)
				{
					low = middle + 1u;
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
			C_UTILS_REPORT_ERROR("Error in function c_utils_generic_binary_search, the element_size is not supported");

			return C_UTILS_RESULT_FAILURE;
		}
	}

	else if(type == 4u)
	{
		if(element_size == 4u)
		{
			const c_utils_float32_t *const type_array = (const c_utils_float32_t *)array;
			const c_utils_float32_t type_target = *(const c_utils_float32_t *)target;
			c_utils_float32_t difference;
			c_utils_float32_t absolute_difference;
			c_utils_float32_t absolute_array;
			c_utils_float32_t absolute_target;
			c_utils_float32_t scale;
			c_utils_size_t low = 0u;
			c_utils_size_t high = count;
			c_utils_size_t middle;

			while(low < high)
			{
				middle = low + (high - low) / 2u;
				difference = type_array[middle] - type_target;
				absolute_difference = difference < 0.0f ? -difference : difference;
				absolute_array = type_array[middle] < 0.0f ? -type_array[middle] : type_array[middle];
				absolute_target = type_target < 0.0f ? -type_target : type_target;
				scale = absolute_array > absolute_target ? absolute_array : absolute_target;

				if(absolute_difference <= 10 * C_UTILS_FLOAT32_EPSILON * scale)
				{
					*position = middle;
				}

				else if(type_array[middle] < type_target)
				{
					low = middle + 1u;
				}

				else
				{
					high = middle;
				}
			}
		}

		else if(element_size == 8u)
		{
			const c_utils_float64_t *const type_array = (const c_utils_float64_t *)array;
			const c_utils_float64_t type_target = *(const c_utils_float64_t *)target;
			c_utils_float64_t difference;
			c_utils_float64_t absolute_difference;
			c_utils_float64_t absolute_array;
			c_utils_float64_t absolute_target;
			c_utils_float64_t scale;
			c_utils_size_t low = 0u;
			c_utils_size_t high = count;
			c_utils_size_t middle;

			while(low < high)
			{
				middle = low + (high - low) / 2u;
				difference = type_array[middle] - type_target;
				absolute_difference = difference < 0.0 ? -difference : difference;
				absolute_array = type_array[middle] < 0.0 ? -type_array[middle] : type_array[middle];
				absolute_target = type_target < 0.0 ? -type_target : type_target;
				scale = absolute_array > absolute_target ? absolute_array : absolute_target;

				if(absolute_difference <= 10 * C_UTILS_FLOAT64_EPSILON * scale)
				{
					*position = middle;
				}

				else if(type_array[middle] < type_target)
				{
					low = middle + 1u;
				}

				else
				{
					high = middle;
				}
			}
		}

		else
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_generic_binary_search, the element_size is not supported");

			return C_UTILS_RESULT_FAILURE;
		}
	}

	else
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_generic_binary_search, the type is not supported");

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
