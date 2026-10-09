/*************************/
/* Library importations: */
/*************************/

#ifndef C_UTILS_COMPILE
#include "../../include/C-Utils/dl-utils.h"
#include "../../include/C-Utils/err-utls.h"
#else
#include "C-Utils/dl-utils.h"
#include "C-Utils/err-utls.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
#include <dlfcn.h>
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

C_UTILS_API c_utils_result_t c_utils_dynamic_library_open(const c_utils_char_t *const path, c_utils_dynamic_library_t *const output)
{
	if(!path)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_dynamic_library_open, the path is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!output)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_dynamic_library_open, the output is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		c_utils_dynamic_library_t library;

		SetLastError(0);

		library = LoadLibraryA(path);

		if(!library)
		{
			const DWORD error_code = GetLastError();
			DWORD value = error_code;
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_dynamic_library_open, function LoadLibraryA failed, error code: ");
			c_utils_size_t error_code_size = 1u;

			while(value >= 10)
			{
				value /= 10;
				error_code_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_code_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_dynamic_library_open, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_dynamic_library_open, function LoadLibraryA failed, error code: %lu", (unsigned long)error_code);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		c_utils_dynamic_library_t library = dlopen(path, RTLD_LAZY);

		if(!library)
		{
			const c_utils_char_t *const error = dlerror();
			const c_utils_char_t *const safe_error = error ? error : "Unknown error";
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_dynamic_library_open, function dlopen failed, error: ");
			c_utils_size_t error_size = strlen(safe_error);

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_dynamic_library_open, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_dynamic_library_open, function dlopen failed, error: %s", safe_error);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
#endif

		*output = library;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_dynamic_library_load_function(const c_utils_dynamic_library_t library, const c_utils_char_t *const name, c_utils_dynamic_library_function_t *const output)
{
	if(!library)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_dynamic_library_load_function, the library is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!name)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_dynamic_library_load_function, the name is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!output)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_dynamic_library_load_function, the output is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		c_utils_dynamic_library_function_t function;

#if defined(_WIN32) || defined(_WIN64)
		SetLastError(0);

		function = GetProcAddress(library, name);

		if(!function)
		{
			const DWORD error_code = GetLastError();
			DWORD value = error_code;
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_dynamic_library_load_function, function GetProcAddress failed, error code: ");
			c_utils_size_t error_code_size = 1u;

			while(value >= 10)
			{
				value /= 10;
				error_code_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_code_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_dynamic_library_load_function, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_dynamic_library_load_function, function GetProcAddress failed, error code: %lu", (unsigned long)error_code);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		const c_utils_char_t *error;

		dlerror();

		*(c_utils_void_t **)&function = dlsym(library, name);
		error = dlerror();

		if(error || !function)
		{
			const c_utils_char_t *const safe_error = error ? error : "Unknown error";
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_dynamic_library_load_function, function dlsym failed, error: ");
			c_utils_size_t error_size = strlen(safe_error);

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_dynamic_library_load_function, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_dynamic_library_load_function, function dlsym failed, error: %s", safe_error);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
#endif

		*output = function;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_dynamic_library_close(const c_utils_dynamic_library_t library)
{
	if(!library)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_dynamic_library_close, the library is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

#if defined(_WIN32) || defined(_WIN64)
	SetLastError(0);

	if(!FreeLibrary(library))
	{
		const DWORD error_code = GetLastError();
		DWORD value = error_code;
		c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
		c_utils_size_t prefix_size = strlen("Error in function c_utils_dynamic_library_close, function FreeLibrary failed, error code: ");
		c_utils_size_t error_code_size = 1u;

		while(value >= 10)
		{
			value /= 10;
			error_code_size++;
		}

		error_buffer = (c_utils_char_t *)malloc((prefix_size + error_code_size + 1u) * sizeof(*error_buffer));

		if(!error_buffer)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_dynamic_library_close, function malloc failed");

			return C_UTILS_RESULT_FAILURE;
		}

		sprintf(error_buffer, "Error in function c_utils_dynamic_library_close, function FreeLibrary failed, error code: %lu", (unsigned long)error_code);

		C_UTILS_REPORT_ERROR(error_buffer);

		free((c_utils_void_t *)error_buffer);

		return C_UTILS_RESULT_FAILURE;
	}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	if(dlclose(library))
	{
		const c_utils_char_t *const error = dlerror();
		const c_utils_char_t *const safe_error = error ? error : "Unknown error";
		c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
		c_utils_size_t prefix_size = strlen("Error in function c_utils_dynamic_library_close, function dlclose failed, error: ");
		c_utils_size_t error_size = strlen(safe_error);

		error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

		if(!error_buffer)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_dynamic_library_close, function malloc failed");

			return C_UTILS_RESULT_FAILURE;
		}

		sprintf(error_buffer, "Error in function c_utils_dynamic_library_close, function dlclose failed, error: %s", safe_error);

		C_UTILS_REPORT_ERROR(error_buffer);

		free((c_utils_void_t *)error_buffer);

		return C_UTILS_RESULT_FAILURE;
	}
#endif

	return C_UTILS_RESULT_SUCCESS;
}

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif
