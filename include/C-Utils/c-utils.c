/* Importations: */
#include "c-utils.h"
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
#endif


/* Import C to C++: */
#ifdef __cplusplus
extern "C"
{
#endif

void c_utils_clear_standard_output(void)
{
	fputs("\033[2J\033[3J\033[H", stdout);

	return;
}

c_utils_int16_t c_utils_validate_date(const c_utils_int32_t year, const c_utils_int32_t month, const c_utils_int32_t day)
{
	if(year < 1L)
	{
		return C_UTILS_FAILURE;
	}

	if(month < 1L || month > 12L)
	{
		return C_UTILS_FAILURE;
	}

	else
	{
		c_utils_int8_t days_in_month[12] =
		{
			31,
			28,
			31,
			30,
			31,
			30,
			31,
			31,
			30,
			31,
			30,
			31
		};
		struct tm current_date = c_utils_current_time();

		if((year % 4L == 0L && year % 100L != 0L) || (year % 400L == 0L))
		{
			*(days_in_month + 1) = 29;
		}

		if(day < 1L || day > (c_utils_int32_t)*(days_in_month + month - 1L))
		{
			return C_UTILS_FAILURE;
		}

		if(year > (c_utils_int32_t)(current_date.tm_year + 1900) || (year == (c_utils_int32_t)(current_date.tm_year + 1900) && month > (c_utils_int32_t)(current_date.tm_mon + 1)) || (year == (c_utils_int32_t)(current_date.tm_year + 1900) && month == (c_utils_int32_t)(current_date.tm_mon + 1) && day > (c_utils_int32_t)current_date.tm_mday))
		{
			return C_UTILS_FAILURE;
		}

		return C_UTILS_SUCCESS;
	}
}

c_utils_int16_t c_utils_validate_date_future(const c_utils_int32_t year, const c_utils_int32_t month, const c_utils_int32_t day)
{
	if(year < 1L)
	{
		return C_UTILS_FAILURE;
	}

	if(month < 1L || month > 12L)
	{
		return C_UTILS_FAILURE;
	}

	else
	{
		c_utils_int8_t days_in_month[12] =
		{
			31,
			28,
			31,
			30,
			31,
			30,
			31,
			31,
			30,
			31,
			30,
			31
		};

		if((year % 4L == 0L && year % 100L != 0L) || (year % 400L == 0L))
		{
			*(days_in_month + 1) = 29;
		}

		if(day < 1L || day > (c_utils_int32_t)*(days_in_month + month - 1L))
		{
			return C_UTILS_FAILURE;
		}

		return C_UTILS_SUCCESS;
	}
}

c_utils_int16_t c_utils_clear_standard_input(void)
{
	signed int characters = getchar();

	while(characters != '\n' && characters != EOF)
	{
		characters = getchar();
	}

	return C_UTILS_SUCCESS;
}

c_utils_int16_t c_utils_enable_virtual_terminal_and_utf8(void)
{
#if defined(_WIN32) || defined(_WIN64)
	HANDLE hOut;
	DWORD mode;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if(hOut == INVALID_HANDLE_VALUE)
	{
		return C_UTILS_FAILURE;
	}

	mode = 0u;

	if(!GetConsoleMode(hOut, &mode))
	{
		return C_UTILS_FAILURE;
	}

	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	if(!SetConsoleMode(hOut, mode))
	{
		DWORD err;
		err = GetLastError();
		(void)err;

		return C_UTILS_FAILURE;
	}
	
	if(!SetConsoleOutputCP(CP_UTF8))
	{
		DWORD err;
		err = GetLastError();
		(void)err;

		return C_UTILS_FAILURE;
	}

	return C_UTILS_SUCCESS;
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	return C_UTILS_SUCCESS;
#else
	return C_UTILS_FAILURE;
#endif
}

c_utils_int16_t c_utils_initialize(void)
{
	if(c_utils_enable_virtual_terminal_and_utf8())
	{
		return C_UTILS_FAILURE;
	}

	return C_UTILS_SUCCESS;
}

c_utils_int16_t c_utils_scan_enter(void)
{
	if(c_utils_clear_standard_input())
	{
		return C_UTILS_FAILURE;
	}

	if(getchar() == EOF)
	{
		return C_UTILS_FAILURE;
	}

	return C_UTILS_SUCCESS;
}

c_utils_int16_t c_utils_url_opener(const c_utils_char_t *const url)
{
	if(url == (void *)0)
	{
		return C_UTILS_FAILURE;
	}
	
	else
	{
#if defined(_WIN32) || defined(_WIN64)
		ShellExecuteA((void *)0, "open", url, (void *)0, (void *)0, SW_SHOWNORMAL);
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

#if defined(__linux__) || defined(__ANDROID__)
			*arguments = "xdg-open";
			*(arguments + 1) = url;
			*(arguments + 2) = (void *)0;
			execv("/usr/bin/xdg-open", (c_utils_char_t *const *)arguments);
#elif defined(__APPLE__)
			*arguments = "open";
			*(arguments + 1) = url;
			*(arguments + 2) = (void *)0;
			execv("/usr/bin/open", (c_utils_char_t *const *)arguments);
#endif
			_exit(1);
		}

		waitpid(pid, (void *)0, 0);

#endif
		return C_UTILS_SUCCESS;
	}
}

