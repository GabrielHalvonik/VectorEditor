#include "TestingWindow.hpp"

#include "Visuals/Basics/Widget.hpp"
#include "Visuals/Basics/VerticalBoxLayout.hpp"
#include "Visuals/Custom/Label.hpp"
#include "Visuals/Basics/LineEdit.hpp"
#include "Visuals/Basics/ProgressBar.hpp"

using namespace Visuals::Basics;
using namespace Visuals::Custom;

TestingWindow::TestingWindow() {

    this->setCentralWidget(
    new Widget ({
        .layout = new VerticalBoxLayout ({
            .items = {
                new Label ({
                    .text = observableText = "default",
                }),
                new LineEdit ({
                    .textChanged = observableText,
                    // .textChanged = {
                    //     [this](const QString& value) {
                    //         observableText = value;
                    //     }
                    // },
                }),
                new Label ({
                    .text = bind (observableText) into <QString> {
                                if (value.length() == 0) return { "[Empty]" };
                                else if (value.length() <= 10) return { value };
                                else return { value.sliced(0, 10) };
                            }
                }),
                new ProgressBar ({
                    .value = (
                        bind (observableText) into <int> {
                            if (value.length() > 10) return { };
                            else return { int(value.length() % 11) * 10 };
                        }
                    ) = 0
                })
            }
        })
    })
);

// new Widget ({
//     .layout = new VerticalBoxLayout ({
//         .items = {
//             new Label ({
//                 .text = observableText = "default",
//             }),
//             new LineEdit ({
//                 .changed = {
//                     delegate {
//                         observableText = value;
//                     }
//                 },
//             }),
//             new Label ({
//                 .text = (
//                     bind (observableText) into <QString> {
//                         if (value.length() == 0) return { "[Empty]" };
//                         else if (value.length() <= 10) return { value };
//                         else return { value.sliced(0, 10) };
//                     }
//                 )
//             }),
//             new ProgressBar ({
//                 .value = (
//                     bind (observableText) into <int> {
//                         if (value.length() > 10) return { };
//                         else return { int(value.length() % 11) * 10 };
//                     }
//                 ) = 20
//             })
//         }
//     })
// });
}

TestingWindow::~TestingWindow() { }
