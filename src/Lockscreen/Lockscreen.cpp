//
// Created by prang on 27.04.2024.
//

#include "Lockscreen.h"
#include "../global/Global.h"

Lockscreen::Lockscreen(QWidget *parent) : QMainWindow(parent) {
    global::geometry(this);

    int inputFieldWidth = 200;
    int inputFieldHeight = 30;

    int buttonWidth = 200;
    int buttonHeight = 30;

    _inputField = new QLineEdit(this);
    _inputField->setGeometry(global::middleWidthScreen - (inputFieldWidth / 2), global::middleHeightScreen - inputFieldHeight, inputFieldWidth, inputFieldHeight); // Adjust the geometry as needed

    _buttonConfirm = new QPushButton("Confirm", this);
    _buttonConfirm->setGeometry(global::middleWidthScreen - (buttonWidth / 2), global::middleHeightScreen + 10, buttonWidth, buttonHeight); // Adjusted button size
    connect(_buttonConfirm, SIGNAL(clicked()), this, SLOT(ConfirmPassword()));
}

void Lockscreen::ConfirmPassword() {
    QString passwordText = _inputField->text();
    if (!(passwordText.toStdString().empty())) {
        passwordUserIn = passwordText.toStdString();
        qDebug() << "== passwordUserIn isn't \"\" its" << passwordUserIn;
        checkPassword();
    } else {
        _inputField->clear();
    }
}
void Lockscreen::checkPassword() {
    qDebug() << "== passwordUserIn is: " << passwordUserIn << "| MasterPassword: " << MasterPassword;
    if (passwordUserIn == MasterPassword) {
        qDebug() << "++ Password is correct!";
        global::openMainWindow(this);
    } else {
        _inputField->clear();
        qDebug() << "-- Password is wrong!";
        static int attemptsRemaining = 3;
        if (passwordUserIn != MasterPassword) {
            attemptsRemaining--;
            if (attemptsRemaining == 0) {
                QMessageBox::critical(this, "Too many tries", "You have entered too many incorrect passwords. The application will be closed.");
                QCoreApplication::quit();
            } else {
                QMessageBox::warning(this, "Wrong Password", "The entered password is incorrect. " + QString::number(attemptsRemaining) + " attempt(s) remaining.");
            }
        }
    }
}
