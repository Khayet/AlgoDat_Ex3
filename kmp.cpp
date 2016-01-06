#include <iostream>
#include <string>

bool match_string(std::string const& pat, std::string const& text, int& pos) {
	
	int j{0};
	for (int i=0; i < text.length(); ++i) {
		if (text.substr(j, j+pat.length()) == pat) {
			pos = j;
			return true;
		} else {
			j += pat.length();
			std::cout << j << "\n";
		}
	}
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
