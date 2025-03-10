/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:27:12 by okrahl            #+#    #+#             */
/*   Updated: 2025/03/10 15:37:28 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/PmergeMe.hpp"


PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) : _vector(other._vector), _deque(other._deque) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_vector = other._vector;
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
		_vector.push_back(std::atoi(argv[i]));
		_deque.push_back(std::atoi(argv[i]));
	}
}

void PmergeMe::displayBefore() const
{
	std::cout << "Before: ";
	for (std::vector<int>::const_iterator it = _vector.begin(); it != _vector.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::displayAfter() const
{
	std::cout << "After: ";
	for (std::vector<int>::const_iterator it = _vector.begin(); it != _vector.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

// Main sorting functions
void PmergeMe::sortVector()
{
	if (_vector.size() <= 1)
		return;
	mergeInsertVector(_vector);
}

void PmergeMe::sortDeque()
{
	mergeInsertDeque(_deque);
}

// Helper function to calculate Jacobsthal numbers
int PmergeMe::jacobsthalNumber(int n) const
{
	if (n == 0) return 0;
	if (n == 1) return 1;
	
	int j_n_minus_1 = 1;
	int j_n_minus_2 = 0;
	int j_n = 0;
	
	for (int i = 2; i <= n; i++)
	{
		j_n = j_n_minus_1 + 2 * j_n_minus_2;
		j_n_minus_2 = j_n_minus_1;
		j_n_minus_1 = j_n;
	}
	
	return j_n;
}

// Generates the Jacobsthal insertion order for n elements
std::vector<int> PmergeMe::generateJacobsthalInsertionOrder(int n) const
{
	std::vector<int> result;
	if (n <= 0) return result;
	
	// Add the first position (always 1)
	result.push_back(1);
	
	// Calculate how many Jacobsthal numbers we need
	int jacobsthalIndex = 3; // Start with J(3) = 3
	int currentJacobsthal = 3;
	
	while (currentJacobsthal <= n)
	{
		// Add the current Jacobsthal position
		result.push_back(currentJacobsthal);
		
		// Add all positions between the previous and current Jacobsthal number
		// (in descending order)
		int prevJacobsthal = jacobsthalNumber(jacobsthalIndex - 1);
		for (int i = currentJacobsthal - 1; i > prevJacobsthal; i--)
		{
			if (i <= n) result.push_back(i);
		}
		
		// Calculate the next Jacobsthal number
		jacobsthalIndex++;
		currentJacobsthal = jacobsthalNumber(jacobsthalIndex);
	}
	
	// Add the remaining positions
	for (int i = n; i > currentJacobsthal && i > 0; i--)
	{
		result.push_back(i);
	}
	
	return result;
}

void PmergeMe::mergeInsertVector(std::vector<int>& vec)
{
	if (vec.size() <= 1)
		return;

	// build pairs
	std::vector<std::pair<int, int> > pairs;
	int single = -1;
	size_t i = 0;
	
	while (i < vec.size())
	{
		int first = vec[i++];
		if (i < vec.size())
		{
			int second = vec[i++];
			if (first > second)
				pairs.push_back(std::make_pair(second, first));
			else
				pairs.push_back(std::make_pair(first, second));
		}
		else
			single = first;
	}

	#ifdef DEBUG_MODE
		std::cout << "\n[VECTOR] Pairs formed:" << std::endl;
		for (std::vector<std::pair<int, int> >::iterator it = pairs.begin(); 
			 it != pairs.end(); ++it)
		{
			std::cout << "(" << it->first << "," << it->second << ") ";
		}
		if (single != -1)
			std::cout << "(" << single << ")";
		std::cout << std::endl;
	#endif

	// sort vector with bigger elements
	std::vector<int> sorted;
	for (std::vector<std::pair<int, int> >::iterator it = pairs.begin(); 
		 it != pairs.end(); ++it)
	{
		sorted.push_back(it->second);
	}

	if (sorted.size() > 1)
		mergeInsertVector(sorted);

	#ifdef DEBUG_MODE
		std::cout << "[VECTOR] Larger elements sorted:" << std::endl;
		for (std::vector<int>::iterator it = sorted.begin(); 
			 it != sorted.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	#endif

	// Store the smaller elements in a vector for easier access
	std::vector<int> smallerElements;
	for (std::vector<std::pair<int, int> >::iterator it = pairs.begin(); 
		 it != pairs.end(); ++it)
	{
		smallerElements.push_back(it->first);
	}
	
	// Generate the Jacobsthal insertion order
	std::vector<int> insertionOrder = generateJacobsthalInsertionOrder(smallerElements.size());
	
	#ifdef DEBUG_MODE
		std::cout << "[VECTOR] Jacobsthal insertion order:" << std::endl;
		for (size_t i = 0; i < insertionOrder.size(); i++)
		{
			std::cout << insertionOrder[i] << " ";
		}
		std::cout << std::endl;
	#endif
	
	// Insert the smaller elements according to the Jacobsthal sequence
	for (size_t i = 0; i < insertionOrder.size(); i++)
	{
		int index = insertionOrder[i] - 1; // -1 because indices start at 0
		if (index < static_cast<int>(smallerElements.size()))
		{
			int valueToInsert = smallerElements[index];
			
			// For vector we can use binary search
			std::vector<int>::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), valueToInsert);
			sorted.insert(pos, valueToInsert);
		}
	}

	// push single element
	if (single != -1)
	{
		// Binary search for the single element
		std::vector<int>::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), single);
		sorted.insert(pos, single);
	}

	#ifdef DEBUG_MODE
		std::cout << "[VECTOR] Final sorted vector:" << std::endl;
		for (std::vector<int>::iterator it = sorted.begin(); 
			 it != sorted.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	#endif
	
	vec = sorted;
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

	// Store the smaller elements in a vector for easier access
	std::vector<int> smallerElements;
	for (std::deque<std::pair<int, int> >::iterator it = pairs.begin(); 
		 it != pairs.end(); ++it)
	{
		smallerElements.push_back(it->first);
	}
	
	// Generate the Jacobsthal insertion order
	std::vector<int> insertionOrder = generateJacobsthalInsertionOrder(smallerElements.size());
	
	#ifdef DEBUG_MODE
		std::cout << "[DEQUE] Jacobsthal insertion order:" << std::endl;
		for (size_t i = 0; i < insertionOrder.size(); i++)
		{
			std::cout << insertionOrder[i] << " ";
		}
		std::cout << std::endl;
	#endif
	
	// Insert the smaller elements according to the Jacobsthal sequence
	for (size_t i = 0; i < insertionOrder.size(); i++)
	{
		int index = insertionOrder[i] - 1; // -1 because indices start at 0
		if (index < static_cast<int>(smallerElements.size()))
		{
			int valueToInsert = smallerElements[index];
			
			// For deque we can use binary search
			size_t left = 0;
			size_t right = sorted.size();
			
			while (left < right)
			{
				size_t mid = left + (right - left) / 2;
				if (sorted[mid] < valueToInsert)
					left = mid + 1;
				else
					right = mid;
			}
			
			sorted.insert(sorted.begin() + left, valueToInsert);
		}
	}

	// push single element
	if (single != -1)
	{
		// Binary search for the single element
		size_t left = 0;
		size_t right = sorted.size();
		
		while (left < right)
		{
			size_t mid = left + (right - left) / 2;
			if (sorted[mid] < single)
				left = mid + 1;
			else
				right = mid;
		}
		
		sorted.insert(sorted.begin() + left, single);
	}

	#ifdef DEBUG_MODE
		std::cout << "[DEQUE] Final sorted deque:" << std::endl;
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
	clock_t startVector = clock();
	sortVector();
	clock_t endVector = clock();
	_vectorTime = static_cast<double>(endVector - startVector) / CLOCKS_PER_SEC * 1000000;

	clock_t startDeque = clock();
	sortDeque();
	clock_t endDeque = clock();
	_dequeTime = static_cast<double>(endDeque - startDeque) / CLOCKS_PER_SEC * 1000000;

	std::cout << "Time to process a range of " << _vector.size() 
			  << " elements with std::vector : " << std::fixed 
			  << std::setprecision(5) << _vectorTime << " us" << std::endl;
	
	std::cout << "Time to process a range of " << _deque.size() 
			  << " elements with std::deque : " << std::fixed 
			  << std::setprecision(5) << _dequeTime << " us" << std::endl;
} 