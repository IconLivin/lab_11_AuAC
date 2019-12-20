#include "pch.h"
#include "..\AuAC_11\alg.h"
TEST(alg, naive_algorithm_return_position_true_position){
	std::string text = "we need more COH";
	std::string pattern = "more";
	int pos=Naive_Match(text, pattern);
	EXPECT_EQ(pos,8);
}

TEST(alg, naive_algorithm_return_error) {
	std::string text = "we need more COH";
	std::string pattern = "less";
	int pos = Naive_Match(text, pattern);
	EXPECT_EQ(pos, -1);
}

TEST(alg, kmp_algorithm_return_position_true_position) {
	std::string text = "we need more COH";
	std::string pattern = "more";
	int pos = KMP_Match(text, pattern);
	EXPECT_EQ(pos, 8);
}

TEST(alg, kmp_algorithm_return_error) {
	std::string text = "we need more COH";
	std::string pattern = "less";
	int pos = KMP_Match(text, pattern);
	EXPECT_EQ(pos, -1);
}

TEST(alg, rk_algorithm_return_position_true_position) {
	std::string text = "we need more COH";
	std::string pattern = "more";
	int pos = RK_Match(text, pattern);
	EXPECT_EQ(pos, 8);
}

TEST(alg, rk_algorithm_return_error) {
	std::string text = "we need more COH";
	std::string pattern = "less";
	int pos = RK_Match(text, pattern);
	EXPECT_EQ(pos, -1);
}