c_utils_int16_t c_utils_ssleep(const c_utils_uint32_t time)
{
	if(time == 0U)
	{
		return C_UTILS_FAILURE;
	}

#if defined(_WIN32) || defined(_WIN64)
	if(time > 4294967295 / 1000)
	{
		return C_UTILS_FAILURE;
	}

	Sleep((DWORD)time * (DWORD)1000U);

#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	if(sleep(time) > 0)
	{
		fputs("Sleep failed...\n", stderr);
		perror("Error");

		return C_UTILS_FAILURE;
	}

#else
	return C_UTILS_FAILURE;
#endif
	return C_UTILS_SUCCESS;
}

c_utils_int16_t c_utils_mssleep(const c_utils_uint32_t time)
{
	if(time == 0UL)
	{
		return C_UTILS_FAILURE;
	}

#if defined(_WIN32) || defined(_WIN64)
	Sleep((DWORD)time);

#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	if(time > 4294967295 / 1000)
	{
		return C_UTILS_FAILURE;
	}

	if(usleep(time * 1000) == -1)
	{
		fputs("Sleep failed...\n", stderr);
		perror("Error");

		return C_UTILS_FAILURE;
	}

#else
	return C_UTILS_FAILURE;
#endif
	return C_UTILS_SUCCESS;
}

c_utils_int16_t c_utils_make_directory(const c_utils_char_t *const path, c_utils_uint32_t mode)
{
	if(path == (void *)0)
	{
		return C_UTILS_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		if(!_mkdir(path))
		{
			return C_UTILS_SUCCESS;
		}

		fputs("Error in function _mkdir...\n", stderr);
		perror("Error");
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		if(!mode)
		{
			mode = 0755L;
		}

		if(mkdir(path, (mode_t)mode) == 0)
		{
			return C_UTILS_SUCCESS;
		}

		fputs("Error in function mkdir...\n", stderr);
		perror("Error");
#endif

		return C_UTILS_FAILURE;
	}
}

signed int c_utils_scan_character(void)
{
	signed int character;
#if defined(_WIN32) || defined(_WIN64)

	character = _getch();
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	signed int keyword;
	ssize_t result;
	struct termios old_terminal;
	struct termios new_terminal;

	if(tcgetattr(STDIN_FILENO, &old_terminal) == -1)
	{
		perror("\"tcgetattr\" error");

		return (signed int)C_UTILS_FAILURE;
	}

	new_terminal = old_terminal;
	new_terminal.c_lflag &= (tcflag_t) ~(ICANON | ECHO);
	*(new_terminal.c_cc + VMIN) = 1;
	*(new_terminal.c_cc + VTIME) = 0;

	if(tcsetattr(STDIN_FILENO, TCSANOW, &new_terminal) == -1)
	{
		perror("\"tcsetattr\" error");

		return (signed int)C_UTILS_FAILURE;
	}

	result = read(STDIN_FILENO, &keyword, 1U);

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

	character = keyword;

	if(tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal) == -1)
	{
		return (signed int)C_UTILS_FAILURE;
	}
#else
	return (signed int)C_UTILS_FAILURE;
#endif

	return character;
}

size_t c_utils_linear_char_t_search(const c_utils_char_t *const array, const size_t count, const c_utils_char_t target)
{
	if(!array)
	{
		return C_UTILS_FAILURE;
	}

	else
	{
		size_t index;

		for(index = 0U; index < count; index++)
		{
			if(*(array + index) == target)
			{
				return index;
			}
		}
	}

	return C_UTILS_FAILURE;
}

