#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <rational/rational.hpp>
#include <doctest/doctest.h>

// Тесты конструктора, операторов сравнения и арифметики
TEST_CASE("[rational] - construction") {
    CHECK(Rational() == Rational(0, 1));
    CHECK(Rational(3) == Rational(3, 1));
    CHECK_THROWS(Rational(1, 0));
}

TEST_CASE("[rational] - normalization") {
    CHECK(Rational(2,4) == Rational(1,2));
    CHECK(Rational(-2,-4) == Rational(1,2));
    CHECK(Rational(-2,4) == Rational(-1,2));
    CHECK(Rational(2,-4) == Rational(-1,2));
}

TEST_CASE("[rational] - equality and comparison") {
    Rational a(1,2);
    Rational b(2,4);
    Rational c(3,4);

    CHECK(a == b);
    CHECK(a != c);

    CHECK(a < c);
    CHECK(a <= b);
    CHECK(c > a);
    CHECK(c >= b);
}

TEST_CASE("[rational] - arithmetic with rationals") {
    Rational a(1,2);
    Rational b(3,4);

    CHECK(a + b == Rational(5,4));  // (1/2)+(3/4) = (2/4+3/4)=5/4
    CHECK(a - b == Rational(-1,4)); // (1/2)-(3/4) = (2/4-3/4)=-1/4
    CHECK(a * b == Rational(3,8));  // (1/2)*(3/4)=3/8
    CHECK(a / b == Rational(2,3));  // (1/2)/(3/4)=(1/2)*(4/3)=4/6=2/3
}

TEST_CASE("[rational] - arithmetic with integers") {
    Rational a(1,2);

    CHECK(a + 1 == Rational(3,2));     // 1/2 + 1 = 1/2+2/2=3/2
    CHECK(a - 1 == Rational(-1,2));    // 1/2 - 1 = 1/2-2/2=-1/2
    CHECK(a * 2 == Rational(1,1));     // (1/2)*2=2/2=1
    CHECK(a / 2 == Rational(1,4));     // (1/2)/2=(1/2)*(1/2)=1/4

    CHECK(1 + a == Rational(3,2));
    CHECK(1 - a == Rational(1,2));     // 1 - 1/2= 2/2-1/2=1/2
    CHECK(2 * a == Rational(1,1));
    CHECK(2 / a == Rational(4,1));     // 2/(1/2)=2*(2/1)=4
}

TEST_CASE("[rational] - unary minus") {
    Rational a(1,2);
    CHECK(-a == Rational(-1,2));
}

TEST_CASE("[rational] - i/o") {
    // Тестируем ввод/вывод
    {
        std::ostringstream oss;
        oss << Rational(3,4);
        CHECK(oss.str() == "3/4");
    }

    {
        std::istringstream iss("3/4");
        Rational r;
        iss >> r;
        CHECK(r == Rational(3,4));
    }

    {
        std::istringstream iss("invalid");
        Rational r;
        iss >> r; // не должно менять r при неудаче
        CHECK(iss.fail());
        CHECK(r == Rational()); // остается (0/1)
    }

    {
        std::istringstream iss("2/0");
        Rational r;
        iss >> r;
        CHECK(iss.fail()); // Невалидный ввод
    }
}
