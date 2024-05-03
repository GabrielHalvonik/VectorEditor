#pragma once

#include <QLabel>
#include <QStyle>

#include "../../Utilities/General.hpp"


namespace Styles {

    struct {
        string name { "Visibility" };

        struct {
            string Visible { "Visible" };
            string Hidden { "Hidden" };
        } Values;

    } Visibility;

    struct {
        string name { "Hovered" };

        struct {
            string True { "True" };
            string False { "False" };
        } Values;

    } Hovered;

    struct {
        string name { "TextLength" };

        struct {
            string Empty { "Empty" };
            string Fine { "Fine" };
            string Long { "Long" };
        } Values;

    } TextLength;

}

namespace Styles {

    template <typename T>
    concept StyledProperty = requires(T style) {
        { style.name } -> std::same_as<string&>;
    };

    template <StyledProperty T>
    void set(QWidget* widget, const T& t, const string& value) {
        widget->setProperty(t.name.c_str(), value.c_str());
        widget->style()->polish(widget);
    }
}

namespace Visuals::Basics {

    struct Label : QLabel {

        parametrize (Label) {
            parameter <const QString&> { affect (Label::setText); } text;
            parameter <int> { affect (Label::setMinimumWidth); } width;
            parameter <int> { affect (Label::setMinimumHeight); } height;
        };

        Label() {
            Styles::set(this, Styles::TextLength, Styles::TextLength.Values.Empty);
            Styles::set(this, Styles::Hovered, Styles::Hovered.Values.False);
            Styles::set(this, Styles::Visibility, Styles::Visibility.Values.Hidden);
            // this->style()->polish(this);
            this->setObjectName("Label");
            // this->setText("PASS");
        }

        virtual ~Label() { }

    protected:
        void setText(const QString& text) {
            qInfo() << text.length();
            if (text.length() == 0) {
                Styles::set(this, Styles::TextLength, Styles::TextLength.Values.Empty);
            } else if (text.length() < 10) {
                Styles::set(this, Styles::TextLength, Styles::TextLength.Values.Fine);
            } else {
                Styles::set(this, Styles::TextLength, Styles::TextLength.Values.Long);
                QLabel::setText(text.sliced(0, 10)); return;
            }
            QLabel::setText(text);
        }
        void enterEvent(QEnterEvent *event) override {
            Styles::set(this, Styles::Hovered, Styles::Hovered.Values.True);
        }
        void leaveEvent(QEvent *event) override {
            Styles::set(this, Styles::Hovered, Styles::Hovered.Values.False);
        }
    };

}
