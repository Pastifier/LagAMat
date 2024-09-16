/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_operations.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 04:55:47 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/16 12:41:39 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLE_OPERATIONS_H
# define SIMPLE_OPERATIONS_H

# include "ltypes.h"
# include <math.h>
# include <string.h>

/// @brief Performs component-wise (vector) addition and stores the result
///        in the vector pointed-to by `out`.
/// @param in1, in2 operand
/// @param out Pointer to the vector that stores the result.
static inline void	lag_vec4d_add(t_vec4d *out, const t_vec4d in1,
						const t_vec4d in2)
{
	out->simd = _mm256_add_pd(in1.simd, in2.simd);
}

/// @brief Performs component-wise (vector) addition.
///        This is to be used when performance is not a concern
///        (i.e. modern compilers, single-usage, etc...),
///        or when function-chaining is desired.
static inline t_vec4d	lag_vec4d_add_ret(const t_vec4d in1, const t_vec4d in2)
{
	return ((t_vec4d)
	{
		.simd = _mm256_add_pd(in1.simd, in2.simd)
	});
}

/// @brief Performs component-wise (vector) subtraction and stores the result
///        in the vector pointed-to by `out`.
/// @param in1, in2 operand
/// @param out Pointer to the vector that stores the result.
static inline void	lag_vec4d_sub(t_vec4d *out, const t_vec4d in1, const t_vec4d in2)
{
	out->simd = _mm256_sub_pd(in1.simd, in2.simd);
}

/// @brief Performs component-wise (vector) subtraction.
///        This is to be used when performance is not a concern
///        (i.e. modern compilers, single-usage, etc...),
///        or when function-chaining is desired.
static inline t_vec4d	lag_vec4d_sub_ret(const t_vec4d in1, const t_vec4d in2)
{
	return ((t_vec4d)
	{
		.simd = _mm256_sub_pd(in1.simd, in2.simd)
	});
}

/// @brief Scales a vector by a scalar and stores the result in the vector
///        pointed-to by `out`.
/// @param in Vector to be scaled
/// @param scalar Scalar to scale the vector by
static inline void	lag_vec4d_scaleby(t_vec4d *out, const t_vec4d in,
						double scalar)
{
	out->simd = _mm256_mul_pd(in.simd, _mm256_set1_pd(scalar));
}

/// @brief Scales a vector by a scalar.
///        This is to be used when performance is not a concern
///        (i.e. modern compilers, single-usage, etc...),
///        or when function-chaining is desired.
static inline t_vec4d	lag_vec4d_scaleby_ret(const t_vec4d in, double scalar)
{
	return ((t_vec4d)
	{
		.simd = _mm256_mul_pd(in.simd, _mm256_set1_pd(scalar))
	});
}

/// @brief Negates a vector and stores the result
///        in the vector pointed-to by `out`.
/// @param in Vector to be negated
/// @param out Pointer to the vector that stores the result.
static inline void	lag_vec4d_negate_new(t_vec4d *out, const t_vec4d in)
{
	out->simd = _mm256_sub_pd(_mm256_set1_pd(0.0), in.simd);
}

/// @brief Negates a vector in place.
/// @param target Pointer to vector to be negated
static inline void	lag_vec4d_negate(t_vec4d *target)
{
	target->simd = _mm256_sub_pd(_mm256_set1_pd(0.0), target->simd);
}

/// @brief Negates a vector.
///        This is to be used when performance is not a concern
///        (i.e. modern compilers, single-usage, etc...),
///        or when function-chaining is desired.
static inline t_vec4d	lag_vec4d_negate_ret(const t_vec4d in)
{
	return ((t_vec4d)
	{
		.simd = _mm256_sub_pd(_mm256_set1_pd(0.0), in.simd)
	});
}
//// DEPRECATED
// @brief Calculates the magnitude of a vector and stores the result
//        in the variable pointed-to by `out`.
// @param in Vector to calculate the magnitude of
// @param out Pointer to the variable that stores the result.
//static inline void	lag_vec4d_magnitude(double *out, const t_vec4d in)
//{
//	__m128d sum;
//	const __m256d squared = _mm256_mul_pd(in.simd, in.simd);
//	// this step is required because _mm_hadd_pd only works on 128-bit values,
//	// and there isn't a "full"-suite of intrinsic functions for 256-bit values
//	const __m128d low_part = _mm256_castpd256_pd128(squared);
//	const __m128d high_part = _mm256_extractf128_pd(squared, 1);

