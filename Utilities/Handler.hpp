#pragma once

#include "Event.hpp"
#include "Bindable.hpp"

template <typename P, typename T>
struct Handler : IBindable {

    using target = Event<P> T::*;

    Handler() { }
    Handler(std::function<void(P)>&& item) : value(std::move(item)), asigned(true) { }

    int binds(void* item) override {
        if (auto source = reinterpret_cast<T*>(item); asigned and source != nullptr) {
            source->*function() += value;
        }

        return sizeof(Handler<P, T>);
    }

protected:
    virtual target function() = 0;

private:
    std::function<void(P)> value;
    bool asigned { false };
};
