#pragma once

#include <QMainWindow>

#include "Utilities/General.hpp"

struct TestingWindow : QMainWindow {

    TestingWindow();

    virtual ~TestingWindow();

private:
    observable <int> observableNumber { };
    Observable<QString> observableText { };
    Observable<QString> observableText2 { "P" };
    Event <QString> event;
};

