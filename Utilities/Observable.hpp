#pragma once

#include <vector>
#include <functional>

template <typename T>
struct Observable {

    using HandlerType = std::function<void(T)>;

    Observable() { }

    Observable(T arg) : value(arg), asigned(true) {
        for (auto& item : handlers) {
            item(arg);
        }
    }

    Observable(T&& arg) : value(std::move(arg)), asigned(true) {
        for (auto& item : handlers) {
            item(arg);
        }
    }

    Observable<T>* operator = (T arg) {
        value = arg;
        asigned = true;

        for (auto& item : handlers) {
            item(arg);
        }
        return this;
    }

    void asign(T arg) {
        value = arg;
        asigned = true;

        for (auto& item : handlers) {
            item(arg);
        }
    }

    void connect(HandlerType&& item) {
        handlers.push_back(std::move(item));
    }

    void operator+=(const HandlerType&& item) {
        handlers.push_back(std::move(item));
    }

    template <typename S>
    void bind(S* first, void(S::*second)(T)) {
        connect([first, second](T arg){ (first->*second)(arg); });
    }

    template <typename S>
    void bind(S* first, void(S::*second)(const T&)) {
        connect([first, second](const T& arg){ (first->*second)(arg); });
    }

    inline T getValue() const { return value; }
    inline bool getAsigned() const { return asigned; }

private:
    std::vector<HandlerType> handlers;
    bool asigned { false };
    T value { };
};
