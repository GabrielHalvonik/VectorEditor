#pragma once

#include "Event.hpp"
#include "Bindable.hpp"
#include "Observable.hpp"

template <typename P, typename T>
struct Handler : IBindable {

    using target = Event<P> T::*;

    Handler() { }

    Handler(Observable<P>& observable) : observable(&observable) { }
    Handler(std::function<void(P)>&& item) : value(std::move(item)), asigned(true) { }
    // Handler(const std::function<void(P)>& item) : value(item) { asigned = true; }
    // Handler(const std::function<void(P)>& item) : value(item), asigned(true) { }

    int binds(void* item) override {
        if (auto source = reinterpret_cast<T*>(item); source != nullptr) {
            if (asigned) {
                source->*function() += value;
            }
            if (observable != nullptr) {
                source->*function() += std::bind(&Observable<P>::asign, observable, std::placeholders::_1);
            }
        }

        return sizeof(Handler<P, T>);
    }

protected:
    virtual target function() = 0;

private:
    Observable<P>* observable { nullptr };
    std::function<void(P)> value;
    bool asigned { false };
};
