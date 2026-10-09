/*************************/
/* Library importations: */
/*************************/

#include <stdio.h>
#ifndef C_UTILS_COMPILE
#include "../../include/C-Utils/rnd-utls.h"
#include "../../include/C-Utils/err-utls.h"
#else
#include "C-Utils/rnd-utls.h"
#include "C-Utils/err-utls.h"
#endif
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

/****************************/
/* Global static variables: */
/****************************/

static c_utils_bool_t c_utils_random_is_initialized = C_UTILS_FALSE;
#if defined(_WIN32) || defined(_WIN64)
typedef BOOL (WINAPI *ProcessPrng_pointer)(PBYTE pbData, SIZE_T cbData);
static HMODULE hMod = C_UTILS_NULL_POINTER;
static ProcessPrng_pointer ProcessPrng = C_UTILS_NULL_POINTER;
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

C_UTILS_API c_utils_result_t c_utils_random_initialize(c_utils_void_t)
{
	if(c_utils_random_is_initialized)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_random_initialize, C-Utils random is already initialized");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		hMod = LoadLibraryA("bcryptprimitives.dll");

		if(!hMod)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_random_initialize, could not load the bcryptprimitives.dll library");

			return C_UTILS_RESULT_FAILURE;
		}

		ProcessPrng = (ProcessPrng_pointer)GetProcAddress(hMod, "ProcessPrng");

		if(!ProcessPrng)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_random_initialize, could not get the ProcessPrng function pointer");

			if(!FreeLibrary(hMod))
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_random_initialize, function FreeLibrary failed");

				return C_UTILS_RESULT_FAILURE;
			}

			return C_UTILS_RESULT_FAILURE;
		}
#endif

		c_utils_random_is_initialized = C_UTILS_TRUE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_random_buffer(c_utils_uint8_t *const buffer, c_utils_size_t size)
{
	if(!c_utils_random_is_initialized)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_random_buffer, C-Utils random is not initialized");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!buffer)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_random_buffer, the buffer is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		ProcessPrng(buffer, size);
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		FILE *const dev_urandom = fopen("/dev/urandom", "rb");

		if(!dev_urandom)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_random_integer, function fopen failed");

			return C_UTILS_RESULT_FAILURE;
		}

		else
		{
			c_utils_size_t total = 0;

			while(total < size)
			{
				c_utils_size_t n = fread((void *)&buffer[total], 1u, size - total, dev_urandom);

				if(n == 0u)
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_random_integer, function fread failed");

					if(fclose(dev_urandom) != 0)
					{
						C_UTILS_REPORT_ERROR("Error in function c_utils_random_integer, function fclose failed");
					}

					return C_UTILS_RESULT_FAILURE;
				}

				total += n;
			}

			if(fclose(dev_urandom) != 0)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_random_integer, function fclose failed");

				return C_UTILS_RESULT_FAILURE;
			}
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_random_integer(c_utils_int32_t minimum, c_utils_int32_t maximum, c_utils_int32_t *const output)
{
	if(!c_utils_random_is_initialized)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_random_integer, C-Utils random is not initialized");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!output)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_random_integer, the output is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(minimum >= maximum)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_random_integer, the minimum is greater than or iqual to the maximum");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		c_utils_uint32_t range = (c_utils_uint32_t)((c_utils_uint32_t)maximum - (c_utils_uint32_t)minimum) + 1u;
		c_utils_uint32_t value = 0u;

		if(c_utils_random_buffer((c_utils_uint8_t *)&value, sizeof(value)))
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_random_integer, function c_utils_random_buffer failed");

			return C_UTILS_RESULT_FAILURE;
		}

		if(range == 0u)
		{
			*output = (c_utils_int32_t)value;
		}

		else
		{
			c_utils_uint32_t limit = C_UTILS_UINT32_MAX - (C_UTILS_UINT32_MAX % range);

			while(value >= limit)
			{
				if(c_utils_random_buffer((c_utils_uint8_t *)&value, sizeof(value)))
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_random_integer, function c_utils_random_buffer failed");

					return C_UTILS_RESULT_FAILURE;
				}
			}

			*output = minimum + (c_utils_int32_t)(value % range);
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_random_terminate(c_utils_void_t)
{
	if(!c_utils_random_is_initialized)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_terminate, C-Utils random is not initialized");

		return C_UTILS_RESULT_FAILURE;
	}

#if defined(_WIN32) || defined(_WIN64)
	if(!FreeLibrary(hMod))
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_terminate, function FreeLibrary failed");

		return C_UTILS_RESULT_FAILURE;
	}
#endif

	c_utils_random_is_initialized = C_UTILS_FALSE;

	return C_UTILS_RESULT_SUCCESS;
}

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif
