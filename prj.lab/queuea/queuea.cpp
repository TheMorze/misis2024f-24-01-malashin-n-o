#include <queuea/queuea.hpp>
#include <algorithm>
#include <stdexcept>

std::ptrdiff_t QueueA::Count() const {
  if (IsEmpty()) {
    return 0;
  }
  return (tail_ >= head_) ? (tail_ - head_ + 1)
                          : (size_ - head_ + tail_ + 1);
}

QueueA::QueueA(const QueueA& src) {
  std::ptrdiff_t count = src.Count();
  if (count > 0) {
    size_ = count; // Просто берём размер равный количеству элементов
    data_ = new T[size_];
    if (src.head_ <= src.tail_) {
      std::copy(src.data_ + src.head_, src.data_ + src.tail_ + 1, data_);
    } else {
      std::ptrdiff_t first_part = src.size_ - src.head_;
      std::copy(src.data_ + src.head_, src.data_ + src.size_, data_);
      std::copy(src.data_, src.data_ + src.tail_ + 1, data_ + first_part);
    }
    head_ = 0;
    tail_ = count - 1;
  }
}

QueueA& QueueA::operator=(const QueueA& src) {
  if (this != &src) {
    Clear();
    delete[] data_;
    data_ = nullptr;
    size_ = 0;

    std::ptrdiff_t count = src.Count();
    if (count > 0) {
      size_ = count;
      data_ = new T[size_];
      if (src.head_ <= src.tail_) {
        std::copy(src.data_ + src.head_, src.data_ + src.tail_ + 1, data_);
      } else {
        std::ptrdiff_t first_part = src.size_ - src.head_;
        std::copy(src.data_ + src.head_, src.data_ + src.size_, data_);
        std::copy(src.data_, src.data_ + src.tail_ + 1, data_ + first_part);
      }
      head_ = 0;
      tail_ = count - 1;
    } else {
      head_ = -1;
      tail_ = -1;
    }
  }
  return *this;
}

void QueueA::Swap(QueueA&& src) noexcept {
  std::swap(size_, src.size_);
  std::swap(data_, src.data_);
  std::swap(head_, src.head_);
  std::swap(tail_, src.tail_);
}

QueueA::QueueA(QueueA&& src) noexcept {
  Swap(std::move(src));
}

QueueA& QueueA::operator=(QueueA&& src) {
  if (this != &src) {
    Clear();
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    Swap(std::move(src));
  }
  return *this;
}

QueueA::~QueueA() {
  delete[] data_;
}

bool QueueA::IsEmpty() const noexcept {
  return head_ < 0;
}

void QueueA::Pop() noexcept {
  if (!IsEmpty()) {
    if (head_ == tail_) {
      head_ = -1;
      tail_ = -1;
    } else {
      head_ = (head_ + 1) % size_;
    }
  }
}

void QueueA::Push(const T val) {
  if (data_ == nullptr) {
    // Пустая очередь, создаём
    size_ = 2;
    data_ = new T[size_];
    head_ = 0;
    tail_ = 0;
    data_[0] = val;
    return;
  }

  if (IsEmpty()) {
    // Очередь была пустой
    head_ = 0;
    tail_ = 0;
    data_[0] = val;
    return;
  }

  // Проверяем, есть ли место
  if ((tail_ + 1) % size_ == head_) {
    // Нет места, расширяем в 2 раза
    std::ptrdiff_t c = Count();
    std::ptrdiff_t old_size = size_;
    size_ = old_size * 2;
    T* new_data = new T[size_];

    // Перекопируем данные линейно в начало new_data
    if (head_ <= tail_) {
      std::copy(data_ + head_, data_ + tail_ + 1, new_data);
    } else {
      std::ptrdiff_t first_part = old_size - head_;
      std::copy(data_ + head_, data_ + old_size, new_data);
      std::copy(data_, data_ + tail_ + 1, new_data + first_part);
    }

    delete[] data_;
    data_ = new_data;
    head_ = 0;
    tail_ = c - 1;  // до добавления нового элемента хвост указывает на последний старый элемент

    // Добавляем новый элемент
    tail_ = (tail_ + 1) % size_;
    data_[tail_] = val;
  } else {
    // Места достаточно
    tail_ = (tail_ + 1) % size_;
    data_[tail_] = val;
  }
}

QueueA::T& QueueA::Top() {
  if (IsEmpty()) {
    throw std::logic_error("QueueA::Top - empty queue");
  }
  return data_[head_];
}

const QueueA::T& QueueA::Top() const {
  if (IsEmpty()) {
    throw std::logic_error("QueueA::Top - empty queue");
  }
  return data_[head_];
}

void QueueA::Clear() noexcept {
  head_ = -1;
  tail_ = -1;
}