//	sum = _mm_add_pd(low_part, high_part);
//	sum = _mm_hadd_pd(sum, sum);
//	*out = sqrt(_mm_cvtsd_f64(sum));
//}
//// DEPRECATED

// @brief Calculates the dot product of two vectors and stores the result
//        in the variable pointed-to by `out`.
// @param in1 Vector to calculate the dot product of
// @param in2 Vector to calculate the dot product of
// @param out Pointer to the variable that stores the result.

typedef __attribute((aligned(32))) double	t_vec4d4[4];

/// @brief Calculates the dot product of two vectors, and stores the result
///        in the variable pointed-to by `out`.
/// @param out Pointer to the variable that stores the result.
/// @param in1 Vector to calculate the dot product of
/// @param in2 Vector to calculate the dot product of
static inline void	lag_vec4d_dot(double *out, const t_vec4d in1, t_vec4d in2)
{
	t_vec4d4		result;
	const __m256d	product = _mm256_mul_pd(in1.simd, in2.simd);

	_mm256_store_pd(result, _mm256_hadd_pd(product, product));
	*out = result[0] + result[2];
}

/// @brief Calculates the dot product of two vectors.
///        This is to be used when performance is not a concern
///        (i.e. modern compilers, single-usage, etc...),
///        or when function-chaining is desired.
static inline double	lag_vec4d_dot_ret(const t_vec4d in1, t_vec4d in2)
{
	t_vec4d4		result;
	const __m256d	product = _mm256_mul_pd(in1.simd, in2.simd);

	_mm256_store_pd(result, (_mm256_hadd_pd(product, product)));
	return (result[0] + result[2]);
}

/// @brief Calculates the magnitude of a vector and stores the result
///        in the variable pointed-to by `out`.
/// @param in Vector to calculate the magnitude of
/// @param out Pointer to the variable that stores the result.
static inline void	lag_vec4d_magnitude(double *out, const t_vec4d in)
{
	lag_vec4d_dot(out, in, in);
	*out = sqrt(*out);
}

/// @brief Calculates the magnitude of a vector.
///        This is to be used when performance is not a concern
///        (i.e. modern compilers, single-usage, etc...),
///        or when function-chaining is desired.
static inline double	lag_vec4d_magnitude_ret(const t_vec4d in)
{
	return (sqrt(lag_vec4d_dot_ret(in, in)));
}

/// @brief Normalizes a vector in place.
/// @param target Pointer to vector to be normalized
static inline void	lag_vec4d_normalize(t_vec4d *target)
{
	double	mag;

	lag_vec4d_magnitude(&mag, *target);
	if (mag == 0.0)
		lag_vec4d_scaleby(target, *target, 0.0);
	else
		lag_vec4d_scaleby(target, *target, 1.0 / mag);
}

/// @brief Returns a normalized version of the vector `in`.
/// @param in Vector to be normalized
static inline t_vec4d	lag_vec4d_normalize_ret(const t_vec4d in)
{
	double	mag;

	lag_vec4d_magnitude(&mag, in);
	if (mag == 0.0)
		return (lag_vec4d_scaleby_ret(in, 0.0));
	return (lag_vec4d_scaleby_ret(in, 1.0 / mag));
}

/// @brief Normalizes a vector and stores the result in the vector pointed-to by `out`.
/// @param out Pointer to the vector that stores the result.
/// @param in Vector to be normalized
static inline void	lag_vec4d_normalize_new(t_vec4d *out, const t_vec4d in)
{
	double	mag;

	lag_vec4d_magnitude(&mag, in);
	if (mag == 0.0)
		lag_vec4d_scaleby(out, in, 0.0);
	else
		lag_vec4d_scaleby(out, in, 1.0 / mag);
}

// I feel like fast-inverse square root is a bit overkill for this project
// but I feel like doing it now...

