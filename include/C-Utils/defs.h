/* Include guard: */
#ifndef C_UTILS_DEFS_H
#define C_UTILS_DEFS_H

/* Solve some systems issues: */
#if (!defined(__USE_MINGW_ANSI_STDIO)) && ((defined(_MSVC_LANG) && _MSVC_LANG < 201103L) || (defined(__cplusplus) && __cplusplus < 201103L))
#define __USE_MINGW_ANSI_STDIO 1
#endif

#if (!defined(_WIN32) && !defined(_WIN64)) && !defined(__cplusplus) && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L && !defined(_POSIX_C_SOURCE)
#define _POSIX_C_SOURCE 199309L
#define _DEFAULT_SOURCE
#endif

#if defined(_WIN32) || defined(_WIN64)
#undef strdup
#define strdup _strdup
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/* Definitions version variables: */
#define C_UTILS_FULL_VERSION         20260227L                 /* C Utils/defs.h full version macro.                                      */
#define C_UTILS_MAJOR_VERSION        2026L                     /* C Utils/defs.h major version macro.                                     */
#define C_UTILS_MINOR_VERSION        2L	                       /* C Utils/defs.h minor version macro.                                     */
#define C_UTILS_PATCH_VERSION        27L                       /* C Utils/defs.h patch version macro.                                     */

/* Terminal colors: */
#define BASE_TERMINAL               "\e[0m"                    /* Reset terminal text macro.                                              */
#define BOLD                        "\e[1m"                    /* Bold terminal text macro.                                               */
#define BASE_TERMINAL_BOLD          "\e[0m\e[1m"               /* Reset and bold terminal text macro.                                     */
#define ITALIC                      "\e[3m"                    /* Italic terminal text macro.                                             */
#define UNDERLINE                   "\e[4m"                    /* Underline terminal text macro.                                          */
#define BLACK_COLOR                 "\e[30m"                   /* Black terminal text macro.                                              */
#define RED_COLOR                   "\e[31m"                   /* Red terminal text macro.                                                */
#define GREEN_COLOR                 "\e[32m"                   /* Green terminal text macro.                                              */
#define YELLOW_COLOR                "\e[33m"                   /* Yellow terminal text macro.                                             */
#define BLUE_COLOR                  "\e[34m"                   /* Blue terminal text macro.                                               */
#define MAGENTA_COLOR               "\e[35m"                   /* Magenta terminal text macro.                                            */
#define CYAN_COLOR                  "\e[36m"                   /* Cyan terminal text macro.                                               */
#define WHITE_COLOR                 "\e[37m"                   /* White terminal text macro.                                              */

/* Recommended precision value: */
#define MIN_RPV                       0                        /* Minimum recommended precision value macro.                              */
#define MAX_RPV                      18                        /* Maximum recommended precision value macro.                              */

/* Temperature limits: */
#define MIN_CELSIUS_F               -273.15f                   /* Minimum Celsius temperature (in float).                                 */
#define MIN_CELSIUS_D               -273.15                    /* Minimum Celsius temperature (in double).                                */
#define MIN_CELSIUS_L               -273.15L                   /* Minimum Celsius temperature (in long double).                           */
#define MIN_FAHRENHEIT_F            -459.67f                   /* Minimum Fahrenheit temperature (in float).                              */
#define MIN_FAHRENHEIT_D            -459.67                    /* Minimum Fahrenheit temperature (in double).                             */
#define MIN_FAHRENHEIT_L            -459.67L                   /* Minimum Fahrenheit temperature (in long double).                        */
#define MIN_KELVIN_F                   0.0f                    /* Minimum Kelvin temperature (in float).                                  */
#define MIN_KELVIN_D                   0.0                     /* Minimum Kelvin temperature (in double).                                 */
#define MIN_KELVIN_L                   0.0L                    /* Minimum Kelvin temperature (in long double).                            */

/* Pi value: */
#define PI_F                           3.14159265358979323846f /* Pi macro using float value.                                             */
#define PI_D                           3.14159265358979323846  /* Pi macro using double value.                                            */
#define PI_LD                          3.14159265358979323846L /* Pi macro using long double value.                                       */

#ifdef __cplusplus
}
#endif

#endif
