/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:27:15 by okrahl            #+#    #+#             */
/*   Updated: 2025/01/10 12:30:23 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/RPN.hpp"

void runTest(RPN& calculator, const std::string& expression, int expectedResult)
{
	try
	{
		int result = calculator.calculate(expression);
		std::cout << "Test \"" << expression << "\": ";
		if (result == expectedResult)
			std::cout << "OK (" << result << ")" << std::endl;
		else
			std::cout << "ERROR! Expected: " << expectedResult << ", Got: " << result << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "Test \"" << expression << "\": ERROR! " << e.what() << std::endl;
	}
}

int main(int argc, char* argv[])
{
	RPN calculator;

	std::cout << "Starting automatic tests:" << std::endl;
	std::cout << "-------------------------" << std::endl;
	runTest(calculator, "3 4 +", 7);
	runTest(calculator, "8 9 * 9 - 9 - 9 - 4 - 1 +", 42);
	runTest(calculator, "7 7 * 7 -", 42);
	runTest(calculator, "1 2 * 2 / 2 * 2 4 - +", 0);
	runTest(calculator, "9 8 * 4 * 4 / 2 + 9 - 8 * 8 - 1 - 4 -", 42);
	runTest(calculator, "1 2 + 3 4 - *", -3);
	std::cout << "-------------------------\n" << std::endl;

	if (argc != 2)
	{
		std::cerr << "Error: Please provide an RPN expression as argument" << std::endl;
		std::cerr << "Example: ./RPN \"1 2 +\"" << std::endl;
		return 1;
	}

	try
	{
		std::cout << "User input: " << argv[1] << std::endl;
		int result = calculator.calculate(argv[1]);
		std::cout << "Result: " << result << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	
	return 0;
}
