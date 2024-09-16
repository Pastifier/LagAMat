/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 05:00:41 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/16 10:22:32 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LagATest.hpp"

typedef class LagATest	LagATest;

int main(int argc, char *argv[])
{
	LagATest tests("|| This field is for future use ||");

	tests.test_vec4d_init();
	tests.test_vec4d_add();
	tests.test_vec4d_sub();
	tests.test_vec4d_scaleby();
	tests.test_vec4d_negation();
	tests.test_vec4d_dot();
	tests.test_vec4d_mag();
	tests.test_vec4d_normalize();
	tests.test_vec4d_cross();

	if (tests.allPassed())
		PRINT_LINE("Congratulations! All test cases have passed!");
}