/*************************/
/* Library importations: */
/*************************/

#ifndef C_UTILS_COMPILE
#include "../../include/C-Utils/c-utils.h"
#include "../../include/C-Utils/err-utls.h"
#else
#include "C-Utils/c-utils.h"
#include "C-Utils/err-utls.h"
#endif
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(_WIN32) || defined(_WIN64)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shellapi.h>
#include <direct.h>
#include <conio.h>
#elif defined(__linux__) || defined(__ANDROID__)
#include <termios.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#elif defined(__APPLE__)
#include <TargetConditionals.h>
#include <termios.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#endif

/****************************/
/* Global static variables: */
/****************************/

static c_utils_bool_t c_utils_is_initialized = C_UTILS_FALSE;
static c_utils_uint32_t c_utils_addresses_to_free_count = 0u;
static c_utils_uint32_t c_utils_addresses_to_free_capacity = 0u;
static c_utils_memory_handle_t **c_utils_addresses_to_free = C_UTILS_NULL_POINTER;

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

C_UTILS_API c_utils_void_t c_utils_clear_standard_output(c_utils_void_t)
{
	fputs("\033[2J\033[3J\033[H", stdout);

	return;
}

C_UTILS_API c_utils_void_t c_utils_clear_standard_input(c_utils_void_t)
{
	signed int characters = getchar();

	while(characters != '\n' && characters != EOF)
	{
		characters = getchar();
	}

	return;
}

C_UTILS_API c_utils_result_t c_utils_initialize(c_utils_void_t)
{
	if(c_utils_is_initialized)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_initialize, C-Utils is already initialized");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

		if(hOut == INVALID_HANDLE_VALUE || !hOut)
		{
			const DWORD error = GetLastError();
			DWORD value = error;
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_initialize, function GetStdHandle failed, error code: ");
			c_utils_size_t error_size = 1u;

			while(value >= 10u)
			{
				value /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_initialize, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_initialize, function GetStdHandle failed, error code: %u", (c_utils_uint32_t)error);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}

		else
		{
			DWORD mode = 0u;

			if(!GetConsoleMode(hOut, &mode))
			{
				const DWORD error = GetLastError();
				DWORD value = error;
				c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
				c_utils_size_t prefix_size = strlen("Error in function c_utils_initialize, function GetConsoleMode failed, error code: ");
				c_utils_size_t error_size = 1u;

				while(value >= 10u)
				{
					value /= 10u;
					error_size++;
				}

				error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

				if(!error_buffer)
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_initialize, function malloc failed");

					return C_UTILS_RESULT_FAILURE;
				}

				sprintf(error_buffer, "Error in function c_utils_initialize, function GetConsoleMode failed, error code: %u", (c_utils_uint32_t)error);

				C_UTILS_REPORT_ERROR(error_buffer);

				free((c_utils_void_t *)error_buffer);

				return C_UTILS_RESULT_FAILURE;
			}

			mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

			if(!SetConsoleMode(hOut, mode))
			{
				const DWORD error = GetLastError();
				DWORD value = error;
				c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
				c_utils_size_t prefix_size = strlen("Error in function c_utils_initialize, function SetConsoleMode failed, error code: ");
				c_utils_size_t error_size = 1u;

				while(value >= 10u)
				{
					value /= 10u;
					error_size++;
				}

				error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

				if(!error_buffer)
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_initialize, function malloc failed");

					return C_UTILS_RESULT_FAILURE;
				}

				sprintf(error_buffer, "Error in function c_utils_initialize, function SetConsoleMode failed, error code: %u", (c_utils_uint32_t)error);

				C_UTILS_REPORT_ERROR(error_buffer);

				free((c_utils_void_t *)error_buffer);

				return C_UTILS_RESULT_FAILURE;
			}
			
			if(!SetConsoleOutputCP(CP_UTF8))
			{
				const DWORD error = GetLastError();
				DWORD value = error;
				c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
				c_utils_size_t prefix_size = strlen("Error in function c_utils_initialize, function SetConsoleOutputCP failed, error code: ");
				c_utils_size_t error_size = 1u;

				while(value >= 10u)
				{
					value /= 10u;
					error_size++;
				}

				error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

				if(!error_buffer)
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_initialize, function malloc failed");

					return C_UTILS_RESULT_FAILURE;
				}

				sprintf(error_buffer, "Error in function c_utils_initialize, function SetConsoleOutputCP failed, error code: %u", (c_utils_uint32_t)error);

				C_UTILS_REPORT_ERROR(error_buffer);

				free((c_utils_void_t *)error_buffer);

				return C_UTILS_RESULT_FAILURE;
			}
		}

