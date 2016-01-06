#include <iostream>
#include <string>
#include <vector>

void print_table(std::vector<int>& table) {
	for (auto i : table) {
		std::cout << i << ", ";
	}
	std::cout << std::endl;
}

void fill_table(std::string const& word, std::vector<int>& table) {
	// refer to: https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
	int pos{2}, index{0};

	table[0] = -1;
	table[1] = 0;

	std::cout << "Still working" << std::endl;

	while (pos < word.length()) {
		if (word[pos-1] == word[index]) {
			table[pos] = index + 1;
			++index;
			++pos;
		} else if (index > 0) {
			index = table[index];
		} else {
			std::cout << "pos = " << pos << std::endl;
			table[pos] = 0;
			std::cout << "table[2] = " << table[2] << std::endl;
			++pos;
		}
	}

	print_table(table);
}

bool match_string(std::string const& pat, std::string const& text, int& pos) {
	std::vector<int> next(pat.length());
	std::cout << "Still working" << std::endl;
	fill_table(pat, next);

	std::cout << "Still working" << std::endl;

	int i{0}, j{0};
	while(i+j < text.length()) 
	{
		std::cout << "Still working; i = " << i << std::endl;
		if (pat[j] == text[i+j]) {
			if (j == pat.length()-1) {
				pos = i;
				return true;
			}
			++j;
		} else {
			if (next[i] > -1) {
				std::cout << "j = " << j << std::endl;
				i = i + j - next[j];
				std::cout << "j = " << j << std::endl;
				j = next[j];
				std::cout << "next[j] = " << next[j] << std::endl;
			} else {
				j = 0;
				++i;
			}
		}
	}

	std::cout << "Still working" << std::endl;
	
	return false;
}

int main(int argc, char* argv[]) {
	std::string pattern{argv[1]};
	std::string text{argv[2]};

	std::cout << "pattern length: " << pattern.length() << std::endl;

	if (pattern.length() > text.length()) {
		std::cout << "Pattern longer than text." << std::endl;
		return 0;
	}

	int pos{0};

	if (match_string(pattern, text, pos)) {
		std::cout << "Found pattern in text at position: " << pos << std::endl;
	} else {
		std::cout << "Did not find pattern in text." << std::endl;
	}

	return 0;
}
