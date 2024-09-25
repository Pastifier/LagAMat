/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4s_cross.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:36:15 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/20 19:27:13 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT4S_CROSS_H
# define MAT4S_CROSS_H

# include "ltypes.h"

/// @brief Returns the cross product of a `t_mat4s` with a `t_vec4s`
///        (in that order).
static inline t_vec4s	lag_mat4s_cross_vec4s(const t_mat4s m,
							const t_vec4s v)
{
	__m128			col[4];
	__m128			mul[4];
	__m128			add[2];
	const __m128	*rows_m = (const __m128 *)&m.r1.simd;

	col[0] = _mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(0, 0, 0, 0));
	col[1] = _mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(1, 1, 1, 1));
	col[2] = _mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(2, 2, 2, 2));
	col[3] = _mm_shuffle_ps(v.simd, v.simd, _MM_SHUFFLE(3, 3, 3, 3));
	mul[0] = _mm_mul_ps(rows_m[0], col[0]);
	mul[1] = _mm_mul_ps(rows_m[1], col[1]);
	mul[2] = _mm_mul_ps(rows_m[2], col[2]);
	mul[3] = _mm_mul_ps(rows_m[3], col[3]);
	add[0] = _mm_add_ps(mul[0], mul[1]);
	add[1] = _mm_add_ps(mul[2], mul[3]);
	return ((t_vec4s)
		{
			.simd = _mm_add_ps(add[0], add[1])
		});
}

#define PRINT_VECTOR(v) printf("%f, %f, %f, %f\n", v.x, v.y, v.z, v.w)

static inline __m128	compute_row(const __m128 *in1, const __m128 *in2,
							int r)
{
	__m128	col[4];
	__m128	mul[4];
	__m128	add[2];

	col[0] = _mm_shuffle_ps(in2[r], in2[r], _MM_SHUFFLE(0, 0, 0, 0));
	col[1] = _mm_shuffle_ps(in2[r], in2[r], _MM_SHUFFLE(1, 1, 1, 1));
	col[2] = _mm_shuffle_ps(in2[r], in2[r], _MM_SHUFFLE(2, 2, 2, 2));
	col[3] = _mm_shuffle_ps(in2[r], in2[r], _MM_SHUFFLE(3, 3, 3, 3));
	mul[0] = _mm_mul_ps(in1[0], col[0]);
	mul[1] = _mm_mul_ps(in1[1], col[1]);
	mul[2] = _mm_mul_ps(in1[2], col[2]);
	mul[3] = _mm_mul_ps(in1[3], col[3]);
	add[0] = _mm_add_ps(mul[0], mul[1]);
	add[1] = _mm_add_ps(mul[2], mul[3]);
	return (_mm_add_ps(add[0], add[1]));
}

/// @brief computes the cross product of `in1` with `in2`
///        (in that order), and stores the result in the `t_mat4s`
///        pointed-to by `out`.
static inline void	lag_mat4s_cross_mat4s(const t_mat4s in1,
							const t_mat4s in2, t_mat4s *out)
{
	const __m128	*in1_rows = &(in1.r1.simd);
	const __m128	*in2_rows = &(in2.r1.simd);
	__m128			*out_rows;

	out_rows = &(out->r1.simd);
	out_rows[0] = compute_row(in1_rows, in2_rows, 0);
	out_rows[1] = compute_row(in1_rows, in2_rows, 1);
	out_rows[2] = compute_row(in1_rows, in2_rows, 2);
	out_rows[3] = compute_row(in1_rows, in2_rows, 3);
}

#endif // !MAT4S_CROSS_H
