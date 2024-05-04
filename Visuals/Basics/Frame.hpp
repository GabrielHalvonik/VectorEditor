#pragma once

#include <QFrame>

#include "../../Utilities/General.hpp"

namespace Visuals::Basics {

    struct Frame : QFrame {

        parametrize (Frame) {
            parameter <QLayout*> { affect(QFrame::setLayout) } layout;
            parameter <const QRect&> { affect(QFrame::setGeometry) } geometry;
        };

        Frame() { }

        virtual ~Frame() { }

    };

}


