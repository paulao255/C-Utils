/* Importations: */
#include "image-utils.h"
#include "c-utils.h"
#include <png.h>
#include <jpeglib.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* Import C to C++: */
#ifdef __cplusplus
extern "C"
{
#endif

c_utils_int16_t c_utils_save_png(const c_utils_char_t *const filename, struct c_utils_image image)
{
	if(!filename || !image.data || (image.channels != 3 && image.channels != 4))
	{
		fprintf(stderr, "Error in function c_utils_save_png (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	else
	{
		FILE *const fp = fopen(filename, "wb");

		if(!fp)
		{
			return C_UTILS_FAILURE;
		}

		else
		{
			png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, (void *)0, (void *)0, (void *)0);

			if(!png_ptr)
			{
				fclose(fp);

				return C_UTILS_FAILURE;
			}

			else
			{
				png_infop info_ptr = png_create_info_struct(png_ptr);

				if(!info_ptr)
				{
					png_destroy_write_struct(&png_ptr, (png_infopp)(void *)0);
					fclose(fp);

					return C_UTILS_FAILURE;
				}

				if(setjmp(png_jmpbuf(png_ptr)))
				{
					png_destroy_write_struct(&png_ptr, &info_ptr);
					fclose(fp);

					return C_UTILS_FAILURE;
				}

				else
				{
					png_bytep *row_pointers;
					int color_type;

					png_init_io(png_ptr, fp);

					color_type = (image.channels == 4) ? PNG_COLOR_TYPE_RGBA : PNG_COLOR_TYPE_RGB;

					png_set_IHDR(png_ptr, info_ptr, image.width, image.height, 8, color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
					png_write_info(png_ptr, info_ptr);

					row_pointers = (png_bytep *)malloc((size_t)image.height * sizeof(png_bytep));

					if(!row_pointers)
					{
						png_destroy_write_struct(&png_ptr, &info_ptr);
						fclose(fp);

						return C_UTILS_FAILURE;
					}

					else
					{
						c_utils_uint32_t y;

						for(y = 0U; y < image.height; y++)
						{
							*(row_pointers + y) = image.data + y * image.width * image.channels;
						}

						png_write_image(png_ptr, row_pointers);
						png_write_end(png_ptr, (png_infop)(void *)0);

						free(row_pointers);
						png_destroy_write_struct(&png_ptr, &info_ptr);
						fclose(fp);
					}
				}
			}
		}
	}

	return C_UTILS_SUCCESS;
}

c_utils_int16_t c_utils_load_png(const c_utils_char_t *const filename, struct c_utils_image *const image)
{
	if(!filename)
	{
		fprintf(stderr, "Error in function c_utils_load_png (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(!image)
	{
		fprintf(stderr, "Error in function c_utils_load_png (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if((*image).data)
	{
		fprintf(stderr, "Error in function c_utils_load_png (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	else
	{
		FILE *fp = fopen(filename, "rb");

		if(!fp)
		{
			return C_UTILS_FAILURE;
		}

		else
		{
			png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, (void *)0, (void *)0, (void *)0);

			if(!png_ptr)
			{
				fclose(fp);

				return C_UTILS_FAILURE;
			}

			else
			{
				png_infop info_ptr = png_create_info_struct(png_ptr);

				if(!info_ptr)
				{
					png_destroy_read_struct(&png_ptr, (png_infopp)(void *)0, (png_infopp)(void *)0);
					fclose(fp);

					return C_UTILS_FAILURE;
				}

				if(setjmp(png_jmpbuf(png_ptr)))
				{
					png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)(void *)0);
					fclose(fp);

					return C_UTILS_FAILURE;
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
					channels   = (c_utils_uint8_t)((color_type == PNG_COLOR_TYPE_RGBA) ? 4 : 3);

					(*image).data = (c_utils_uint8_t *)malloc((size_t)width * (size_t)height * (size_t)channels);

					if(!(*image).data)
					{
						png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)(void *)0);
						fclose(fp);

						return C_UTILS_FAILURE;
					}

					else
					{
						png_bytep *row_pointers = (png_bytep *)malloc((size_t)height * sizeof(png_bytep));

						if(!row_pointers)
						{
							free((*image).data);
							(*image).data = (void *)0;
							png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)(void *)0);
							fclose(fp);

							return C_UTILS_FAILURE;
						}

						else
						{
							c_utils_uint32_t y;

							for(y = 0U; y < height; y++)
							{
								*(row_pointers + y) = (*image).data + y * width * channels;
							}

							png_read_image(png_ptr, row_pointers);

							free(row_pointers);
							png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)(void *)0);
							fclose(fp);

							(*image).width = (c_utils_uint32_t)width;
							(*image).height = (c_utils_uint32_t)height;
							(*image).channels = channels;

							if(c_utils_regist_address_to_free((void *)(*image).data) != C_UTILS_SUCCESS)
							{
								free((void *)(*image).data);
								(*image).data = (void *)0;

								fprintf(stderr, "Error in function c_utils_regist_address_to_free (File: %s, Line: %d)...\n", __FILE__, __LINE__);

								return C_UTILS_FAILURE;
							}
						}
					}
				}
			}
		}
	}

	return C_UTILS_SUCCESS;
}

