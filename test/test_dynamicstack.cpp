#include "DynamicStack.h"

#include <gtest.h>

TEST(DynamicStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(DynamicStack<int> test(3));
}

TEST(DynamicStack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(DynamicStack<int> test(-1));
}


TEST(DynamicStack, stack_creates_empty)
{
	DynamicStack<int> example(3);
	EXPECT_EQ(true, example.isEmpty());
}

TEST(DynamicStack, can_add_value_to_stack)
{
	DynamicStack<int> example(3);
	ASSERT_NO_THROW(example.push(2););
}

TEST(DynamicStack, can_get_value_from_stack_using_pop)
{
	DynamicStack<int> example(3);
	example.push(2);
	EXPECT_EQ(2, example.pop());
}

TEST(DynamicStack, can_get_value_from_stack_using_top)
{
	DynamicStack<int> example(3);
	example.push(2);
	EXPECT_EQ(2, example.top());
}

TEST(DynamicStack, can_copy_stack) {
	DynamicStack<int> example1(3);
	DynamicStack<int> example2(4);
	example1.push(10);
	example2 = example1;
	EXPECT_EQ(10, example2.pop());
}

TEST(DynamicStack, stack_expands_when_runs_out_of_space)
{
	DynamicStack<int> example(3);
	example.push(2);
	example.push(2);
	example.push(2);
	ASSERT_NO_THROW(example.push(3));
}


