/* Include guard: */
#ifndef C_UTILS_C_UTILS_H
#define C_UTILS_C_UTILS_H

/* Importations: */
#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#include <errno.h>

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


#ifdef __cplusplus
extern "C"
{
#endif

/* Main struct prototypes: */
static struct tm get_current_time(void);                                                                 /* Get current time struct.                            */
static struct tm *current_time(void);                                                                    /* Current time struct.                                */

static struct tm get_current_time(void)
{
	int ok;
	time_t now = time(NULL);
	static struct tm result;

#if defined(_WIN32) || defined(_WIN64)
	localtime_s(&result, &now);

	ok = 0;
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	localtime_r(&now, &result);

	ok = 0;
#else
	ok = 1;
#endif

	return result;
}

static struct tm *current_time(void)
{
	int ok;
	time_t now = time(NULL);
	static struct tm result;

#if defined(_WIN32) || defined(_WIN64)
	localtime_s(&result, &now);

	ok = 0;
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	localtime_r(&now, &result);

	ok = 0;
#else
	ok = 1;
#endif

	return &result;
}

/* Main functions prototypes: */
static int clear_stdout(void);                                                                                      /* Function to clear the terminal.                     */
static int clear_stdin(void);                                                                                       /* Function to clear the standard input.               */
static int scan_enter(void);                                                                                        /* Press enter to continue function.                   */
static int easter_egg_function(void);                                                                               /* Easter egg function.                                */
static int enable_virtual_terminal_and_utf8(void);                                                                  /* Function to solve encoding in the Windows terminal. */
static int scan_char(void);                                                                                         /* Press any key to continue function.                 */
static int rlf(void);                                                                                               /* Read "LICENSE" function.                            */
static int rrmf(void);                                                                                              /* Read "READ-ME" function.                            */
static int url_opener(const char *url);                                                                             /* URL opener function.                                */
static int ssleep(const unsigned int time);                                                                         /* Seconds sleep function.                             */
static int mssleep(const unsigned int time);                                                                        /* Milliseconds sleep function.                        */
static int validate_date(const int year, const int month, const int day);                                           /* Validate date function.                             */
static int validate_date_future(const int year, const int month, const int day);                                    /* Validate all time date function.                    */
static int make_directory(const char *const path, unsigned int mode);                                               /* Function to create a directory.                     */
static int linear_char_search(const char *const array, size_t bytes, const char target);                            /* Linear char search function.                        */
static int linear_short_int_search(const short int *const array, size_t bytes, const short int target);             /* Linear short int search function.                   */
static int linear_int_search(const int *const array, size_t bytes, const int target);                               /* Linear int search function.                         */
static int linear_long_int_search(const long int *const array, size_t bytes, const long int target);                /* Linear long int search function.                    */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
static int linear_long_long_int_search(const long long int *const array, size_t bytes, const long long int target); /* Linear long long int search function.               */
#endif
static int linear_float_search(const float *const array, size_t bytes, const float target);                         /* Linear float search function.                       */
static int linear_double_search(const double *const array, size_t bytes, const double target);                      /* Linear double search function.                      */
static int linear_long_double_search(const long double *const array, size_t bytes, const long double target);       /* Linear long double search function.                 */
static int linear_array_search(const char **const array, size_t bytes, const char *const target);                   /* Linear array search function.                       */
static char *verify_os(void);                                                                                       /* Function to verify the operating system.            */

static int clear_stdout(void)
{
	fputs("\e[2J\e[3J\e[H", stdout);

	return 0;
}

static int clear_stdin(void)
{
	int characters = getchar();

	while(characters != 10 && characters != -1)
	{
		characters = getchar();
	}

	return 0;
}

static int scan_enter(void)
{
	if(clear_stdin() != 0)
	{
		return 1;
	}

	if(getchar() == -1)
	{
		return 1;
	}

	return 0;
}

static int easter_egg_function(void)
{
	puts("Congratulations!!! You just discovered a new easter egg! (please don't say it to anyone ok!)");
	puts("This is the link to our github account! If you want to see our projects, codes, etc...");
	puts("Link: https://github.com/paulao255/");

#if defined(_WIN32) || defined(_WIN64)
	system("start https://github.com/paulao255/");
#elif defined(__linux__) || defined(__ANDROID__)
	system("xdg-open https://github.com/paulao255/");
#elif defined(__APPLE__)
	system("open https://github.com/paulao255/");
#endif

	fputs("Press any key to continue...", stdout);

	if(scan_char() != 0)
	{
		return 1;
	}

	return 0;
}

static int enable_virtual_terminal_and_utf8(void)
{
#if defined(_WIN32) || defined(_WIN64)
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if(hOut == INVALID_HANDLE_VALUE)
	{
		return 1;
	}

	DWORD mode = 0u;

	if(!GetConsoleMode(hOut, &mode))
	{
		return 1;
	}

	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	if(!SetConsoleMode(hOut, mode))
	{
		DWORD err = GetLastError();
		(void)err;

		return 1;
	}
	
	if(!SetConsoleOutputCP(CP_UTF8))
	{
		DWORD err = GetLastError();
		(void)err;

		return 1;
	}
#else
	return 1;
#endif
	return 0;
}

static int scan_char(void)
{
#if defined(_WIN32) || defined(_WIN64)
	if(fflush(stdout) == -1)
	{
		fputs("Error while flushing standard output...", stderr);

		return 1;
	}

	if(_getch() == -1)
	{
		fputs("Error on function _getch()...", stderr);

		return 1;
	}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	struct termios old_terminal;
	struct termios new_terminal;

	if(fflush(stdout) == -1)
	{
		fputs("Error while flushing standard output...", stderr);

		return 1;
	}
		
	tcgetattr(STDIN_FILENO, &old_terminal);

	new_terminal = old_terminal;
	new_terminal.c_lflag &= (tcflag_t) ~(ICANON | ECHO);

	tcsetattr(STDIN_FILENO, TCSANOW, &new_terminal);

	if(getchar() == -1)
	{
		return 1;
	}

	tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal);
#else
	return 1;
#endif
	return 0;
}

