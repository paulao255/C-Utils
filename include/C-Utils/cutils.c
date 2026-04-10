/* Importations: */
#include "cutils.h"
#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
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

struct tm c_utils_get_current_time(void)
{
	struct tm result;
	const time_t now = time(NULL);

#if defined(_WIN32) || defined(_WIN64)
	localtime_s(&result, &now);
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	localtime_r(&now, &result);
#endif

	return result;
}

struct tm *c_utils_current_time(void)
{
	static struct tm result;
	const time_t now = time(NULL);

#if defined(_WIN32) || defined(_WIN64)
	localtime_s(&result, &now);
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	localtime_r(&now, &result);
#endif

	return &result;
}

int c_utils_clear_stdout(void)
{
	fputs("\033[2J\033[3J\033[H", stdout);

	return C_UTILS_SUCCESS;
}

int c_utils_clear_stdin(void)
{
	int characters = getchar();

	while(characters != '\n' && characters != EOF)
	{
		characters = getchar();
	}

	return C_UTILS_SUCCESS;
}

int c_utils_scan_enter(void)
{
	if(c_utils_clear_stdin() < 0)
	{
		return C_UTILS_INTERNAL_FAILURE;
	}

	if(getchar() == EOF)
	{
		return C_UTILS_STANDARD_FAILURE;
	}

	return C_UTILS_SUCCESS;
}

int c_utils_enable_virtual_terminal_and_utf8(void)
{
#if defined(_WIN32) || defined(_WIN64)
	HANDLE hOut;
	DWORD mode;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if(hOut == INVALID_HANDLE_VALUE)
	{
		return C_UTILS_STANDARD_FAILURE;
	}

	mode = 0u;

	if(!GetConsoleMode(hOut, &mode))
	{
		return C_UTILS_STANDARD_FAILURE;
	}

	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	if(!SetConsoleMode(hOut, mode))
	{
		DWORD err;
		err = GetLastError();
		(void)err;

		return C_UTILS_STANDARD_FAILURE;
	}
	
	if(!SetConsoleOutputCP(CP_UTF8))
	{
		DWORD err;
		err = GetLastError();
		(void)err;

		return C_UTILS_STANDARD_FAILURE;
	}

#else
	return C_UTILS_STANDARD_FAILURE;
#endif
	return C_UTILS_SUCCESS;
}

int c_utils_scan_char(void)
{
#if defined(_WIN32) || defined(_WIN64)
	int character;

	if(fflush(stdout) == EOF)
	{
		fputs("Error while flushing standard output...\n", stderr);

		return C_UTILS_STANDARD_FAILURE;
	}

	character = _getch();
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	struct termios old_terminal;
	struct termios new_terminal;
	int character;

	if(fflush(stdout) == EOF)
	{
		fputs("Error while flushing standard output...", stderr);

		return C_UTILS_STANDARD_FAILURE;
	}
		
	if(tcgetattr(STDIN_FILENO, &old_terminal) == -1)
	{
		perror("\"tcgetattr\" error");

		return C_UTILS_STANDARD_FAILURE;
	}

	new_terminal = old_terminal;
	new_terminal.c_lflag &= (tcflag_t) ~(ICANON | ECHO);
	*(new_terminal.c_cc + VMIN) = 1;
	*(new_terminal.c_cc + VTIME) = 0;

	if(tcsetattr(STDIN_FILENO, TCSANOW, &new_terminal) == -1)
	{
		perror("\"tcsetattr\" error");

		return C_UTILS_STANDARD_FAILURE;
	}

	character = getchar();

	if(character == EOF)
	{
		if(tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal) == -1)
		{
			return C_UTILS_STANDARD_FAILURE;
		}

		return C_UTILS_STANDARD_FAILURE;
	}

	if(tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal) == -1)
	{
		return C_UTILS_STANDARD_FAILURE;
	}
#else
	return C_UTILS_INTERNAL_FAILURE;
#endif

	return character;
}

