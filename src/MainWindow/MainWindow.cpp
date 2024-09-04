#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->setGeometry(50, 50, _screenWidth, _screenHeight);
    this->setFixedSize(_screenWidth, _screenHeight);

    checkIfFirstStart();
    // fillPasswords();
    // encryptPasswords();
    decryptPasswords();

    _showPasswordList = _passwordList;

    // setup all widgets
    setupLockscreen();
    setupPasswordList();
    setupPasswordGen();
    setupEditMaster();
    setupAddPassword();
    setupPasswordDel();
    setupPasswordEdit();
    setupPasswordDel();
    setupSidebar();
    setupTopbar();
}

///////////////
// off/on ui //
///////////////

void MainWindow::showStdMenu() {
    hideAll();
    showBars();
    _centerPasswordList->show();
    decryptPasswords();
    populateGrid();
}

void MainWindow::hideAll() {
    _sideBarWidget->hide();
    _topBarWidget->hide();
    _LabelLogo->hide();

    _lockscreenWidget->hide();

    _centerPasswordList->hide();
    _centerPasswordGen->hide();
    _centerMasterPasswordEdit->hide();
    _centerNormPasswordEdit->hide();
    _centerPasswordDel->hide();
    _centerAddPassword->hide();
}

void MainWindow::showBars() {
    _sideBarWidget->show();
    _topBarWidget->show();
    _LabelLogo->show();
}
