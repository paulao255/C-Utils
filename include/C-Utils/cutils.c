/* Importations: */
#include "cutils.h"
#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#include <float.h>

#if defined(_WIN32) || defined(_WIN64)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <direct.h>
#include <conio.h>
#elif defined(__linux__) || defined(__ANDROID__)
#include <termios.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#elif defined(__APPLE__)
#include <TargetConditionals.h>
#include <termios.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#endif

/* Import C to C++: */
#ifdef __cplusplus
extern "C"
{
#endif

struct tm get_current_time(void)
{
	struct tm result;
	time_t now = time(NULL);

#if defined(_WIN32) || defined(_WIN64)
	localtime_s(&result, &now);
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	localtime_r(&now, &result);
#endif

	return result;
}

struct tm *current_time(void)
{
	static struct tm result;
	time_t now = time(NULL);

#if defined(_WIN32) || defined(_WIN64)
	localtime_s(&result, &now);
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	localtime_r(&now, &result);
#endif

	return &result;
}

int clear_stdout(void)
{
	fputs("\033[2J\033[3J\033[H", stdout);

	return C_UTILS_SUCCESS;
}

int clear_stdin(void)
{
	short int characters = (short int)getchar();

	while(characters != 10 && characters != EOF)
	{
		characters = (short int)getchar();
	}

	return C_UTILS_SUCCESS;
}

int scan_enter(void)
{
	if(clear_stdin() < 0)
	{
		return C_UTILS_INTERNAL_FAILURE;
	}

	if(getchar() == EOF)
	{
		return C_UTILS_STANDARD_FAILURE;
	}

	return C_UTILS_SUCCESS;
}

int easter_egg_function(void)
{
	fputs("Congratulations!!! You just discovered a new easter egg! (please don't say it to anyone ok!)\n", stdout);
	fputs("This is the link to our github account! If you want to see our projects, codes, etc...\n", stdout);
	fputs("Link: https://github.com/paulao255/\n", stdout);
	fputs("Press any key to continue...", stdout);

	if(url_opener("https://github.com/paulao255/") == C_UTILS_STANDARD_FAILURE)
	{
		return C_UTILS_INTERNAL_FAILURE;
	}

	if(scan_char() < 0)
	{
		return C_UTILS_INTERNAL_FAILURE;
	}

	return C_UTILS_SUCCESS;
}

int enable_virtual_terminal_and_utf8(void)
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

int scan_char(void)
{
#if defined(_WIN32) || defined(_WIN64)
	short int character;

	if(fflush(stdout) == EOF)
	{
		fputs("Error while flushing standard output...\n", stderr);

		return C_UTILS_STANDARD_FAILURE;
	}

	character = (short int)_getch();
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	struct termios old_terminal;
	struct termios new_terminal;
	short int character;

	if(fflush(stdout) == EOF)
	{
		fputs("Error while flushing standard output...", stderr);

		return C_UTILS_STANDARD_FAILURE;
	}
		
	if(tcgetattr(STDIN_FILENO, &old_terminal) == EOF)
	{
		return C_UTILS_STANDARD_FAILURE;
	}

	new_terminal = old_terminal;
	new_terminal.c_lflag &= (tcflag_t) ~(ICANON | ECHO);
	*(new_terminal.c_cc + VMIN) = 1;
	*(new_terminal.c_cc + VTIME) = 0;

	if(tcsetattr(STDIN_FILENO, TCSANOW, &new_terminal) == EOF)
	{
		return C_UTILS_STANDARD_FAILURE;
	}

	character = (short int)getchar();

	if(character == EOF)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal);

		return C_UTILS_STANDARD_FAILURE;
	}

	if(tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal))
	{
		return C_UTILS_STANDARD_FAILURE;
	}
#else
	return C_UTILS_INTERNAL_FAILURE;
#endif

	return character;
}

int rrmf(void)
{
#if defined(_WIN32) || defined(_WIN64)
	system("more /C /P .\\README.md");

	if(scan_char() < 0)
	{
		return C_UTILS_INTERNAL_FAILURE;
	}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	system("more -cp ./README.md");

	if(scan_char() < 0)
	{
		return C_UTILS_INTERNAL_FAILURE;
	}
#else
	return C_UTILS_STANDARD_FAILURE;
#endif

	return C_UTILS_SUCCESS;
}

int rlf(void)
{
#if defined(_WIN32) || defined(_WIN64)
	system("more /C /P .\\LICENSE");

	if(scan_char() < 0)
	{
		return C_UTILS_INTERNAL_FAILURE;
	}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	system("more -cp ./LICENSE");

	if(scan_char() < 0)
	{
		return C_UTILS_INTERNAL_FAILURE;
	}
#else
	return C_UTILS_STANDARD_FAILURE;
#endif

	return C_UTILS_SUCCESS;
}

