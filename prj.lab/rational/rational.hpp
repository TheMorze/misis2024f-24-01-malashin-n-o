// 2024 by Polevoi Dmitry under Unlicense

#pragma once
#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <cstdint>
#include <iosfwd>

class Rational {
public:
    Rational() = default;
    Rational(const Rational&) = default;
    //Rational(Rational&&) = default;

    // Конструктор из целого числа: num/1
    explicit Rational(std::int32_t num) noexcept : num_(num) { }

    // Конструктор из числителя и знаменателя
    // Бросает исключение при нуле в знаменателе
    Rational(std::int32_t num, std::int32_t den);

    ~Rational() = default;

    Rational& operator=(const Rational&) = default;
    //Rational& operator=(Rational&&) = default;

    [[nodiscard]] std::int32_t num() const noexcept { return num_; }
    [[nodiscard]] std::int32_t den() const noexcept { return den_; }

    [[nodiscard]] bool operator==(const Rational& rhs) const noexcept;
    [[nodiscard]] bool operator!=(const Rational& rhs) const noexcept;
    [[nodiscard]] bool operator<(const Rational& rhs) const noexcept;
    [[nodiscard]] bool operator<=(const Rational& rhs) const noexcept;
    [[nodiscard]] bool operator>(const Rational& rhs) const noexcept;
    [[nodiscard]] bool operator>=(const Rational& rhs) const noexcept;

    [[nodiscard]] Rational operator-() const noexcept { return { -num_, den_ }; }

    Rational& operator+=(const Rational& rhs) noexcept;
    Rational& operator-=(const Rational& rhs) noexcept;
    Rational& operator*=(const Rational& rhs) noexcept;
    Rational& operator/=(const Rational& rhs);

    Rational& operator+=(std::int32_t rhs) noexcept;
    Rational& operator-=(std::int32_t rhs) noexcept;
    Rational& operator*=(std::int32_t rhs) noexcept;
    Rational& operator/=(std::int32_t rhs);

    // Форматированный вывод в поток ostrm: num/den
    std::ostream& WriteTo(std::ostream& ostrm) const noexcept;

    // Форматированный ввод из потока istrm: num/den
    std::istream& ReadFrom(std::istream& istrm) noexcept;

private:
    std::int32_t num_ = 0; //!< числитель
    std::int32_t den_ = 1; //!< знаменатель, всегда > 0 после Normalize()

    // Нормализация дроби: знак в числителе, сокращение к несократимой форме
    void Normalize() noexcept;
};

[[nodiscard]] Rational operator+(const Rational& lhs, const Rational& rhs) noexcept;
[[nodiscard]] Rational operator-(const Rational& lhs, const Rational& rhs) noexcept;
[[nodiscard]] Rational operator*(const Rational& lhs, const Rational& rhs) noexcept;
[[nodiscard]] Rational operator/(const Rational& lhs, const Rational& rhs);

[[nodiscard]] Rational operator+(const Rational& lhs, std::int32_t rhs) noexcept;
[[nodiscard]] Rational operator-(const Rational& lhs, std::int32_t rhs) noexcept;
[[nodiscard]] Rational operator*(const Rational& lhs, std::int32_t rhs) noexcept;
[[nodiscard]] Rational operator/(const Rational& lhs, std::int32_t rhs);

[[nodiscard]] Rational operator+(std::int32_t lhs, const Rational& rhs) noexcept;
[[nodiscard]] Rational operator-(std::int32_t lhs, const Rational& rhs) noexcept;
[[nodiscard]] Rational operator*(std::int32_t lhs, const Rational& rhs) noexcept;
[[nodiscard]] Rational operator/(std::int32_t lhs, const Rational& rhs);

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) noexcept;

std::istream& operator>>(std::istream& istrm, Rational& rhs) noexcept;

#endif
