/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4s_inverse_utils.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 04:43:47 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/28 09:38:15 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT4S_INVERSE_UTILS_H
# define MAT4S_INVERSE_UTILS_H

# include "ltypes.h"

// 2x2 row-major Matrix multiply A * B
static inline __m128 mat2mul(const __m128 m1, const __m128 m2)
{
	return _mm_add_ps(
		_mm_mul_ps(m1, _mm_shuffle_ps(m2, m2, _MM_SHUFFLE(0, 3, 0, 3))),
		_mm_mul_ps(_mm_shuffle_ps(m1, m1, _MM_SHUFFLE(1, 0, 3, 2)),
		           _mm_shuffle_ps(m2, m2, _MM_SHUFFLE(2, 1, 2, 1))));
}

// 2x2 row-major Matrix adjugate multiply (A#) * B
static inline __m128 mat2_adjmul(const __m128 m1, const __m128 m2)
{
	return _mm_sub_ps(
		_mm_mul_ps(_mm_shuffle_ps(m1, m1, _MM_SHUFFLE(3, 3, 0, 0)), m2),
		_mm_mul_ps(_mm_shuffle_ps(m1, m1, _MM_SHUFFLE(1, 1, 2, 2)),
		           _mm_shuffle_ps(m2, m2, _MM_SHUFFLE(2, 3, 0, 1))));
}

// 2x2 row-major Matrix multiply adjugate A * (B#)
static inline __m128 mat2_muladj(const __m128 m1, const __m128 m2)
{
	return _mm_sub_ps(
		_mm_mul_ps(m1, _mm_shuffle_ps(m2, m2, _MM_SHUFFLE(3, 0, 3, 0))),
		_mm_mul_ps(_mm_shuffle_ps(m1, m1, _MM_SHUFFLE(1, 0, 3, 2)),
		           _mm_shuffle_ps(m2, m2, _MM_SHUFFLE(2, 1, 2, 1))));
}

/*
https://
lxjk.github.io/2017/09/03/Fast-4x4-Matrix-Inverse-with-SSE-SIMD-Explained.html
*/

#endif // !MAT4S_INVERSE_UTILS_H