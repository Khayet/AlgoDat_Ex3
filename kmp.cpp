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

    print_table(table); //for debugging purposes
}

bool match_string(std::string const& pat, std::string const& text, int& pos) {
    std::vector<int> next(pat.length()); //vector which saves backtracking distance
    fill_table(pat, next);

    int i{0}, j{0};
    while(i+j < text.length())
    {
        if (pat[j] == text[i+j]) { //corresponding characters of text and pattern match
            if (j == pat.length()-1) { //end of pattern reached
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

    if (pattern.length() > text.length()) {
        return 0;
    }
    if (argc != 2) {
        std::cout << "ERROR: Wrong number of arguments." << std::endl;
    }

    int pos{0};

    if (match_string(pattern, text, pos)) {
        std::cout << "Found pattern in text at position: " << pos << std::endl;
    } else {
        std::cout << "Did not find pattern in text." << std::endl;
    }

    return 0;
}
