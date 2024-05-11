#pragma once

#include <utility>

template <typename T>
struct Property {

    T operator->() const {
        return value;
    }

    T getValue() const {
        return value;
    }

    T operator = (T value) {
        this->value = value;
        asigned = true;
        return this->value;
    }

    T operator = (T&& value) {
        this->value = std::move(value);
        asigned = true;
        return this->value;
    }

    operator T () {
        return value;
    }

private:
    T value { };
    bool asigned { false };
};



template <typename T>
struct Property<T*> {

    T* operator->() const {
        return value;
    }

    T* getValue() const {
        return value;
    }

    T* operator = (T* value) {
        this->value = value;
        asigned = true;
        return value;
    }

    operator T* () {
        return value;
    }

private:
    T* value { };
    bool asigned { false };
};

template <typename T>
struct field : public Property<T> { };
