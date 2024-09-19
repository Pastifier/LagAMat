/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ps.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 22:13:08 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/18 23:20:24 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_PS_H
# define INIT_PS_H

# include "ltypes.h"

/// @brief Returns a `t_vec4s` with components (x, y, z, w)
static inline t_vec4s	lag_vec4s_ret(float x, float y, float z, float w)
{
	return ((t_vec4s)
		{
			.simd = _mm_set_ps(w, z, y, x)
		});
}

/// @brief Initialises a `t_vec4s` in homogenous coordinates with a w of `1`
static inline void	lag_vec4sp_init(t_vec4s *target, float x, float y,
						float z)
{
	target->simd = _mm_set_ps(1.0, z, y, x);
}

/// @brief Returns a `t_vec4s` in homogenous coordinates with a w of `1`
static inline t_vec4s	lag_vec4sp_ret(float x, float y, float z)
{
	return ((t_vec4s)
		{
			.simd = _mm_set_ps(1.0, z, y, x)
		});
}

/// @brief Initialises a `t_vec4s` in homogenous coordinates with a w of `0`
static inline void	lag_vec4sv_init(t_vec4s *target, float x, float y,
						float z)
{
	target->simd = _mm_set_ps(0.0, z, y, x);
}

/// @brief Returns a `t_vec4s` in homogenous coordinates with a w of `0`
static inline t_vec4s	lag_vec4sv_ret(float x, float y, float z)
{
	return ((t_vec4s)
		{
			.simd = _mm_set_ps(0.0, z, y, x)
		});
}


#endif // !INIT_PS_H