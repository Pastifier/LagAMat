/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4s_inverse.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 04:41:45 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/28 09:41:14 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT4S_INVERSE_H
# define MAT4S_INVERSE_H

# include "ltypes.h"
# include "./mat4s_inverse_utils.h"

static inline t_mat4s	lag_mat4s_inverse(const t_mat4s in)
{
	const __m128	adj_signmask = _mm_setr_ps(1.f, -1.f, -1.f, 1.f);
	__m128			shuff[4];
	__m128			det2sub;
	__m128			det2[4];
	__m128			d_c;
	__m128			a_b;
	__m128			r_[4];
	__m128			det_m;
	__m128			tr2;
	__m128			rcp_det_m;
	t_mat4s			res;
	
	shuff[0] = _mm_shuffle_ps(in.simd[0], in.simd[1], _MM_SHUFFLE(0, 1, 0, 1));
	shuff[1] = _mm_shuffle_ps(in.simd[0], in.simd[1], _MM_SHUFFLE(2, 3, 2, 3));
	shuff[2] = _mm_shuffle_ps(in.simd[2], in.simd[3], _MM_SHUFFLE(0, 1, 0, 1));
	shuff[3] = _mm_shuffle_ps(in.simd[2], in.simd[3], _MM_SHUFFLE(2, 3, 2, 3));
	det2sub = _mm_sub_ps(\
		_mm_mul_ps(\
			_mm_shuffle_ps(in.simd[0], in.simd[1], _MM_SHUFFLE(0, 2, 0, 2)), \
			_mm_shuffle_ps(in.simd[1], in.simd[3], _MM_SHUFFLE(1, 3, 1, 3)) \
		), \
		_mm_mul_ps(\
			_mm_shuffle_ps(in.simd[0], in.simd[2], _MM_SHUFFLE(1, 3, 1, 3)), \
			_mm_shuffle_ps(in.simd[1], in.simd[3], _MM_SHUFFLE(0, 2, 0, 2)) \
		) \
	);
	det2[0] = _mm_shuffle_ps(det2sub, det2sub, _MM_SHUFFLE(0, 0, 0, 0));
	det2[1] = _mm_shuffle_ps(det2sub, det2sub, _MM_SHUFFLE(1, 1, 1, 1));
	det2[2] = _mm_shuffle_ps(det2sub, det2sub, _MM_SHUFFLE(2, 2, 2, 2));
	det2[3] = _mm_shuffle_ps(det2sub, det2sub, _MM_SHUFFLE(3, 3, 3, 3));
	d_c = mat2_adjmul(shuff[3], shuff[2]);
	a_b = mat2_adjmul(shuff[0], shuff[1]);
	r_[0] = _mm_sub_ps(_mm_mul_ps(det2[3], shuff[0]), mat2mul(shuff[1], d_c));
	r_[3] = _mm_sub_ps(_mm_mul_ps(det2[0], shuff[3]), mat2mul(shuff[2], a_b));
	det_m = _mm_mul_ps(det2[0], det2[3]);
	r_[1] = _mm_sub_ps(\
		_mm_mul_ps(det2[1], shuff[2]), \
		mat2_muladj(shuff[3], a_b) \
	);
	r_[2] = _mm_sub_ps(\
		_mm_mul_ps(det2[2], shuff[1]), \
		mat2_muladj(shuff[0], d_c) \
	);
	det_m = _mm_add_ps(det_m, _mm_mul_ps(det2[1], det2[3]));
	tr2 = _mm_mul_ps(a_b, _mm_shuffle_ps(d_c, d_c, _MM_SHUFFLE(0, 2, 1, 3)));
	tr2 = _mm_hadd_ps(tr2, tr2);
	tr2 = _mm_hadd_ps(tr2, tr2);
	det_m = _mm_sub_ps(det_m, tr2);
	rcp_det_m = _mm_div_ps(adj_signmask, det_m);
	r_[0] = _mm_mul_ps(r_[0], rcp_det_m);
	r_[1] = _mm_mul_ps(r_[1], rcp_det_m);
	r_[2] = _mm_mul_ps(r_[2], rcp_det_m);
	r_[3] = _mm_mul_ps(r_[3], rcp_det_m);
	res.simd[0] = _mm_shuffle_ps(r_[0], r_[1], _MM_SHUFFLE(3, 1, 3, 1));
	res.simd[1] = _mm_shuffle_ps(r_[0], r_[1], _MM_SHUFFLE(2, 0, 2, 0));
	res.simd[2] = _mm_shuffle_ps(r_[2], r_[3], _MM_SHUFFLE(3, 1, 3, 1));
	res.simd[3] = _mm_shuffle_ps(r_[2], r_[3], _MM_SHUFFLE(2, 0, 2, 0));
	return (res);
}

