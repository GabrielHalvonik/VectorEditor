#pragma once

#include <QGraphicsView>
#include <QResizeEvent>

#include "../../Utilities/General.hpp"

namespace Visuals::Basics {

    struct VectorEditorView : QGraphicsView {

        parametrize (VectorEditorView) {
            parameter <QGraphicsScene*> { affect (QGraphicsView::setScene) } scene;
            parameter <const list<QWidget*>&> { affect (VectorEditorView::addMultipleWidget) } items;
            handler <const QSize&> { attach (VectorEditorView::sizeChanged) } sizeChanged;

            // struct : Handler { using Handler::Handler;
        };

        VectorEditorView() {
            this->setDragMode(QGraphicsView::DragMode::ScrollHandDrag);
            this->setBackgroundBrush(QBrush(QColor::fromRgb(35, 35, 35)));
            setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
            setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        }

        virtual ~VectorEditorView() { }



        void addMultipleWidget(const list<QWidget*>& widgets) {
            for (QWidget* widget : widgets) {
                widget->setParent(this);
            }
        }

    protected:
        void resizeEvent(QResizeEvent* event) override {
            QGraphicsView::resizeEvent(event);
            sizeChanged(event->size());
        }

    private:
        Event<const QSize&> sizeChanged;
    };

}

