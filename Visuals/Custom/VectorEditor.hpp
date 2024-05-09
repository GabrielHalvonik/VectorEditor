#pragma once

#include <QFrame>

#include "../../Utilities/General.hpp"

namespace Visuals::Basics {
    struct LeftToolBar;
    struct BottomToolBar;
}

using namespace Visuals::Basics;

namespace Visuals::Custom {

    struct VectorEditor : QFrame {

        VectorEditor();

        virtual ~VectorEditor();

    protected:
        void resizeEvent(QResizeEvent *event) override;

    private:
        observable <const QSize&> editorViewSizeObservable;

        property <LeftToolBar*> leftToolBar;
        property <BottomToolBar*> bottomToolBar;
    };

}
