//
// Created by prang on 27.04.2024.
//

#include "src/Lockscreen/Lockscreen.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Lockscreen w;
    w.show();
    return a.exec();
}