int c_utils_rrmf(void)
{
#if defined(_WIN32) || defined(_WIN64)
	if(system("more /C /P .\\README.md") == -1)
	{
		perror("\"system\" error");

		return C_UTILS_STANDARD_FAILURE;
	}

	if(c_utils_scan_char() < 0)
	{
		return C_UTILS_INTERNAL_FAILURE;
	}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	if(system("more -cp ./README.md") == -1)
	{
		perror("\"system\" error");

		return C_UTILS_STANDARD_FAILURE;
	}

	if(c_utils_scan_char() < 0)
	{
		return C_UTILS_INTERNAL_FAILURE;
	}
#else
	return C_UTILS_STANDARD_FAILURE;
#endif

	return C_UTILS_SUCCESS;
}

int c_utils_rlf(void)
{
#if defined(_WIN32) || defined(_WIN64)
	if(system("more /C /P .\\LICENSE") == -1)
	{
		perror("\"system\" error");

		return C_UTILS_STANDARD_FAILURE;
	}

	if(c_utils_scan_char() < 0)
	{
		return C_UTILS_INTERNAL_FAILURE;
	}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	if(system("more -cp ./LICENSE") == -1)
	{
		perror("\"system\" error");

		return C_UTILS_STANDARD_FAILURE;
	}

	if(c_utils_scan_char() < 0)
	{
		return C_UTILS_INTERNAL_FAILURE;
	}
#else
	return C_UTILS_STANDARD_FAILURE;
#endif

	return C_UTILS_SUCCESS;
}

int c_utils_url_opener(const char *const url)
{
	if(!url)
	{
		return C_UTILS_INPUT_FAILURE;
	}
	
	else
	{
#if defined(_WIN32) || defined(_WIN64)
		ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		pid_t pid = fork();

		if(pid == -1)
		{
			perror("\"fork\" error");

			return C_UTILS_STANDARD_FAILURE;
		}

		if(pid == 0)
		{
#if defined(__linux__) || defined(__ANDROID__)
			char *arguments[3];
			*arguments = "xdg-open";
			*(arguments + 1) = (char *)url;
			*(arguments + 2) = NULL;
			execv("/usr/bin/xdg-open", arguments);
#elif defined(__APPLE__)
			char *arguments[3];
			*arguments = "open";
			*(arguments + 1) = (char *)url;
			*(arguments + 2) = NULL;
			execv("/usr/bin/open", arguments);
#endif
			_exit(1);
		}

		waitpid(pid, NULL, 0);

#endif
		return C_UTILS_SUCCESS;
	}
}

int c_utils_ssleep(const unsigned int time)
{
	if(time == 0U)
	{
		return C_UTILS_INPUT_FAILURE;
	}

#if defined(_WIN32) || defined(_WIN64)
	Sleep((DWORD)time * (DWORD)1000UL);

#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	if(sleep(time) > 0)
	{
		fputs("Sleep failed...\n", stderr);
		perror("Error");

		return C_UTILS_STANDARD_FAILURE;
	}

#else
	return C_UTILS_STANDARD_FAILURE;
#endif
	return C_UTILS_SUCCESS;
}

int c_utils_mssleep(const unsigned int time)
{
	if(time == 0U)
	{
		return C_UTILS_INPUT_FAILURE;
	}

#if defined(_WIN32) || defined(_WIN64)
	Sleep((DWORD)time);

#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	if(time > UINT_MAX / 1000)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	if(usleep(time * 1000) == -1)
	{
		fputs("Sleep failed...\n", stderr);
		perror("Error");

		return C_UTILS_STANDARD_FAILURE;
	}

#else
	return C_UTILS_STANDARD_FAILURE;
#endif
	return C_UTILS_SUCCESS;
}

