#include <complex/complex.hpp>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_CASE("[complex] - ctor") {
    CHECK(Complex() == Complex(0.0, 0.0));
    CHECK(Complex(2.0) == Complex(2.0, 0.0));
    CHECK(Complex(3.0, 4.0) == Complex(3.0, 4.0));
}

TEST_CASE("[complex] - equality and inequality") {
    Complex c1(3.0,4.0);
    Complex c2(3.0 + 2 * std::numeric_limits<double>::epsilon(),4.0);
    Complex c3(1.0,-2.0);
    CHECK(c1 == c2); // с учётом eps
    CHECK(c1 != c3);
}

TEST_CASE("[complex] - addition") {
    Complex c1(3.0,4.0);
    Complex c2(1.0,-2.0);
    CHECK((c1 + c2) == Complex(4.0,2.0));
    CHECK((c1 + 5.0) == Complex(8.0,4.0));
    CHECK((5.0 + c2) == Complex(6.0,-2.0));
}

TEST_CASE("[complex] - subtraction") {
    Complex c1(3.0,4.0);
    Complex c2(1.0,-2.0);
    CHECK((c1 - c2) == Complex(2.0,6.0));
    CHECK((c1 - 1.0) == Complex(2.0,4.0));
    CHECK((10.0 - c2) == Complex(9.0,2.0));
}

TEST_CASE("[complex] - multiplication") {
    Complex c1(3.0,4.0);
    Complex c2(1.0,-2.0);
    CHECK((c1 * c2) == Complex(11.0,-2.0));
    CHECK((c1 * 2.0) == Complex(6.0,8.0));
    CHECK((3.0 * c2) == Complex(3.0,-6.0));
}

TEST_CASE("[complex] - division") {
    Complex c1(3.0,4.0);
    Complex c2(1.0,-2.0);
    CHECK((c1 / c2) == Complex(-1.0,2.0));
    CHECK((c1 / 2.0) == Complex(1.5,2.0));
    CHECK((10.0 / c2) == Complex(2.0,4.0));
}