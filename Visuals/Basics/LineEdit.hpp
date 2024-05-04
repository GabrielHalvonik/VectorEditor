#pragma once

#include <QLineEdit>

#include "../../Utilities/General.hpp"

namespace Visuals::Basics {

    struct LineEdit : QLineEdit {

        parametrize (LineEdit) {
            connection <const QString&, QLineEdit> { subscribe (QLineEdit::textEdited) } changed;
        };

        LineEdit() { }

        virtual ~LineEdit() { }

    };

}
