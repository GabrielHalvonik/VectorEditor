#include <QApplication>
#include <QFile>

#include "ApplicationWindow.hpp"
#include "Utilities/Resources.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    Utilities::Resources::setStyleSheet(app, ":/Styles/General.qss");

    ApplicationWindow window;
    window.show();

    return app.exec();
}
