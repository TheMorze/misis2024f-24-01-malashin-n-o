#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <stackl/stackl.hpp>
#include <doctest/doctest.h>

TEST_CASE("[stackl] - basic operations") {
    StackL s;
    CHECK(s.IsEmpty() == true);

    s.Push(10);
    s.Push(20);
    s.Push(30);

    CHECK(s.IsEmpty() == false);
    CHECK(s.Top() == 30);

    s.Pop();
    CHECK(s.Top() == 20);

    s.Pop();
    CHECK(s.Top() == 10);

    s.Pop();
    CHECK(s.IsEmpty() == true);

    // Попытка Top() на пустом стеке
    CHECK_THROWS(s.Top());
}

TEST_CASE("[stackl] - multiple push/pop") {
    StackL s;
    for (int i = 0; i < 100; ++i) {
        s.Push(static_cast<StackL::T>(i));
    }
    CHECK(s.Top() == 99);

    for (int i = 99; i >= 0; --i) {
        CHECK(s.Top() == i);
        s.Pop();
    }
    CHECK(s.IsEmpty() == true);
}

TEST_CASE("[stackl] - copy constructor") {
    StackL s;
    s.Push(1);
    s.Push(2);

    StackL s2 = s;
    CHECK(s2.Top() == 2);
    s2.Pop();
    CHECK(s2.Top() == 1);

    // проверяем, что оригинал не изменился
    CHECK(s.Top() == 2);
}

TEST_CASE("[stackl] - assignment") {
    StackL s;
    s.Push(42);
    s.Push(43);

    StackL s2;
    s2 = s;
    CHECK(s2.Top() == 43);
    s2.Pop();
    CHECK(s2.Top() == 42);

    // Оригинал не изменился
    CHECK(s.Top() == 43);

    // Самоприсваивание
    s2 = s2;
    CHECK(s2.Top() == 42);

    // Проверка очистки при присваивании пустого стека
    StackL s3;
    s3.Push(100);
    s3 = s2; // s2 не пуст
    CHECK(s3.Top() == 42);
    s3 = s;  // s не пуст
    CHECK(s3.Top() == 43);

    StackL s4;
    s4.Push(200);
    s4.Clear();
    s4 = s;
    CHECK(s4.Top() == 43);
}

TEST_CASE("[stackl] - move constructor and move assignment") {
    StackL s;
    s.Push(50);
    s.Push(60);

    // move-конструктор
    StackL s2 = std::move(s);
    CHECK(s2.Top() == 60);
    s2.Pop(); // теперь в s2 остался только 50
    CHECK(s2.Top() == 50);

    // move-присваивание
    StackL s3;
    s3.Push(70);
    s3.Push(80);

    s3 = std::move(s2);
    // Теперь s3 содержит те элементы, которые были в s2.
    // Перед move s2: top был 50, и это был единственный элемент.
    // Значит теперь в s3 один элемент: 50.
    CHECK(s3.Top() == 50);

    s3.Pop(); // удаляем 50, теперь s3 пустой
    CHECK(s3.IsEmpty() == true);
    // Проверять Top() сейчас нельзя, т.к. s3 пуст.
}

TEST_CASE("[stackl] - clear") {
    StackL s;
    s.Push(1);
    s.Push(2);
    s.Push(3);
    s.Clear();
    CHECK(s.IsEmpty());
    CHECK_THROWS(s.Top());
}
