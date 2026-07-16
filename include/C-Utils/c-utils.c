/*************************/
/* Library importations: */
/*************************/

#include "c-utils.h"
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
#elif defined(__DOS__) || defined(MSDOS) || defined(_MSDOS) || defined (__MSDOS__) || defined(__DOS_386__) || defined(__DJGPP__)
#include <DIRECT.H>
#elif defined(ESP_PLATFORM)
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#endif

/****************************/
/* Global static variables: */
/****************************/

static void **c_utils_addresses_to_free = (void **)0;
static c_utils_uint8_t c_utils_is_initialized = 0u;
static c_utils_uint32_t c_utils_addresses_to_free_count = 0u;
static c_utils_uint32_t c_utils_addresses_to_free_cap = 0u;

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

void c_utils_clear_standard_output(void)
{
	fputs("\033[2J\033[3J\033[H", stdout);

	return;
}
#if defined(_WIN32) || defined(_WIN64)

static c_utils_int16_t c_utils_enable_virtual_terminal_and_utf8(void)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if(hOut == INVALID_HANDLE_VALUE || hOut == (HANDLE)0)
	{
		DWORD error = GetLastError();

		fprintf(stderr, "Error in function GetStdHandle (File: %s, Line: %d)...\n", __FILE__, __LINE__);
		fprintf(stderr, "Error code: %d\n", error);
		perror("Error");

		return C_UTILS_FAILURE;
	}

	else
	{
		DWORD mode = 0u;

		if(GetConsoleMode(hOut, &mode) == 0)
		{
			DWORD error = GetLastError();

			fprintf(stderr, "Error in function GetConsoleMode (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %d\n", error);
			perror("Error");

			return C_UTILS_FAILURE;
		}

		mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

		if(SetConsoleMode(hOut, mode) == 0)
		{
			DWORD error = GetLastError();

			fprintf(stderr, "Error in function SetConsoleMode (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %d\n", error);
			perror("Error");

			return C_UTILS_FAILURE;
		}
		
		if(SetConsoleOutputCP(CP_UTF8) == 0)
		{
			DWORD error = GetLastError();

			fprintf(stderr, "Error in function SetConsoleOutputCP (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %d\n", error);
			perror("Error");

			return C_UTILS_FAILURE;
		}
	}

	return C_UTILS_SUCCESS;
}
#endif

