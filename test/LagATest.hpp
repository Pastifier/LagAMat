/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LagATest.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 03:29:08 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/18 00:38:31 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../include/lag.h"

#define MAX_LEVEL 1
#define PRINT_LINE(X) std::cout << X << std::endl
#define PRINT_ERR(X) std::cerr << X << std::endl

#ifndef EPSILON
# define EPSILON 0.0001
#endif // !EPSILON

#define PRINT_MATRIX4x4(M) \
{ \
Vec4 r1(M->getMatrix().r1); \
Vec4 r2(M->getMatrix().r2); \
Vec4 r3(M->getMatrix().r3); \
Vec4 r4(M->getMatrix().r4); \
PRINT_LINE(""); \
PRINT_LINE(r1); \
PRINT_LINE(r2); \
PRINT_LINE(r3); \
PRINT_LINE(r4); \
PRINT_LINE(""); \
}


#include <cmath>

class Vec4
{
public:
	Vec4() : _internal((t_vec4d){0.0, 0.0, 0.0, 0.0}) {};
	Vec4(const t_vec4d init) : _internal(init) {};
	Vec4(const Vec4& other) : _internal(other.getVector()) {};

	const t_vec4d getVector() const {
		return _internal;
	}

	void setVector(double x, double y, double z, double w) {
		_internal.simd = _mm256_set_pd(w, z, y, x);
	}

	void invertBits() {
		_internal.simd = _mm256_andnot_pd(_internal.simd, _internal.simd);
	}

	bool operator==(const Vec4& other) const {
		// Need to use EPSILON
		const t_vec4d otherVec = other.getVector();
		return std::abs(_internal.x - otherVec.x) < EPSILON &&
			std::abs(_internal.y - otherVec.y) < EPSILON &&
			std::abs(_internal.z - otherVec.z) < EPSILON &&
			std::abs(_internal.w - otherVec.w) < EPSILON;
	}

	bool operator!=(const Vec4& other) const {
		return !(*this == other);
	}

	friend std::ostream& operator<<(std::ostream& os, const Vec4& vec) {
		const t_vec4d v = vec.getVector();
		os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
		return os;
	}

private:
	t_vec4d _internal;
};

class Mat4
{
public:
	Mat4() : _internal(((t_mat4d){0})) {};
	Mat4(const t_mat4d init) : _internal(init) {};
	Mat4(const Mat4& other) : _internal(other.getMatrix()) {};

	const t_mat4d getMatrix() const {
		return _internal;
	}

	void print() {
		PRINT_MATRIX4x4(this);
	}

	bool operator==(const Mat4& other) const {
		bool	expr = true;
		for (int i = 0; i < 4; i++) {
			expr &= lag_vec4d_eq(
				*(t_vec4d *)this->getMatrix().a[i],
				*(t_vec4d *)other.getMatrix().a[i],
				EPSILON
			);
		}
		return expr;
	}

	bool operator!=(const Mat4& other) const {
		return !(*this == other);
	}

	friend std::ostream& operator<<(std::ostream& os, const Mat4& m) {
		Vec4 r[4];
		os << std::endl;
		for (int i = 0; i < 4; i++) {
			r[i] = Vec4(*(t_vec4d *)m.getMatrix().a[i]);
			os << r[i] << std::endl;
		}
		os << std::endl;
		return os;
	}

private:
	t_mat4d _internal;
};


class LagATest
{
public:
	~LagATest() {};
	LagATest(const std::string& option) :
		_option(option), _failedTests(0), _passedTests(0) {};

	bool allPassed() {
		return _failedTests == 0;
	}

	void test_vec4d_init();
	void test_vec4d_add();
	void test_vec4d_sub();
	void test_vec4d_scaleby();
	void test_vec4d_negation();
	void test_vec4d_dot();
	void test_vec4d_mag();
	void test_vec4d_normalize();
	void test_vec4d_cross();
	void test_vec4d_eq();

	void runVec4dTests() {
		test_vec4d_init();
		test_vec4d_add();
		test_vec4d_sub();
		test_vec4d_scaleby();
		test_vec4d_negation();
		test_vec4d_dot();
		test_vec4d_mag();
		test_vec4d_normalize();
		test_vec4d_cross();
		test_vec4d_eq();
	}

private:
	int _failedTests;
	int _passedTests;

	template <typename T>
	void assertEqual(T expected, T actual) {
		if (expected != actual) {
			PRINT_ERR("Test failed: Expected " << expected << ", but got " << actual);
			++_failedTests;
		} else {
			++_passedTests;
		}
	}

	void routineCheck() {
		if (allPassed())
			PRINT_LINE("\tPass!");
		else
			PRINT_LINE("\tFail.");
	}

	std::string _option;
};

typedef class LagATest	LagATest;