#include <stackl/stackl.hpp>
#include <stdexcept>
#include <utility>

StackL::StackL(const StackL& src) {
  // Копирующий конструктор
  if (!src.IsEmpty()) {
    // Создаём первый узел
    head_ = new Node{ src.head_->val };
    Node* p_src = src.head_->next;
    Node* p_dst = head_;
    while (p_src) {
      p_dst->next = new Node{ p_src->val };
      p_dst = p_dst->next;
      p_src = p_src->next;
    }
  }
}

StackL::StackL(StackL&& src) noexcept {
  std::swap(head_, src.head_);
}

StackL& StackL::operator=(const StackL& src) {
  if (this != &src) {
    Clear();
    if (!src.IsEmpty()) {
      head_ = new Node{ src.head_->val };
      Node* p_src = src.head_->next;
      Node* p_dst = head_;
      while (p_src) {
        p_dst->next = new Node{ p_src->val };
        p_dst = p_dst->next;
        p_src = p_src->next;
      }
    }
  }
  return *this;
}

StackL& StackL::operator=(StackL&& src) noexcept {
  if (this != &src) {
    Clear();
    std::swap(head_, src.head_);
  }
  return *this;
}

bool StackL::IsEmpty() const noexcept {
  return (head_ == nullptr);
}

void StackL::Pop() noexcept {
  if (!IsEmpty()) {
    Node* deleted = head_;
    head_ = head_->next;
    delete deleted;
  }
}

void StackL::Push(const T val) {
  head_ = new Node{ val, head_ };
}

StackL::T& StackL::Top() & {
  if (IsEmpty()) {
    throw std::logic_error("StackL - try get top from empty stack.");
  }
  return head_->val;
}

const StackL::T& StackL::Top() const & {
  if (IsEmpty()) {
    throw std::logic_error("StackL - try get top from empty stack.");
  }
  return head_->val;
}

void StackL::Clear() noexcept {
  while (!IsEmpty()) {
    Pop();
  }
}
