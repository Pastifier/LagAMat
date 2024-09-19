/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 05:00:41 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/18 22:47:17 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LagATest.hpp"

typedef class LagATest	LagATest;

int main(int argc, char *argv[])
{
	LagATest tests("|| This field is for future use ||");

	//tests.runVec4dTests();
	tests.runVec4sTests();

	if (tests.allPassed())
		PRINT_LINE("Congratulations! All test cases have passed!");
}