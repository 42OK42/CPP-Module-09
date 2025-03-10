/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:45:01 by okrahl            #+#    #+#             */
/*   Updated: 2025/03/10 15:15:02 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <climits>

class PmergeMe {
private:
	std::vector<int> _vector;
	std::deque<int> _deque;
	double _vectorTime;
	double _dequeTime;
	
public:
	PmergeMe();
	~PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);

	void parseInput(int argc, char** argv);
	void sort();
	void displayBefore() const;
	void displayAfter() const;
	
private:
	void sortVector();
	void sortDeque();
	void mergeInsertVector(std::vector<int>& vec);
	void mergeInsertDeque(std::deque<int>& dq);
	bool isPositiveNumber(const std::string& str) const;
	int jacobsthalNumber(int n) const;
	std::vector<int> generateJacobsthalInsertionOrder(int n) const;
};

#endif 