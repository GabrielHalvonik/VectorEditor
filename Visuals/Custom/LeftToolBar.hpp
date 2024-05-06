#pragma once

#include <QFrame>
#include <QActionGroup>
#include <QToolBar>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QToolButton>

#include "../Basics/ToolButton.hpp"

#include "../../Utilities/General.hpp"

namespace Visuals::Basics {

    struct LeftToolBar : QFrame {

        parametrize (LeftToolBar) {
            parameter <int> { affect(QToolBar::setFixedWidth) } width;
            parameter <int> { affect(QToolBar::setFixedHeight) } height;
            parameter <QLayout*> { affect(QFrame::setLayout) } layout;
            parameter <const QRect&> { affect(QFrame::setGeometry) } geometry;
            // parameter <const list<QAction*>&> { affect(LeftToolBar::addActions) } actions;
        };

        LeftToolBar() {
            new QToolButton(this);
            auto layout = new QVBoxLayout();

            layout->setGeometry(QRect(0, 0, 40, 600));
            // layout->setAlignment(new ToolButton({.width= 30}), Qt::AlignLeft);
            // this->setLayout(layout);

            // layout->setAlignment(layout, Qt::AlignLeft);
            // auto tb = new QToolBar(this);

            // layout->addWidget(tb);
            // auto ac = new QAction("P");
            layout->addWidget(new ToolButton({.width= 30}), 1,  Qt::AlignLeft);
            layout->addWidget(new ToolButton());
            layout->addWidget(new ToolButton());
            // layout->addWidget(new QAction("P"));
            // layout->addWidget(new QAction("P"));

            QObject::setObjectName("LeftToolBar");
        }

        virtual ~LeftToolBar() { }



        // void addActions(const list<QAction*>& actions) {
        //     for (QAction* action : actions) {
        //         QToolBar::addAction(action);
        //     }
        // }

    };

}


