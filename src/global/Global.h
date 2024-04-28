//
// Created by prang on 27.04.2024.
//

#ifndef PASSWORDMANAGERCPPQT_GLOBAL_H
#define PASSWORDMANAGERCPPQT_GLOBAL_H

#include <QMainWindow>

namespace global {

    const int screenHeight = 650; //norm 650
    const int screenWidth = 1050; //norm 1050

    const int middleWidthScreen = screenWidth / 2;
    const int middleHeightScreen = screenHeight / 2;

    void geometry(QMainWindow *currentWindow);
    void openLockscreen(QMainWindow *currentWindow);
    void openMainWindow(QMainWindow *currentWindow);
}

#endif //PASSWORDMANAGERCPPQT_GLOBAL_H
