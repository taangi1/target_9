/**
 * @file mainwindow.hpp
 * @brief This file defines the MainWindow class, which serves as the main application window.
 *
 * The MainWindow class inherits from QMainWindow and contains the user interface elements
 * and logic for the main application window. It manages interactions with the user and
 * coordinates the game logic through the GameLogic class.
 *
 * @author Ignat Romanov
 * @version 1.0
 * @date 19.11.2024
 */

#include "gamelogic.hpp"
#include <QMainWindow>
#include <QPushButton>

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

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

    /**
     * @brief Determine and highlight a cell containing the best move.
     */
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

    /**
     * @brief Highlights a button based on a game move.
     *
     * This function takes a move from the game logic and highlights the corresponding button.
     *
     * @param move The move to be highlighted.
     */
    void highlightButton(const GameLogic::Move &move);

    /**
     * @brief Highlights a specific QPushButton.
     *
     * This function highlights the provided QPushButton.
     *
     * @param button Pointer to the QPushButton to be highlighted.
     */
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

    /**
     * @brief Retrieves the QPushButton associated with a specific game move.
     *
     * This function takes a game move as input and returns the corresponding
     * QPushButton that represents that move in the user interface.
     * If no button is associated with the given move, the function may return
     * a nullptr.
     *
     * @param move The game move for which to retrieve the associated button.
     * @return A pointer to the QPushButton associated with the move, or nullptr
     *         if no such button exists.
     */
    QPushButton *getButtonByMove(const GameLogic::Move &move) const;

    Ui::MainWindow *ui;
    GameLogic game;
    bool show_colors;
};
#endif // MAINWINDOW_HPP
