#include <iostream>

struct complex {
    double real;
    double imag;

    // Конструкторы
    complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // Оператор сложения
    complex operator+(const complex& rhs) const {
        return complex(real + rhs.real, imag + rhs.imag);
    }

    complex& operator+=(const complex& rhs) {
        real += rhs.real;
        imag += rhs.imag;
        return *this;
    }

    // Оператор вычитания
    complex operator-(const complex& rhs) const {
        return complex(real - rhs.real, imag - rhs.imag);
    }

    complex& operator-=(const complex& rhs) {
        real -= rhs.real;
        imag -= rhs.imag;
        return *this;
    }

    // Оператор умножения
    complex operator*(const complex& rhs) const {
        return complex(
            real * rhs.real - imag * rhs.imag,
            real * rhs.imag + imag * rhs.real
        );
    }

    complex& operator*=(const complex& rhs) {
        double temp_real = real * rhs.real - imag * rhs.imag;
        imag = real * rhs.imag + imag * rhs.real;
        real = temp_real;
        return *this;
    }

    // Оператор деления
    complex operator/(const complex& rhs) const {
        double denom = rhs.real * rhs.real + rhs.imag * rhs.imag;
        if (denom == 0) {
            std::cerr << "Ошибка: деление на ноль\n";
            return complex();
        }
        return complex(
            (real * rhs.real + imag * rhs.imag) / denom,
            (imag * rhs.real - real * rhs.imag) / denom
        );
    }

    complex& operator/=(const complex& rhs) {
        double denom = rhs.real * rhs.real + rhs.imag * rhs.imag;
        if (denom == 0) {
            std::cerr << "Ошибка: деление на ноль\n";
            real = imag = 0;
            return *this;
        }
        double temp_real = (real * rhs.real + imag * rhs.imag) / denom;
        imag = (imag * rhs.real - real * rhs.imag) / denom;
        real = temp_real;
        return *this;
    }

    // Операторы сравнения
    bool operator==(const complex& rhs) const {
        return real == rhs.real && imag == rhs.imag;
    }

    bool operator!=(const complex& rhs) const {
        return !(*this == rhs);
    }

    // Дружественные функции ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const complex& c);
    friend std::istream& operator>>(std::istream& is, complex& c);
};

// Оператор вывода
std::ostream& operator<<(std::ostream& os, const complex& c) {
    os << "(" << c.real << " + " << c.imag << "i)";
    return os;
}

// Оператор ввода
std::istream& operator>>(std::istream& is, complex& c) {
    is >> c.real >> c.imag;
    return is;
}

int main() {
    complex num1, num2;

    std::cout << "Введите действительную и мнимую часть первого числа: ";
    std::cin >> num1;
    std::cout << "Введите действительную и мнимую часть второго числа: ";
    std::cin >> num2;

    complex sum = num1 + num2;
    std::cout << "Сумма: " << sum << "\n";

    complex difference = num1 - num2;
    std::cout << "Разность: " << difference << "\n";

    complex product = num1 * num2;
    std::cout << "Произведение: " << product << "\n";

    complex quotient = num1 / num2;
    std::cout << "Частное: " << quotient << "\n";

    return 0;
}
