/* Include guard: */
#ifndef C_UTILS_DEFINITIONS_H
#define C_UTILS_DEFINITIONS_H

/* If is not in C90^ or C++98^: ERROR */
#ifndef __STDC__
#ifndef __cplusplus
#error "FATAL ERROR: !__STDC__ && !__cplusplus."
#endif
#endif

/* Solve some systems issues: */
#if defined(__MINGW32__) && !defined(__USE_MINGW_ANSI_STDIO)
#define __USE_MINGW_ANSI_STDIO 1
#endif

/* Activate the default source on Linux, Android and AppleOS. */
#if (defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)) && !defined(_DEFAULT_SOURCE)
#define _DEFAULT_SOURCE
#endif

/* Importations: */
#include <limits.h>
#include <float.h>


/* If 1 byte != 8 bits: ERROR */
#if CHAR_BIT != 8
#error "FATAL ERROR: CHAR_BIT != 8."
#endif

/* 1 byte: */
typedef char c_utils_char_t;                     /* C-Utils 1 byte character type.         */
typedef signed char c_utils_int8_t;              /* C-Utils 1 byte signed integer type.    */
typedef unsigned char c_utils_uint8_t;           /* C-Utils 1 byte unsigned integer type.  */

/* 2 Bytes: */
#if USHRT_MAX == 0xFFFFU
typedef signed short int c_utils_int16_t;        /* C-Utils 2 bytes signed integer type.   */
typedef unsigned short int c_utils_uint16_t;     /* C-Utils 2 bytes unsigned integer type. */
#elif UINT_MAX == 0xFFFFU
typedef signed int c_utils_int16_t;              /* C-Utils 2 bytes signed integer type.   */
typedef unsigned int c_utils_uint16_t;           /* C-Utils 2 bytes unsigned integer type. */
#else
#error "FATAL ERROR: USHRT_MAX != 0xFFFFU && UINT_MAX != 0xFFFFU."
#endif

/* 4 bytes: */
#if UINT_MAX == 0xFFFFFFFFUL
typedef signed int c_utils_int32_t;              /* C-Utils 4 bytes signed integer type.   */
typedef unsigned int c_utils_uint32_t;           /* C-Utils 4 bytes unsigned integer type. */
#elif ULONG_MAX == 0xFFFFFFFFUL
typedef signed long int c_utils_int32_t;         /* C-Utils 4 bytes signed integer type.   */
typedef unsigned long int c_utils_uint32_t;      /* C-Utils 4 bytes unsigned integer type. */
#else
#error "FATAL ERROR: UINT_MAX != 0xFFFFFFFFUL && ULONG_MAX != 0xFFFFFFFFUL."
#endif

#if FLT_MANT_DIG == 24 && FLT_MAX_EXP == 128 && FLT_MIN_EXP == -125
typedef float c_utils_float32_t;
#else
#error "FATAL ERROR: IEEE 754 (Single precision float) not detected."
#endif

/* 8 bytes: */
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L) || defined(C_UTILS_ENABLE_LONG_LONG_INT) || defined(C_UTILS_ENABLE_ALL_EXTENSIONS)
typedef signed long long int c_utils_int64_t;    /* C-Utils 8 bytes signed integer type.   */
typedef unsigned long long int c_utils_uint64_t; /* C-Utils 8 bytes unsigned integer type. */
#endif

#if DBL_MANT_DIG == 53 && DBL_MAX_EXP == 1024 && DBL_MIN_EXP == -1021
typedef double c_utils_float64_t;
#else
#error "FATAL ERROR: IEEE 754 (Double precision float) not detected."
#endif

/* Import C to C++: */
#ifdef __cplusplus
extern "C"
{
#endif

/* Terminal colors: */
extern const c_utils_char_t *const C_UTILS_BASE_TERMINAL     ; /* Reset terminal text constant.                   */
extern const c_utils_char_t *const C_UTILS_BOLD              ; /* Bold terminal text constant.                    */
extern const c_utils_char_t *const C_UTILS_BASE_TERMINAL_BOLD; /* Reset and bold terminal text constant.          */
extern const c_utils_char_t *const C_UTILS_ITALIC            ; /* Italic terminal text constant.                  */
extern const c_utils_char_t *const C_UTILS_UNDERLINE         ; /* Underline terminal text constant.               */
extern const c_utils_char_t *const C_UTILS_BLACK_COLOR       ; /* Black terminal text constant.                   */
extern const c_utils_char_t *const C_UTILS_RED_COLOR         ; /* Red terminal text constant.                     */
extern const c_utils_char_t *const C_UTILS_GREEN_COLOR       ; /* Green terminal text constant.                   */
extern const c_utils_char_t *const C_UTILS_YELLOW_COLOR      ; /* Yellow terminal text constant.                  */
extern const c_utils_char_t *const C_UTILS_BLUE_COLOR        ; /* Blue terminal text constant.                    */
extern const c_utils_char_t *const C_UTILS_MAGENTA_COLOR     ; /* Magenta terminal text constant.                 */
extern const c_utils_char_t *const C_UTILS_CYAN_COLOR        ; /* Cyan terminal text constant.                    */
extern const c_utils_char_t *const C_UTILS_WHITE_COLOR       ; /* White terminal text constant.                   */

/* C Utils errors handlers. */
extern const c_utils_int16_t C_UTILS_SUCCESS       ; /* C-Utils success constant.                       */
extern const c_utils_int16_t C_UTILS_FAILURE       ; /* C-Utils failure constant.                       */

/* Recommended precision value: */
extern const signed int C_UTILS_MIN_RPV            ; /* Minimum recommended precision value constant.   */
extern const signed int C_UTILS_MAX_RPV            ; /* Maximum recommended precision value constant.   */

/* Standardization: */
extern const c_utils_int32_t C_UTILS_MACHINE_BITS  ; /* Machine bits constant.                          */

/* C-Utils version variables: */
extern const c_utils_int32_t C_UTILS_FULL_VERSION  ; /* C Utils full version constant.                  */
extern const c_utils_int32_t C_UTILS_MAJOR_VERSION ; /* C Utils major version constant.                 */
extern const c_utils_int32_t C_UTILS_MINOR_VERSION ; /* C Utils minor version constant.                 */
extern const c_utils_int32_t C_UTILS_PATCH_VERSION ; /* C Utils patch version constant.                 */

/* End importation: */
#ifdef __cplusplus
}
#endif

/* End C_UTILS_DEFS_H. */
#endif
