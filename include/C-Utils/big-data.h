/******************/
/* Include guard: */
/******************/

#ifndef C_UTILS_BIG_DATA_H
#define C_UTILS_BIG_DATA_H

/*************************/
/* Library importations: */
/*************************/

#include "defs.h"
#include <stddef.h>

/********************/
/* Import C to C++: */
/********************/

#ifdef __cplusplus
extern "C"
{
#endif

/*************************/
/* Functions prototypes: */
/*************************/

/* Function to verify if array is sorted. */
c_utils_int16_t c_utils_generic_array_is_sorted(const void *const array, const size_t count, const size_t element_size, const c_utils_uint8_t type);

/* Function to sort a generic array by insertion sorting (best case: O(n), average case: O(n^2), worst case: O(n^2)). */
c_utils_int16_t c_utils_generic_insertion_sort(const void *const array, const size_t count, const size_t element_size, const c_utils_uint8_t type);

/* Function to sort a generic array by merge sorting (best case: O(n log(n)), average case: O(n log(n)), worst case: O(n log(n))). */
c_utils_int16_t c_utils_generic_merge_sort(const void *const array, const size_t count, const size_t element_size, const c_utils_uint8_t type);

/* Function to find an element in a generic array, by a linear search (O(n)). */
c_utils_int16_t c_utils_generic_linear_search(const void *const array, const void *const target, const size_t count, const size_t element_size, const c_utils_uint8_t type, size_t *const position);

/* Function to find an element in a generic ordered array, by a binary search (O(log n)). */
c_utils_int16_t c_utils_generic_binary_search(const void *const array, const void *const target, const size_t count, const size_t element_size, const c_utils_uint8_t type, size_t *const position);

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif

/***************************/
/* End C_UTILS_BIG_DATA_H: */
/***************************/

#endif
