// Copyright 2020 Your Name <your_email>
#include "atomic"
#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
template <typename T>
class SharedPtr {
 private:
  T* pointerToObject;
  std::atomic_uint* counter;

 public:
  SharedPtr() : pointerToObject{nullptr}, counter(nullptr){};
  explicit SharedPtr(T* ptr) : pointerToObject{ptr}, counter(new std::atomic_uint) {
    *counter = 1;
  };
  SharedPtr(const SharedPtr& r)
      : pointerToObject(r.pointerToObject), counter(r.counter){++(*counter);};
  SharedPtr(SharedPtr&& r)
        : pointerToObject(r.pointerToObject), counter(r.counter){++(*counter);};
  ~SharedPtr() {
    if (*counter == 1) {
      delete counter;
      counter = nullptr;
      pointerToObject = nullptr;
    } else {
      --(*counter);
    }
  };
  auto operator=(const SharedPtr& r) -> SharedPtr& {
    this->reset();
    this->pointerToObject = r.pointerToObject;
    this->counter = r.counter;
    if (counter != nullptr) {
      ++(*counter);
    }
    return *this;
  };
  auto operator=(SharedPtr&& r) -> SharedPtr& {
    this->reset();
    this->pointerToObject = r.pointerToObject;
    this->counter = r.counter;
    if (counter != nullptr) {
      ++(*counter);
    }
    return *this;
  };

  // проверяет, указывает ли указатель на объект
  explicit operator bool() const {
    if (pointerToObject == nullptr) {
      return false;
    } else {
      return true;
    }
  };
  auto operator*() const -> T& { return *pointerToObject; };
  auto operator->() const -> T* { return pointerToObject; };

  auto get() -> T* { return pointerToObject; };
  void reset() {
    if (counter != nullptr) {
      if (*counter != 1) {
        --(*counter);
      } else {
        delete pointerToObject;
        delete counter;
      }
      pointerToObject = nullptr;
      counter = nullptr;
    }
  };
  void reset(T* ptr) {
    if (counter != nullptr) {
      --(*counter);
    }
    counter = new std::atomic_uint;
    *counter = 1;
    pointerToObject = ptr;
  };
  void swap(SharedPtr& r){
      SharedPtr<T> temp(r);
      r = *this;
      *this = temp;
  };
  // возвращает количество объектов SharedPtr, которые ссылаются на тот же
  // управляемый объект
  auto use_count() const -> std::size_t{return *counter;};
};
#endif  // INCLUDE_HEADER_HPP_
