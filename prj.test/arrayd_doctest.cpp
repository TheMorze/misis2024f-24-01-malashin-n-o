#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <arrayd/arrayd.hpp>
#include <doctest/doctest.h>

TEST_CASE("[arrayd] - default constructor") {
    ArrayD arr;
    CHECK(arr.Size() == 0);
}

TEST_CASE("[arrayd] - constructor with size") {
    CHECK_THROWS(ArrayD(0));  // Нулевой размер должен выбросить исключение
    CHECK_THROWS(ArrayD(-1)); // Отрицательный размер тоже

    ArrayD arr(5);
    CHECK(arr.Size() == 5);
    for (std::ptrdiff_t i = 0; i < arr.Size(); ++i) {
        CHECK(arr[i] == 0.0);
    }
}

TEST_CASE("[arrayd] - copy constructor") {
    ArrayD arr1(3);
    arr1[0] = 1.1;
    arr1[1] = 2.2;
    arr1[2] = 3.3;

    ArrayD arr2 = arr1;
    CHECK(arr2.Size() == arr1.Size());
    for (std::ptrdiff_t i = 0; i < arr2.Size(); ++i) {
        CHECK(arr2[i] == arr1[i]);
    }

    // Изменение arr1 не влияет на arr2
    arr1[0] = 9.9;
    CHECK(arr2[0] == 1.1);
}

TEST_CASE("[arrayd] - operator=") {
    ArrayD arr1(2);
    arr1[0] = 42.0;
    arr1[1] = 43.0;

    ArrayD arr2(1);
    arr2 = arr1;
    CHECK(arr2.Size() == 2);
    CHECK(arr2[0] == 42.0);
    CHECK(arr2[1] == 43.0);

    // Самоприсваивание
    arr2 = arr2;
    CHECK(arr2.Size() == 2);
    CHECK(arr2[0] == 42.0);
}

TEST_CASE("[arrayd] - Resize") {
    ArrayD arr(2);
    arr[0] = 10.0;
    arr[1] = 20.0;

    arr.Resize(4);
    CHECK(arr.Size() == 4);
    CHECK(arr[0] == 10.0);
    CHECK(arr[1] == 20.0);
    CHECK(arr[2] == 0.0);
    CHECK(arr[3] == 0.0);

    arr.Resize(1);
    CHECK(arr.Size() == 1);
    CHECK(arr[0] == 10.0);

    CHECK_THROWS(arr.Resize(-1)); // Отрицательный размер
}

TEST_CASE("[arrayd] - Insert") {
    ArrayD arr(3);
    arr[0] = 10.0;
    arr[1] = 20.0;
    arr[2] = 30.0;

    // Вставляем в начало
    arr.Insert(0, 5.0);
    CHECK(arr.Size() == 4);
    CHECK(arr[0] == 5.0);
    CHECK(arr[1] == 10.0);
    CHECK(arr[2] == 20.0);
    CHECK(arr[3] == 30.0);

    // Вставляем в конец
    arr.Insert(arr.Size(), 40.0);
    CHECK(arr.Size() == 5);
    CHECK(arr[4] == 40.0);

    // Вставляем в середину
    arr.Insert(2, 15.0);
    CHECK(arr.Size() == 6);
    CHECK(arr[0] == 5.0);
    CHECK(arr[1] == 10.0);
    CHECK(arr[2] == 15.0);
    CHECK(arr[3] == 20.0);
}

TEST_CASE("[arrayd] - Remove") {
    ArrayD arr(5);
    for (std::ptrdiff_t i = 0; i < arr.Size(); ++i) {
        arr[i] = (double)(i+1)*10; // 10,20,30,40,50
    }

    // Удаляем первый элемент
    arr.Remove(0);
    CHECK(arr.Size() == 4);
    CHECK(arr[0] == 20.0);
    CHECK(arr[1] == 30.0);
    CHECK(arr[2] == 40.0);
    CHECK(arr[3] == 50.0);

    // Удаляем последний элемент
    arr.Remove(arr.Size()-1);
    CHECK(arr.Size() == 3);
    CHECK(arr[0] == 20.0);
    CHECK(arr[1] == 30.0);
    CHECK(arr[2] == 40.0);

    // Удаляем средний элемент
    arr.Remove(1);
    CHECK(arr.Size() == 2);
    CHECK(arr[0] == 20.0);
    CHECK(arr[1] == 40.0);

    // Неверный индекс
    CHECK_THROWS(arr.Remove(-1));
    CHECK_THROWS(arr.Remove(arr.Size()));
}

TEST_CASE("[arrayd] - operator[] const correctness") {
    const ArrayD arr(3);
    CHECK(arr[0] == 0.0);
    CHECK(arr[1] == 0.0);
    CHECK(arr[2] == 0.0);
    CHECK_THROWS(arr[-1]);
    CHECK_THROWS(arr[3]);
}
