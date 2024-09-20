/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4s_init_rot.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:08:59 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/20 14:34:47 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT4S_INIT_ROT_H
# define MAT4S_INIT_ROT_H

# include "ltypes.h"
# include "math.h" // for trig functions

/// @brief Returns a rotation matrix around the x-axis.
/// @param rad Rotation in radians
static inline t_mat4s	lag_mat4s_rotation_x(float rad)
{
	return ((t_mat4s)
		{
			.r1.simd = _mm_set_ps(0.f, 0.f, 0.f, 1.f),
			.r2.simd = _mm_set_ps(0.f, -sin(rad), cos(rad), 0.f),
			.r3.simd = _mm_set_ps(0.f, cos(rad), sin(rad), 0.f),
			.r4.simd = _mm_set_ps(1.f, 0.f, 0.f, 0.f)
		});
}

/// @brief Returns a rotation matrix around the y-axis.
/// @param rad Rotation in radians
static inline t_mat4s	lag_mat4s_rotation_y(float rad)
{
	return ((t_mat4s)
		{
			.r1.simd = _mm_set_ps(0.f, sin(rad), 0.f, cos(rad)),
			.r2.simd = _mm_set_ps(0.f, 0.f, 1.f, 0.f),
			.r3.simd = _mm_set_ps(0.f, cos(rad), 0.f, -sin(rad)),
			.r4.simd = _mm_set_ps(1.f, 0.f, 0.f, 0.f)
		});
}

/// @brief Returns a rotation matrix around the z-axis.
/// @param rad Rotation in radians
static inline t_mat4s	lag_mat4s_rotation_z(float rad)
{
	return ((t_mat4s)
		{
			.r1.simd = _mm_set_ps(0.f, 0.f, -sin(rad), cos(rad)),
			.r2.simd = _mm_set_ps(0.f, 0.f, cos(rad), sin(rad)),
			.r3.simd = _mm_set_ps(0.f, 1.f, 0.f, 0.f),
			.r4.simd = _mm_set_ps(1.f, 0.f, 0.f, 0.f)
		});
}

#endif // !MAT4S_INIT_ROT_H
