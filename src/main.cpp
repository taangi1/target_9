/**
 * @file main.cpp
 * @brief Main entry point to the target 9 game.
 *
 * This file contains the implementation of the main function, which initializes
 * the QApplication, creates the main window, sets its properties, and starts
 * the event loop for the Target 9 Game application.
 *
 * @author Ignat Romanov
 * @version 1.1
 * @date 15.12.2024
 */

#include "mainwindow.hpp"

#include <QApplication>

/**
 * @brief The main entry point of the target 9 game
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line argument strings.
 * @return int The exit status of the application.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    w.setWindowTitle("Target 9 Game");

    w.show();

    return a.exec();
}
