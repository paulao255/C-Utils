#if defined(__cplusplus)
extern "C"
{
#endif

/* Terminal colors: */
const unsigned char *const C_UTILS_BASE_TERMINAL      = (const unsigned char *const)"\033[0m"       ; /* Reset terminal text constant.                 */
const unsigned char *const C_UTILS_BOLD               = (const unsigned char *const)"\033[1m"       ; /* Bold terminal text constant.                  */
const unsigned char *const C_UTILS_BASE_TERMINAL_BOLD = (const unsigned char *const)"\033[0m\033[1m"; /* Reset and bold terminal text constant.        */
const unsigned char *const C_UTILS_ITALIC             = (const unsigned char *const)"\033[3m"       ; /* Italic terminal text constant.                */
const unsigned char *const C_UTILS_UNDERLINE          = (const unsigned char *const)"\033[4m"       ; /* Underline terminal text constant.             */
const unsigned char *const C_UTILS_BLACK_COLOR        = (const unsigned char *const)"\033[30m"      ; /* Black terminal text constant.                 */
const unsigned char *const C_UTILS_RED_COLOR          = (const unsigned char *const)"\033[31m"      ; /* Red terminal text constant.                   */
const unsigned char *const C_UTILS_GREEN_COLOR        = (const unsigned char *const)"\033[32m"      ; /* Green terminal text constant.                 */
const unsigned char *const C_UTILS_YELLOW_COLOR       = (const unsigned char *const)"\033[33m"      ; /* Yellow terminal text constant.                */
const unsigned char *const C_UTILS_BLUE_COLOR         = (const unsigned char *const)"\033[34m"      ; /* Blue terminal text constant.                  */
const unsigned char *const C_UTILS_MAGENTA_COLOR      = (const unsigned char *const)"\033[35m"      ; /* Magenta terminal text constant.               */
const unsigned char *const C_UTILS_CYAN_COLOR         = (const unsigned char *const)"\033[36m"      ; /* Cyan terminal text constant.                  */
const unsigned char *const C_UTILS_WHITE_COLOR        = (const unsigned char *const)"\033[37m"      ; /* White terminal text constant.                 */

/* C Utils errors handlers. */
const signed int C_UTILS_SUCCESS                      =  0                                          ; /* C-Utils success constant.                     */
const signed int C_UTILS_STANDARD_FAILURE             = -1                                          ; /* C-Utils failure constant.                     */
const signed int C_UTILS_INTERNAL_FAILURE             = -2                                          ; /* C-Utils internal failure constant.            */
const signed int C_UTILS_INPUT_FAILURE                = -3                                          ; /* C-Utils input failure constant.               */
const signed int C_UTILS_NOT_FOUND                    = -4                                          ; /* C-Utils not found constant.                   */

/* Recommended precision value: */
const signed int C_UTILS_MIN_RPV                      =  0                                          ; /* Minimum recommended precision value constant. */
const signed int C_UTILS_MAX_RPV                      = 18                                          ; /* Maximum recommended precision value constant. */

/* C-Utils version variables: */
const signed long int C_UTILS_FULL_VERSION            = 20260418L                                   ; /* C Utils full version constant.                */
const signed long int C_UTILS_MAJOR_VERSION           = 2026L                                       ; /* C Utils major version constant.               */
const signed long int C_UTILS_MINOR_VERSION           = 4L	                                    ; /* C Utils minor version constant.               */
const signed long int C_UTILS_PATCH_VERSION           = 18L                                         ; /* C Utils patch version constant.               */

#if defined(__cplusplus)
}
#endif
