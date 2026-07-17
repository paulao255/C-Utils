/*************************/
/* Library importations: */
/*************************/

#include "big-data.h"
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

c_utils_int16_t c_utils_generic_array_is_sorted(const void *const array, const size_t count, const size_t element_size, const c_utils_uint8_t type)
{
	if(array == (void *)0)
	{
		fprintf(stderr, "Error in function c_utils_generic_array_is_sorted (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(element_size == 0u || element_size > 8u)
	{
		fprintf(stderr, "Error in function c_utils_generic_array_is_sorted (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(type == 0u)
	{
		size_t index;
		const c_utils_char_t *const type_array = (const c_utils_char_t *)array;

		for(index = 0u; index < count - 1u; index++)
		{
			if(type_array[index] > type_array[index + 1u])
			{
				return C_UTILS_FAILURE;
			}
		}
	}

	else if(type == 1u)
	{
		size_t index;
		const c_utils_char_t *const *const type_array = (const c_utils_char_t *const *)array;

		for(index = 0u; index < count - 1u; index++)
		{
			if(strcmp(type_array[index], type_array[index + 1u]) > 0)
			{
				return C_UTILS_FAILURE;
			}
		}
	}

	else if(type == 2u)
	{
		if(element_size == 1u)
		{
			size_t index;
			const c_utils_uint8_t *const type_array = (const c_utils_uint8_t *)array;

			for(index = 0u; index < count - 1u; index++)
			{
				if(type_array[index] > type_array[index + 1u])
				{
					return C_UTILS_FAILURE;
				}
			}
		}

		else if(element_size == 2u)
		{
			size_t index;
			const c_utils_uint16_t *const type_array = (const c_utils_uint16_t *)array;

			for(index = 0u; index < count - 1u; index++)
			{
				if(type_array[index] > type_array[index + 1u])
				{
					return C_UTILS_FAILURE;
				}
			}
		}

		else if(element_size == 4u)
		{
			size_t index;
			const c_utils_uint32_t *const type_array = (const c_utils_uint32_t *)array;

			for(index = 0u; index < count - 1u; index++)
			{
				if(type_array[index] > type_array[index + 1u])
				{
					return C_UTILS_FAILURE;
				}
			}
		}
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L) || \
defined(C_UTILS_ENABLE_INT64) || defined(C_UTILS_ENABLE_ALL_EXTENSIONS)

		else if(element_size == 8u)
		{
			size_t index;
			const c_utils_uint64_t *const type_array = (const c_utils_uint64_t *)array;

			for(index = 0u; index < count - 1u; index++)
			{
				if(type_array[index] > type_array[index + 1u])
				{
					return C_UTILS_FAILURE;
				}
			}
		}
#endif

		else
		{
			fprintf(stderr, "Error in function c_utils_generic_array_is_sorted (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_FAILURE;
		}
	}

	else if(type == 3u)
	{
		if(element_size == 1u)
		{
			size_t index;
			const c_utils_int8_t *const type_array = (const c_utils_int8_t *)array;

			for(index = 0u; index < count - 1u; index++)
			{
				if(type_array[index] > type_array[index + 1u])
				{
					return C_UTILS_FAILURE;
				}
			}
		}

		else if(element_size == 2u)
		{
			size_t index;
			const c_utils_int16_t *const type_array = (const c_utils_int16_t *)array;

			for(index = 0u; index < count - 1u; index++)
			{
				if(type_array[index] > type_array[index + 1u])
				{
					return C_UTILS_FAILURE;
				}
			}
		}

		else if(element_size == 4u)
		{
			size_t index;
			const c_utils_int32_t *const type_array = (const c_utils_int32_t *)array;

			for(index = 0u; index < count - 1u; index++)
			{
				if(type_array[index] > type_array[index + 1u])
				{
					return C_UTILS_FAILURE;
				}
			}
		}
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L) || \
defined(C_UTILS_ENABLE_INT64) || defined(C_UTILS_ENABLE_ALL_EXTENSIONS)

		else if(element_size == 8u)
		{
			size_t index;
			const c_utils_int64_t *const type_array = (const c_utils_int64_t *)array;

			for(index = 0u; index < count - 1u; index++)
			{
				if(type_array[index] > type_array[index + 1u])
				{
					return C_UTILS_FAILURE;
				}
			}
		}
#endif

		else
		{
			fprintf(stderr, "Error in function c_utils_generic_array_is_sorted (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_FAILURE;
		}

	}

	else if(type == 4u)
	{
		if(element_size == 4u)
		{
			size_t index;
			const c_utils_float32_t *const type_array = (const c_utils_float32_t *)array;

			for(index = 0u; index < count - 1u; index++)
			{
				if(type_array[index] > type_array[index + 1u])
				{
					return C_UTILS_FAILURE;
				}
			}
		}

		else if(element_size == 8u)
		{
			size_t index;
			const c_utils_float64_t *const type_array = (const c_utils_float64_t *)array;

			for(index = 0u; index < count - 1u; index++)
			{
				if(type_array[index] > type_array[index + 1u])
				{
					return C_UTILS_FAILURE;
				}
			}
		}

		else
		{
			fprintf(stderr, "Error in function c_utils_generic_array_is_sorted (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_FAILURE;
		}
	}

	else
	{
		fprintf(stderr, "Error in function c_utils_generic_array_is_sorted (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	return C_UTILS_SUCCESS;
}

c_utils_int16_t c_utils_generic_insertion_sort(const void *const array, const size_t count, const size_t element_size, const c_utils_uint8_t type)
{
	if(array == (void *)0)
	{
		fprintf(stderr, "Error in function c_utils_generic_insertion_sort (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(element_size == 0u || element_size > 8u)
	{
		fprintf(stderr, "Error in function c_utils_generic_insertion_sort (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(type == 0u)
	{
		size_t index;
		c_utils_char_t *const type_array = (c_utils_char_t *)array;

		for(index = 1u; index < count; index++)
		{
			c_utils_char_t key = type_array[index];
			size_t j = index;

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
		size_t index;
		c_utils_char_t **const type_array = (c_utils_char_t **)array;

		for(index = 1u; index < count; index++)
		{
			c_utils_char_t *const key = type_array[index];
			size_t j = index;

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
			size_t index;
			c_utils_uint8_t *const type_array = (c_utils_uint8_t *)array;

			for(index = 1u; index < count; index++)
			{
				c_utils_uint8_t key = type_array[index];
				size_t j = index;

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
			size_t index;
			c_utils_uint16_t *const type_array = (c_utils_uint16_t *)array;

			for(index = 1u; index < count; index++)
			{
				c_utils_uint16_t key = type_array[index];
				size_t j = index;

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
			size_t index;
			c_utils_uint32_t *const type_array = (c_utils_uint32_t *)array;

			for(index = 1u; index < count; index++)
			{
				c_utils_uint32_t key = type_array[index];
				size_t j = index;

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
			size_t index;
			c_utils_uint64_t *const type_array = (c_utils_uint64_t *)array;

			for(index = 1u; index < count; index++)
			{
				c_utils_uint64_t key = type_array[index];
				size_t j = index;

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
			fprintf(stderr, "Error in function c_utils_generic_insertion_sort (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_FAILURE;
		}
	}

	else if(type == 3u)
	{
		if(element_size == 1u)
		{
			size_t index;
			c_utils_int8_t *const type_array = (c_utils_int8_t *)array;

			for(index = 1u; index < count; index++)
			{
				c_utils_int8_t key = type_array[index];
				size_t j = index;

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
			size_t index;
			c_utils_int16_t *const type_array = (c_utils_int16_t *)array;

			for(index = 1u; index < count; index++)
			{
				c_utils_int16_t key = type_array[index];
				size_t j = index;

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
			size_t index;
			c_utils_int32_t *const type_array = (c_utils_int32_t *)array;

			for(index = 1u; index < count; index++)
			{
				c_utils_int32_t key = type_array[index];
				size_t j = index;

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
			size_t index;
			c_utils_int64_t *const type_array = (c_utils_int64_t *)array;

			for(index = 1u; index < count; index++)
			{
				c_utils_int64_t key = type_array[index];
				size_t j = index;

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
			fprintf(stderr, "Error in function c_utils_generic_insertion_sort (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_FAILURE;
		}
	}

	else if(type == 4u)
	{
		if(element_size == 4u)
		{
			size_t index;
			c_utils_float32_t *const type_array = (c_utils_float32_t *)array;

			for(index = 1u; index < count; index++)
			{
				c_utils_float32_t key = type_array[index];
				size_t j = index;

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
			size_t index;
			c_utils_float64_t *const type_array = (c_utils_float64_t *)array;

			for(index = 1u; index < count; index++)
			{
				c_utils_float64_t key = type_array[index];
				size_t j = index;

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
			fprintf(stderr, "Error in function c_utils_generic_insertion_sort (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_FAILURE;
		}
	}

	else
	{
		fprintf(stderr, "Error in function c_utils_generic_insertion_sort (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	return C_UTILS_SUCCESS;
}

c_utils_int16_t c_utils_generic_merge_sort(const void *const array, const size_t count, const size_t element_size, const c_utils_uint8_t type)
{
	if(array == (void *)0)
	{
		fprintf(stderr, "Error in function c_utils_generic_merge_sort (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(element_size == 0u || element_size > 8u)
	{
		fprintf(stderr, "Error in function c_utils_generic_merge_sort (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(count > 1u)
	{
		if(type == 0u)
		{
			c_utils_char_t *const type_array = (c_utils_char_t *)array;
			c_utils_char_t *const temporary_array = (c_utils_char_t *)malloc(count * sizeof(c_utils_char_t));
			size_t width;

			if(temporary_array == (c_utils_char_t *)0)
			{
				fprintf(stderr, "Error in function c_utils_generic_merge_sort (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_FAILURE;
			}

			for(width = 1u; width < count; width *= 2u)
			{
				size_t left;

				for(left = 0u; left < count; left += 2u * width)
				{
					size_t middle = (left + width < count) ? (left + width) : count;
					size_t right = (left + 2u * width < count) ? (left + 2u * width) : count;
					size_t left_index = left;
					size_t right_index = middle;
					size_t merge_index = left;

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

			free((void *)temporary_array);
		}

		else if(type == 1u)
		{
			c_utils_char_t **const type_array = (c_utils_char_t **)array;
			c_utils_char_t **const temporary_array = (c_utils_char_t **)malloc(count * sizeof(c_utils_char_t *));
			size_t width;

			if(temporary_array == (c_utils_char_t **)0)
			{
				fprintf(stderr, "Error in function c_utils_generic_merge_sort (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_FAILURE;
			}

			for(width = 1u; width < count; width *= 2u)
			{
				size_t left;

				for(left = 0u; left < count; left += 2u * width)
				{
					size_t middle = (left + width < count) ? (left + width) : count;
					size_t right = (left + 2u * width < count) ? (left + 2u * width) : count;
					size_t left_index = left;
					size_t right_index = middle;
					size_t merge_index = left;

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

			free((void *)temporary_array);
		}

		else if(type == 2u)
		{
			if(element_size == 1u)
			{
				c_utils_uint8_t *const type_array = (c_utils_uint8_t *)array;
				c_utils_uint8_t *const temporary_array = (c_utils_uint8_t *)malloc(count * sizeof(c_utils_uint8_t));
				size_t width;

				if(temporary_array == (c_utils_uint8_t *)0)
				{
					fprintf(stderr, "Error in function c_utils_generic_merge_sort (File: %s, Line: %d)...\n", __FILE__, __LINE__);

					return C_UTILS_FAILURE;
				}

				for(width = 1u; width < count; width *= 2u)
				{
					size_t left;

					for(left = 0u; left < count; left += 2u * width)
					{
						size_t middle = (left + width < count) ? (left + width) : count;
						size_t right = (left + 2u * width < count) ? (left + 2u * width) : count;
						size_t left_index = left;
						size_t right_index = middle;
						size_t merge_index = left;

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

				free((void *)temporary_array);
			}

			else if(element_size == 2u)
			{
				c_utils_uint16_t *const type_array = (c_utils_uint16_t *)array;
				c_utils_uint16_t *const temporary_array = (c_utils_uint16_t *)malloc(count * sizeof(c_utils_uint16_t));
				size_t width;

				if(temporary_array == (c_utils_uint16_t *)0)
				{
					fprintf(stderr, "Error in function c_utils_generic_merge_sort (File: %s, Line: %d)...\n", __FILE__, __LINE__);

					return C_UTILS_FAILURE;
				}

				for(width = 1u; width < count; width *= 2u)
				{
					size_t left;

					for(left = 0u; left < count; left += 2u * width)
					{
						size_t middle = (left + width < count) ? (left + width) : count;
						size_t right = (left + 2u * width < count) ? (left + 2u * width) : count;
						size_t left_index = left;
						size_t right_index = middle;
						size_t merge_index = left;

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

				free((void *)temporary_array);
			}

			else if(element_size == 4u)
			{
				c_utils_uint32_t *const type_array = (c_utils_uint32_t *)array;
				c_utils_uint32_t *const temporary_array = (c_utils_uint32_t *)malloc(count * sizeof(c_utils_uint32_t));
				size_t width;

				if(temporary_array == (c_utils_uint32_t *)0)
				{
					fprintf(stderr, "Error in function c_utils_generic_merge_sort (File: %s, Line: %d)...\n", __FILE__, __LINE__);

					return C_UTILS_FAILURE;
				}

				for(width = 1u; width < count; width *= 2u)
				{
					size_t left;

					for(left = 0u; left < count; left += 2u * width)
					{
						size_t middle = (left + width < count) ? (left + width) : count;
						size_t right = (left + 2u * width < count) ? (left + 2u * width) : count;
						size_t left_index = left;
						size_t right_index = middle;
						size_t merge_index = left;

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

				free((void *)temporary_array);
			}
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L) || \
     defined(C_UTILS_ENABLE_INT64) || defined(C_UTILS_ENABLE_ALL_EXTENSIONS)

			else if(element_size == 8u)
			{
				c_utils_uint64_t *const type_array = (c_utils_uint64_t *)array;
				c_utils_uint64_t *const temporary_array = (c_utils_uint64_t *)malloc(count * sizeof(c_utils_uint64_t));
				size_t width;

				if(temporary_array == (c_utils_uint64_t *)0)
				{
					fprintf(stderr, "Error in function c_utils_generic_merge_sort (File: %s, Line: %d)...\n", __FILE__, __LINE__);

					return C_UTILS_FAILURE;
				}

				for(width = 1u; width < count; width *= 2u)
				{
					size_t left;

					for(left = 0u; left < count; left += 2u * width)
					{
						size_t middle = (left + width < count) ? (left + width) : count;
						size_t right = (left + 2u * width < count) ? (left + 2u * width) : count;
						size_t left_index = left;
						size_t right_index = middle;
						size_t merge_index = left;

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

				free((void *)temporary_array);
			}
#endif

			else
			{
				fprintf(stderr, "Error in function c_utils_generic_merge_sort (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_FAILURE;
			}
		}

		else if(type == 3u)
		{
			if(element_size == 1u)
			{
				c_utils_int8_t *const type_array = (c_utils_int8_t *)array;
				c_utils_int8_t *const temporary_array = (c_utils_int8_t *)malloc(count * sizeof(c_utils_int8_t));
				size_t width;

				if(temporary_array == (c_utils_int8_t *)0)
				{
					fprintf(stderr, "Error in function c_utils_generic_merge_sort (File: %s, Line: %d)...\n", __FILE__, __LINE__);

					return C_UTILS_FAILURE;
				}

				for(width = 1u; width < count; width *= 2u)
				{
					size_t left;

					for(left = 0u; left < count; left += 2u * width)
					{
						size_t middle = (left + width < count) ? (left + width) : count;
						size_t right = (left + 2u * width < count) ? (left + 2u * width) : count;
						size_t left_index = left;
						size_t right_index = middle;
						size_t merge_index = left;

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

				free((void *)temporary_array);
			}

			else if(element_size == 2u)
			{
				c_utils_int16_t *const type_array = (c_utils_int16_t *)array;
				c_utils_int16_t *const temporary_array = (c_utils_int16_t *)malloc(count * sizeof(c_utils_int16_t));
				size_t width;

				if(temporary_array == (c_utils_int16_t *)0)
				{
					fprintf(stderr, "Error in function c_utils_generic_merge_sort (File: %s, Line: %d)...\n", __FILE__, __LINE__);

					return C_UTILS_FAILURE;
				}

				for(width = 1u; width < count; width *= 2u)
				{
					size_t left;

					for(left = 0u; left < count; left += 2u * width)
					{
						size_t middle = (left + width < count) ? (left + width) : count;
						size_t right = (left + 2u * width < count) ? (left + 2u * width) : count;
						size_t left_index = left;
						size_t right_index = middle;
						size_t merge_index = left;

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

				free((void *)temporary_array);
			}

			else if(element_size == 4u)
			{
				c_utils_int32_t *const type_array = (c_utils_int32_t *)array;
				c_utils_int32_t *const temporary_array = (c_utils_int32_t *)malloc(count * sizeof(c_utils_int32_t));
				size_t width;

				if(temporary_array == (c_utils_int32_t *)0)
				{
					fprintf(stderr, "Error in function c_utils_generic_merge_sort (File: %s, Line: %d)...\n", __FILE__, __LINE__);

					return C_UTILS_FAILURE;
				}

				for(width = 1u; width < count; width *= 2u)
				{
					size_t left;

					for(left = 0u; left < count; left += 2u * width)
					{
						size_t middle = (left + width < count) ? (left + width) : count;
						size_t right = (left + 2u * width < count) ? (left + 2u * width) : count;
						size_t left_index = left;
						size_t right_index = middle;
						size_t merge_index = left;

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

				free((void *)temporary_array);
			}
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L) || \
     defined(C_UTILS_ENABLE_INT64) || defined(C_UTILS_ENABLE_ALL_EXTENSIONS)

			else if(element_size == 8u)
			{
				c_utils_int64_t *const type_array = (c_utils_int64_t *)array;
				c_utils_int64_t *const temporary_array = (c_utils_int64_t *)malloc(count * sizeof(c_utils_int64_t));
				size_t width;

				if(temporary_array == (c_utils_int64_t *)0)
				{
					fprintf(stderr, "Error in function c_utils_generic_merge_sort (File: %s, Line: %d)...\n", __FILE__, __LINE__);

					return C_UTILS_FAILURE;
				}

				for(width = 1u; width < count; width *= 2u)
				{
					size_t left;

					for(left = 0u; left < count; left += 2u * width)
					{
						size_t middle = (left + width < count) ? (left + width) : count;
						size_t right = (left + 2u * width < count) ? (left + 2u * width) : count;
						size_t left_index = left;
						size_t right_index = middle;
						size_t merge_index = left;

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

				free((void *)temporary_array);
			}
#endif

			else
			{
				fprintf(stderr, "Error in function c_utils_generic_merge_sort (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_FAILURE;
			}
		}

		else if(type == 4u)
		{
			if(element_size == 4u)
			{
				c_utils_float32_t *const type_array = (c_utils_float32_t *)array;
				c_utils_float32_t *const temporary_array = (c_utils_float32_t *)malloc(count * sizeof(c_utils_float32_t));
				size_t width;

				if(temporary_array == (c_utils_float32_t *)0)
				{
					fprintf(stderr, "Error in function c_utils_generic_merge_sort (File: %s, Line: %d)...\n", __FILE__, __LINE__);

					return C_UTILS_FAILURE;
				}

				for(width = 1u; width < count; width *= 2u)
				{
					size_t left;

					for(left = 0u; left < count; left += 2u * width)
					{
						size_t middle = (left + width < count) ? (left + width) : count;
						size_t right = (left + 2u * width < count) ? (left + 2u * width) : count;
						size_t left_index = left;
						size_t right_index = middle;
						size_t merge_index = left;

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

				free((void *)temporary_array);
			}

			else if(element_size == 8u)
			{
				c_utils_float64_t *const type_array = (c_utils_float64_t *)array;
				c_utils_float64_t *const temporary_array = (c_utils_float64_t *)malloc(count * sizeof(c_utils_float64_t));
				size_t width;

				if(temporary_array == (c_utils_float64_t *)0)
				{
					fprintf(stderr, "Error in function c_utils_generic_merge_sort (File: %s, Line: %d)...\n", __FILE__, __LINE__);

					return C_UTILS_FAILURE;
				}

				for(width = 1u; width < count; width *= 2u)
				{
					size_t left;

					for(left = 0u; left < count; left += 2u * width)
					{
						size_t middle = (left + width < count) ? (left + width) : count;
						size_t right = (left + 2u * width < count) ? (left + 2u * width) : count;
						size_t left_index = left;
						size_t right_index = middle;
						size_t merge_index = left;

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

				free((void *)temporary_array);
			}

			else
			{
				fprintf(stderr, "Error in function c_utils_generic_merge_sort (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_FAILURE;
			}
		}

		else
		{
			fprintf(stderr, "Error in function c_utils_generic_merge_sort (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_FAILURE;
		}
	}

	return C_UTILS_SUCCESS;
}

c_utils_int16_t c_utils_generic_linear_search(const void *const array, const void *const target, const size_t count, const size_t element_size, const c_utils_uint8_t type, size_t *const position)
{
	if(array == (void *)0)
	{
		fprintf(stderr, "Error in function c_utils_generic_linear_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(target == (void *)0)
	{
		fprintf(stderr, "Error in function c_utils_generic_linear_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(position == (size_t *)0)
	{
		fprintf(stderr, "Error in function c_utils_generic_linear_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(element_size == 0u || element_size > 8u)
	{
		fprintf(stderr, "Error in function c_utils_generic_linear_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(type == 0u)
	{
		const c_utils_char_t *const type_array = (const c_utils_char_t *)array;
		const c_utils_char_t type_target = *(const c_utils_char_t *)target;
		size_t index;

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
		size_t index;

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
			size_t index;

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
			size_t index;

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
			size_t index;

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
			size_t index;

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
			fprintf(stderr, "Error in function c_utils_generic_linear_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_FAILURE;
		}
	}

	else if(type == 3u)
	{
		if(element_size == 1u)
		{
			const c_utils_int8_t *const type_array = (const c_utils_int8_t *)array;
			const c_utils_int8_t type_target = *(const c_utils_int8_t *)target;
			size_t index;

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
			size_t index;

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
			size_t index;

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
			size_t index;

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
			fprintf(stderr, "Error in function c_utils_generic_linear_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_FAILURE;
		}
	}

	else if(type == 4u)
	{
		if(element_size == 4u)
		{
			const c_utils_float32_t *const type_array = (const c_utils_float32_t *)array;
			const c_utils_float32_t type_target = *(const c_utils_float32_t *)target;
			size_t index;

			for(index = 0u; index < count; index++)
			{
				const c_utils_float32_t difference = type_array[index] - type_target;
				const c_utils_float32_t absolute_difference = difference < 0.0f ? -difference : difference;
				const c_utils_float32_t absolute_array = type_array[index] < 0.0f ? -type_array[index] : type_array[index];
				const c_utils_float32_t absolute_target = type_target < 0.0f ? -type_target : type_target;
				const c_utils_float32_t scale = absolute_array > absolute_target ? absolute_array : absolute_target;

				if(absolute_difference <= 10 * FLT_EPSILON * scale)
				{
					*position = index;
				}
			}
		}

		else if(element_size == 8u)
		{
			const c_utils_float64_t *const type_array = (const c_utils_float64_t *)array;
			const c_utils_float64_t type_target = *(const c_utils_float64_t *)target;
			size_t index;

			for(index = 0u; index < count; index++)
			{
				const c_utils_float64_t difference = type_array[index] - type_target;
				const c_utils_float64_t absolute_difference = difference < 0.0 ? -difference : difference;
				const c_utils_float64_t absolute_array = type_array[index] < 0.0 ? -type_array[index] : type_array[index];
				const c_utils_float64_t absolute_target = type_target < 0.0 ? -type_target : type_target;
				const c_utils_float64_t scale = absolute_array > absolute_target ? absolute_array : absolute_target;

				if(absolute_difference <= 10 * DBL_EPSILON * scale)
				{
					*position = index;
				}
			}
		}

		else
		{
			fprintf(stderr, "Error in function c_utils_generic_linear_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_FAILURE;
		}
	}

	else
	{
		fprintf(stderr, "Error in function c_utils_generic_linear_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	return C_UTILS_SUCCESS;
}

c_utils_int16_t c_utils_generic_binary_search(const void *const array, const void *const target, const size_t count, const size_t element_size, const c_utils_uint8_t type, size_t *const position)
{
	if(array == (void *)0)
	{
		fprintf(stderr, "Error in function c_utils_generic_binary_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(target == (void *)0)
	{
		fprintf(stderr, "Error in function c_utils_generic_binary_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(position == (size_t *)0)
	{
		fprintf(stderr, "Error in function c_utils_generic_binary_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(element_size == 0u || element_size > 8u)
	{
		fprintf(stderr, "Error in function c_utils_generic_binary_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(type == 0u)
	{
		const c_utils_char_t *const type_array = (const c_utils_char_t *)array;
		const c_utils_char_t type_target = *(const c_utils_char_t *)target;
		size_t low = 0u;
		size_t high = count;
		size_t middle;

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
		size_t low = 0u;
		size_t high = count;
		size_t middle;

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
			size_t low = 0u;
			size_t high = count;
			size_t middle;

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
			size_t low = 0u;
			size_t high = count;
			size_t middle;

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
			size_t low = 0u;
			size_t high = count;
			size_t middle;

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
			size_t low = 0u;
			size_t high = count;
			size_t middle;

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
			fprintf(stderr, "Error in function c_utils_generic_binary_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_FAILURE;
		}
	}

	else if(type == 3u)
	{
		if(element_size == 1u)
		{
			const c_utils_int8_t *const type_array = (const c_utils_int8_t *)array;
			const c_utils_int8_t type_target = *(const c_utils_int8_t *)target;
			size_t low = 0u;
			size_t high = count;
			size_t middle;

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
			size_t low = 0u;
			size_t high = count;
			size_t middle;

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
			size_t low = 0u;
			size_t high = count;
			size_t middle;

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
			size_t low = 0u;
			size_t high = count;
			size_t middle;

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
			fprintf(stderr, "Error in function c_utils_generic_binary_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_FAILURE;
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
			size_t low = 0u;
			size_t high = count;
			size_t middle;

			while(low < high)
			{
				middle = low + (high - low) / 2u;
				difference = type_array[middle] - type_target;
				absolute_difference = difference < 0.0f ? -difference : difference;
				absolute_array = type_array[middle] < 0.0f ? -type_array[middle] : type_array[middle];
				absolute_target = type_target < 0.0f ? -type_target : type_target;
				scale = absolute_array > absolute_target ? absolute_array : absolute_target;

				if(absolute_difference <= 10 * FLT_EPSILON * scale)
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
			size_t low = 0u;
			size_t high = count;
			size_t middle;

			while(low < high)
			{
				middle = low + (high - low) / 2u;
				difference = type_array[middle] - type_target;
				absolute_difference = difference < 0.0 ? -difference : difference;
				absolute_array = type_array[middle] < 0.0 ? -type_array[middle] : type_array[middle];
				absolute_target = type_target < 0.0 ? -type_target : type_target;
				scale = absolute_array > absolute_target ? absolute_array : absolute_target;

				if(absolute_difference <= 10 * DBL_EPSILON * scale)
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
			fprintf(stderr, "Error in function c_utils_generic_binary_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_FAILURE;
		}
	}

	else
	{
		fprintf(stderr, "Error in function c_utils_generic_binary_search (File: %s, Line: %d)...\n", __FILE__, __LINE__);

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
