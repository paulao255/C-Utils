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

c_utils_float32_t c_utils_circumfer_float32(const c_utils_float32_t radius_value)
{
	return 2.0f * C_UTILS_MATH_PI_FLOAT32 * radius_value;
}

c_utils_float32_t c_utils_circle_area_float32(const c_utils_float32_t radius_value)
{
	return C_UTILS_MATH_PI_FLOAT32 * (radius_value * radius_value);
}

c_utils_float32_t c_utils_sphere_volume_float32(const c_utils_float32_t radius_value)
{
	return (4.0f / 3.0f) * C_UTILS_MATH_PI_FLOAT32 * (radius_value * radius_value * radius_value);
}

c_utils_float32_t c_utils_summation_float32(c_utils_float32_t (*f)(c_utils_float32_t i), c_utils_int32_t lower_bound, const c_utils_int32_t upper_bound)
{
	c_utils_float32_t result = 0.0f;

	while(lower_bound <= upper_bound)
	{
		result += f((c_utils_float32_t)lower_bound);
		++lower_bound;
	}

	return result;
}

c_utils_float32_t c_utils_product_float32(c_utils_float32_t (*f)(c_utils_float32_t i), c_utils_int32_t lower_bound, const c_utils_int32_t upper_bound)
{
	c_utils_float32_t result = 1.0;

	while(lower_bound <= upper_bound)
	{
		result *= f((c_utils_float32_t)lower_bound);
		++lower_bound;
	}

	return result;
}

c_utils_float64_t c_utils_circumfer_float64(const c_utils_float64_t radius_value)
{
	return 2.0 * C_UTILS_MATH_PI_FLOAT64 * radius_value;
}

c_utils_float64_t c_utils_circle_area_float64(const c_utils_float64_t radius_value)
{
	return C_UTILS_MATH_PI_FLOAT64 * (radius_value * radius_value);
}

c_utils_float64_t c_utils_sphere_volume_float64(const c_utils_float64_t radius_value)
{
	return (4.0 / 3.0) * C_UTILS_MATH_PI_FLOAT64 * (radius_value * radius_value * radius_value);
}

c_utils_float64_t c_utils_summation_float64(c_utils_float64_t (*f)(c_utils_float64_t i), c_utils_int32_t lower_bound, const c_utils_int32_t upper_bound)
{
	c_utils_float64_t result = 0.0;

	while(lower_bound <= upper_bound)
	{
		result += f((c_utils_float64_t)lower_bound);
		++lower_bound;
	}

	return result;
}

c_utils_float64_t c_utils_product_float64(c_utils_float64_t (*f)(c_utils_float64_t i), c_utils_int32_t lower_bound, const c_utils_int32_t upper_bound)
{
	c_utils_float64_t result = 1.0;

	while(lower_bound <= upper_bound)
	{
		result *= f((c_utils_float64_t)lower_bound);
		++lower_bound;
	}

	return result;
}

/* End C to C++ importation: */
#ifdef __cplusplus
}
#endif
