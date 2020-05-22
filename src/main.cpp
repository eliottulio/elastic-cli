#include <iostream>
#include <string>
#include <vector>

#include "elastic.hpp"

int main() {
	std::vector<std::string> lines;

	std::string line;
	while (std::getline(std::cin, line))
		lines.push_back(line);

	std::vector<std::vector<std::size_t>> tabstops = elastic::calc_tabstops(lines, 4, ":{", [](std::string_view str) {
		return elastic::get_strlen(str) - (str[str.size() - 2] == '(' ? 1 : 0);
	});

	for (std::size_t i = 0; i < lines.size(); i++) {
		std::string_view line = lines[i];

		std::size_t prev_j = -1;
		std::size_t j;
		std::size_t tab = 0;

		while ((j = line.find_first_of('\t', prev_j + 1)) != std::string::npos) {
			std::size_t len = elastic::get_strlen(line.substr(prev_j + 1, j - prev_j - 1));

			std::cout << line.substr(prev_j + 1, j - prev_j - 1);
			for (std::size_t k = len; k < tabstops[i][tab]; k++)
				std::cout << ' ';

			prev_j = j;
			tab++;
		}
		std::cout << line.substr(prev_j + 1) << '\n';
	}
}