c_utils_int16_t c_utils_mem_free_and_unregist(const void *const address)
{
	if(c_utils_is_initialized == 0u)
	{
		fprintf(stderr, "Error in function c_utils_mem_free_and_unregist, C-Utils is not initialized (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(address == (void *)0)
	{
		fprintf(stderr, "Error in function c_utils_mem_free_and_unregist, invalid address (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	else
	{
		c_utils_uint32_t index;

		for(index = 0u; index < c_utils_addresses_to_free_count; index++)
		{
			if(c_utils_addresses_to_free[index] == address)
			{
				free((void *)address);

				c_utils_addresses_to_free_count--;
				c_utils_addresses_to_free[index] = c_utils_addresses_to_free[c_utils_addresses_to_free_count];
				c_utils_addresses_to_free[c_utils_addresses_to_free_count] = (void *)0;

				return C_UTILS_SUCCESS;
			}
		}
	}

	fprintf(stderr, "Error in function c_utils_mem_free_and_unregist, address not registred (File: %s, Line: %d)...\n", __FILE__, __LINE__);

	return C_UTILS_FAILURE;
}

c_utils_int16_t c_utils_get_current_time(struct tm *const time_struct)
{
	if(time_struct == (struct tm *)0)
	{
		fprintf(stderr, "Error in function c_utils_get_current_time (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	else
	{
		const time_t now = time((time_t *)0);

		if(now == (time_t)-1)
		{
			fprintf(stderr, "Error: time() failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return C_UTILS_FAILURE;
		}

		else
		{
#if defined(_WIN32) || defined(_WIN64)
			if(localtime_s(time_struct, &now) != 0)
			{
				fprintf(stderr, "Error in function localtime_s (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_FAILURE;
			}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
			if(localtime_r(&now, time_struct) == (struct tm *)0)
			{
				fprintf(stderr, "Error in function localtime_r (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_FAILURE;
			}
#else
			const struct tm *const result = localtime(&now);

			if(result == (struct tm *)0)
			{
				fprintf(stderr, "Error in function localtime (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_FAILURE;
			}

			*time_struct = *result;
#endif

			time_struct->tm_year += 1900;
			time_struct->tm_mon += 1;
		}
	}

	return C_UTILS_SUCCESS;
}

c_utils_int16_t c_utils_validate_date(const c_utils_int32_t year, const c_utils_uint8_t month, const c_utils_uint8_t day, const c_utils_uint8_t is_future_date_valid)
{
	if(year < 1L)
	{
		fprintf(stderr, "Error in function c_utils_validate_date (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(month < 1u || month > 12u)
	{
		fprintf(stderr, "Error in function c_utils_validate_date (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(day < 1u || day > 31u)
	{
		fprintf(stderr, "Error in function c_utils_validate_date (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
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

		if(is_future_date_valid == 0u)
		{
			struct tm current_date;

			if(c_utils_get_current_time(&current_date) != C_UTILS_SUCCESS)
			{
				fprintf(stderr, "Error in function c_utils_validate_date, c_utils_get_current_time failed (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_FAILURE;
			}

			if((year % 4L == 0L && year % 100L != 0L) || (year % 400L == 0L))
			{
				days_in_month[1] = 29u;
			}

			if(day > days_in_month[month - 1u])
			{
				return C_UTILS_FAILURE;
			}

			if(year > (c_utils_int32_t)(current_date.tm_year) || (year == (c_utils_int32_t)(current_date.tm_year) && month > (c_utils_uint8_t)(current_date.tm_mon)) || (year == (c_utils_int32_t)(current_date.tm_year) && month == (c_utils_uint8_t)(current_date.tm_mon) && day > (c_utils_uint8_t)current_date.tm_mday))
			{
				return C_UTILS_FAILURE;
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
				return C_UTILS_FAILURE;
			}
		}
	}

	return C_UTILS_SUCCESS;
}

c_utils_int16_t c_utils_clear_standard_input(void)
{
#if defined(ESP_PLATFORM)
	fprintf(stderr, "Error in function c_utils_clear_standard_input, %s does not support this function (File: %s, Line: %d)...\n", c_utils_verify_os, __FILE__, __LINE__);

	return C_UTILS_FAILURE;
#else
	signed int characters = getchar();

	while(characters != '\n' && characters != EOF)
	{
		characters = getchar();
	}

	return C_UTILS_SUCCESS;
#endif
}

c_utils_int16_t c_utils_initialize(void)
{
	if(c_utils_is_initialized != 0u)
	{
		fprintf(stderr, "Error in function c_utils_initialize, C-Utils is already initialized (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

#if defined(_WIN32) || defined(_WIN64)
	if(c_utils_enable_virtual_terminal_and_utf8() != C_UTILS_SUCCESS)
	{
		fprintf(stderr, "Error in function c_utils_enable_virtual_terminal_and_utf8 (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

#endif

	c_utils_is_initialized = 1u;

	return C_UTILS_SUCCESS;
}

c_utils_int16_t c_utils_terminate(void)
{
	if(c_utils_is_initialized == 0u)
	{
		fprintf(stderr, "Error in function c_utils_terminate, C-Utils is not initialized (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	else
	{
		c_utils_uint32_t index;

		for(index = 0u; index < c_utils_addresses_to_free_count; index++)
		{
			if(c_utils_addresses_to_free[index] != (void *)0)
			{
				free(c_utils_addresses_to_free[index]);
				c_utils_addresses_to_free[index] = (void *)0;
			}
		}

		free(c_utils_addresses_to_free);

		c_utils_addresses_to_free = (void **)0;
		c_utils_addresses_to_free_count = 0u;
		c_utils_addresses_to_free_cap = 0u;
		c_utils_is_initialized = 0u;
	}

	return C_UTILS_SUCCESS;
}

c_utils_int16_t c_utils_mem_regist_to_free(const void *const address)
{
	if(address == (void *)0)
	{
		fprintf(stderr, "Error in function c_utils_mem_regist_to_free (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(c_utils_is_initialized == 0u)
	{
		fprintf(stderr, "Error in function c_utils_mem_regist_to_free (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	else
	{
		c_utils_uint32_t index;

		for(index = 0u; index < c_utils_addresses_to_free_count; index++)
		{
			if(c_utils_addresses_to_free[index] == address)
			{
				fprintf(stderr, "Error in function c_utils_mem_regist_to_free (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_FAILURE;
			}
		}

		if(c_utils_addresses_to_free_count >= c_utils_addresses_to_free_cap)
		{
			if(c_utils_addresses_to_free_cap > (c_utils_uint32_t)0x0FFFFFFFU)
			{
				fprintf(stderr, "Error in function c_utils_mem_regist_to_free (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				return C_UTILS_FAILURE;
			}

			else
			{
				c_utils_uint32_t new_cap = (c_utils_addresses_to_free_cap == 0u) ? 8u : (c_utils_addresses_to_free_cap << 1);
				void **new_block = (void **)realloc((void *)c_utils_addresses_to_free, (size_t)new_cap * sizeof(void *));

				if(new_block == (void **)0)
				{
					fprintf(stderr, "Error in function c_utils_mem_regist_to_free (File: %s, Line: %d)...\n", __FILE__, __LINE__);

					return C_UTILS_FAILURE;
				}

				else
				{
					c_utils_addresses_to_free = new_block;
					c_utils_addresses_to_free_cap = new_cap;
				}
			}
		}

		c_utils_addresses_to_free[c_utils_addresses_to_free_count] = (void *)address;
		c_utils_addresses_to_free_count++;
	}

	return C_UTILS_SUCCESS;
}

c_utils_int16_t c_utils_scan_enter(void)
{
#if defined(ESP_PLATFORM)
	fprintf(stderr, "Error in function c_utils_scan_enter, %s does not support this function (File: %s, Line: %d)...\n", c_utils_verify_os, __FILE__, __LINE__);

	return C_UTILS_FAILURE;
#else
	if(c_utils_clear_standard_input() != C_UTILS_SUCCESS)
	{
		fprintf(stderr, "Error in function c_utils_scan_enter (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(getchar() == EOF)
	{
		fprintf(stderr, "Error in function c_utils_scan_enter (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	return C_UTILS_SUCCESS;
#endif
}

c_utils_int16_t c_utils_url_opener(const c_utils_char_t *const url)
{
#if defined(__DOS__) || defined(MSDOS) || defined(_MSDOS) || defined (__MSDOS__) || defined(__DOS_386__) || defined(__DJGPP__)
	fprintf(stderr, "Error in function c_utils_url_opener, DOS does not support this function (File: %s, Line: %d)...\n", __FILE__, __LINE__);

	return C_UTILS_FAILURE;
#elif defined(ESP_PLATFORM)
	fprintf(stderr, "Error in function c_utils_url_opener, %s does not support this function (File: %s, Line: %d)...\n", c_utils_verify_os, __FILE__, __LINE__);

	return C_UTILS_FAILURE;
#else
	if(url == (c_utils_char_t *)0)
	{
		return C_UTILS_FAILURE;
	}
	
	else
	{
#if defined(_WIN32) || defined(_WIN64)
		HINSTANCE result = ShellExecuteA(
			(HWND)0,
			"open",
			url,
			(char *)0,
			(char *)0,
			SW_SHOWNORMAL
		);

		if((INT_PTR)result <= 32)
		{
			fprintf(stderr, "Error in function ShellExecuteA (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			fprintf(stderr, "Error code: %ld\n", (signed long int)(INT_PTR)result);

			return C_UTILS_FAILURE;
		}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		pid_t pid = fork();

		if(pid == -1)
		{
			perror("\"fork\" error");

			return C_UTILS_FAILURE;
		}

		if(pid == 0)
		{
			const c_utils_char_t *arguments[3];

			arguments[1] = url;
			arguments[2] = (char *)0;

#if defined(__linux__) || defined(__ANDROID__)
			arguments[0] = "xdg-open";
			execv("/usr/bin/xdg-open", (c_utils_char_t *const *)arguments);
#elif defined(__APPLE__)
			arguments[0] = "open";
			execv("/usr/bin/open", (c_utils_char_t *const *)arguments);
#endif
			_exit(1);
		}

		waitpid(pid, (int *)0, 0);
#endif
	}

	return C_UTILS_SUCCESS;
#endif
}

c_utils_int16_t c_utils_sleep(const c_utils_uint32_t seconds, const c_utils_uint16_t milliseconds)
{
#if defined(__DOS__) || defined(MSDOS) || defined(_MSDOS) || defined (__MSDOS__) || defined(__DOS_386__) || defined(__DJGPP__)
	fprintf(stderr, "Error in function c_utils_sleep, DOS does not support this function (File: %s, Line: %d)...\n", __FILE__, __LINE__);

	return C_UTILS_FAILURE;
#else
	if(seconds == 0u && milliseconds == 0u)
	{
		fprintf(stderr, "Error in function c_utils_sleep, invalid time (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	if(milliseconds > 999U)
	{
		fprintf(stderr, "Error in function c_utils_sleep, invalid time (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

#if defined(_WIN32) || defined(_WIN64)
	if(seconds > (0xFFFFFFFF - (c_utils_uint32_t)milliseconds) / 1000u)
	{
		fprintf(stderr, "Error in function c_utils_sleep, invalid time (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	Sleep((DWORD)seconds * 1000u + (DWORD)milliseconds);
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	if(seconds > 0U)
	{
		if(sleep(seconds) > 0)
		{
			fprintf(stderr, "Error in function sleep (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			perror("Error");

			return C_UTILS_FAILURE;
		}
	}

	if(milliseconds > 0u)
	{
		if(usleep((useconds_t)(milliseconds * 1000u)) == -1)
		{
			fprintf(stderr, "Error in function usleep (File: %s, Line: %d)...\n", __FILE__, __LINE__);
			perror("Error");

			return C_UTILS_FAILURE;
		}
	}
#elif defined(ESP_PLATFORM)
	vTaskDelay(pdMS_TO_TICKS(seconds * 1000u + milliseconds));
#else
	return C_UTILS_FAILURE;
#endif

	return C_UTILS_SUCCESS;
#endif
}

c_utils_int16_t c_utils_make_directory(const c_utils_char_t *const path, c_utils_uint32_t mode)
{
#if defined(ESP_PLATFORM)
	fprintf(stderr, "Error in function c_utils_make_directory, %s does not support this function (File: %s, Line: %d)...\n", c_utils_verify_os, __FILE__, __LINE__);

	return C_UTILS_FAILURE;
#else
	if(path == (c_utils_char_t *)0)
	{
		fprintf(stderr, "Error in function c_utils_make_directory (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64) \
 || defined(__DOS__) || defined(MSDOS) || defined(_MSDOS) || defined (__MSDOS__) || defined(__DOS_386__) || defined(__DJGPP__)
		(void)mode;
#if !defined(_WIN32) && !defined(_WIN64)
		if(mkdir(path) != 0)
#else
		if(_mkdir(path) != 0)
#endif
		{
#if !defined(_WIN32) && !defined(_WIN64)
			fprintf(stderr, "Error in function mkdir (File: %s, Line: %d)...\n", __FILE__, __LINE__);
#else
			fprintf(stderr, "Error in function _mkdir (File: %s, Line: %d)...\n", __FILE__, __LINE__);
#endif
			perror("Error");

			return C_UTILS_FAILURE;
		}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		if(mode == 0UL)
		{
			mode = 0755UL;
		}

		if(mkdir(path, (mode_t)mode) != 0)
		{
			fprintf(stderr, "Error in function mkdir (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			perror("Error");

			return C_UTILS_FAILURE;
		}
#endif
	}

	return C_UTILS_SUCCESS;
#endif
}

signed int c_utils_scan_character(void)
{
#if defined(ESP_PLATFORM)
	fprintf(stderr, "Error in function c_utils_scan_character, %s does not support this function (File: %s, Line: %d)...\n", c_utils_verify_os, __FILE__, __LINE__);

	return (signed int)C_UTILS_FAILURE;
#else
#if defined(_WIN32) || defined(_WIN64) || defined(__DOS__) || defined(MSDOS) || defined(_MSDOS) || defined (__MSDOS__) || defined(__DOS_386__) || defined(__DJGPP__)
	signed int character =
#if !defined(_WIN32) && !defined(_WIN64)
		getch()
#else
		_getch()
#endif
	;

	return character;
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	struct termios old_terminal;

	if(tcgetattr(STDIN_FILENO, &old_terminal) == -1)
	{
		perror("\"tcgetattr\" error");

		return (signed int)C_UTILS_FAILURE;
	}

	else
	{
		struct termios new_terminal = old_terminal;

		new_terminal.c_lflag &= (tcflag_t) ~(ICANON | ECHO);
		new_terminal.c_cc[VMIN] = 1;
		new_terminal.c_cc[VTIME] = 0;

		if(tcsetattr(STDIN_FILENO, TCSANOW, &new_terminal) == -1)
		{
			perror("\"tcsetattr\" error");

			return (signed int)C_UTILS_FAILURE;
		}

		else
		{
			c_utils_char_t keyword;
			ssize_t result = read(STDIN_FILENO, &keyword, 1U);

			if(result == 0)
			{
				if(tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal) == -1)
				{
					return (signed int)C_UTILS_FAILURE;
				}

				return (signed int)C_UTILS_FAILURE;
			}

			else if(result < 0)
			{
				perror("\"read\" error");

				if(tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal) == -1)
				{
					return (signed int)C_UTILS_FAILURE;
				}

				return (signed int)C_UTILS_FAILURE;
			}

			else
			{
				signed int character = (c_utils_uint8_t)keyword;

				if(tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal) == -1)
				{
					return (signed int)C_UTILS_FAILURE;
				}

				return character;
			}
		}
	}
#else
	return (signed int)C_UTILS_FAILURE;
#endif
#endif
}

void *c_utils_mem_allocate(const void *const old_pointer, const size_t size)
{
	if(size == 0u)
	{
		fprintf(stderr, "Error in function c_utils_mem_allocate (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return (void *)0;
	}

	if(old_pointer == (void *)0)
	{
		void *pointer = malloc(size);

		if(pointer == (void *)0)
		{
			fprintf(stderr, "Error in function c_utils_mem_allocate (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return (void *)0;
		}

		if(c_utils_mem_regist_to_free(pointer) != C_UTILS_SUCCESS)
		{
			fprintf(stderr, "Error in function c_utils_mem_allocate (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			free(pointer);
			pointer = (void *)0;
		}

		return pointer;
	}

	else
	{
		size_t saved_address  = (size_t)old_pointer;
		const void *const new_pointer = realloc((void *)old_pointer, size);

		if(new_pointer == (void *)0)
		{
			fprintf(stderr, "Error in function c_utils_mem_allocate (File: %s, Line: %d)...\n", __FILE__, __LINE__);

			return ((void *)0);
		}

		if(new_pointer == (void *)saved_address)
		{
			return (void *)new_pointer;
		}

		else
		{
			c_utils_uint32_t index;

			for(index = 0u; index < c_utils_addresses_to_free_count; index++)
			{
				if((size_t)c_utils_addresses_to_free[index] == saved_address)
				{
					c_utils_addresses_to_free[index] = (void *)new_pointer;

					return (void *)new_pointer;
				}
			}

			if(c_utils_mem_regist_to_free(new_pointer) != C_UTILS_SUCCESS)
			{
				fprintf(stderr, "Error in function c_utils_mem_allocate (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				free((void *)new_pointer);

				return (void *)0;
			}
		}

		return (void *)new_pointer;
	}
}

const c_utils_char_t *c_utils_read_file(const c_utils_char_t *const path)
{
#if defined(ESP_PLATFORM)
	fprintf(stderr, "Error in function c_utils_read_file, %s does not support this function (File: %s, Line: %d)...\n", c_utils_verify_os, __FILE__, __LINE__);

	return (c_utils_char_t *)0;
#else
	if(c_utils_is_initialized == 0u)
	{
		fprintf(stderr, "Error in function c_utils_read_file, C-Utils not initialized (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return (c_utils_char_t *)0;
	}

	if(path == (c_utils_char_t *)0)
	{
		fprintf(stderr, "Error in function c_utils_read_file, invalid path (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return (c_utils_char_t *)0;
	}

	else
	{
		FILE *const file = fopen(path, "rb");

		if(file == (FILE *)0)
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

			return (c_utils_char_t *)0;
		}

		else
		{
			if(fseek(file, 0L, SEEK_END) != 0)
			{
				fprintf(stderr, "Error in function fseek (File: %s, Line: %d)...\n", __FILE__, __LINE__);

				if(fclose(file) != 0)
				{
					fprintf(stderr, "Error in function fclose (File: %s, Line: %d)...\n", __FILE__, __LINE__);
					perror("Error");
				}

				return (c_utils_char_t *)0;
			}

			else
			{
				const signed long int size = ftell(file);

				if(size < 0L)
				{
					if(fclose(file) != 0)
					{
						fprintf(stderr, "Error in function fclose (File: %s, Line: %d)...\n", __FILE__, __LINE__);
						perror("Error");
					}

					return (c_utils_char_t *)0;
				}

				else
				{
					c_utils_char_t *buffer = (c_utils_char_t *)malloc((size_t)size + 1U);

					if(buffer == (c_utils_char_t *)0)
					{
						if(fclose(file) != 0)
						{
							fprintf(stderr, "Error in function fclose (File: %s, Line: %d)...\n", __FILE__, __LINE__);
							perror("Error");
						}

						return (c_utils_char_t *)0;
					}

					if(fseek(file, 0L, SEEK_SET) != 0)
					{
						fprintf(stderr, "Error in function fseek (File: %s, Line: %d)...\n", __FILE__, __LINE__);

						free(buffer);

						if(fclose(file) != 0)
						{
							fprintf(stderr, "Error in function fclose (File: %s, Line: %d)...\n", __FILE__, __LINE__);
							perror("Error");
						}

						return (c_utils_char_t *)0;
					}

					clearerr(file);

					if(fread(buffer, 1U, (size_t)size, file) != (size_t)size)
					{
						free(buffer);

						if(fclose(file) != 0)
						{
							fprintf(stderr, "Error in function fclose (File: %s, Line: %d)...\n", __FILE__, __LINE__);
							perror("Error");
						}

						return (c_utils_char_t *)0;
					}

					buffer[size] = '\0';

					if(fclose(file) != 0)
					{
						fprintf(stderr, "Error in function fclose (File: %s, Line: %d)...\n", __FILE__, __LINE__);
						perror("Error");
					}

					if(c_utils_mem_regist_to_free((void *)buffer) != C_UTILS_SUCCESS)
					{
						fprintf(stderr, "Error in function c_utils_regist_address_to_free (File: %s, Line: %d)...\n", __FILE__, __LINE__);

						free((void *)buffer);

						return (c_utils_char_t *)0;
					}

					return buffer;
				}
			}
		}
	}
#endif
}

const c_utils_char_t *c_utils_verify_os(void)
{
#if defined(_WIN32) || defined(_WIN64)
	return "Windows";
#elif defined(__linux__)
	const c_utils_char_t *const is_wayland = getenv("WAYLAND_DISPLAY");
	const c_utils_char_t *const is_x11 = getenv("DISPLAY");

	if(is_wayland)
	{
		if(is_x11)
		{
			return "Linux, Wayland and XWayland";
		}

		else
		{
			return "Linux, Wayland";
		}
	}

	else if(is_x11)
	{
		return "Linux, X11";
	}

	else
	{
		return "Linux (No graphics)";
	}
#elif defined(__ANDROID__)
	return "Android";
#elif defined(__APPLE__)
#if TARGET_OS_OSX
	return "macOS";
#elif TARGET_OS_IOS
	return "iOS";
#elif TARGET_OS_TV
	return "tvOS";
#elif TARGET_OS_WATCH
	return "watchOS";
#else
	return "Apple (unknown OS)";
#endif
#elif defined(__DOS__) || defined(MSDOS) || defined(_MSDOS) || defined (__MSDOS__) || defined(__DOS_386__) || defined(__DJGPP__)
	return "DOS";
#elif defined(ESP_PLATFORM)
#if defined(CONFIG_IDF_TARGET_ESP32)
	return "ESP32";
#elif defined(CONFIG_IDF_TARGET_ESP32S2)
	return "ESP32-S2";
#elif defined(CONFIG_IDF_TARGET_ESP32S3)
	return "ESP32-S3";
#elif defined(CONFIG_IDF_TARGET_ESP32C2)
	return "ESP32-C2";
#elif defined(CONFIG_IDF_TARGET_ESP32C3)
	return "ESP32-C3";
#elif defined(CONFIG_IDF_TARGET_ESP32C5)
	return "ESP32-C5";
#elif defined(CONFIG_IDF_TARGET_ESP32C6)
	return "ESP32-C6";
#elif defined(CONFIG_IDF_TARGET_ESP32C61)
	return "ESP32-C61";
#elif defined(CONFIG_IDF_TARGET_ESP32H2)
	return "ESP32-H2";
#elif defined(CONFIG_IDF_TARGET_ESP32P4)
	return "ESP32-P4";
#else
	return "ESP (unknown model)";
#endif
#else
	return "Unknown OS";
#endif
}

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif
