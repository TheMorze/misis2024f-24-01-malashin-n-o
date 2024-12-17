#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <arrayt/arrayt.hpp>
#include <doctest/doctest.h>
#include <string>

TEST_CASE("[arrayt<int>] - default constructor") {
    ArrayT<int> arr;
    CHECK(arr.Size() == 0);
}

TEST_CASE("[arrayt<int>] - constructor with size") {
    CHECK_THROWS(ArrayT<int>(0));  // Нулевой размер должен бросать исключение
    CHECK_THROWS(ArrayT<int>(-1)); // Отрицательный размер тоже должен бросать

    ArrayT<int> arr(5);
    CHECK(arr.Size() == 5);
    for (std::ptrdiff_t i = 0; i < arr.Size(); ++i) {
        CHECK(arr[i] == 0);
    }
}

TEST_CASE("[arrayt<int>] - copy constructor") {
    ArrayT<int> arr1(3);
    arr1[0] = 10;
    arr1[1] = 20;
    arr1[2] = 30;

    ArrayT<int> arr2 = arr1;
    CHECK(arr2.Size() == arr1.Size());
    for (std::ptrdiff_t i = 0; i < arr2.Size(); ++i) {
        CHECK(arr2[i] == arr1[i]);
    }

    // Изменение arr1 не затрагивает arr2
    arr1[0] = 99;
    CHECK(arr2[0] == 10);
}

TEST_CASE("[arrayt<int>] - operator=") {
    ArrayT<int> arr1(2);
    arr1[0] = 42;
    arr1[1] = 43;

    ArrayT<int> arr2(1);
    arr2 = arr1;
    CHECK(arr2.Size() == 2);
    CHECK(arr2[0] == 42);
    CHECK(arr2[1] == 43);

    // Самоприсваивание
    arr2 = arr2;
    CHECK(arr2.Size() == 2);
    CHECK(arr2[0] == 42);
}

TEST_CASE("[arrayt<int>] - Resize") {
    ArrayT<int> arr(2);
    arr[0] = 10;
    arr[1] = 20;

    arr.Resize(4);
    CHECK(arr.Size() == 4);
    CHECK(arr[0] == 10);
    CHECK(arr[1] == 20);
    CHECK(arr[2] == 0);
    CHECK(arr[3] == 0);

    arr.Resize(1);
    CHECK(arr.Size() == 1);
    CHECK(arr[0] == 10);

    CHECK_THROWS(arr.Resize(-1)); // Отрицательный размер должен бросить исключение
}

TEST_CASE("[arrayt<int>] - Insert") {
    ArrayT<int> arr(3);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    // Вставляем в начало
    arr.Insert(0, 5);
    CHECK(arr.Size() == 4);
    CHECK(arr[0] == 5);
    CHECK(arr[1] == 10);
    CHECK(arr[2] == 20);
    CHECK(arr[3] == 30);

    // Вставляем в конец
    arr.Insert(arr.Size(), 40);
    CHECK(arr.Size() == 5);
    CHECK(arr[4] == 40);

    // Вставляем в середину
    arr.Insert(2, 15);
    CHECK(arr.Size() == 6);
    CHECK(arr[0] == 5);
    CHECK(arr[1] == 10);
    CHECK(arr[2] == 15);
    CHECK(arr[3] == 20);
}

TEST_CASE("[arrayt<int>] - Remove") {
    ArrayT<int> arr(5);
    for (std::ptrdiff_t i = 0; i < arr.Size(); ++i) {
        arr[i] = static_cast<int>((i + 1) * 10); // 10,20,30,40,50
    }

    // Удаляем первый элемент
    arr.Remove(0);
    CHECK(arr.Size() == 4);
    CHECK(arr[0] == 20);
    CHECK(arr[1] == 30);
    CHECK(arr[2] == 40);
    CHECK(arr[3] == 50);

    // Удаляем последний элемент
    arr.Remove(arr.Size() - 1);
    CHECK(arr.Size() == 3);
    CHECK(arr[0] == 20);
    CHECK(arr[1] == 30);
    CHECK(arr[2] == 40);

    // Удаляем средний элемент
    arr.Remove(1);
    CHECK(arr.Size() == 2);
    CHECK(arr[0] == 20);
    CHECK(arr[1] == 40);

    // Неверный индекс
    CHECK_THROWS(arr.Remove(-1));
    CHECK_THROWS(arr.Remove(arr.Size()));
}

TEST_CASE("[arrayt<int>] - operator[] const correctness") {
    const ArrayT<int> arr(3);
    CHECK(arr[0] == 0);
    CHECK(arr[1] == 0);
    CHECK(arr[2] == 0);
    CHECK_THROWS(arr[-1]);
    CHECK_THROWS(arr[3]);
}

// Дополнительные тесты с другим типом, например std::string
TEST_CASE("[arrayt<std::string>] - basic ops") {
    ArrayT<std::string> arr(2);
    CHECK(arr.Size() == 2);
    CHECK(arr[0].empty());
    CHECK(arr[1].empty());

    arr[0] = "Hello";
    arr[1] = "World";

    ArrayT<std::string> arr2 = arr;
    CHECK(arr2.Size() == 2);
    CHECK(arr2[0] == "Hello");
    CHECK(arr2[1] == "World");

    arr2.Insert(1, "Beautiful");
    CHECK(arr2.Size() == 3);
    CHECK(arr2[0] == "Hello");
    CHECK(arr2[1] == "Beautiful");
    CHECK(arr2[2] == "World");

    arr2.Remove(1);
    CHECK(arr2.Size() == 2);
    CHECK(arr2[0] == "Hello");
    CHECK(arr2[1] == "World");
}
