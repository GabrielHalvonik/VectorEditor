#include "ApplicationWindow.hpp"

#include "Visuals/Basics/Widget.hpp"
#include "Visuals/Basics/VerticalBoxLayout.hpp"
#include "Visuals/Basics/Label.hpp"
#include "Visuals/Basics/LineEdit.hpp"
#include "Visuals/Basics/ProgressBar.hpp"

using namespace Visuals::Basics;

template <typename T>
struct Bind {

    Observable<T>* source;

    Bind(Observable<T>& value) : source(&value) {
        // this->value->connect([this](T p) {
        //     target.asign();
        // });
    }

    // Observable<int>* operator += (const std::function<int(T val)>& fun) {

    // }

    // Observable<std::optional<std::any>>* operator +=(std::function<std::optional<std::any>(T val)>&& fun) {
    //     Observable<std::optional<std::any>>* target = new Observable<std::optional<std::any>>();
    //     value->connect([target, fun](T p) {
    //         target->asign(fun(p));
    //     });
    //     return target;
    // }

    // template <typename P>
    // Observable<P>* asign(std::function<std::optional<P>(T val)>&& fun) {
    //     Observable<P>* target = new Observable<P>();

    //     value->connect([target, fun = std::move(fun)](T p) {
    //         if (auto f = fun(p); f.has_value()) {
    //             // std::any_cast<P>(f.value());
    //             target->asign(f.value());
    //         }
    //     });

    //     return target;
    // }

    // template <typename P>
    // Observable<P>* operator +=(std::function<std::optional<P>(T val)>&& fun) {
    //     qInfo() << "ASDASFS";
    //     Observable<P>* target = new Observable<P>();

    //     value->connect([target, fun = std::move(fun)](T p) {
    //         if (auto f = fun(p); f.has_value()) {
    //             // std::any_cast<P>(f.value());
    //             target->asign(f.value());
    //         }
    //     });

    //     return target;
    // }

    AnonymousObservable* operator +=(std::function<std::any(T val)>&& fun) {
        AnonymousObservable* target = new AnonymousObservable();

        source->connect([target, fun = std::move(fun)](T p) {
            target->asign(fun(p));
        });

        return target;
    }

    // AnonymousObservable* operator +=(std::function<std::optional<std::any>(T val)>&& fun) {
    //     AnonymousObservable* target = new AnonymousObservable();

    //     source->connect([target, fun = std::move(fun)](T p) {
    //         target->asign(fun(p));
    //     });

    //     return target;
    // }
};

// #define when(observable) When { observable } += [](auto value) -> std::optional
#define bind(observable) Bind { observable }
#define into += [](auto value) -> std::optional

void tst(Observable<std::optional<std::any>>* obs) {

    obs->connect([](std::optional<std::any> p) {

        qInfo() << "HV? " << p.has_value();
        // int v = std::any_cast<int>(p.value());

        try {
            qInfo() << p.value().type().name() << "_--------_____" << std::any_cast<qsizetype>(p.value());
        } catch (std::bad_any_cast& e) {
            qInfo() << "err: " << e.what();
        }

    });
}

template <typename P>
void tst(Observable<P>* obs) {

    obs->connect([](P p) {
        qInfo() << "HV? " << p;
        // int v = std::any_cast<int>(p.value());

        // try {
        //     qInfo() << p.value().type().name() << "_--------_____" << std::any_cast<int>(p.value());
        // } catch (std::bad_any_cast& e) {
        //     qInfo() << "err: " << e.what();
        // }

    });
}

ApplicationWindow::ApplicationWindow() {

    // std::any item = QString("Hello");
    // qInfo() << std::any_cast<QString>(item);

    // std::optional<QString> opt = QString("Hello");
    // qInfo() << "HV " << opt.has_value();

    // std::any it = std::optional<QString>("Hello");
    // qInfo() << "EC" << std::any_cast<std::optional<QString>>(it).value();


// tst(bind (observableText) to { return { value.length() }; });

    // tst(bindto (observableText) into <int> { return { value.length() }; });

    // dd.connect([this](auto ii) {
    //     // auto cast = std::any_cast<std::optional<QString>>(ii);
    //     // cast.value();
    //     // observableText2 = std::any_cast<std::optional<QString>>(item);
    // });

    qInfo() << [](int str) -> std::optional<string> { return { }; }(2).has_value();

// tst(Bind { observableNumber } += [](auto value) -> std::optional<std::any> { return { value }; });

    // pt.connect([](std::optional<std::any> p) {

    //     int v = std::any_cast<int>(p.value());

    //     try {
    //         qInfo() << p.value().type().name() << "_--------_____" << std::any_cast<int>(p.value());
    //     } catch (std::bad_any_cast& e) {
    //         qInfo() << "err: " << e.what();
    //     }

    // });
        // auto pt = When {observableText} += [](QString str) -> int { return 2; };

    function<std::any(void)> f = []() { return (std::rand() % 2 == 0) ? 2 : 3; };
    auto p = f();
    qInfo() << std::any_cast<int>(p);

    event += [](auto value) {
        qInfo() << "evnt " << value;
    };

    observableText += [this](const auto& val) {
        if (val.startsWith("Xp")) {
            observableText2 = val;
        }
        return 2;
    };

    this->setCentralWidget(new Widget ({
        .layout = new VerticalBoxLayout ({
            .items = {
                new Label ({
                    .text = observableText = "bp",
                }),
                new LineEdit ({
                    .changed = {
                        [this](auto value) {
                            observableText = value;
                        }
                    },
                }),
                new Label ({
                    .text = bind (observableText) into <QString> {
                        if (value.length() == 0) return { "[Empty]" };
                        else if (value.length() <= 5) return { value };
                        else return { value.sliced(0, 5) };
                    },
                }),
                new ProgressBar ({
                    .value = bind (observableText) into <int> {
                        if (value.length() > 10) return { };
                        else return { int(value.length() % 11) * 10 };
                    }
                })
            }
        })
    }));
}

ApplicationWindow::~ApplicationWindow() {

}
