#pragma once

#include <QWidget>

#include "../../Utilities/General.hpp"

namespace Visuals::Basics {

    struct Widget : QWidget {

        parametrize (Widget) {
            parameter <QLayout*> { affect (QWidget::setLayout); } layout;
        };

        Widget() { }

        virtual ~Widget() { }

    };

}