#endif
		c_utils_is_initialized = C_UTILS_TRUE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_terminate(c_utils_void_t)
{
	if(!c_utils_is_initialized)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_terminate, C-Utils is not initialized");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		c_utils_uint32_t index;

		for(index = 0u; index < c_utils_addresses_to_free_count; index++)
		{
			if(c_utils_addresses_to_free[index] && c_utils_addresses_to_free[index]->pointer)
			{
				free(c_utils_addresses_to_free[index]->pointer);
				c_utils_addresses_to_free[index]->pointer = C_UTILS_NULL_POINTER;
			}
		}

		free((c_utils_void_t *)c_utils_addresses_to_free);

		c_utils_addresses_to_free = C_UTILS_NULL_POINTER;
		c_utils_addresses_to_free_count = 0u;
		c_utils_addresses_to_free_capacity = 0u;

		c_utils_is_initialized = C_UTILS_FALSE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_mem_free_and_unregist(c_utils_memory_handle_t *const handle)
{
	if(!c_utils_is_initialized)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_mem_free_and_unregist, C-Utils is not initialized");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!handle)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_mem_free_and_unregist, the handle is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!handle->pointer)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_mem_free_and_unregist, the handle->pointer is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		c_utils_uint32_t index = handle->location;

		if(index >= c_utils_addresses_to_free_count || c_utils_addresses_to_free[index] != handle)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_mem_free_and_unregist, the handle is not registered or already freed");

			return C_UTILS_RESULT_FAILURE;
		}

		free(handle->pointer);
		handle->pointer = C_UTILS_NULL_POINTER;

		c_utils_addresses_to_free_count--;

		if(index < c_utils_addresses_to_free_count)
		{
			c_utils_memory_handle_t *last_handle = c_utils_addresses_to_free[c_utils_addresses_to_free_count];
			c_utils_addresses_to_free[index] = last_handle;
			last_handle->location = index;
		}

		c_utils_addresses_to_free[c_utils_addresses_to_free_count] = C_UTILS_NULL_POINTER;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_get_current_time(struct tm *const time_struct)
{
	if(!time_struct)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_get_current_time, the time_struct is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const time_t now = time(C_UTILS_NULL_POINTER);

		if(now == (time_t)-1)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_get_current_time, function time failed");

			return C_UTILS_RESULT_FAILURE;
		}

		else
		{
#if defined(_WIN32) || defined(_WIN64)
			if(localtime_s(time_struct, &now))
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_get_current_time, function localtime_s failed");

				return C_UTILS_RESULT_FAILURE;
			}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
			if(!localtime_r(&now, time_struct))
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_get_current_time, function localtime_r failed");

				return C_UTILS_RESULT_FAILURE;
			}
#else
			const struct tm *const result = localtime(&now);

			if(!result)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_get_current_time, function localtime failed");

				return C_UTILS_RESULT_FAILURE;
			}

			*time_struct = *result;
