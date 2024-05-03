#pragma once

#include "Observable.hpp"

template <typename T>
struct Bind {

    Observable<T>* source;

    Bind(Observable<T>& value) : source(&value) { }

    AnonymousObservable& operator +=(std::function<std::any(T val)>&& fun) {
        AnonymousObservable* target = new AnonymousObservable();
        source->registerAnonymousObservable(target);

        source->connect([target, fun = std::move(fun)](T p) {
            target->asign(fun(p));
        });

        return *target;
    }

};
