/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:27:12 by okrahl            #+#    #+#             */
/*   Updated: 2025/01/10 12:30:14 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN& other) : _stack(other._stack) {}

RPN& RPN::operator=(const RPN& other) {
	if (this != &other) {
		_stack = other._stack;
	}
	return *this;
}

bool RPN::isOperator(char c) const
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

void RPN::performOperation(char op)
{
	if (_stack.size() < 2)
		throw std::runtime_error("Not enough operands");
		
	int b = _stack.top();
	_stack.pop();
	int a = _stack.top();
	_stack.pop();
	
	switch(op)
	{
		case '+':
			_stack.push(a + b);
			break;
		case '-':
			_stack.push(a - b);
			break;
		case '*':
			_stack.push(a * b);
			break;
		case '/':
			if (b == 0)
				throw std::runtime_error("Division by zero");
			_stack.push(a / b);
			break;
	}
}

int RPN::calculate(const std::string& expression)
{
	while (!_stack.empty())
		_stack.pop();
	
	for (size_t i = 0; i < expression.length(); i++)
	{
		char c = expression[i];
		
		if (c == ' ')
			continue;
			
		if (isdigit(c))
		{
			int number = c - '0';
			if (number >= 10)
				throw std::runtime_error("Numbers must be less than 10");
			_stack.push(number);
		}
		else if (isOperator(c))
		{
			performOperation(c);
		}
		else
		{
			throw std::runtime_error("Invalid character");
		}
	}
	
	if (_stack.size() != 1)
		throw std::runtime_error("Invalid expression");
		
	return _stack.top();
}