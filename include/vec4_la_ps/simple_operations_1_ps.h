/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_operations_1_ps.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 22:57:10 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/18 23:22:07 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLE_OPERATIONS_1_PS_H
# define SIMPLE_OPERATIONS_1_PS_H

# include "ltypes.h"

/// @brief Performs component-wise (vector) addition and stores the result
///        in the vector pointed-to by `out`.
/// @param in1, in2 operand
/// @param out Pointer to the vector that stores the result.
static inline void	lag_vec4s_add(t_vec4s *out, const t_vec4s in1,
						const t_vec4s in2)
{
	out->simd = _mm_add_ps(in1.simd, in2.simd);
}

/// @brief Performs component-wise (vector) addition.
static inline t_vec4s	lag_vec4s_add_ret(const t_vec4s in1, const t_vec4s in2)
{
	return ((t_vec4s)
		{
			.simd = _mm_add_ps(in1.simd, in2.simd)
		});
}

/// @brief Performs component-wise (vector) subtraction and stores the result
///        in the vector pointed-to by `out`.
/// @param in1, in2 operand
/// @param out Pointer to the vector that stores the result.
static inline void	lag_vec4s_sub(t_vec4s *out, const t_vec4s in1,
						const t_vec4s in2)
{
	out->simd = _mm_sub_ps(in1.simd, in2.simd);
}

/// @brief Performs component-wise (vector) subtraction.
static inline t_vec4s	lag_vec4s_sub_ret(const t_vec4s in1, const t_vec4s in2)
{
	return ((t_vec4s)
		{
			.simd = _mm_sub_ps(in1.simd, in2.simd)
		});
}

#endif // !SIMPLE_OPERATIONS_1_PS_H
