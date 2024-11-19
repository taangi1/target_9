#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->b31, &QPushButton::clicked, this, &MainWindow::showMessageBox);
    connect(ui->slider_difficulty, &QSlider::valueChanged, this, &MainWindow::updateDifficultyLabel);

    updateDifficultyLabel(ui->slider_difficulty->value());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showMessageBox() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Congratulations!");
    msgBox.setText("You Won!");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setStandardButtons(QMessageBox::Ok);

    msgBox.exec();
}

void MainWindow::updateDifficultyLabel(int value) {
    ui->label_difficulty->setText(QString("Difficulty: %1").arg(value));
}
