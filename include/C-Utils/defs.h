/******************/
/* Include guard: */
/******************/

#ifndef C_UTILS_DEFS_H
#define C_UTILS_DEFS_H

/*************************************************/
/* If is not in C90^ or C++98^ make fatal error: */
/*************************************************/

#ifndef __STDC__
#ifndef __cplusplus
#error "FATAL ERROR: !__STDC__ && !__cplusplus (Not C90 or C++98)."
#endif
#endif

/******************************/
/* Solve some systems issues: */
/******************************/

#if defined(__MINGW32__) && !defined(__USE_MINGW_ANSI_STDIO)
#define __USE_MINGW_ANSI_STDIO 1
#endif

/**********************************************************/
/* Activate _DEFAULT_SOURCE for Linux, Android and Apple: */
/**********************************************************/

#if (defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)) && !defined(_DEFAULT_SOURCE)
#define _DEFAULT_SOURCE
#endif

/*************************/
/* Library importations: */
/*************************/

#include <limits.h>
#include <float.h>

/**********************************/
/* Machine types standardization: */
/**********************************/

/***************************************/
/* Verify minimum bits of 1 byte type: */
/***************************************/

#if CHAR_BIT != 8
#error "FATAL ERROR: CHAR_BIT != 8."
#endif

/*****************/
/* 1 Byte types: */
/*****************/

/* C-Utils 1 byte character type (8 bits). */
typedef char c_utils_char_t;

/* C-Utils character minimum value. */
#define C_UTILS_CHAR_MIN CHAR_MIN

/* C-Utils character maximum value. */
#define C_UTILS_CHAR_MAX CHAR_MAX

/* C-Utils 1 byte signed integer type (7 bits for numbers and 1 bit for signal). */
typedef signed char c_utils_int8_t;

/* C-Utils 8 bit signed integer minimum value. */
#define C_UTILS_INT8_MIN SCHAR_MIN

/* C-Utils 8 bit signed integer maximum value. */
#define C_UTILS_INT8_MAX SCHAR_MAX

/* C-Utils 1 byte unsigned integer type (8 bits for numbers). */
typedef unsigned char c_utils_uint8_t;

/* C-Utils 8 bit unsigned integer minimum value. */
#define C_UTILS_UINT8_MIN UCHAR_MIN

/* C-Utils 8 bit unsigned integer maximum value. */
#define C_UTILS_UINT8_MAX UCHAR_MAX

/******************/
/* 2 bytes types: */
/******************/

#if USHRT_MAX == 0xFFFFU
/* C-Utils 2 bytes signed integer type (15 bits for numbers and 1 bit for signal). */
typedef signed short int c_utils_int16_t;

/* C-Utils 16 bits signed integer minimum value. */
#define C_UTILS_INT16_MIN SHRT_MIN

/* C-Utils 16 bits signed integer maximum value. */
#define C_UTILS_INT16_MAX SHRT_MAX

/* C-Utils 2 bytes unsigned integer type (16 bits for numbers). */
typedef unsigned short int c_utils_uint16_t;

/* C-Utils 16 bits unsigned integer minimum value. */
#define C_UTILS_UINT16_MIN USHRT_MIN

/* C-Utils 16 bits unsigned integer maximum value. */
#define C_UTILS_UINT16_MAX USHRT_MAX
#elif UINT_MAX == 0xFFFFU
/* C-Utils 2 bytes signed integer type (15 bits for numbers and 1 bit for signal). */
typedef signed int c_utils_int16_t;

/* C-Utils 16 bits signed integer minimum value. */
#define C_UTILS_INT16_MIN INT_MIN

/* C-Utils 16 bits signed integer maximum value. */
#define C_UTILS_INT16_MAX INT_MAX

/* C-Utils 2 bytes unsigned integer type (16 bits for numbers). */
typedef unsigned int c_utils_uint16_t;

/* C-Utils 16 bits unsigned integer minimum value. */
#define C_UTILS_UINT16_MIN UINT_MIN

/* C-Utils 16 bits unsigned integer maximum value. */
#define C_UTILS_UINT16_MAX UINT_MAX
#else
#error "FATAL ERROR: USHRT_MAX != 0xFFFFU && UINT_MAX != 0xFFFFU."
#endif

/******************/
/* 4 bytes types: */
/******************/

#if UINT_MAX == 0xFFFFFFFFUL
/* C-Utils 4 bytes signed integer type (31 bits for numbers and 1 bit for signal). */
typedef signed int c_utils_int32_t;

