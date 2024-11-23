/**
 * @file mainwindow.cpp
 * @brief Implementation of MainWindow class from mainwindow.h
 * @author Ignat Romanov
 * @version 0.1
 * @date 19.11.2024
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hoverbutton.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this); // Set up the ui.

    for (int i = 0; i < ui->gridLayout->count(); ++i)
    {
        QLayoutItem *item = ui->gridLayout->itemAt(i);
        HoverButton *button = qobject_cast<HoverButton *>(item->widget());
        if (button)
        {
            connect(button, &HoverButton::clicked, this, &MainWindow::playCell);
            connect(button, &HoverButton::hovered, this, &MainWindow::hoverEffect);
            connect(button, &HoverButton::unhovered, this, &MainWindow::unHoverEffect);
        }
    }

    // Connect the signal from difficulty slider value change to updateDifficultyLabel slot.
    connect(ui->slider_difficulty, &QSlider::valueChanged, this, &MainWindow::updateDifficultyLabel);
    connect(ui->slider_difficulty, &QSlider::sliderReleased, this, &MainWindow::updateDifficulty);

    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionNew_Game, &QAction::triggered, this, &MainWindow::updateDifficulty);

    connect(ui->actionUndo, &QAction::triggered, this, &MainWindow::undoAction);
    connect(ui->actionRedo, &QAction::triggered, this, &MainWindow::redoAction);
    connect(ui->actionShow_Colors, &QAction::triggered, this, &MainWindow::colorsToggle);
    connect(ui->actionHint, &QAction::triggered, this, &MainWindow::hintAction);

    show_colors = true;

    // Set the default slider value to label.
    updateDifficultyLabel(ui->slider_difficulty->value());

    game.init();

    updateCells();
}

MainWindow::~MainWindow()
{
    delete ui; // Delete ui to prevent memory leak.
}

int MainWindow::showPopup(int level)
{
    QMessageBox msgBox; // Pop-up.
    switch (level)
    {
    case 2:
    {
        msgBox.setWindowTitle("Warning");             // Set the title of pop-up.
        msgBox.setText("All progress will be lost!"); // Set the text of pop-up.
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Apply | QMessageBox::Discard); // Add two buttons to pop-up.
        msgBox.setDefaultButton(QMessageBox::Discard);
        int ret = msgBox.exec();
        switch (ret)
        {
        case QMessageBox::Apply:
        {
            return 1;
            break;
        }

        default:
            return 0;
            break;
        }
        break;
    }

    case 0:
    {
        msgBox.setWindowTitle("Congratulations!"); // Set the title of pop-up.
        msgBox.setText("You WIN!");                // Set the text of pop-up.
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Reset); // Add two buttons to pop-up.
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        switch (ret)
        {
        case QMessageBox::Ok:
        {
            return 0;
            break;
        }

        default:
            return 1;
            break;
        }
        break;
    }

    default:
        break;
    }
    return 0;
}

void MainWindow::updateDifficultyLabel(int value)
{
    ui->label_difficulty->setText(QString("Difficulty: %1").arg(value)); // Set text of label_difficulty.
}

void MainWindow::playCell()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    GameLogic::Move move = getButtonRowCol(button);
    game.makeMove(move);
    updateCells();
    if (game.isWin())
    {
        if (showPopup(0))
        {
            game.init();
        }
        else
            disable_all();
    }
    updateCells();
}

void MainWindow::hoverEffect()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    GameLogic::Move selected = getButtonRowCol(button);

    for (int i = 0; i < ui->gridLayout->count(); ++i)
    {
        QLayoutItem *item = ui->gridLayout->itemAt(i);
        QPushButton *button = qobject_cast<QPushButton *>(item->widget());
        GameLogic::Move move = getButtonRowCol(button);

        if (move.row == selected.row || move.col == selected.col)
        {
            button->setStyleSheet(button->styleSheet().append(QString("border: 5px solid red;")));
            button->setStyleSheet(button->styleSheet().append(QString("padding: 5px;")));
        }
    }
}

void MainWindow::unHoverEffect()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    GameLogic::Move selected = getButtonRowCol(button);

    for (int i = 0; i < ui->gridLayout->count(); ++i)
    {
        QLayoutItem *item = ui->gridLayout->itemAt(i);
        QPushButton *button = qobject_cast<QPushButton *>(item->widget());
        GameLogic::Move move = getButtonRowCol(button);

        if (move.row == selected.row || move.col == selected.col)
        {
            button->setStyleSheet(button->styleSheet().remove(QString("border: 5px solid red;")));
            button->setStyleSheet(button->styleSheet().remove(QString("padding: 5px;")));
        }
    }
}

void MainWindow::updateDifficulty()
{
    if (showPopup(2))
    {
        QString difficultyText = ui->label_difficulty->text();

        QStringList parts = difficultyText.split(": "); // Split the string by ": "
        if (parts.size() == 2)
        {
            bool ok;                                   // Variable to check if conversion was successful
            int difficultyLevel = parts[1].toInt(&ok); // Convert the second part to int

            if (ok)
            { // Check if conversion was successful
                game.setDifficulty(difficultyLevel);
                game.init(); // Initialize the game
                enable_all();
                updateCells();
            }
            else
            {
                // Handle the error: conversion failed
                QMessageBox::warning(this, "Error", "Invalid difficulty level.");
            }
        }
        else
        {
            // Handle the error: unexpected format
            QMessageBox::warning(this, "Error", "Unexpected difficulty label format.");
        }
    }
    else
    {
        ui->slider_difficulty->setValue(game.getDifficulty());
        updateDifficultyLabel(game.getDifficulty());
    }
}

void MainWindow::undoAction()
{
    game.undoMove();
    updateCells();
}

void MainWindow::redoAction()
{
    game.redoMove();
    updateCells();
}

void MainWindow::colorsToggle()
{
    show_colors = !show_colors;
    updateCells();
}

void MainWindow::hintAction()
{
    GameLogic::Move nextMove = game.hintNextMove();
    highlightButton(nextMove);
}

void MainWindow::updateCells()
{
    for (int i = 0; i < ui->gridLayout->count(); ++i)
    {
        QLayoutItem *item = ui->gridLayout->itemAt(i);
        QPushButton *button = qobject_cast<QPushButton *>(item->widget());
        GameLogic::Move move = getButtonRowCol(button);
        button->setText(QString::number(game.getBoardValue(move)));
        if (show_colors)
            button->setStyleSheet("background-color: " + getColorForValue(button->text()).name() + ";");
        else
            button->setStyleSheet("");
        ui->label_moves->setText(QString("Moves: %1").arg(game.getNumMoves()));
    }

    ui->actionHint->setEnabled(game.isCanHint());
    ui->actionRedo->setEnabled(game.isCanRedo());
    ui->actionUndo->setEnabled(game.isCanUndo());
        
}

void MainWindow::highlightButton(const GameLogic::Move &move)
{
    QPushButton *button = getButtonByMove(move);
    if (button)
    {
        button->setStyleSheet(button->styleSheet().append(QString("border: 5px solid yellow;")));
        button->setStyleSheet(button->styleSheet().append(QString("padding: 5px;")));
    }
}

void MainWindow::highlightButton(QPushButton *button)
{
    if (button)
    {
        button->setStyleSheet(button->styleSheet().append(QString("border: 5px solid yellow;")));
        button->setStyleSheet(button->styleSheet().append(QString("padding: 5px;")));
    }
}

QColor MainWindow::getColorForValue(const QString &value)
{
    if (value == "1")
        return QColor(255, 192, 203); // Pastel Pink
    if (value == "2")
        return QColor(173, 216, 230); // Pastel Cyan
    if (value == "3")
        return QColor(255, 255, 224); // Pastel Yellow
    if (value == "4")
        return QColor(255, 182, 100); // Pastel Red
    if (value == "5")
        return QColor(144, 238, 144); // Pastel Green
    if (value == "6")
        return QColor(255, 218, 185); // Pastel Peach
    if (value == "7")
        return QColor(221, 160, 221); // Pastel Violet
    if (value == "8")
        return QColor(240, 230, 140); // Pastel Olive
    if (value == "9")
        return QColor(255, 160, 122); // Pastel Salmon
    return QColor(255, 255, 255);     // Default color (white)
}

void MainWindow::disable_all()
{
    for (int i = 0; i < ui->gridLayout->count(); ++i)
    {
        QLayoutItem *item = ui->gridLayout->itemAt(i);
        HoverButton *button = qobject_cast<HoverButton *>(item->widget());
        if (button)
        {
            disconnect(button, &HoverButton::clicked, this, &MainWindow::playCell);
            disconnect(button, &HoverButton::hovered, this, &MainWindow::hoverEffect);
            disconnect(button, &HoverButton::unhovered, this, &MainWindow::unHoverEffect);
        }
    }
}

void MainWindow::enable_all()
{
    disable_all(); // To prevent errors.
    for (int i = 0; i < ui->gridLayout->count(); ++i)
    {
        QLayoutItem *item = ui->gridLayout->itemAt(i);
        HoverButton *button = qobject_cast<HoverButton *>(item->widget());
        if (button)
        {
            connect(button, &HoverButton::clicked, this, &MainWindow::playCell);
            connect(button, &HoverButton::hovered, this, &MainWindow::hoverEffect);
            connect(button, &HoverButton::unhovered, this, &MainWindow::unHoverEffect);
        }
    }
}

GameLogic::Move MainWindow::getButtonRowCol(QPushButton *button) const
{
    if (button)
    {
        QString buttonName = button->objectName(); // Get name of the button.

        // Extract row and column from the button name.
        if (buttonName.startsWith("b") && buttonName.length() == 3) // Check if the name is in the expected format.
        {
            int row = buttonName[1].digitValue(); // Get the first index (row)
            int col = buttonName[2].digitValue(); // Get the second index (col)
            return GameLogic::Move({row, col});
        }
    }
    return GameLogic::Move({-1, -1});
}

QPushButton *MainWindow::getButtonByMove(const GameLogic::Move &move) const
{
    for (int i = 0; i < ui->gridLayout->count(); ++i)
    {
        QLayoutItem *item = ui->gridLayout->itemAt(i);
        if (item)
        {
            QWidget *widget = item->widget();
            if (widget && qobject_cast<QPushButton *>(widget))
            {
                QPushButton *button = qobject_cast<QPushButton *>(widget);
                if (button->objectName().contains(QString::number(move.row) + QString::number(move.col), Qt::CaseInsensitive))
                {
                    return button;
                }
            }
        }
    }
    return nullptr;
}
