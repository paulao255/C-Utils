/* Importations: */
#include "definitions.h"


/* Import C to C++: */
#ifdef __cplusplus
extern "C"
{
#endif

/* Terminal colors: */
const c_utils_char_t *const C_UTILS_BASE_TERMINAL      = "\033[0m"       ;
const c_utils_char_t *const C_UTILS_BOLD               = "\033[1m"       ;
const c_utils_char_t *const C_UTILS_BASE_TERMINAL_BOLD = "\033[0m\033[1m";
const c_utils_char_t *const C_UTILS_ITALIC             = "\033[3m"       ;
const c_utils_char_t *const C_UTILS_UNDERLINE          = "\033[4m"       ;
const c_utils_char_t *const C_UTILS_BLACK_COLOR        = "\033[30m"      ;
const c_utils_char_t *const C_UTILS_RED_COLOR          = "\033[31m"      ;
const c_utils_char_t *const C_UTILS_GREEN_COLOR        = "\033[32m"      ;
const c_utils_char_t *const C_UTILS_YELLOW_COLOR       = "\033[33m"      ;
const c_utils_char_t *const C_UTILS_BLUE_COLOR         = "\033[34m"      ;
const c_utils_char_t *const C_UTILS_MAGENTA_COLOR      = "\033[35m"      ;
const c_utils_char_t *const C_UTILS_CYAN_COLOR         = "\033[36m"      ;
const c_utils_char_t *const C_UTILS_WHITE_COLOR        = "\033[37m"      ;

/* C Utils errors handlers. */
const c_utils_int16_t C_UTILS_SUCCESS                  = 0               ;
const c_utils_int16_t C_UTILS_FAILURE                  = 1               ;

/* Recommended precision value: */
const signed int C_UTILS_MIN_RPV                       = 0               ;
const signed int C_UTILS_MAX_RPV                       = 18              ;

/* Standardization: */
const c_utils_int32_t C_UTILS_MACHINE_BITS   =
#if defined(_WIN64) || defined(__x86_64__) || defined(__aarch64__) || defined(__powerpc64__) || defined(__ppc64__)
	64L;
#elif defined(_WIN32) || defined(__i386__) || defined(__arm__) || defined(__XTENSA__)
	32L;
#else
	0L;
#endif

/* C-Utils version variables: */
const c_utils_int32_t C_UTILS_FULL_VERSION             = 20260522L       ;
const c_utils_int32_t C_UTILS_MAJOR_VERSION            = 2026L           ;
const c_utils_int32_t C_UTILS_MINOR_VERSION            = 5L	         ;
const c_utils_int32_t C_UTILS_PATCH_VERSION            = 22L             ;

/* End C to C++ importation: */
#ifdef __cplusplus
}
#endif