/* C-Utils 32 bits signed integer minimum value. */
#define C_UTILS_INT32_MIN INT_MIN

/* C-Utils 32 bits signed integer maximum value. */
#define C_UTILS_INT32_MAX INT_MAX
/* C-Utils 4 bytes unsigned integer type (32 bits for numbers). */
typedef unsigned int c_utils_uint32_t;

/* C-Utils 32 bits unsigned integer minimum value. */
#define C_UTILS_UINT32_MIN UINT_MIN

/* C-Utils 32 bits unsigned integer maximum value. */
#define C_UTILS_UINT32_MAX UINT_MAX
#elif ULONG_MAX == 0xFFFFFFFFUL
/* C-Utils 4 bytes signed integer type (31 bits for numbers and 1 bit for signal). */
typedef signed long int c_utils_int32_t;

/* C-Utils 32 bits signed integer minimum value. */
#define C_UTILS_INT32_MIN LONG_MIN

/* C-Utils 32 bits signed integer maximum value. */
#define C_UTILS_INT32_MAX LONG_MAX

/* C-Utils 4 bytes unsigned integer type (32 bits for numbers). */
typedef unsigned long int c_utils_uint32_t;

/* C-Utils 32 bits unsigned integer minimum value. */
#define C_UTILS_UINT32_MIN ULONG_MIN

/* C-Utils 32 bits unsigned integer maximum value. */
#define C_UTILS_UINT32_MAX ULONG_MAX
#else
#error "FATAL ERROR: UINT_MAX != 0xFFFFFFFFUL && ULONG_MAX != 0xFFFFFFFFUL."
#endif

#if FLT_MANT_DIG == 24 && FLT_MAX_EXP == 128 && FLT_MIN_EXP == -125
/* C-Utils 4 bytes float type (23 bits of fraction, 8 bits of exponent and 1 bit of sign). */
typedef float c_utils_float32_t;

/* C-Utils 32 bits float minimum value. */
#define C_UTILS_FLOAT32_MIN FLT_MIN

/* C-Utils 32 bits float maximum value. */
#define C_UTILS_FLOAT32_MAX FLT_MAX

/* C-Utils 32 bits float epsilon value. */
#define C_UTILS_FLOAT32_EPSILON FLT_EPSILON

/* C-Utils 32 bits float minimum exponent value. */
#define C_UTILS_FLOAT32_EXP_MIN FLT_MIN_EXP

/* C-Utils 32 bits float maximum exponent value. */
#define C_UTILS_FLOAT32_EXP_MAX FLT_MAX_EXP
#else
#error "FATAL ERROR: IEEE 754 (Single precision float) not detected."
#endif

/******************/
/* 8 bytes types: */
/******************/

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L) || \
     defined(C_UTILS_ENABLE_INT64) || defined(C_UTILS_ENABLE_ALL_EXTENSIONS)
#if ULONG_MAX == 0xFFFFFFFFFFFFFFFFULL
/* C-Utils 8 bytes signed integer type (63 bits for numbers and 1 bit for signal). */
typedef signed long int c_utils_int64_t;

/* C-Utils 64 bits signed integer minimum value. */
#define C_UTILS_INT64_MIN LONG_MIN

/* C-Utils 64 bits signed integer maximum value. */
#define C_UTILS_INT64_MAX LONG_MAX

/* C-Utils 8 bytes unsigned integer type (64 bits for numbers). */
typedef unsigned long int c_utils_uint64_t;

/* C-Utils 64 bits unsigned integer minimum value. */
#define C_UTILS_UINT64_MIN ULONG_MIN

/* C-Utils 64 bits unsigned integer maximum value. */
#define C_UTILS_UINT64_MAX ULONG_MAX
#elif ULLONG_MAX == 0xFFFFFFFFFFFFFFFFULL
/* C-Utils 8 bytes signed integer type (63 bits for numbers and 1 bit for signal). */
typedef signed long long int c_utils_int64_t;

/* C-Utils 64 bits signed integer minimum value. */
#define C_UTILS_INT64_MIN LLONG_MIN

/* C-Utils 64 bits signed integer maximum value. */
#define C_UTILS_INT64_MAX LLONG_MAX

/* C-Utils 8 bytes unsigned integer type (64 bits for numbers). */
typedef unsigned long long int c_utils_uint64_t;

/* C-Utils 64 bits unsigned integer minimum value. */
#define C_UTILS_UINT64_MIN ULLONG_MIN

