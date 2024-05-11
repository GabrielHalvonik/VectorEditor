#pragma once

#include <QWidget>
#include <QTabBar>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QApplication>
#include <QPushButton>
#include <QScrollBar>
#include <QPainter>
#include <QStyle>

#include "../../Utilities/General.hpp"
#include "../General/Styles.hpp"

#include "../Basics/PushButton.hpp"

using namespace Visuals::Basics;

namespace Visuals::Custom {

    struct EditorTabBar : QScrollArea {

        EditorTabBar(QWidget* parent = nullptr) : QScrollArea(parent) {
            QScrollArea::setFixedHeight(barHeight);
            tabBar->setFixedHeight(barHeight);

            // this->setWidgetResizable(true);
            this->verticalScrollBar()->setDisabled(true);
            this->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
            this->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

            // tabBar->addTab("A");
            // tabBar->addTab("B");
            // tabBar->addTab("C");
            // tabBar->addTab("D");
            // tabBar->addTab("E");
            // tabBar->addTab("F");
            // tabBar->addTab("G");
            // tabBar->addTab("H");

            QObject::connect(tabBar, &QTabBar::tabCloseRequested, this, [this](int index) {
                tabBar->removeTab(index);
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
                    [this](bool state) {
                        tabBar->addTab("X");
                    }
                }
            }));

            inner->setLayout(layout);

            this->setWidget(inner);
        }

        virtual ~EditorTabBar() { }

    private:

        const int barHeight = 20;

        struct ScrollableTabBar : QTabBar {

            EditorTabBar* parent { };

            ScrollableTabBar(EditorTabBar* parent = nullptr) : QTabBar(parent), parent(parent) {
                QObject::setObjectName("ScrollableTabBar");

                QTabBar::setDrawBase(false);
            }

            virtual ~ScrollableTabBar() { }

            void tabInserted(int index) override {
                QTabBar::tabInserted(index);

                QTabBar::setTabButton(index, QTabBar::ButtonPosition::RightSide,
                    new CustomCloseButton ({
                        .parent = this,
                        .size = 12,
                        .clicked = {
                            delegate {
                                 if (auto self = reinterpret_cast<PushButton*>(source); self != nullptr) {
                                     QTabBar::tabCloseRequested(QTabBar::tabAt(self->pos()));
                                 }
                            }
                        },
                    })
                );
            }

            void wheelEvent(QWheelEvent* event) override {
                if (parent != nullptr) {
                    QApplication::sendEvent(parent->horizontalScrollBar(), event);
                } else {
                    QTabBar::wheelEvent(event);
                }
            }

            struct CustomCloseButton : public QPushButton {

                parametrize (CustomCloseButton) {
                    parameter <QWidget*> { affect (QWidget::setParent) } parent;
                    parameter <int> { affect (CustomCloseButton::setSize) } size;
                    connection <bool, QPushButton> { subscribe (QPushButton::clicked) } clicked;
                };

                CustomCloseButton() : QPushButton() {
                    QObject::setObjectName("TabBarCloseButton");
                }

                void mousePressEvent(QMouseEvent* event) override { QPushButton::mousePressEvent(event); pressed = true; repaint(); }
                void mouseReleaseEvent(QMouseEvent* event) override { QPushButton::mouseReleaseEvent(event); pressed = false; repaint(); }
                void enterEvent(QEnterEvent* event) override { QPushButton::enterEvent(event); hovered = true; }
                void leaveEvent(QEvent* event) override { QPushButton::leaveEvent(event); hovered = false; }

                void paintEvent(QPaintEvent* event) override {
                    QPainter painter(this);
                    painter.setRenderHint(QPainter::Antialiasing);

                    if (pressed) {
                        painter.setBrush(QColor(200, 100, 100));
                    } else if (hovered) {
                        painter.setBrush(QColor(100, 100, 100));
                    }
                    painter.setPen(Qt::NoPen);
                    painter.drawRoundedRect(rect(), 2, 2);
                    painter.setPen(Qt::gray);

                    int lineLength = size * 0.6;
                    int centerX = width() / 2;
                    int centerY = height() / 2;

                    QPainterPath path;
                    path.moveTo(centerX - lineLength / 2, centerY - lineLength / 2);
                    path.lineTo(centerX + lineLength / 2, centerY + lineLength / 2);
                    path.moveTo(centerX + lineLength / 2, centerY - lineLength / 2);
                    path.lineTo(centerX - lineLength / 2, centerY + lineLength / 2);
                    painter.drawPath(path);
                }

                inline void setSize(int value) { QPushButton::setFixedSize(size, size);  size = value; }

            private:
                int size = 12;

                bool pressed { };
                bool hovered { };

            };
        protected:
            void tabLayoutChange() override {
                if (QTabBar::count() == 0) {
                    Styles::set(this, Styles::Fulfillment, Styles::Fulfillment.Values.Empty);
                } else {
                    Styles::set(this, Styles::Fulfillment, Styles::Fulfillment.Values.Filled);
                }
            }

        } * tabBar = new ScrollableTabBar { this };

    };

}
