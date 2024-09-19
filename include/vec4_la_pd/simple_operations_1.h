/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_operations_1.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 04:55:47 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/18 23:21:57 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLE_OPERATIONS_1_H
# define SIMPLE_OPERATIONS_1_H

# include "ltypes.h"

/// @brief Performs component-wise (vector) addition and stores the result
///        in the vector pointed-to by `out`.
/// @param in1, in2 operand
/// @param out Pointer to the vector that stores the result.
static inline void	lag_vec4d_add(t_vec4d *out, const t_vec4d in1,
						const t_vec4d in2)
{
	out->simd = _mm256_add_pd(in1.simd, in2.simd);
}

/// @brief Performs component-wise (vector) addition.
static inline t_vec4d	lag_vec4d_add_ret(const t_vec4d in1, const t_vec4d in2)
{
	return ((t_vec4d)
		{
			.simd = _mm256_add_pd(in1.simd, in2.simd)
		});
}

/// @brief Performs component-wise (vector) subtraction and stores the result
///        in the vector pointed-to by `out`.
/// @param in1, in2 operand
/// @param out Pointer to the vector that stores the result.
static inline void	lag_vec4d_sub(t_vec4d *out, const t_vec4d in1,
						const t_vec4d in2)
{
	out->simd = _mm256_sub_pd(in1.simd, in2.simd);
}

/// @brief Performs component-wise (vector) subtraction.
static inline t_vec4d	lag_vec4d_sub_ret(const t_vec4d in1, const t_vec4d in2)
{
	return ((t_vec4d)
		{
			.simd = _mm256_sub_pd(in1.simd, in2.simd)
		});
}

#endif // !SIMPLE_OPERATIONS_1_H
