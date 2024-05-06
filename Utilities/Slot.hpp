#pragma once

#include <QObject>
#include <functional>
#include "Observable.hpp"

#include "Bindable.hpp"

template <typename P, typename T>
struct Slot : IBindable {

    using target = void (T::*)(P);

    Slot() { }
    Slot(Observable<P>& observable) : observable(&observable) { }
    Slot(std::function<void(P)>&& item) : value(std::move(item)), asigned(true) { }

    int binds(void* item) override {
        if (auto source = reinterpret_cast<T*>(item); source != nullptr) {
            if (asigned) {
                QObject::connect(source, function(), value);
            }
            if (observable != nullptr) {
                QObject::connect(source, function(), std::bind(&Observable<P>::asign, observable, std::placeholders::_1));
            }
        }
        return sizeof(Slot<P, T>);
    }

protected:
    virtual target function() = 0;

private:
    Observable<P>* observable { nullptr };
    std::function<void(P)> value { };
    bool asigned { false };
};

template <typename P, typename T>
struct Slot<const P&, T> : IBindable {

    using target = void (T::*)(const P&);

    Slot() { }
    Slot(Observable<P>& observable) : observable(&observable) { }
    Slot(std::function<void(const P&)>&& item) : value(std::move(item)), asigned(true) { }

    int binds(void* item) override {
        if (auto source = reinterpret_cast<T*>(item); source != nullptr) {
            if (asigned) {
                QObject::connect(source, function(), value);
            }
            if (observable != nullptr) {
                QObject::connect(source, function(), std::bind(&Observable<P>::asign, observable, std::placeholders::_1));
            }
        }
        return sizeof(Slot<const P&, T>);
    }

protected:
    virtual target function() = 0;

private:
    Observable<P>* observable { nullptr };
    std::function<void(const P&)> value { };
    bool asigned { false };
};
