#ifndef HOVERBUTTON_H
#define HOVERBUTTON_H

#include <QPushButton>
#include <QEvent>
#include <QEnterEvent>

class HoverButton : public QPushButton {
    Q_OBJECT
public:
    // explicit HoverButton(QWidget *parent = nullptr) : QPushButton(parent) {}
    using QPushButton::QPushButton;
signals:
    void hovered();   // Custom signal for hover
    void unhovered(); // Custom signal for unhover

protected:
    // void enterEvent(QEnterEvent * event) override {
    //     emit hovered(); // Emit the custom signal
    //     QPushButton::enterEvent(event);
    // }
    virtual void enterEvent(QEnterEvent * event){
       emit hovered();
       QPushButton::enterEvent(event);
    }

    virtual void leaveEvent(QEvent * event){
       emit unhovered();
       QPushButton::leaveEvent(event);
    }
};

#endif // HOVERBUTTON_H
