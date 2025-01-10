/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:27:24 by okrahl            #+#    #+#             */
/*   Updated: 2025/01/10 12:30:32 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>
#include <iostream>

class RPN {
private:
	std::stack<int> _stack;
	
public:
	RPN();
	~RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	
	int calculate(const std::string& expression);
	
private:
	void performOperation(char op);
	bool isOperator(char c) const;
};

#endif 