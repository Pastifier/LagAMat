/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_operations_3.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:15:53 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/19 02:50:43 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLE_OPERATIONS_3_H
# define SIMPLE_OPERATIONS_3_H

# include "simple_operations_2.h"
# include <math.h>

typedef __attribute((aligned(32))) double	t_vec4d4[4];

/// @brief Calculates the dot product of two `t_vec4d`, and stores the result
///        in the variable pointed-to by `out`.
/// @param out Pointer to the variable that stores the result.
/// @param in1 Vector to calculate the dot product of
/// @param in2 Vector to calculate the dot product of
static inline void	lag_vec4d_dot(double *out, const t_vec4d in1,
						const t_vec4d in2)
{
	t_vec4d4		result;
	const __m256d	product = _mm256_mul_pd(in1.simd, in2.simd);

	_mm256_store_pd(result, _mm256_hadd_pd(product, product));
	*out = result[0] + result[2];
}

/// @brief Calculates the dot product of two `t_vec4d`.
static inline double	lag_vec4d_dot_ret(const t_vec4d in1,
							const t_vec4d in2)
{
	t_vec4d4		result;
	const __m256d	product = _mm256_mul_pd(in1.simd, in2.simd);

	_mm256_store_pd(result, (_mm256_hadd_pd(product, product)));
	return (result[0] + result[2]);
}

/// @brief Calculates the magnitude of a `t_vec4d` and stores the result
///        in the variable pointed-to by `out`.
/// @param in Vector to calculate the magnitude of
/// @param out Pointer to the variable that stores the result.
static inline void	lag_vec4d_magnitude(double *out, const t_vec4d in)
{
	lag_vec4d_dot(out, in, in);
	*out = sqrt(*out);
}

/// @brief Calculates the magnitude of a `t_vec4d`.
static inline double	lag_vec4d_magnitude_ret(const t_vec4d in)
{
	return (sqrt(lag_vec4d_dot_ret(in, in)));
}

#endif // !SIMPLE_OPERATIONS_3_H
