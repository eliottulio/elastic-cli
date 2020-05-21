#include <iostream>
#include <string>
#include <vector>

std::vector<std::vector<std::size_t>> calc_tabstops(std::vector<std::string> lines, std::size_t min_tabsize = 4);

int main() {
	std::vector<std::string> lines;

	std::string line;
	while (std::getline(std::cin, line))
		lines.push_back(line);

	std::vector<std::vector<std::size_t>> tabstops = calc_tabstops(lines);

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

std::vector<std::vector<std::size_t>> calc_tabstops(std::vector<std::string> lines, std::size_t min_tabsize) {
	std::vector<std::vector<std::size_t>> tabstops;

	std::size_t max_tab_nb = 0;

	// Get all tab positions:
	for (const std::string& line : lines) {
		tabstops.push_back(std::vector<std::size_t>());

		std::size_t prev_i = -1;
		std::size_t i;

		while ((i = line.find_first_of('\t', prev_i + 1)) != std::string::npos) {
			tabstops.back().push_back(i - prev_i);
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

			// Calc tab length:
			std::size_t tab_size = min_tabsize;
			std::size_t start_line = line;
			while (line < tabstops.size() && tabstops[line].size() > tab_nb) {
				if (tabstops[line][tab_nb] > tab_size)
					tab_size = tabstops[line][tab_nb];
				line++;
			}
			// Assign tab length:
			for (std::size_t line_ = start_line; line_ < line; line_++)
				tabstops[line_][tab_nb] = tab_size;
		}
	}

	return tabstops;
}
/*
	Things to test the program:

----------------------------------------------------------------------------------------------

	Consumed	Produced	Net total
Dirt:	250000	0	-250000
Meal Lice:	0	5000	5000
Phosphorite:	20000	0	-20000
Pincha Peppernut:	0	10000	10000
Polluted Water:	700000	0	-700000

----------------------------------------------------------------------------------------------

	--------|	--------------------------	|--------
	--------|	Welcome to Elastic Notepad	|--------
	--------|	--------------------------	|--------
	--------|		|--------
	--------|	This is your scratch file.	|--------
	--------|	It's initialised with this	|--------
	--------|	text so you can play with	|--------
	--------|	elastic tabstops.	|--------
	--------|		|--------
	--------|	--------------------------	|--------


int someDemoCode(	int start,
	int length)
{
	x()	// try making	//
	print("hello!")	// this comment	//
	doSomethingComplicated()	// a bit longer	//
	for (i in range(start, length))
	{
		if (isValid(i))
		{
			count++
		}
	}
	return count
}


You can use elastic tabstops with tables and TSV files too

Title	Author	Publisher	Year
Generation X	Douglas Coupland	Abacus	1995
Informagic	Jean-Pierre Petit	John Murray Ltd	1982
The Cyberiad	Stanislaw Lem	Harcourt Publishers Ltd	1985
The Selfish Gene	Richard Dawkins	Oxford University Press	2006
*/
