#include <rational/rational.hpp>

#include <stdexcept>
#include <limits>
#include <iostream>
#include <cstdint>

// Вспомогательная функция для вычисления НОД (наибольшего общего делителя)
// Используем алгоритм Евклида.
static std::int32_t gcd(std::int32_t a, std::int32_t b) noexcept {
    // Комментарий по-русски: приводим к положительным значениям,
    // т.к. gcd(a, b) == gcd(|a|, |b|)
    if (a < 0) { a = -a; }
    if (b < 0) { b = -b; }

    while (b != 0) {
        std::int32_t temp = a % b;
        a = b;
        b = temp;
    }
    return (a == 0) ? 1 : a;
}

Rational::Rational(const std::int32_t num, const std::int32_t den)
  : num_(num), den_(den) {
    // Комментарий по-русски: Проверяем, что знаменатель не ноль
    if (0 == den_) {
        throw std::invalid_argument("Zero denominator in Rational constructor");
    }
    Normalize();
}

void Rational::Normalize() noexcept {
    // Комментарий по-русски:
    // 1) Переносим знак в числитель.
    // 2) Находим НОД числителя и знаменателя.
    // 3) Делим числитель и знаменатель на НОД для сокращения дроби.
    // 4) Гарантируем, что знаменатель > 0.
    if (den_ < 0) {
        den_ = -den_;
        num_ = -num_;
    }
    const std::int32_t g = gcd(num_, den_);
    num_ /= g;
    den_ /= g;
}

// Операторы сравнения
bool Rational::operator==(const Rational& rhs) const noexcept {
    return (num_ == rhs.num_) && (den_ == rhs.den_);
}
bool Rational::operator!=(const Rational& rhs) const noexcept {
    return !(*this == rhs);
}

bool Rational::operator<(const Rational& rhs) const noexcept {
    // Комментарий по-русски:
    // Сравниваем (num_/den_) и (rhs.num_/rhs.den_) с помощью перекрёстного умножения,
    // чтобы не работать с числами с плавающей точкой:
    // a/b < c/d <=> a*d < c*b
    // Учитываем, что все знаменатели > 0 после Normalize()
    return static_cast<long long>(num_) * rhs.den_ < static_cast<long long>(rhs.num_) * den_;
}

bool Rational::operator<=(const Rational& rhs) const noexcept {
    return !(*this > rhs);
}

bool Rational::operator>(const Rational& rhs) const noexcept {
    return rhs < *this;
}

bool Rational::operator>=(const Rational& rhs) const noexcept {
    return !(*this < rhs);
}

// Арифметические операции с рациональными числами
Rational& Rational::operator+=(const Rational& rhs) noexcept {
    // (a/b) + (c/d) = (ad + bc) / bd
    num_ = num_ * rhs.den_ + rhs.num_ * den_;
    den_ = den_ * rhs.den_;
    Normalize();
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs) noexcept {
    // (a/b) - (c/d) = (ad - bc) / bd
    num_ = num_ * rhs.den_ - rhs.num_ * den_;
    den_ = den_ * rhs.den_;
    Normalize();
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs) noexcept {
    // (a/b) * (c/d) = (ac)/(bd)
    num_ = num_ * rhs.num_;
    den_ = den_ * rhs.den_;
    Normalize();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
    // (a/b) / (c/d) = (a/b)*(d/c) = (ad)/(bc)
    if (rhs.num_ == 0) {
        throw std::runtime_error("Division by zero in Rational operator/=");
    }
    num_ = num_ * rhs.den_;
    den_ = den_ * rhs.num_;
    if (den_ == 0) {
        throw std::runtime_error("Division leads to zero denominator in Rational");
    }
    Normalize();
    return *this;
}

// Арифметические операции с int32_t
Rational& Rational::operator+=(const int32_t rhs) noexcept {
    return (*this += Rational(rhs));
}

Rational& Rational::operator-=(const int32_t rhs) noexcept {
    return (*this -= Rational(rhs));
}

Rational& Rational::operator*=(const int32_t rhs) noexcept {
    return (*this *= Rational(rhs));
}

Rational& Rational::operator/=(const int32_t rhs) {
    if (rhs == 0) {
        throw std::runtime_error("Division by zero in Rational operator/=(int32_t)");
    }
    return (*this /= Rational(rhs));
}

// Свободные операторы для Rational
Rational operator+(const Rational& lhs, const Rational& rhs) noexcept {
    Rational result(lhs);
    result += rhs;
    return result;
}

Rational operator-(const Rational& lhs, const Rational& rhs) noexcept {
    Rational result(lhs);
    result -= rhs;
    return result;
}

Rational operator*(const Rational& lhs, const Rational& rhs) noexcept {
    Rational result(lhs);
    result *= rhs;
    return result;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    Rational result(lhs);
    result /= rhs;
    return result;
}

Rational operator+(const Rational& lhs, const int32_t rhs) noexcept {
    Rational result(lhs);
    result += rhs;
    return result;
}

Rational operator-(const Rational& lhs, const int32_t rhs) noexcept {
    Rational result(lhs);
    result -= rhs;
    return result;
}

Rational operator*(const Rational& lhs, const int32_t rhs) noexcept {
    Rational result(lhs);
    result *= rhs;
    return result;
}

Rational operator/(const Rational& lhs, const int32_t rhs) {
    Rational result(lhs);
    result /= rhs;
    return result;
}

Rational operator+(const int32_t lhs, const Rational& rhs) noexcept {
    Rational result(lhs);
    result += rhs;
    return result;
}

Rational operator-(const int32_t lhs, const Rational& rhs) noexcept {
    Rational result(lhs);
    // lhs - rhs = Rational(lhs) - rhs
    result -= rhs;
    return result;
}

Rational operator*(const int32_t lhs, const Rational& rhs) noexcept {
    Rational result(lhs);
    result *= rhs;
    return result;
}

Rational operator/(const int32_t lhs, const Rational& rhs) {
    Rational result(lhs);
    result /= rhs;
    return result;
}

// Форматированный вывод в поток: num/den
std::ostream& Rational::WriteTo(std::ostream& ostrm) const noexcept {
    // Комментарий по-русски:
    // Выводим в формате num/den
    ostrm << num_ << '/' << den_;
    return ostrm;
}

// Форматированный ввод из потока: ожидается формат num/den
std::istream& Rational::ReadFrom(std::istream& istrm) noexcept {
    // Комментарий по-русски:
    // Пытаемся считать два целых и символ '/', если ошибка - фейлим поток
    std::int32_t n(0), d(1);
    char slash = '\0';
    std::istream::sentry s(istrm);
    if (s) {
        const auto pos = istrm.tellg();
        if ((istrm >> n) && (istrm >> slash) && (slash == '/') && (istrm >> d)) {
            if (d == 0) {
                // Недопустимая дробь
                istrm.setstate(std::ios_base::failbit);
                return istrm;
            }
            num_ = n;
            den_ = d;
            Normalize();
        } else {
            // Формат не распознан, откат позиции
            istrm.clear(std::ios_base::failbit);
            istrm.seekg(pos);
        }
    }
    return istrm;
}

// Перегрузка операторов ввода/вывода << и >>
std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) noexcept {
    return rhs.WriteTo(ostrm);
}

std::istream& operator>>(std::istream& istrm, Rational& rhs) noexcept {
    return rhs.ReadFrom(istrm);
}