static int rrmf(void)
{
#if defined(_WIN32) || defined(_WIN64)
	system("more /C /P .\\README.md");

	if(scan_char() != 0)
	{
		return 1;
	}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	system("more -cp ./README.md");

	if(scan_char() != 0)
	{
		return 1;
	}
#else
	return 1;
#endif
	return 0;
}

static int rlf(void)
{
#if defined(_WIN32) || defined(_WIN64)
	system("more /C /P .\\LICENSE");

	if(scan_char() != 0)
	{
		return 1;
	}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	system("more -cp ./LICENSE");

	if(scan_char() != 0)
	{
		return 1;
	}
#else
	return 1;
#endif
	return 0;
}

static int url_opener(const char *url)
{
	if(!url)
	{
		return 1;
	}

	else
	{
		char command[16384];

#if defined(_WIN32) || defined(_WIN64)
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L)
		snprintf(command, sizeof(command), "start %s", url);
#else
		sprintf(command, "start %s", url);
#endif
#elif defined(__linux__) || defined(__ANDROID__)
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L)
		snprintf(command, sizeof(command), "xdg-open %s", url);
#else
		sprintf(command, "xdg-open %s", url);
#endif
#elif defined(__APPLE__)
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L)
		snprintf(command, sizeof(command), "open %s", url);
#else
		sprintf(command, "open %s", url);
#endif
#else
		return 1;
#endif

		system(command);

		return 0;
	}
}

static int ssleep(const unsigned int time)
{
	if(time == 0U)
	{
		return 1;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		Sleep((DWORD)time * (DWORD)1000UL);
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		if(sleep(time) > 0)
		{
			perror("sleep failed");

			return 1;
		}
#else
		return 1;
#endif
		return 0;
	}
}

static int mssleep(const unsigned int time)
{
	if(time == 0U)
	{
		return 1;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		Sleep((DWORD)time);
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		if(usleep(time * 1000) == -1)
		{
			perror("usleep failed");

			return 1;
		}
#else
		return 1;
#endif
		return 0;
	}
}

static int validate_date(const int year, const int month, const int day)
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
	struct tm *current_date = current_time();

	if(year < 1)
	{
		return 1;
	}

	else
	{
		if(month < 1 || month > 12)
		{
			return 1;
		}

		else
		{
			if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
			{
				*(days_in_month + 1) = 29;
			}

			if(day < 1 || day > *(days_in_month + month - 1))
			{
				return 1;
			}

			else
			{
				if(year > current_date->tm_year + 1900 || (year == current_date->tm_year + 1900 && month > current_date->tm_mon + 1) || (year == current_date->tm_year + 1900 && month == current_date->tm_mon + 1 && day > current_date->tm_mday))
				{
					return 1;
				}

				else
				{
					return 0;
				}
			}
		}
	}
}

