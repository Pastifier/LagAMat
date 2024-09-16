/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_operations_4.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:21:01 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/16 11:42:17 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLE_OPERATIONS_4_H
# define SIMPLE_OPERATIONS_4_H

# include "simple_operations_3.h"

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

/// @brief Normalizes a vector and stores the result
///        in the vector pointed-to by `out`.
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

/// @brief Calculates the cross product of two 3D vectors
///        (ignoring the w component) and stores the result
///        in the vector pointed-to by `out`.
/// @param in1, in2 operand
/// @param out Pointer to the vector that stores the result.
static inline void	lag_vec4d_cross(t_vec4d *out, const t_vec4d in1,
						const t_vec4d in2)
{
	__m256d	a_yzx;
	__m256d	b_yzx;
	__m256d	a_zxy;
	__m256d	b_zxy;

	a_yzx = _mm256_permute4x64_pd(in1.simd, _MM_SHUFFLE(3, 0, 2, 1));
	b_yzx = _mm256_permute4x64_pd(in2.simd, _MM_SHUFFLE(3, 0, 2, 1));
	a_zxy = _mm256_permute4x64_pd(in1.simd, _MM_SHUFFLE(3, 1, 0, 2));
	b_zxy = _mm256_permute4x64_pd(in2.simd, _MM_SHUFFLE(3, 1, 0, 2));
	out->simd = _mm256_sub_pd(\
		_mm256_mul_pd(a_yzx, b_zxy), \
		_mm256_mul_pd(a_zxy, b_yzx) \
	);
}

/// @brief Calculates the cross product of two 3D vectors
///        (ignoring the w component).
///        This is to be used when performance is not a concern
///        (i.e. modern compilers, single-usage, etc...),
///        or when function-chaining is desired.
static inline t_vec4d	lag_vec4d_cross_ret(const t_vec4d in1,
							const t_vec4d in2)
{
	__m256d	a_yzx;
	__m256d	b_yzx;
	__m256d	a_zxy;
	__m256d	b_zxy;

	a_yzx = _mm256_permute4x64_pd(in1.simd, _MM_SHUFFLE(3, 0, 2, 1));
	b_yzx = _mm256_permute4x64_pd(in2.simd, _MM_SHUFFLE(3, 0, 2, 1));
	a_zxy = _mm256_permute4x64_pd(in1.simd, _MM_SHUFFLE(3, 1, 0, 2));
	b_zxy = _mm256_permute4x64_pd(in2.simd, _MM_SHUFFLE(3, 1, 0, 2));
	return ((t_vec4d)
		{
			.simd = _mm256_sub_pd(
				_mm256_mul_pd(a_yzx, b_zxy),
				_mm256_mul_pd(a_zxy, b_yzx)
			)
		});
}

#endif // !SIMPLE_OPERATIONS_4_H