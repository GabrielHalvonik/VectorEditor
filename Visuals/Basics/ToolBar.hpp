#pragma once

#include <QToolBar>

#include "../../Utilities/General.hpp"

namespace Visuals::Basics {

    struct ToolBar : QToolBar {

        parametrize (ToolBar) {
            parameter <const list<QAction*>&> { affect(ToolBar::addActions) } actions;
        };

        ToolBar() { }

        virtual ~ToolBar() { }



        void addActions(const list<QAction*>& actions) {
            for (QAction* action : actions) {
                QToolBar::addAction(action);
            }
        }

    };

}


