#include "TestingWindow.hpp"
#include "ApplicationWindow.hpp"
#include "Utilities/Resources.hpp"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    Utilities::Resources::setStyleSheet(app, ":/Styles/General.qss");

    ApplicationWindow window;
    window.show();

    return app.exec();
}
