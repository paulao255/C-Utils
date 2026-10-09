/*************************/
/* Library importations: */
/*************************/

#ifndef C_UTILS_COMPILE
#include "../../include/C-Utils/img-utls.h"
#include "../../include/C-Utils/err-utls.h"
#else
#include "C-Utils/img-utls.h"
#include "C-Utils/err-utls.h"
#endif
#include <png.h>
#include <jpeglib.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

/******************************/
/* C-Utils JPG error manager: */
/******************************/

struct c_utils_jpg_error_manager
{
	struct jpeg_error_mgr pub;
	jmp_buf setjmp_buffer;
};

typedef struct c_utils_jpg_error_manager c_utils_jpg_error_manager;

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

static c_utils_void_t c_utils_jpg_error_exit(j_common_ptr cinfo)
{
	struct c_utils_jpg_error_manager *myerr = (struct c_utils_jpg_error_manager *)(c_utils_void_t *)cinfo->err;
	cinfo->err->output_message(cinfo);
	longjmp(myerr->setjmp_buffer, 1);
}

C_UTILS_API c_utils_result_t c_utils_image_save_png(const c_utils_char_t *const filename, struct c_utils_image image)
{
	if(!filename)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_image_save_png, the filename is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!image.data.pointer)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_image_save_png, the image.data.pointer is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(image.channels != 3u && image.channels != 4u)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_image_save_png, the image.channels != 3u && image.channels != 4u");	

		return C_UTILS_RESULT_FAILURE;
	}

	if(!image.width || !image.height)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_image_save_png, the image.width == 0u || image.height == 0u");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		FILE *const fp = fopen(filename, "wb");

		if(!fp)
		{
			const signed int errno_error = errno;
			unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_image_save_png, function fopen failed, error code: ");
			c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

			while(error >= 10u)
			{
				error /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_image_save_png, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_image_save_png, function fopen failed, error code: %d", errno_error);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}

		else
		{
			png_structp png_ptr = png_create_write_struct(
				PNG_LIBPNG_VER_STRING,
				C_UTILS_NULL_POINTER,
				C_UTILS_NULL_POINTER,
				C_UTILS_NULL_POINTER
			);

			if(!png_ptr)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_image_save_png, function png_create_write_struct failed");

				if(fclose(fp))
				{
					const signed int errno_error = errno;
					unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
					c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
					c_utils_size_t prefix_size = strlen("Error in function c_utils_image_save_png, function fclose failed, error code: ");
					c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

					while(error >= 10u)
					{
						error /= 10u;
						error_size++;
					}

					error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

					if(!error_buffer)
					{
						C_UTILS_REPORT_ERROR("Error in function c_utils_image_save_png, function malloc failed");

						return C_UTILS_RESULT_FAILURE;
					}

					sprintf(error_buffer, "Error in function c_utils_image_save_png, function fclose failed, error code: %d", errno_error);

					C_UTILS_REPORT_ERROR(error_buffer);

					free((c_utils_void_t *)error_buffer);
				}

				return C_UTILS_RESULT_FAILURE;
			}

			else
			{
				png_bytep *row_pointers = C_UTILS_NULL_POINTER;

				if(setjmp(png_jmpbuf(png_ptr)))
				{
					if(row_pointers)
					{
						free((c_utils_void_t *)row_pointers);
						row_pointers = C_UTILS_NULL_POINTER;
					}

					png_destroy_write_struct(&png_ptr, C_UTILS_NULL_POINTER);

					if(fclose(fp))
					{
						const signed int errno_error = errno;
						unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
						c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
						c_utils_size_t prefix_size = strlen("Error in function c_utils_image_save_png, function fclose failed, error code: ");
						c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

						while(error >= 10u)
						{
							error /= 10u;
							error_size++;
						}

						error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

						if(!error_buffer)
						{
							C_UTILS_REPORT_ERROR("Error in function c_utils_image_save_png, function malloc failed");

							return C_UTILS_RESULT_FAILURE;
						}

						sprintf(error_buffer, "Error in function c_utils_image_save_png, function fclose failed, error code: %d", errno_error);

						C_UTILS_REPORT_ERROR(error_buffer);

						free((c_utils_void_t *)error_buffer);
					}

					return C_UTILS_RESULT_FAILURE;
				}

				else
				{
					png_infop info_ptr = png_create_info_struct(png_ptr);

					if(!info_ptr)
					{
						C_UTILS_REPORT_ERROR("Error in function c_utils_image_save_png, function png_create_info_struct failed");

						png_destroy_write_struct(&png_ptr, C_UTILS_NULL_POINTER);

						if(fclose(fp))
						{
							const signed int errno_error = errno;
							unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
							c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
							c_utils_size_t prefix_size = strlen("Error in function c_utils_image_save_png, function fclose failed, error code: ");
							c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

							while(error >= 10u)
							{
								error /= 10u;
								error_size++;
							}

							error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

							if(!error_buffer)
							{
								C_UTILS_REPORT_ERROR("Error in function c_utils_image_save_png, function malloc failed");

								return C_UTILS_RESULT_FAILURE;
							}

							sprintf(error_buffer, "Error in function c_utils_image_save_png, function fclose failed, error code: %d", errno_error);

							C_UTILS_REPORT_ERROR(error_buffer);

							free((c_utils_void_t *)error_buffer);
						}

						return C_UTILS_RESULT_FAILURE;
					}

					else
					{
						const signed int color_type = (image.channels == 4u) ? PNG_COLOR_TYPE_RGBA : PNG_COLOR_TYPE_RGB;

						png_init_io(png_ptr, fp);

						png_set_IHDR(
							png_ptr,
							info_ptr,
							image.width,
							image.height,
							8,
							color_type,
							PNG_INTERLACE_NONE,
							PNG_COMPRESSION_TYPE_DEFAULT,
							PNG_FILTER_TYPE_DEFAULT
						);
						png_write_info(png_ptr, info_ptr);

						row_pointers = (png_bytep *)malloc((c_utils_size_t)image.height * sizeof(*row_pointers));

						if(!row_pointers)
						{
							C_UTILS_REPORT_ERROR("Error in function c_utils_image_save_png, function malloc failed");

							png_destroy_write_struct(&png_ptr, &info_ptr);

							if(fclose(fp))
							{
								const signed int errno_error = errno;
								unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
								c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
								c_utils_size_t prefix_size = strlen("Error in function c_utils_image_save_png, function fclose failed, error code: ");
								c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

								while(error >= 10u)
								{
									error /= 10u;
									error_size++;
								}

								error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

								if(!error_buffer)
								{
									C_UTILS_REPORT_ERROR("Error in function c_utils_image_save_png, function malloc failed");

									return C_UTILS_RESULT_FAILURE;
								}

								sprintf(error_buffer, "Error in function c_utils_image_save_png, function fclose failed, error code: %d", errno_error);

								C_UTILS_REPORT_ERROR(error_buffer);

								free((c_utils_void_t *)error_buffer);
							}

							return C_UTILS_RESULT_FAILURE;
						}

						else
						{
							c_utils_uint32_t y;

							for(y = 0u; y < image.height; y++)
							{
								row_pointers[y] = (c_utils_uint8_t *)image.data.pointer + (c_utils_size_t)y * (c_utils_size_t)image.width * (c_utils_size_t)image.channels;
							}

							png_write_image(png_ptr, row_pointers);
							png_write_end(png_ptr, C_UTILS_NULL_POINTER);

							free((c_utils_void_t *)row_pointers);
							row_pointers = C_UTILS_NULL_POINTER;

							png_destroy_write_struct(&png_ptr, &info_ptr);

							if(fclose(fp))
							{
								const signed int errno_error = errno;
								unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
								c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
								c_utils_size_t prefix_size = strlen("Error in function c_utils_image_save_png, function fclose failed, error code: ");
								c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

								while(error >= 10u)
								{
									error /= 10u;
									error_size++;
								}

								error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

								if(!error_buffer)
								{
									C_UTILS_REPORT_ERROR("Error in function c_utils_image_save_png, function malloc failed");

									return C_UTILS_RESULT_FAILURE;
								}

								sprintf(error_buffer, "Error in function c_utils_image_save_png, function fclose failed, error code: %d", errno_error);

								C_UTILS_REPORT_ERROR(error_buffer);

								free((c_utils_void_t *)error_buffer);
							}
						}
					}
				}
			}
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_image_load_png(const c_utils_char_t *const filename, struct c_utils_image *const image)
{
	if(!filename)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_image_load_png, the filename is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!image)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_image_load_png, the image is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(image->data.pointer)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_image_load_png, the image->data.pointer is not a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		FILE *const fp = fopen(filename, "rb");

		if(!fp)
		{
			const signed int errno_error = errno;
			unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_image_load_png, function fopen failed, error code: ");
			c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

			while(error >= 10u)
			{
				error /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_image_load_png, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_image_load_png, function fopen failed, error code: %d", errno_error);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}

		else
		{
			png_structp png_ptr = png_create_read_struct(
				PNG_LIBPNG_VER_STRING,
				C_UTILS_NULL_POINTER,
				C_UTILS_NULL_POINTER,
				C_UTILS_NULL_POINTER
			);

			if(!png_ptr)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_image_load_png, function png_create_read_struct failed");

				if(fclose(fp))
				{
					const signed int errno_error = errno;
					unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
					c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
					c_utils_size_t prefix_size = strlen("Error in function c_utils_image_load_png, function fclose failed, error code: ");
					c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

					while(error >= 10u)
					{
						error /= 10u;
						error_size++;
					}

					error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

					if(!error_buffer)
					{
						C_UTILS_REPORT_ERROR("Error in function c_utils_image_load_png, function malloc failed");

						return C_UTILS_RESULT_FAILURE;
					}

					sprintf(error_buffer, "Error in function c_utils_image_load_png, function fclose failed, error code: %d", errno_error);

					C_UTILS_REPORT_ERROR(error_buffer);

					free((c_utils_void_t *)error_buffer);
				}

				return C_UTILS_RESULT_FAILURE;
			}

			else
			{
				png_bytep *row_pointers = C_UTILS_NULL_POINTER;

				if(setjmp(png_jmpbuf(png_ptr)))
				{
					if(image->data.pointer)
					{
						if(c_utils_mem_free_and_unregist(&image->data))
						{
							C_UTILS_REPORT_ERROR("Error in function c_utils_image_load_png, function c_utils_mem_free_and_unregist failed");
						}
					}

					if(row_pointers)
					{
						free((c_utils_void_t *)row_pointers);
						row_pointers = C_UTILS_NULL_POINTER;
					}

					png_destroy_read_struct(
						&png_ptr,
						C_UTILS_NULL_POINTER,
						C_UTILS_NULL_POINTER
					);

					if(fclose(fp))
					{
						const signed int errno_error = errno;
						unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
						c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
						c_utils_size_t prefix_size = strlen("Error in function c_utils_image_load_png, function fclose failed, error code: ");
						c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

						while(error >= 10u)
						{
							error /= 10u;
							error_size++;
						}

						error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

						if(!error_buffer)
						{
							C_UTILS_REPORT_ERROR("Error in function c_utils_image_load_png, function malloc failed");

							return C_UTILS_RESULT_FAILURE;
						}

						sprintf(error_buffer, "Error in function c_utils_image_load_png, function fclose failed, error code: %d", errno_error);

						C_UTILS_REPORT_ERROR(error_buffer);

						free((c_utils_void_t *)error_buffer);
					}

					return C_UTILS_RESULT_FAILURE;
				}

				else
				{
					png_infop info_ptr = png_create_info_struct(png_ptr);

					if(!info_ptr)
					{
						C_UTILS_REPORT_ERROR("Error in function c_utils_image_load_png, function png_create_info_struct failed");

						png_destroy_read_struct(
							&png_ptr,
							C_UTILS_NULL_POINTER,
							C_UTILS_NULL_POINTER
						);

						if(fclose(fp))
						{
							const signed int errno_error = errno;
							unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
							c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
							c_utils_size_t prefix_size = strlen("Error in function c_utils_image_load_png, function fclose failed, error code: ");
							c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

							while(error >= 10u)
							{
								error /= 10u;
								error_size++;
							}

							error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

							if(!error_buffer)
							{
								C_UTILS_REPORT_ERROR("Error in function c_utils_image_load_png, function malloc failed");

								return C_UTILS_RESULT_FAILURE;
							}

							sprintf(error_buffer, "Error in function c_utils_image_load_png, function fclose failed, error code: %d", errno_error);

							C_UTILS_REPORT_ERROR(error_buffer);

							free((c_utils_void_t *)error_buffer);
						}

						return C_UTILS_RESULT_FAILURE;
					}

					else
					{
						c_utils_uint8_t channels;
						int bit_depth;
						int color_type;
						png_uint_32 width;
						png_uint_32 height;

						png_init_io(png_ptr, fp);
						png_read_info(png_ptr, info_ptr);

						width = png_get_image_width(png_ptr, info_ptr);
						height = png_get_image_height(png_ptr, info_ptr);
						bit_depth = png_get_bit_depth(png_ptr, info_ptr);
						color_type = png_get_color_type(png_ptr, info_ptr);

						if(color_type == PNG_COLOR_TYPE_PALETTE)
						{
							png_set_palette_to_rgb(png_ptr);
						}

						if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
						{
							png_set_expand_gray_1_2_4_to_8(png_ptr);
						}

						if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
						{
							png_set_tRNS_to_alpha(png_ptr);
						}

						if(bit_depth == 16)
						{
							png_set_strip_16(png_ptr);
						}

						if(color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
						{
							png_set_gray_to_rgb(png_ptr);
						}

						png_read_update_info(png_ptr, info_ptr);

						color_type = png_get_color_type(png_ptr, info_ptr);
						channels = (color_type == PNG_COLOR_TYPE_RGBA) ? 4u : 3u;

						if(c_utils_mem_allocate(&image->data, (c_utils_size_t)width * (c_utils_size_t)height * (c_utils_size_t)channels))
						{
							C_UTILS_REPORT_ERROR("Error in function c_utils_image_load_png, function c_utils_mem_allocate failed");

							png_destroy_read_struct(
								&png_ptr,
								&info_ptr,
								C_UTILS_NULL_POINTER
							);

							if(fclose(fp))
							{
								const signed int errno_error = errno;
								unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
								c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
								c_utils_size_t prefix_size = strlen("Error in function c_utils_image_load_png, function fclose failed, error code: ");
								c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

								while(error >= 10u)
								{
									error /= 10u;
									error_size++;
								}

								error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

								if(!error_buffer)
								{
									C_UTILS_REPORT_ERROR("Error in function c_utils_image_load_png, function malloc failed");

									return C_UTILS_RESULT_FAILURE;
								}

								sprintf(error_buffer, "Error in function c_utils_image_load_png, function fclose failed, error code: %d", errno_error);

								C_UTILS_REPORT_ERROR(error_buffer);

								free((c_utils_void_t *)error_buffer);
							}

							return C_UTILS_RESULT_FAILURE;
						}

						else
						{
							row_pointers = (png_bytep *)malloc((c_utils_size_t)height * sizeof(*row_pointers));

							if(!row_pointers)
							{
								C_UTILS_REPORT_ERROR("Error in function c_utils_image_load_png, function malloc failed");

								if(c_utils_mem_free_and_unregist(&image->data))
								{
									C_UTILS_REPORT_ERROR("Error in function c_utils_image_load_png, function c_utils_mem_free_and_unregist failed");
								}

								png_destroy_read_struct(
									&png_ptr,
									&info_ptr,
									C_UTILS_NULL_POINTER
								);

								if(fclose(fp))
								{
									const signed int errno_error = errno;
									unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
									c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
									c_utils_size_t prefix_size = strlen("Error in function c_utils_image_load_png, function fclose failed, error code: ");
									c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

									while(error >= 10u)
									{
										error /= 10u;
										error_size++;
									}

									error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

									if(!error_buffer)
									{
										C_UTILS_REPORT_ERROR("Error in function c_utils_image_load_png, function malloc failed");

										return C_UTILS_RESULT_FAILURE;
									}

									sprintf(error_buffer, "Error in function c_utils_image_load_png, function fclose failed, error code: %d", errno_error);

									C_UTILS_REPORT_ERROR(error_buffer);

									free((c_utils_void_t *)error_buffer);
								}

								return C_UTILS_RESULT_FAILURE;
							}

							else
							{
								c_utils_uint32_t y;

								for(y = 0u; y < height; y++)
								{
									row_pointers[y] = (c_utils_uint8_t *)image->data.pointer + y * png_get_rowbytes(png_ptr, info_ptr);
								}

								png_read_image(png_ptr, row_pointers);

								free((c_utils_void_t *)row_pointers);
								row_pointers = C_UTILS_NULL_POINTER;

								png_destroy_read_struct(
									&png_ptr,
									&info_ptr,
									C_UTILS_NULL_POINTER
								);

								if(fclose(fp))
								{
									const signed int errno_error = errno;
									unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
									c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
									c_utils_size_t prefix_size = strlen("Error in function c_utils_image_load_png, function fclose failed, error code: ");
									c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

									while(error >= 10u)
									{
										error /= 10u;
										error_size++;
									}

									error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

									if(!error_buffer)
									{
										C_UTILS_REPORT_ERROR("Error in function c_utils_image_load_png, function malloc failed");

										return C_UTILS_RESULT_FAILURE;
									}

									sprintf(error_buffer, "Error in function c_utils_image_load_png, function fclose failed, error code: %d", errno_error);

									C_UTILS_REPORT_ERROR(error_buffer);

									free((c_utils_void_t *)error_buffer);
								}

								image->width = (c_utils_uint32_t)width;
								image->height = (c_utils_uint32_t)height;
								image->channels = channels;
							}
						}
					}
				}
			}
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_image_save_jpg(const c_utils_char_t *const filename, struct c_utils_image image, c_utils_int8_t quality)
{
	if(!filename)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_image_save_jpg, the filename is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!image.data.pointer)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_image_save_jpg, the image.data.pointer is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(image.channels != 3u && image.channels != 4u)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_image_save_jpg, the image.channels != 3u && image.channels != 4u");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!image.width || !image.height)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_image_save_jpg, the image.width == 0u || image.height == 0u");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		FILE *const fp = fopen(filename, "wb");

		if(!fp)
		{
			const signed int errno_error = errno;
			unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_image_save_jpg, function fopen failed, error code: ");
			c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

			while(error >= 10u)
			{
				error /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_image_save_jpg, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_image_save_jpg, function fopen failed, error code: %d", errno_error);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}

		else
		{
			struct jpeg_compress_struct cinfo;
			struct c_utils_jpg_error_manager jerr;
			JSAMPROW row_pointer;
			c_utils_int8_t free_rgb = 0;
			c_utils_uint8_t *rgb_data;

			if(image.channels == 4)
			{
				rgb_data = (c_utils_uint8_t *)malloc((c_utils_size_t)image.width * (c_utils_size_t)image.height * 3u);

				if(!rgb_data)
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_image_save_jpg, function malloc failed");

					if(fclose(fp))
					{
						const signed int errno_error = errno;
						unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
						c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
						c_utils_size_t prefix_size = strlen("Error in function c_utils_image_save_jpg, function fclose failed, error code: ");
						c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

						while(error >= 10u)
						{
							error /= 10u;
							error_size++;
						}

						error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

						if(!error_buffer)
						{
							C_UTILS_REPORT_ERROR("Error in function c_utils_image_save_jpg, function malloc failed");

							return C_UTILS_RESULT_FAILURE;
						}

						sprintf(error_buffer, "Error in function c_utils_image_save_jpg, function fclose failed, error code: %d", errno_error);

						C_UTILS_REPORT_ERROR(error_buffer);

						free((c_utils_void_t *)error_buffer);
					}

					return C_UTILS_RESULT_FAILURE;
				}

				else
				{
					c_utils_size_t y;
					c_utils_size_t x;
					c_utils_size_t width_size = (c_utils_size_t)image.width;

					for(y = 0u; y < (c_utils_size_t)image.height; y++)
					{
						for(x = 0u; x < width_size; x++)
						{
							c_utils_size_t idx_dst = (y * width_size + x) * 3u;
							c_utils_size_t idx_src = (y * width_size + x) * 4u;

							rgb_data[idx_dst + 0u] = ((c_utils_uint8_t *)image.data.pointer)[idx_src + 0u];
							rgb_data[idx_dst + 1u] = ((c_utils_uint8_t *)image.data.pointer)[idx_src + 1u];
							rgb_data[idx_dst + 2u] = ((c_utils_uint8_t *)image.data.pointer)[idx_src + 2u];
						}
					}

					free_rgb = 1;
				}
			}

			else
			{
				rgb_data = (c_utils_uint8_t *)image.data.pointer;
			}

			cinfo.err = jpeg_std_error(&jerr.pub);
			jerr.pub.error_exit = c_utils_jpg_error_exit;

			if(setjmp(jerr.setjmp_buffer))
			{
				jpeg_destroy_compress(&cinfo);

				if(free_rgb == 1)
				{
					free((c_utils_void_t *)rgb_data);
					rgb_data = C_UTILS_NULL_POINTER;
				}

				if(fclose(fp))
				{
					const signed int errno_error = errno;
					unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
					c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
					c_utils_size_t prefix_size = strlen("Error in function c_utils_image_save_jpg, function fclose failed, error code: ");
					c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

					while(error >= 10u)
					{
						error /= 10u;
						error_size++;
					}

					error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

					if(!error_buffer)
					{
						C_UTILS_REPORT_ERROR("Error in function c_utils_image_save_jpg, function malloc failed");

						return C_UTILS_RESULT_FAILURE;
					}

					sprintf(error_buffer, "Error in function c_utils_image_save_jpg, function fclose failed, error code: %d", errno_error);

					C_UTILS_REPORT_ERROR(error_buffer);

					free((c_utils_void_t *)error_buffer);
				}

				return C_UTILS_RESULT_FAILURE;
			}

			jpeg_create_compress(&cinfo);
			jpeg_stdio_dest(&cinfo, fp);

			cinfo.image_width      = image.width;
			cinfo.image_height     = image.height;
			cinfo.input_components = 3;
			cinfo.in_color_space   = JCS_RGB;

			if(quality < 0)
			{
				quality = 0;
			}

			if(quality > 100)
			{
				quality = 100;
			}

			jpeg_set_defaults(&cinfo);
			jpeg_set_quality(&cinfo, (int)quality, TRUE);
			jpeg_start_compress(&cinfo, TRUE);

			while(cinfo.next_scanline < cinfo.image_height)
			{
				row_pointer = rgb_data + (c_utils_size_t)cinfo.next_scanline * (c_utils_size_t)image.width * 3u;
				jpeg_write_scanlines(&cinfo, &row_pointer, 1);
			}

			jpeg_finish_compress(&cinfo);
			jpeg_destroy_compress(&cinfo);

			if(free_rgb)
			{
				free((c_utils_void_t *)rgb_data);
				rgb_data = C_UTILS_NULL_POINTER;
			}

			if(fclose(fp))
			{
				const signed int errno_error = errno;
				unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
				c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
				c_utils_size_t prefix_size = strlen("Error in function c_utils_image_save_jpg, function fclose failed, error code: ");
				c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

				while(error >= 10u)
				{
					error /= 10u;
					error_size++;
				}

				error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

				if(!error_buffer)
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_image_save_jpg, function malloc failed");

					return C_UTILS_RESULT_FAILURE;
				}

				sprintf(error_buffer, "Error in function c_utils_image_save_jpg, function fclose failed, error code: %d", errno_error);

				C_UTILS_REPORT_ERROR(error_buffer);

				free((c_utils_void_t *)error_buffer);

				return C_UTILS_RESULT_FAILURE;
			}
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_image_load_jpg(const c_utils_char_t *const filename, struct c_utils_image *const image)
{
	if(!filename)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_image_load_jpg, the filename is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!image)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_image_load_jpg, the image is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(image->data.pointer)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_image_load_jpg, the image->data.pointer is not a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		FILE *const fp = fopen(filename, "rb");

		if(!fp)
		{
			const signed int errno_error = errno;
			unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_image_load_jpg, function fopen failed, error code: ");
			c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

			while(error >= 10u)
			{
				error /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((error_size + prefix_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_image_load_jpg, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_image_load_jpg, function fopen failed, error code: %d", errno_error);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}

		else
		{
			struct c_utils_jpg_error_manager jerr;
			struct jpeg_decompress_struct cinfo;

			cinfo.err = jpeg_std_error(&jerr.pub);
			jerr.pub.error_exit = c_utils_jpg_error_exit;

			if(setjmp(jerr.setjmp_buffer))
			{
				jpeg_destroy_decompress(&cinfo);

				if(image->data.pointer)
				{
					if(c_utils_mem_free_and_unregist(&image->data))
					{
						C_UTILS_REPORT_ERROR("Error in function c_utils_image_load_jpg, function c_utils_mem_free_and_unregist failed");
					}
				}

				if(fclose(fp))
				{
					const signed int errno_error = errno;
					unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
					c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
					c_utils_size_t prefix_size = strlen("Error in function c_utils_image_load_jpg, function fclose failed, error code: ");
					c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

					while(error >= 10u)
					{
						error /= 10u;
						error_size++;
					}

					error_buffer = (c_utils_char_t *)malloc((error_size + prefix_size + 1u) * sizeof(*error_buffer));

					if(!error_buffer)
					{
						C_UTILS_REPORT_ERROR("Error in function c_utils_image_load_jpg, function malloc failed");

						return C_UTILS_RESULT_FAILURE;
					}

					sprintf(error_buffer, "Error in function c_utils_image_load_jpg, function fclose failed, error code: %d", errno_error);

					C_UTILS_REPORT_ERROR(error_buffer);

					free((c_utils_void_t *)error_buffer);
				}

				return C_UTILS_RESULT_FAILURE;
			}

			jpeg_create_decompress(&cinfo);
			jpeg_stdio_src(&cinfo, fp);
			jpeg_read_header(&cinfo, TRUE);
			jpeg_start_decompress(&cinfo);

			image->width = (c_utils_uint32_t)cinfo.output_width;
			image->height = (c_utils_uint32_t)cinfo.output_height;
			image->channels = (c_utils_uint8_t)cinfo.output_components;

			if(c_utils_mem_allocate(&image->data, (c_utils_size_t)image->width * (c_utils_size_t)image->height * (c_utils_size_t)image->channels))
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_image_load_jpg, function c_utils_mem_allocate failed");

				jpeg_destroy_decompress(&cinfo);

				if(fclose(fp))
				{
					const signed int errno_error = errno;
					unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
					c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
					c_utils_size_t prefix_size = strlen("Error in function c_utils_image_load_jpg, function fclose failed, error code: ");
					c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

					while(error >= 10u)
					{
						error /= 10u;
						error_size++;
					}

					error_buffer = (c_utils_char_t *)malloc((error_size + prefix_size + 1u) * sizeof(*error_buffer));

					if(!error_buffer)
					{
						C_UTILS_REPORT_ERROR("Error in function c_utils_image_load_jpg, function malloc failed");

						return C_UTILS_RESULT_FAILURE;
					}

					sprintf(error_buffer, "Error in function c_utils_image_load_jpg, function fclose failed, error code: %d", errno_error);

					C_UTILS_REPORT_ERROR(error_buffer);

					free((c_utils_void_t *)error_buffer);
				}

				return C_UTILS_RESULT_FAILURE;
			}

			else
			{
				c_utils_size_t row_stride = (c_utils_size_t)image->width * (c_utils_size_t)image->channels;

				while(cinfo.output_scanline < cinfo.output_height)
				{
					JSAMPROW row_pointer = (c_utils_uint8_t *)image->data.pointer + (c_utils_size_t)cinfo.output_scanline * row_stride;
					jpeg_read_scanlines(&cinfo, &row_pointer, 1);
				}

				jpeg_finish_decompress(&cinfo);
				jpeg_destroy_decompress(&cinfo);

				if(fclose(fp))
				{
					const signed int errno_error = errno;
					unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
					c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
					c_utils_size_t prefix_size = strlen("Error in function c_utils_image_load_jpg, function fclose failed, error code: ");
					c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

					while(error >= 10u)
					{
						error /= 10u;
						error_size++;
					}

					error_buffer = (c_utils_char_t *)malloc((error_size + prefix_size + 1u) * sizeof(*error_buffer));

					if(!error_buffer)
					{
						C_UTILS_REPORT_ERROR("Error in function c_utils_image_load_jpg, function malloc failed");

						return C_UTILS_RESULT_FAILURE;
					}

					sprintf(error_buffer, "Error in function c_utils_image_load_jpg, function fclose failed, error code: %d", errno_error);

					C_UTILS_REPORT_ERROR(error_buffer);

					free((c_utils_void_t *)error_buffer);
				}
			}
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_image_flip_vertical(struct c_utils_image *const image)
{
	if(!image)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_image_flip_vertical, the image is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!image->data.pointer)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_image_flip_vertical, the image->data.pointer is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!image->height || !image->width)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_image_flip_vertical, the image->height == 0u || image->width == 0u");

		return C_UTILS_RESULT_FAILURE;
	}

	if(image->channels != 3u && image->channels != 4u)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_image_flip_vertical, the image->channels != 3u && image->channels != 4u");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		c_utils_size_t row_size = (c_utils_size_t)image->width * (c_utils_size_t)image->channels;
		c_utils_uint8_t *const temp = (c_utils_uint8_t *)malloc(row_size);

		if(!temp)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_image_flip_vertical, function malloc failed");

			return C_UTILS_RESULT_FAILURE;
		}

		else
		{
			c_utils_uint8_t *top;
			c_utils_uint8_t *bottom;
			c_utils_uint32_t i;

			for(i = 0u; i < image->height / 2u; i++)
			{
				top = (c_utils_uint8_t *)image->data.pointer + (c_utils_size_t)i * row_size;
				bottom = (c_utils_uint8_t *)image->data.pointer + (c_utils_size_t)(image->height - 1u - i) * row_size;

				memcpy((c_utils_void_t *)temp, (c_utils_void_t *)top, row_size);
				memcpy((c_utils_void_t *)top, (c_utils_void_t *)bottom, row_size);
				memcpy((c_utils_void_t *)bottom, (c_utils_void_t *)temp, row_size);
			}

			free((c_utils_void_t *)temp);
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_image_flip_horizontal(struct c_utils_image *const image)
{
	if(!image)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_image_flip_horizontal, the image is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!image->data.pointer)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_image_flip_horizontal, the image->data.pointer is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!image->height || !image->width)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_image_flip_horizontal, the image->height == 0u || image->width == 0u");

		return C_UTILS_RESULT_FAILURE;
	}

	if(image->channels != 3u && image->channels != 4u)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_image_flip_horizontal, the image->channels != 3u && image->channels != 4u");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		c_utils_uint8_t *const data = (c_utils_uint8_t *)image->data.pointer;
		const c_utils_size_t channels = (c_utils_size_t)image->channels;
		const c_utils_size_t row_size = (c_utils_size_t)image->width * channels;
		c_utils_uint8_t temp;
		c_utils_uint32_t x;
		c_utils_uint32_t y;
		c_utils_size_t c;

		for(y = 0u; y < image->height; y++)
		{
			c_utils_uint8_t *const row = data + (c_utils_size_t)y * row_size;

			for(x = 0u; x < image->width / 2u; x++)
			{
				c_utils_uint8_t *const left = row + (c_utils_size_t)x * channels;
				c_utils_uint8_t *const right = row + (c_utils_size_t)(image->width - 1u - x) * channels;

				for(c = 0u; c < channels; c++)
				{
					temp = left[c];
					left[c] = right[c];
					right[c] = temp;
				}
			}
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif
