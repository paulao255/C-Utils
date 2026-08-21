/*************************/
/* Library importations: */
/*************************/

#include "c-utils.h"
#include "defs.h"
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(_WIN32) || defined(_WIN64)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shellapi.h>
#include <direct.h>
#include <conio.h>
#include "cryptrnd.h"
#elif defined(__linux__) || defined(__ANDROID__)
#include <termios.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "cryptrnd.h"
#elif defined(__APPLE__)
#include <TargetConditionals.h>
#include <termios.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "cryptrnd.h"
#elif defined(__DOS__) || defined(MSDOS) || defined(_MSDOS) || defined (__MSDOS__) || defined(__DOS_386__) || defined(__DJGPP__)
#include <DIRECT.H>
#include <CONIO.H>
#elif defined(ESP_PLATFORM)
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_random.h>
#endif

/****************************/
/* Global static variables: */
/****************************/

static c_utils_void_t **c_utils_addresses_to_free = C_UTILS_NULL_POINTER;
static c_utils_uint8_t c_utils_is_initialized = 0u;
static c_utils_uint32_t c_utils_addresses_to_free_count = 0u;
static c_utils_uint32_t c_utils_addresses_to_free_cap = 0u;
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

extern c_utils_void_t c_utils_clear_standard_output(c_utils_void_t)
{
	fputs("\033[2J\033[3J\033[H", stdout);

	return;
}
#if defined(_WIN32) || defined(_WIN64)

static c_utils_result c_utils_enable_windows_console_features(c_utils_void_t)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if(hOut == INVALID_HANDLE_VALUE || !hOut)
	{
		DWORD error = GetLastError();

		fprintf(stderr, "Error in function GetStdHandle (File: %s, Line: %d)...\n", __FILE__, __LINE__);
		fprintf(stderr, "Error code: %d\n", error);
		perror("Error");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		DWORD mode = 0u;

		if(!GetConsoleMode(hOut, &mode))
		{
			DWORD error = GetLastError();

			fprintf(stderr, "Error in function GetConsoleMode (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %d\n", error);
			perror("Error");

			return C_UTILS_RESULT_FAILURE;
		}

		mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

		if(!SetConsoleMode(hOut, mode))
		{
			DWORD error = GetLastError();

			fprintf(stderr, "Error in function SetConsoleMode (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %d\n", error);
			perror("Error");

			return C_UTILS_RESULT_FAILURE;
		}
		
		if(!SetConsoleOutputCP(CP_UTF8))
		{
			DWORD error = GetLastError();

			fprintf(stderr, "Error in function SetConsoleOutputCP (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %d\n", error);
			perror("Error");

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}
#endif

extern c_utils_result c_utils_mem_free_and_unregist(const c_utils_void_t *const address)
{
	if(!c_utils_is_initialized)
	{
		fprintf(stderr, "Error in function c_utils_mem_free_and_unregist, C-Utils is not initialized (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!address)
	{
		fprintf(stderr, "Error in function c_utils_mem_free_and_unregist, invalid address (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		c_utils_uint32_t index;

		for(index = 0u; index < c_utils_addresses_to_free_count; index++)
		{
			if(c_utils_addresses_to_free[index] == address)
			{
				free((c_utils_void_t *)address);

				c_utils_addresses_to_free_count--;
				c_utils_addresses_to_free[index] = c_utils_addresses_to_free[c_utils_addresses_to_free_count];
				c_utils_addresses_to_free[c_utils_addresses_to_free_count] = C_UTILS_NULL_POINTER;

				return C_UTILS_RESULT_SUCCESS;
			}
		}
	}

	fprintf(stderr, "Error in function c_utils_mem_free_and_unregist, address not registred (File: %s, Line: %d)...\n", __FILE__, __LINE__);

	return C_UTILS_RESULT_FAILURE;
}

extern c_utils_result c_utils_get_current_time(struct tm *const time_struct)
{
	if(!time_struct)
	{
		fprintf(stderr, "Error in function c_utils_get_current_time (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const time_t now = time(C_UTILS_NULL_POINTER);

		if(now == (time_t)-1)
		{
			fprintf(stderr, "Error: time() failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_RESULT_FAILURE;
		}

		else
		{
#if defined(_WIN32) || defined(_WIN64)
			if(localtime_s(time_struct, &now))
			{
				fprintf(stderr, "Error in function localtime_s (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_RESULT_FAILURE;
			}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
			if(!localtime_r(&now, time_struct))
			{
				fprintf(stderr, "Error in function localtime_r (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_RESULT_FAILURE;
			}
#else
			const struct tm *const result = localtime(&now);

			if(!result)
			{
				fprintf(stderr, "Error in function localtime (File: %s, Line: %d)...\n", __FILE__, __LINE__);

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

extern c_utils_result c_utils_validate_date(const c_utils_int32_t year, const c_utils_uint8_t month, const c_utils_uint8_t day, const c_utils_bool_t is_future_date_valid)
{
	if(year < 1L)
	{
		fprintf(stderr, "Error in function c_utils_validate_date (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(month < 1u || month > 12u)
	{
		fprintf(stderr, "Error in function c_utils_validate_date (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(day < 1u || day > 31u)
	{
		fprintf(stderr, "Error in function c_utils_validate_date (File: %s, Line: %d)...\n", __FILE__, __LINE__);

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
				fprintf(stderr, "Error in function c_utils_validate_date, c_utils_get_current_time failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_RESULT_FAILURE;
			}

			if((year % 4L == 0L && year % 100L != 0L) || (year % 400L == 0L))
			{
				days_in_month[1] = 29u;
			}

			if(day > days_in_month[month - 1u])
			{
				return C_UTILS_RESULT_FAILURE;
			}

			if(year > (c_utils_int32_t)(current_date.tm_year) || (year == (c_utils_int32_t)(current_date.tm_year) && month > (c_utils_uint8_t)(current_date.tm_mon)) || (year == (c_utils_int32_t)(current_date.tm_year) && month == (c_utils_uint8_t)(current_date.tm_mon) && day > (c_utils_uint8_t)current_date.tm_mday))
			{
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
				return C_UTILS_RESULT_FAILURE;
			}
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result c_utils_clear_standard_input(c_utils_void_t)
{
#if defined(ESP_PLATFORM)
	fprintf(stderr, "Error in function c_utils_clear_standard_input, %s does not support this function (File: %s, Line: %d)...\n", c_utils_verify_os(), __FILE__, __LINE__);

	return C_UTILS_RESULT_FAILURE;
#else
	signed int characters = getchar();

	while(characters != '\n' && characters != EOF)
	{
		characters = getchar();
	}

	return C_UTILS_RESULT_SUCCESS;
#endif
}

extern c_utils_result c_utils_initialize(c_utils_void_t)
{
	if(c_utils_is_initialized)
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
#if defined(_WIN32) || defined(_WIN64)
		if(c_utils_enable_windows_console_features() != C_UTILS_RESULT_SUCCESS)
		{
			fprintf(stderr, "Error in function c_utils_initialize, c_utils_enable_windows_console_features (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_RESULT_FAILURE;
		}

#endif
		c_utils_is_initialized = 1u;
	}

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result c_utils_terminate(c_utils_void_t)
{
	if(!c_utils_is_initialized)
	{
		fprintf(stderr, "Error in function c_utils_terminate, C-Utils is not even initialized (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		c_utils_uint32_t index;

		for(index = 0u; index < c_utils_addresses_to_free_count; index++)
		{
			if(c_utils_addresses_to_free[index])
			{
				free(c_utils_addresses_to_free[index]);
				c_utils_addresses_to_free[index] = 0;
			}
		}

		free((c_utils_void_t *)c_utils_addresses_to_free);

		c_utils_addresses_to_free = C_UTILS_NULL_POINTER;
		c_utils_addresses_to_free_count = 0u;
		c_utils_addresses_to_free_cap = 0u;

#if defined(_WIN32) || defined(_WIN64) \
 || defined(__linux__) || defined(__ANDROID__) \
 || defined(__APPLE__)
		cryptorand_uninit(&c_utils_rng);
#endif

		c_utils_is_initialized = 0u;
	}

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result c_utils_mem_regist_to_free(const c_utils_void_t *const address)
{
	if(!c_utils_is_initialized)
	{
		fprintf(stderr, "Error in function c_utils_mem_regist_to_free, C-Utils is not even initialized (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!address)
	{
		fprintf(stderr, "Error in function c_utils_mem_regist_to_free, address is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		c_utils_uint32_t index;

		for(index = 0u; index < c_utils_addresses_to_free_count; index++)
		{
			if(c_utils_addresses_to_free[index] == address)
			{
				fprintf(stderr, "Error in function c_utils_mem_regist_to_free, address is already registered (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_RESULT_FAILURE;
			}
		}

		if(c_utils_addresses_to_free_count >= c_utils_addresses_to_free_cap)
		{
			if(c_utils_addresses_to_free_cap > (c_utils_uint32_t)0x0FFFFFFFU)
			{
				fprintf(stderr, "Error in function c_utils_mem_regist_to_free, c_utils_addresses_to_free_cap is too big (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_RESULT_FAILURE;
			}

			else
			{
				c_utils_uint32_t new_cap = !c_utils_addresses_to_free_cap ? 8u : c_utils_addresses_to_free_cap << 1;
				c_utils_void_t **const new_block = (c_utils_void_t **)realloc((c_utils_void_t *)c_utils_addresses_to_free, (size_t)new_cap * sizeof(c_utils_void_t *));

				if(!new_block)
				{
					fprintf(stderr, "Error in function c_utils_mem_regist_to_free, realloc returned a null pointer to new_block (File: %s, Line: %d)...\n", __FILE__, __LINE__);

					return C_UTILS_RESULT_FAILURE;
				}

				else
				{
					c_utils_addresses_to_free = new_block;
					c_utils_addresses_to_free_cap = new_cap;
				}
			}
		}

		c_utils_addresses_to_free[c_utils_addresses_to_free_count] = (c_utils_void_t *)address;
		c_utils_addresses_to_free_count++;
	}

	return C_UTILS_RESULT_SUCCESS;
}

extern c_utils_result c_utils_scan_enter(c_utils_void_t)
{
#if defined(ESP_PLATFORM)
	fprintf(stderr, "Error in function c_utils_scan_enter, %s does not support this function (File: %s, Line: %d)...\n", c_utils_verify_os(), __FILE__, __LINE__);

	return C_UTILS_RESULT_FAILURE;
#else
	if(c_utils_clear_standard_input() != C_UTILS_RESULT_SUCCESS)
	{
		fprintf(stderr, "Error in c_utils_scan_enter, c_utils_clear_standard_input failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(getchar() == EOF)
	{
		fprintf(stderr, "Error in c_utils_scan_enter, getchar failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
#endif
}

extern c_utils_result c_utils_url_opener(const c_utils_char_t *const url)
{
#if defined(__DOS__) || defined(MSDOS) || defined(_MSDOS) || defined (__MSDOS__) || defined(__DOS_386__) || defined(__DJGPP__)
	fprintf(stderr, "Error in function c_utils_url_opener, DOS does not support this function (File: %s, Line: %d)...\n", __FILE__, __LINE__);

	return C_UTILS_RESULT_FAILURE;
#elif defined(ESP_PLATFORM)
	fprintf(stderr, "Error in function c_utils_url_opener, %s does not support this function (File: %s, Line: %d)...\n", c_utils_verify_os(), __FILE__, __LINE__);

	return C_UTILS_RESULT_FAILURE;
#else
	if(!url)
	{
		fprintf(stderr, "Error in function c_utils_url_opener, URL is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

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
			fprintf(stderr, "Error in function ShellExecuteA (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %ld\n", (signed long int)(INT_PTR)result);

			return C_UTILS_RESULT_FAILURE;
		}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		pid_t pid = fork();

		if(pid == -1)
		{
			perror("\"fork\" error");

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
#endif
}

extern c_utils_result c_utils_sleep(const c_utils_uint32_t seconds, const c_utils_uint16_t milliseconds)
{
#if defined(__DOS__) || defined(MSDOS) || defined(_MSDOS) || defined (__MSDOS__) || defined(__DOS_386__) || defined(__DJGPP__)
	fprintf(stderr, "Error in function c_utils_sleep, DOS does not support this function (File: %s, Line: %d)...\n", __FILE__, __LINE__);

	return C_UTILS_RESULT_FAILURE;
#else
	if(!seconds && !milliseconds)
	{
		goto print_invalid_time_error;
	}

	if(milliseconds > 999U)
	{
		goto print_invalid_time_error;
	}

#if defined(_WIN32) || defined(_WIN64)
	if(seconds > (0xFFFFFFFF - (c_utils_uint32_t)milliseconds) / 1000u)
	{
		goto print_invalid_time_error;
	}

	Sleep((DWORD)seconds * 1000u + (DWORD)milliseconds);
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	if(seconds > 0U)
	{
		if(sleep(seconds) > 0)
		{
			fprintf(stderr, "Error in function sleep (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			goto print_errno;
		}
	}

	if(milliseconds > 0u)
	{
		if(usleep((useconds_t)(milliseconds * 1000u)) == -1)
		{
			fprintf(stderr, "Error in function usleep (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			goto print_errno;
		}
	}
#elif defined(ESP_PLATFORM)
	vTaskDelay(pdMS_TO_TICKS(seconds * 1000u + milliseconds));
#else
	return C_UTILS_RESULT_FAILURE;
#endif

	return C_UTILS_RESULT_SUCCESS;
print_invalid_time_error:
	fprintf(stderr, "Error in function c_utils_sleep, invalid time (File: %s, Line: %d)...\n", __FILE__, __LINE__);

	return C_UTILS_RESULT_FAILURE;
print_errno:
	perror("Error");

	return C_UTILS_RESULT_FAILURE;
#endif
}

extern c_utils_result c_utils_make_directory(const c_utils_char_t *const path, c_utils_uint32_t mode)
{
#if defined(ESP_PLATFORM)
	fprintf(stderr, "Error in function c_utils_make_directory, %s does not support this function (File: %s, Line: %d)...\n", c_utils_verify_os(), __FILE__, __LINE__);

	return C_UTILS_RESULT_FAILURE;
#else
	if(!path)
	{
		fprintf(stderr, "Error in function c_utils_make_directory (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64) \
 || defined(__DOS__) || defined(MSDOS) || defined(_MSDOS) || defined (__MSDOS__) || defined(__DOS_386__) || defined(__DJGPP__)
		(c_utils_void_t)mode;
#if !defined(_WIN32) && !defined(_WIN64)
		if(mkdir(path))
#else
		if(_mkdir(path))
#endif
		{
#if !defined(_WIN32) && !defined(_WIN64)
			fprintf(stderr, "Error in function c_utils_make_directory, function mkdir (File: %s, Line: %d)...\n", __FILE__, __LINE__);
#else
			fprintf(stderr, "Error in function c_utils_make_directory, function _mkdir (File: %s, Line: %d)...\n", __FILE__, __LINE__);
#endif
			perror("Error");

			return C_UTILS_RESULT_FAILURE;
		}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		if(!mode)
		{
			mode = 0755UL;
		}

		if(mkdir(path, (mode_t)mode))
		{
			fprintf(stderr, "Error in c_utils_make_directory, function mkdir (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			perror("Error");

			return C_UTILS_RESULT_FAILURE;
		}
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
#endif
}

extern c_utils_result c_utils_scan_character(signed int *const character_output)
{
#if defined(ESP_PLATFORM)
	fprintf(stderr, "Error in function c_utils_scan_character, %s does not support this function (File: %s, Line: %d)...\n", c_utils_verify_os(), __FILE__, __LINE__);

	return C_UTILS_RESULT_FAILURE;
#else
	if(!character_output)
	{
		fprintf(stderr, "Error in function c_utils_scan_character, character_output is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64) || defined(__DOS__) || defined(MSDOS) || defined(_MSDOS) || defined (__MSDOS__) || defined(__DOS_386__) || defined(__DJGPP__)
		*character_output =
#if !defined(_WIN32) && !defined(_WIN64)
			getch()
#else
			_getch()
#endif
		;
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		struct termios old_terminal;

		if(tcgetattr(STDIN_FILENO, &old_terminal) == -1)
		{
			fprintf(stderr, "Error in c_utils_scan_character, function tcgetattr (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			goto print_errno;
		}

		else
		{
			struct termios new_terminal = old_terminal;

			new_terminal.c_lflag &= (tcflag_t) ~(ICANON | ECHO);
			new_terminal.c_cc[VMIN] = 1;
			new_terminal.c_cc[VTIME] = 0;

			if(tcsetattr(STDIN_FILENO, TCSANOW, &new_terminal) == -1)
			{
				goto tcsetattr_error;
			}

			else
			{
				c_utils_char_t keyword;
				ssize_t result = read(STDIN_FILENO, (c_utils_void_t *)&keyword, 1U);

				if(!result)
				{
					fprintf(stderr, "Error in c_utils_scan_character, function read, EOF (File: %s, Line: %d)...\n", __FILE__, __LINE__);

					if(tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal) == -1)
					{
						goto tcsetattr_error;
					}

					return C_UTILS_RESULT_FAILURE;
				}

				else if(result < 0)
				{
					fprintf(stderr, "Error in c_utils_scan_character, function read (File: %s, Line: %d)...\n", __FILE__, __LINE__);
					perror("Error");

					if(tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal) == -1)
					{
						goto tcsetattr_error;
					}

					return C_UTILS_RESULT_FAILURE;
				}

				else
				{
					if(tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal) == -1)
					{
						goto tcsetattr_error;
					}

					*character_output = (signed int)keyword;
				}
			}
		}
#else
	return C_UTILS_RESULT_FAILURE;
#endif
	}

	return C_UTILS_RESULT_SUCCESS;
#if defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
tcsetattr_error:
	fprintf(stderr, "Error in c_utils_scan_character, function tcsetattr (File: %s, Line: %d)...\n", __FILE__, __LINE__);
print_errno:
	perror("Error");

	return C_UTILS_RESULT_FAILURE;
#endif
#endif
}

extern c_utils_result c_utils_mem_allocate(const c_utils_void_t **const address_pointer, const size_t size)
{
	if(!size)
	{
		fprintf(stderr, "Error in function c_utils_mem_allocate, size is zero (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!address_pointer)
	{
		fprintf(stderr, "Error in function c_utils_mem_allocate, address_pointer is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!(*address_pointer))
	{
		c_utils_void_t *const pointer = malloc(size);

		if(!pointer)
		{
			fprintf(stderr, "Error in c_utils_mem_allocate, function malloc failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_RESULT_FAILURE;
		}

		if(c_utils_mem_regist_to_free(pointer) != C_UTILS_RESULT_SUCCESS)
		{
			fprintf(stderr, "Error in c_utils_mem_allocate, function c_utils_mem_regist_to_free failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			free(pointer);

			return C_UTILS_RESULT_FAILURE;
		}

		*address_pointer = pointer;

		return C_UTILS_RESULT_SUCCESS;
	}

	else
	{
		size_t saved_address = (size_t)(*address_pointer);
		c_utils_void_t *const new_pointer = realloc((c_utils_void_t *)*address_pointer, size);

		if(!new_pointer)
		{
			fprintf(stderr, "Error in c_utils_mem_allocate, function realloc failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_RESULT_FAILURE;
		}

		if(new_pointer == (c_utils_void_t *)saved_address)
		{
			*address_pointer = new_pointer;

			return C_UTILS_RESULT_SUCCESS;
		}

		else
		{
			c_utils_uint32_t index;

			for(index = 0u; index < c_utils_addresses_to_free_count; index++)
			{
				if((size_t)c_utils_addresses_to_free[index] == saved_address)
				{
					c_utils_addresses_to_free[index] = new_pointer;

					*address_pointer = new_pointer;

					return C_UTILS_RESULT_SUCCESS;
				}
			}

			if(c_utils_mem_regist_to_free(new_pointer) != C_UTILS_RESULT_SUCCESS)
			{
				fprintf(stderr, "Error in c_utils_mem_allocate, function c_utils_mem_regist_to_free failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				free(new_pointer);

				return C_UTILS_RESULT_FAILURE;
			}
		}

		*address_pointer = new_pointer;

		return C_UTILS_RESULT_SUCCESS;
	}
}

extern c_utils_result c_utils_random_integer(c_utils_int32_t minimum, c_utils_int32_t maximum, c_utils_int32_t *const output)
{
#if defined(__DOS__) || defined(MSDOS) || defined(_MSDOS) || defined (__MSDOS__) || defined(__DOS_386__) || defined(__DJGPP__)
	fprintf(stderr, "Error in c_utils_random_integer, DOS does not support this function (File: %s, Line: %d)...\n", __FILE__, __LINE__);

	return C_UTILS_RESULT_FAILURE;
#else
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
#endif
}

extern c_utils_result c_utils_read_file(const c_utils_char_t *const path, const c_utils_char_t **const output)
{
#if defined(ESP_PLATFORM)
	fprintf(stderr, "Error in c_utils_read_file, %s does not support this function (File: %s, Line: %d)...\n", c_utils_verify_os(), __FILE__, __LINE__);

	return C_UTILS_RESULT_FAILURE;
#else
	if(!c_utils_is_initialized)
	{
		fprintf(stderr, "Error in c_utils_read_file, C-Utils is not initialized (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!path)
	{
		fprintf(stderr, "Error in c_utils_read_file, invalid path (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!output)
	{
		fprintf(stderr, "Error in c_utils_read_file, the output is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		FILE *const file = fopen(path, "rb");

		if(!file)
		{
			const int error = errno;

			if(error == ENOENT)
			{
				fprintf(stderr, "Error in function c_utils_read_file, file not found (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			}

			else if(error == EACCES)
			{
				fprintf(stderr, "Error in function c_utils_read_file, permission denied (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			}

			else
			{
				fprintf(stderr, "Error in function c_utils_read_file (File: %s, Line: %d)...\n", __FILE__, __LINE__);
				perror("Error");
			}

			return C_UTILS_RESULT_FAILURE;
		}

		else
		{
			if(fseek(file, 0L, SEEK_END))
			{
				fprintf(stderr, "Error in function c_utils_read_file, fseek failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				if(fclose(file))
				{
					fprintf(stderr, "Error in function c_utils_read_file, fclose failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);
					perror("Error");
				}

				return C_UTILS_RESULT_FAILURE;
			}

			else
			{
				const signed long int size = ftell(file);

				if(size < 0L)
				{
					fprintf(stderr, "Error in function c_utils_read_file, ftell failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);
					perror("Error");

					if(fclose(file))
					{
						fprintf(stderr, "Error in function c_utils_read_file, fclose failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);
						perror("Error");
					}

					return C_UTILS_RESULT_FAILURE;
				}

				else if(size == LONG_MAX)
				{
					fprintf(stderr, "Error in function c_utils_read_file, file too big (File: %s, Line: %d)...\n", __FILE__, __LINE__);

					if(fclose(file))
					{
						fprintf(stderr, "Error in function c_utils_read_file, fclose failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);
						perror("Error");
					}

					return C_UTILS_RESULT_FAILURE;
				}

				else
				{
					c_utils_char_t *buffer = (c_utils_char_t *)malloc((size_t)size + 1U);

					if(!buffer)
					{
						if(fclose(file))
						{
							fprintf(stderr, "Error in function c_utils_read_file, fclose failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);
							perror("Error");
						}

						return C_UTILS_RESULT_FAILURE;
					}

					if(fseek(file, 0L, SEEK_SET))
					{
						fprintf(stderr, "Error in function c_utils_read_file, fseek failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);

						free((c_utils_void_t *)buffer);

						if(fclose(file))
						{
							fprintf(stderr, "Error in function c_utils_read_file, fclose failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);
							perror("Error");
						}

						return C_UTILS_RESULT_FAILURE;
					}

					clearerr(file);

					if(fread((c_utils_void_t *)buffer, 1U, (size_t)size, file) != (size_t)size)
					{
						free((c_utils_void_t *)buffer);

						if(fclose(file))
						{
							fprintf(stderr, "Error in function c_utils_read_file, fclose failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);
							perror("Error");
						}

						return C_UTILS_RESULT_FAILURE;
					}

					buffer[size] = '\0';

					if(fclose(file))
					{
						fprintf(stderr, "Error in function c_utils_read_file, fclose failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);
						perror("Error");

						free((c_utils_void_t *)buffer);

						return C_UTILS_RESULT_FAILURE;
					}

					if(c_utils_mem_regist_to_free((c_utils_void_t *)buffer) != C_UTILS_RESULT_SUCCESS)
					{
						fprintf(stderr, "Error in function c_utils_regist_address_to_free (File: %s, Line: %d)...\n", __FILE__, __LINE__);

						free((c_utils_void_t *)buffer);

						return C_UTILS_RESULT_FAILURE;
					}

					*output = buffer;
				}
			}
		}
	}

	return C_UTILS_RESULT_SUCCESS;
#endif
}

extern c_utils_result c_utils_verify_os(const c_utils_char_t **const output)
{
	if(!output)
	{
		fprintf(stderr, "Error in function c_utils_verify_os, the output is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		*output = "Windows";

		return C_UTILS_RESULT_SUCCESS;
#elif defined(__linux__)
		const c_utils_char_t *const is_wayland = getenv("WAYLAND_DISPLAY");
		const c_utils_char_t *const is_x11 = getenv("DISPLAY");

		if(is_wayland)
		{
			if(is_x11)
			{
				*output = "Linux, Wayland and XWayland";
			}

			else
			{
				*output = "Linux, Wayland";
			}
		}

		else if(is_x11)
		{
			*output = "Linux, X11";
		}

		else
		{
			*output = "Linux (No graphics)";
		}

		return C_UTILS_RESULT_SUCCESS;
#elif defined(__ANDROID__)
		*output = "Android";

		return C_UTILS_RESULT_SUCCESS;
#elif defined(__APPLE__)
#if TARGET_OS_OSX
		*output = "macOS";

		return C_UTILS_RESULT_SUCCESS;
#elif TARGET_OS_IOS
		*output = "iOS";

		return C_UTILS_RESULT_SUCCESS;
#elif TARGET_OS_TV
		*output = "tvOS";

		return C_UTILS_RESULT_SUCCESS;
#elif TARGET_OS_WATCH
		*output = "watchOS";

		return C_UTILS_RESULT_SUCCESS;
#else
		*output = "Apple (unknown OS)";

		return C_UTILS_RESULT_FAILURE;
#endif
#elif defined(__DOS__) || defined(MSDOS) || defined(_MSDOS) || defined (__MSDOS__) || defined(__DOS_386__) || defined(__DJGPP__)
		*output = "DOS";

		return C_UTILS_RESULT_SUCCESS;
#elif defined(ESP_PLATFORM)
#if defined(CONFIG_IDF_TARGET_ESP32)
		*output = "ESP32";

		return C_UTILS_RESULT_SUCCESS;
#elif defined(CONFIG_IDF_TARGET_ESP32S2)
		*output = "ESP32-S2";

		return C_UTILS_RESULT_SUCCESS;
#elif defined(CONFIG_IDF_TARGET_ESP32S3)
		*output = "ESP32-S3";

		return C_UTILS_RESULT_SUCCESS;
#elif defined(CONFIG_IDF_TARGET_ESP32C2)
		*output = "ESP32-C2";

		return C_UTILS_RESULT_SUCCESS;
#elif defined(CONFIG_IDF_TARGET_ESP32C3)
		*output = "ESP32-C3";

		return C_UTILS_RESULT_SUCCESS;
#elif defined(CONFIG_IDF_TARGET_ESP32C5)
		*output = "ESP32-C5";

		return C_UTILS_RESULT_SUCCESS;
#elif defined(CONFIG_IDF_TARGET_ESP32C6)
		*output = "ESP32-C6";

		return C_UTILS_RESULT_SUCCESS;
#elif defined(CONFIG_IDF_TARGET_ESP32C61)
		*output = "ESP32-C61";

		return C_UTILS_RESULT_SUCCESS;
#elif defined(CONFIG_IDF_TARGET_ESP32H2)
		*output = "ESP32-H2";

		return C_UTILS_RESULT_SUCCESS;
#elif defined(CONFIG_IDF_TARGET_ESP32P4)
		*output = "ESP32-P4";

		return C_UTILS_RESULT_SUCCESS;
#else
		*output = "ESP (unknown model)";

		return C_UTILS_RESULT_FAILURE;
#endif
#else
		*output = "Unknown OS";

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
