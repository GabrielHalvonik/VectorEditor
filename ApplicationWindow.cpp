#include "ApplicationWindow.hpp"

#include "Visuals/Basics/Widget.hpp"
#include "Visuals/Basics/VerticalBoxLayout.hpp"
#include "Visuals/Basics/Label.hpp"
#include "Visuals/Basics/LineEdit.hpp"
#include "Visuals/Basics/ProgressBar.hpp"

using namespace Visuals::Basics;

ApplicationWindow::ApplicationWindow() {

    this->setCentralWidget(new Widget ({
        .layout = new VerticalBoxLayout ({
            .items = {
                new Label ({
                    .text = observableText = "bp",
                }),
                new LineEdit ({
                    .changed = {
                        [this](auto value) {
                            observableText = value;
                        }
                    },
                }),
                new Label ({
                    .text = bind (observableText) into <QString> {
                        if (value.length() == 0) return { "[Empty]" };
                        else if (value.length() <= 5) return { value };
                        else return { value.sliced(0, 5) };
                    },
                }),
                new ProgressBar ({
                    .value = bind (observableText) into <int> {
                        if (value.length() > 10) return { };
                        else return { int(value.length() % 11) * 10 };
                    }
                })
            }
        })
    }));
}

ApplicationWindow::~ApplicationWindow() {

}
