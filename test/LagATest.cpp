/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LagATest.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 05:13:18 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/20 12:25:02y ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LagATest.hpp"
#include <random>

/*--- Vec4d ---*/

void LagATest::test_vec4d_init() {
	PRINT_LINE("Testing vec4dp_init(), vec4dv_init().");
	const t_vec4d v1 = {4.3, -4.2, 3.1, 1.0};
	t_vec4d v2;
	const t_vec4d v3 = {4.3, -4.2, 3.1, 0.0};
	t_vec4d v4;

	lag_vec4dp_init(&v2, v1.x, v1.y, v1.z);
	lag_vec4dv_init(&v4, v3.x, v3.y, v3.z);

	Vec4 vec1(v1);
	Vec4 vec2(v2);
	Vec4 vec3(v3);
	Vec4 vec4dth(v4); // oops LOL

	assertEqual(vec1, vec2);
	assertEqual(vec3, vec4dth);

	// Edge cases
	const t_vec4d zeroVec = {0.0, 0.0, 0.0, 0.0};
	t_vec4d zeroResult;
	lag_vec4dv_init(&zeroResult, 0.0, 0.0, 0.0);
	Vec4 vecZero(zeroVec);
	Vec4 vecZeroResult(zeroResult);
	assertEqual(vecZero, vecZeroResult);

	routineCheck();
	PRINT_LINE("");
}

void LagATest::test_vec4d_add() {
	PRINT_LINE("Testing vec4d_add(), vec4d_add_ret().");
	const t_vec4d p1 = lag_vec4dp_ret(3, -2, 5);
	const t_vec4d v1 = lag_vec4dv_ret(-2, 3, 1);
	const t_vec4d expected = lag_vec4dp_ret(1, 1, 6);

	t_vec4d res = lag_vec4d_add_ret(p1, v1);
	t_vec4d res2;
	lag_vec4d_add(&res2, p1, v1);

	Vec4 vec1(expected);
	Vec4 vec2(res);
	Vec4 vec3(res2);

	assertEqual(vec1, vec2);
	assertEqual(vec1, vec3);

	// Edge cases
	const t_vec4d zeroVec = {0.0, 0.0, 0.0, 0.0};
	const t_vec4d addResult = lag_vec4d_add_ret(zeroVec, zeroVec);
	const t_vec4d addExpected = zeroVec;
	Vec4 vecAddExpected(addExpected);
	Vec4 vecAddResult(addResult);
	assertEqual(vecAddExpected, vecAddResult);

	routineCheck();
	PRINT_LINE("");
}

void LagATest::test_vec4d_sub() {
	PRINT_LINE("Testing vec4d_sub(), vec4d_sub_ret().");
	const t_vec4d zeroVec = {0.0, 0.0, 0.0, 0.0};
	const t_vec4d p1 = lag_vec4dp_ret(3, -2, 5);
	const t_vec4d v1 = lag_vec4dv_ret(-2, 3, 1);
	const t_vec4d expected = lag_vec4dp_ret(5, -5, 4);

	t_vec4d res = lag_vec4d_sub_ret(p1, v1);
	t_vec4d res2;
	lag_vec4d_sub(&res2, p1, v1);

	Vec4 vec1(expected);
	Vec4 vec2(res);
	Vec4 vec3(res2);

	assertEqual(vec1, vec2);
	assertEqual(vec1, vec3);

	// Edge cases
	const t_vec4d subResult = lag_vec4d_sub_ret(zeroVec, zeroVec);
	const t_vec4d subExpected = zeroVec;
	Vec4 vecSubExpected(subExpected);
	Vec4 vecSubResult(subResult);
	assertEqual(vecSubExpected, vecSubResult);

	routineCheck();
	PRINT_LINE("");
}

