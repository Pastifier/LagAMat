/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_operations_2.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:14:32 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/16 11:46:03 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLE_OPERATIONS_2_H
# define SIMPLE_OPERATIONS_2_H

# include "simple_operations_1.h"

/// @brief Scales a vector by a scalar and stores the result in the vector
///        pointed-to by `out`.
/// @param in Vector to be scaled
/// @param scalar Scalar to scale the vector by
static inline void	lag_vec4d_scaleby(t_vec4d *out, const t_vec4d in,
						double scalar)
{
	out->simd = _mm256_mul_pd(in.simd, _mm256_set1_pd(scalar));
}

/// @brief Scales a vector by a scalar.
///        This is to be used when performance is not a concern
///        (i.e. modern compilers, single-usage, etc...),
///        or when function-chaining is desired.
static inline t_vec4d	lag_vec4d_scaleby_ret(const t_vec4d in, double scalar)
{
	return ((t_vec4d)
		{
			.simd = _mm256_mul_pd(in.simd, _mm256_set1_pd(scalar))
		});
}

/// @brief Negates a vector and stores the result
///        in the vector pointed-to by `out`.
/// @param in Vector to be negated
/// @param out Pointer to the vector that stores the result.
static inline void	lag_vec4d_negate_new(t_vec4d *out, const t_vec4d in)
{
	out->simd = _mm256_sub_pd(_mm256_set1_pd(0.0), in.simd);
}

/// @brief Negates a vector in place.
/// @param target Pointer to vector to be negated
static inline void	lag_vec4d_negate(t_vec4d *target)
{
	target->simd = _mm256_sub_pd(_mm256_set1_pd(0.0), target->simd);
}

/// @brief Negates a vector.
///        This is to be used when performance is not a concern
///        (i.e. modern compilers, single-usage, etc...),
///        or when function-chaining is desired.
static inline t_vec4d	lag_vec4d_negate_ret(const t_vec4d in)
{
	return ((t_vec4d)
		{
			.simd = _mm256_sub_pd(_mm256_set1_pd(0.0), in.simd)
		});
}

#endif // !SIMPLE_OPERATIONS_2_H
