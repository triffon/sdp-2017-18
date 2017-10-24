#include "UnitTestFramework.h"
#include <iostream>
#include "arithmetic.h"

TEST_CASE("Arithmetic", CalculateRPNExampleFromSlides) {
  Arithmetic a;
  Assert::AreEqual(a.calculateRPN("12+345/-*"), 6.6);
}

TEST_CASE("Arithmetic", CalculateRPNConstant) {
  Arithmetic a;
  Assert::AreEqual(a.calculateRPN("5"), 5);
}

TEST_CASE("Arithmetic", CalculateRPNOneOperation) {
  Arithmetic a;
  Assert::AreEqual(a.calculateRPN("35+"), 8);
}

TEST_CASE("Arithmetic", ConvertToRPNExampleFromSlides) {
  Arithmetic a;
  Assert::AreEqual(a.toRPN("(1+2)*(3-4/5)"), "12+345/-*");
}

TEST_CASE("Arithmetic", ConvertToRPNExampleFromSlides2) {
  Arithmetic a;
  Assert::AreEqual(a.toRPN("(1+2)*(3/4-5)"), "12+34/5-*");
}

TEST_CASE("Arithmetic", ConvertToRPNConstant) {
  Arithmetic a;
  Assert::AreEqual(a.toRPN("5"), "5");
}

TEST_CASE("Arithmetic", ConvertToRPNOneOperation) {
  Arithmetic a;
  Assert::AreEqual(a.toRPN("3+5"), "35+");
}

TEST_CASE("Arithmetic", ConvertToRPNPlusDivide) {
  Arithmetic a;
  Assert::AreEqual(a.toRPN("3+5/7"), "357/+");
}

TEST_CASE("Arithmetic", ConvertToRPNDividePlus) {
  Arithmetic a;
  Assert::AreEqual(a.toRPN("3/5+7"), "35/7+");
}

TEST_CASE("Arithmetic", ConvertToRPNParenPlusDivide) {
  Arithmetic a;
  Assert::AreEqual(a.toRPN("(3+5)/7"), "35+7/");
}

TEST_CASE("Arithmetic", ConvertToRPNSamePriority) {
  Arithmetic a;
  Assert::AreEqual(a.toRPN("3/4/5"), "34/5/");
}

