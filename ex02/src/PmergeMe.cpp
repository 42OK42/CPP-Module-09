/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:27:12 by okrahl            #+#    #+#             */
/*   Updated: 2025/01/16 12:56:24 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/PmergeMe.hpp"


PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) : _list(other._list), _deque(other._deque) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_list = other._list;
		_deque = other._deque;
	}
	return *this;
}


bool PmergeMe::isPositiveNumber(const std::string& str) const
{
	if (str.empty())
		return false;
	for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
	{
		if (!isdigit(*it))
			return false;
	}
	char* endptr;
	long num = std::strtol(str.c_str(), &endptr, 10);
	if (*endptr != '\0' || num <= 0 || num > INT_MAX)
		return false;
	return true;
}

void PmergeMe::parseInput(int argc, char** argv)
{
	for (int i = 1; i < argc; ++i)
	{
		if (!isPositiveNumber(argv[i]))
			throw std::invalid_argument("Invalid input: " + std::string(argv[i]));
		_list.push_back(std::atoi(argv[i]));
		_deque.push_back(std::atoi(argv[i]));
	}
}

void PmergeMe::displayBefore() const
{
	std::cout << "Before: ";
	for (std::list<int>::const_iterator it = _list.begin(); it != _list.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::displayAfter() const
{
	std::cout << "After: ";
	for (std::list<int>::const_iterator it = _list.begin(); it != _list.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

// Main sorting functions
void PmergeMe::sortList()
{
	if (_list.size() <= 1)
		return;
	mergeInsertList(_list);
}

void PmergeMe::sortDeque()
{
	mergeInsertDeque(_deque);
}

void PmergeMe::mergeInsertList(std::list<int>& lst)
{
	if (lst.size() <= 1)
		return;

	// build pairs
	std::list<std::pair<int, int> > pairs;
	int single = -1;
	std::list<int>::iterator it = lst.begin();
	
	while (it != lst.end())
	{
		int first = *it++;
		if (it != lst.end())
		{
			int second = *it++;
			if (first > second)
				pairs.push_back(std::make_pair(second, first));
			else
				pairs.push_back(std::make_pair(first, second));
		}
		else
			single = first;
	}

	#ifdef DEBUG_MODE
		std::cout << "\n[LIST] Pairs formed:" << std::endl;
		for (std::list<std::pair<int, int> >::iterator it = pairs.begin(); 
			 it != pairs.end(); ++it)
		{
			std::cout << "(" << it->first << "," << it->second << ") ";
		}
		if (single != -1)
			std::cout << "(" << single << ")";
		std::cout << std::endl;
	#endif

	// sort List with bigger elements
	std::list<int> sorted;
	for (std::list<std::pair<int, int> >::iterator it = pairs.begin(); 
		 it != pairs.end(); ++it)
	{
		sorted.push_back(it->second);
	}

	if (sorted.size() > 1)
		mergeInsertList(sorted);

	#ifdef DEBUG_MODE
		std::cout << "[LIST] Larger elements sorted:" << std::endl;
		for (std::list<int>::iterator it = sorted.begin(); 
			 it != sorted.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	#endif

	// push smaller elements
	for (std::list<std::pair<int, int> >::iterator it = pairs.begin(); 
		 it != pairs.end(); ++it)
	{
		std::list<int>::iterator pos = sorted.begin();
		while (pos != sorted.end() && *pos < it->first)
			++pos;
		sorted.insert(pos, it->first);
	}

	// push single elements
	if (single != -1)
	{
		std::list<int>::iterator pos = sorted.begin();
		while (pos != sorted.end() && *pos < single)
			++pos;
		sorted.insert(pos, single);
	}

	#ifdef DEBUG_MODE
		std::cout << "[LIST] Final sorted list:" << std::endl;
		for (std::list<int>::iterator it = sorted.begin(); 
			 it != sorted.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	#endif
	
	lst = sorted;
}

void PmergeMe::mergeInsertDeque(std::deque<int>& dq)
{
	if (dq.size() <= 1)
		return;

	// build pairs
	std::deque<std::pair<int, int> > pairs;
	int single = -1;
	std::deque<int>::iterator it = dq.begin();
	
	while (it != dq.end())
	{
		int first = *it++;
		if (it != dq.end())
		{
			int second = *it++;
			if (first > second)
				pairs.push_back(std::make_pair(second, first));
			else
				pairs.push_back(std::make_pair(first, second));
		}
		else
			single = first;
	}

	#ifdef DEBUG_MODE
		std::cout << "\n[DEQUE] Pairs formed:" << std::endl;
		for (std::deque<std::pair<int, int> >::iterator it = pairs.begin(); 
			 it != pairs.end(); ++it)
		{
			std::cout << "(" << it->first << "," << it->second << ") ";
		}
		if (single != -1)
			std::cout << "(" << single << ")";
		std::cout << std::endl;
	#endif

	// sort deque with bigger elements
	std::deque<int> sorted;
	for (std::deque<std::pair<int, int> >::iterator it = pairs.begin(); 
		 it != pairs.end(); ++it)
	{
		sorted.push_back(it->second);
	}

	if (sorted.size() > 1)
		mergeInsertDeque(sorted);

	#ifdef DEBUG_MODE
		std::cout << "[DEQUE] Larger elements sorted:" << std::endl;
		for (std::deque<int>::iterator it = sorted.begin(); 
			 it != sorted.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	#endif

	// push smaller elements
	for (std::deque<std::pair<int, int> >::iterator it = pairs.begin(); 
		 it != pairs.end(); ++it)
	{
		std::deque<int>::iterator pos = sorted.begin();
		while (pos != sorted.end() && *pos < it->first)
			++pos;
		sorted.insert(pos, it->first);
	}

	// push single elements
	if (single != -1)
	{
		std::deque<int>::iterator pos = sorted.begin();
		while (pos != sorted.end() && *pos < single)
			++pos;
		sorted.insert(pos, single);
	}

	#ifdef DEBUG_MODE
		std::cout << "[DEQUE] Final sorted list:" << std::endl;
		for (std::deque<int>::iterator it = sorted.begin(); 
			 it != sorted.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	#endif
	
	dq = sorted;
}

void PmergeMe::sort()
{
	clock_t startList = clock();
	sortList();
	clock_t endList = clock();
	_listTime = static_cast<double>(endList - startList) / CLOCKS_PER_SEC * 1000000;

	clock_t startDeque = clock();
	sortDeque();
	clock_t endDeque = clock();
	_dequeTime = static_cast<double>(endDeque - startDeque) / CLOCKS_PER_SEC * 1000000;

	std::cout << "Time to process a range of " << _list.size() 
			  << " elements with std::list : " << std::fixed 
			  << std::setprecision(5) << _listTime << " us" << std::endl;
	
	std::cout << "Time to process a range of " << _deque.size() 
			  << " elements with std::deque : " << std::fixed 
			  << std::setprecision(5) << _dequeTime << " us" << std::endl;
} 