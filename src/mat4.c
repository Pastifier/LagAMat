/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:51:29 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/16 12:28:08 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lavx.h"

// Nobody likes loops.
static inline void	unrolled_cross(const t_mat4d *in, const __m256d col[4],
						t_mat4d *out)
{
	out->r1.x = lag_dot_product_avx(in->r1.simd, col[0]);
	out->r1.y = lag_dot_product_avx(in->r1.simd, col[1]);
	out->r1.z = lag_dot_product_avx(in->r1.simd, col[2]);
	out->r1.w = lag_dot_product_avx(in->r1.simd, col[3]);
	out->r2.x = lag_dot_product_avx(in->r2.simd, col[0]);
	out->r2.y = lag_dot_product_avx(in->r2.simd, col[1]);
	out->r2.z = lag_dot_product_avx(in->r2.simd, col[2]);
	out->r2.w = lag_dot_product_avx(in->r2.simd, col[3]);
	out->r3.x = lag_dot_product_avx(in->r3.simd, col[0]);
	out->r3.y = lag_dot_product_avx(in->r3.simd, col[1]);
	out->r3.z = lag_dot_product_avx(in->r3.simd, col[2]);
	out->r3.w = lag_dot_product_avx(in->r3.simd, col[3]);
	out->r4.x = lag_dot_product_avx(in->r4.simd, col[0]);
	out->r4.y = lag_dot_product_avx(in->r4.simd, col[1]);
	out->r4.z = lag_dot_product_avx(in->r4.simd, col[2]);
	out->r4.w = lag_dot_product_avx(in->r4.simd, col[3]);
}

void	lag_mat4_cross(const t_mat4d *in, const t_mat4d *in2, t_mat4d *out)
{
	__m256d	col[4];

	lag_extract_column4_avx(in2, 0, &col[0]);
	lag_extract_column4_avx(in2, 1, &col[1]);
	lag_extract_column4_avx(in2, 2, &col[2]);
	lag_extract_column4_avx(in2, 3, &col[3]);
	unrolled_cross(in, col, out);
}
