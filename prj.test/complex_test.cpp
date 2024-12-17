#include <complex/complex.hpp>
#include <iostream>

int main() {
    Complex num1, num2;

    std::cout << "Введите действительную и мнимую часть первого числа в формате {re,im}: ";
    std::cin >> num1;
    std::cout << "Введите действительную и мнимую часть второго числа в формате {re,im}: ";
    std::cin >> num2;

    Complex sum = num1 + num2;
    std::cout << "Сумма: " << sum << "\n";

    Complex difference = num1 - num2;
    std::cout << "Разность: " << difference << "\n";

    Complex product = num1 * num2;
    std::cout << "Произведение: " << product << "\n";

    Complex quotient = num1 / num2;
    std::cout << "Частное: " << quotient << "\n";

    return 0;
}