void LagATest::test_vec4d_scaleby() {
	PRINT_LINE("Testing vec4d_scaleby(), vec4d_scaleby_ret().");
	const t_vec4d a = lag_vec4d_ret(1, -2, 3, -4);
	const double scalar = 3.5;
	const t_vec4d expected = lag_vec4d_ret(3.5, -7.0, 10.5, -14.0);

	t_vec4d res = lag_vec4d_scaleby_ret(a, scalar);
	t_vec4d res2;
	lag_vec4d_scaleby(&res2, a, scalar);

	Vec4 vec1(expected);
	Vec4 vec2(res);
	Vec4 vec3(res2);

	assertEqual(vec1, vec2);
	assertEqual(vec1, vec3);

	// Division
	const double scalar2 = 2.0;
	const t_vec4d expected2 = lag_vec4d_ret(0.5, -1.0, 1.5, -2.0);
	t_vec4d res3 = lag_vec4d_scaleby_ret(a, 1.0 / scalar2);
	t_vec4d res4;
	lag_vec4d_scaleby(&res4, a, 1.0 / scalar2);

	Vec4 vec4(expected2);
	Vec4 vec5(res3);
	Vec4 vec6(res4);

	assertEqual(vec4, vec5);
	assertEqual(vec4, vec6);

	// Edge cases
	const double zeroScalar = 0.0;
	const t_vec4d scaledByZero = lag_vec4d_scaleby_ret(a, zeroScalar);
	const t_vec4d expectedZero = lag_vec4d_ret(0.0, 0.0, 0.0, 0.0);
	Vec4 vecScaleZero(expectedZero);
	Vec4 vecScaledZero(scaledByZero);
	assertEqual(vecScaleZero, vecScaledZero);

	routineCheck();
	PRINT_LINE("");
}

void LagATest::test_vec4d_negation() {
	PRINT_LINE("Testing vec4d_negate_new(), vec4d_negate_ret(), vec4d_negate().");
	const t_vec4d v1 = lag_vec4dv_ret(1, -2, 3);
	const t_vec4d expected = lag_vec4dv_ret(-1, 2, -3);
	t_vec4d v2 = v1;
	t_vec4d v3;
	t_vec4d v4 = lag_vec4d_negate_ret(v1);

	lag_vec4d_negate_new(&v3, v1);
	lag_vec4d_negate(&v2);

	Vec4 vec1(expected);
	Vec4 vec2(v2);
	Vec4 vec3(v3);
	Vec4 vec4(v4);

	const t_vec4d a = lag_vec4d_ret(1, -2, 3, -4);
	const t_vec4d expected2 = lag_vec4d_ret(-1, 2, -3, 4);
	t_vec4d res = lag_vec4d_negate_ret(a);
	t_vec4d res2 = a;
	t_vec4d res3;
	lag_vec4d_negate(&res2);
	lag_vec4d_negate_new(&res3, a);

	Vec4 vec5(expected2);
	Vec4 vec6(res);
	Vec4 vec7(res2);
	Vec4 vec8(res3);

	assertEqual(vec1, vec2);
	assertEqual(vec1, vec3);
	assertEqual(vec1, vec4);
	assertEqual(vec5, vec6);
	assertEqual(vec5, vec7);
	assertEqual(vec5, vec8);

	routineCheck();
	PRINT_LINE("");
}

void	LagATest::test_vec4d_mag() {
	PRINT_LINE("Testing vec4d_magnitude(), vec4d_magnitude_ret().");

	// Normalized vectors
	const t_vec4d v1 = lag_vec4dv_ret(0, 1, 0);
	const double expected = 1.0;
	const double result = lag_vec4d_magnitude_ret(v1);
	double result2;
	lag_vec4d_magnitude(&result2, v1);

	assertEqual(expected, result);
	assertEqual(expected, result2);

	const t_vec4d v2 = lag_vec4dv_ret(0, 0, 1);
	const double result3 = lag_vec4d_magnitude_ret(v2);
	double result4;
	lag_vec4d_magnitude(&result4, v2);

	assertEqual(expected, result3);
	assertEqual(expected, result4);

	const t_vec4d v3 = lag_vec4dv_ret(1, 0, 0);
	const double result5 = lag_vec4d_magnitude_ret(v3);
	double result6;
	lag_vec4d_magnitude(&result6, v3);

	assertEqual(expected, result5);
	assertEqual(expected, result6);

	// Non-normalized vectors
	const t_vec4d v4 = lag_vec4dv_ret(1, 1, 1);
	const double expected2 = sqrt(3);
	const double result7 = lag_vec4d_magnitude_ret(v4);
	double result8;
	lag_vec4d_magnitude(&result8, v4);

	assertEqual(expected2, result7);
	assertEqual(expected2, result8);
	
	const t_vec4d v5 = lag_vec4dv_ret(1, 2, 3);
	const double expected3 = sqrt(14);
	const double result9 = lag_vec4d_magnitude_ret(v5);
	double result10;
	lag_vec4d_magnitude(&result10, v5);

	assertEqual(expected3, result9);
	assertEqual(expected3, result10);

	// Edge cases
	const t_vec4d zeroVec = lag_vec4dv_ret(0, 0, 0);
	const double zeroResult = lag_vec4d_magnitude_ret(zeroVec);
	double zeroResult2;
	lag_vec4d_magnitude(&zeroResult2, zeroVec);

	assertEqual(0.0, zeroResult);
	assertEqual(0.0, zeroResult2);
	
	routineCheck();
	PRINT_LINE("");
}

