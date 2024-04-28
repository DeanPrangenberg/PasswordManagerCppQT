//
// Created by prang on 27.04.2024.
//

#ifndef PASSWORDMANAGERCPPQT_LOCKSCREEN_H
#define PASSWORDMANAGERCPPQT_LOCKSCREEN_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QApplication>

class Lockscreen : public QMainWindow {
Q_OBJECT

public:
    Lockscreen(QWidget *parent = nullptr);

private slots:
    void ConfirmPassword();
    void checkPassword();

private:
    QPushButton *_buttonConfirm;
    QLineEdit *_inputField; // Declare QLineEdit member variable
    std::string passwordUserIn; // Declare passwordUserIn as a member variable
    std::string MasterPassword = "gg";
};
#endif //PASSWORDMANAGERCPPQT_LOCKSCREEN_H
