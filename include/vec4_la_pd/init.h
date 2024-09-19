/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 02:19:02 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/18 22:25:38 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "ltypes.h"

/// @brief Returns a `t_vec4d` with components (x, y, z, w)
static inline t_vec4d	lag_vec4d_ret(double x, double y, double z, double w)
{
	return ((t_vec4d)
		{
			.simd = _mm256_set_pd(w, z, y, x)
		});
}

/// @brief Initialises a `t_vec4d` in homogenous coordinates with a w of `1`
static inline void	lag_vec4dp_init(t_vec4d *target, double x, double y,
						double z)
{
	target->simd = _mm256_set_pd(1.0, z, y, x);
}

/// @brief Returns a `t_vec4d` in homogenous coordinates with a w of `1`
static inline t_vec4d	lag_vec4dp_ret(double x, double y, double z)
{
	return ((t_vec4d)
		{
			.simd = _mm256_set_pd(1.0, z, y, x)
		});
}

/// @brief Initialises a `t_vec4d` in homogenous coordinates with a w of `0`
static inline void	lag_vec4dv_init(t_vec4d *target, double x, double y,
						double z)
{
	target->simd = _mm256_set_pd(0.0, z, y, x);
}

/// @brief Returns a `t_vec4d` in homogenous coordinates with a w of `0`
static inline t_vec4d	lag_vec4dv_ret(double x, double y, double z)
{
	return ((t_vec4d)
		{
			.simd = _mm256_set_pd(0.0, z, y, x)
		});
}

#endif // !INIT_H