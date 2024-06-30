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
#include <QVector>
#include <QString>
#include <QListWidget>
#include <QScrollArea>
#include <QDebug>
#include <QRandomGenerator>
#include <QFont>
#include <QMessageBox>
#include <QMouseEvent>
#include <QClipboard>
#include <QFile>
#include <QGridLayout>

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
    QPushButton *_ButtonOpenLockscreen;
    QPushButton *_ButtonChangeMasterPassword;
    QPushButton *_ButtonDelPassword;
    QPushButton *_ButtonEditPassword;

    // Topbar
    QHBoxLayout *_topBarLayout;
    QWidget *_topBarWidget;
    QPushButton *_ButtonStartSearch;
    QPushButton *_ButtonChangeSort;
    QLineEdit *_inputSearch;

    // Center Widget
    QWidget *_centerPasswordList;
    QScrollArea *_scrollArea;
    QGridLayout *_gridLayout;

    // Data
    QVector<QVector<QString>> _passwordList;

    // Helper functions
    void setupSidebar();
    void setupTopbar();
    void setupCenterPasswordList();
    void populateGrid();

    void readPasswordFromFile();
    void writePasswordsInFile();

    void copySelectedText(QListWidgetItem *item);

    const QString allChars = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
    QString genKey();
    QString genPassword(int length, QString allowedChars);
    QString decryptString(const QString &input, const QString &key);
    QString encryptString(const QString &input, const QString &key);

    void encryptPasswords();
    void decryptPasswords();
};

#endif // PASSWORDMANAGERCPPQT_MAINWINDOW_H
