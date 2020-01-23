#include <string>
#include <iostream>
#include <chrono>
#include <fstream>
#include "alg.h"



int main() {
	std::string path = "../../doc/test2.txt";
	std::ios_base::sync_with_stdio(false);
	std::string text;
	std::ofstream out;
	out.open("OUTPUT.txt");
	ReadData(path, text);
	if (text.length() == 0)
	{
		std::cout << "Error read text" << std::endl;
		return -1;
	}
	std::string pattern;
	for (int i = 10000; i < 20000; i += 1000) {
		Generate_Text(text, i);
		pattern = text.substr(i - i/4, i / 4);
		out << i << std::endl;
		auto start = std::chrono::high_resolution_clock::now();
		std::string::size_type naive = Naive_Match(text, pattern);
		auto end = std::chrono::high_resolution_clock::now();
		auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		out << float(time)<< std::endl;
		start = std::chrono::high_resolution_clock::now();
		std::string::size_type kmp = KMP_Match(text, pattern);
		end = std::chrono::high_resolution_clock::now();
		time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		out << float(time) << std::endl;
		out << 0 << std::endl;
	}
	
	return 0;
}