void	LagATest::test_vec4d_dot() {
	PRINT_LINE("Testing vec4d_dot(), vec4d_dot_ret().");

	const t_vec4d v1 = lag_vec4dv_ret(1, 2, 3);
	const t_vec4d v2 = lag_vec4dv_ret(2, 3, 4);
	const double expected = 20.0;

	double result;
	lag_vec4d_dot(&result, v1, v2);
	
	const double result2 = lag_vec4d_dot_ret(v1, v2);
	
	assertEqual(expected, result);
	assertEqual(expected, result2);

	const t_vec4d v3 = lag_vec4dv_ret(0, 0, 0);
	const double expected2 = 0.0;

	double result3;
	lag_vec4d_dot(&result3, v1, v3);

	const double result4 = lag_vec4d_dot_ret(v1, v3);
	
	assertEqual(expected2, result3);
	assertEqual(expected2, result4);

	const t_vec4d v4 = lag_vec4dv_ret(1, 0, 0);
	const t_vec4d v5 = lag_vec4dv_ret(0, 1, 0);
	const double expected3 = 0.0;

	double result5;
	lag_vec4d_dot(&result5, v4, v5);

	const double result6 = lag_vec4d_dot_ret(v4, v5);

	assertEqual(expected3, result5);
	assertEqual(expected3, result6);

	routineCheck();
	PRINT_LINE("");
}

void	LagATest::test_vec4d_normalize() {
	PRINT_LINE("Testing vec4d_normalize(), vec4d_normalize_new().");
	const t_vec4d v1 = lag_vec4dv_ret(4, 0, 0);
	const t_vec4d expected = lag_vec4dv_ret(1, 0, 0);

	t_vec4d v2 = v1;
	t_vec4d v3;
	lag_vec4d_normalize(&v2);
	lag_vec4d_normalize_new(&v3, v1);

	Vec4 vec1(expected);
	Vec4 vec2(v2);
	Vec4 vec3(v3);

	assertEqual(vec1, vec2);
	assertEqual(vec1, vec3);
	
	const t_vec4d v4 = lag_vec4dv_ret(1, 2, 3);
	const t_vec4d expected2 = lag_vec4dv_ret(1.0 / sqrt(14), 2.0 / sqrt(14), 3.0 / sqrt(14));

	t_vec4d v5 = v4;
	t_vec4d v6;
	lag_vec4d_normalize(&v5);
	lag_vec4d_normalize_new(&v6, v4);

	Vec4 vec4(expected2);
	Vec4 vec5(v5);
	Vec4 vec6(v6);

	assertEqual(vec4, vec5);
	assertEqual(vec4, vec6);
	
	const t_vec4d v7 = lag_vec4dv_ret(0, 0, 0);
	const t_vec4d expected3 = lag_vec4dv_ret(0, 0, 0);
	
	t_vec4d v8 = v7;
	t_vec4d v9;
	lag_vec4d_normalize(&v8);
	lag_vec4d_normalize_new(&v9, v7);

	Vec4 vec7(expected3);
	Vec4 vec8(v8);
	Vec4 vec9(v9);

	assertEqual(vec7, vec8);
	assertEqual(vec7, vec9);

	routineCheck();
	PRINT_LINE("");
}

void	LagATest::test_vec4d_cross() {
	PRINT_LINE("Testing vec4d_cross(), vec4d_cross_ret().");
	const t_vec4d v1 = lag_vec4dv_ret(1, 2, 3);
	const t_vec4d v2 = lag_vec4dv_ret(2, 3, 4);
	const t_vec4d expected = lag_vec4dv_ret(-1, 2, -1);
	const t_vec4d expected2 = lag_vec4dv_ret(1, -2, 1);

	t_vec4d res = lag_vec4d_cross_ret(v1, v2);
	t_vec4d res2;
	lag_vec4d_cross(&res2, v1, v2);

	Vec4 vec1(expected);
	Vec4 vec2(res);
	Vec4 vec3(res2);

	assertEqual(vec1, vec2);
	assertEqual(vec1, vec3);
	
	t_vec4d res3 = lag_vec4d_cross_ret(v2, v1);
	t_vec4d res4;
	lag_vec4d_cross(&res4, v2, v1);

	Vec4 vec4(expected2);
	Vec4 vec5(res3);
	Vec4 vec6(res4);

	assertEqual(vec4, vec5);
	assertEqual(vec4, vec6);

	// Edge cases
	const t_vec4d zeroVec = lag_vec4dv_ret(0, 0, 0);
	const t_vec4d zeroResult = lag_vec4d_cross_ret(zeroVec, zeroVec);
	const t_vec4d zeroExpected = zeroVec;

	Vec4 vecZeroExpected(zeroExpected);
	Vec4 vecZeroResult(zeroResult);

	assertEqual(vecZeroExpected, vecZeroResult);

	routineCheck();
	PRINT_LINE("");
}

