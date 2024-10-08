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

    void addPasswordEntry();

    void showPasswords();

    void showPasswordGen();

    void showMasterPasswordEdit();

    void showPasswordDel();

    void showAddEntry();

    void deletePasswordEntry();

    void showEditPassword();

    void checkChangeMasterPassword();

    void lockScreen();

    void ConfirmPassword();

    void onAllowLowAlphabetToggled(bool checked);

    void onAllowUpAlphabetToggled(bool checked);

    void onAllowNumbersToggled(bool checked);

    void onAllowSymbolsToggled(bool checked);

    void startPasswordGen();

    void searchRowEdit();

    void searchRowDel();

    void transferValues();

    void changePasswordEntry();

    void searchInList();

    void reloadList();

private:
    // UI setup
    void setupSidebar();

    void setupTopbar();

    void setupPasswordList();

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
    QPushButton *_ButtonReload;
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

    // center normal Password editor
    QWidget *_centerNormPasswordEdit;
    QLineEdit *_inputRowEdit;
    QLineEdit *_inputNewName;
    QLineEdit *_inputNewUsername;
    QLineEdit *_inputNewPassword;

    QLabel *_showOldName;
    QLabel *_showOldUsername;
    QLabel *_showOldPassword;
    QLabel *_showNewName;
    QLabel *_showNewUsername;
    QLabel *_showNewPassword;
    QPushButton *_saveChangesNormPasswordEdit;

    // center delete password
    QWidget *_centerPasswordDel;
    QLineEdit *_inputRowDel;
    QLabel *_showOldNameDel;
    QLabel *_showOldUsernameDel;
    QLabel *_showOldPasswordDel;

    // add new entry
    QWidget *_centerAddPassword;
    QLineEdit *_inputAddName;
    QLineEdit *_inputAddUsername;
    QLineEdit *_inputAddPassword;
    QLabel *_showAddName;
    QLabel *_showAddUsername;
    QLabel *_showAddPassword;
    QPushButton *_saveNewPasswordButton;

    // Data storage
    QVector<QVector<QString>> _passwordList;
    QVector<QVector<QString>> _showPasswordList;

    // Constants
    const QString allChars = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
    const int _screenWidth = 1050; //norm 1050
    const int _screenHeight = 650; //norm 650
    const int _middleWidthScreen = _screenWidth / 2;
    const int _middleHeightScreen = _screenHeight / 2;

    // Global var
    QString _masterPassword;
    QString _allowedCharsPasswordGen;

    // Style
    QString groupBoxStyle = QString(
            "QGroupBox {"
            "    border: 1px solid #BDBDBD; /* Rahmen der GroupBox */"
            "    border-radius: 5px; /* Abgerundete Ecken */"
            "    margin-top: 20px; /* Abstand für den Titel */"
            "    background-color: #6495ED; /* Hintergrundfarbe */"
            "}"
            "QGroupBox::title {"
            "    subcontrol-origin: margin; /* Ursprung des Titels */"
            "    subcontrol-position: top left; /* Position des Titels */"
            "    padding: 0 5px; /* Innenabstand des Titels */"
            "    color: #0047AB; /* Textfarbe des Titels */"
            "    background-color: #FFFFFF; /* Hintergrundfarbe des Titels (falls benötigt) */"
            "    border-radius: 3px; /* Abgerundete Ecken des Titels */"
            "}"
    );
    QString QLineEditStyle = QString("QLineEdit {"
                                "    border: 1px solid #BDBDBD; /* Rahmen des Eingabefelds */"
                                "    padding: 5px; /* Innenabstand */"
                                "    border-radius: 10px; /* Abgerundete Ecken */"
                                "}"
    );
};

#endif // PASSWORDMANAGERCPPQT_MAINWINDOW_H