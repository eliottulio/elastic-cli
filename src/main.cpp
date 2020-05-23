#include <iostream>
#include <string>
#include <vector>

#include "elastic.hpp"

int main(int argc, char** argv) {
	argc--;
	argv++;

	std::size_t tab_size = 4;
	std::string block_end_chars = ":{";
	while (argc > 0) {
		if (std::string(argv[0]) == "-t") {
			if (argc == 1) {
				std::cerr << "-t expects a number.\n";
				return 1;
			}
			tab_size = std::atoi(argv[1]);
			++ ++argv;
			-- --argc;
		} else if (std::string(argv[0]) == "--block-end-chars") {
			if (argc == 1) {
				std::cerr << "--block-end-chars expects a list of chars.\n";
				return 1;
			}
			block_end_chars = argv[1];
			++ ++argv;
			-- --argc;
		} else {
			std::cerr << "Unknown argument: '" << argv[0] << "'.\n";
			return 1;
		}
	}


	std::vector<std::string> lines;

	std::string line;
	while (std::getline(std::cin, line))
		lines.push_back(line);

	std::vector<std::vector<std::size_t>> tabstops = elastic::calc_tabstops(lines, tab_size, block_end_chars, [](std::string_view str) {
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
