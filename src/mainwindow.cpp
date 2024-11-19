/**
 * @file mainwindow.cpp
 * @brief Implementation of MainWindow class from mainwindow.h
 * @author Ignat Romanov
 * @version 0.1
 * @date 19.11.2024
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); // Set up the ui.

    // Connect the signal from pressing button b31 to showWin slot.
    connect(ui->b31, &QPushButton::clicked, this, &MainWindow::showWin);

    // Connect the signal from difficulty slider value change to updateDifficultyLabel slot.
    connect(ui->slider_difficulty, &QSlider::valueChanged, this, &MainWindow::updateDifficultyLabel);

    // Set the default slider value to label.
    updateDifficultyLabel(ui->slider_difficulty->value());
}

MainWindow::~MainWindow()
{
    delete ui; // Delete ui to prevent memory leak.
}

void MainWindow::showWin() {
    QMessageBox msgBox; // Pop-up.
    msgBox.setWindowTitle("Congratulations!"); // Set the title of pop-up.
    msgBox.setText("You Won!"); // Set the text of pop-up.
    msgBox.setIcon(QMessageBox::Information); 
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Reset); // Add two buttons to pop-up.
    msgBox.exec();
}

void MainWindow::updateDifficultyLabel(int value) {
    ui->label_difficulty->setText(QString("Difficulty: %1").arg(value)); // Set text of label_difficulty.
}
