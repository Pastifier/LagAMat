/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4s_transform_inverse.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:34:23 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/02 21:37:32 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT4S_TRANSFORM_INVERSE
# define MAT4S_TRANSFORM_INVERSE

# include "ltypes.h"

/*Process documented in https://docs.google.com/document/d/1ok8dzMk7EZiZaVRB61zGDlxRSDoelX3z6ixaCRlg0yM/edit?usp=sharing*/

/// @brief Calculates the inverse of a decomposed matrix
/// (rotation, scale, translation)
/// @param rot The rotational component of the matrix
/// @param s The scale factor of the matrix
/// @param t The translation component of the matrix
/// @return The inverse of the decomposed matrix
/// @warning The scale should NOT contain any zero components as that will
/// cause divide-by-zero errors! (And it doesn't really make sense anyway)
static inline t_mat4s	lag_mat4s_get_transform_inverse(const t_mat4s rot, const __m128 s,
			const __m128 t)
{
	t_mat4s			ret0;
	__m128			tmp0, tmp1, tmp2, tmp3;
	const __m128	rcps = _mm_div_ps(_mm_set1_ps(1.f), s);
	const __m128	tinv = _mm_sub_ps(_mm_set1_ps(0.f), t);

	tmp0 = _mm_unpacklo_ps(rot.simd[0], rot.simd[1]);
	tmp1 = _mm_unpackhi_ps(rot.simd[0], rot.simd[1]);
	tmp2 = _mm_unpacklo_ps(rot.simd[2], rot.simd[3]);
	tmp3 = _mm_unpackhi_ps(rot.simd[2], rot.simd[3]);

	ret0.simd[0] = _mm_movelh_ps(tmp0, tmp2);
	ret0.simd[1] = _mm_movehl_ps(tmp2, tmp0);
	ret0.simd[2] = _mm_movelh_ps(tmp1, tmp3);
	ret0.simd[3] = _mm_set_ps(1, 0, 0, 0);

	ret0.simd[0] = _mm_mul_ps(ret0.simd[0],
			_mm_shuffle_ps(rcps, rcps, _MM_SHUFFLE(0, 0, 0, 0)));
	ret0.simd[1] = _mm_mul_ps(ret0.simd[1],
			_mm_shuffle_ps(rcps, rcps, _MM_SHUFFLE(1, 1, 1, 1)));
	ret0.simd[2] = _mm_mul_ps(ret0.simd[2],
			_mm_shuffle_ps(rcps, rcps, _MM_SHUFFLE(2, 2, 2, 2)));

	ret0.r1.w = _mm_cvtss_f32(_mm_dp_ps(ret0.simd[0], tinv, 0xF1));
	ret0.r2.w = _mm_cvtss_f32(_mm_dp_ps(ret0.simd[1], tinv, 0xF1));
	ret0.r3.w = _mm_cvtss_f32(_mm_dp_ps(ret0.simd[2], tinv, 0xF1));
	return (ret0);
}

//static inline t_mat4s lag_mat4s_get_transform_inverse(const t_mat4s s,
//						const t_mat4s r, const t_mat4s t)
//{
//	const __m128 zeros = _mm_set1_ps(0);
//	const __m128 mul00 = _mm_set_ps(1, t.r3.w, t.r2.w, t.r1.w);
//	t_mat4s t1w0;
//	t_mat4s s1rr;

//	__m128 tmp0 = _mm_unpacklo_ps(r.simd[0], r.simd[1]); // [r00, r10, r01, r11]
//	__m128 tmp1 = _mm_unpackhi_ps(r.simd[0], r.simd[1]); // [r02, r12, r03, r13]
//	__m128 tmp2 = _mm_unpacklo_ps(r.simd[2], r.simd[3]); // [r20, r30, r21, r31]
//	__m128 tmp3 = _mm_unpackhi_ps(r.simd[2], r.simd[3]); // [r22, r32, r23, r33]