static int validate_date_future(const int year, const int month, const int day)
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

	if(year < 1)
	{
		return 1;
	}

	else
	{
		if(month < 1 || month > 12)
		{
			return 1;
		}

		else
		{
			if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
			{
				*(days_in_month + 1) = 29;
			}

			if(day < 1 || day > *(days_in_month + month - 1))
			{
				return 1;
			}

			else
			{
				return 0;
			}
		}
	}
}

static int make_directory(const char *const path, unsigned int mode)
{
	if(!path)
	{
		return 1;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		if(_mkdir(path) == 0)
		{
			return 0;
		}

		else
		{
			perror("Error");

			return 1;
		}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		if(!mode)
		{
			mode = 0755;

			if(mkdir(path, (mode_t)mode) == 0)
			{
				return 0;
			}

			else
			{
				perror("Error");

				return 1;
			}
		}

		else
		{
			if(mkdir(path, (mode_t)mode) == 0)
			{
				return 0;
			}

			else
			{
				perror("Error");

				return 1;
			}
		}
#else
		return 1;
#endif
	}
}

static int linear_char_search(const char *const array, const size_t bytes, const char target)
{
	size_t index;

	if(!array)
	{
		return 1;
	}

	for(index = 0U; index < bytes; index++)
	{
		if(*(array + index) == target)
		{
			return (const int)index;
		}
	}

	return -1;
}

static int linear_short_int_search(const short int *const array, size_t bytes, const short int target)
{
	size_t index;
	bytes = bytes / sizeof(short int);

	for(index = 0U; index < bytes; index++)
	{
		if(*(array + index) == target)
		{
			return (const int)index;
		}
	}

	return -1;
}

static int linear_int_search(const int *const array, size_t bytes, const int target)
{
	size_t index;
	bytes = bytes / sizeof(int);

	for(index = 0U; index < bytes; index++)
	{
		if(*(array + index) == target)
		{
			return (const int)index;
		}
	}

	return -1;
}

static int linear_long_int_search(const long int *const array, size_t bytes, const long int target)
{
	size_t index;
	bytes = bytes / sizeof(long int);

	for(index = 0U; index < bytes; index++)
	{
		if(*(array + index) == target)
		{
			return (const int)index;
		}
	}

	return -1;
}

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
static int linear_long_long_int_search(const long long int *const array, size_t bytes, const long long int target)
{
	size_t index;
	bytes = bytes / sizeof(long long int);

	for(index = 0U; index < bytes; index++)
	{
		if(*(array + index) == target)
		{
			return (const int)index;
		}
	}

	return -1;
}
#endif

static int linear_float_search(const float *const array, size_t bytes, const float target)
{
	size_t index;
	bytes = bytes / sizeof(float);

	for(index = 0U; index < bytes; index++)
	{
		if(*(array + index) == target)
		{
			return (const int)index;
		}
	}

	return -1;
}

static int linear_double_search(const double *const array, size_t bytes, const double target)
{
	size_t index;
	bytes = bytes / sizeof(double);

	for(index = 0U; index < bytes; index++)
	{
		if(*(array + index) == target)
		{
			return (const int)index;
		}
	}

	return -1;
}

static int linear_long_double_search(const long double *const array, size_t bytes, const long double target)
{
	size_t index;
	bytes = bytes / sizeof(long double);

	for(index = 0U; index < bytes; index++)
	{
		if(*(array + index) == target)
		{
			return (const int)index;
		}
	}

	return -1;
}

static int linear_array_search(const char **const array, const size_t bytes, const char *const target)
{
	size_t index;

	if(!array || !target)
	{
		return -1;
	}

	for(index = 0U; index < bytes; index++)
	{
		if(!strcmp(*(array + index), target))
		{
			return (const int)index;
		}
	}

	return -1;
}

static char *verify_os(void)
{
#if defined(_WIN32) || defined(_WIN64)
	return "Windows";
#elif defined(__linux__)
	return "Linux";
#elif defined(__ANDROID__)
	return "Android";
#elif defined(__APPLE__)
#if TARGET_OS_MAC
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

#ifdef __cplusplus
}
#endif

/* End code: */
#endif