void	LagATest::test_vec4d_eq() {
	PRINT_LINE("Testing vec4d_eq().");
	const t_vec4d v1 = lag_vec4d_ret(0, 0, 0, 0);
	const t_vec4d v2 = lag_vec4d_ret(0, 0, 0, 0);
	Vec4 vectors1[20];
	Vec4 vectors2[20];

	for (int i = 0; i < 20; i++) {
		vectors1[i].setVector(
			((double)std::rand() / __DBL_DIG__),
			((double)std::rand() / __DBL_DIG__),
			((double)std::rand() / __DBL_DIG__),
			((double)std::rand() / __DBL_DIG__)
		);
		vectors2[i] = vectors1[i];
		assertEqual(
			true,
			lag_vec4d_eq(
				vectors1[i].getVector(),
				vectors2[i].getVector(),
				EPSILON)
		);
	}

	for (int i = 0; i < 20; i++) {
		vectors1[i].setVector(
			((double)std::rand() / __DBL_DIG__),
			((double)std::rand() / __DBL_DIG__),
			((double)std::rand() / __DBL_DIG__),
			((double)std::rand() / __DBL_DIG__)
		);
		vectors2[i] = vectors1[i];
		vectors2[i].invertBits();
		assertEqual(
			false,
			lag_vec4d_eq(
				vectors1[i].getVector(),
				vectors2[i].getVector(),
				EPSILON)
		);
	}

	routineCheck();
	PRINT_LINE("");
}

/*---- Vec4s ----*/

void	LagATest::test_vec4s_init() {
	PRINT_LINE("Testing vec4sp_init(), vec4sv_init().");
	const t_vec4s v1 = {4.3, -4.2, 3.1, 1.0};
	t_vec4s v2;
	const t_vec4s v3 = {4.3, -4.2, 3.1, 0.0};
	t_vec4s v4;

	lag_vec4sp_init(&v2, v1.x, v1.y, v1.z);
	lag_vec4sv_init(&v4, v3.x, v3.y, v3.z);

	Vec4s vec1(v1);
	Vec4s vec2(v2);
	Vec4s vec3(v3);
	Vec4s vec4th(v4); // oops LOL

	assertEqual(vec1, vec2);
	assertEqual(vec3, vec4th);

	// Edge cases
	const t_vec4s zeroVec = {0.0, 0.0, 0.0, 0.0};
	t_vec4s zeroResult;
	lag_vec4sv_init(&zeroResult, 0.0, 0.0, 0.0);
	Vec4s vecZero(zeroVec);
	Vec4s vecZeroResult(zeroResult);
	assertEqual(vecZero, vecZeroResult);

	routineCheck();
	PRINT_LINE("");
}

void LagATest::test_vec4s_add() {
	PRINT_LINE("Testing vec4s_add(), vec4s_add_ret().");
	const t_vec4s p1 = lag_vec4sp_ret(3, -2, 5);
	const t_vec4s v1 = lag_vec4sv_ret(-2, 3, 1);
	const t_vec4s expected = lag_vec4sp_ret(1, 1, 6);

	t_vec4s res = lag_vec4s_add_ret(p1, v1);
	t_vec4s res2;
	lag_vec4s_add(&res2, p1, v1);

	Vec4s vec1(expected);
	Vec4s vec2(res);
	Vec4s vec3(res2);

	assertEqual(vec1, vec2);
	assertEqual(vec1, vec3);

	// Edge cases
	const t_vec4s zeroVec = {0.0, 0.0, 0.0, 0.0};
	const t_vec4s addResult = lag_vec4s_add_ret(zeroVec, zeroVec);
	const t_vec4s addExpected = zeroVec;
	Vec4s vecAddExpected(addExpected);
	Vec4s vecAddResult(addResult);
	assertEqual(vecAddExpected, vecAddResult);

	routineCheck();
	PRINT_LINE("");
}

