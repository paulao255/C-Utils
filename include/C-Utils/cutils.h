/* Include guard: */
#ifndef _C_UTILS_H_
#define _C_UTILS_H_

/* Defines: */
#if defined(_MSVC_LANG) && _MSVC_LANG < 201103L || defined(__cplusplus) && __cplusplus < 201103L
	#define __USE_MINGW_ANSI_STDIO 1
#endif

#if (!defined(_WIN32) || !defined(_WIN64)) && !defined(_POSIX_C_SOURCE)
	#define _POSIX_C_SOURCE 199309L
#endif

/* Importations: */
#include <stdio.h>
#include <stdlib.h>

#if defined(_WIN32) || defined(_WIN64)
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include <direct.h>
	#define MKDIR(dir) _mkdir(dir)
#elif defined(__linux__) || defined(__ANDROID__)
	#include <unistd.h>
	#include <time.h>
	#include <errno.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#define MKDIR(dir) mkdir(dir, 0755)
#elif defined(__APPLE__)
	#include <TargetConditionals.h>
	#include <unistd.h>
	#include <time.h>
	#include <errno.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#define MKDIR(dir) mkdir(dir, 0755)
#elif defined(__DJGPP__)
	#include <unistd.h>
	#include <time.h>
	#include <errno.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#define MKDIR(dir) mkdir(dir)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

/* C Utils version variables: */
#define C_UTILS_FULL_VERSION  20260116      /* C Utils full version variable (2026/01/16).      */
#define C_UTILS_MAJOR_VERSION 2026          /* C Utils major version variable (2026).           */
#define C_UTILS_MINOR_VERSION 01            /* C Utils minor version variable (01).             */
#define C_UTILS_PATCH_VERSION 16            /* C Utils patch version variable (16).             */

/* Terminal colors: */
#define BASE_TERMINAL       "\033[m"        /* Reset terminal text.                             */
#define BOLD                "\033[1m"       /* Bold terminal text.                              */
#define BASE_TERMINAL_BOLD  "\033[m\033[1m" /* Reset and bold terminal text.                    */
#define ITALIC              "\033[3m"       /* Italic terminal text.                            */
#define UNDERLINE           "\033[4m"       /* Underline terminal text.                         */
#define BLACK_COLOR         "\033[30m"      /* Black terminal text.                             */
#define RED_COLOR           "\033[31m"      /* Red terminal text.                               */
#define GREEN_COLOR         "\033[32m"      /* Green terminal text.                             */
#define YELLOW_COLOR        "\033[33m"      /* Yellow terminal text.                            */
#define BLUE_COLOR          "\033[34m"      /* Blue terminal text.                              */
#define MAGENTA_COLOR       "\033[35m"      /* Magenta terminal text.                           */
#define CYAN_COLOR          "\033[36m"      /* Cyan terminal text.                              */
#define WHITE_COLOR         "\033[37m"      /* White terminal text.                             */

/* Precision variables: */
#define MIN_RPV              0              /* Minimum recommended precision value variable.    */
#define MAX_RPV             18              /* Maximum recommended precision value variable.    */

/* Temperature limits variables: */
#define MIN_CELSIUS_F     -273.15f          /* Minimum Celsius temperature (in float).          */
#define MIN_CELSIUS_D     -273.15           /* Minimum Celsius temperature (in double).         */
#define MIN_CELSIUS_L     -273.15L          /* Minimum Celsius temperature (in long double).    */
#define MIN_FAHRENHEIT_F  -459.67f          /* Minimum Fahrenheit temperature (in float).       */
#define MIN_FAHRENHEIT_D  -459.67           /* Minimum Fahrenheit temperature (in double).      */
#define MIN_FAHRENHEIT_L  -459.67L          /* Minimum Fahrenheit temperature (in long double). */
#define MIN_KELVIN_F         0.0f           /* Minimum Kelvin temperature (in float).           */
#define MIN_KELVIN_D         0.0            /* Minimum Kelvin temperature (in double).          */
#define MIN_KELVIN_L         0.0L           /* Minimum Kelvin temperature (in long double).     */

