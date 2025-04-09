/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:27:12 by okrahl            #+#    #+#             */
/*   Updated: 2025/04/08 12:54:45 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/PmergeMe.hpp"

void runTests()
{
	std::cout << "\nRunning predefined tests..." << std::endl;
	
	//  Test 1: Simple sequence
	{
		std::cout << "\nTest 1: Simple sequence" << std::endl;
		char* args[] = {(char*)"./PmergeMe", (char*)"3", (char*)"5", (char*)"9", (char*)"7", (char*)"4",(char*)"8", (char*)"2", (char*)"1", (char*)"6", (char*)"10"};
		PmergeMe sorter;
		sorter.parseInput(11, args);
		sorter.displayBefore();
		sorter.sort();
		sorter.displayAfter();
	}
	
	// Test 2: Already sorted
	{
		std::cout << "\nTest 2: Already sorted" << std::endl;
		char* args[] = {(char*)"./PmergeMe", (char*)"1", (char*)"2", (char*)"3", (char*)"4", (char*)"5"};
		PmergeMe sorter;
		sorter.parseInput(6, args);
		sorter.displayBefore();
		sorter.sort();
		sorter.displayAfter();
	}
	
	// Test 3: Reverse sorted
	{
		std::cout << "\nTest 3: Reverse sorted" << std::endl;
		char* args[] = {(char*)"./PmergeMe", (char*)"5", (char*)"4", (char*)"3", (char*)"2", (char*)"1"};
		PmergeMe sorter;
		sorter.parseInput(6, args);
		sorter.displayBefore();
		sorter.sort();
		sorter.displayAfter();
	}
	
	// Test 4: Single element
	{
		std::cout << "\nTest 4: Single element" << std::endl;
		char* args[] = {(char*)"./PmergeMe", (char*)"42"};
		PmergeMe sorter;
		sorter.parseInput(2, args);
		sorter.displayBefore();
		sorter.sort();
		sorter.displayAfter();
	}
	
	// Test 5: Error cases
	{
		std::cout << "\nTest 5: Error cases" << std::endl;
		try {
			char* args[] = {(char*)"./PmergeMe", (char*)"-1", (char*)"2", (char*)"3"};
			PmergeMe sorter;
			sorter.parseInput(4, args);
		}
		catch (const std::exception& e) {
			std::cout << "Expected error caught: " << e.what() << std::endl;
		}
		
		try {
			char* args[] = {(char*)"./PmergeMe", (char*)"1", (char*)"abc", (char*)"3"};
			PmergeMe sorter;
			sorter.parseInput(4, args);
		}
		catch (const std::exception& e) {
			std::cout << "Expected error caught: " << e.what() << std::endl;
		}
	}
}

int main(int argc, char* argv[])
{
	if (argc < 2) {
		runTests();
		return 0;
	}

	try {
		PmergeMe sorter;
		sorter.parseInput(argc, argv);
		sorter.displayBefore();
		sorter.sort();
		sorter.displayAfter();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	
	return 0;
}
