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
    void ConfirmPassword();

private:
    // Lockscreen
    QWidget *_lockscreenWidget{};
    QLayout *_lockscreenLayout{};
    QPushButton *_buttonConfirm{};
    QLineEdit *_inputField{};
    QString _passwordUserIn;

    // Sidebar widgets
    QWidget *_sideBarWidget{};
    QVBoxLayout *_sideBarLayout{};
    QLabel *_LabelLogo{};
    QPushButton *_ButtonShowPasswords{};
    QPushButton *_ButtonShowPasswordGen{};
    QPushButton *_ButtonAddEntry{};
    QPushButton *_ButtonOpenLockscreen{};
    QPushButton *_ButtonChangeMasterPassword{};
    QPushButton *_ButtonDelPassword{};
    QPushButton *_ButtonEditPassword{};

    // Top bar widgets
    QHBoxLayout *_topBarLayout{};
    QWidget *_topBarWidget{};
    QPushButton *_ButtonStartSearch{};
    QPushButton *_ButtonChangeSort{};
    QLineEdit *_inputSearch{};

    // Center password list widgets
    QWidget *_centerPasswordList{};
    QScrollArea *_scrollArea{};
    QGridLayout *_gridLayout{};

    // Data storage
    QVector<QVector<QString>> _passwordList;

    // UI setup
    void setupSidebar();
    void setupTopbar();
    void setupCenterPasswordList();
    void setupLockscreen();
    void setupPasswordGen();
    void setupPasswordEdit();
    void setupPasswordDel();
    void setupAddPassword();
    void setupEditMaster();

    // on/off Ui
    void hideAll();
    void showStdMenu();

    // data handling
    void checkPassword();
    QString genPassword(int length, QString allowedChars);
    void encryptPasswords();
    QString genKey();
    QString encryptString(const QString &input, const QString &key);
    void decryptPasswords();
    QString decryptString(const QString &input, const QString &key);
    void fillPasswords();
    void populateGrid();

    // Constants
    const QString allChars = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
    const int _screenHeight = 650; //norm 650
    const int _screenWidth = 1050; //norm 1050
    const int _middleWidthScreen = _screenWidth / 2;
    const int _middleHeightScreen = _screenHeight / 2;

    // Global var
    QString _masterPassword;


};

#endif // PASSWORDMANAGERCPPQT_MAINWINDOW_H