/* Include guard: */
#ifndef _C_UTILS_H_
#define _C_UTILS_H_

/* Defines: */
#if defined(_MSVC_LANG)
	#if _MSVC_LANG < 201103L
		#define __USE_MINGW_ANSI_STDIO 1
	#endif
#elif defined(__cplusplus)
	#if __cplusplus < 201103L
		#define __USE_MINGW_ANSI_STDIO 1
	#endif
#endif

#if !defined(_WIN32) || !defined(_WIN64)
	#ifndef _POSIX_C_SOURCE
		#define _POSIX_C_SOURCE 199309L
	#endif
#endif

/* Importations: */
#include <stdio.h>
#include <stdlib.h>

#if defined(_WIN32) || defined(_WIN64)
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include <direct.h>
	#define MKDIR(dir) _mkdir(dir)
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
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
#define C_UTILS_FULL_VERSION  180.0L           /* C Utils full version variable (1.8.0).           */
#define C_UTILS_MAJOR_VERSION   1.0L           /* C Utils major version variable (1).              */
#define C_UTILS_MINOR_VERSION   8.0L           /* C Utils minor version variable (8).              */
#define C_UTILS_PATCH_VERSION   0.0L           /* C Utils patch version variable (0).              */

/* Terminal colors: */
#define BASE_TERMINAL          "\033[m"        /* Reset terminal text.                             */
#define BOLD                   "\033[1m"       /* Bold terminal text.                              */
#define BASE_TERMINAL_BOLD     "\033[m\033[1m" /* Reset and bold terminal text.                    */
#define ITALIC                 "\033[3m"       /* Italic terminal text.                            */
#define UNDERLINE              "\033[4m"       /* Underline terminal text.                         */
#define BLACK_COLOR            "\033[30m"      /* Black terminal text.                             */
#define RED_COLOR              "\033[31m"      /* Red terminal text.                               */
#define GREEN_COLOR            "\033[32m"      /* Green terminal text.                             */
#define YELLOW_COLOR           "\033[33m"      /* Yellow terminal text.                            */
#define BLUE_COLOR             "\033[34m"      /* Blue terminal text.                              */
#define MAGENTA_COLOR          "\033[35m"      /* Magenta terminal text.                           */
#define CYAN_COLOR             "\033[36m"      /* Cyan terminal text.                              */
#define WHITE_COLOR            "\033[37m"      /* White terminal text.                             */

/* Precision variables: */
#define MIN_RPV                 0              /* Minimum recommended precision value variable.    */
#define MAX_RPV                18              /* Maximum recommended precision value variable.    */

/* Temperature limits variables: */
#define MIN_CELSIUS_F        -273.15f          /* Minimum Celsius temperature (in float).          */
#define MIN_CELSIUS_D        -273.15           /* Minimum Celsius temperature (in double).         */
#define MIN_CELSIUS_L        -273.15L          /* Minimum Celsius temperature (in long double).    */
#define MIN_FAHRENHEIT_F     -459.67f          /* Minimum Fahrenheit temperature (in float).       */
#define MIN_FAHRENHEIT_D     -459.67           /* Minimum Fahrenheit temperature (in double).      */
#define MIN_FAHRENHEIT_L     -459.67L          /* Minimum Fahrenheit temperature (in long double). */
#define MIN_KELVIN_F            0.0f           /* Minimum Kelvin temperature (in float).           */
#define MIN_KELVIN_D            0.0            /* Minimum Kelvin temperature (in double).          */
#define MIN_KELVIN_L            0.0L           /* Minimum Kelvin temperature (in long double).     */