void LagATest::test_vec4s_sub() {
	PRINT_LINE("Testing vec4s_sub(), vec4s_sub_ret().");
	const t_vec4s zeroVec = {0.0, 0.0, 0.0, 0.0};
	const t_vec4s p1 = lag_vec4sp_ret(3, -2, 5);
	const t_vec4s v1 = lag_vec4sv_ret(-2, 3, 1);
	const t_vec4s expected = lag_vec4sp_ret(5, -5, 4);

	t_vec4s res = lag_vec4s_sub_ret(p1, v1);
	t_vec4s res2;
	lag_vec4s_sub(&res2, p1, v1);

	Vec4s vec1(expected);
	Vec4s vec2(res);
	Vec4s vec3(res2);

	assertEqual(vec1, vec2);
	assertEqual(vec1, vec3);

	// Edge cases
	const t_vec4s subResult = lag_vec4s_sub_ret(zeroVec, zeroVec);
	const t_vec4s subExpected = zeroVec;
	Vec4s vecSubExpected(subExpected);
	Vec4s vecSubResult(subResult);
	assertEqual(vecSubExpected, vecSubResult);

	routineCheck();
	PRINT_LINE("");
}

void LagATest::test_vec4s_scaleby() {
	PRINT_LINE("Testing vec4s_scaleby(), vec4s_scaleby_ret().");
	const t_vec4s a = lag_vec4s_ret(1, -2, 3, -4);
	const float scalar = 3.5;
	const t_vec4s expected = lag_vec4s_ret(3.5, -7.0, 10.5, -14.0);

	t_vec4s res = lag_vec4s_scaleby_ret(a, scalar);
	t_vec4s res2;
	lag_vec4s_scaleby(&res2, a, scalar);

	Vec4s vec1(expected);
	Vec4s vec2(res);
	Vec4s vec3(res2);

	assertEqual(vec1, vec2);
	assertEqual(vec1, vec3);

	// Division
	const float scalar2 = 2.0;
	const t_vec4s expected2 = lag_vec4s_ret(0.5, -1.0, 1.5, -2.0);
	t_vec4s res3 = lag_vec4s_scaleby_ret(a, 1.0 / scalar2);
	t_vec4s res4;
	lag_vec4s_scaleby(&res4, a, 1.0 / scalar2);

	Vec4s vec4(expected2);
	Vec4s vec5(res3);
	Vec4s vec6(res4);

	assertEqual(vec4, vec5);
	assertEqual(vec4, vec6);

	// Edge cases
	const float zeroScalar = 0.0;
	const t_vec4s scaledByZero = lag_vec4s_scaleby_ret(a, zeroScalar);
	const t_vec4s expectedZero = lag_vec4s_ret(0.0, 0.0, 0.0, 0.0);
	Vec4s vecScaleZero(expectedZero);
	Vec4s vecScaledZero(scaledByZero);
	assertEqual(vecScaleZero, vecScaledZero);

	routineCheck();
	PRINT_LINE("");
}

void LagATest::test_vec4s_negation() {
	PRINT_LINE("Testing vec4s_negate_new(), vec4s_negate_ret(), vec4s_negate().");
	const t_vec4s v1 = lag_vec4sv_ret(1, -2, 3);
	const t_vec4s expected = lag_vec4sv_ret(-1, 2, -3);
	t_vec4s v2 = v1;
	t_vec4s v3;
	t_vec4s v4 = lag_vec4s_negate_ret(v1);

	lag_vec4s_negate_new(&v3, v1);
	lag_vec4s_negate(&v2);

	Vec4s vec1(expected);
	Vec4s vec2(v2);
	Vec4s vec3(v3);
	Vec4s vec4(v4);

	const t_vec4s a = lag_vec4s_ret(1, -2, 3, -4);
	const t_vec4s expected2 = lag_vec4s_ret(-1, 2, -3, 4);
	t_vec4s res = lag_vec4s_negate_ret(a);
	t_vec4s res2 = a;
	t_vec4s res3;
	lag_vec4s_negate(&res2);
	lag_vec4s_negate_new(&res3, a);

	Vec4s vec5(expected2);
	Vec4s vec6(res);
	Vec4s vec7(res2);
	Vec4s vec8(res3);

	assertEqual(vec1, vec2);
	assertEqual(vec1, vec3);
	assertEqual(vec1, vec4);
	assertEqual(vec5, vec6);
	assertEqual(vec5, vec7);
	assertEqual(vec5, vec8);

	routineCheck();
	PRINT_LINE("");
}

