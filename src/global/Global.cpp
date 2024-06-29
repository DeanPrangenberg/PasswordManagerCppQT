//
// Created by prang on 27.04.2024.
//

#include "Global.h"
#include "../MainWindow/MainWindow.h"
#include "../Lockscreen/Lockscreen.h"

void global::geometry(QMainWindow* currentWindow) {
    currentWindow->setGeometry(50, 50, global::screenWidth, global::screenHeight);
}

////////////////////////////////////////////////////////
//                 Go to other window                 //
////////////////////////////////////////////////////////

void global::openLockscreen(QMainWindow* currentWindow) { // Added 'global::' before 'Lockscreen'
    Lockscreen* lockScreen = new Lockscreen;
    currentWindow->hide();
    lockScreen->show();
}

void global::openMainWindow(QMainWindow* currentWindow) { // Added 'global::' before 'Lockscreen'
    MainWindow* MainWin = new MainWindow;
    currentWindow->hide();
    MainWin->show();
}