/* Math utils: */
#ifdef IMPORT_MATH_UTILS
	/* Functions to calculate the circumference: */
	#define CIRCUMFER_F(pi_val_float) ((float)(2.0f) * (float)(pi_val_) * (float)(radius_val_))                                                 /* Float version.       */
	#define CIRCUMFER_D(pi_val_double) ((double)(2.0) * (double)(pi_val_) * (double)(radius_val_))                                              /* Double version.      */
	#define CIRCUMFER_L(pi_val_long_double, radius_val_long_double) ((long double)(2.0L) * (long double)(pi_val_) * (long double)(radius_val_)) /* Long double version. */

	/* Functions to calculate the area of a circle: */
	float circle_area_f(float pi_val_float, float radius_val_float)                                 /* Float version.       */
	{
		return pi_val_float * (radius_val_float * radius_val_float);
	}

	double circle_area_d(double pi_val_double, double radius_val_double)                            /* Double version.      */
	{
		return pi_val_double * (radius_val_double * radius_val_double);
	}

	long double circle_area_l(long double pi_val_long_double, long double radius_val_long_double)   /* Long double version. */
	{
		return pi_val_long_double * (radius_val_long_double * radius_val_long_double);
	}

	/* Functions to calculate the volume of a sphere: */
	float sphere_volume_f(float pi_val_float, float radius_val_float)                               /* Float version.       */
	{
		return (4.0f / 3.0f) * pi_val_float * (radius_val_float * radius_val_float * radius_val_float);
	}

	double sphere_volume_d(double pi_val_double, double radius_val_double)                          /* Double version.      */
	{
		return (4.0 / 3.0) * pi_val_double * (radius_val_double * radius_val_double * radius_val_double);
	}

	long double sphere_volume_l(long double pi_val_long_double, long double radius_val_long_double) /* Long double version. */
	{
		return (4.0L / 3.0L) * pi_val_long_double * (radius_val_long_double * radius_val_long_double * radius_val_long_double);
	}

	/* Temperature convertion functions: */
	#define KELVIN_TO_CELSIUS_F(kelvin_val_float)               ((float)(kelvin_val_float) - (float)(273.15f))                                                      /* Kelvin to Celsius (in float).           */
	#define KELVIN_TO_CELSIUS_D(kelvin_val_double)              ((double)(kelvin_val_double) - (double)(273.15))                                                    /* Kelvin to Celsius (in double).          */
	#define KELVIN_TO_CELSIUS_L(kelvin_val_long_double)         ((long double)(kelvin_val_long_double) - (long double)(273.15L))                                    /* Kelvin to Celsius (in long double).     */
	#define KELVIN_TO_FAHRENHEIT_F(kelvin_val_float)            ((float)(kelvin_val_float) * (float)(9.0f / 5.0f) - (float)(459.67f))                               /* Kelvin to Fahrenheit (in float).        */
	#define KELVIN_TO_FAHRENHEIT_D(kelvin_val_double)           ((double)(kelvin_val_double) * (double)(9.0 / 5.0) - (double)(459.67))                              /* Kelvin to Fahrenheit (in double).       */
	#define KELVIN_TO_FAHRENHEIT_L(kelvin_val_long_double)      ((long double)(kelvin_val_long_double) * (long double)(9.0L / 5.0L) - (long double)(459.67L))       /* Kelvin to Fahrenheit (in long double).  */
	#define CELSIUS_TO_KELVIN_F(celsius_val_float)              ((float)(celsius_val_float) + (float)(273.15f))                                                     /* Celsius to Kelvin (in float).           */
	#define CELSIUS_TO_KELVIN_D(celsius_val_double)             ((double)(celsius_val_double) + (double)(273.15))                                                   /* Celsius to Kelvin (in double).          */
	#define CELSIUS_TO_KELVIN_L(celsius_val_long_double)        ((long double)(celsius_val_long_double) + (long double)(273.15L))                                   /* Celsius to Kelvin (in long double).     */
	#define CELSIUS_TO_FAHRENHEIT_F(celsius_val_float)          ((float)(celsius_val_float) * (float)(9.0f / 5.0f) + (float)(32.0f))                                /* Celsius to Fahrenheit (in float).       */
	#define CELSIUS_TO_FAHRENHEIT_D(celsius_val_double)         ((double)(celsius_val_double) * (double)(9.0 / 5.0) + (double)(32.0))                               /* Celsius to Fahrenheit (in double).      */
	#define CELSIUS_TO_FAHRENHEIT_L(celsius_val_long_double)    ((long double)(celsius_val_long_double) * (long double)(9.0L / 5.0L) + (long double)(32.0L))        /* Celsius to Fahrenheit (in long double). */
	#define FAHRENHEIT_TO_KELVIN_F(fahrenheit_val_float)        (((float)(fahrenheit_val_float) + (float)(459.67f)) * (float)(5.0f / 9.0f))                         /* Fahrenheit to Kelvin (in float).        */
	#define FAHRENHEIT_TO_KELVIN_D(fahrenheit_val_double)       (((double)(fahrenheit_val_double) + (double)(459.67)) * (double)(5.0 / 9.0))                        /* Fahrenheit to Kelvin (in double).       */
	#define FAHRENHEIT_TO_KELVIN_L(fahrenheit_val_long_double)  (((long double)(fahrenheit_val_long_double) + (long double)(459.67L)) * (long double)(5.0L / 9.0L)) /* Fahrenheit to Kelvin (in long double).  */
	#define FAHRENHEIT_TO_CELSIUS_F(fahrenheit_val_float)       (((float)(fahrenheit_val_float) - (float)(32.0f)) * (float)(5.0f / 9.0f))                           /* Fahrenheit to Celsius (in float).       */
	#define FAHRENHEIT_TO_CELSIUS_D(fahrenheit_val_double)      (((double)(fahrenheit_val_double) - (double)(32.0)) * (double)(5.0 / 9.0))                          /* Fahrenheit to Celsius (in double).      */
	#define FAHRENHEIT_TO_CELSIUS_L(fahrenheit_val_long_double) (((long double)(fahrenheit_val_long_double) - (long double)(32.0L)) * (long double)(5.0L / 9.0L))   /* Fahrenheit to Celsius (in long double). */

	/* Undefine math utils: */
	#undef IMPORT_MATH_UTILS
