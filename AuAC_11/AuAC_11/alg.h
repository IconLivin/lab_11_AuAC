#pragma once
#include <string>
#include <random>
#include<fstream>
#include <chrono>
#include <vector>


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
uint64_t First_Hash(std::string str, std::size_t degree, uint64_t p)
{
	uint64_t hash = 0;
	for (std::size_t i = 0; i < str.length(); ++i)
	{
		hash += pow(degree, i) * str[i];
	}
	return hash % p;
}

uint64_t Hash(std::string str, uint64_t prev_hash, std::size_t degree, uint64_t p)
{
	prev_hash = (prev_hash - str[0]) / degree + str[str.size() - 1] * pow(degree, static_cast<int>(str.size()) - 2);
	return prev_hash % p;
}

std::string::size_type RK_Match(const std::string& text, const std::string& pattern) {
	uint64_t p = 1000000017;
	std::random_device rd;
	std::mt19937 mersenne(rd());
	std::uniform_int_distribution<uint32_t> dist(pattern.size(), p);
	const std::size_t rk_const = dist(mersenne);

	const uint64_t pattern_hash = First_Hash(pattern, rk_const, p);
	uint64_t hash = First_Hash(text.substr(0, pattern.size()), rk_const, p);
	if (hash == pattern_hash) {
		if (!pattern.compare(text.substr(0, pattern.size()))) {
			return 0;
		}
	}
	for (std::size_t i = 0; i < static_cast<std::size_t>(text.size()) - static_cast<std::size_t>(pattern.size()); ++i) {
		std::string tmp = text.substr(i, pattern.size() + 1);
		hash = Hash(tmp, hash, rk_const, p);
		if (hash == pattern_hash) {
			if (!pattern.compare(tmp.substr(1, pattern.size()))) {
				return i + 1;
			}
		}
	}
	return std::string::npos;
}

std::string::size_type KMP_Match(const std::string& text, const std::string& pattern) {

	std::vector<int> pf;
	pf.resize(pattern.length());
	for (int k = 0, i = 1; i < pattern.length(); ++i) {
		while ((k > 0) && (pattern[i] != pattern[k])) {
			k = pf[k - 1];
		}
		if (pattern[i] == pattern[k]) {
			++k;
		}
		pf[i] = k;
	}

	for (int k = 0, i = 0; i < text.length(); ++i) {
		while ((k > 0) && (pattern[k] != text[i])) {
			k = pf[k - 1];
		}
		if (pattern[k] == text[i]) {
			++k;
		}
		if (k == pattern.length()) {
			return (i - pattern.length() + 1);
		}
	}
	
	return std::string::npos;
}

std::string::size_type Naive_Match(const std::string& text, const std::string& pattern) {
	const std::size_t text_length = text.length();
	const std::size_t pattern_length = pattern.length();
	for (std::size_t i = 0; i < text_length; ++i) {
		std::size_t j = 0, i1 = i;
		while (text[i1] == pattern[j]) {
			if (j == pattern_length - 1) {
				return i1 - pattern_length + 1;
			}
			++i1;
			++j;
		}
	}
	return std::string::npos;
}


void Generate_Text(std::string& text, int size) {//генерация текста
	auto now = std::chrono::high_resolution_clock::now();
	std::mt19937 generator(now.time_since_epoch().count());
	for (int i = 0; i < size; ++i) {
		text += char(generator() % 127);
	}
}