//	s1rr.simd[0] = _mm_mul_ps(_mm_movelh_ps(tmp0, tmp2), _mm_set1_ps(1.f / s.r1.x)); // [r00/sx, r10/sx, r20/sx, r30/sx]
//	s1rr.simd[1] = _mm_mul_ps(_mm_movehl_ps(tmp2, tmp0), _mm_set1_ps(1.f / s.r2.y)); // [r01/sy, r11/sy, r21/sy, r31/sy]
//	s1rr.simd[2] = _mm_mul_ps(_mm_movelh_ps(tmp1, tmp3), _mm_set1_ps(1.f / s.r3.z)); // [r02/sz, r12/sz, r22/sz, r32/sz]
//	s1rr.simd[3] = _mm_movehl_ps(tmp3, tmp1); // [0, 0, 0, 1]

//	t1w0.simd[0] = _mm_sub_ps(zeros, _mm_dp_ps(s1rr.simd[0], mul00, 0xF1));
//	t1w0.simd[1] = _mm_sub_ps(zeros, _mm_dp_ps(s1rr.simd[1], mul00, 0xF1));
//	t1w0.simd[2] = _mm_sub_ps(zeros, _mm_dp_ps(s1rr.simd[2], mul00, 0xF1));

//	s1rr.r1.w = _mm_cvtss_f32(t1w0.simd[0]);
//	s1rr.r2.w = _mm_cvtss_f32(t1w0.simd[1]);
//	s1rr.r3.w = _mm_cvtss_f32(t1w0.simd[2]);

//	return (s1rr);
//}

//static inline t_mat4s lag_mat4s_get_transform_inverse(const t_mat4s s, const t_mat4s r, const t_mat4s t)
//{
//    // const __m128 zeros = _mm_set1_ps(0);
//    const __m128 mul00 = _mm_set_ps(1, -t.r3.w, -t.r2.w, -t.r1.w);
//    t_mat4s t1w0;
//    t_mat4s s1rr;

//    __m128 tmp0 = _mm_unpacklo_ps(r.simd[0], r.simd[1]); // [r00, r10, r01, r11]
//    __m128 tmp1 = _mm_unpackhi_ps(r.simd[0], r.simd[1]); // [r02, r12, r03, r13]
//    __m128 tmp2 = _mm_unpacklo_ps(r.simd[2], r.simd[3]); // [r20, r30, r21, r31]
//    __m128 tmp3 = _mm_unpackhi_ps(r.simd[2], r.simd[3]); // [r22, r32, r23, r33]

//    s1rr.simd[0] = _mm_mul_ps(_mm_movelh_ps(tmp0, tmp2), _mm_set1_ps(1.f / s.r1.x)); // [r00/sx, r10/sx, r20/sx, r30/sx]
//    s1rr.simd[1] = _mm_mul_ps(_mm_movehl_ps(tmp2, tmp0), _mm_set1_ps(1.f / s.r2.y)); // [r01/sy, r11/sy, r21/sy, r31/sy]
//    s1rr.simd[2] = _mm_mul_ps(_mm_movelh_ps(tmp1, tmp3), _mm_set1_ps(1.f / s.r3.z)); // [r02/sz, r12/sz, r22/sz, r32/sz]
//    s1rr.simd[3] = _mm_movehl_ps(tmp3, tmp1); // [0, 0, 0, 1]

//    //t1w0.simd[0] = /*_mm_sub_ps(zeros, */_mm_dp_ps(s1rr.simd[0], mul00, 0xF1)/*)*/;
//	t1w0.simd[0] = _mm_mul_ps(s1rr.simd[0], mul00);
//	_mm_storeu_ps((float *)&t1w0.r1, _mm_hadd_ps(t1w0.simd[0], t1w0.simd[0]));
//	s1rr.r1.w = t1w0.r1.a[0] + t1w0.r1.a[2];
//    t1w0.simd[1] = /*_mm_sub_ps(zeros, */_mm_dp_ps(s1rr.simd[1], mul00, 0xF1)/*)*/;
//    t1w0.simd[2] = /*_mm_sub_ps(zeros, */_mm_dp_ps(s1rr.simd[2], mul00, 0xF1)/*)*/;

//    //s1rr.r1.w = _mm_cvtss_f32(t1w0.simd[0]);
//    s1rr.r2.w = _mm_cvtss_f32(t1w0.simd[1]);
//    s1rr.r3.w = _mm_cvtss_f32(t1w0.simd[2]);

//    return (s1rr);
//}

#endif // !MAT4S_TRANSFORM_INVERSE
