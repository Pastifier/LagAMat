/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_operations_3_ps.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 01:27:03 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/19 03:09:07 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLE_OPERATIONS_3_PS_H
# define SIMPLE_OPERATIONS_3_PS_H

# include "simple_operations_2_ps.h"

/// @brief Calculates the dot product of two `t_vec4s`, and stores the result
///        in the variable pointed-to by `out`.
/// @param out Pointer to the variable that stores the result.
/// @param in1 Vector to calculate the dot product of
/// @param in2 Vector to calculate the dot product of
static inline void	lag_vec4s_dot(float *out, const t_vec4s in1,
						const t_vec4s in2)
{
	*out = _mm_cvtss_f32(_mm_dp_ps(in1.simd, in2.simd, 0xF1));
}

/// @brief Calculates the dot product of two `t_vec4s`.
static inline float	lag_vec4s_dot_ret(const t_vec4s in1,
							const t_vec4s in2)
{
	return (_mm_cvtss_f32(_mm_dp_ps(in1.simd, in2.simd, 0xF1)));
}

/// @brief Calculates the magnitude of a `t_vec4s` and stores the result
///        in the variable pointed-to by `out`.
/// @param in Vector to calculate the magnitude of
/// @param out Pointer to the variable that stores the result.
static inline void	lag_vec4s_magnitude(float *out, const t_vec4s in)
{
	const __m128	mul0 = _mm_dp_ps(in.simd, in.simd, 0xF1);
	const __m128	sqt0 = _mm_sqrt_ps(mul0);

	*out = _mm_cvtss_f32(sqt0);
}

/// @brief Calculates the magnitude of a `t_vec4s`.
static inline float	lag_vec4s_magnitude_ret(const t_vec4s in)
{
	const __m128	mul0 = _mm_dp_ps(in.simd, in.simd, 0xF1);
	const __m128	sqt0 = _mm_sqrt_ps(mul0);

	return(_mm_cvtss_f32(sqt0));
}

#endif // !SIMPLE_OPERATIONS_3_PS_H