void	LagATest::test_vec4s_dot() {
	PRINT_LINE("Testing vec4s_dot(), vec4s_dot_ret().");

	const t_vec4s v1 = lag_vec4sv_ret(1, 2, 3);
	const t_vec4s v2 = lag_vec4sv_ret(2, 3, 4);
	const float expected = 20.0;

	float result;
	lag_vec4s_dot(&result, v1, v2);
	
	const float result2 = lag_vec4s_dot_ret(v1, v2);
	
	assertEqual(expected, result);
	assertEqual(expected, result2);

	const t_vec4s v3 = lag_vec4sv_ret(0, 0, 0);
	const float expected2 = 0.0;

	float result3;
	lag_vec4s_dot(&result3, v1, v3);

	const float result4 = lag_vec4s_dot_ret(v1, v3);
	
	assertEqual(expected2, result3);
	assertEqual(expected2, result4);

	const t_vec4s v4 = lag_vec4sv_ret(1, 0, 0);
	const t_vec4s v5 = lag_vec4sv_ret(0, 1, 0);
	const float expected3 = 0.0;

	float result5;
	lag_vec4s_dot(&result5, v4, v5);

	const float result6 = lag_vec4s_dot_ret(v4, v5);

	assertEqual(expected3, result5);
	assertEqual(expected3, result6);

	routineCheck();
	PRINT_LINE("");
}

void	LagATest::test_vec4s_mag() {
	PRINT_LINE("Testing vec4s_magnitude(), vec4s_magnitude_ret().");

	// Normalized vectors
	const t_vec4s v1 = lag_vec4sv_ret(0, 1, 0);
	const float expected = 1.0;
	const float result = lag_vec4s_magnitude_ret(v1);
	float result2;
	lag_vec4s_magnitude(&result2, v1);

	assertEqual(expected, result);
	assertEqual(expected, result2);

	const t_vec4s v2 = lag_vec4sv_ret(0, 0, 1);
	const float result3 = lag_vec4s_magnitude_ret(v2);
	float result4;
	lag_vec4s_magnitude(&result4, v2);

	assertEqual(expected, result3);
	assertEqual(expected, result4);

	const t_vec4s v3 = lag_vec4sv_ret(1, 0, 0);
	const float result5 = lag_vec4s_magnitude_ret(v3);
	float result6;
	lag_vec4s_magnitude(&result6, v3);

	assertEqual(expected, result5);
	assertEqual(expected, result6);

	// Non-normalized vectors
	const t_vec4s v4 = lag_vec4sv_ret(1, 1, 1);
	const float expected2 = sqrtf(3);
	const float result7 = lag_vec4s_magnitude_ret(v4);
	float result8;
	lag_vec4s_magnitude(&result8, v4);

	assertEqual(expected2, result7);
	assertEqual(expected2, result8);
	
	const t_vec4s v5 = lag_vec4sv_ret(1, 2, 3);
	const float expected3 = sqrtf(14);
	const float result9 = lag_vec4s_magnitude_ret(v5);
	float result10;
	lag_vec4s_magnitude(&result10, v5);

	assertEqual(expected3, result9);
	assertEqual(expected3, result10);

	// Edge cases
	const t_vec4s zeroVec = lag_vec4sv_ret(0, 0, 0);
	const float zeroResult = lag_vec4s_magnitude_ret(zeroVec);
	float zeroResult2;
	lag_vec4s_magnitude(&zeroResult2, zeroVec);

	assertEqual(0.0f, zeroResult);
	assertEqual(0.0f, zeroResult2);
	
	routineCheck();
	PRINT_LINE("");
}

void	LagATest::test_vec4s_cross() {
	PRINT_LINE("Testing vec4s_cross(), vec4s_cross_ret().");
	const t_vec4s v1 = lag_vec4sv_ret(1, 2, 3);
	const t_vec4s v2 = lag_vec4sv_ret(2, 3, 4);
	const t_vec4s expected = lag_vec4sv_ret(-1, 2, -1);
	const t_vec4s expected2 = lag_vec4sv_ret(1, -2, 1);

	t_vec4s res = lag_vec4s_cross_ret(v1, v2);
	t_vec4s res2;
	lag_vec4s_cross(&res2, v1, v2);

	Vec4s vec1(expected);
	Vec4s vec2(res);
	Vec4s vec3(res2);

	assertEqual(vec1, vec2);
	assertEqual(vec1, vec3);
	
	t_vec4s res3 = lag_vec4s_cross_ret(v2, v1);
	t_vec4s res4;
	lag_vec4s_cross(&res4, v2, v1);

	Vec4s vec4(expected2);
	Vec4s vec5(res3);
	Vec4s vec6(res4);

	assertEqual(vec4, vec5);
	assertEqual(vec4, vec6);

	// Edge cases
	const t_vec4s zeroVec = lag_vec4sv_ret(0, 0, 0);
	const t_vec4s zeroResult = lag_vec4s_cross_ret(zeroVec, zeroVec);
	const t_vec4s zeroExpected = zeroVec;

	Vec4s vecZeroExpected(zeroExpected);
	Vec4s vecZeroResult(zeroResult);

	assertEqual(vecZeroExpected, vecZeroResult);

	routineCheck();
	PRINT_LINE("");
}

