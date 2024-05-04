#include <QApplication>
#include <QFile>

#include "TestingWindow.hpp"
#include "ApplicationWindow.hpp"
#include "Utilities/Resources.hpp"

#include <QProgressBar>
#include "Visuals/Basics/BoxLayout.hpp"

using namespace Visuals::Basics;

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    Utilities::Resources::setStyleSheet(app, ":/Styles/General.qss");

    // // Create the main window
    // QWidget mainWindow;
    // // mainWindow.setFixedSize(400, 300);

    // mainWindow.setLayout(new BoxLayout ({
    //     .items = {
    //         new QProgressBar {}
    //     }
    // }));
    // // Create the central frame
    // QFrame centralFrame(&mainWindow);
    // centralFrame.setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    // centralFrame.setMidLineWidth(3);
    // centralFrame.setGeometry(10, 10, 48, 1000);  // Set position and size
    // // centralFrame.setStyleSheet("background-color: blue;");


    // mainWindow.show();
    // return app.exec();

    // QApplication app(argc, argv);

    // Utilities::Resources::setStyleSheet(app, ":/Styles/General.qss");

    // TestingWindow window;
    ApplicationWindow window;
    window.show();

    return app.exec();
}
