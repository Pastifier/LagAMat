/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4s_init.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 07:03:08 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/20 13:19:57 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT4S_INIT
# define MAT4S_INIT

# include "mat4s_init_rot.h"

/// @brief Returns a `t_mat4s` using the parameters as its rows.
static inline t_mat4s	lag_mat4s_rows_ret(const t_vec4s r1, const t_vec4s r2,
						const t_vec4s r3, const t_vec4s r4)
{
	return ((t_mat4s)
		{
			.r1 = r1,
			.r2 = r2,
			.r3 = r3,
			.r4 = r4
		});
}

/// @brief Returns a `t_mat4s` identity matrix.
static inline t_mat4s	lag_mat4s_identity(void)
{
	return ((t_mat4s)
		{
			.r1.simd = _mm_set_ps(0.f, 0.f, 0.f, 1.f),
			.r2.simd = _mm_set_ps(0.f, 0.f, 1.f, 0.f),
			.r3.simd = _mm_set_ps(0.f, 1.f, 0.f, 0.f),
			.r4.simd = _mm_set_ps(1.f, 0.f, 0.f, 0.f)
		});
}

/// @brief Returns a `t_mat4s` affine translation-matrix
///        (`r4 = {0, 0, 0, 1}`).
static inline t_mat4s	lag_mat4s_translation(float tx, float ty, float tz)
{
	return ((t_mat4s)
		{
			.r1.simd = _mm_set_ps(tx, 0.f, 0.f, 1.f),
			.r2.simd = _mm_set_ps(ty, 0.f, 1.f, 0.f),
			.r3.simd = _mm_set_ps(tz, 1.f, 0.f, 0.f),
			.r4.simd = _mm_set_ps(1.f, 0.f, 0.f, 0.f)
		});
}

/// @brief Returns a `t_mat4s` affine scaling-matrix.
///        (`r4 = {0, 0, 0, 1}`).
static inline t_mat4s	lag_mat4s_scaling(float sx, float sy, float sz)
{
	return ((t_mat4s)
		{
			.r1.simd = _mm_set_ps(0.f, 0.f, 0.f, sx),
			.r2.simd = _mm_set_ps(0.f, 0.f, sy, 0.f),
			.r3.simd = _mm_set_ps(0.f, sz, 0.f, 0.f),
			.r4.simd = _mm_set_ps(1.f, 0.f, 0.f, 0.f)
		});
}

#endif // !MAT4S_INIT
