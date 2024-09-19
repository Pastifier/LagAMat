/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_linear_algebra.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:58:47 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/18 21:26:01by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC4_LINEAR_ALGEBRA_H
# define VEC4_LINEAR_ALGEBRA_H

# include "./init.h"
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
static inline bool	lag_vec4d_eq(const t_vec4d a, const t_vec4d b,
						double tolerance)
{
	const __m256d	sign_mask = _mm256_set1_pd(-0.0);
	const __m256d	abs_diff = _mm256_andnot_pd(\
						sign_mask, \
						_mm256_sub_pd(a.simd, b.simd) \
					);
	const __m256d	load_tol = _mm256_set1_pd(tolerance);
	const __m256d	cmp = _mm256_cmp_pd(\
						abs_diff, \
						load_tol, \
						_CMP_LT_OQ \
					);
	const int	mask = _mm256_movemask_pd(cmp);

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
	const int	mask = _mm256_movemask_pd(\
							_mm256_cmp_pd(a.simd, b.simd, _CMP_EQ_OQ) \
						);

	return (mask == 0xF);
}

/// @brief Normalizes a `t_vec4d` in place.
/// @param target Pointer to `t_vec4d` to be normalized
static inline void	lag_vec4d_normalize(t_vec4d *target)
{
	double	mag;

	lag_vec4d_magnitude(&mag, *target);
	if (mag == 0.0)
		*target = (t_vec4d){0};
	else
		lag_vec4d_scaleby(target, *target, 1.0 / mag);
}

/// @brief Returns a normalized version of the `t_vec4d`: `in`.
/// @param in `t_vec4d` to be normalized.
static inline t_vec4d	lag_vec4d_normalize_ret(const t_vec4d in)
{
	double	mag;

	lag_vec4d_magnitude(&mag, in);
	if (mag == 0.0)
		return (lag_vec4d_scaleby_ret(in, 0.0));
	return (lag_vec4d_scaleby_ret(in, 1.0 / mag));
}

/// @brief Normalizes a `t_vec4d` and stores the result
///        in the `t_vec4d` pointed-to by `out`.
/// @param out Pointer to the `t_vec4d` that stores the result.
/// @param in `t_vec4d` to be normalized.
static inline void	lag_vec4d_normalize_new(t_vec4d *out, const t_vec4d in)
{
	double	mag;

	lag_vec4d_magnitude(&mag, in);
	if (mag == 0.0)
		lag_vec4d_scaleby(out, in, 0.0);
	else
		lag_vec4d_scaleby(out, in, 1.0 / mag);
}

#endif // !VEC4_LINEAR_ALGEBRA_H
