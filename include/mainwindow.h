/**
 * @file mainwindow.h
 * @brief This file defines the MainWindow class, which serves as the main application window.
 * @author Ignat Romanov
 * @version 0.1
 * @date 19.11.2024
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamelogic.h"
#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief The MainWindow class represents the main application window.
 *
 * This class inherits from QMainWindow and contains the UI elements and
 * logic for the main window of the application.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a MainWindow object.
     *
     * @param parent The parent widget (default is nullptr for a top-level window).
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destroys the MainWindow object.
     */
    ~MainWindow();

private slots:

    /**
     * @brief Updates the difficulty label based on the provided value.
     *
     * @param value The new difficulty value to display.
     */
    void updateDifficultyLabel(int value);

    /**
     * @brief Play the cell using GameLogic class.
     */
    void playCell();

    /**
     * @brief Highlights squares in same column and row by adding red border.
     */
    void hoverEffect();

    /**
     * @brief Deletes the red border set by hoverEffect().
     */
    void unHoverEffect();

    /**
     * @brief Update difficulty according to slider position. Show popup warning the user that progress will be removed.
     */
    void updateDifficulty();

    /**
     * @brief Undo last move.
     */
    void undoAction();

    /**
     * @brief Redo last move.
     */
    void redoAction();

    /**
     * @brief Enable or disable colors of squares. On by default.
     */
    void colorsToggle();

    void hintAction();

private:
    /**
     * @brief Shows a win pop-up message when player wins.
     */
    int showPopup(int level);

    /**
     * @brief Updates all cells in grid layout.
     */
    void updateCells();

    void highlightButton(const GameLogic::Move &move);
    void highlightButton(QPushButton *button);

    /**
     * @brief Helper function which returns QColor for given value of a text.
     * @param value Value of a text of QWidget.
     * @return QColor rgb color in pastel colors.
     */
    QColor getColorForValue(const QString &value);

    /**
     * @brief Disable all buttons.
     */
    void disable_all();

    /**
     * @brief Enable all buttons.
     */
    void enable_all();

    /**
     * @brief Helper function to extract row and column from button name.
     * @param button Button to extract name from.
     * @return GameLogic::Move
     */
    GameLogic::Move getButtonRowCol(QPushButton *button) const;

    QPushButton *getButtonByMove(const GameLogic::Move &move) const;

    Ui::MainWindow *ui;
    GameLogic game;
    bool show_colors;
};
#endif // MAINWINDOW_H
