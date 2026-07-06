/*************************/
/* Library importations: */
/*************************/

#include "defs.h"

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

const c_utils_char_t *const C_UTILS_BASE_TERMINAL = "\x1B[0m";
const c_utils_char_t *const C_UTILS_BOLD_TERMINAL = "\x1B[1m";
const c_utils_char_t *const C_UTILS_BASE_BOLD_TERMINAL = "\x1B[0m\x1B[1m";
#if defined(__DOS__) || defined(MSDOS) || defined(_MSDOS) || defined (__MSDOS__) || defined(__DOS_386__) || defined(__DJGPP__)
const c_utils_char_t *const C_UTILS_ITALIC_TERMINAL = "";
#else
const c_utils_char_t *const C_UTILS_ITALIC_TERMINAL = "\x1B[3m";
#endif
const c_utils_char_t *const C_UTILS_UNDERLINE_TERMINAL = "\x1B[4m";
const c_utils_char_t *const C_UTILS_FOREGROUND_BLACK_CLR = "\x1B[30m";
const c_utils_char_t *const C_UTILS_FOREGROUND_RED_CLR = "\x1B[31m";
const c_utils_char_t *const C_UTILS_FOREGROUND_GREEN_CLR = "\x1B[32m";
const c_utils_char_t *const C_UTILS_FOREGROUND_YELLOW_CLR = "\x1B[33m";
const c_utils_char_t *const C_UTILS_FOREGROUND_BLUE_CLR = "\x1B[34m";
const c_utils_char_t *const C_UTILS_FOREGROUND_MAGENTA_CLR = "\x1B[35m";
const c_utils_char_t *const C_UTILS_FOREGROUND_CYAN_CLR = "\x1B[36m";
const c_utils_char_t *const C_UTILS_FOREGROUND_WHITE_CLR = "\x1B[37m";

/****************************/
/* C Utils errors handlers: */
/****************************/

const c_utils_int16_t C_UTILS_SUCCESS = 0;
const c_utils_int16_t C_UTILS_FAILURE = 1;

/*********************************/
/* Recommended precision values: */
/*********************************/

const signed int C_UTILS_MIN_RPV = 0;
const signed int C_UTILS_MAX_RPV = 18;

/********************/
/* Standardization: */
/********************/

const c_utils_uint16_t C_UTILS_MACHINE_BITS =
#if defined(_WIN64) || defined(__x86_64__) || defined(__aarch64__) || defined(__powerpc64__) || defined(__ppc64__)
64u
#elif defined(_WIN32) || defined(__i386__) || defined(__arm__) || defined(ESP_PLATFORM) || defined(__386__)
32u
#elif defined(M_I86)
16u
#else
0u
#endif
;

/******************************/
/* C-Utils version constants: */
/******************************/

const c_utils_int32_t C_UTILS_FULL_VERSION = 20260706L;
const c_utils_int32_t C_UTILS_MAJOR_VERSION = 2026L;
const c_utils_int32_t C_UTILS_MINOR_VERSION = 7L;
const c_utils_int32_t C_UTILS_PATCH_VERSION = 6L;

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif
