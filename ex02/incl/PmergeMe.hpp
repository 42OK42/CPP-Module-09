/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:45:01 by okrahl            #+#    #+#             */
/*   Updated: 2025/01/16 12:30:17 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <list>
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
	std::list<int> _list;
	std::deque<int> _deque;
	double _listTime;
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
	void sortList();
	void sortDeque();
	void mergeInsertList(std::list<int>& lst);
	void mergeInsertDeque(std::deque<int>& dq);
	bool isPositiveNumber(const std::string& str) const;
};

#endif 