/* Math utils: */
#ifdef IMPORT_MATH_UTILS
	/* Importations and defines: */
	#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
		#include <math.h>
		#define PI_F  (acosf(-1.0f))                  /* Pi constant using float value.          */
		#define PI_D  (acos(-1.0))                    /* Pi constant using double value.         */
		#define PI_LD (acosl(-1.0L))                  /* Pi constant using long double value.    */
	#elif (defined(_MSVC_LANG) && _MSVC_LANG >= 201103L) || (defined(__cplusplus) && __cplusplus >= 201103L)
		#include <cmath>
		#define PI_F  (std::acosf(-1.0f))             /* Pi constant using float value.          */
		#define PI_D  (std::acos(-1.0))               /* Pi constant using double value.         */
		#define PI_LD (std::acosl(-1.0L))             /* Pi constant using long double value.    */
	#else
		#define PI_F  3.14159265358979323846f         /* Pi constant using float value.          */
		#define PI_D  3.14159265358979323846          /* Pi constant using double value.         */
		#define PI_LD 3.14159265358979323846L         /* Pi constant using long double value.    */
	#endif

	/* Math utils functions prototypes: */
	float circumfer_f(float radius_val);                  /* Function to calculate a circumference using a float value.              */
	float circle_area_f(float radius_val);                /* Function to calculate the area of a circle using a float value.         */
	float sphere_volume_f(float radius_val);              /* Function to calculate the volume of a sphere using a float value.       */
	double circumfer_d(double radius_val);                /* Function to calculate a circumference using a double value.             */
	double circle_area_d(double radius_val);              /* Function to calculate the area of a circle using a double value.        */
	double sphere_volume_d(double radius_val);            /* Function to calculate the volume of a sphere using a double value.      */
	long double circumfer_ld(long double radius_val);     /* Function to calculate a circumference using a long double value.        */
	long double circle_area_ld(long double radius_val);   /* Function to calculate the area of a circle using a long double value.   */
	long double sphere_volume_ld(long double radius_val); /* Function to calculate the volume of a sphere using a long double value. */

	float circumfer_f(float radius_val)
	{
		return 2.0f * PI_F * radius_val;
	}

	float circle_area_f(float radius_val)
	{
		return PI_F * (radius_val * radius_val);
	}

	float sphere_volume_f(float radius_val)
	{
		return (4.0f / 3.0f) * PI_F * (radius_val * radius_val * radius_val);
	}

	double circumfer_d(double radius_val)
	{
		return 2.0 * PI_D * radius_val;
	}

	double circle_area_d(double radius_val)
	{
		return PI_D * (radius_val * radius_val);
	}

	double sphere_volume_d(double radius_val)
	{
		return (4.0 / 3.0) * PI_D * (radius_val * radius_val * radius_val);
	}

	long double circumfer_ld(long double radius_val)
	{
		return 2.0L * PI_LD * radius_val;
	}

	long double circle_area_ld(long double radius_val)
	{
		return PI_LD * (radius_val * radius_val);
	}

	long double sphere_volume_ld(long double radius_val)
	{
		return (4.0L / 3.0L) * PI_LD * (radius_val * radius_val * radius_val);
	}

	/* Undefine math utils: */
	#undef IMPORT_MATH_UTILS
#endif