#endif

/* Function to solve encoding in the Windows terminal: */
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

/* Clear terminal function: */
#define CLEAR_TERMINAL(void) (fputs("\033[2J\033[3J\033[H", stdout))

/* Press enter to continue function: */
static void petc(void)
{
	int characters = 0; /* Variable to store characters. */
	while((characters = getchar()) != EOF && characters != '\n');
	fputs("Press \"ENTER\" to continue...", stdout);
	getchar();
}

/* Alternative press enter to continue function (without pausing, just saying to press "ENTER"): */
static void apetc(void)
{
	fputs("Press \"ENTER\" to continue...", stdout);
	getchar();
}

/* Char verify OS function: */
static char verify_os(void)
{
	#if defined(_WIN32) || defined(_WIN64) /* For Windows. */
		return 1;
	#elif defined(__linux__)               /* For Linux. */
		return 2;
	#elif defined(__ANDROID__)             /* For Android. */
		return 3
	#elif defined(__APPLE__)               /* For Apple/macOS. */
		return 4;
	#elif defined(__DJGPP__)               /* For MS-DOS. */
		return 5;
	#else                                  /* For another unknown OS. */
		return 0;
	#endif
}

/* Seconds sleep function: */
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

/* Milliseconds sleep function: */
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

/* Read "READ-ME" function: */
static void rrmf(void)
{
	#if defined(_WIN32) || defined(_WIN64)
		puts("When you enter just press \"space\" to advance 1 page, \"enter\" to go down 1 line and \"Ctrl-C\" to quit \"READ-ME\"!");
		petc();
		system("more /C /P README.md");
		petc_a();
	#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
		puts("When you enter press \"q\" to quit, \"enter\" to go down to the next line, \"space\" to go down next page, and type \"/ + text\" to search for text!");
		petc();
		system("more -cp README.md");
	#elif defined(__DJGPP__)
		system("TYPE README.MD");
		petc();
	#else
		return;
	#endif
}

/* Open URL function: */
static void url_openner(const char *url)
{
	#ifndef __DJGPP__
		if(url == NULL)
		{
			return;
		}

		else
		{
			char command[8192] = ""; /* Command variable. */

			#if defined(_WIN32) || defined(_WIN64)
				snprintf(command, sizeof(command), "start %s", url);
			#elif defined(__linux__) || defined(__ANDROID__)
				snprintf(command, sizeof(command), "xdg-open %s", url);
			#elif defined(__APPLE__) /* For Apple. */
				snprintf(command, sizeof(command), "open %s", url);
			#else
				return;
			#endif

			system(command);
		}
	#else
		return;
	#endif
}

/* Easter egg function: */
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

#ifdef __cplusplus
}
#endif

/* End code: */
#endif
