/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:52:33 by okrahl            #+#    #+#             */
/*   Updated: 2025/01/07 13:02:42 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

class BitcoinExchange {
private:
	std::map<std::string, float> _database;

public:
	BitcoinExchange(void);
	BitcoinExchange(const BitcoinExchange &src);
	~BitcoinExchange();
	BitcoinExchange &operator=(const BitcoinExchange &src);

	void	loadDatabase(const std::string &filename);
	void	processInput(const std::string &filename);
	float	getExchangeRate(const std::string &date) const;
	
private:
	bool	isValidDate(const std::string &date) const;
	bool	isValidValue(const float value) const;
	void	parseAndCalculate(const std::string &line);
};

#endif 