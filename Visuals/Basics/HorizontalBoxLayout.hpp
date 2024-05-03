#pragma once

#include <QHBoxLayout>

#include "../../Utilities/General.hpp"

namespace Visuals::Basics {

    struct HorizontalBoxLayout : QHBoxLayout {

        parametrize (HorizontalBoxLayout) {
            parameter <list<QWidget*>> { affect(HorizontalBoxLayout::addMultipleWidget) } items;
        };

        HorizontalBoxLayout() { }

        virtual ~HorizontalBoxLayout() { }

        void addMultipleWidget(list<QWidget*> widgets) {
            for (auto widget : widgets) {
                this->addWidget(widget);
            }
        }

    };

}
