#pragma once

#define parameters struct Parameters

#define parametrized(owner) owner (Parameters&& Parameters) { \
for (int i = 0; i < sizeof(Parameters); ) { \
        i += reinterpret_cast<IBindable*>(reinterpret_cast<byte*>(&Parameters) + i)->bind(this); \
    } \
}

#define parametrize(item) \
template <typename T> \
    using DeducedParameter = Parameter<T, item>; \
    template <typename T> \
    using DeducedHandler = Handler<T, item>; \
    struct Parameters; \
    parametrized(item) \
    parameters



#define set_parameter using Parameter::Parameter;
#define affect(value) set_parameter target function() { return &value; }
#define parameter struct : DeducedParameter



#define set_slot using Slot::Slot;
#define subscribe(value) set_slot target function() { return &value; }
#define connection struct : Slot



#define set_handler using Handler::Handler;
#define attach(value) set_handler target function() { return &value; }
#define handler struct : DeducedHandler



#define property Property
#define observable Observable
