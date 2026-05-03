/* Importations: */
#include "cutils.h"
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
#include <pthread.h>
#include <termios.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#elif defined(__APPLE__)
#include <TargetConditionals.h>
#include <pthread.h>
#include <termios.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#endif


/* Import C to C++: */
#if defined(__cplusplus)
extern "C"
{
#endif

signed int c_utils_clear_standard_output(void)
{
	fputs("\033[2J\033[3J\033[H", stdout);

	return C_UTILS_SUCCESS;
}

signed int c_utils_clear_standard_input(void)
{
	signed int characters = getchar();

	while(characters != '\n' && characters != EOF)
	{
		characters = getchar();
	}

	return C_UTILS_SUCCESS;
}

signed int c_utils_enable_virtual_terminal_and_utf8(void)
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

	return C_UTILS_SUCCESS;
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	return C_UTILS_SUCCESS;
#else
	return C_UTILS_STANDARD_FAILURE;
#endif
}

signed int c_utils_initialize(void)
{
	if(c_utils_enable_virtual_terminal_and_utf8() < 0)
	{
		return C_UTILS_STANDARD_FAILURE;
	}

	return C_UTILS_SUCCESS;
}

signed int c_utils_scan_character(void)
{
	signed int character;
#if defined(_WIN32) || defined(_WIN64)

	if(fflush(stdout) == EOF)
	{
		fputs("Error while flushing standard output...\n", stderr);

		return C_UTILS_STANDARD_FAILURE;
	}

	character = _getch();
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	struct termios old_terminal;
	struct termios new_terminal;
	signed int keyword;
	ssize_t result;

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

	result = read(STDIN_FILENO, &keyword, 1U);

	if(result == 0)
	{
		if(tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal) == -1)
		{
			return C_UTILS_STANDARD_FAILURE;
		}

		return C_UTILS_STANDARD_FAILURE;
	}

	else if(result < 0)
	{
		perror("\"read\" error");

		if(tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal) == -1)
		{
			return C_UTILS_STANDARD_FAILURE;
		}

		return C_UTILS_STANDARD_FAILURE;
	}

	character = keyword;

	if(tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal) == -1)
	{
		return C_UTILS_STANDARD_FAILURE;
	}
#else
	return C_UTILS_INTERNAL_FAILURE;
#endif

	return character;
}

signed int c_utils_scan_enter(void)
{
	if(c_utils_clear_standard_input() < 0)
	{
		return C_UTILS_INTERNAL_FAILURE;
	}

	if(getchar() == EOF)
	{
		return C_UTILS_STANDARD_FAILURE;
	}

	return C_UTILS_SUCCESS;
}

signed int c_utils_rlf(void)
{
#if defined(_WIN32) || defined(_WIN64)
	if(system("more /C /P .\\LICENSE") == -1)
	{
		perror("\"system\" error");

		return C_UTILS_STANDARD_FAILURE;
	}

	if(c_utils_scan_character() < 0)
	{
		return C_UTILS_INTERNAL_FAILURE;
	}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	if(system("more -cp ./LICENSE") == -1)
	{
		perror("\"system\" error");

		return C_UTILS_STANDARD_FAILURE;
	}

	if(c_utils_scan_character() < 0)
	{
		return C_UTILS_INTERNAL_FAILURE;
	}
#else
	return C_UTILS_STANDARD_FAILURE;
#endif

	return C_UTILS_SUCCESS;
}

signed int c_utils_rrmf(void)
{
#if defined(_WIN32) || defined(_WIN64)
	if(system("more /C /P .\\README.md") == -1)
	{
		perror("\"system\" error");

		return C_UTILS_STANDARD_FAILURE;
	}

	if(c_utils_scan_character() < 0)
	{
		return C_UTILS_INTERNAL_FAILURE;
	}
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	if(system("more -cp ./README.md") == -1)
	{
		perror("\"system\" error");

		return C_UTILS_STANDARD_FAILURE;
	}

	if(c_utils_scan_character() < 0)
	{
		return C_UTILS_INTERNAL_FAILURE;
	}
#else
	return C_UTILS_STANDARD_FAILURE;
#endif

	return C_UTILS_SUCCESS;
}

