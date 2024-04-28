//
// Created by prang on 27.04.2024.
//

#include "MainWindow.h"
#include "../global/Global.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    global::geometry(this);

    /////////////
    // Sidebar //
    /////////////

    // geometric
    int logoHeight = 100;
    int logoWidth = 210;

    int spacingButtonSidebar = 10;
    int spacingSide = 10;

    int ButtonsInSideBar = 6;

    int buttonWidthSidebar = logoWidth - spacingSide;
    int buttonHeightSidebar = (global::screenHeight - logoHeight - spacingButtonSidebar * (ButtonsInSideBar + 1)) / ButtonsInSideBar;

    QVector<int> SidebarYPos = {
            logoHeight + spacingButtonSidebar,
            logoHeight + buttonHeightSidebar * 1 + spacingButtonSidebar * 2,
            logoHeight + buttonHeightSidebar * 2 + spacingButtonSidebar * 3,
            logoHeight + buttonHeightSidebar * 3 + spacingButtonSidebar * 4,
            logoHeight + buttonHeightSidebar * 4 + spacingButtonSidebar * 5,
            logoHeight + buttonHeightSidebar * 5 + spacingButtonSidebar * 6
    };

    // Logo
    QLabel* _LabelLogo = new QLabel(this);

    QPixmap pixmap("../res/password-manager-logo-img.png");
    pixmap = pixmap.scaled(logoWidth, logoHeight, Qt::KeepAspectRatio);
    _LabelLogo->setPixmap(pixmap);
    _LabelLogo->setAlignment(Qt::AlignCenter);
    _LabelLogo->setFixedSize(logoWidth, logoHeight);
    _LabelLogo->show();

    // Button
    _ButtonShowAll = new QPushButton("Show All", this);
    _ButtonShowPasswords = new QPushButton("Show Password", this);
    _ButtonShowAddress = new QPushButton("Show Address", this);
    _ButtonShowBank = new QPushButton("Show Bank", this);
    _ButtonShowPasswordGen = new QPushButton("Password Gen", this);
    _ButtonShowSetting = new QPushButton("Show Settings", this);

    _ButtonShowAll->setGeometry(spacingSide, SidebarYPos[0], buttonWidthSidebar, buttonHeightSidebar);
    _ButtonShowPasswords->setGeometry(spacingSide, SidebarYPos[1], buttonWidthSidebar, buttonHeightSidebar);
    _ButtonShowAddress->setGeometry(spacingSide, SidebarYPos[2], buttonWidthSidebar, buttonHeightSidebar);
    _ButtonShowBank->setGeometry(spacingSide, SidebarYPos[3], buttonWidthSidebar, buttonHeightSidebar);
    _ButtonShowPasswordGen->setGeometry(spacingSide, SidebarYPos[4], buttonWidthSidebar, buttonHeightSidebar);
    _ButtonShowSetting->setGeometry(spacingSide, SidebarYPos[5], buttonWidthSidebar, buttonHeightSidebar);

    ////////////
    // Topbar //
    ////////////

    //geometrics

    int topbarHieght = 30;

    int spacingToTop = (logoHeight - topbarHieght) / 2;

    int stuffInTop = 5;

    int EntryWidth = (global::screenWidth - logoWidth) / 5;
    int NameListingWidth = (global::screenWidth - logoWidth) / 5;
    int SearchbarWidth = (global::screenWidth - logoWidth) / 5;
    int SearchButtonWidth = (global::screenWidth - logoWidth) / 10;

    int spacingTopbar = (global::screenWidth - (logoWidth + EntryWidth + NameListingWidth + SearchbarWidth + SearchButtonWidth)) / stuffInTop;

    QVector<int> topbarXPos {
            logoWidth + spacingTopbar,
            logoWidth + spacingTopbar * 2 + EntryWidth,
            logoWidth + spacingTopbar * 3 + EntryWidth + NameListingWidth,
            logoWidth + spacingTopbar * 4 + EntryWidth + NameListingWidth + SearchbarWidth,
            logoWidth + spacingTopbar * 4  + EntryWidth + NameListingWidth + SearchbarWidth + SearchButtonWidth
    };

    // Button
    _ButtonAddEntry = new QPushButton("Add Entry", this);
    _ButtonStartSearch = new QPushButton("Q", this);

    _ButtonAddEntry->setGeometry(topbarXPos[0], spacingToTop, EntryWidth, topbarHieght);
    _ButtonStartSearch->setGeometry(topbarXPos[3], spacingToTop, SearchButtonWidth, topbarHieght);

    // Label
    _LabelNameListing = new QLabel(this);
    _LabelNameListing->setGeometry(topbarXPos[1], spacingToTop, NameListingWidth, topbarHieght);
    _LabelNameListing->setStyleSheet("background-color: gray");
    _LabelNameListing->setAlignment(Qt::AlignCenter);
    _LabelNameListing->setText("Showing " + openTab);

    // LineEdit
    _inputSearch = new QLineEdit(this);
    _inputSearch->setGeometry(topbarXPos[2], spacingToTop, SearchbarWidth, topbarHieght);

    ////////////
    // center //
    ////////////

}


