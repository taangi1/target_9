/**
 * @file hoverbutton.hpp
 * @brief Custom QPushButton that emits signals on hover events.
 *
 * The HoverButton class extends the QPushButton class to provide
 * additional functionality for hover events. It emits a signal when
 * the mouse enters or leaves the button area, allowing for custom
 * behavior in response to hover actions.
 *
 * @author Ignat Romanov
 * @version 1.0
 * @date 20.11.2024
 */

#include <QPushButton>
#include <QEvent>
#include <QEnterEvent>

#ifndef HOVERBUTTON_HPP
#define HOVERBUTTON_HPP

/**
 * @class HoverButton
 * @brief A QPushButton that emits signals on hover.
 *
 * This class inherits from QPushButton and overrides the enter and
 * leave event handlers to emit custom signals when the mouse hovers
 * over or leaves the button. This can be useful for implementing
 * visual feedback or other interactions based on hover state.
 */
class HoverButton : public QPushButton
{
    Q_OBJECT
public:
    using QPushButton::QPushButton;
signals:
    void hovered();   // Custom signal for hover
    void unhovered(); // Custom signal for unhover

protected:
    /**
     * @brief Handles the event when the mouse enters the button area.
     *
     * This method emits the hovered() signal and then calls the base
     * class implementation to ensure normal behavior.
     *
     * @param event The QEnterEvent that triggered this method.
     */
    virtual void enterEvent(QEnterEvent *event)
    {
        emit hovered();
        QPushButton::enterEvent(event);
    }

    /**
     * @brief Handles the event when the mouse leaves the button area.
     *
     * This method emits the unhovered() signal and then calls the base
     * class implementation to ensure normal behavior.
     *
     * @param event The QEvent that triggered this method.
     */
    virtual void leaveEvent(QEvent *event)
    {
        emit unhovered();
        QPushButton::leaveEvent(event);
    }
};

#endif // HOVERBUTTON_HPP
