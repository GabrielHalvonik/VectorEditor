#include "ApplicationWindow.hpp"

#include "Visuals/Basics/Frame.hpp"
#include "Visuals/Custom/Label.hpp"
#include "Visuals/Basics/Widget.hpp"
#include "Visuals/Basics/ToolBar.hpp"
#include "Visuals/Basics/LineEdit.hpp"
#include "Visuals/Basics/StatusBar.hpp"
#include "Visuals/Basics/BoxLayout.hpp"
#include "Visuals/Custom/TopToolBar.hpp"
#include "Visuals/Basics/DockWidget.hpp"
#include "Visuals/Basics/ProgressBar.hpp"
#include "Visuals/Custom/LeftToolBar.hpp"
#include "Visuals/Basics/GraphicsView.hpp"
#include "Visuals/Custom/RightToolBar.hpp"
#include "Visuals/Basics/GraphicsScene.hpp"
#include "Visuals/Custom/VectorEditorView.hpp"
#include "Visuals/Basics/VerticalBoxLayout.hpp"

#include <QResizeEvent>
#include <QFrame>
#include <QStackedLayout>
#include <QPushButton>
#include <QGraphicsBlurEffect>
#include <QGraphicsItem>
#include <QAction>
#include <QList>
#include <QIcon>
#include <QSize>
#include <QStatusBar>

using namespace Visuals::Basics;
using namespace Visuals::Custom;

ApplicationWindow::ApplicationWindow() {

    this->setStatusBar(new StatusBar ({
        .height = 24
    }));
    // this->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea,  new QDockWidget(), Qt::Orientation::Vertical);
    this->setMinimumSize(600, 400);
    // new ToolBar ({  });
    this->addToolBar(Qt::ToolBarArea::TopToolBarArea, new TopToolBar ({
        .height = 34,
        .actions = {
            new QAction (QIcon::fromTheme(QIcon::ThemeIcon::EditUndo), "Undo"),
            new QAction (QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackPause), "Redo"),
            new QAction (QIcon::fromTheme(QIcon::ThemeIcon::EditRedo), "Redo"),
        }
    }));

    this->addToolBar(Qt::ToolBarArea::RightToolBarArea, new RightToolBar ({
        .width = 300,
        .actions = {
            new QAction (QIcon::fromTheme(QIcon::ThemeIcon::EditUndo), "Undo"),
            new QAction (QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackPause), "Redo"),
            new QAction (QIcon::fromTheme(QIcon::ThemeIcon::EditRedo), "Redo"),
        }
    }));

    auto scene = new QGraphicsScene(0, 0, 2000, 2000);
    QGraphicsItem* it = scene->addText("pass");
    it->setPos(200, 200);
    this->setCentralWidget(new VectorEditorView ({
        .scene = scene,
        .items = {
            new LeftToolBar ({
                .geometry = bind (editorViewSizeObservable) into <QRect> {
                    return QRect(10, 10, 32, value.height() - 20);
                    // return QRect(10, value.height() / 2 - value.height()/2 + 100, 32, value.height() - 200);
                }
            }),
        },
        .sizeChanged = editorViewSizeObservable,
        // .sizeChanged = { [this](const QSize& a) { qInfo() << a.height() << "aaa"; } },
    }));

    // QFrame* centralFrame = new QFrame(this);
    // QGraphicsBlurEffect* p_blur = new QGraphicsBlurEffect;
    // p_blur->setBlurRadius(30);
    // p_blur->setBlurHints(QGraphicsBlurEffect::QualityHint);
    // centralFrame->setGraphicsEffect(p_blur);
    // auto l = new QStackedLayout();
    // l->addWidget(new QPushButton());
    // centralFrame->setLayout(l);
    // centralFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    // centralFrame->setMidLineWidth(3);

    // centralFrame->setGeometry(10, 10, 48, 800);
}

ApplicationWindow::~ApplicationWindow() { }



void ApplicationWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    windowSizeObservable = event->size();
}
