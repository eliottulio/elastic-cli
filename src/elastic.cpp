#include <string>
#include <vector>
#include <functional>

#include "elastic.hpp"

std::vector<std::vector<std::size_t>> elastic::calc_tabstops(	std::vector<std::string> lines,
	std::size_t min_tabsize,
	std::string_view block_begin_chars,
	std::function<std::size_t(std::string_view)> get_str_size) {

	std::vector<std::vector<std::size_t>> tabstops;

	std::size_t max_tab_nb = 0;

	// Get all tab positions:
	for (const std::string& line : lines) {
		tabstops.push_back(std::vector<std::size_t>());

		std::size_t prev_i = -1;
		std::size_t i;

		while ((i = line.find_first_of('\t', prev_i + 1)) != std::string::npos) {
			tabstops.back().push_back(get_str_size(std::string_view(line).substr(prev_i + 1, i - prev_i - 1)) + get_str_size(" "));
			prev_i = i;
		}

		// Get number of tabs in line with most tabs:
		if (tabstops.size() > max_tab_nb)
			max_tab_nb = tabstops.size();
	}

	// Calculate actual tabstops:
	for (std::size_t tab_nb = 0; tab_nb < max_tab_nb; tab_nb++) {
		for (std::size_t line = 0; line < tabstops.size(); line++) {
			// Skip lines that aren't long enough:
			while (line < tabstops.size() && tabstops[line].size() <= tab_nb)
				line++;

			// Calc max tab length:
			std::size_t tab_size = min_tabsize;
			std::size_t start_line = line;
			// Loops until the end of the block:
			while (line < tabstops.size() && tabstops[line].size() > tab_nb && (line == start_line || block_begin_chars.find_first_of(lines[line - 1].back()) == std::string::npos)) {
				if (tabstops[line][tab_nb] > tab_size)
					tab_size = tabstops[line][tab_nb];
				line++;
			}
			// Assign tab length:
			for (std::size_t line_ = start_line; line_ < line; line_++)
				tabstops[line_][tab_nb] = tab_size;

			// If block over because start of code block, start new block on next line, not skipping one:
			if (line != start_line && block_begin_chars.find_first_of(lines[line - 1].back()) != std::string::npos)
				line -= 1;
		}
	}

	return tabstops;
}
