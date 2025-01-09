/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:51:35 by okrahl            #+#    #+#             */
/*   Updated: 2025/01/07 12:56:14 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/BitcoinExchange.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}

	try {
		BitcoinExchange btc;
		btc.loadDatabase("data/subject/data.csv");
		btc.processInput(argv[1]);
	}
	catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}

