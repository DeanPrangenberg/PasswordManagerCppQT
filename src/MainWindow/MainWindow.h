//
// Created by prang on 27.04.2024.
//

#ifndef PASSWORDMANAGERCPPQT_MAINWINDOW_H
#define PASSWORDMANAGERCPPQT_MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void changeSort();
    void newEntry();
    void showPasswords();
    void showPasswordGen();
    void delPassword();
    void editPassword();
    void ChangeMasterPassword();
    void lockScreen();

private:
    // Sidebar
    QWidget *_sidebarWidget;
    QVBoxLayout *_sidebarLayout;
    QLabel *_LabelLogo;
    QPushButton *_ButtonShowPasswords;
    QPushButton *_ButtonShowPasswordGen;
    QPushButton *_ButtonAddEntry;
    QPushButton *_ButtonCloseMenu;
    QPushButton *_ButtonChangeMasterPassword;
    QPushButton *_ButtonDelPassword;
    QPushButton *_ButtonEditPassword;

    // Topbar
    QHBoxLayout *_topBarLayout;
    QWidget *_topBarWidget;
    QPushButton *_ButtonStartSearch;
    QPushButton *_ButtonChangeSort;
    QLineEdit *_inputSearch;

};
#endif //PASSWORDMANAGERCPPQT_MAINWINDOW_H
