#pragma once

#include <QFrame>
#include <QActionGroup>
#include <QToolBar>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QToolButton>
#include <QGraphicsItem>
#include <QScrollArea>
#include <QScroller>

#include "../Basics/ToolButton.hpp"

#include "../../Utilities/General.hpp"

#include "ToolBarSeparator.hpp"

namespace Visuals::Basics {

    struct LeftToolBar : QFrame {

        parametrize (LeftToolBar) {
            parameter <int> { affect (QToolBar::setFixedWidth) } width;
            parameter <int> { affect (QToolBar::setFixedHeight) } height;
            parameter <QLayout*> { affect (QFrame::setLayout) } layout;
            parameter <const QRect&> { affect (QFrame::setGeometry) } geometry;
            // parameter <const list<QAction*>&> { affect(LeftToolBar::addActions) } actions;
        };

        LeftToolBar() : QFrame() {
            QObject::setObjectName("LeftToolBar");

            {
                auto tb = new ToolButton();
                tb->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::ZoomFitBest));
                tb->setStyleSheet("QToolButton { border: 0px; background-color: transparent; }"
                                  "QToolButton:pressed { border-top-left-radius: 6px; border-top-right-radius: 6px; border: 0px; background-color: rgba(100, 100, 100, 100); }");
                // tb->setStyleSheet("QToolButton {background-color: transparent;}");
                tb->setGeometry(0, 0, 32, 32);
                tb->setParent(this);
            }
            {
                auto tb = new ToolButton();
                tb->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::ZoomIn));
                tb->setStyleSheet("QToolButton { border: 0px; background-color: transparent; }"
                                  "QToolButton:pressed { border: 0px; background-color: rgba(100, 100, 100, 100); }");
                // tb->setStyleSheet("QToolButton {background-color: transparent;}");
                tb->setGeometry(0, 1*32, 32, 32);
                tb->setParent(this);
            }
            {
                auto tb = new ToolButton();
                tb->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::ZoomOut));
                tb->setStyleSheet("QToolButton { border: 0px; background-color: transparent; }"
                                  "QToolButton:pressed { border: 0px; background-color: rgba(100, 100, 100, 100); }");
                // tb->setStyleSheet("QToolButton {background-color: transparent;}");
                tb->setGeometry(0, 2*32, 32, 32);
                tb->setParent(this);
            }
            {
                auto tb = new ToolButton();
                tb->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::FormatJustifyLeft));
                tb->setStyleSheet("QToolButton { border: 0px; background-color: transparent; }"
                                  "QToolButton:pressed { border: 0px; background-color: rgba(100, 100, 100, 100); }");
                // tb->setStyleSheet("QToolButton {background-color: transparent;}");
                tb->setGeometry(0, 3*32, 32, 32);
                tb->setParent(this);
            }
            {
                auto tb = new ToolButton();
                tb->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::FormatJustifyRight));
                tb->setStyleSheet("QToolButton { border: 0px; background-color: transparent; }"
                                  "QToolButton:pressed { border: 0px; background-color: rgba(100, 100, 100, 100); }");
                // tb->setStyleSheet("QToolButton {background-color: transparent;}");
                tb->setGeometry(0, 4*32, 32, 32);
                tb->setParent(this);
            }
            {
                auto tb = new ToolButton();
                tb->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::InputKeyboard));
                tb->setStyleSheet("QToolButton { border: 0px; background-color: transparent; }"
                                  "QToolButton:pressed { border: 0px; background-color: rgba(100, 100, 100, 100); }");
                // tb->setStyleSheet("QToolButton {background-color: transparent;}");
                tb->setGeometry(0, 5*32, 32, 32);
                tb->setParent(this);
            }
            {
                auto tb = new ToolButton();
                tb->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::InputTablet));
                tb->setStyleSheet("QToolButton { border: 0px; background-color: transparent; }"
                                  "QToolButton:pressed { border: 0px; background-color: rgba(100, 100, 100, 100); }");
                // tb->setStyleSheet("QToolButton {background-color: transparent;}");
                tb->setGeometry(0, 6*32, 32, 32);
                tb->setParent(this);
            }
            {
                auto tb = new ToolButton();
                tb->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::AppointmentNew));
                tb->setStyleSheet("QToolButton { border: 0px; background-color: transparent; }"
                                  "QToolButton:pressed { border: 0px; background-color: rgba(100, 100, 100, 100); }");
                // tb->setStyleSheet("QToolButton {background-color: transparent;}");
                tb->setGeometry(0, 7*32, 32, 32);
                tb->setParent(this);
            }
            {
                auto tb = new ToolButton();
                tb->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::FolderVisiting));
                tb->setStyleSheet("QToolButton { border: 0px; background-color: transparent; }"
                                  "QToolButton:pressed { border: 0px; background-color: rgba(100, 100, 100, 100); }");
                // tb->setStyleSheet("QToolButton {background-color: transparent;}");
                tb->setGeometry(0, 8*32, 32, 32);
                tb->setParent(this);
            }
            {
                auto tb = new ToolButton();
                tb->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::MediaTape));
                tb->setStyleSheet("QToolButton { border: 0px; background-color: transparent; }"
                                  "QToolButton:pressed { border: 0px; background-color: rgba(100, 100, 100, 100); }");
                // tb->setStyleSheet("QToolButton {background-color: transparent;}");
                tb->setGeometry(0, 9*32, 32, 32);
                tb->setParent(this);
            }
            {
                auto tb = new ToolButton();
                tb->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::GoUp));
                tb->setStyleSheet("QToolButton { border: 0px; background-color: transparent; }"
                                  "QToolButton:pressed { border: 0px; background-color: rgba(100, 100, 100, 100); }");
                // tb->setStyleSheet("QToolButton {background-color: transparent;}");
                tb->setGeometry(0, 10*32, 32, 32);
                tb->setParent(this);
            }
            {
                auto tb = new ToolBarSeparator({
                    .orientation = Orientation::Horizontal,
                    .frameSize = QSize { 32, 10 },
                    .separatorSize = QSize { 24, 2 },
                    .offset = QPoint { 0, 11*32 },
                                                // 4, 11*32+4, 24
                });

                tb->setParent(this);
            }
            {
                auto tb = new ToolButton();
                tb->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::GoUp));
                tb->setStyleSheet("QToolButton { border: 0px; background-color: transparent; }"
                                  "QToolButton:pressed { border: 0px; background-color: rgba(100, 100, 100, 100); }");
                // tb->setStyleSheet("QToolButton {background-color: transparent;}");
                tb->setGeometry(0, 11*32+10, 32, 32);
                tb->setParent(this);
            }
            {
                auto tb = new ToolButton();

                tb->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::MediaTape));
                tb->setStyleSheet("QToolButton { border: 0px; background-color: transparent; }"
                                  "QToolButton:pressed { border: 0px; background-color: rgba(100, 100, 100, 100); }");
                // tb->setStyleSheet("QToolButton {background-color: transparent;}");
                tb->setGeometry(0, 12*32+10, 32, 32);
                tb->setParent(this);
            }
            {
                auto sa = new QScrollArea();
                sa->setGeometry(0, 13*32+10, 0, 0);
                sa->setWidgetResizable(true);
                sa->setFixedWidth(32);
                sa->setFixedHeight(64);
                sa->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
                sa->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                // sa->setGeometry(0, 13*32+10, 32, 320);
                // sa->setAlignment(Qt::AlignLeft| Qt::AlignTop);

                sa->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
                // sa->resize(32, 64);
                auto w = new QWidget();
                w->resize(32, 128);
                // w->setOrientation(Qt::Orientation::Vertical);
                w->setLayout(new QVBoxLayout());
                w->layout()->setContentsMargins(0, 0, 0, 0);
                {
                    auto tb = new ToolButton();

                    tb->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::MediaTape));
                    tb->setStyleSheet("QToolButton { border: 0px; background-color: transparent; }"
                                      "QToolButton:pressed { border: 0px; background-color: rgba(100, 100, 100, 100); }");
                    tb->setMinimumSize(32, 32);
                    tb->setFixedSize(32, 32);
                    w->layout()->addWidget(tb);
                    // tb->setGeometry(0, 0, 32, 32);
                    // tb->setParent(sa);
                }
                {
                    auto tb = new ToolButton();

                    tb->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::MediaTape));
                    tb->setStyleSheet("QToolButton { border: 0px; background-color: transparent; }"
                                      "QToolButton:pressed { border: 0px; background-color: rgba(100, 100, 100, 100); }");
                    tb->setMinimumSize(32, 32);
                    tb->setFixedSize(32, 32);
                    w->layout()->addWidget(tb);
                    // tb->setGeometry(0, 32, 32, 32);
                    // tb->setParent(sa);
                }
                {
                    auto tb = new ToolButton();

                    tb->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::MediaTape));
                    tb->setStyleSheet("QToolButton { border: 0px; background-color: transparent; }"
                                      "QToolButton:pressed { border: 0px; background-color: rgba(100, 100, 100, 100); }");
                    tb->setFixedSize(32, 32);
                    w->layout()->addWidget(tb);
                    // tb->setGeometry(0, 64, 32, 32);
                    // tb->setParent(sa);
                }
                {
                    auto tb = new ToolButton();

                    tb->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::MediaTape));
                    tb->setStyleSheet("QToolButton { border: 0px; background-color: transparent; }"
                                      "QToolButton:pressed { border: 0px; background-color: rgba(100, 100, 100, 100); }");
                    tb->setFixedSize(32, 32);
                    w->layout()->addWidget(tb);
                    // tb->setGeometry(0, 64, 32, 32);
                    // tb->setParent(sa);
                }

                sa->setViewport(w);
                // tb->setStyleSheet("QToolButton {background-color: transparent;}");
                sa->setParent(this);
            }

            // w->setParent(this);
            // this->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
            // this->setFixedHeight(300);
            // this->setFixedWidth(30);
            // auto btn = new QToolButton(this);
            // btn->setGeometry(0, 20, 20, 20);
            // this->addAction(new QAction (QIcon::fromTheme(QIcon::ThemeIcon::EditUndo), "Undo"));
            return;
            // layout->setGeometry(QRect(0, 0, 40, 100));
            // layout->setAlignment(new ToolButton({.width= 30}), Qt::AlignLeft);
            // w->setLayout(layout);

            // layout->setAlignment(layout, Qt::AlignLeft);
            // auto tb = new QToolBar(this);



        }

        virtual ~LeftToolBar() { }



        // void addActions(const list<QAction*>& actions) {
        //     for (QAction* action : actions) {
        //         QToolBar::addAction(action);
        //     }
        // }

    };

}


