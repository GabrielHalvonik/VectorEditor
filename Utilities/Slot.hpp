#pragma once

#include <QObject>
#include <functional>

#include "Bindable.hpp"

template <typename P, typename T>
struct Slot : IBindable {

    using target = void (T::*)(P);

    Slot() { }
    Slot(std::function<void(P)>&& item) : value(std::move(item)), asigned(true) { }

    int binds(void* item) override {
        if (auto source = reinterpret_cast<T*>(item); asigned and source != nullptr) {
            QObject::connect(source, function(), value);
        }
        return sizeof(Slot<P, T>);
    }

protected:
    virtual target function() = 0;

private:
    std::function<void(P)> value { };
    bool asigned { false };
};

template <typename P, typename T>
struct Slot<const P&, T> : IBindable {

    using target = void (T::*)(const P&);

    Slot() { }
    Slot(std::function<void(const P&)>&& item) : value(std::move(item)), asigned(true) { }

    int binds(void* item) override {
        if (auto source = reinterpret_cast<T*>(item); asigned and source != nullptr) {
            QObject::connect(source, function(), value);
        }
        return sizeof(Slot<const P&, T>);
    }

protected:
    virtual target function() = 0;

private:
    std::function<void(const P&)> value { };
    bool asigned { false };
};