/* Temperature conversion utils: */
#ifdef IMPORT_TEMPERATURE_CONVERSION_UTILS
	/* Temperature conversion utils functions prototypes: */
	float kelvin_to_celsius_f(float kelvin_val);                      /* Function to convert Kelvin to Celsius using a float value.           */
	float kelvin_to_fahrenheit_f(float kelvin_val);                   /* Function to convert Kelvin to Fahrenheit using a float value.        */
	float celsius_to_kelvin_f(float celsius_val);                     /* Function to convert Celsius to Kelvin using a float value.           */
	float celsius_to_fahrenheit_f(float celsius_val);                 /* Function to convert Celsius to Fahrenheit using a float value.       */
	float fahrenheit_to_kelvin_f(float fahrenheit_val);               /* Function to convert Fahrenheit to Kelvin using a float value.        */
	float fahrenheit_to_celsius_f(float fahrenheit_val);              /* Function to convert Fahrenheit to Celsius using a float value.       */
	double kelvin_to_celsius_d(double kelvin_val);                    /* Function to convert Kelvin to Celsius using a double value.          */
	double kelvin_to_fahrenheit_d(double kelvin_val);                 /* Function to convert Kelvin to Fahrenheit using a double value.       */
	double celsius_to_kelvin_d(double celsius_val);                   /* Function to convert Celsius to Kelvin using a double value.          */
	double celsius_to_fahrenheit_d(double celsius_val);               /* Function to convert Celsius to Fahrenheit using a double value.      */
	double fahrenheit_to_kelvin_d(double fahrenheit_val);             /* Function to convert Fahrenheit to Kelvin using a double value.       */
	double fahrenheit_to_celsius_d(double fahrenheit_val);            /* Function to convert Fahrenheit to Celsius using a double value.      */
	long double kelvin_to_celsius_ld(long double kelvin_val);         /* Function to convert Kelvin to Celsius using a long double value.     */
	long double kelvin_to_fahrenheit_ld(long double kelvin_val);      /* Function to convert Kelvin to Fahrenheit using a long double value.  */
	long double celsius_to_kelvin_ld(long double celsius_val);        /* Function to convert Celsius to Kelvin using a long double value.     */
	long double celsius_to_fahrenheit_ld(long double celsius_val);    /* Function to convert Celsius to Fahrenheit using a long double value. */
	long double fahrenheit_to_kelvin_ld(long double fahrenheit_val);  /* Function to convert Fahrenheit to Kelvin using a long double value.  */
	long double fahrenheit_to_celsius_ld(long double fahrenheit_val); /* Function to convert Fahrenheit to Celsius using a long double value. */

	float kelvin_to_celsius_f(float kelvin_val)
	{
		return kelvin_val - 273.15f;
	}

	float kelvin_to_fahrenheit_f(float kelvin_val)
	{
		return kelvin_val * (9.0f / 5.0f) - 459.67f;
	}

	float celsius_to_kelvin_f(float celsius_val)
	{
		return celsius_val + 273.15f;
	}

	float celsius_to_fahrenheit_f(float celsius_val)
	{
		return celsius_val * (9.0f / 5.0f) + 32.0f;
	}

	float fahrenheit_to_kelvin_f(float fahrenheit_val)
	{
		return (fahrenheit_val + 459.67f) * (5.0f / 9.0f);
	}

	float fahrenheit_to_celsius_f(float fahrenheit_val)
	{
		return (fahrenheit_val - 32.0f) * (5.0f / 9.0f);
	}

	double kelvin_to_celsius_d(double kelvin_val)
	{
		return kelvin_val - 273.15;
	}

	double kelvin_to_fahrenheit_d(double kelvin_val)
	{
		return kelvin_val * (9.0 / 5.0) - 459.67;
	}

	double celsius_to_kelvin_d(double celsius_val)
	{
		return celsius_val + 273.15;
	}

	double celsius_to_fahrenheit_d(double celsius_val)
	{
		return celsius_val * (9.0 / 5.0) + 32.0;
	}

	double fahrenheit_to_kelvin_d(double fahrenheit_val)
	{
		return (fahrenheit_val + 459.67) * (5.0 / 9.0);
	}

	double fahrenheit_to_celsius_d(double fahrenheit_val)
	{
		return (fahrenheit_val - 32.0) * (5.0 / 9.0);
	}

	long double kelvin_to_celsius_ld(long double kelvin_val)
	{
		return kelvin_val - 273.15L;
	}

	long double kelvin_to_fahrenheit_ld(long double kelvin_val)
	{
		return kelvin_val * (9.0L / 5.0L) - 459.67L;
	}

	long double celsius_to_kelvin_ld(long double celsius_val)
	{
		return celsius_val + 273.15L;
	}

	long double celsius_to_fahrenheit_ld(long double celsius_val)
	{
		return celsius_val * (9.0L / 5.0L) + 32.0L;
	}

	long double fahrenheit_to_kelvin_ld(long double fahrenheit_val)
	{
		return (fahrenheit_val + 459.67L) * (5.0L / 9.0L);
	}

	long double fahrenheit_to_celsius_ld(long double fahrenheit_val)
	{
		return (fahrenheit_val - 32.0L) * (5.0L / 9.0L);
	}

	/* Undefine temperature conversion utils: */
	#undef IMPORT_TEMPERATURE_CONVERSION_UTILS
#endif

/* Main functions prototype: */
static void enable_vt_and_utf8(void);    /* Function to solve encoding in the Windows terminal. */
static void clear_terminal(void);        /* Function to clear the terminal.                     */
static void petc(void);                  /* Press enter to continue function.                   */
static void apetc(void);                 /* Alternative press enter to continue function.       */
static void rrmf(void);                  /* Read "READ-ME" function.                            */
static void easter_egg_function(void);   /* Easter egg function.                                */
static void ssleep(unsigned int time);   /* Seconds sleep function.                             */
static void mssleep(unsigned int time);  /* Milliseconds sleep function.                        */
static void url_opener(const char *url); /* URL opener function.                                */
static const char *verify_os(void);      /* Function to verify the operating system.            */

static void enable_vt_and_utf8(void)
{
	#if defined(_WIN32) || defined(_WIN64)
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

		if(hOut == INVALID_HANDLE_VALUE)
		{
			return;
		}

		DWORD mode = 0u;

		if(!GetConsoleMode(hOut, &mode))
		{
			return;
		}

		mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

		if(!SetConsoleMode(hOut, mode))
		{
			DWORD err = GetLastError();
			(void)err;
			return;
		}
	
		if(!SetConsoleOutputCP(CP_UTF8))
		{
			DWORD err = GetLastError();
			(void)err;
		}
	#else
		return;
	#endif
}

