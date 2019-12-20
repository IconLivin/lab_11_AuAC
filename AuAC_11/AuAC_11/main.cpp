#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <chrono>
#include <map>
#include <conio.h>
#include <fstream>

void ReadData(std::string path,std::string& str) 
{
	std::ifstream in;
	in.open(path);
	if (in.is_open())
	{
		while (!in.eof())
		{
			std::string tmp;
			getline(in, tmp);
			str += tmp+'\n';
		}
	}
	else
	{
		str = "";
	}
	in.close();
}
uint64_t First_Hash(std::string str, size_t degree,uint64_t p)
{
	uint64_t hash = 0;
	for (size_t i = 0; i < str.size(); ++i)
	{
		hash += pow(degree, i) * str[i];
	}
	return hash%p;
}

uint64_t Hash(std::string str, uint64_t prev_hash, size_t degree,uint64_t p)
{
	prev_hash = (prev_hash - str[0]) / degree + str[str.size() - 1] * pow(degree, static_cast<int>(str.size()) - 2);
	return prev_hash%p;
}

int RK_Match(std::string text, std::string pattern) {
	uint64_t p = 1000000017;
	std::random_device rd;
	std::mt19937 mersenne(rd());
	std::uniform_int_distribution<uint32_t> dist(pattern.size(), p);
	const size_t rk_const = dist(mersenne); 

	const uint64_t pattern_hash = First_Hash(pattern, rk_const,p);
	uint64_t hash = First_Hash(text.substr(0, pattern.size()), rk_const,p);
	if (hash == pattern_hash) {
		if (!pattern.compare(text.substr(0, pattern.size()))) {
			return 0;
		}
	}
	for (size_t i = 0; i < static_cast<size_t>(text.size()) - static_cast<size_t>(pattern.size()); ++i) {
		std::string tmp = text.substr(i, pattern.size() + 1);
		hash = Hash(tmp, hash, rk_const,p);
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

int main() {
	
	std::string path = "D:\\GithubProjects\\lab_11_AuAC\\doc\\Block.txt";
	std::ios_base::sync_with_stdio(false);
	std::string text;
	std::uint32_t pattern_length;
	//Generate_Text(text, 100000);
	ReadData(path, text);
	if (text.size() == 0)
	{
		std::cout << "Error read text" << std::endl;
		return -1;
	}
	std::cout << KMP_Match(text, ",") << std::endl;
	std::cout << Naive_Match(text, ",") << std::endl;
	std::cout << RK_Match(text, ",") << std::endl;
	std::cout << text << std::endl;
	//const int rk_const = 2;
	//for (pattern_length = 2; pattern_length < text.size(); ++pattern_length) {//перебираем всем множества до длины текста
	//	std::map<uint64_t, int> hashes;//таблица - [хеш, позиция в массиве]

	//	uint64_t hash = First_Hash(text.substr(0, pattern_length), rk_const);//первичное хеширование
	//	
	//	hashes.insert(std::make_pair(hash, 0));//добавляем первый ключ и нулевую позицию

	//	for (size_t i = 0; i + pattern_length < text.size(); ++i) {//пробегаем по всему тексту
	//		std::string tmp = text.substr(i, uint64_t(pattern_length) + 1);
	//		hash = Hash(tmp, hash, rk_const);//вычилсение хеша для следующей подстроки
	//		if (hashes.find(hash) == hashes.end()) {//проверяем есть ли такой хеш в мапе
	//			hashes.insert(std::make_pair(hash, i + 1));//если нет добавляем его и позицию
	//		}
	//		else if (tmp.substr(1, pattern_length).compare(text.substr(hashes[hash], pattern_length)) == 0) {//проверяем не совпали ли строчки
	//			std::cout << "Repeat!\n";
	//			continue;
	//		}
	//		else {//мы нашли коллизию
	//			std::cout << "COLLISION on length of pattern: " << pattern_length << std::endl;
	//			std::cout << "Hash:" << hash << std::endl;
	//			std::cout << "Position:" << i << std::endl;
	//			std::cout << text.substr(fmin(hashes[hash], i), fmax(hashes[hash], i) + pattern_length) << std::endl;
	//			std::cout << text.substr(i, pattern_length) << std::endl << text.substr(hashes[hash], pattern_length) << std::endl;
	//			for (std::map<uint64_t, int>::iterator i = hashes.begin(); i != hashes.end(); ++i) {
	//				std::cout << "Hash:" << i->first << std::endl;
	//			}
	//			_getch();
	//		}
	//	}
	//}
	
	return 0;
}