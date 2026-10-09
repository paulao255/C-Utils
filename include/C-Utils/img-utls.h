/******************/
/* Include guard: */
/******************/

#ifndef C_UTILS_IMG_UTLS_H
#define C_UTILS_IMG_UTLS_H

/*************************/
/* Library importations: */
/*************************/

#include "defs.h"
#include "c-utils.h"

/********************/
/* Import C to C++: */
/********************/

#ifdef __cplusplus
extern "C"
{
#endif

/*********************/
/* Type definitions: */
/*********************/

/* C-Utils image structure type: */
struct c_utils_image
{
	c_utils_uint32_t width;
	c_utils_uint32_t height;
	c_utils_uint8_t  channels;
	c_utils_memory_handle_t data;
};

/* C-Utils typedef image structure type: */
typedef struct c_utils_image c_utils_image;

/*************************/
/* Functions prototypes: */
/*************************/

/* C-Utils image save PNG function. */
C_UTILS_API c_utils_result_t c_utils_image_save_png(const c_utils_char_t *const filename, struct c_utils_image image);

/* C-Utils image load PNG function. */
C_UTILS_API c_utils_result_t c_utils_image_load_png(const c_utils_char_t *const filename, struct c_utils_image *const image);

/* C-Utils image save JPG function. */
C_UTILS_API c_utils_result_t c_utils_image_save_jpg(const c_utils_char_t *const filename, struct c_utils_image image, c_utils_int8_t quality);

/* C-Utils image load JPG function. */
C_UTILS_API c_utils_result_t c_utils_image_load_jpg(const c_utils_char_t *const filename, struct c_utils_image *const image);

/* C-Utils image vertical flip function. */
C_UTILS_API c_utils_result_t c_utils_image_flip_vertical(struct c_utils_image *const image);

/* C-Utils image horizontal flip function. */
C_UTILS_API c_utils_result_t c_utils_image_flip_horizontal(struct c_utils_image *const image);

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif

/***************************/
/* End C_UTILS_IMG_UTLS_H: */
/***************************/

#endif