c_utils_int16_t c_utils_save_jpg(const c_utils_char_t *const filename, struct c_utils_image image, c_utils_int8_t quality)
{
	if(!filename || !image.data || (image.channels != 3 && image.channels != 4))
	{
		fprintf(stderr, "Error in function c_utils_save_jpg (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	else
	{
		FILE *fp = fopen(filename, "wb");

		if(!fp)
		{
			return C_UTILS_FAILURE;
		}

		else
		{
			struct jpeg_compress_struct cinfo;
			struct jpeg_error_mgr jerr;
			JSAMPROW row_pointer;
			c_utils_uint8_t *rgb_data;
			c_utils_int8_t free_rgb = 0;

			if(image.channels == 4)
			{
				rgb_data = (c_utils_uint8_t *)malloc((size_t)image.width * (size_t)image.height * 3u);

				if(!rgb_data)
				{
					fclose(fp);

					return C_UTILS_FAILURE;
				}

				else
				{
					c_utils_uint32_t y;
					c_utils_uint32_t x;

					for(y = 0; y < image.height; y++)
					{
						for(x = 0; x < image.width; x++)
						{
							*(rgb_data + ((y * image.width + x) * 3u + 0u)) = *(image.data + ((y * image.width + x) * 4u + 0u));
							*(rgb_data + ((y * image.width + x) * 3u + 1u)) = *(image.data + ((y * image.width + x) * 4u + 1u));
							*(rgb_data + ((y * image.width + x) * 3u + 2u)) = *(image.data + ((y * image.width + x) * 4u + 2u));
						}
					}

					free_rgb = 1;
				}
			}

			else
			{
				rgb_data = image.data;
			}

			cinfo.err = jpeg_std_error(&jerr);
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
				row_pointer = rgb_data + cinfo.next_scanline * image.width * 3u;
				jpeg_write_scanlines(&cinfo, &row_pointer, 1);
			}

			jpeg_finish_compress(&cinfo);
			jpeg_destroy_compress(&cinfo);

			if(free_rgb)
			{
				free(rgb_data);
			}

			fclose(fp);
		}
	}

	return C_UTILS_SUCCESS;
}

c_utils_int16_t c_utils_load_jpg(const c_utils_char_t *const filename, struct c_utils_image *const image)
{
	if(!filename)
	{
		fprintf(stderr, "Error in function c_utils_load_jpg (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(!image)
	{
		fprintf(stderr, "Error in function c_utils_load_jpg (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if((*image).data)
	{
		fprintf(stderr, "Error in function c_utils_load_jpg (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	else
	{
		FILE *const fp = fopen(filename, "rb");

		if(!fp)
		{
			return C_UTILS_FAILURE;
		}

		else
		{
			struct jpeg_decompress_struct cinfo;
			struct jpeg_error_mgr jerr;

			cinfo.err = jpeg_std_error(&jerr);
			jpeg_create_decompress(&cinfo);
			jpeg_stdio_src(&cinfo, fp);
			jpeg_read_header(&cinfo, TRUE);
			jpeg_start_decompress(&cinfo);

			(*image).width = (c_utils_uint32_t)cinfo.output_width;
			(*image).height = (c_utils_uint32_t)cinfo.output_height;
			(*image).channels = (c_utils_uint8_t)cinfo.output_components;
			(*image).data = (c_utils_uint8_t *)malloc((size_t)(*image).width * (size_t)(*image).height * (size_t)(*image).channels);

			if(!(*image).data)
			{
				jpeg_destroy_decompress(&cinfo);
				fclose(fp);

				return C_UTILS_FAILURE;
			}

			if(c_utils_regist_address_to_free((void *)(*image).data) != C_UTILS_SUCCESS)
			{
				jpeg_destroy_decompress(&cinfo);
				fclose(fp);

				free((void *)(*image).data);
				(*image).data = (void *)0;

				fprintf(stderr, "Error in function c_utils_regist_address_to_free (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_FAILURE;
			}

			else
			{
				JSAMPROW row_pointer;
				c_utils_uint32_t row_stride = (*image).width * (*image).channels;

				while(cinfo.output_scanline < cinfo.output_height)
				{
					row_pointer = (*image).data + cinfo.output_scanline * row_stride;
					jpeg_read_scanlines(&cinfo, &row_pointer, 1);
				}

				jpeg_finish_decompress(&cinfo);
				jpeg_destroy_decompress(&cinfo);
				fclose(fp);
			}
		}
	}

	return C_UTILS_SUCCESS;
}

c_utils_int16_t c_utils_image_flip_vertical(struct c_utils_image *const image)
{
	if(!image || !(*image).data)
	{
		return C_UTILS_FAILURE;
	}

	else
	{
		c_utils_uint32_t row_size = (*image).width * (*image).channels;
		c_utils_uint8_t *temp = (c_utils_uint8_t *)malloc((size_t)row_size);

		if(!temp)
		{
			return C_UTILS_FAILURE;
		}

		else
		{
			c_utils_uint8_t *top;
			c_utils_uint8_t *bottom;
			c_utils_uint32_t i;

			for(i = 0; i < (*image).height / 2u; i++)
			{
				top = (*image).data + i * row_size;
				bottom = (*image).data + ((*image).height - 1u - i) * row_size;

				memcpy(temp,   top,    row_size);
				memcpy(top,    bottom, row_size);
				memcpy(bottom, temp,   row_size);
			}

			free(temp);
		}
	}

	return C_UTILS_SUCCESS;
}

/* End C to C++ importation: */
#ifdef __cplusplus
}
#endif
