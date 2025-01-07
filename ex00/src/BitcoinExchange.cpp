/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:51:38 by okrahl            #+#    #+#             */
/*   Updated: 2025/01/07 12:53:37 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void) {}

void BitcoinExchange::loadDatabase(const std::string &filename) {
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("Could not open database file");
	
	std::string line;
	std::getline(file, line); // Skip header
	
	while (std::getline(file, line)) {
		size_t comma = line.find(',');
		if (comma != std::string::npos) {
			std::string date = line.substr(0, comma);
			float value = std::atof(line.substr(comma + 1).c_str());
			_database[date] = value;
		}
	}
}

