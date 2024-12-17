#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <queuea/queuea.hpp>
#include <doctest/doctest.h>

TEST_CASE("[queuea] - empty queue") {
    QueueA q;
    CHECK(q.IsEmpty() == true);
    CHECK_THROWS_AS(q.Top(), std::logic_error); // top on empty
    q.Pop(); // pop on empty should be no-op
    CHECK(q.IsEmpty() == true);
    q.Clear(); // clear on empty also no-op
    CHECK(q.IsEmpty() == true);
}

TEST_CASE("[queuea] - single element") {
    QueueA q;
    q.Push(42);
    CHECK(q.IsEmpty() == false);
    CHECK(q.Top() == 42);
    q.Pop();
    CHECK(q.IsEmpty() == true);
    CHECK_THROWS_AS(q.Top(), std::logic_error);
}

TEST_CASE("[queuea] - multiple elements push/pop") {
    QueueA q;
    q.Push(10);
    q.Push(20);
    q.Push(30);
    CHECK(q.Top() == 10);

    q.Pop(); // remove 10
    CHECK(q.Top() == 20);
    q.Pop(); // remove 20
    CHECK(q.Top() == 30);
    q.Pop(); // remove 30
    CHECK(q.IsEmpty() == true);
}

TEST_CASE("[queuea] - continuous push/pop") {
    QueueA q;
    // Push 0..9
    for (int i = 0; i < 10; ++i) {
        q.Push(static_cast<QueueA::T>(i));
    }
    // Pop first 5
    for (int i = 0; i < 5; ++i) {
        CHECK(q.Top() == i);
        q.Pop();
    }
    // Now push 10..14
    for (int i = 10; i < 15; ++i) {
        q.Push(static_cast<QueueA::T>(i));
    }

    // Queue should have 5..9 followed by 10..14
    // 5 elements popped, so first top is now 5
    for (int expected = 5; expected < 15; ++expected) {
        CHECK(q.Top() == expected);
        q.Pop();
    }
    CHECK(q.IsEmpty() == true);
}

TEST_CASE("[queuea] - large number of elements to force resize") {
    QueueA q;
    // Push a bunch of elements to ensure we resize multiple times
    const int N = 200;
    for (int i = 0; i < N; ++i) {
        q.Push(static_cast<QueueA::T>(i));
    }
    // Check first element
    CHECK(q.Top() == 0);

    // Pop half
    for (int i = 0; i < N/2; ++i) {
        CHECK(q.Top() == i);
        q.Pop();
    }

    // Now push another batch
    for (int i = N; i < N + 50; ++i) {
        q.Push(static_cast<QueueA::T>(i));
    }

    // Now we should have N/2 elements popped, queue should start at N/2
    int expected = N/2;
    while (!q.IsEmpty()) {
        CHECK(q.Top() == expected);
        q.Pop();
        expected++;
    }
    CHECK(expected == N + 50);
}

TEST_CASE("[queuea] - clear") {
    QueueA q;
    q.Push(1);
    q.Push(2);
    q.Clear();
    CHECK(q.IsEmpty() == true);
    CHECK_THROWS_AS(q.Top(), std::logic_error);
    q.Push(42);
    CHECK(q.Top() == 42);
}

TEST_CASE("[queuea] - copy constructor") {
    QueueA q;
    q.Push(10);
    q.Push(20);
    q.Push(30);

    QueueA q2 = q;
    CHECK(q2.Top() == 10);
    q2.Pop();
    CHECK(q2.Top() == 20);
    // ensure original unchanged
    CHECK(q.Top() == 10);
}

TEST_CASE("[queuea] - copy assignment") {
    QueueA q;
    for (int i = 0; i < 5; ++i) {
        q.Push(static_cast<QueueA::T>(i));
    }

    QueueA q2;
    q2 = q;
    CHECK(q2.Top() == 0);
    q2.Pop();
    CHECK(q2.Top() == 1);

    // original unchanged
    CHECK(q.Top() == 0);

    // assign empty to q2
    QueueA q3;
    q2 = q3;
    CHECK(q2.IsEmpty() == true);
}

TEST_CASE("[queuea] - move constructor") {
    QueueA q;
    q.Push(1);
    q.Push(2);

    QueueA q2 = std::move(q);
    CHECK(q2.Top() == 1);
    q2.Pop();
    CHECK(q2.Top() == 2);
    q2.Pop();
    CHECK(q2.IsEmpty() == true);
    CHECK_THROWS_AS(q2.Top(), std::logic_error);

    // original should be empty after move
    CHECK_THROWS_AS(q.Top(), std::logic_error);
    CHECK(q.IsEmpty() == true);
}

TEST_CASE("[queuea] - move assignment") {
    QueueA q;
    q.Push(100);
    q.Push(101);

    QueueA q2;
    q2.Push(200);

    q2 = std::move(q);
    CHECK(q2.Top() == 100);
    q2.Pop();
    CHECK(q2.Top() == 101);
    q2.Pop();
    CHECK(q2.IsEmpty() == true);

    // q should be empty after move
    CHECK_THROWS_AS(q.Top(), std::logic_error);
    CHECK(q.IsEmpty() == true);
}
