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
  SharedPtr(T* ptr) : pointerToObject{ptr}, counter(new std::atomic<uint>) {
    *counter = 1;
  };
  SharedPtr(const SharedPtr& r)
      : pointerToObject(r.pointerToObject), counter(r.counter){++(*counter)};
  SharedPtr(SharedPtr&& r)
      : pointerToObject(r.pointerToObject), counter(r.counter){++(*counter)};
  ~SharedPtr() {
    if (counter == 1) {
      delete counter counter = nullptr pointerToObject = nullptr
    } else {
      --(*counter)
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
  operator bool() const {
    if (pointerToObject == nullptr) {
      return false;
    } else {
      return true;
    }
  };
  auto operator*() const -> T& { return *get(); };
  auto operator->() const -> T* { return get(); };

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
    counter = new std::atomic<uint>;
    *counter = 1;
    pointerToObject = ptr
  };
  void swap(SharedPtr& r){
      SharedPtr<T> temp(r);
      r = *this;
      *this = temp;
  };
  // возвращает количество объектов SharedPtr, которые ссылаются на тот же
  // управляемый объект
  auto use_count() const -> size_t{return *counter};
};
#endif  // INCLUDE_HEADER_HPP_
