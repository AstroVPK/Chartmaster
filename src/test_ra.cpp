#include<cmath>
#include <iostream>

#include "gtest/gtest.h"
#include "ra.hpp"

template <typename T>
class RATests : public testing::Test {
	public:
		coordinates::RA<T> ra;
  		void SetUp(const T& deg) {
    		this->ra = coordinates::RA<T>(deg);
  		}

  		template <typename I>
  		void SetUp(I const & hour, I const & min, T const & sec) {
    		this->ra = coordinates::RA<T>(hour, min, sec);
  		}
};

using MyTypes = ::testing::Types<float, double, long double>;

using MyIntTypes = ::testing::Types<char, short, int, long>;

TYPED_TEST_SUITE(RATests, MyTypes);

TYPED_TEST(RATests, ValueInitialization) {
  EXPECT_EQ(this->ra.value(), 0);
}

TYPED_TEST(RATests, DirectInitialization00) {
  int hrs = 5, min = 33;
  float sec = 30;
  this->SetUp(hrs, min, sec);
  if (static_cast<TypeParam>(hrs) == hrs) {
    EXPECT_EQ(this->ra.value(), 83.375);
  }
}

TYPED_TEST(RATests, DirectInitialization01) {
  int hrs = 29, min = 33;
  float sec = 30;
  this->SetUp(hrs, min, sec);
  if (static_cast<TypeParam>(hrs) == hrs) {
    EXPECT_EQ(this->ra.value(), 83.375);
  }
}