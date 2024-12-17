#pragma once
#ifndef QUEUEA_QUEUEA_HPP_20241207
#define QUEUEA_QUEUEA_HPP_20241207

#include <cstddef>
#include <cstdint>

class QueueA final {
public:
  using T = std::uint8_t;

  QueueA() = default;

  QueueA(const QueueA& src);

  QueueA(QueueA&& src) noexcept;

  ~QueueA();

  QueueA& operator=(const QueueA& src);

  QueueA& operator=(QueueA&& src);

  [[nodiscard]] bool IsEmpty() const noexcept;

  void Pop() noexcept;

  void Push(const T val);

  [[nodiscard]] T& Top();

  [[nodiscard]] const T& Top() const;

  void Clear() noexcept;

private:
  std::ptrdiff_t size_ = 0;  //!< размер буфера
  T* data_ = nullptr;        //!< буфер
  std::ptrdiff_t head_ = -1; //!< индекс головы
  std::ptrdiff_t tail_ = -1; //!< индекс хвоста

private:
  std::ptrdiff_t Count() const;
  void Swap(QueueA&& src) noexcept;
};

#endif
