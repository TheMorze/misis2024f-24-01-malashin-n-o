#ifndef RATIONAL
#define RATIONAL

#include <iostream>

struct Rational {
    int numerator;
    int denominator;

    // Конструктор
    Rational(int num = 0, int denom = 1) : numerator(num), denominator(denom) {
        if (denominator == 0) {
            std::cerr << "Ошибка: знаменатель не может быть нулевым\n";
            numerator = 0;
            denominator = 1;
        } else {
            reduce();
        }
    }

    // Функция для вычисления наибольшего общего делителя (НОД)
    int gcd(int a, int b) const {
        a = (a < 0) ? -a : a; // Модуль числа a
        b = (b < 0) ? -b : b; // Модуль числа b
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    // Функция сокращения дроби
    void reduce() {
        int divisor = gcd(numerator, denominator);
        numerator /= divisor;
        denominator /= divisor;
        // Обеспечиваем положительный знаменатель
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    // Оператор сложения
    Rational operator+(const Rational& rhs) const {
        int num = numerator * rhs.denominator + rhs.numerator * denominator;
        int denom = denominator * rhs.denominator;
        return Rational(num, denom);
    }

    Rational& operator+=(const Rational& rhs) {
        numerator = numerator * rhs.denominator + rhs.numerator * denominator;
        denominator *= rhs.denominator;
        reduce();
        return *this;
    }

    // Оператор вычитания
    Rational operator-(const Rational& rhs) const {
        int num = numerator * rhs.denominator - rhs.numerator * denominator;
        int denom = denominator * rhs.denominator;
        return Rational(num, denom);
    }

    Rational& operator-=(const Rational& rhs) {
        numerator = numerator * rhs.denominator - rhs.numerator * denominator;
        denominator *= rhs.denominator;
        reduce();
        return *this;
    }

    // Оператор умножения
    Rational operator*(const Rational& rhs) const {
        int num = numerator * rhs.numerator;
        int denom = denominator * rhs.denominator;
        return Rational(num, denom);
    }

    Rational& operator*=(const Rational& rhs) {
        numerator *= rhs.numerator;
        denominator *= rhs.denominator;
        reduce();
        return *this;
    }

    // Оператор деления
    Rational operator/(const Rational& rhs) const {
        if (rhs.numerator == 0) {
            std::cerr << "Ошибка: деление на ноль\n";
            return Rational(0, 1);
        }
        int num = numerator * rhs.denominator;
        int denom = denominator * rhs.numerator;
        return Rational(num, denom);
    }

    Rational& operator/=(const Rational& rhs) {
        if (rhs.numerator == 0) {
            std::cerr << "Ошибка: деление на ноль\n";
            numerator = 0;
            denominator = 1;
        } else {
            numerator *= rhs.denominator;
            denominator *= rhs.numerator;
            reduce();
        }
        return *this;
    }

    // Операторы сравнения
    bool operator==(const Rational& rhs) const {
        return numerator == rhs.numerator && denominator == rhs.denominator;
    }

    bool operator!=(const Rational& rhs) const {
        return !(*this == rhs);
    }

    // Операторы ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Rational& r);
    friend std::istream& operator>>(std::istream& is, Rational& r);
};

// Оператор вывода
std::ostream& operator<<(std::ostream& os, const Rational& r) {
    os << r.numerator;
    if (r.denominator != 1) {
        os << '/' << r.denominator;
    }
    return os;
}

// Оператор ввода
std::istream& operator>>(std::istream& is, Rational& r) {
    int num, denom = 1;
    char ch;
    is >> num;
    if (is.peek() == '/') {
        is >> ch >> denom;
    }
    r = Rational(num, denom);
    return is;
}

#endif

