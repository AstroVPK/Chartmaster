#include<cmath>
#include <iostream>

#include "gtest/gtest.h"
#include "dec.hpp"

template <typename T>
class DecTests : public testing::Test {
	public:
		coordinates::Dec<T> dec;
  		void SetUp(const T& deg) {
    		this->dec = coordinates::Dec<T>(deg);
  		}

  		template <typename I>
  		void SetUp(I const & deg, I const & arcmin, T const & arcsec) {
    		this->dec = coordinates::Dec<T>(deg, arcmin, arcsec);
  		}
};

using MyTypes = ::testing::Types<float, double, long double>;

using MyIntTypes = ::testing::Types<char, short, int, long>;

TYPED_TEST_SUITE(DecTests, MyTypes);

TYPED_TEST(DecTests, ValueInitialization) {
  EXPECT_EQ(this->dec.value(), 0);
}

TYPED_TEST(DecTests, DirectInitialization00) {
  int deg = 5, arcmin = 33;
  float arcsec = 18;
  this->SetUp(deg, arcmin, arcsec);
  if (static_cast<TypeParam>(deg) == deg) {
    EXPECT_EQ(this->dec.value(), 5.555);
  }
}

TYPED_TEST(DecTests, DirectInitialization01) {
  int hrs = 65, min = 33;
  float sec = 36;
  this->SetUp(hrs, min, sec);
  if (static_cast<TypeParam>(hrs) == hrs) {
    EXPECT_EQ(this->dec.value(), 65.56);
  }
}