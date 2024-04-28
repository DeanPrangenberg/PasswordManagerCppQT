//
// Created by prang on 27.04.2024.
//

#ifndef PASSWORDMANAGERCPPQT_MAINWINDOW_H
#define PASSWORDMANAGERCPPQT_MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QApplication>
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:


private:
    QLabel *_LabelLogo;

    // Sidebar
    QPushButton *_ButtonShowAll;
    QPushButton *_ButtonShowPasswords;
    QPushButton *_ButtonShowAddress;
    QPushButton *_ButtonShowBank;
    QPushButton *_ButtonShowPasswordGen;
    QPushButton *_ButtonShowSetting;

    // Topbar
    QPushButton *_ButtonAddEntry;
    QPushButton *_ButtonStartSearch;
    QLabel *_LabelNameListing;
    QLineEdit *_inputSearch;

    // var
    QString openTab;

};
#endif //PASSWORDMANAGERCPPQT_MAINWINDOW_H
