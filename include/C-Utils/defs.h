/* Include guard: */
#ifndef C_UTILS_DEFS_H
#define C_UTILS_DEFS_H

/* Solve some systems issues: */
#if (!defined(__USE_MINGW_ANSI_STDIO)) && ((defined(_MSVC_LANG) && _MSVC_LANG < 201103L) || (defined(__cplusplus) && __cplusplus < 201103L))
#define __USE_MINGW_ANSI_STDIO 1
#endif

/* Solve strdup. */
#if defined(_WIN32) || defined(_WIN64)
#undef strdup
#define strdup _strdup
#elif (!defined(__cplusplus) && defined(__STDC__)) && (defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__))
#undef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif

/* Terminal colors: */
extern const char *const C_UTILS_BASE_TERMINAL     ; /* Reset terminal text constant.                 */
extern const char *const C_UTILS_BOLD              ; /* Bold terminal text constant.                  */
extern const char *const C_UTILS_BASE_TERMINAL_BOLD; /* Reset and bold terminal text constant.        */
extern const char *const C_UTILS_ITALIC            ; /* Italic terminal text constant.                */
extern const char *const C_UTILS_UNDERLINE         ; /* Underline terminal text constant.             */
extern const char *const C_UTILS_BLACK_COLOR       ; /* Black terminal text constant.                 */
extern const char *const C_UTILS_RED_COLOR         ; /* Red terminal text constant.                   */
extern const char *const C_UTILS_GREEN_COLOR       ; /* Green terminal text constant.                 */
extern const char *const C_UTILS_YELLOW_COLOR      ; /* Yellow terminal text constant.                */
extern const char *const C_UTILS_BLUE_COLOR        ; /* Blue terminal text constant.                  */
extern const char *const C_UTILS_MAGENTA_COLOR     ; /* Magenta terminal text constant.               */
extern const char *const C_UTILS_CYAN_COLOR        ; /* Cyan terminal text constant.                  */
extern const char *const C_UTILS_WHITE_COLOR       ; /* White terminal text constant.                 */

/* C Utils errors handlers. */
extern const signed int C_UTILS_SUCCESS            ; /* C-Utils success constant.                     */
extern const signed int C_UTILS_STANDARD_FAILURE   ; /* C-Utils failure constant.                     */
extern const signed int C_UTILS_INTERNAL_FAILURE   ; /* C-Utils internal failure constant.            */
extern const signed int C_UTILS_INPUT_FAILURE      ; /* C-Utils input failure constant.               */
extern const signed int C_UTILS_NOT_FOUND          ; /* C-Utils not found constant.                   */

/* Recommended precision value: */
extern const signed int C_UTILS_MIN_RPV            ; /* Minimum recommended precision value constant. */
extern const signed int C_UTILS_MAX_RPV            ; /* Maximum recommended precision value constant. */

/* C-Utils version variables: */
extern const signed long int C_UTILS_FULL_VERSION  ; /* C Utils full version constant.                */
extern const signed long int C_UTILS_MAJOR_VERSION ; /* C Utils major version constant.               */
extern const signed long int C_UTILS_MINOR_VERSION ; /* C Utils minor version constant.               */
extern const signed long int C_UTILS_PATCH_VERSION ; /* C Utils patch version constant.               */

/* End C_UTILS_DEFS_H. */
#endif
