/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lavx.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:35:07 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/16 12:30:58 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAVX_H
# define LAVX_H

# include "ltypes.h"

static inline double	lag_dot_product_avx(const __m256d in, const __m256d in2)
{
	double			result[4];
	const __m256d	mul = _mm256_mul_pd(in, in2);

	_mm256_storeu_pd(result, _mm256_hadd_pd(mul, mul));
	return (result[0] + result[2]);
}

static inline void	lag_extract_column4_avx(const t_mat4d *in, const short c,
						__m256d *out)
{
	*out = _mm256_set_pd(in->a[3][c], in->a[2][c], in->a[1][c], in->a[0][c]);
}

#endif // !LAVX_H