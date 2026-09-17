/******************/
/* Include guard: */
/******************/

#ifndef C_UTILS_RND_UTLS_H
#define C_UTILS_RND_UTLS_H

/*************************/
/* Library importations: */
/*************************/

#include "defs.h"

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

/* Function to initialize C-Utils random. */
C_UTILS_API c_utils_result_t c_utils_random_initialize(c_utils_void_t);

/* Function to get a random 32 bits signed integer based on the minimum and maximum values. */
C_UTILS_API c_utils_result_t c_utils_random_integer(c_utils_int32_t minimum, c_utils_int32_t maximum, c_utils_int32_t *const output);

/* Function to terminate C-Utils random. */
C_UTILS_API c_utils_result_t c_utils_random_terminate(c_utils_void_t);

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif

/***************************/
/* End C_UTILS_RND_UTLS_H: */
/***************************/

#endif
