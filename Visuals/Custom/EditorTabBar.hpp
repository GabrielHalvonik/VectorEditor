#pragma once

#include <QWidget>
#include <QTabBar>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QApplication>
#include <QPushButton>
#include <QScrollBar>
#include <QStackedLayout>
#include <QSlider>

#include "../../Utilities/General.hpp"

#include "../Basics/PushButton.hpp"

using namespace Visuals::Basics;

namespace Visuals::Custom {

    struct EditorTabBar : QScrollArea {

        EditorTabBar() {
            QScrollArea::setFixedHeight(barHeight);
            tabBar->setFixedHeight(barHeight);

            // this->setWidgetResizable(true);
            this->verticalScrollBar()->setDisabled(true);
            this->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
            this->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

            // tabBar->setTabButton();
            tabBar->addTab("A");
            tabBar->addTab("B");
            tabBar->addTab("C");
            tabBar->addTab("D");
            tabBar->addTab("E");
            tabBar->addTab("F");
            tabBar->addTab("G");
            tabBar->addTab("H");

            QObject::connect(tabBar, &QTabBar::tabCloseRequested, this, [this](int index) {
                qInfo() << "tab requested to close: " << index;
            });

            tabBar->setMovable(true);
            tabBar->setTabsClosable(true);

            auto inner = new QWidget();
            auto layout = new QHBoxLayout();
            layout->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
            layout->setContentsMargins(0, 0, 0, 0);
            layout->setSpacing(0);

            layout->addWidget(tabBar);
            layout->addWidget(new PushButton ({
                .name = { "TabBarAddTabButton" },
                .width = barHeight,
                .height = barHeight,
                .text = { "+" },
                .clicked = {
                    [](bool state) {
                        qInfo() << "clck";
                    }
                }
            }));
            inner->setLayout(layout);

            this->setWidget(inner);
        }

        virtual ~EditorTabBar() { }
        // QWidget interface

    private:

        const int barHeight = 20;

        struct ScrollableTabBar : QTabBar {

            EditorTabBar* parent;

            ScrollableTabBar(EditorTabBar* parent = nullptr) : QTabBar(parent), parent(parent) { }
            virtual ~ScrollableTabBar() { }

            void wheelEvent(QWheelEvent* event) override {
                if (parent != nullptr) {
                    QApplication::sendEvent(parent->horizontalScrollBar(), event);
                } else {
                    QTabBar::wheelEvent(event);
                }
            }
        } * tabBar = new ScrollableTabBar { this };

    };

}
