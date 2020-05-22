#include <iostream>
#include <string>
#include <vector>

#include "elastic.hpp"

int main() {
	std::vector<std::string> lines;

	std::string line;
	while (std::getline(std::cin, line))
		lines.push_back(line);

	std::vector<std::vector<std::size_t>> tabstops = elastic::calc_tabstops(lines);

	for (std::size_t i = 0; i < lines.size(); i++) {
		std::string_view line = lines[i];
		for (std::size_t c = 0, count = 0, tab = 0; c < line.size(); c++) {
			if (line[c] == '\t') {
				while (count++ < tabstops[i][tab])
					std::cout << ' ';
				count = 0;
				tab++;
			} else {
				std::cout << line[c];
				count++;
			}
		}
		std::cout << '\n';
	}
}
