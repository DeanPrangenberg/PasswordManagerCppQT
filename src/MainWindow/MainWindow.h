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
#include <QCheckBox>
#include <QGroupBox>
#include <QInputDialog>

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void changeSort();
    void newEntry();
    void showPasswords();
    void showPasswordGen();
    void showMasterPasswordEdit();
    void delPassword();
    void editPassword();
    void checkChangeMasterPassword();
    void lockScreen();
    void ConfirmPassword();
    void onAllowLowAlphabetToggled(bool checked);
    void onAllowUpAlphabetToggled(bool checked);
    void onAllowNumbersToggled(bool checked);
    void onAllowSymbolsToggled(bool checked);
    void startPasswordGen();

private:
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
    void showBars();

    // data handling
    void populateGrid();
    void checkIfFirstStart();
    void checkPassword();
    void fillPasswords();
    void encryptPasswords();
    void decryptPasswords();
    QString genKey();
    QString genPassword(int length, QString allowedChars);
    QString encryptString(const QString &input, const QString &key);
    QString decryptString(const QString &input, const QString &key);
    void updateAllowedCharacters();

    // Lockscreen
    QWidget *_lockscreenWidget;
    QVBoxLayout *_lockscreenLayout;
    QPushButton *_buttonConfirm;
    QLineEdit *_inputField;
    QString _passwordUserIn;

    // Sidebar widgets
    QWidget *_sideBarWidget;
    QVBoxLayout *_sideBarLayout;
    QLabel *_LabelLogo;
    QPushButton *_ButtonShowPasswords;
    QPushButton *_ButtonShowPasswordGen;
    QPushButton *_ButtonAddEntry;
    QPushButton *_ButtonOpenLockscreen;
    QPushButton *_ButtonChangeMasterPassword;
    QPushButton *_ButtonDelPassword;
    QPushButton *_ButtonEditPassword;

    // Top bar widgets
    QHBoxLayout *_topBarLayout;
    QWidget *_topBarWidget;
    QPushButton *_ButtonStartSearch;
    QPushButton *_ButtonChangeSort;
    QLineEdit *_inputSearch;

    // Center password list
    QWidget *_centerPasswordList;
    QScrollArea *_scrollArea;
    QGridLayout *_gridLayout;

    // Center password generator
    QWidget *_centerPasswordGen;
    QLineEdit *_passwordOutput;
    QLabel *_showLowAlphabet;
    QLabel *_showUpAlphabet;
    QLabel *_showNumbers;
    QLineEdit *_showAllowedSymbols;
    QLineEdit *_passwordLengthInput;
    QCheckBox *_allowLowAlphabet;
    QCheckBox *_allowUpAlphabet;
    QCheckBox *_allowNumbers;
    QCheckBox *_allowSymbols;
    QPushButton *_startPasswordGen;
    bool _allowLowAlphabetChecked;
    bool _allowUpAlphabetChecked;
    bool _allowNumbersChecked;
    bool _allowSymbolsChecked;

    // center Master Password editor
    QWidget *_centerMasterPasswordEdit;
    QLineEdit *_inputOldMasterPassword;
    QLineEdit *_inputNewMasterPassword;
    QLabel *_oldMasterPasswordLabel;
    QLabel *_newMasterPasswordLabel;
    QPushButton *_changeMasterPassword;

    // Data storage
    QVector<QVector<QString>> _passwordList;

    // Constants
    const QString allChars = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
    const int _screenWidth = 1050; //norm 1050
    const int _screenHeight = 650; //norm 650
    const int _middleWidthScreen = _screenWidth / 2;
    const int _middleHeightScreen = _screenHeight / 2;

    // Global var
    QString _masterPassword;

    QString _allowedCharsPasswordGen;
};

#endif // PASSWORDMANAGERCPPQT_MAINWINDOW_H