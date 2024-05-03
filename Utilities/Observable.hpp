#pragma once

#include <vector>
#include <functional>
#include <any>

template <typename T>
struct Observable {

    using HandlerType = std::function<void(T)>;

    Observable() { }

    // Observable(T arg) : value(arg), asigned(true) {
    //     // for (auto& item : handlers) {
    //     //     item(arg);
    //     // }
    // }

    Observable(T&& arg) : value(std::move(arg)), asigned(true) {
        // for (auto& item : handlers) {
        //     item(arg);
        // }
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



struct AnonymousObservable {

    // using HandlerType = std::function<void(std::optional<std::any>)>;

    AnonymousObservable() { }

    // AnonymousObservable(std::optional<std::any> arg) : value(arg), asigned(true) {
        // for (auto& item : handlers) {
        //     item(arg);
        // }
    // }

    // AnonymousObservable(std::optional<std::any>&& arg) : value(std::move(arg)), asigned(true) {
        // for (auto& item : handlers) {
        //     item(arg);
        // }
    // }

    AnonymousObservable* operator = (std::any arg) {
        value = arg;
        asigned = true;

        for (auto& item : handlers) {
            item(arg);
        }
        return this;
    }

    void asign(std::any arg) {
        value = arg;
        asigned = true;

        for (auto& item : handlers) {
            item(arg);
        }
    }

    void connect(std::function<void(std::any)>&& item) {
        handlers.push_back(std::move(item));
    }

    void operator+=(const std::function<void(std::any)>&& item) {
        handlers.push_back(std::move(item));
    }

    template <typename S, typename P>
    void bind(S* first, void(S::*second)(P)) {
        connect([first, second](const std::any& arg) {
            if (arg.has_value()) {
                if (auto val = std::any_cast<std::optional<P>>(arg); val.has_value()) {
                    (first->*second)(val.value());
                }
            }
        });
    }

    template <typename S, typename P>
    void bind(S* first, void(S::*second)(const P&)) {
        connect([first, second](const std::any& arg) {
            if (arg.has_value()) {
                if (auto val = std::any_cast<std::optional<P>>(arg); val.has_value()) {
                    (first->*second)(val.value());
                }
            }
        });
    }

    inline std::any getValue() const { return value; }
    inline bool getAsigned() const { return asigned; }

private:
    std::vector<std::function<void(std::any)>> handlers;
    bool asigned { false };
    std::any value { };
};


