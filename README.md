Disclaimer: This repository is primarily my thought process focused on integrating a declarative programming style in C++ with graphical editor being testing platform for this idea. The project will most likely not be actively developed into a full-fledged vector graphics editor.

### Declarative C++ style API documentation (C++ 20 required):

#### General types:
  - #### Event\<T\>
    - Custom event implementation to register handlers to event parameter (T) changes (replacement for Qt's signal-slot mechanism without reflection involvement)
  - #### Observable\<T\>
    - Property of type (T) with similar functionality as **Event\<T\>** but can also be binded to **parameter\<T\>** for automatic function triggering and also can be used for custom anonymous binding (see later)
  - #### Property\<T\>
    - Wrapper for class attribute member with overloaded operators


### Object parametrization 

##### structure:
```c++
struct ClassName : OptionalBase {

    parametrize (ClassName) {
        ...                                    // parameter types (parameter<> | handler<> | connection<,>)
    };

    ClassName() : OptionalBase() { }           // default constructor required
};
```

In order to use object construction with [designated initializers](https://en.cppreference.com/w/cpp/language/aggregate_initialization#Designated_initializers) for your class, you have to add following construct:
```c++
    parametrize (ClassName) {
        ...
    };
```


### there are 3 possible parameter types:
#### (these three parameterized types can be combined or omitted when initializing the object)

- ### (1) Parameter (general C++)
  - structure:
    ```c++
    parametrize (ClassName) {
        parameter <parameter_type> { affect (FunctionOwnerClass::target_function) } parameter_name;
    };
    ```
    - **parameter_type**: Defines the data type accepted by the target_function.
    - **FunctionOwnerClass::target_function**: A function within FunctionOwnerClass that gets called if a value of parameter_type is provided for parameter during object creation. 
    
  - example:
    - declaration
     ```c++
       parametrize (Widget) {
           parameter <int> { affect (QWidget::setFixedHeight) } height;
           parameter <Layout*> { affect (QWidget::setLayout) } layout;
           parameter <const QRect&> { affect (QWidget::setGeometry) } geometry;
           parameter <const std::initializer_list<QWidget*>&> { affect(Widget::addChildren) } children;
       };
    ```
    - usage
     ```c++
       Widget ({
          .height = 30,
          .layout = new Layout(),
          .geometry = QGeometry(0, 0, 20, 20),
          .children = {
              new Widget ({
                  .height = 20
              }),
              new Widget ({
                  .layout = m_layout,
              })
          }
       });
    ```

- ### (2) Handler  (general C++)
  - structure:
    ```c++
    parametrize (ClassName) {
        handler <event_handling_type> { attach (EventOwnerClass::event_name) } handler_name;
    };
    ```
    - **event_handling_type**: type of parameter Event<type> is working with
    - **EventOwnerClass::event_name**: event within OwnerClass to register handler to
    
  - example:
    - declaration
     ```c++
       parametrize (Widget) {
           handler <const QSize&> { attach (Widget::sizeChangedEvent) } sizeChanged;
       };
    ```
    - usage
     ```c++
       Widget ({
          .sizeChanged = { [](const QSize&) { ...reaction code... } }
       });
    ```

 - ### (3) Connection  (Qt-framework specific)
    - structure:
      ```c++
      parametrize (ClassName) {
          connection <signal_parameter_type, SignalOwnerClass> { subscribe (SignalOwnerClass::signal_name) } connection_name;
      };
      ```
      - signal_parameter_type: type Qt's signal parameter
      - SignalOwnerClass::signal_name: signal within SignalOwnerClass to connect subsription handler to
      - due to Qt's reflection involvement in signal-slot mechanism, second template parameter **SignalOwnerClass** is required. Otherwise, parameterized class would also need to be marked with the Q_OBJECT macro (personal decision to not implement and prefer own Event<T> instead)
      
    - example:
      - declaration
       ```c++
         parametrize (LineEdit) {
             connection <const QString&, QLineEdit> { subscribe (QLineEdit::textEdited) } textChanged;
         };
      ```
      - usage
       ```c++
         LineEdit ({
            .textChanged = { [](const QString&) { ...reaction code... } }
         });
      ```

#### Additional features:
- Binding **observable \<T\>** into **parameter \<T\>**
  ```c++
   observable <const QString&> textObservable;   // class attribute member
   ...
   Label ({                                            
      .text = textObservable                    // bind textObservable into .text parameter so Label::setText() will be called every time observable changes
   }),
  ```
- Binding **observable \<T\>** into **handler \<T\>**
  ```c++
   observable <const QString&> textObservable;   // class attribute member
   ...
   LineEdit ({                                            
      .textChanged = textObservable             // bind textObservable into .textChanged handler so every time textChanged is invoked textObservable changes its state identically 
   }),
  ```
- Custom anonymous binding: 
  ```c++
   observable <const QString&> textObservable;                                    // class attribute member
   ...
   Label ({                                            
      .width = bind (textObservable) into <int> { return value.size() * 20;  }    // bind anonymous observable into .width parameter so Label::setWidth() will be called every time observable textObservable changes and binding value is calculated from the lambda return statement.
   }),
  ```
  - (observable that triggers anonymous binding is responsible for ownership of anonymous binding)

#### Complex sample:  

```c++
  struct Widget : QWidget {

        parametrize (Widget) {
            parameter <QLayout*> { affect (QWidget::setLayout) } layout;
            handler <const QSize&> { attach (Widget::sizeChanged) } sizeChanged;   
        };
            
        Widget() { }

    protected:
        void resizeEvent(QResizeEvent* event) override {
            sizeChanged(event->size());            
            //or                                            // invoking event's subscriptions
            sizeChanged.raise(event->size());
        }
        
    private:
        Event<const QSize&> sizeChanged;                    // custom Event
  };

  struct VerticalBoxLayout : QVBoxLayout {

        parametrize (VerticalBoxLayout) {
            parameter <const list<QWidget*>&> { affect(VerticalBoxLayout::addMultipleWidget) } items;
        };

        VerticalBoxLayout() { }

        void addMultipleWidget(const list<QWidget*>& widgets) {
            for (QWidget* widget : widgets) {
                QVBoxLayout::addWidget(widget);
            }
        }
  };

  struct Label : QLabel {

        parametrize (Label) {
            parameter <const QString&> { affect (QLabel::setText) } text;
        };

        Label() { }
  }

  struct LineEdit : QLineEdit {

        parametrize (LineEdit) {
            connection <const QString&, QLineEdit> { subscribe (QLineEdit::textEdited) } textChanged;
        };

        LineEdit() { }
  };

  struct ProgressBar : QProgressBar {

        parametrize (ProgressBar) {
            parameter <int> { affect (QProgressBar::setValue) } value;
        };

        ProgressBar() { }
   };

   struct MainWindow : QMainWindow {

       observable <QString> observableText;      // member attribute
       property <ProgressBar*> progressBar;      // member attribute

       MainWindow() {
          QMainWindow::setCentralWidget(
             new Widget ({
                  .sizeChanged = { [this](auto size) { progressBar->setFixedWidth(size.width); } },    // react to raised Event with lambda function that scales progressBar as widget scales
                  .layout = new VerticalBoxLayout ({
                      .items = {
                          new Label ({
                              .text = observableText = "default",     // Label's setText is invoked everytime observableText changes. it is initially triggered with "default" 
                          }),
                          new LineEdit ({
                              .textChanged = observableText,          // bind techChanged changes into observableText
                              // these two are equivalent in this case, bottom approach allow to do more then just bind to observable
                              .textChanged = {                        // react to textChanged (parametrized signal) with lambda function        
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
                          progressBar = new ProgressBar ({                    // asign allocated widget into member attribute progressBar 
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
       }
    }
  ```
        