size_t c_utils_linear_int16_t_search(const c_utils_int16_t *const array, const size_t count, const c_utils_int16_t target)
{
	if(!array)
	{
		return C_UTILS_FAILURE;
	}

	else
	{
		size_t index;

		for(index = 0U; index < count; index++)
		{
			if(*(array + index) == target)
			{
				return index;
			}
		}
	}

	return C_UTILS_FAILURE;
}

size_t c_utils_linear_int32_t_search(const c_utils_int32_t *const array, const size_t count, const c_utils_int32_t target)
{
	if(!array)
	{
		return C_UTILS_FAILURE;
	}

	else
	{
		size_t index;

		for(index = 0U; index < count; index++)
		{
			if(*(array + index) == target)
			{
				return index;
			}
		}
	}

	return C_UTILS_FAILURE;
}

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L) || defined(C_UTILS_ENABLE_LONG_LONG_INT) || defined(C_UTILS_ENABLE_ALL_EXTENSIONS)
size_t c_utils_linear_int64_t_search(const c_utils_int64_t *const array, const size_t count, const c_utils_int64_t target)
{
	if(!array)
	{
		return C_UTILS_FAILURE;
	}

	else
	{
		size_t index;

		for(index = 0U; index < count; index++)
		{
			if(*(array + index) == target)
			{
				return index;
			}
		}
	}

	return C_UTILS_FAILURE;
}
#endif

size_t c_utils_linear_float32_t_search(const c_utils_float32_t *const array, const size_t count, const c_utils_float32_t target)
{
	if(!array)
	{
		return C_UTILS_FAILURE;
	}

	else
	{
		size_t index;

		for(index = 0U; index < count; index++)
		{
			const c_utils_float32_t difference = *(array + index) - target;

			if((difference < 0.0f ? -difference : difference) < 10 * FLT_EPSILON)
			{
				return index;
			}
		}
	}

	return C_UTILS_FAILURE;
}

size_t c_utils_linear_float64_t_search(const c_utils_float64_t *const array, const size_t count, const c_utils_float64_t target)
{
	if(!array)
	{
		return C_UTILS_FAILURE;
	}

	else
	{
		size_t index;

		for(index = 0U; index < count; index++)
		{
			const c_utils_float64_t difference = *(array + index) - target;

			if((difference < 0.0 ? -difference : difference) < 10 * DBL_EPSILON)
			{
				return index;
			}
		}
	}

	return C_UTILS_FAILURE;
}

size_t c_utils_linear_char_t_array_search(const c_utils_char_t *const *const array, const size_t count, const c_utils_char_t *const target)
{
	if(!array || !target)
	{
		return C_UTILS_FAILURE;
	}

	else
	{
		size_t index;

		for(index = 0U; index < count; index++)
		{
			if(!strcmp(*(array + index), target))
			{
				return index;
			}
		}
	}

	return C_UTILS_FAILURE;
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
#else
	return "Unknown OS";
#endif
}

c_utils_char_t *c_utils_read_file(const c_utils_char_t *const path)
{
	FILE *file;

	if(!(file = fopen(path, "rb")))
	{
		return (void *)0;
	}

	else
	{
		if(fseek(file, 0L, SEEK_END) != 0)
		{
			fclose(file);

			return (void *)0;
		}

		else
		{
			const c_utils_int32_t size = (c_utils_int32_t)ftell(file);

			if(size < 0L)
			{
				fclose(file);

				return (void *)0;
			}

			else
			{
				c_utils_char_t *const buffer = (c_utils_char_t *const)malloc((size_t)size + 1U);

				if(buffer == (void *)0)
				{
					fclose(file);

					return (void *)0;
				}

				rewind(file);

				if(fread(buffer, 1U, (size_t)size, file) != (size_t)size)
				{
					free(buffer);
					fclose(file);

					return (void *)0;
				}

				*(buffer + size) = '\0';

				fclose(file);

				return buffer;
			}
		}
	}
}

struct tm c_utils_current_time(void)
{
	struct tm result;
	const time_t now = time((void *)0);

#if defined(_WIN32) || defined(_WIN64)
	localtime_s(&result, &now);
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	localtime_r(&now, &result);
#endif

	return result;
}

/* End C to C++ importation: */
#ifdef __cplusplus
}
#endif