//static inline t_mat4s shuffle_inputs(const t_mat4s in)
//{
//	t_mat4s ret;

//	ret.simd[0] = _mm_shuffle_ps(in.simd[0], in.simd[1],
//							  _MM_SHUFFLE(0, 1, 0, 1));
//	ret.simd[1] = _mm_shuffle_ps(in.simd[0], in.simd[1],
//							  _MM_SHUFFLE(2, 3, 2, 3));
//	ret.simd[2] = _mm_shuffle_ps(in.simd[2], in.simd[3],
//							  _MM_SHUFFLE(0, 1, 0, 1));
//	ret.simd[3] = _mm_shuffle_ps(in.simd[2], in.simd[3],
//							  _MM_SHUFFLE(2, 3, 2, 3));
//	return (ret);
//}

//static inline __m128 compute_det2sub(const t_mat4s in)
//{
//	__m128 a = _mm_shuffle_ps(in.simd[0], in.simd[1],
//							 _MM_SHUFFLE(0, 2, 0, 2));
//	__m128 b = _mm_shuffle_ps(in.simd[1], in.simd[3],
//							 _MM_SHUFFLE(1, 3, 1, 3));
//	__m128 c = _mm_shuffle_ps(in.simd[0], in.simd[2],
//							 _MM_SHUFFLE(1, 3, 1, 3));
//	__m128 d = _mm_shuffle_ps(in.simd[1], in.simd[3],
//							 _MM_SHUFFLE(0, 2, 0, 2));
//	__m128 det2sub = _mm_sub_ps(_mm_mul_ps(a, b), _mm_mul_ps(c, d));
//	return det2sub;
//}

//static inline t_mat4s shuffle_det2sub(const __m128 det2sub)
//{
//	t_mat4s	ret;

//	ret.simd[0] = _mm_shuffle_ps(det2sub, det2sub, _MM_SHUFFLE(0, 0, 0, 0));
//	ret.simd[1] = _mm_shuffle_ps(det2sub, det2sub, _MM_SHUFFLE(1, 1, 1, 1));
//	ret.simd[2] = _mm_shuffle_ps(det2sub, det2sub, _MM_SHUFFLE(2, 2, 2, 2));
//	ret.simd[3] = _mm_shuffle_ps(det2sub, det2sub, _MM_SHUFFLE(3, 3, 3, 3));
//	return (ret);
//}

//static inline t_mat4s compute_cofactors(const __m128 shuff[4],
//				const __m128 det2[4], __m128 *d_c, __m128 *a_b)
//{
//	t_mat4s	ret;

//	*d_c = mat2_adjmul(shuff[3], shuff[2]);
//	*a_b = mat2_adjmul(shuff[0], shuff[1]);
//	ret.simd[0] = _mm_sub_ps(_mm_mul_ps(det2[3], shuff[0]),
//					  mat2mul(shuff[1], *d_c));
//	ret.simd[3] = _mm_sub_ps(_mm_mul_ps(det2[0], shuff[3]),
//					  mat2mul(shuff[2], *a_b));
//	ret.simd[1] = _mm_sub_ps(_mm_mul_ps(det2[1], shuff[2]),
//					  mat2_muladj(shuff[3], *a_b));
//	ret.simd[2] = _mm_sub_ps(_mm_mul_ps(det2[2], shuff[1]),
//					  mat2_muladj(shuff[0], *d_c));
//	return (ret);
//}

//static inline t_mat4s finalize_inverse(const __m128 r_[4],
//						const __m128 a_b, const __m128 d_c,
//						const __m128 det2[4])
//{
//	__m128 det_m;
//	__m128 tr2;
//	__m128 rcp_det_m;
//	t_mat4s res;
//	const __m128 adj_signmask = _mm_setr_ps(1.f, -1.f, -1.f, 1.f);

