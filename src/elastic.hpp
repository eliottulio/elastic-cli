#pragma once

#include <string>
#include <vector>
#include <functional>

namespace elastic {
	std::vector<std::vector<std::size_t>> calc_tabstops(	std::vector<std::string> lines,
		std::size_t min_tabsize = 4,
		std::string_view block_begin_chars = ":{",
		std::function<std::size_t(std::string_view)> get_str_size = [](std::string_view str) {return str.size();});
}