int url_opener(const char *const url)
{
	char command[16384];

	if(!url)
	{
		return C_UTILS_INPUT_FAILURE;
	}

#if defined(_WIN32) || defined(_WIN64)
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L)
	snprintf(command, sizeof(command), "start \"%s\"", url);
#else
	sprintf(command, "start \"%s\"", url);
#endif
#elif defined(__linux__) || defined(__ANDROID__)
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L)
	snprintf(command, sizeof(command), "xdg-open \"%s\"", url);
#else
	sprintf(command, "xdg-open \"%s\"", url);
#endif
#elif defined(__APPLE__)
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L)
	snprintf(command, sizeof(command), "open \"%s\"", url);
#else
	sprintf(command, "open \"%s\"", url);
#endif
#else
	return C_UTILS_STANDARD_FAILURE;
#endif

	system(command);

	return C_UTILS_SUCCESS;
}

int ssleep(const unsigned int time)
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

int mssleep(const unsigned int time)
{
	if(time == 0U)
	{
		return C_UTILS_INPUT_FAILURE;
	}

#if defined(_WIN32) || defined(_WIN64)
	Sleep((DWORD)time);

#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
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

int validate_date(const int year, const int month, const int day)
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
		struct tm current_date = get_current_time();

		if(year == current_date.tm_year + 1900 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
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

int validate_date_future(const int year, const int month, const int day)
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

int make_directory(const char *const path, unsigned int mode)
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

int linear_char_search(const char *const array, const size_t bytes, const char target)
{
	size_t index;

	if(!array)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	for(index = 0U; index < bytes; index++)
	{
		if(*(array + index) == target)
		{
			return (int)index;
		}
	}

	return C_UTILS_NOT_FOUND;
}

int linear_short_int_search(const short int *const array, size_t bytes, const short int target)
{
	size_t index;

	if(!array)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	bytes = bytes / sizeof(short int);

	for(index = 0U; index < bytes; index++)
	{
		if(*(array + index) == target)
		{
			return (int)index;
		}
	}

	return C_UTILS_NOT_FOUND;
}

int linear_int_search(const int *const array, size_t bytes, const int target)
{
	size_t index;

	if(!array)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	bytes = bytes / sizeof(int);

	for(index = 0U; index < bytes; index++)
	{
		if(*(array + index) == target)
		{
			return (int)index;
		}
	}

	return C_UTILS_NOT_FOUND;
}

int linear_long_int_search(const long int *const array, size_t bytes, const long int target)
{
	size_t index;

	if(!array)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	bytes = bytes / sizeof(long int);

	for(index = 0U; index < bytes; index++)
	{
		if(*(array + index) == target)
		{
			return (int)index;
		}
	}

	return C_UTILS_NOT_FOUND;
}

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
int linear_long_long_int_search(const long long int *const array, size_t bytes, const long long int target)
{
	size_t index;

	if(!array)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	bytes = bytes / sizeof(long long int);

	for(index = 0U; index < bytes; index++)
	{
		if(*(array + index) == target)
		{
			return (int)index;
		}
	}

	return C_UTILS_NOT_FOUND;
}
#endif

int linear_float_search(const float *const array, size_t bytes, const float target)
{
	size_t index;

	if(!array)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	bytes = bytes / sizeof(float);

	for(index = 0U; index < bytes; index++)
	{
		const float difference = *(array + index) - target;

		if((difference < 0.0f ? -difference : difference) < 10 * FLT_EPSILON)
		{
			return (int)index;
		}
	}

	return C_UTILS_NOT_FOUND;
}

int linear_double_search(const double *const array, size_t bytes, const double target)
{
	size_t index;

	if(!array)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	bytes = bytes / sizeof(double);

	for(index = 0U; index < bytes; index++)
	{
		const double difference = *(array + index) - target;

		if((difference < 0.0 ? -difference : difference) < 10 * DBL_EPSILON)
		{
			return (int)index;
		}
	}

	return C_UTILS_NOT_FOUND;
}

int linear_long_double_search(const long double *const array, size_t bytes, const long double target)
{
	size_t index;

	if(!array)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	bytes = bytes / sizeof(long double);

	for(index = 0U; index < bytes; index++)
	{
		const long double difference = *(array + index) - target;

		if((difference < 0.0L ? -difference : difference) < 10 * LDBL_EPSILON)
		{
			return (int)index;
		}
	}

	return C_UTILS_NOT_FOUND;
}

int linear_array_search(const char *const *const array, size_t bytes, const char *const target)
{
	size_t index;

	if(!array || !target)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	bytes = bytes / sizeof(char *);

	for(index = 0U; index < bytes; index++)
	{
		if(!strcmp(*(array + index), target))
		{
			return (int)index;
		}
	}

	return C_UTILS_NOT_FOUND;
}

const char *verify_os(void)
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
