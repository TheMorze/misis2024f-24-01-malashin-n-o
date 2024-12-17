#include <complex/complex.hpp>
#include <iostream>
#include <limits>
#include <cmath>
#include <stdexcept>

// Унарный минус.
Complex Complex::operator-() const noexcept {
    return Complex(-re, -im);
}

// Сравнение на равенство.
bool Complex::operator==(const Complex& rhs) const noexcept {
    // eps - некоторое маленькое число для сравнения с учётом неточности double.
    const double eps = 2 * std::numeric_limits<double>::epsilon();
    return (std::fabs(re - rhs.re) <= eps) && (std::fabs(im - rhs.im) <= eps);
}

// Сравнение на неравенство.
bool Complex::operator!=(const Complex& rhs) const noexcept {
    return !(*this == rhs);
}

// Присваивающее сложение с комплексным числом.
Complex& Complex::operator+=(const Complex& rhs) noexcept {
    re += rhs.re;
    im += rhs.im;
    return *this;
}

// Присваивающее сложение с вещественным числом.
Complex& Complex::operator+=(const double rhs) noexcept {
    re += rhs;
    return *this;
}

// Присваивающее вычитание комплексного числа.
Complex& Complex::operator-=(const Complex& rhs) noexcept {
    re -= rhs.re;
    im -= rhs.im;
    return *this;
}

// Присваивающее вычитание вещественного числа.
Complex& Complex::operator-=(const double rhs) noexcept {
    re -= rhs;
    return *this;
}

// Присваивающее умножение на комплексное число.
Complex& Complex::operator*=(const Complex& rhs) noexcept {
    // (a+bi)*(c+di) = (ac - bd) + (ad+bc)i
    const double newRe = re * rhs.re - im * rhs.im;
    const double newIm = re * rhs.im + im * rhs.re;
    re = newRe;
    im = newIm;
    return *this;
}

// Присваивающее умножение на вещественное число.
Complex& Complex::operator*=(const double rhs) noexcept {
    re *= rhs;
    im *= rhs;
    return *this;
}

// Присваивающее деление на комплексное число.
Complex& Complex::operator/=(const Complex& rhs) {
    // (a+bi)/(c+di) = ((a+bi)*(c-di)) / (c^2 + d^2)
    const double denom = rhs.re * rhs.re + rhs.im * rhs.im;
    if (denom == 0.0) {
        throw std::runtime_error("Division by zero in complex division");
    }

    const double newRe = (re * rhs.re + im * rhs.im) / denom;
    const double newIm = (im * rhs.re - re * rhs.im) / denom;

    re = newRe;
    im = newIm;
    return *this;
}

// Присваивающее деление на вещественное число.
Complex& Complex::operator/=(const double rhs) {
    if (rhs == 0.0) {
        throw std::runtime_error("Division by zero in complex division");
    }
    re /= rhs;
    im /= rhs;
    return *this;
}

// Форматированный вывод в поток
std::ostream& Complex::WriteTo(std::ostream& ostrm) const noexcept {
    ostrm << leftBrace << re << separator << im << rightBrace;
    return ostrm;
}

// Форматированный ввод из потока
std::istream& Complex::ReadFrom(std::istream& istrm) noexcept {
    // Формат: {re,im}
    char lbrace = 0;
    char comma = 0;
    char rbrace = 0;
    double realVal = 0.0;
    double imagVal = 0.0;

    // Сохраняем состояние потока, чтобы при неудаче можно было вернуть исходное.
    std::istream::sentry s(istrm);
    if (s) {
        const auto pos = istrm.tellg();
        if ((istrm >> lbrace) && (lbrace == leftBrace) &&
            (istrm >> realVal) && (istrm >> comma) && (comma == separator) &&
            (istrm >> imagVal) && (istrm >> rbrace) && (rbrace == rightBrace)) {
            re = realVal;
            im = imagVal;
        } else {
            // Если формат неправильный, откатим позицию потока.
            istrm.clear(std::ios_base::failbit);
            istrm.seekg(pos);
        }
    }

    return istrm;
}

//-----------------------------------
// Реализации свободных операторов
//-----------------------------------

Complex operator+(const Complex& lhs, const Complex& rhs) noexcept {
    Complex result(lhs);
    return (result += rhs);
}

Complex operator+(const Complex& lhs, const double rhs) noexcept {
    Complex result(lhs);
    return (result += rhs);
}

Complex operator+(const double lhs, const Complex& rhs) noexcept {
    Complex result(rhs);
    return (result += lhs);
}

Complex operator-(const Complex& lhs, const Complex& rhs) noexcept {
    Complex result(lhs);
    return (result -= rhs);
}

Complex operator-(const Complex& lhs, const double rhs) noexcept {
    Complex result(lhs);
    return (result -= rhs);
}

Complex operator-(const double lhs, const Complex& rhs) noexcept {
    // lhs - rhs = (lhs - rhs.re) + (-rhs.im)i
    // Можно сделать так: Complex temp(lhs, 0.0); return temp - rhs;
    Complex temp(lhs, 0.0);
    return temp - rhs;
}

Complex operator*(const Complex& lhs, const Complex& rhs) noexcept {
    Complex result(lhs);
    return (result *= rhs);
}

Complex operator*(const Complex& lhs, const double rhs) noexcept {
    Complex result(lhs);
    return (result *= rhs);
}

Complex operator*(const double lhs, const Complex& rhs) noexcept {
    Complex result(rhs);
    return (result *= lhs);
}

Complex operator/(const Complex& lhs, const Complex& rhs) {
    Complex result(lhs);
    return (result /= rhs);
}

Complex operator/(const Complex& lhs, const double rhs) {
    Complex result(lhs);
    return (result /= rhs);
}

Complex operator/(const double lhs, const Complex& rhs) {
    // (lhs + 0i)/rhs
    Complex temp(lhs, 0.0);
    return temp / rhs;
}