#endif

			time_struct->tm_year += 1900;
			time_struct->tm_mon += 1;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_validate_date(const c_utils_int32_t year, const c_utils_uint8_t month, const c_utils_uint8_t day, const c_utils_bool_t is_future_date_valid)
{
	if(year < 1l)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_validate_date, year is less than 1l");

		return C_UTILS_RESULT_FAILURE;
	}

	if(month < 1u || month > 12u)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_validate_date, month is less than 1u or greater than 12u");

		return C_UTILS_RESULT_FAILURE;
	}

	if(day < 1u || day > 31u)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_validate_date, day is less than 1u or greater than 31u");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		c_utils_uint8_t days_in_month[12] =
		{
			31u,
			28u,
			31u,
			30u,
			31u,
			30u,
			31u,
			31u,
			30u,
			31u,
			30u,
			31u
		};

		if(!is_future_date_valid)
		{
			struct tm current_date;

			if(c_utils_get_current_time(&current_date) != C_UTILS_RESULT_SUCCESS)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_validate_date, c_utils_get_current_time failed");

				return C_UTILS_RESULT_FAILURE;
			}

			if((year % 4L == 0L && year % 100L != 0L) || (year % 400L == 0L))
			{
				days_in_month[1] = 29u;
			}

			if(day > days_in_month[month - 1u])
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_validate_date, day is greater than days in month");

				return C_UTILS_RESULT_FAILURE;
			}

			if(year > (c_utils_int32_t)(current_date.tm_year) || (year == (c_utils_int32_t)(current_date.tm_year) && month > (c_utils_uint8_t)(current_date.tm_mon)) || (year == (c_utils_int32_t)(current_date.tm_year) && month == (c_utils_uint8_t)(current_date.tm_mon) && day > (c_utils_uint8_t)current_date.tm_mday))
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_validate_date, date is greater than current date");

				return C_UTILS_RESULT_FAILURE;
			}
		}

		else
		{
			if((year % 4L == 0L && year % 100L != 0L) || (year % 400L == 0L))
			{
				days_in_month[1] = 29u;
			}

			if(day > days_in_month[month - 1u])
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_validate_date, day is greater than days in month");

				return C_UTILS_RESULT_FAILURE;
			}
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_mem_regist_to_free(c_utils_memory_handle_t *const handle)
{
	if(!c_utils_is_initialized)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_mem_regist_to_free, C-Utils is not initialized");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!handle)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_mem_regist_to_free, the handle is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!handle->pointer)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_mem_regist_to_free, the handle->pointer is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_addresses_to_free_count >= c_utils_addresses_to_free_capacity)
	{
		if(c_utils_addresses_to_free_capacity > (c_utils_uint32_t)0x0FFFFFFFu)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_mem_regist_to_free, c_utils_addresses_to_free_capacity is greater than 0x0FFFFFFFu");

			return C_UTILS_RESULT_FAILURE;
		}

		else
		{
			c_utils_uint32_t new_capacity = !c_utils_addresses_to_free_capacity ? 8u : c_utils_addresses_to_free_capacity << 1;
			c_utils_memory_handle_t **const new_block = (c_utils_memory_handle_t **)realloc(c_utils_addresses_to_free, (c_utils_size_t)new_capacity * sizeof(*new_block));

			if(!new_block)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_mem_regist_to_free, function realloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			c_utils_addresses_to_free = new_block;
			c_utils_addresses_to_free_capacity = new_capacity;
		}
	}

	handle->location = c_utils_addresses_to_free_count;
	c_utils_addresses_to_free[c_utils_addresses_to_free_count++] = handle;

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_scan_enter(c_utils_void_t)
{
	c_utils_clear_standard_input();

	if(getchar() == EOF)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_scan_enter, function getchar failed");

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_url_open(const c_utils_char_t *const url)
{
	if(!url)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_url_open, URL is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}
	
	else
	{
#if defined(_WIN32) || defined(_WIN64)
		HINSTANCE result = ShellExecuteA(
			C_UTILS_NULL_POINTER,
			"open",
			url,
			C_UTILS_NULL_POINTER,
			C_UTILS_NULL_POINTER,
			SW_SHOWNORMAL
		);

		if((INT_PTR)result <= 32)
		{
			signed long int error = (signed long int)(INT_PTR)result;
			unsigned long int code = (unsigned long int)(error < 0 ? -error : error);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_url_open, function ShellExecuteA failed, error code: ");
			c_utils_size_t error_size = (result < 0) ? 2u : 1u;

			while(code >= 10u)
			{
				code /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_url_open, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_url_open, function ShellExecuteA failed, error code: %ld", error);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		pid_t pid = fork();

		if(pid == -1)
		{
			const signed int errno_error = errno;
			unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_url_open, function fork failed, error code: ");
			c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

			while(error >= 10u)
			{
				error /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_url_open, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_url_open, function fork failed, error code: %d", errno_error);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}

		if(!pid)
		{
			const c_utils_char_t *arguments[3];

			arguments[1] = url;
			arguments[2] = C_UTILS_NULL_POINTER;

#if defined(__linux__) || defined(__ANDROID__)
			arguments[0] = "xdg-open";
			execv("/usr/bin/xdg-open", (c_utils_char_t *const *)arguments);
#elif defined(__APPLE__)
			arguments[0] = "open";
			execv("/usr/bin/open", (c_utils_char_t *const *)arguments);
#endif
			_exit(1);
		}

		waitpid(pid, C_UTILS_NULL_POINTER, 0);
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_sleep(const c_utils_uint32_t seconds, const c_utils_uint16_t milliseconds)
{
	if(!seconds && !milliseconds)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_sleep, seconds and milliseconds are both 0");

		return C_UTILS_RESULT_FAILURE;
	}

	if(milliseconds > 999u)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_sleep, milliseconds is greater than 999u");

		return C_UTILS_RESULT_FAILURE;
	}

#if defined(_WIN32) || defined(_WIN64)
	if(seconds > (0xFFFFFFFF - (c_utils_uint32_t)milliseconds) / 1000u)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_sleep, seconds is greater than (0xFFFFFFFF - milliseconds) / 1000u");

		return C_UTILS_RESULT_FAILURE;
	}

	Sleep((DWORD)seconds * 1000u + (DWORD)milliseconds);
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	if(seconds > 0u)
	{
		if(sleep(seconds) > 0)
		{
			const signed int errno_error = errno;
			unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_sleep, function sleep failed, error code: ");
			c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

			while(error >= 10u)
			{
				error /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_sleep, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_sleep, function sleep failed, error code: %d", errno_error);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	if(milliseconds > 0u)
	{
		if(usleep((useconds_t)(milliseconds * 1000u)) == -1)
		{
			const signed int errno_error = errno;
			unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_sleep, function usleep failed, error code: ");
			c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

			while(error >= 10u)
			{
				error /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_sleep, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_sleep, function usleep failed, error code: %d", errno_error);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
	}
#endif

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_make_directory(const c_utils_char_t *const path, c_utils_uint32_t mode)
{
	if(!path)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_make_directory, path is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		(c_utils_void_t)mode;

		if(_mkdir(path))
		{
			const signed int errno_error = errno;
			unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_make_directory, function _mkdir failed, error code: ");
			c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

			while(error >= 10u)
			{
				error /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_make_directory, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_make_directory, function _mkdir failed, error code: %d", errno_error);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		if(!mode)
		{
			mode = 0755UL;
		}

		if(mkdir(path, (mode_t)mode))
		{
			const signed int errno_error = errno;
			unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_make_directory, function mkdir failed, error code: ");
			c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

			while(error >= 10u)
			{
				error /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_make_directory, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_make_directory, function mkdir failed, error code: %d", errno_error);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_scan_character(signed int *const character_output)
{
	if(!character_output)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_scan_character, the character_output is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		*character_output = _getch();
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		struct termios old_terminal;

		if(tcgetattr(STDIN_FILENO, &old_terminal) == -1)
		{
			const signed int errno_error = errno;
			unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_scan_character, function tcgetattr failed, error code: ");
			c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

			while(error >= 10u)
			{
				error /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_scan_character, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_scan_character, function tcgetattr failed, error code: %d", errno_error);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}

		else
		{
			struct termios new_terminal = old_terminal;

			new_terminal.c_lflag &= (tcflag_t) ~(ICANON | ECHO);
			new_terminal.c_cc[VMIN] = 1;
			new_terminal.c_cc[VTIME] = 0;

			if(tcsetattr(STDIN_FILENO, TCSANOW, &new_terminal) == -1)
			{
				const signed int errno_error = errno;
				unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
				c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
				c_utils_size_t prefix_size = strlen("Error in function c_utils_scan_character, function tcsetattr failed, error code: ");
				c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

				while(error >= 10u)
				{
					error /= 10u;
					error_size++;
				}

				error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

				if(!error_buffer)
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_scan_character, function malloc failed");

					return C_UTILS_RESULT_FAILURE;
				}

				sprintf(error_buffer, "Error in function c_utils_scan_character, function tcsetattr failed, error code: %d", errno_error);

				C_UTILS_REPORT_ERROR(error_buffer);

				free((c_utils_void_t *)error_buffer);

				return C_UTILS_RESULT_FAILURE;
			}

			else
			{
				c_utils_char_t keyword;
				ssize_t result = read(STDIN_FILENO, (c_utils_void_t *)&keyword, 1U);

				if(!result)
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_scan_character, function read failed, EOF");

					if(tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal) == -1)
					{
						const signed int errno_error = errno;
						unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
						c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
						c_utils_size_t prefix_size = strlen("Error in function c_utils_scan_character, function tcsetattr failed, error code: ");
						c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

						while(error >= 10u)
						{
							error /= 10u;
							error_size++;
						}

						error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

						if(!error_buffer)
						{
							C_UTILS_REPORT_ERROR("Error in function c_utils_scan_character, function malloc failed");

							return C_UTILS_RESULT_FAILURE;
						}

						sprintf(error_buffer, "Error in function c_utils_scan_character, function tcsetattr failed, error code: %d", errno_error);

						C_UTILS_REPORT_ERROR(error_buffer);

						free((c_utils_void_t *)error_buffer);
					}

					return C_UTILS_RESULT_FAILURE;
				}

				else if(result < 0)
				{
					signed int errno_error = errno;
					unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
					c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
					c_utils_size_t prefix_size = strlen("Error in function c_utils_scan_character, function read failed, error code: ");
					c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

					while(error >= 10u)
					{
						error /= 10u;
						error_size++;
					}

					error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

					if(!error_buffer)
					{
						C_UTILS_REPORT_ERROR("Error in function c_utils_scan_character, function malloc failed");

						return C_UTILS_RESULT_FAILURE;
					}

					sprintf(error_buffer, "Error in function c_utils_scan_character, function read failed, error code: %d", errno_error);

					C_UTILS_REPORT_ERROR(error_buffer);

					free((c_utils_void_t *)error_buffer);

					if(tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal) == -1)
					{
						errno_error = errno;
						error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
						error_buffer = C_UTILS_NULL_POINTER;
						prefix_size = strlen("Error in function c_utils_scan_character, function tcsetattr failed, error code: ");
						error_size = (errno_error < 0) ? 2u : 1u;

						while(error >= 10u)
						{
							error /= 10u;
							error_size++;
						}

						error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

						if(!error_buffer)
						{
							C_UTILS_REPORT_ERROR("Error in function c_utils_scan_character, function malloc failed");

							return C_UTILS_RESULT_FAILURE;
						}

						sprintf(error_buffer, "Error in function c_utils_scan_character, function tcsetattr failed, error code: %d", errno_error);

						C_UTILS_REPORT_ERROR(error_buffer);

						free((c_utils_void_t *)error_buffer);
					}

					return C_UTILS_RESULT_FAILURE;
				}

				else
				{
					if(tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal) == -1)
					{
						const signed int errno_error = errno;
						unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
						c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
						c_utils_size_t prefix_size = strlen("Error in function c_utils_scan_character, function tcsetattr failed, error code: ");
						c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

						while(error >= 10u)
						{
							error /= 10u;
							error_size++;
						}

						error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

						if(!error_buffer)
						{
							C_UTILS_REPORT_ERROR("Error in function c_utils_scan_character, function malloc failed");

							return C_UTILS_RESULT_FAILURE;
						}

						sprintf(error_buffer, "Error in function c_utils_scan_character, function tcsetattr failed, error code: %d", errno_error);

						C_UTILS_REPORT_ERROR(error_buffer);

						free((c_utils_void_t *)error_buffer);

						return C_UTILS_RESULT_FAILURE;
					}

					*character_output = (signed int)keyword;
				}
			}
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_mem_allocate(c_utils_memory_handle_t *const handle, const c_utils_size_t size)
{
	if(!size)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_mem_allocate, the size is zero");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!handle)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_mem_allocate, the handle is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!handle->pointer)
	{
		c_utils_void_t *const pointer = malloc(size);

		if(!pointer)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_mem_allocate, function malloc failed");

			return C_UTILS_RESULT_FAILURE;
		}

		handle->pointer = pointer;

		if(c_utils_mem_regist_to_free(handle))
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_mem_allocate, function c_utils_mem_regist_to_free failed");

			free(pointer);
			handle->pointer = C_UTILS_NULL_POINTER;

			return C_UTILS_RESULT_FAILURE;
		}
	}

	else
	{
		c_utils_void_t *const new_pointer = realloc(handle->pointer, size);

		if(!new_pointer)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_mem_allocate, function realloc failed");

			return C_UTILS_RESULT_FAILURE;
		}

		handle->pointer = new_pointer;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_read_file(const c_utils_char_t *const path, c_utils_memory_handle_t *const output)
{
	if(!c_utils_is_initialized)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_read_file, C-Utils is not initialized");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!path)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_read_file, the path is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!output)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_read_file, the output is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		FILE *const file = fopen(path, "rb");

		if(!file)
		{
			const signed int errno_error = errno;
			unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_read_file, function fopen failed, error code: ");
			c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

			while(error >= 10u)
			{
				error /= 10u;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_read_file, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_read_file, function fopen failed, error code: %d", errno_error);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}

		else
		{
			if(fseek(file, 0L, SEEK_END))
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_read_file, function fseek failed");

				if(fclose(file))
				{
					const signed int errno_error = errno;
					unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
					c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
					c_utils_size_t prefix_size = strlen("Error in function c_utils_read_file, function fclose failed, error code: ");
					c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

					while(error >= 10u)
					{
						error /= 10u;
						error_size++;
					}

					error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

					if(!error_buffer)
					{
						C_UTILS_REPORT_ERROR("Error in function c_utils_read_file, function malloc failed");

						return C_UTILS_RESULT_FAILURE;
					}

					sprintf(error_buffer, "Error in function c_utils_read_file, function fclose failed, error code: %d", errno_error);

					C_UTILS_REPORT_ERROR(error_buffer);

					free((c_utils_void_t *)error_buffer);
				}

				return C_UTILS_RESULT_FAILURE;
			}

			else
			{
				const signed long int size = ftell(file);

				if(size < 0L)
				{
					signed int errno_error = errno;
					unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
					c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
					c_utils_size_t prefix_size = strlen("Error in function c_utils_read_file, function ftell failed, error code: ");
					c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

					while(error >= 10u)
					{
						error /= 10u;
						error_size++;
					}

					error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

					if(!error_buffer)
					{
						C_UTILS_REPORT_ERROR("Error in function c_utils_read_file, function malloc failed");

						return C_UTILS_RESULT_FAILURE;
					}

					sprintf(error_buffer, "Error in function c_utils_read_file, function ftell failed, error code: %d", errno_error);

					C_UTILS_REPORT_ERROR(error_buffer);

					free((c_utils_void_t *)error_buffer);

					if(fclose(file))
					{
						errno_error = errno;
						error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
						error_buffer = C_UTILS_NULL_POINTER;
						prefix_size = strlen("Error in function c_utils_read_file, function fclose failed, error code: ");
						error_size = (errno_error < 0) ? 2u : 1u;

						while(error >= 10u)
						{
							error /= 10u;
							error_size++;
						}

						error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

						if(!error_buffer)
						{
							C_UTILS_REPORT_ERROR("Error in function c_utils_read_file, function malloc failed");

							return C_UTILS_RESULT_FAILURE;
						}

						sprintf(error_buffer, "Error in function c_utils_read_file, function fclose failed, error code: %d", errno_error);

						C_UTILS_REPORT_ERROR(error_buffer);

						free((c_utils_void_t *)error_buffer);
					}

					return C_UTILS_RESULT_FAILURE;
				}

				else if(size == LONG_MAX)
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_read_file, the file is too big");

					if(fclose(file))
					{
						const signed int errno_error = errno;
						unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
						c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
						c_utils_size_t prefix_size = strlen("Error in function c_utils_read_file, function fclose failed, error code: ");
						c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

						while(error >= 10u)
						{
							error /= 10u;
							error_size++;
						}

						error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

						if(!error_buffer)
						{
							C_UTILS_REPORT_ERROR("Error in function c_utils_read_file, function malloc failed");

							return C_UTILS_RESULT_FAILURE;
						}

						sprintf(error_buffer, "Error in function c_utils_read_file, function fclose failed, error code: %d", errno_error);

						C_UTILS_REPORT_ERROR(error_buffer);

						free((c_utils_void_t *)error_buffer);
					}

					return C_UTILS_RESULT_FAILURE;
				}

				else
				{
					if(c_utils_mem_allocate(output, (c_utils_size_t)size + 1u))
					{
						C_UTILS_REPORT_ERROR("Error in function c_utils_read_file, function c_utils_mem_allocate failed");

						if(fclose(file))
						{
							const signed int errno_error = errno;
							unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
							c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
							c_utils_size_t prefix_size = strlen("Error in function c_utils_read_file, function fclose failed, error code: ");
							c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

							while(error >= 10u)
							{
								error /= 10u;
								error_size++;
							}

							error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

							if(!error_buffer)
							{
								C_UTILS_REPORT_ERROR("Error in function c_utils_read_file, function malloc failed");

								return C_UTILS_RESULT_FAILURE;
							}

							sprintf(error_buffer, "Error in function c_utils_read_file, function fclose failed, error code: %d", errno_error);

							C_UTILS_REPORT_ERROR(error_buffer);

							free((c_utils_void_t *)error_buffer);
						}

						return C_UTILS_RESULT_FAILURE;
					}

					else
					{
						c_utils_char_t *const buffer = (c_utils_char_t *)output->pointer;

						if(fseek(file, 0L, SEEK_SET))
						{
							C_UTILS_REPORT_ERROR("Error in function c_utils_read_file, function fseek failed");

							if(c_utils_mem_free_and_unregist(output))
							{
								C_UTILS_REPORT_ERROR("Error in function c_utils_read_file, function c_utils_mem_free_and_unregist failed");
							}

							if(fclose(file))
							{
								const signed int errno_error = errno;
								unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
								c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
								c_utils_size_t prefix_size = strlen("Error in function c_utils_read_file, function fclose failed, error code: ");
								c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

								while(error >= 10u)
								{
									error /= 10u;
									error_size++;
								}

								error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

								if(!error_buffer)
								{
									C_UTILS_REPORT_ERROR("Error in function c_utils_read_file, function malloc failed");

									return C_UTILS_RESULT_FAILURE;
								}

								sprintf(error_buffer, "Error in function c_utils_read_file, function fclose failed, error code: %d", errno_error);

								C_UTILS_REPORT_ERROR(error_buffer);

								free((c_utils_void_t *)error_buffer);
							}

							return C_UTILS_RESULT_FAILURE;
						}

						clearerr(file);

						if(fread((c_utils_void_t *)buffer, 1U, (c_utils_size_t)size, file) != (c_utils_size_t)size)
						{
							C_UTILS_REPORT_ERROR("Error in function c_utils_read_file, function fread failed");

							if(c_utils_mem_free_and_unregist(output))
							{
								C_UTILS_REPORT_ERROR("Error in function c_utils_read_file, function c_utils_mem_free_and_unregist failed");
							}

							if(fclose(file))
							{
								const signed int errno_error = errno;
								unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
								c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
								c_utils_size_t prefix_size = strlen("Error in function c_utils_read_file, function fclose failed, error code: ");
								c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

								while(error >= 10u)
								{
									error /= 10u;
									error_size++;
								}

								error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

								if(!error_buffer)
								{
									C_UTILS_REPORT_ERROR("Error in function c_utils_read_file, function malloc failed");

									return C_UTILS_RESULT_FAILURE;
								}

								sprintf(error_buffer, "Error in function c_utils_read_file, function fclose failed, error code: %d", errno_error);

								C_UTILS_REPORT_ERROR(error_buffer);

								free((c_utils_void_t *)error_buffer);
							}

							return C_UTILS_RESULT_FAILURE;
						}

						buffer[size] = '\0';

						if(fclose(file))
						{
							const signed int errno_error = errno;
							unsigned int error = (unsigned int)(errno_error < 0 ? -errno_error : errno_error);
							c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
							c_utils_size_t prefix_size = strlen("Error in function c_utils_read_file, function fclose failed, error code: ");
							c_utils_size_t error_size = (errno_error < 0) ? 2u : 1u;

							while(error >= 10u)
							{
								error /= 10u;
								error_size++;
							}

							error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

							if(!error_buffer)
							{
								C_UTILS_REPORT_ERROR("Error in function c_utils_read_file, function malloc failed");

								return C_UTILS_RESULT_FAILURE;
							}

							sprintf(error_buffer, "Error in function c_utils_read_file, function fclose failed, error code: %d", errno_error);

							C_UTILS_REPORT_ERROR(error_buffer);

							free((c_utils_void_t *)error_buffer);

							if(c_utils_mem_free_and_unregist(output))
							{
								C_UTILS_REPORT_ERROR("Error in function c_utils_read_file, function c_utils_mem_free_and_unregist failed");
							}

							return C_UTILS_RESULT_FAILURE;
						}
					}
				}
			}
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_verify_os(const c_utils_char_t *const output)
{
	if(!output)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_verify_os, the output is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const c_utils_char_t **const type_output = (const c_utils_char_t **const)(const c_utils_void_t *const)output;
#if defined(_WIN32) || defined(_WIN64)
		*type_output = "Windows";

		return C_UTILS_RESULT_SUCCESS;
#elif defined(__linux__)
		const c_utils_char_t *const is_wayland = getenv("WAYLAND_DISPLAY");
		const c_utils_char_t *const is_x11 = getenv("DISPLAY");

		if(is_wayland)
		{
			if(is_x11)
			{
				*type_output = "Linux, Wayland and XWayland";
			}

			else
			{
				*type_output = "Linux, Wayland";
			}
		}

		else if(is_x11)
		{
			*type_output = "Linux, X11";
		}

		else
		{
			*type_output = "Linux (No graphics)";
		}

		return C_UTILS_RESULT_SUCCESS;
#elif defined(__ANDROID__)
		*type_output = "Android";

		return C_UTILS_RESULT_SUCCESS;
#elif defined(__APPLE__)
#if TARGET_OS_OSX
		*type_output = "macOS";

		return C_UTILS_RESULT_SUCCESS;
#elif TARGET_OS_IOS
		*type_output = "iOS";

		return C_UTILS_RESULT_SUCCESS;
#elif TARGET_OS_TV
		*type_output = "tvOS";

		return C_UTILS_RESULT_SUCCESS;
#elif TARGET_OS_WATCH
		*type_output = "watchOS";

		return C_UTILS_RESULT_SUCCESS;
#else
		*type_output = "Apple (unknown OS)";

		return C_UTILS_RESULT_FAILURE;
#endif
#else
		*type_output = "Unknown OS";

		return C_UTILS_RESULT_FAILURE;
#endif
	}
}

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif
