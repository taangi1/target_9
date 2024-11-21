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

    void hoverEffect();

    void unHoverEffect();

    void updateDifficulty();

    void undoAction();

    void redoAction();

private:
    /**
     * @brief Shows a win pop-up message when player wins.
     */
    int showPopup(int level);

    /**
     * @brief Updates all cells in grid layout.
     */
    void updateCells();

    GameLogic::Move getButtonRowCol(QPushButton *button) const;

    Ui::MainWindow *ui;
    GameLogic game;
};
#endif // MAINWINDOW_H