static inline double	fast_inverse_sqrt(double number)
{
	const double	half_number = 0.5 * number;
	int64_t			i;

	if (number == 0)
		return (0);
	memcpy(&i, &number, sizeof(i));
	i = 0x5fe6eb50c7b537a9 - (i >> 1);
	memcpy(&number, &i, sizeof(number));
	number *= (1.5 - half_number * number * number);
	number *= (1.5 - half_number * number * number);
	//number *= (1.5 - half_number * number * number);
	return (number);
}

/// @brief Normalizes a vector in place.
/// @param target Pointer to vector to be normalized
/// @note This function is faster than lag_vec4d_normalize() but less accurate
static inline void	lag_vec4d_normalize_fast(t_vec4d *target)
{
	double	mag_squared;

	lag_vec4d_dot(&mag_squared, *target, *target);
	lag_vec4d_scaleby(target, *target, fast_inverse_sqrt(mag_squared));
}

/// @brief Returns a normalized version of the vector `in`.
/// @param in Vector to be normalized
/// @note This function is faster than lag_vec4d_normalize() but less accurate
static inline t_vec4d	lag_vec4d_normalize_fast_ret(const t_vec4d in)
{
	double	mag_squared;
	
	lag_vec4d_dot(&mag_squared, in, in);
	return (lag_vec4d_scaleby_ret(in, fast_inverse_sqrt(mag_squared)));
}

/// @brief Normalizes a vector and stores the result in the vector pointed-to by `out`.
/// @param out Pointer to the vector that stores the result.
/// @param in Vector to be normalized
/// @note This function is faster than lag_vec4d_normalize() but less accurate
static inline void	lag_vec4d_normalize_fast_new(t_vec4d *out, const t_vec4d in)
{
	double	mag_squared;

	lag_vec4d_dot(&mag_squared, in, in);
	lag_vec4d_scaleby(out, in, fast_inverse_sqrt(mag_squared));
}

/// @brief Calculates the cross product of two 3D vectors (ignoring the w component) 
///        and stores the result in the vector pointed-to by `out`.
/// @param in1, in2 operand
/// @param out Pointer to the vector that stores the result.
static inline void	lag_vec4d_cross(t_vec4d *out, const t_vec4d in1, const t_vec4d in2)
{
	// Cross product calculation: [a_y*b_z - a_z*b_y, a_z*b_x - a_x*b_z, a_x*b_y - a_y*b_x, 0]
	__m256d a_yzx = _mm256_permute4x64_pd(in1.simd, _MM_SHUFFLE(3, 0, 2, 1));
	__m256d b_yzx = _mm256_permute4x64_pd(in2.simd, _MM_SHUFFLE(3, 0, 2, 1));
	__m256d a_zxy = _mm256_permute4x64_pd(in1.simd, _MM_SHUFFLE(3, 1, 0, 2));
	__m256d b_zxy = _mm256_permute4x64_pd(in2.simd, _MM_SHUFFLE(3, 1, 0, 2));
	out->simd = _mm256_sub_pd(_mm256_mul_pd(a_yzx, b_zxy), _mm256_mul_pd(a_zxy, b_yzx));
}

/// @brief Calculates the cross product of two 3D vectors (ignoring the w component).
///        This is to be used when performance is not a concern
///        (i.e. modern compilers, single-usage, etc...),
///        or when function-chaining is desired.
static inline t_vec4d	lag_vec4d_cross_ret(const t_vec4d in1, const t_vec4d in2)
{
	__m256d a_yzx = _mm256_permute4x64_pd(in1.simd, _MM_SHUFFLE(3, 0, 2, 1));
	__m256d b_yzx = _mm256_permute4x64_pd(in2.simd, _MM_SHUFFLE(3, 0, 2, 1));
	__m256d a_zxy = _mm256_permute4x64_pd(in1.simd, _MM_SHUFFLE(3, 1, 0, 2));
	__m256d b_zxy = _mm256_permute4x64_pd(in2.simd, _MM_SHUFFLE(3, 1, 0, 2));
	return ((t_vec4d)
	{
		.simd = _mm256_sub_pd(_mm256_mul_pd(a_yzx, b_zxy), _mm256_mul_pd(a_zxy, b_yzx))
	});
}



#endif // !SIMPLE_OPERATIONS_H