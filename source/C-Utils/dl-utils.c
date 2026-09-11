/*************************/
/* Library importations: */
/*************************/

#ifndef C_UTILS_COMPILE
#include "../../include/C-Utils/dl-utils.h"
#else
#include "C-Utils/dl-utils.h"
#endif
#include <stdio.h>
#if defined(_WIN32) || defined(_WIN64)
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
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
		fprintf(stderr, "Error in function c_utils_dynamic_library_open, the path is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!output)
	{
		fprintf(stderr, "Error in function c_utils_dynamic_library_open, the output is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

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
			fprintf(stderr, "Error in function c_utils_dynamic_library_open, function LoadLibraryA (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %u\n", (c_utils_uint32_t)GetLastError());

			return C_UTILS_RESULT_FAILURE;
		}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		c_utils_dynamic_library_t library = dlopen(path, RTLD_LAZY);

		if(!library)
		{
			fprintf(stderr, "Error in function c_utils_dynamic_library_open, function dlopen (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %s\n", dlerror());

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
		fprintf(stderr, "Error in function c_utils_dynamic_library_load_function, the library is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!name)
	{
		fprintf(stderr, "Error in function c_utils_dynamic_library_load_function, the name is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!output)
	{
		fprintf(stderr, "Error in function c_utils_dynamic_library_load_function, the output is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

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
			fprintf(stderr, "Error in function c_utils_dynamic_library_load_function, function GetProcAddress (File: %s, Line: %d)...\n", __FILE__, __FILE__);
			fprintf(stderr, "Error code: %u\n", (c_utils_uint32_t)GetLastError());

			return C_UTILS_RESULT_FAILURE;
		}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		const char *error_string;

		dlerror();

		*(void **)&function = dlsym(library, name);
		error_string = dlerror();

		if(error_string || !function)
		{
			fprintf(stderr, "Error in function c_utils_dynamic_library_load_function, function dlsym (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %s\n", error_string ? error_string : "Unknown error");

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
		fprintf(stderr, "Error in function c_utils_dynamic_library_close, the library is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

#if defined(_WIN32) || defined(_WIN64)
	SetLastError(0);

	if(!FreeLibrary(library))
	{
		fprintf(stderr, "Error in function c_utils_dynamic_library_close, function FreeLibrary (File: %s, Line: %d)...\n", __FILE__, __LINE__);
		fprintf(stderr, "Error code: %u\n", (c_utils_uint32_t)GetLastError());

		return C_UTILS_RESULT_FAILURE;
	}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	if(dlclose(library))
	{
		fprintf(stderr, "Error in function c_utils_dynamic_library_close, function dlclose (File: %s, Line: %d)...\n", __FILE__, __LINE__);
		fprintf(stderr, "Error code: %s\n", dlerror());

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
