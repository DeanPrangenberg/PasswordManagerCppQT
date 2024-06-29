#include "MainWindow.h"
#include "../global/Global.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    global::geometry(this);

    /////////////
    // Sidebar //
    /////////////

    // Geometric
    int logoHeight = 100;
    int logoWidth = 210;

    int spacingButtonSidebar = 10;
    int spacingSide = 10;

    int buttonsInSideBar = 7;

    int buttonWidthSidebar = logoWidth - spacingSide;
    int buttonHeightSidebar = (global::screenHeight - logoHeight - spacingButtonSidebar * (buttonsInSideBar + 1)) / buttonsInSideBar;

    // Logo
    _LabelLogo = new QLabel(this);
    QPixmap pixmap("../res/password-manager-logo-img.png");
    pixmap = pixmap.scaled(logoWidth, logoHeight, Qt::KeepAspectRatio);
    _LabelLogo->setPixmap(pixmap);
    _LabelLogo->setAlignment(Qt::AlignCenter);
    _LabelLogo->setFixedSize(logoWidth, logoHeight);

    // sidebar area
    _sidebarWidget = new QWidget(this);
    _sidebarWidget->setFixedWidth(buttonWidthSidebar);

    _sidebarLayout = new QVBoxLayout(_sidebarWidget);
    _sidebarLayout->setSpacing(spacingButtonSidebar);
    _sidebarLayout->setContentsMargins(spacingSide, spacingSide, spacingSide, spacingSide);

    _sidebarWidget->setLayout(_sidebarLayout);

    // Buttons
    _ButtonAddEntry = new QPushButton("Add Entry", _sidebarWidget);
    _ButtonAddEntry->setFixedSize(buttonWidthSidebar, buttonHeightSidebar);
    _sidebarLayout->addWidget(_ButtonAddEntry);

    _ButtonShowPasswords = new QPushButton("Show Password", _sidebarWidget);
    _ButtonShowPasswords->setFixedSize(buttonWidthSidebar, buttonHeightSidebar);
    _sidebarLayout->addWidget(_ButtonShowPasswords);

    _ButtonShowPasswordGen = new QPushButton("Password Gen", _sidebarWidget);
    _ButtonShowPasswordGen->setFixedSize(buttonWidthSidebar, buttonHeightSidebar);
    _sidebarLayout->addWidget(_ButtonShowPasswordGen);

    _ButtonDelPassword = new QPushButton("Delete Password", _sidebarWidget);
    _ButtonDelPassword->setFixedSize(buttonWidthSidebar, buttonHeightSidebar);
    _sidebarLayout->addWidget(_ButtonDelPassword);

    _ButtonEditPassword = new QPushButton("Edit Password", _sidebarWidget);
    _ButtonEditPassword->setFixedSize(buttonWidthSidebar, buttonHeightSidebar);
    _sidebarLayout->addWidget(_ButtonEditPassword);

    _ButtonChangeMasterPassword = new QPushButton("Change Master", _sidebarWidget);
    _ButtonChangeMasterPassword->setFixedSize(buttonWidthSidebar, buttonHeightSidebar);
    _sidebarLayout->addWidget(_ButtonChangeMasterPassword);

    _ButtonCloseMenu = new QPushButton("Close Menu", _sidebarWidget);
    _ButtonCloseMenu->setFixedSize(buttonWidthSidebar, buttonHeightSidebar);
    _sidebarLayout->addWidget(_ButtonCloseMenu);

    _sidebarWidget->setGeometry(spacingSide, logoHeight, logoWidth, global::screenHeight - logoHeight);
    _sidebarWidget->show();

    ////////////
    // Topbar //
    ////////////

    int topbarHeight = 40;

    _topBarWidget = new QWidget(this);
    _topBarLayout = new QHBoxLayout(_topBarWidget);

    _ButtonChangeSort = new QPushButton("Sort: A-Z", this);
    _ButtonChangeSort->setFixedHeight(topbarHeight);

    _inputSearch = new QLineEdit(this);
    _inputSearch->setFixedHeight(topbarHeight);

    _ButtonStartSearch = new QPushButton("Q", this);
    _ButtonStartSearch->setFixedHeight(topbarHeight);

    _topBarLayout->addWidget(_ButtonChangeSort);
    _topBarLayout->addWidget(_inputSearch);
    _topBarLayout->addWidget(_ButtonStartSearch);

    _topBarWidget->setGeometry(logoWidth, 0, global::screenWidth - logoWidth, logoHeight);
    _topBarWidget->show();

    ////////////
    // center //
    ////////////

}

void MainWindow::changeSort() {

}

void MainWindow::newEntry() {

}

void MainWindow::showPasswords() {

}

void MainWindow::showPasswordGen() {

}

void MainWindow::delPassword() {

}

void MainWindow::editPassword() {

}

void MainWindow::ChangeMasterPassword() {

}

void MainWindow::lockScreen() {

}
