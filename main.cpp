#include "TestingWindow.hpp"
#include "ApplicationWindow.hpp"
#include "Utilities/Resources.hpp"

#include <QStyleFactory>

int main(int argc, char *argv[]) {

    property <int> myProperty {
        setter { field = value + 20; },
        getter { return field - 10; }
    };

    QApplication app(argc, argv);

    QApplication::setStyle(QStyleFactory::create("Fusion"));

    Utilities::Resources::setStyleSheet(app, ":/Styles/General.qss");

    ApplicationWindow window;
    window.show();

    return app.exec();
}
