/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_operations_4.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:21:01 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/19 04:14:27 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLE_OPERATIONS_4_H
# define SIMPLE_OPERATIONS_4_H

# include "simple_operations_3.h"

/// @brief Calculates the cross product of two `t_vec4d`
///        (ignoring the w component) and stores the result
///        in the vector pointed-to by `out`.
/// @param in1, in2 operand
/// @param out Pointer to the vector that stores the result.
static inline void	lag_vec4d_cross(t_vec4d *out, const t_vec4d in1,
						const t_vec4d in2)
{
	const __m256d	a_yzx = \
					_mm256_permute4x64_pd(in1.simd, _MM_SHUFFLE(3, 0, 2, 1));
	const __m256d	b_yzx = \
					_mm256_permute4x64_pd(in2.simd, _MM_SHUFFLE(3, 0, 2, 1));
	const __m256d	a_zxy = \
					_mm256_permute4x64_pd(in1.simd, _MM_SHUFFLE(3, 1, 0, 2));
	const __m256d	b_zxy = \
					_mm256_permute4x64_pd(in2.simd, _MM_SHUFFLE(3, 1, 0, 2));

	out->simd = _mm256_sub_pd(\
		_mm256_mul_pd(a_yzx, b_zxy), \
		_mm256_mul_pd(a_zxy, b_yzx) \
	);
}

/// @brief Calculates the cross product of two `t_vec4d`
///        (ignoring the w component).
static inline t_vec4d	lag_vec4d_cross_ret(const t_vec4d in1,
							const t_vec4d in2)
{
	const __m256d	a_yzx = \
					_mm256_permute4x64_pd(in1.simd, _MM_SHUFFLE(3, 0, 2, 1));
	const __m256d	b_yzx = \
					_mm256_permute4x64_pd(in2.simd, _MM_SHUFFLE(3, 0, 2, 1));
	const __m256d	a_zxy = \
					_mm256_permute4x64_pd(in1.simd, _MM_SHUFFLE(3, 1, 0, 2));
	const __m256d	b_zxy = \
					_mm256_permute4x64_pd(in2.simd, _MM_SHUFFLE(3, 1, 0, 2));

	return ((t_vec4d)
		{
			.simd = _mm256_sub_pd(\
				_mm256_mul_pd(a_yzx, b_zxy), \
				_mm256_mul_pd(a_zxy, b_yzx) \
			)
		});
}

#endif // !SIMPLE_OPERATIONS_4_H