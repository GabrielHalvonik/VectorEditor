#pragma once

#include <QFrame>

#include "../../Utilities/General.hpp"

namespace Visuals::Basics {

    struct EditorToolBar : QFrame {

        parametrize (EditorToolBar) {
            parameter <QLayout*> { affect(QFrame::setLayout) } layout;
            parameter <const QRect&> { affect(QFrame::setGeometry) } geometry;
        };

        EditorToolBar() {
            QObject::setObjectName("EditorToolBar");
        }

        virtual ~EditorToolBar() { }

    };

}