int c_utils_validate_date(const int year, const int month, const int day)
{
	if(year < 1)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	if(month < 1 || month > 12)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	else
	{
		int days_in_month[12] = {
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
		struct tm current_date = c_utils_get_current_time();

		if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		{
			*(days_in_month + 1) = 29;
		}

		if(day < 1 || day > *(days_in_month + month - 1))
		{
			return C_UTILS_INPUT_FAILURE;
		}

		if(year > current_date.tm_year + 1900 || (year == current_date.tm_year + 1900 && month > current_date.tm_mon + 1) || (year == current_date.tm_year + 1900 && month == current_date.tm_mon + 1 && day > current_date.tm_mday))
		{
			return C_UTILS_INPUT_FAILURE;
		}

		return C_UTILS_SUCCESS;
	}
}

int c_utils_validate_date_future(const int year, const int month, const int day)
{
	if(year < 1)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	if(month < 1 || month > 12)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	else
	{
		int days_in_month[12] = {
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

		if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		{
			*(days_in_month + 1) = 29;
		}

		if(day < 1 || day > *(days_in_month + month - 1))
		{
			return C_UTILS_INPUT_FAILURE;
		}

		return C_UTILS_SUCCESS;
	}
}

int c_utils_make_directory(const char *const path, unsigned int mode)
{
	if(!path)
	{
		return C_UTILS_INPUT_FAILURE;
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

		return C_UTILS_STANDARD_FAILURE;
	}
}

int c_utils_linear_char_search(const char *const array, const size_t count, const char target)
{
	size_t index;

	if(!array)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	for(index = 0U; index < count; index++)
	{
		if(*(array + index) == target)
		{
			return (int)index;
		}
	}

	return C_UTILS_NOT_FOUND;
}

int c_utils_linear_short_int_search(const short int *const array, const size_t count, const short int target)
{
	size_t index;

	if(!array)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	for(index = 0U; index < count; index++)
	{
		if(*(array + index) == target)
		{
			return (int)index;
		}
	}

	return C_UTILS_NOT_FOUND;
}

int c_utils_linear_int_search(const int *const array, const size_t count, const int target)
{
	size_t index;

	if(!array)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	for(index = 0U; index < count; index++)
	{
		if(*(array + index) == target)
		{
			return (int)index;
		}
	}

	return C_UTILS_NOT_FOUND;
}

int c_utils_linear_long_int_search(const long int *const array, const size_t count, const long int target)
{
	size_t index;

	if(!array)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	for(index = 0U; index < count; index++)
	{
		if(*(array + index) == target)
		{
			return (int)index;
		}
	}

	return C_UTILS_NOT_FOUND;
}

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
int c_utils_linear_long_long_int_search(const long long int *const array, const size_t count, const long long int target)
{
	size_t index;

	if(!array)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	for(index = 0U; index < count; index++)
	{
		if(*(array + index) == target)
		{
			return (int)index;
		}
	}

	return C_UTILS_NOT_FOUND;
}
#endif

int c_utils_linear_float_search(const float *const array, const size_t count, const float target)
{
	size_t index;

	if(!array)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	for(index = 0U; index < count; index++)
	{
		const float difference = *(array + index) - target;

		if((difference < 0.0f ? -difference : difference) < 10 * FLT_EPSILON)
		{
			return (int)index;
		}
	}

	return C_UTILS_NOT_FOUND;
}

int c_utils_linear_double_search(const double *const array, const size_t count, const double target)
{
	size_t index;

	if(!array)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	for(index = 0U; index < count; index++)
	{
		const double difference = *(array + index) - target;

		if((difference < 0.0 ? -difference : difference) < 10 * DBL_EPSILON)
		{
			return (int)index;
		}
	}

	return C_UTILS_NOT_FOUND;
}

int c_utils_linear_long_double_search(const long double *const array, const size_t count, const long double target)
{
	size_t index;

	if(!array)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	for(index = 0U; index < count; index++)
	{
		const long double difference = *(array + index) - target;

		if((difference < 0.0L ? -difference : difference) < 10 * LDBL_EPSILON)
		{
			return (int)index;
		}
	}

	return C_UTILS_NOT_FOUND;
}

int c_utils_linear_array_search(const char *const *const array, const size_t count, const char *const target)
{
	size_t index;

	if(!array || !target)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	for(index = 0U; index < count; index++)
	{
		if(!strcmp(*(array + index), target))
		{
			return (int)index;
		}
	}

	return C_UTILS_NOT_FOUND;
}

const char *c_utils_verify_os(void)
{
#if defined(_WIN32) || defined(_WIN64)
	return "Windows";
#elif defined(__linux__)
	return "Linux";
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

/* End importation: */
#ifdef __cplusplus
}
#endif