void	LagATest::test_vec4s_eq() {
	PRINT_LINE("Testing vec4s_eq().");
	const t_vec4s v1 = lag_vec4s_ret(0, 0, 0, 0);
	const t_vec4s v2 = lag_vec4s_ret(0, 0, 0, 0);
	Vec4s vectors1[20];
	Vec4s vectors2[20];

	for (int i = 0; i < 20; i++) {
		vectors1[i].setVector(
			((double)std::rand() / __DBL_DIG__),
			((double)std::rand() / __DBL_DIG__),
			((double)std::rand() / __DBL_DIG__),
			((double)std::rand() / __DBL_DIG__)
		);
		vectors2[i] = vectors1[i];
		assertEqual(
			true,
			lag_vec4s_eq(
				vectors1[i].getVector(),
				vectors2[i].getVector(),
				EPSILON)
		);
	}

	for (int i = 0; i < 20; i++) {
		vectors1[i].setVector(
			((double)std::rand() / __DBL_DIG__),
			((double)std::rand() / __DBL_DIG__),
			((double)std::rand() / __DBL_DIG__),
			((double)std::rand() / __DBL_DIG__)
		);
		vectors2[i] = vectors1[i];
		vectors2[i].invertBits();
		assertEqual(
			false,
			lag_vec4s_eq(
				vectors1[i].getVector(),
				vectors2[i].getVector(),
				EPSILON)
		);
	}

	routineCheck();
	PRINT_LINE("");
}

void	LagATest::test_vec4s_normalize() {
	PRINT_LINE("Testing vec4s_normalize(), vec4s_normalize_new().");
	const t_vec4s v1 = lag_vec4sv_ret(4, 0, 0);
	const t_vec4s expected = lag_vec4sv_ret(1, 0, 0);

	t_vec4s v2 = v1;
	t_vec4s v3;
	lag_vec4s_normalize(&v2);
	lag_vec4s_normalize_new(&v3, v1);

	Vec4s vec1(expected);
	Vec4s vec2(v2);
	Vec4s vec3(v3);

	assertEqual(vec1, vec2);
	assertEqual(vec1, vec3);
	
	const t_vec4s v4 = lag_vec4sv_ret(1, 2, 3);
	const t_vec4s expected2 = lag_vec4sv_ret(1.0 / sqrtf(14), 2.0 / sqrtf(14), 3.0 / sqrtf(14));

	t_vec4s v5 = v4;
	t_vec4s v6;
	lag_vec4s_normalize(&v5);
	lag_vec4s_normalize_new(&v6, v4);

	Vec4s vec4(expected2);
	Vec4s vec5(v5);
	Vec4s vec6(v6);

	assertEqual(vec4, vec5);
	assertEqual(vec4, vec6);
	
	const t_vec4s v7 = lag_vec4sv_ret(0, 0, 0);
	const t_vec4s expected3 = lag_vec4sv_ret(0, 0, 0);
	
	t_vec4s v8 = v7;
	t_vec4s v9;
	lag_vec4s_normalize(&v8);
	lag_vec4s_normalize_new(&v9, v7);

	Vec4s vec7(expected3);
	Vec4s vec8(v8);
	Vec4s vec9(v9);

	assertEqual(vec7, vec8);
	assertEqual(vec7, vec9);

	routineCheck();
	PRINT_LINE("");
}

