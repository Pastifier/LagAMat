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
	t_mat4s	ret;

	ret.r1.simd = _mm_set_ps(0.f, 0.f, 0.f, 1.f);
	ret.r2.simd = _mm_set_ps(0.f, -sin(rad), cos(rad), 0.f);
	ret.r3.simd = _mm_set_ps(0.f, cos(rad), sin(rad), 0.f);
	ret.r4.simd = _mm_set_ps(1.f, 0.f, 0.f, 0.f);
	return (ret);
}

/// @brief Returns a rotation matrix around the y-axis.
/// @param rad Rotation in radians
static inline t_mat4s	lag_mat4s_rotation_y(float rad)
{
	t_mat4s	ret;


	ret.r1.simd = _mm_set_ps(0.f, sin(rad), 0.f, cos(rad));
	ret.r2.simd = _mm_set_ps(0.f, 0.f, 1.f, 0.f);
	ret.r3.simd = _mm_set_ps(0.f, cos(rad), 0.f, -sin(rad));
	ret.r4.simd = _mm_set_ps(1.f, 0.f, 0.f, 0.f);
	return (ret);
}

/// @brief Returns a rotation matrix around the z-axis.
/// @param rad Rotation in radians
static inline t_mat4s	lag_mat4s_rotation_z(float rad)
{
	t_mat4s	ret;
	
	ret.r1.simd = _mm_set_ps(0.f, 0.f, -sin(rad), cos(rad));
	ret.r2.simd = _mm_set_ps(0.f, 0.f, cos(rad), sin(rad));
	ret.r3.simd = _mm_set_ps(0.f, 1.f, 0.f, 0.f);
	ret.r4.simd = _mm_set_ps(1.f, 0.f, 0.f, 0.f);
	return (ret);
}

#endif // !MAT4S_INIT_ROT_H
