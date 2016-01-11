#include <iostream>
#include <string>
#include <vector>

void print_table(std::vector<int>& table) {
    for (auto i : table) {
        std::cout << i << ", ";
    }
    std::cout << std::endl;
}

bool arg_error(std::string const& pattern, std::string const& text, int argc) {
    if (pattern.length() > text.length()) {
    	std::cout 
    		<< "Pattern is shorter than text - please enter the pattern as first argument and the text as second." 
    		<< std::endl;
        return 0;
    }
    if (argc != 3) {
        std::cout << "ERROR: Wrong number of arguments." << std::endl;
        return 0;
    }
	return false;
}

void fill_table(std::string const& word, std::vector<int>& table) {
    int pos{2}, index{0};

    table[0] = -1; //marks start of array
    table[1] = 0;

    while (pos < word.length()) {
        if (word[pos-1] == word[index]) {
            table[pos] = index + 1;
            ++index;
            ++pos;
        } else if (index > 0) {
            index = table[index];
        } else {
            table[pos] = 0;
            ++pos;
        }
    }
}

bool match_string(std::string const& pat, std::string const& text, int& pos) {
    std::vector<int> next(pat.length()); //vector which saves backtracking distance
    fill_table(pat, next);

    int i{0}, j{0};
    while(i+j < text.length())
    {
        if (pat[j] == text[i+j]) { //corresponding characters of text and pattern match
            if (j == pat.length()-1) { //found match
                pos = i;
                return true;
            }
            ++j;
        } else {
            if (next[i] > 0) { //backtrack according to next
                i = i + j - next[j];
                j -= next[j];
            } else { //move pattern one step
                j = 0;
                ++i;
            }
        }
    }

    return false;
}

int main(int argc, char* argv[]) {
    std::string pattern{argv[1]};
    std::string text{argv[2]};

    if (arg_error(pattern, text, argc)) return 0;

    int pos{0}, match_count{0};

    for (int k=0; k < text.length()-pattern.length(); ++k) {
    	if (match_string(pattern, text.substr(k), pos)) {
			std::cout << "Found pattern in text at position: " << k+pos << std::endl;    	
    		k += pos;
    		++match_count;
    	}
    }

    if (0 == match_count) {
    	std::cout << "Did not find pattern in the text." << std::endl; 
    } else {
    	std::cout << "Found " << match_count << " matches in the text." << std::endl;
    }

    return 0;
}
