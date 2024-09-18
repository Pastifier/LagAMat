/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_linear_algebra.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:58:47 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/18 06:09:52 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC4_LINEAR_ALGEBRA_H
# define VEC4_LINEAR_ALGEBRA_H

# include "simple_operations_4.h"

/// @brief Checks equality of `a` and `b` within a set `tolerance`.
///        `__DBL_EPSILON__` highly recommended, unless you know what you're
///        doing.
/// @param a `t_vec4d` vector
/// @param b `t_vec4d` vector
/// @param tolerance Desired tolerance.
/// @return `true (1)` or `false (0)`, depending on the comparison result.
/// @warning If either of the values entered contain `NaN`, the result
///          will be `false (0)`.
static inline bool	lag_vec4d_eq(const t_vec4d a, const t_vec4d b, double tolerance)
{
	__m256d			abs_diff;
	__m256d			load_tol;
	__m256d			cmp;
	const __m256d	sign_mask = _mm256_set1_pd(-0.0);
	int				mask;

	abs_diff = _mm256_andnot_pd(\
				sign_mask, \
				_mm256_sub_pd(a.simd, b.simd) \
			);
	load_tol = _mm256_set1_pd(tolerance);
	cmp = _mm256_cmp_pd(\
				abs_diff, \
				load_tol, \
				_CMP_LT_OQ \
			);
	mask = _mm256_movemask_pd(cmp);
	return (mask == 0xF);
}

/// @brief Checks EXACT equality of `a` and `b`. Use wisely.
/// @param a `t_vec4d` vector
/// @param b `t_vec4d` vector
/// @return `true (1)` or `false (0)`, depending on the comparison result.
/// @warning If either of the values entered contain `NaN`, the result
///          will be `false (0)`.
static inline bool	lag_vec4d_exacteq(const t_vec4d a, const t_vec4d b)
{
	int	mask;

	mask = _mm256_movemask_pd(_mm256_cmp_pd(a.simd, b.simd, _CMP_EQ_OQ));
	return (mask == 0xF);
}

#endif // !VEC4_LINEAR_ALGEBRA_H