//	det_m = _mm_mul_ps(det2[0], det2[3]);
//	tr2 = _mm_mul_ps(a_b, \
//			_mm_shuffle_ps(d_c, d_c, _MM_SHUFFLE(0, 2, 1, 3)));
//	tr2 = _mm_hadd_ps(tr2, tr2);
//	tr2 = _mm_hadd_ps(tr2, tr2);
//	det_m = _mm_sub_ps(det_m, tr2);
//	rcp_det_m = _mm_div_ps(adj_signmask, det_m);
//	res.simd[0] = _mm_mul_ps(r_[0], rcp_det_m);
//	res.simd[1] = _mm_mul_ps(r_[1], rcp_det_m);
//	res.simd[2] = _mm_mul_ps(r_[2], rcp_det_m);
//	res.simd[3] = _mm_mul_ps(r_[3], rcp_det_m);
//	res.simd[0] = _mm_shuffle_ps(r_[0], r_[1], _MM_SHUFFLE(3, 1, 3, 1));
//	res.simd[1] = _mm_shuffle_ps(r_[0], r_[1], _MM_SHUFFLE(2, 0, 2, 0));
//	res.simd[2] = _mm_shuffle_ps(r_[2], r_[3], _MM_SHUFFLE(3, 1, 3, 1));
//	res.simd[3] = _mm_shuffle_ps(r_[2], r_[3], _MM_SHUFFLE(2, 0, 2, 0));
//	return (res);
//}

//static inline t_mat4s lag_mat4s_inverse(const t_mat4s in)
//{
//	__m128 det2sub;
//	__m128 d_c;
//	__m128 a_b;
//	t_mat4s r_;
//	t_mat4s res;
	
//	det2sub = compute_det2sub(in);
//	r_ = compute_cofactors(\
//		shuffle_inputs(in).simd, \
//		shuffle_det2sub(det2sub).simd, \
//		&d_c, &a_b
//	);
//	res = finalize_inverse(r_.simd, a_b, d_c, shuffle_det2sub(det2sub).simd);
//	return (res);
//} ////////////

//static inline t_mat4s shuffle_inputs(const t_mat4s in)
//{
//	t_mat4s ret;

//	ret.simd[0] = _mm_shuffle_ps(in.simd[0], in.simd[1],
//							  _MM_SHUFFLE(0, 1, 0, 1));
//	ret.simd[1] = _mm_shuffle_ps(in.simd[0], in.simd[1],
//							  _MM_SHUFFLE(2, 3, 2, 3));
//	ret.simd[2] = _mm_shuffle_ps(in.simd[2], in.simd[3],
//							  _MM_SHUFFLE(0, 1, 0, 1));
//	ret.simd[3] = _mm_shuffle_ps(in.simd[2], in.simd[3],
//							  _MM_SHUFFLE(2, 3, 2, 3));
//	return (ret);
//}

//static inline __m128 compute_det2sub(const t_mat4s in)
//{
//	__m128 a = _mm_shuffle_ps(in.simd[0], in.simd[1],
//							 _MM_SHUFFLE(0, 2, 0, 2));
//	__m128 b = _mm_shuffle_ps(in.simd[1], in.simd[3],
//							 _MM_SHUFFLE(1, 3, 1, 3));
//	__m128 c = _mm_shuffle_ps(in.simd[0], in.simd[2],
//							 _MM_SHUFFLE(1, 3, 1, 3));
//	__m128 d = _mm_shuffle_ps(in.simd[1], in.simd[3],
//							 _MM_SHUFFLE(0, 2, 0, 2));
//	__m128 det2sub = _mm_sub_ps(_mm_mul_ps(a, b), _mm_mul_ps(c, d));
//	return det2sub;
//}

//static inline t_mat4s shuffle_det2sub(const __m128 det2sub)
//{
//	t_mat4s	ret;

//	ret.simd[0] = _mm_shuffle_ps(det2sub, det2sub, _MM_SHUFFLE(0, 0, 0, 0));
//	ret.simd[1] = _mm_shuffle_ps(det2sub, det2sub, _MM_SHUFFLE(1, 1, 1, 1));
//	ret.simd[2] = _mm_shuffle_ps(det2sub, det2sub, _MM_SHUFFLE(2, 2, 2, 2));
//	ret.simd[3] = _mm_shuffle_ps(det2sub, det2sub, _MM_SHUFFLE(3, 3, 3, 3));
//	return (ret);
//}

