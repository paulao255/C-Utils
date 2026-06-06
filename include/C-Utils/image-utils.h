/* Include guard: */
#ifndef C_UTILS_IMAGE_UTILS_H
#define C_UTILS_IMAGE_UTILS_H

/* Importations: */
#include "definitions.h"


/* C-Utils image structure type: */
struct c_utils_image
{
	c_utils_uint32_t width;
	c_utils_uint32_t height;
	c_utils_uint8_t  channels;
	c_utils_uint8_t *data;
};

typedef struct c_utils_image c_utils_image;

/* Import C to C++: */
#ifdef __cplusplus
extern "C"
{
#endif

c_utils_int16_t c_utils_save_png(const c_utils_char_t *const filename, struct c_utils_image image);                         /* C-Utils save PNG function.            */
c_utils_int16_t c_utils_load_png(const c_utils_char_t *const filename, struct c_utils_image *const image);                  /* C-Utils load PNG function.            */
c_utils_int16_t c_utils_save_jpg(const c_utils_char_t *const filename, struct c_utils_image image, c_utils_int8_t quality); /* C-Utils save JPG function.            */
c_utils_int16_t c_utils_load_jpg(const c_utils_char_t *const filename, struct c_utils_image *const image);                  /* C-Utils load JPG function.            */
c_utils_int16_t c_utils_image_flip_vertical(struct c_utils_image *const image);                                             /* C-Utils image flip vertical function. */

/* End C to C++ importation: */
#ifdef __cplusplus
}
#endif

/* End C_UTILS_IMAGE_UTILS_H: */
#endif
