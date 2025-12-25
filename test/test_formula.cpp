#include "Formula.h"

#include <gtest.h>

TEST(Formula, can_create_formula)
{
  ASSERT_NO_THROW(Formula ex("3+4+2"));
}

TEST(Formula, can_check_valid_brackets)
{
	Formula example("(2+3)*(5-2)");
	EXPECT_EQ(true, example.validateBrackets());
}

TEST(Formula, can_check_invalid_brackets)
{
	Formula example("(2+3)*((5-2)");
	EXPECT_EQ(false, example.validateBrackets());
}

TEST(Formula, can_check_valid_operations)
{
	Formula example("(2+3)*(5-2)");
	EXPECT_EQ(true, example.validateOperations());
}

TEST(Formula, can_check_invalid_operations)
{
	Formula example("(2+3)*(5-2-)");
	EXPECT_EQ(false, example.validateOperations());
}

TEST(Formula, can_convert_to_postfix)
{
	Formula example("(2+3)*(5-2)");
	example.convertToPostfix();
	EXPECT_EQ("2 3 + 5 2 - *", example.getPostfix());
}
TEST(Formula, throws_when_postfix_not_converted) {
	Formula example("(2+3)*(5-2)");
	ASSERT_ANY_THROW(example.getPostfix());
}

TEST(Formula, can_calculate_postfix)
{
	Formula example("(2+3)*(100-97)");
	example.convertToPostfix();
	EXPECT_EQ(15, example.Calculate());
}

TEST(Formula, works_with_negative_values) {
	Formula example("((10+(-15))-5)*5/2");
	example.convertToPostfix();
	EXPECT_EQ(-25, example.Calculate());
}





