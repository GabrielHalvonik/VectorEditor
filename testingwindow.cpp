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
                    .text = observableText = "default",     // Label's setText is invoked everytime observableText changes. it is initially triggered with "default"
                }),
                new LineEdit ({
                    // .textChanged = observableText,          // bind techChanged changes into observableText
                    // these two are equivalent in this case, bottom approach allow to do more then just bind to observable
                    .textChanged = {                        // react to textChanged with lambda function
                        [this](auto value) {
                            observableText = value;
                        }
                    },
                }),
                new Label ({
                    .text = bind (observableText) into <QString> {                  // anonymous binding that is triggered by invoked observableText
                                if (value.length() == 0) return { "[Empty]" };      // and processed return value is binded to corresponded parameter
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
                    ) = 0                                           // default value can be set in initializer (has to be wrapped in parenthesis)
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
