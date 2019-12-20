#pragma once
#include <string>
#include <conio.h>
#include <random>
#include<fstream>
#include <chrono>
void ReadData(std::string path, std::string& str)
{
	std::ifstream in;
	in.open(path);
	if (in.is_open())
	{
		while (!in.eof())
		{
			std::string tmp;
			getline(in, tmp);
			str += tmp + '\n';
		}
	}
	else
	{
		str = "";
	}
	in.close();
}
uint64_t First_Hash(std::string str, size_t degree, uint64_t p)
{
	uint64_t hash = 0;
	for (size_t i = 0; i < str.size(); ++i)
	{
		hash += pow(degree, i) * str[i];
	}
	return hash % p;
}

uint64_t Hash(std::string str, uint64_t prev_hash, size_t degree, uint64_t p)
{
	prev_hash = (prev_hash - str[0]) / degree + str[str.size() - 1] * pow(degree, static_cast<int>(str.size()) - 2);
	return prev_hash % p;
}

int RK_Match(std::string text, std::string pattern) {
	uint64_t p = 1000000017;
	std::random_device rd;
	std::mt19937 mersenne(rd());
	std::uniform_int_distribution<uint32_t> dist(pattern.size(), p);
	const size_t rk_const = dist(mersenne);

	const uint64_t pattern_hash = First_Hash(pattern, rk_const, p);
	uint64_t hash = First_Hash(text.substr(0, pattern.size()), rk_const, p);
	if (hash == pattern_hash) {
		if (!pattern.compare(text.substr(0, pattern.size()))) {
			return 0;
		}
	}
	for (size_t i = 0; i < static_cast<size_t>(text.size()) - static_cast<size_t>(pattern.size()); ++i) {
		std::string tmp = text.substr(i, pattern.size() + 1);
		hash = Hash(tmp, hash, rk_const, p);
		if (hash == pattern_hash) {
			if (!pattern.compare(tmp.substr(1, pattern.size()))) {
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
			k = pie[size_t(k - 1)];

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


void Generate_Text(std::string& text, int size) {//генерация текста
	auto now = std::chrono::high_resolution_clock::now();
	std::mt19937 generator(now.time_since_epoch().count());
	for (int i = 0; i < size; ++i) {
		text += char(generator() % 127);
	}
}
