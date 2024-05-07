#include <QAbstractSlider>
#include <QApplication>
#include <QFile>
#include <QScrollArea>
#include <QScrollBar>
#include <QScroller>
#include <QToolButton>

#include "TestingWindow.hpp"
#include "ApplicationWindow.hpp"
#include "Utilities/Resources.hpp"

#include <QProgressBar>
#include "Visuals/Basics/BoxLayout.hpp"

struct Scrll : QScrollArea {
    Scrll() {
        this->scrollContentsBy(32, 0);
    }

protected:
    void scrollContentsBy(int dx, int dy) override {
        // Calculate new content position
        int newX = horizontalScrollBar()->value() - dx;
        int newY = verticalScrollBar()->value() - dy;

        // Apply snapping logic for horizontal scrolling
        if (dx != 0) {
            int remainder = newX % snapInterval;
            if (remainder > snapInterval / 2) {
                newX += snapInterval - remainder;
            } else if (remainder < -snapInterval / 2) {
                newX -= remainder + snapInterval;
            }
        }

        // Apply snapping logic for vertical scrolling (similar logic)
        if (dy != 0) {
            // ... (implement vertical snapping logic)
        }

        // Enforce content boundaries
        newX = qBound(0, newX, 1000 - viewport()->width());
        newY = qBound(0, newY, 32 - viewport()->height());

        // Update scrollbar positions (optional)
        horizontalScrollBar()->setValue(newX);
        verticalScrollBar()->setValue(newY);

        QScrollArea::scrollContentsBy(dx, dy);
    }

private:
    int snapInterval;
};

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

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Create a widget to contain the tool buttons
    QWidget *widget = new QWidget();
    widget->setLayout(new QHBoxLayout());

    // Add the tool buttons to the widget
    for (int i = 0; i < 20; ++i) {
        QToolButton *button = new QToolButton();
        // Set up the button as needed
        widget->layout()->addWidget(button);
    }

    // Set the widget as the viewport of the scroll area
    scrollArea->setWidget(widget);

    // Set the scroll area as the toolbar's widget
    // toolBar->addWidget(scrollArea);

    QScroller::grabGesture(scrollArea->viewport(), QScroller::LeftMouseButtonGesture);
    QScroller* scroller = QScroller::scroller(scrollArea);
    scroller->setSnapPositionsX(20, 20);
    QVariant OvershootPolicy = QVariant::fromValue<QScrollerProperties::OvershootPolicy>(QScrollerProperties::OvershootAlwaysOff);
    QScrollerProperties ScrollerProperties = QScroller::scroller(scrollArea->viewport())->scrollerProperties();
    ScrollerProperties.setScrollMetric(QScrollerProperties::SnapTime, 0.1);
    ScrollerProperties.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy, OvershootPolicy);
    ScrollerProperties.setScrollMetric(QScrollerProperties::HorizontalOvershootPolicy, OvershootPolicy);
    // ScrollerProperties.setScrollMetric(QScrollerProperties::SnapPositionRatio, 0.5);
    scroller = QScroller::scroller(scrollArea->viewport());

    scroller->setScrollerProperties(ScrollerProperties);
    scroller->setSnapPositionsX(32, 32);

    scrollArea->show();

    // ApplicationWindow window;
    TestingWindow window;
    window.show();

    return app.exec();
}
