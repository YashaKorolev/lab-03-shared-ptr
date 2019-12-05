//
// Created by alexandergaranin on 01.12.2019.
//

#ifndef TEMPLATE_SHAREDPTR_H
#define TEMPLATE_SHAREDPTR_H

#include <iostream>
#include <atomic>

template<typename T>
class SharedPtr {

private:
    T *object = nullptr;
    std::atomic_uint *counter = nullptr;
public:
    SharedPtr();

    explicit SharedPtr(T *);

    SharedPtr(const SharedPtr &);

    SharedPtr(SharedPtr &&);

    ~SharedPtr();

    auto operator=(const SharedPtr &) -> SharedPtr &;

    auto operator=(SharedPtr &&) -> SharedPtr &;

    explicit operator bool() const;

    auto operator*() const -> T &;

    auto operator->() const -> T *;

    auto get() -> T *;

    void reset();

    void reset(T *);

    void swap(SharedPtr &);

    auto use_count() const -> size_t;

};

template<typename T>
SharedPtr<T>::SharedPtr() {
    //counter = new std::atomic_uint {1};
    counter = new std::atomic_uint{1};
}

template<typename T>
SharedPtr<T>::SharedPtr(T *ptr) {
    object = ptr;
    counter = new std::atomic_uint{1};

}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr &r) {
    *this = r;
}

template<typename T>
SharedPtr<T>::SharedPtr(SharedPtr &&r) {
    *this = move(r);
}

template<typename T>
SharedPtr<T>::~SharedPtr() {
    bool b = (--(*counter)) == 0;
    if (b) {


        delete object;
        delete counter;


    }
    object = nullptr;
    counter = nullptr;
}

template<typename T>
auto SharedPtr<T>::operator=(const SharedPtr &r) -> SharedPtr & {
//    this->SharedPtr();
    counter = r.counter;
    object = r.object;
    ++(*counter);
    return *this;
}

template<typename T>
auto SharedPtr<T>::operator=(SharedPtr &&r) -> SharedPtr & {
    //  this->SharedPtr1();
    counter = r.counter;
    object = r.object;
    r.counter = nullptr;
    r.object = nullptr;
    return *this;
}

template<typename T>
SharedPtr<T>::operator bool() const {
    bool flag = true;
    if (object == nullptr)
        flag = false;
    return flag;
}

template<typename T>
auto SharedPtr<T>::operator*() const -> T & {
    return *object;
}

template<typename T>
auto SharedPtr<T>::operator->() const -> T * {
    return object;
}

template<typename T>
auto SharedPtr<T>::get() -> T * {
    return object;
}


template<typename T>
void SharedPtr<T>::reset() {
    reset(nullptr);
}

template<typename T>
void SharedPtr<T>::reset(T *ptr) {
    //this->~SharedPtr();
    object = ptr;
    counter = new std::atomic_uint{1};
}

//template <typename T>
//void SharedPtr<T>::reset()
//{
//    *this = SharedPtr();
//}
//
//template <typename T>
//void SharedPtr<T>::reset(T* ptr)
//{
//    *this = SharedPtr(ptr);
//}

template<typename T>
void SharedPtr<T>::swap(SharedPtr &r) {
    std::swap(r.counter, counter);
    std::swap(r.object, object);
}

template<typename T>
auto SharedPtr<T>::use_count() const -> size_t {
    return *counter;
}


#endif //TEMPLATE_SHAREDPTR_H
