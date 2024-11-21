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
        msgBox.setWindowTitle("Warning");                                                  // Set the title of pop-up.
        msgBox.setText("Changing this setting will overwrite current state of the game!"); // Set the text of pop-up.
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
        msgBox.setWindowTitle("Congratulations!");                                                  // Set the title of pop-up.
        msgBox.setText("You WIN!"); // Set the text of pop-up.
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
            game.init();
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
            button->setStyleSheet(
                "QPushButton {"
                "   border: 5px solid red;" // Set the border color to red
                "   padding: 5px;"
                "}");
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
            button->setStyleSheet("");
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

void MainWindow::updateCells()
{
    for (int i = 0; i < ui->gridLayout->count(); ++i)
    {
        QLayoutItem *item = ui->gridLayout->itemAt(i);
        QPushButton *button = qobject_cast<QPushButton *>(item->widget());
        GameLogic::Move move = getButtonRowCol(button);
        button->setText(QString::number(game.getBoardValue(move)));
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