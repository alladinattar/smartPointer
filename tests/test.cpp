// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>
#include "header.hpp"
TEST(Example, EmptyTest) { EXPECT_TRUE(true); }

/*TEST(SharedPtr, constructor1) {
  SharedPtr<int> constr1;
  ASSERT_EQ(*constr1, nullptr);
}*/

TEST(SharedPtr, constructorWithArgument) {
  int a = 8;
  SharedPtr<int> var(&a);
  ASSERT_EQ(*var, a);
}

TEST(SharedPtr, constructorWithLValLink){
  int a = 8;
  SharedPtr var(&a);
  SharedPtr l(var);
  ASSERT_EQ(var.use_count(), 2);
}

TEST(SharedPtr, constructorWithRValLink){
  int a = 9;
  SharedPtr var(&a);
  SharedPtr r(std::move(var));
  ASSERT_EQ(var.use_count(),2);
}