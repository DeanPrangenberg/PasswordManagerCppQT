//
// Created by prang on 27.04.2024.
//

#include "src\MainWindow\MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
