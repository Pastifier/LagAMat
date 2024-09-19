/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_operations_2_ps.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 23:24:33 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/18 23:27:37 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLE_OPERATIONS_2_PS_H
# define SIMPLE_OPERATIONS_2_PS_H

# include "simple_operations_1_ps.h"

/// @brief Scales a vector by a scalar and stores the result in the vector
///        pointed-to by `out`.
/// @param in Vector to be scaled
/// @param scalar Scalar to scale the vector by
static inline void	lag_vec4s_scaleby(t_vec4s *out, const t_vec4s in,
						float scalar)
{
	out->simd = _mm_mul_ps(in.simd, _mm_set1_ps(scalar));
}

/// @brief Scales a vector by a scalar.
///        This is to be used when performance is not a concern
///        (i.e. modern compilers, single-usage, etc...),
///        or when function-chaining is desired.
static inline t_vec4s	lag_vec4s_scaleby_ret(const t_vec4s in, float scalar)
{
	return ((t_vec4s)
		{
			.simd = _mm_mul_ps(in.simd, _mm_set1_ps(scalar))
		});
}

/// @brief Negates a vector and stores the result
///        in the vector pointed-to by `out`.
/// @param in Vector to be negated
/// @param out Pointer to the vector that stores the result.
static inline void	lag_vec4s_negate_new(t_vec4s *out, const t_vec4s in)
{
	out->simd = _mm_sub_ps(_mm_set1_ps(0.0f), in.simd);
}

/// @brief Negates a vector in place.
/// @param target Pointer to vector to be negated
static inline void	lag_vec4s_negate(t_vec4s *target)
{
	target->simd = _mm_sub_ps(_mm_set1_ps(0.0f), target->simd);
}

/// @brief Negates a vector.
///        This is to be used when performance is not a concern
///        (i.e. modern compilers, single-usage, etc...),
///        or when function-chaining is desired.
static inline t_vec4s	lag_vec4s_negate_ret(const t_vec4s in)
{
	return ((t_vec4s)
		{
			.simd = _mm_sub_ps(_mm_set1_ps(0.0f), in.simd)
		});
}

#endif // !SIMPLE_OPERATIONS_2_PS_H