#include <string>
#include <vector>
#include <iostream>

int KMP_Match(std::string text, std::string pattern) {
	const size_t n = text.length();
	const size_t m = pattern.length();

	//PREFIX FUNCTION
	std::vector<size_t> pie(m);
	for (size_t q = 1; q < m; ++q) {
		size_t j = pie[q - 1];
		while ((j > 0) && (pattern[j] != pattern[q])) {
			j = pie[j - 1];
		}
		if (pattern[j] == pattern[q]) {
			++j;
		}
		pie[q] = j;
	}

	//MATCHING
	for (int k = 0, i = 0; i < n; ++i)
	{
		while ((k > 0) && (pattern[k] != text[i]))
			k = pie[k - 1];

		if (pattern[k] == text[i])
			k++;

		if (k == m)
			return (i - m + 1);
	}
	return -1;
}

int Naive_Match(std::string text, std::string pattern) {
	const size_t text_length = text.length();
	const size_t pattern_length = pattern.length();
	for (size_t i = 0; i < text_length; ++i) {
		size_t j = 0, i1 = i;
		while (text[i1] == pattern[j]) {
			if (j == pattern_length - 1) {
				return i1 - pattern_length + 1;
			}
			++i1;
			++j;
		}
	}
	return -1;
}


int main() {
	std::ios_base::sync_with_stdio(false);
	std::string text,find_it;
	std::cout << "Insert text:";
	std::cin >> text;
	std::cout << "What to find:";
	std::cin >> find_it;
	int kmp_pos = KMP_Match(text, find_it);
	int naive_pos = Naive_Match(text, find_it);
	kmp_pos == naive_pos ? std::cout << "Ok!\n" : std::cout << "Bad :(\n";
	
	return 0;
}