void	LagATest::test_mat4s_init() {
	{
		PRINT_LINE("Testing `lag_mat4s_identity()`:");
		t_mat4s m1 = (t_mat4s)
		{
			.r1 = (t_vec4s){1, 0, 0, 0},
			.r2 = (t_vec4s){0, 1, 0, 0},
			.r3 = (t_vec4s){0, 0, 1, 0},
			.r4 = (t_vec4s){0, 0, 0, 1},
		};
		t_mat4s m2 = lag_mat4s_identity();

		Mat4<t_mat4s, t_vec4s, Vec4s> expected(m1);
		Mat4<t_mat4s, t_vec4s, Vec4s> actual(m2);
		if (assertEqual(expected, actual))
			PRINT_LINE("Test 1 passed!");
	}

	{
		PRINT_LINE("Testing `lag_mat4s_translation()`:");
		t_mat4s expected_mats[200];
		t_mat4s actual_mats[200];

		for (int i = 0; i < 200; i++) {
			const float sx = std::rand() / __FLT_MAX__;
			const float sy = std::rand() / __FLT_MAX__;
			const float sz = std::rand() / __FLT_MAX__;

			expected_mats[i] = (t_mat4s)
			{
				.r1 = (t_vec4s){0, 0, 0, sx},
				.r2 = (t_vec4s){0, 0, 0, sy},
				.r3 = (t_vec4s){0, 0, 0, sz},
				.r4 = (t_vec4s){0, 0, 0, 1}
			};
			actual_mats[i] = lag_mat4s_scaling(sx, sy, sz);
			Mat4<t_mat4s, t_vec4s, Vec4s> expected(expected_mats[i]);
			Mat4<t_mat4s, t_vec4s, Vec4s> actual(actual_mats[i]);
			if (assertEqual(expected, actual))
				PRINT_LINE("Pass.");
		}
	}

	{
		PRINT_LINE("Testing `lag_mat4s_rows_ret()`:");
		t_mat4s expected_mats[200] = {0};
		t_mat4s actual_mats[200] = {0};

		for (int n = 0; n < 200; n++) {
			for (int r = 0; r < 4; r++) {
				for (int c = 0; c < 4; c++ /*hehe~*/) 
					expected_mats[n].a[r][c] = std::rand() / __FLT_MAX__;
			}
			actual_mats[n] = lag_mat4s_rows_ret(
				expected_mats[n].r1,
				expected_mats[n].r2,
				expected_mats[n].r3,
				expected_mats[n].r4
			);
			Mat4<t_mat4s, t_vec4s, Vec4s> expected(expected_mats[n]);
			Mat4<t_mat4s, t_vec4s, Vec4s> actual(actual_mats[n]);
			if (assertEqual(expected, actual))
				PRINT_LINE("Pass.");
		}
	}

	{
		PRINT_LINE("Testing `lag_mat4s_rotation_x()`");
		t_mat4s expected_mats[360] = {0};
		t_mat4s actual_mats[360] = {0};

		for (int n = 0; n < 360; n++) {
			float rad = M_PI * n / 180;
			expected_mats[n] = (t_mat4s)
			{
				.r1 = lag_vec4s_ret(1, 0, 0, 0),
				.r2 = lag_vec4s_ret(0, cos(rad), -sin(rad), 0),
				.r3 = lag_vec4s_ret(0, sin(rad), cos(rad), 0),
				.r4 = lag_vec4s_ret(0, 0, 0, 1),
			};
			actual_mats[n] = lag_mat4s_rotation_x(rad);
			Mat4<t_mat4s, t_vec4s, Vec4s> expected(expected_mats[n]);
			Mat4<t_mat4s, t_vec4s, Vec4s> actual(actual_mats[n]);
			if (assertEqual(expected, actual))
				PRINT_LINE("Pass.");
		}
	}

	{
		PRINT_LINE("Testing `lag_mat4s_rotation_y()`");
		t_mat4s expected_mats[360] = {0};
		t_mat4s actual_mats[360] = {0};

		for (int n = 0; n < 360; n++) {
			float rad = M_PI * n / 180;
			expected_mats[n] = (t_mat4s)
			{
				.r1 = lag_vec4s_ret(cos(rad), 0, sin(rad), 0),
				.r2 = lag_vec4s_ret(0, 1, 0, 0),
				.r3 = lag_vec4s_ret(-sin(rad), 0, cos(rad), 0),
				.r4 = lag_vec4s_ret(0, 0, 0, 1),
			};
			actual_mats[n] = lag_mat4s_rotation_y(rad);
			Mat4<t_mat4s, t_vec4s, Vec4s> expected(expected_mats[n]);
			Mat4<t_mat4s, t_vec4s, Vec4s> actual(actual_mats[n]);
			if (assertEqual(expected, actual))
				PRINT_LINE("Pass.");
		}
	}

	{
		PRINT_LINE("Testing `lag_mat4s_rotation_z()`");
		t_mat4s expected_mats[360] = {0};
		t_mat4s actual_mats[360] = {0};

		for (int n = 0; n < 360; n++) {
			float rad = M_PI * n / 180;
			expected_mats[n] = (t_mat4s)
			{
				.r1 = lag_vec4s_ret(cos(rad), -sin(rad), 0, 0),
				.r2 = lag_vec4s_ret(sin(rad), cos(rad), 0, 0),
				.r3 = lag_vec4s_ret(0, 0, 1, 0),
				.r4 = lag_vec4s_ret(0, 0, 0, 1),
			};
			actual_mats[n] = lag_mat4s_rotation_z(rad);
			Mat4<t_mat4s, t_vec4s, Vec4s> expected(expected_mats[n]);
			Mat4<t_mat4s, t_vec4s, Vec4s> actual(actual_mats[n]);
			if (assertEqual(expected, actual))
				PRINT_LINE("Pass.");
		}
	}
}