//static inline t_mat4s compute_cofactors(const __m128 shuff[4],
//				const __m128 det2[4], __m128 *d_c, __m128 *a_b)
//{
//	t_mat4s	ret;

//	*d_c = mat2_adjmul(shuff[3], shuff[2]);
//	*a_b = mat2_adjmul(shuff[0], shuff[1]);
//	ret.simd[0] = _mm_sub_ps(_mm_mul_ps(det2[3], shuff[0]),
//					  mat2mul(shuff[1], *d_c));
//	ret.simd[3] = _mm_sub_ps(_mm_mul_ps(det2[0], shuff[3]),
//					  mat2mul(shuff[2], *a_b));
//	ret.simd[1] = _mm_sub_ps(_mm_mul_ps(det2[1], shuff[2]),
//					  mat2_muladj(shuff[3], *a_b));
//	ret.simd[2] = _mm_sub_ps(_mm_mul_ps(det2[2], shuff[1]),
//					  mat2_muladj(shuff[0], *d_c));
//	return (ret);
//}

//static inline t_mat4s finalize_inverse(const __m128 r_[4],
//                                       const __m128 a_b, const __m128 d_c,
//                                       const __m128 det2[4])
//{
//    __m128 det_m;
//    __m128 tr2;
//    __m128 rcp_det_m;
//    t_mat4s res;
//    const __m128 adj_signmask = _mm_setr_ps(1.f, -1.f, -1.f, 1.f);

//    // Correct determinant calculation (det(A) * det(D) - trace adjustment)
//    det_m = _mm_mul_ps(det2[0], det2[3]);  // det(A) * det(D)
    
//    // Compute trace adjustment (trace of cofactor matrix)
//    tr2 = _mm_mul_ps(a_b, _mm_shuffle_ps(d_c, d_c, _MM_SHUFFLE(0, 2, 1, 3)));
//    tr2 = _mm_hadd_ps(tr2, tr2);
//    tr2 = _mm_hadd_ps(tr2, tr2);
    
//    det_m = _mm_sub_ps(det_m, tr2);  // Adjust determinant with trace

//    // Extract the determinant scalar value
//    float det_m_val;
//    _mm_store_ss(&det_m_val, det_m);

//    // Check if the determinant is zero (singular matrix)
//    if (fabsf(det_m_val) < 1e-6f || isnan(det_m_val)) {
//        // Return identity matrix if matrix is singular
//        res.simd[0] = _mm_setr_ps(1.f, 0.f, 0.f, 0.f);
//        res.simd[1] = _mm_setr_ps(0.f, 1.f, 0.f, 0.f);
//        res.simd[2] = _mm_setr_ps(0.f, 0.f, 1.f, 0.f);
//        res.simd[3] = _mm_setr_ps(0.f, 0.f, 0.f, 1.f);
//        return res;
//    }

//    // Compute 1 / determinant
//    rcp_det_m = _mm_div_ps(adj_signmask, det_m); 

//    // Apply the reciprocal determinant to each row
//    res.simd[0] = _mm_mul_ps(r_[0], rcp_det_m);
//    res.simd[1] = _mm_mul_ps(r_[1], rcp_det_m);
//    res.simd[2] = _mm_mul_ps(r_[2], rcp_det_m);
//    res.simd[3] = _mm_mul_ps(r_[3], rcp_det_m);

//    return res;
//}

//static inline t_mat4s lag_mat4s_inverse(const t_mat4s in)
//{
//    __m128 det2sub;
//    __m128 d_c;
//    __m128 a_b;
//    t_mat4s r_;
//    t_mat4s res;

//    // Compute the 2x2 determinant submatrices
//    det2sub = compute_det2sub(in);

//    // Compute cofactors of the matrix
//    r_ = compute_cofactors(
//        shuffle_inputs(in).simd,
//        shuffle_det2sub(det2sub).simd,
//        &d_c, &a_b
//    );

//    // Finalize inverse while checking for valid determinant
//    res = finalize_inverse(r_.simd, a_b, d_c, shuffle_det2sub(det2sub).simd);
    
//    return res;
//}


#endif // !MAT4S_INVERSE_H