signed int c_utils_url_opener(const unsigned char *const url)
{
	if(!url)
	{
		return C_UTILS_INPUT_FAILURE;
	}
	
	else
	{
#if defined(_WIN32) || defined(_WIN64)
		ShellExecuteA((void *)0, "open", (LPCSTR)url, (void *)0, (void *)0, SW_SHOWNORMAL);
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		pid_t pid = fork();

		if(pid == -1)
		{
			perror("\"fork\" error");

			return C_UTILS_STANDARD_FAILURE;
		}

		if(pid == 0)
		{
			const char *arguments[3];

#if defined(__linux__) || defined(__ANDROID__)
			*arguments = "xdg-open";
			*(arguments + 1) = (const char *)url;
			*(arguments + 2) = (void *)0;
			execv("/usr/bin/xdg-open", (char *const *)arguments);
#elif defined(__APPLE__)
			*arguments = "open";
			*(arguments + 1) = (const char *)url;
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

signed int c_utils_ssleep(const unsigned int time)
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

signed int c_utils_mssleep(const unsigned int time)
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

signed int c_utils_validate_date(const signed int year, const signed int month, const signed int day)
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
		signed int days_in_month[12] = {
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

signed int c_utils_validate_date_future(const signed int year, const signed int month, const signed int day)
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
		signed int days_in_month[12] = {
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

signed int c_utils_make_directory(const unsigned char *const path, unsigned int mode)
{
	if(!path)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	else
	{
#if defined(_WIN32) || defined(_WIN64)
		if(!_mkdir((const char *const)path))
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

		if(mkdir((const char *const)path, (mode_t)mode) == 0)
		{
			return C_UTILS_SUCCESS;
		}

		fputs("Error in function mkdir...\n", stderr);
		perror("Error");
#endif

		return C_UTILS_STANDARD_FAILURE;
	}
}

signed int c_utils_linear_unsigned_char_search(const unsigned char *const array, const size_t count, const unsigned char target)
{
	if(!array)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	else
	{
		size_t index;

		for(index = 0U; index < count; index++)
		{
			if(*(array + index) == target)
			{
				return (signed int)index;
			}
		}
	}

	return C_UTILS_NOT_FOUND;
}

signed int c_utils_linear_signed_short_int_search(const signed short int *const array, const size_t count, const signed short int target)
{
	if(!array)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	else
	{
		size_t index;

		for(index = 0U; index < count; index++)
		{
			if(*(array + index) == target)
			{
				return (signed int)index;
			}
		}
	}

	return C_UTILS_NOT_FOUND;
}

signed int c_utils_linear_signed_int_search(const signed int *const array, const size_t count, const signed int target)
{
	if(!array)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	else
	{
		size_t index;

		for(index = 0U; index < count; index++)
		{
			if(*(array + index) == target)
			{
				return (signed int)index;
			}
		}
	}

	return C_UTILS_NOT_FOUND;
}

signed int c_utils_linear_signed_long_int_search(const signed long int *const array, const size_t count, const signed long int target)
{
	if(!array)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	else
	{
		size_t index;

		for(index = 0U; index < count; index++)
		{
			if(*(array + index) == target)
			{
				return (signed int)index;
			}
		}
	}

	return C_UTILS_NOT_FOUND;
}

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
signed int c_utils_linear_signed_long_long_int_search(const signed long long int *const array, const size_t count, const signed long long int target)
{
	if(!array)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	else
	{
		size_t index;

		for(index = 0U; index < count; index++)
		{
			if(*(array + index) == target)
			{
				return (signed int)index;
			}
		}
	}

	return C_UTILS_NOT_FOUND;
}
#endif

signed int c_utils_linear_float_search(const float *const array, const size_t count, const float target)
{
	if(!array)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	else
	{
		size_t index;

		for(index = 0U; index < count; index++)
		{
			const float difference = *(array + index) - target;

			if((difference < 0.0f ? -difference : difference) < 10 * FLT_EPSILON)
			{
				return (signed int)index;
			}
		}
	}

	return C_UTILS_NOT_FOUND;
}

signed int c_utils_linear_double_search(const double *const array, const size_t count, const double target)
{
	if(!array)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	else
	{
		size_t index;

		for(index = 0U; index < count; index++)
		{
			const double difference = *(array + index) - target;

			if((difference < 0.0 ? -difference : difference) < 10 * DBL_EPSILON)
			{
				return (signed int)index;
			}
		}
	}

	return C_UTILS_NOT_FOUND;
}

signed int c_utils_linear_long_double_search(const long double *const array, const size_t count, const long double target)
{
	if(!array)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	else
	{
		size_t index;

		for(index = 0U; index < count; index++)
		{
			const long double difference = *(array + index) - target;

			if((difference < 0.0L ? -difference : difference) < 10 * LDBL_EPSILON)
			{
				return (signed int)index;
			}
		}
	}

	return C_UTILS_NOT_FOUND;
}

signed int c_utils_linear_unsigned_array_search(const unsigned char *const *const array, const size_t count, const unsigned char *const target)
{
	if(!array || !target)
	{
		return C_UTILS_INPUT_FAILURE;
	}

	else
	{
		size_t index;

		for(index = 0U; index < count; index++)
		{
			if(!strcmp((const char *const)*(array + index), (const char *const)target))
			{
				return (signed int)index;
			}
		}
	}

	return C_UTILS_NOT_FOUND;
}

signed int c_utils_thread_create(c_utils_thread_t *thread, C_UTILS_THREAD_FUNCTION (*function)(void *), void *arguments)
{
#if defined(_WIN32) || defined(_WIN64)
	return ((*thread = CreateThread((void *)0, 0, (LPTHREAD_START_ROUTINE)function, arguments, 0, (void *)0)) == (void *)0) ? C_UTILS_STANDARD_FAILURE : C_UTILS_SUCCESS;
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	return (pthread_create(thread, (void *)0, function, arguments) != 0) ? C_UTILS_STANDARD_FAILURE : C_UTILS_SUCCESS;
#endif
}

signed int c_utils_thread_join(c_utils_thread_t thread)
{
#if defined(_WIN32) || defined(_WIN64)
	if(WaitForSingleObject(thread, INFINITE) != WAIT_OBJECT_0)
	{
		if(!CloseHandle(thread))
		{
			return C_UTILS_STANDARD_FAILURE;
		}

		return C_UTILS_STANDARD_FAILURE;
	}

	if(!CloseHandle(thread))
	{
		return C_UTILS_STANDARD_FAILURE;
	}

	return C_UTILS_SUCCESS;
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	return (pthread_join(thread, (void *)0) != 0) ? C_UTILS_STANDARD_FAILURE : C_UTILS_SUCCESS;
#endif
}

signed int c_utils_thread_detach(c_utils_thread_t thread)
{
#if defined(_WIN32) || defined(_WIN64)
	return (CloseHandle(thread) == 0) ? C_UTILS_STANDARD_FAILURE : C_UTILS_SUCCESS;
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	return (pthread_detach(thread) != 0) ? C_UTILS_STANDARD_FAILURE : C_UTILS_SUCCESS;
#endif
}

signed long int c_utils_get_maximum_threads(void)
{
#if defined(_WIN32) || defined(_WIN64)
	return (signed long int)GetActiveProcessorCount(ALL_PROCESSOR_GROUPS);
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
	return sysconf(_SC_NPROCESSORS_ONLN);
#endif
}

const unsigned char *c_utils_verify_os(void)
{
#if defined(_WIN32) || defined(_WIN64)
	return (const unsigned char *)"Windows";
#elif defined(__linux__)
	return (const unsigned char *)"Linux";
#elif defined(__ANDROID__)
	return (const unsigned char *)"Android";
#elif defined(__APPLE__)
#if TARGET_OS_OSX
	return (const unsigned char *)"macOS";
#elif TARGET_OS_IOS
	return (const unsigned char *)"iOS";
#elif TARGET_OS_TV
	return (const unsigned char *)"tvOS";
#elif TARGET_OS_WATCH
	return (const unsigned char *)"watchOS";
#else
	return (const unsigned char *)"Apple (unknown OS)";
#endif
#else
	return (const unsigned char *)"Unknown OS";
#endif
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

/* End importation: */
#if defined(__cplusplus)
}
#endif
