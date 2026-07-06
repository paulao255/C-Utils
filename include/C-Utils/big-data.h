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
