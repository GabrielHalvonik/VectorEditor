#pragma once

#include <QVBoxLayout>

#include "../../Utilities/General.hpp"

namespace Visuals::Basics {

    struct VerticalBoxLayout : QVBoxLayout {

        parametrize (VerticalBoxLayout) {
            parameter <list<QWidget*>> { affect(VerticalBoxLayout::addMultipleWidget) } items;
        };

        VerticalBoxLayout() { }

        virtual ~VerticalBoxLayout() { }

        void addMultipleWidget(list<QWidget*> widgets) {
            for (QWidget* widget : widgets) {
                this->addWidget(widget);
            }
        }

    };

}
