/* Importations: */
#include "math-utils.h"


/* Import C to C++: */
#ifdef __cplusplus
extern "C"
{
#endif

/* Pi constants: */
const c_utils_float32_t C_UTILS_MATH_PI_FLOAT32 = 3.141592653589793f;
const c_utils_float64_t C_UTILS_MATH_PI_FLOAT64 = 3.141592653589793 ;

c_utils_float32_t c_utils_circumfer_float(const c_utils_float32_t radius_value)
{
	return 2.0f * C_UTILS_MATH_PI_FLOAT32 * radius_value;
}

c_utils_float32_t c_utils_circle_area_float(const c_utils_float32_t radius_value)
{
	return C_UTILS_MATH_PI_FLOAT32 * (radius_value * radius_value);
}

c_utils_float32_t c_utils_sphere_volume_float(const c_utils_float32_t radius_value)
{
	return (4.0f / 3.0f) * C_UTILS_MATH_PI_FLOAT32 * (radius_value * radius_value * radius_value);
}

c_utils_float32_t c_utils_summation_float(c_utils_float32_t (*f)(c_utils_float32_t i), c_utils_int32_t index, const c_utils_int32_t end)
{
	c_utils_float32_t result = 0.0f;

	while(index <= end)
	{
		result = result + f((c_utils_float32_t)index);
		++index;
	}

	return result;
}

c_utils_float64_t c_utils_circumfer_double(const c_utils_float64_t radius_value)
{
	return 2.0 * C_UTILS_MATH_PI_FLOAT64 * radius_value;
}

c_utils_float64_t c_utils_circle_area_double(const c_utils_float64_t radius_value)
{
	return C_UTILS_MATH_PI_FLOAT64 * (radius_value * radius_value);
}

c_utils_float64_t c_utils_sphere_volume_double(const c_utils_float64_t radius_value)
{
	return (4.0 / 3.0) * C_UTILS_MATH_PI_FLOAT64 * (radius_value * radius_value * radius_value);
}

c_utils_float64_t c_utils_summation_double(c_utils_float64_t (*f)(c_utils_float64_t i), c_utils_int32_t index, const c_utils_int32_t end)
{
	c_utils_float64_t result = 0.0;

	while(index <= end)
	{
		result = result + f((c_utils_float64_t)index);
		++index;
	}

	return result;
}

/* End C to C++ importation: */
#ifdef __cplusplus
}
#endif
