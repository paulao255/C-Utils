/*************************/
/* Library importations: */
/*************************/

#include <stdio.h>
#ifndef C_UTILS_COMPILE
#include "../../include/C-Utils/rnd-utls.h"
#else
#include "C-Utils/rnd-utls.h"
#endif
#if defined(_WIN32) || defined(_WIN64) \
 || defined(__linux__) || defined(__ANDROID__) \
 || defined(__APPLE__)
#ifndef C_UTILS_COMPILE
#include "../../include/C-Utils/cryptrnd.h"
#else
#include "C-Utils/cryptrnd.h"
#endif
#elif defined(ESP_PLATFORM)
#include <esp_random.h>
#endif

/****************************/
/* Global static variables: */
/****************************/

static c_utils_bool_t c_utils_random_is_initialized = C_UTILS_FALSE;
#if defined(_WIN32) || defined(_WIN64) \
 || defined(__linux__) || defined(__ANDROID__) \
 || defined(__APPLE__)
static cryptorand c_utils_rng;
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
		fprintf(stderr, "Error in function c_utils_initialize, C-Utils is already initialized (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64) \
 || defined(__linux__) || defined(__ANDROID__) \
 || defined(__APPLE__)
		const cryptorand_result cryptrnd_result = cryptorand_init(&c_utils_rng);

		if(cryptrnd_result != CRYPTORAND_SUCCESS)
		{
			fprintf(stderr, "Error in function c_utils_initialize, cryptorand_init failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %d\n", cryptrnd_result);

			return C_UTILS_RESULT_FAILURE;
		}

#endif
		c_utils_random_is_initialized = C_UTILS_TRUE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_random_integer(c_utils_int32_t minimum, c_utils_int32_t maximum, c_utils_int32_t *const output)
{
	if(!c_utils_random_is_initialized)
	{
		fprintf(stderr, "Error in c_utils_random_integer, C-Utils random is not initialized (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!output)
	{
		fprintf(stderr, "Error in c_utils_random_integer, the output is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(minimum >= maximum)
	{
		fprintf(stderr, "Error in c_utils_random_integer, the minimum is greater than or iqual to the maximum (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		c_utils_uint32_t range = (c_utils_uint32_t)((c_utils_uint32_t)maximum - (c_utils_uint32_t)minimum) + 1u;
		c_utils_uint32_t value = 0u;
#if defined(_WIN32) || defined(_WIN64) \
 || defined(__linux__) || defined(__ANDROID__) \
 || defined(__APPLE__)
		cryptorand_result cryptrnd_result = cryptorand_generate(&c_utils_rng, &value, sizeof(value));

		if(cryptrnd_result != CRYPTORAND_SUCCESS)
		{
			fprintf(stderr, "Error in c_utils_random_integer, function cryptorand_generate failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %d\n", cryptrnd_result);

			return C_UTILS_RESULT_FAILURE;
		}
#elif defined(ESP_PLATFORM)
		value = esp_random();
#endif

		if(range == 0u)
		{
			*output = (c_utils_int32_t)value;
		}

		else
		{
			c_utils_uint32_t limit = C_UTILS_UINT32_MAX - (C_UTILS_UINT32_MAX % range);

			while(value >= limit)
			{
#if defined(_WIN32) || defined(_WIN64) \
 || defined(__linux__) || defined(__ANDROID__) \
 || defined(__APPLE__)
				cryptrnd_result = cryptorand_generate(&c_utils_rng, &value, sizeof(value));

				if(cryptrnd_result != CRYPTORAND_SUCCESS)
				{
					fprintf(stderr, "Error in c_utils_random_integer, function cryptorand_generate failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);
					fprintf(stderr, "Error code: %d\n", cryptrnd_result);

					return C_UTILS_RESULT_FAILURE;
				}
#elif defined(ESP_PLATFORM)
				value = esp_random();
#endif
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
		fprintf(stderr, "Error in function c_utils_terminate, C-Utils is not even initialized (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

#if defined(_WIN32) || defined(_WIN64) \
 || defined(__linux__) || defined(__ANDROID__) \
 || defined(__APPLE__)
	cryptorand_uninit(&c_utils_rng);
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