static void clear_terminal(void)
{
	fputs("\033[2J\033[3J\033[H", stdout);
}

static void petc(void)
{
	int characters = 0;
	while((characters = getchar()) != EOF && characters != '\n');
	fputs("Press \"ENTER\" to continue...", stdout);
	getchar();
}

static void apetc(void)
{
	fputs("Press \"ENTER\" to continue...", stdout);
	getchar();
}

static void rrmf(void)
{
	#if defined(_WIN32) || defined(_WIN64)
		puts("When you enter just press \"space\" to advance 1 page, \"enter\" to go down 1 line and \"Ctrl-C\" to quit \"READ-ME\"!");
		petc();
		system("more /C /P .\\README.md");
		petc();
	#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		puts("When you enter press \"q\" to quit, \"enter\" to go down to the next line, \"space\" to go down next page, and type \"/ + text\" to search for text!");
		petc();
		system("more -cp ./README.md");
		petc();
	#elif defined(__DJGPP__)
		system("TYPE .\\README.MD");
		petc();
	#else
		return;
	#endif
}

static void easter_egg_function(void)
{
	puts("Congratulations!!! You just discovered a new easter egg! (please don't say it to anywhone ok!)");
	puts("This is the link to our github account! If you want to see our projects, codes, etc...");
	puts("Link: https://github.com/paulao255/");

	#if defined(_WIN32) || defined(_WIN64)
	  system("start https://github.com/paulao255/");
	#elif defined(__linux__) || defined(__ANDROID__)
	  system("xdg-open https://github.com/paulao255/");
	#elif defined(__APPLE__)
	  system("open https://github.com/paulao255/");
	#endif

	petc();
}

static void ssleep(unsigned int time)
{
	#ifndef __DJGPP__
		if(time == 0UL)
		{
			return;
		}

		else
		{
			#if defined(_WIN32) || defined(_WIN64)
				Sleep((DWORD)time * (DWORD)1000UL);
			#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
				struct timespec req;
				struct timespec rem;
				int res;

				req.tv_sec = (time_t)time;
				req.tv_nsec = 0L;

				while((res = nanosleep(&req, &rem)) == -1)
				{
					if(errno == EINTR)
					{
						req = rem;
					}

					else
					{
						break;
					}
				}
			#else
				return;
			#endif
		}
	#else
		return;
	#endif
}

static void mssleep(unsigned int time)
{
	#ifndef __DJGPP__
		if(time == 0UL)
		{
			return;
		}

		else
		{
			#if defined(_WIN32) || defined(_WIN64)
				Sleep((DWORD)time);
			#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
				struct timespec req;
				struct timespec rem;
				int res;

				req.tv_sec = (time_t)(time / 1000);
				req.tv_nsec = (long)((time % 1000) * 1000000L);

				while((res = nanosleep(&req, &rem)) == -1)
				{
					if(errno == EINTR)
					{
						req = rem;
					}

					else
					{
						break;
					}
				}
			#else
				return;
			#endif
		}
	#else
		return;
	#endif
}

static void url_opener(const char *url)
{
	#ifndef __DJGPP__
		if(!url)
		{
			return;
		}

		else
		{
			char command[16384] = "";

			#if defined(_WIN32) || defined(_WIN64)
				#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
					snprintf(command, sizeof(command), "start %s", url);
				#elif defined(__cplusplus) && __cplusplus >= 201103L
					snprintf(command, sizeof(command), "start %s", url);
				#else
					sprintf(command, "start %s", url);
				#endif
			#elif defined(__linux__) || defined(__ANDROID__)
				#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
					snprintf(command, sizeof(command), "xdg-open %s", url);
				#elif defined(__cplusplus) && __cplusplus >= 201103L
					snprintf(command, sizeof(command), "xdg-open %s", url);
				#else
					sprintf(command, "xdg-open %s", url);
				#endif
			#elif defined(__APPLE__)
				#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
					snprintf(command, sizeof(command), "open %s", url);
				#elif defined(__cplusplus) && __cplusplus >= 201103L
					snprintf(command, sizeof(command), "open %s", url);
				#else
					sprintf(command, "open %s", url);
				#endif
			#else
				return;
			#endif

			system(command);
		}
	#else
		return;
	#endif
}

static const char *verify_os(void)
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
	#elif defined(__DJGPP__)
		return "MS-DOS";
	#else
		return "Unknown OS";
	#endif
}

#ifdef __cplusplus
}
#endif

/* End code: */
#endif
