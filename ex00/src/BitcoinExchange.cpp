/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:51:38 by okrahl            #+#    #+#             */
/*   Updated: 2025/01/07 14:42:44 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void) {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src)
{
	*this = src;
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src)
{
	if (this != &src)
	{
		this->_database = src._database;
	}
	return *this;
}

void BitcoinExchange::loadDatabase(const std::string &filename) {
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error: could not open database file.");
	
	std::string line;
	std::getline(file, line); // Skip header
	
	while (std::getline(file, line)) {
		size_t comma = line.find(',');
		if (comma != std::string::npos) {
			std::string date = line.substr(0, comma);
			float value = static_cast<float>(std::atof(line.substr(comma + 1).c_str()));
			_database[date] = value;
		}
	}
}

void BitcoinExchange::processInput(const std::string &filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("Could not open input file");

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		try
		{
			parseAndCalculate(line);
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
	}
}

void	BitcoinExchange::parseAndCalculate(const std::string &line)
{
	size_t separator = line.find(" | ");
	if (separator == std::string::npos)
		throw std::runtime_error("Error: bad input => " + line);
	
	std::string date = line.substr(0, separator);
	if (!isValidDate(date))
		throw std::runtime_error("Error: bad input => " + line);

	try {
		float value = static_cast<float>(std::atof(line.substr(separator + 3).c_str()));
		if (!isValidValue(value))
			throw std::runtime_error("Error: value must be between 0 and 1000");
			
		float rate = getExchangeRate(date);

		std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
	}
	catch (...) {
		throw std::runtime_error("Error: invalid number format => " + line);
	}
}

float	BitcoinExchange::getExchangeRate(const std::string &date) const
{
	std::map<std::string, float>::const_iterator it = _database.upper_bound(date);
	
	if (it == _database.begin())
		return it->second;		//could also throw an error but i decided against it cause value is 0 anyways
	
	--it;
	return it->second;
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
	if (date.length() != 10)
		return false;
	
	// Check format YYYY-MM-DD
	if (date[4] != '-' || date[7] != '-')
		return false;

	try {
		int year = std::atoi(date.substr(0, 4).c_str());
		int month = std::atoi(date.substr(5, 2).c_str());
		int day = std::atoi(date.substr(8, 2).c_str());

		if (year < 2009 || year > 2022)
			return false;
		if (month < 1 || month > 12)
			return false;
		if (day < 1 || day > 31)
			return false;

		if (month == 4 || month == 6 || month == 9 || month == 11)
			return day <= 30;
		if (month == 2)
		{
			bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
			return day <= (isLeapYear ? 29 : 28);
		}
		return true;
	}
	catch (...) {
		return false;
	}
}

bool BitcoinExchange::isValidValue(const float value) const
{
	return value >= 0 && value <= 1000;
}
