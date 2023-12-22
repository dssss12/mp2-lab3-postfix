#include "postfix.h"
#include "postfix.cpp"
#include <gtest.h>


TEST(TPostfix, can_create_postfix_with_valid_infix)
{
	ASSERT_NO_THROW(TPostfix p("a+b*(c^d-e)"));
}

TEST(TPostfix, can_convert_infix_to_postfix)
{
	TPostfix p("a+b*(c^d-e)^(f+g*h)-i");
	ASSERT_EQ("abcd^e-fgh*+^*+i-", p.GetPostfix());
}

TEST(TPostfix, can_retrieve_infix_expression)
{
	TPostfix p("a+b*(c^d-e)^(f+g*h)-i");
	ASSERT_EQ("a+b*(c^d-e)^(f+g*h)-i", p.GetInfix());
}

TEST(TPostfix, can_calculate_correct_value)
{
	TPostfix p("a+b*c");
	map<char, double> values = { {'a', 1}, {'b', 2}, {'c', 3} };
	ASSERT_EQ(7, p.Calculate(values));
}

TEST(TPostfix, can_handle_parentheses)
{
	TPostfix p("(a+b)*c");
	ASSERT_EQ("ab+c*", p.GetPostfix());
}

TEST(TPostfix, can_handle_multiple_operators)
{
	TPostfix p("a+b*c-d/e");
	ASSERT_EQ("abc*+de/-", p.GetPostfix());
}

TEST(TPostfix, can_handle_default_operators) {
	TPostfix expr("a+b-c*d/e");
	map<char, double> variables = { {'a', 1}, {'b', 2} , {'c', 3} , {'d', 4}, {'e', 5} };
}

TEST(TPostfix, can_handle_power_operator)
{
	TPostfix p("a^b");
	ASSERT_EQ("ab^", p.GetPostfix());
}

TEST(TPostfix, can_handle_empty_expression)
{
	ASSERT_ANY_THROW(TPostfix p(""));
}

TEST(TPostfix, can_get_postfix)
{
	TPostfix expr("a+b");
	EXPECT_EQ(expr.GetPostfix(), "ab+");
}

TEST(TPostfix, can_get_postfix_with_parenthesis)
{
	TPostfix expr("a+b*c/(d-e)");
	EXPECT_EQ(expr.GetPostfix(), "abc*de-/+");
}

TEST(TPostfix, priority_works_well) 
{
	TPostfix expr("(a+b)*c/d-e^f");
	EXPECT_EQ(expr.GetPostfix(), "ab+c*d/ef^-");
}