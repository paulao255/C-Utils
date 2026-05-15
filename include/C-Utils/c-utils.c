/* Importations: */
#include "c-utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <float.h>
#include <time.h>
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

signed short int c_utils_validate_date(const signed long int year, const signed long int month, const signed long int day)
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
		signed short int days_in_month[12] = {
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

		if(day < 1L || day > (signed long int)*(days_in_month + month - 1L))
		{
			return C_UTILS_FAILURE;
		}

		if(year > (signed long int)(current_date.tm_year + 1900) || (year == (signed long int)(current_date.tm_year + 1900) && month > (signed long int)(current_date.tm_mon + 1)) || (year == (signed long int)(current_date.tm_year + 1900) && month == (signed long int)(current_date.tm_mon + 1) && day > (signed long int)current_date.tm_mday))
		{
			return C_UTILS_FAILURE;
		}

		return C_UTILS_SUCCESS;
	}
}

signed short int c_utils_validate_date_future(const signed long int year, const signed long int month, const signed long int day)
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
		signed short int days_in_month[12] =
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

		if(day < 1L || day > (signed long int)*(days_in_month + month - 1L))
		{
			return C_UTILS_FAILURE;
		}

		return C_UTILS_SUCCESS;
	}
}

signed short int c_utils_clear_standard_input(void)
{
	signed int characters = getchar();

	while(characters != '\n' && characters != EOF)
	{
		characters = getchar();
	}

	return C_UTILS_SUCCESS;
}

signed short int c_utils_enable_virtual_terminal_and_utf8(void)
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

signed short int c_utils_initialize(void)
{
	if(c_utils_enable_virtual_terminal_and_utf8())
	{
		return C_UTILS_FAILURE;
	}

	return C_UTILS_SUCCESS;
}

signed short int c_utils_scan_enter(void)
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

signed short int c_utils_url_opener(const char *const url)
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
			const char *arguments[3];

#if defined(__linux__) || defined(__ANDROID__)
			*arguments = "xdg-open";
			*(arguments + 1) = url;
			*(arguments + 2) = (void *)0;
			execv("/usr/bin/xdg-open", (char *const *)arguments);
#elif defined(__APPLE__)
			*arguments = "open";
			*(arguments + 1) = url;
			*(arguments + 2) = (void *)0;
			execv("/usr/bin/open", (char *const *)arguments);
#endif
			_exit(1);
		}

		waitpid(pid, (void *)0, 0);

#endif
		return C_UTILS_SUCCESS;
	}
}

signed short int c_utils_ssleep(const unsigned int time)
{
	if(time == 0U)
	{
		return C_UTILS_FAILURE;
	}

#if defined(_WIN32) || defined(_WIN64)
	if(time > UINT_MAX / 1000)
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

signed short int c_utils_mssleep(const unsigned int time)
{
	if(time == 0U)
	{
		return C_UTILS_FAILURE;
	}

#if defined(_WIN32) || defined(_WIN64)
	Sleep((DWORD)time);

#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	if(time > UINT_MAX / 1000)
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

signed short int c_utils_make_directory(const char *const path, unsigned int mode)
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
			mode = 0755;
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

size_t c_utils_linear_char_search(const char *const array, const size_t count, const char target)
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

size_t c_utils_linear_signed_short_int_search(const signed short int *const array, const size_t count, const signed short int target)
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

size_t c_utils_linear_signed_int_search(const signed int *const array, const size_t count, const signed int target)
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

size_t c_utils_linear_signed_long_int_search(const signed long int *const array, const size_t count, const signed long int target)
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

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L) || defined(C_UTILS_ENABLE_LONG_LONG_INT)
size_t c_utils_linear_signed_long_long_int_search(const signed long long int *const array, const size_t count, const signed long long int target)
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

size_t c_utils_linear_float_search(const float *const array, const size_t count, const float target)
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
			const float difference = *(array + index) - target;

			if((difference < 0.0f ? -difference : difference) < 10 * FLT_EPSILON)
			{
				return index;
			}
		}
	}

	return C_UTILS_FAILURE;
}

size_t c_utils_linear_double_search(const double *const array, const size_t count, const double target)
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
			const double difference = *(array + index) - target;

			if((difference < 0.0 ? -difference : difference) < 10 * DBL_EPSILON)
			{
				return index;
			}
		}
	}

	return C_UTILS_FAILURE;
}

size_t c_utils_linear_long_double_search(const long double *const array, const size_t count, const long double target)
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
			const long double difference = *(array + index) - target;

			if((difference < 0.0L ? -difference : difference) < 10 * LDBL_EPSILON)
			{
				return index;
			}
		}
	}

	return C_UTILS_FAILURE;
}

size_t c_utils_linear_array_search(const char *const *const array, const size_t count, const char *const target)
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

const char *c_utils_verify_os(void)
{
#if defined(_WIN32) || defined(_WIN64)
	return "Windows";
#elif defined(__linux__)
	const char *const is_wayland = getenv("WAYLAND_DISPLAY");
	const char *const is_x11 = getenv("DISPLAY");

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

char *c_utils_read_file(const char *const path)
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
			const signed long int size = ftell(file);

			if(size < 0L)
			{
				fclose(file);

				return (void *)0;
			}

			else
			{
				char *const buffer = (char *const)malloc((size_t)size + 1U);

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