/* C-Utils 64 bits unsigned integer maximum value. */
#define C_UTILS_UINT64_MAX ULLONG_MAX
#else
#error "FATAL ERROR: ULONG_MAX != 0xFFFFFFFFFFFFFFFFULL && ULLONG_MAX != 0xFFFFFFFFFFFFFFFFULL."
#endif
#endif

#if DBL_MANT_DIG == 53 && DBL_MAX_EXP == 1024 && DBL_MIN_EXP == -1021
/* C-Utils 8 bytes float type (52 bits of fraction, 11 bits of exponent and 1 bit of sign). */
typedef double c_utils_float64_t;

/* C-Utils 64 bits float minimum value. */
#define C_UTILS_FLOAT64_MIN DBL_MIN

/* C-Utils 64 bits float maximum value. */
#define C_UTILS_FLOAT64_MAX DBL_MAX

/* C-Utils 64 bits float epsilon value. */
#define C_UTILS_FLOAT64_EPSILON DBL_EPSILON

/* C-Utils 64 bits float minimum exponent value. */
#define C_UTILS_FLOAT64_EXP_MIN DBL_MIN_EXP

/* C-Utils 64 bits float maximum exponent value. */
#define C_UTILS_FLOAT64_EXP_MAX DBL_MAX_EXP
#else
#error "FATAL ERROR: IEEE 754 (Double precision float) not detected."
#endif

/********************/
/* Import C to C++: */
/********************/

#ifdef __cplusplus
extern "C"
{
#endif

/********************/
/* Terminal colors: */
/********************/

/* C-Utils Reset terminal text constant. */
extern const c_utils_char_t *const C_UTILS_BASE_TERMINAL;

/* C-Utils Bold terminal text constant. */
extern const c_utils_char_t *const C_UTILS_BOLD_TERMINAL;

/* C-Utils Reset and bold terminal text constant. */
extern const c_utils_char_t *const C_UTILS_BASE_BOLD_TERMINAL;

/* C-Utils Italic terminal text constant (Not supported by DOS). */
extern const c_utils_char_t *const C_UTILS_ITALIC_TERMINAL;

/* Underline terminal text constant. */
extern const c_utils_char_t *const C_UTILS_UNDERLINE_TERMINAL;

/* Black terminal text constant. */
extern const c_utils_char_t *const C_UTILS_FOREGROUND_BLACK_CLR;

/* Red terminal text constant. */
extern const c_utils_char_t *const C_UTILS_FOREGROUND_RED_CLR;

/* Green terminal text constant. */
extern const c_utils_char_t *const C_UTILS_FOREGROUND_GREEN_CLR;

/* Yellow terminal text constant. */
extern const c_utils_char_t *const C_UTILS_FOREGROUND_YELLOW_CLR;

/* Blue terminal text constant. */
extern const c_utils_char_t *const C_UTILS_FOREGROUND_BLUE_CLR;

/* Magenta terminal text constant. */
extern const c_utils_char_t *const C_UTILS_FOREGROUND_MAGENTA_CLR;

/* Cyan terminal text constant. */
extern const c_utils_char_t *const C_UTILS_FOREGROUND_CYAN_CLR;

/* White terminal text constant. */
extern const c_utils_char_t *const C_UTILS_FOREGROUND_WHITE_CLR;

/****************************/
/* C Utils errors handlers: */
/****************************/

/* C-Utils simple success code (0). */
extern const c_utils_int16_t C_UTILS_SUCCESS;

/* C-Utils simple error code (1). */
extern const c_utils_int16_t C_UTILS_FAILURE;

/*********************************/
/* Recommended precision values: */
/*********************************/

/* Minimum recommended precision value constant. */
extern const signed int C_UTILS_MIN_RPV;

/* Maximum recommended precision value constant. */
extern const signed int C_UTILS_MAX_RPV;

/********************/
/* Standardization: */
/********************/

/* C-Utils machine bits constant. */
extern const c_utils_uint16_t C_UTILS_MACHINE_BITS;

/******************************/
/* C-Utils version constants: */
/******************************/

/* C-Utils version full constant. */
extern const c_utils_int32_t C_UTILS_VERSION_FULL;

/* C-Utils version year constant. */
extern const c_utils_int32_t C_UTILS_VERSION_YEAR;

/* C-Utils version month constant. */
extern const c_utils_int32_t C_UTILS_VERSION_MONTH;

/* C-Utils version day constant. */
extern const c_utils_int32_t C_UTILS_VERSION_DAY;

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif

/***********************/
/* End C_UTILS_DEFS_H. */
/***********************/

#endif
