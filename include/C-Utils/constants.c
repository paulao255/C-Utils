#if defined(__cplusplus)
extern "C"
{
#endif

/* Terminal colors: */
const char *const C_UTILS_BASE_TERMINAL      = "\033[0m"       ;
const char *const C_UTILS_BOLD               = "\033[1m"       ;
const char *const C_UTILS_BASE_TERMINAL_BOLD = "\033[0m\033[1m";
const char *const C_UTILS_ITALIC             = "\033[3m"       ;
const char *const C_UTILS_UNDERLINE          = "\033[4m"       ;
const char *const C_UTILS_BLACK_COLOR        = "\033[30m"      ;
const char *const C_UTILS_RED_COLOR          = "\033[31m"      ;
const char *const C_UTILS_GREEN_COLOR        = "\033[32m"      ;
const char *const C_UTILS_YELLOW_COLOR       = "\033[33m"      ;
const char *const C_UTILS_BLUE_COLOR         = "\033[34m"      ;
const char *const C_UTILS_MAGENTA_COLOR      = "\033[35m"      ;
const char *const C_UTILS_CYAN_COLOR         = "\033[36m"      ;
const char *const C_UTILS_WHITE_COLOR        = "\033[37m"      ;

/* C Utils errors handlers. */
const signed int C_UTILS_SUCCESS             =  0              ;
const signed int C_UTILS_STANDARD_FAILURE    = -1              ;
const signed int C_UTILS_INTERNAL_FAILURE    = -2              ;
const signed int C_UTILS_INPUT_FAILURE       = -3              ;
const signed int C_UTILS_NOT_FOUND           = -4              ;

/* Recommended precision value: */
const signed int C_UTILS_MIN_RPV             =  0              ;
const signed int C_UTILS_MAX_RPV             = 18              ;

/* C-Utils version variables: */
const signed long int C_UTILS_FULL_VERSION   = 20260503L       ;
const signed long int C_UTILS_MAJOR_VERSION  = 2026L           ;
const signed long int C_UTILS_MINOR_VERSION  = 5L	       ;
const signed long int C_UTILS_PATCH_VERSION  = 6L              ;

#if defined(__cplusplus)
}
#endif
