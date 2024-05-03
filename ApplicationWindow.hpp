#pragma once

#include <QMainWindow>

#include "Utilities/General.hpp"

struct ApplicationWindow : QMainWindow {

    ApplicationWindow();
    virtual ~ApplicationWindow();

private:
    Observable<int> observableNumber { };
    Observable<QString> observableText { };
    Observable<QString> observableText2 { "P" };
    Event <QString> event;
};
