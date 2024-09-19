/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_operations_4_ps.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 03:28:04 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/19 04:13:50 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLE_OPERATIONS_4_PS_H
# define SIMPLE_OPERATIONS_4_PS_H

# include "simple_operations_3_ps.h"

/// @brief Calculates the cross product of two `t_vec4s`
///        (ignoring the `w` component) and stores the result
///        in the vector pointed-to by `out`.
/// @param in1, in2 operand
/// @param out Pointer to the vector that stores the result.
static inline void	lag_vec4s_cross(t_vec4s *out, const t_vec4s in1,
						const t_vec4s in2)
{
	const __m128	a_yzx = \
					_mm_shuffle_ps(in1.simd, in1.simd, _MM_SHUFFLE(3, 0, 2, 1));
	const __m128	b_yzx = \
					_mm_shuffle_ps(in2.simd, in2.simd, _MM_SHUFFLE(3, 0, 2, 1));
	const __m128	a_zxy = \
					_mm_shuffle_ps(in1.simd, in1.simd, _MM_SHUFFLE(3, 1, 0, 2));
	const __m128	b_zxy = \
					_mm_shuffle_ps(in2.simd, in2.simd, _MM_SHUFFLE(3, 1, 0, 2));
	out->simd = _mm_sub_ps(\
		_mm_mul_ps(a_yzx, b_zxy), \
		_mm_mul_ps(a_zxy, b_yzx) \
	);
}

/// @brief Calculates the cross product of two `t_vec4s`
///        (ignoring the w component).
static inline t_vec4s	lag_vec4s_cross_ret(const t_vec4s in1,
						const t_vec4s in2)
{
	const __m128	a_yzx = \
					_mm_shuffle_ps(in1.simd, in1.simd, _MM_SHUFFLE(3, 0, 2, 1));
	const __m128	b_yzx = \
					_mm_shuffle_ps(in2.simd, in2.simd, _MM_SHUFFLE(3, 0, 2, 1));
	const __m128	a_zxy = \
					_mm_shuffle_ps(in1.simd, in1.simd, _MM_SHUFFLE(3, 1, 0, 2));
	const __m128	b_zxy = \
					_mm_shuffle_ps(in2.simd, in2.simd, _MM_SHUFFLE(3, 1, 0, 2));
	return ((t_vec4s)
		{
			.simd = _mm_sub_ps(\
				_mm_mul_ps(a_yzx, b_zxy), \
				_mm_mul_ps(a_zxy, b_yzx) \
			)
		});
}

#endif // !SIMPLE_OPEARTIONS_4_PS_H