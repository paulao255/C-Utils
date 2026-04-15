/* Include guard: */
#ifndef C_UTILS_DEFS_H
#define C_UTILS_DEFS_H

/* Solve some systems issues: */
#if (!defined(__USE_MINGW_ANSI_STDIO)) && ((defined(_MSVC_LANG) && _MSVC_LANG < 201103L) || (defined(__cplusplus) && __cplusplus < 201103L))
#define __USE_MINGW_ANSI_STDIO 1
#endif

#if defined(_WIN32) || defined(_WIN64)
#undef strdup
#define strdup _strdup
#elif (!defined(__cplusplus) && defined(__STDC__)) && (defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__))
#undef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/* Terminal colors: */
const char *const C_UTILS_BASE_TERMINAL      = "\033[0m"       ; /* Reset terminal text constant.                 */
const char *const C_UTILS_BOLD               = "\033[1m"       ; /* Bold terminal text constant.                  */
const char *const C_UTILS_BASE_TERMINAL_BOLD = "\033[0m\033[1m"; /* Reset and bold terminal text constant.        */
const char *const C_UTILS_ITALIC             = "\033[3m"       ; /* Italic terminal text constant.                */
const char *const C_UTILS_UNDERLINE          = "\033[4m"       ; /* Underline terminal text constant.             */
const char *const C_UTILS_BLACK_COLOR        = "\033[30m"      ; /* Black terminal text constant.                 */
const char *const C_UTILS_RED_COLOR          = "\033[31m"      ; /* Red terminal text constant.                   */
const char *const C_UTILS_GREEN_COLOR        = "\033[32m"      ; /* Green terminal text constant.                 */
const char *const C_UTILS_YELLOW_COLOR       = "\033[33m"      ; /* Yellow terminal text constant.                */
const char *const C_UTILS_BLUE_COLOR         = "\033[34m"      ; /* Blue terminal text constant.                  */
const char *const C_UTILS_MAGENTA_COLOR      = "\033[35m"      ; /* Magenta terminal text constant.               */
const char *const C_UTILS_CYAN_COLOR         = "\033[36m"      ; /* Cyan terminal text constant.                  */
const char *const C_UTILS_WHITE_COLOR        = "\033[37m"      ; /* White terminal text constant.                 */

/* C Utils errors handlers. */
const signed int C_UTILS_SUCCESS             =  0              ; /* C-Utils success constant.                     */
const signed int C_UTILS_STANDARD_FAILURE    = -1              ; /* C-Utils failure constant.                     */
const signed int C_UTILS_INTERNAL_FAILURE    = -2              ; /* C-Utils internal failure constant.            */
const signed int C_UTILS_INPUT_FAILURE       = -3              ; /* C-Utils input failure constant.               */
const signed int C_UTILS_NOT_FOUND           = -4              ; /* C-Utils not found constant.                   */

/* Recommended precision value: */
const signed int C_UTILS_MIN_RPV             =  0              ; /* Minimum recommended precision value constant. */
const signed int C_UTILS_MAX_RPV             = 18              ; /* Maximum recommended precision value constant. */

/* C-Utils version variables: */
const signed long int C_UTILS_FULL_VERSION   = 20260415L       ; /* C Utils full version constant.                */
const signed long int C_UTILS_MAJOR_VERSION  = 2026L           ; /* C Utils major version constant.               */
const signed long int C_UTILS_MINOR_VERSION  = 4L	       ; /* C Utils minor version constant.               */
const signed long int C_UTILS_PATCH_VERSION  = 15L             ; /* C Utils patch version constant.               */

#ifdef __cplusplus
}
#endif

#endif
