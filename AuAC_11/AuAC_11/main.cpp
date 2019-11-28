#include <string>
#include <vector>
#include <iostream>

uint64_t First_Hash(std::string str, size_t degree)
{
	uint64_t hash = 0;
	for (size_t i = 0; i < str.size(); ++i)
	{
		hash += pow(degree, i) * str[i];
	}
	return hash;
}

uint64_t Hash(std::string str, uint64_t prev_hash, size_t degree)
{
	prev_hash = (prev_hash - str[0]) / degree + str[str.size() - 1] * pow(degree, static_cast<int>(str.size()) - 2);
	return prev_hash;
}

int RK_Match(std::string text, std::string pattern) {
	size_t rk_const = 2;
	const uint64_t pattern_hash = First_Hash(pattern, rk_const);
	uint64_t hash = First_Hash(text.substr(0, pattern.size()), rk_const);
	if (hash == pattern_hash) {
		if (!pattern.compare(text.substr(0, pattern.size()))) {
			return 0;
		}
	}
	for (size_t i = 0; i < static_cast<size_t>(text.size()) - static_cast<size_t>(pattern.size()); ++i) {
		std::string tmp = text.substr(i, pattern.size() + 1);
		hash = Hash(tmp, hash, rk_const);
		if (hash == pattern_hash) {
			if (!pattern.compare(tmp.substr(1,pattern.size()))) {
				return i + 1;
			}
		}
	}
	return -1;
}

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
	int rk_pos = RK_Match(text, find_it);
	std::cout << kmp_pos << std::endl << naive_pos << std::endl << rk_pos << std::endl;
	
	return 0;
}