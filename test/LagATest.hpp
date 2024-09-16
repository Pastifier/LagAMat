/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LagATest.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 03:29:08 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/16 10:18:31 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../include/lag.h"

#define MAX_LEVEL 1
#define PRINT_LINE(X) std::cout << X << std::endl
#define PRINT_ERR(X) std::cerr << X << std::endl
#define EPSILON 0.0001

#include <cmath>

class Vec4
{
public:
	Vec4() : _internal((t_vec4d){0.0, 0.0, 0.0, 0.0}) {};
	Vec4(const t_vec4d init) : _internal(init) {};
	Vec4(const Vec4& other) : _internal(other._internal) {};

	const t_vec4d getVector() const {
		return _internal;
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