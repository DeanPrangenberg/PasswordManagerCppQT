#include "MainWindow.h"
#include "../global/Global.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    global::geometry(this);

    decryptPasswords();

    setupSidebar();
    setupTopbar();
    setupCenterPasswordList();
}

void MainWindow::changeSort() {
    // Implement sorting logic here
}

void MainWindow::newEntry() {
    // Implement new entry logic here
}

void MainWindow::showPasswords() {
    // Implement show passwords logic here
}

void MainWindow::showPasswordGen() {
    // Implement password generation logic here
}

void MainWindow::delPassword() {
    // Implement delete password logic hier
}

void MainWindow::editPassword() {
    // Implement edit password logic hier
}

void MainWindow::ChangeMasterPassword() {
    // Implement change master password logic hier
}

void MainWindow::lockScreen() {
    global::openLockscreen(this);
}

QString MainWindow::genKey() {
    QString key;
    QVector<int> posNums;

    for (int i = 0; i < allChars.size(); ++i) {
        int random_num;
        bool num_in_list;
        do {
            random_num = QRandomGenerator::global()->bounded(allChars.size());
            num_in_list = false;
            for (int j = 0; j < i; j++) {
                if (posNums[j] == random_num) {
                    num_in_list = true;
                    break;
                }
            }
        } while (num_in_list);
        posNums.push_back(random_num);
        key += allChars[random_num];
    }

    qDebug() << "The Gen Key is: " << key;
    return key;
}

QString MainWindow::genPassword(int length, QString allowedChars) {
    QString password;
    for (int i = 0; i < length; ++i) {
        int randomInt = QRandomGenerator::global()->bounded(allowedChars.size());
        password += allowedChars[randomInt];
    }

    qDebug() << "The Gen Password is: " << password;
    return password;
}

void MainWindow::encryptPasswords() {
    QString filePath = "../res/passwords.txt";
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Fehler beim Öffnen der Datei zum Schreiben:" << file.errorString();
        return;
    }

    QTextStream out(&file);

    QString key = genKey();
    out << key + "\n";
    for (const QVector<QString>& vec : _passwordList) {
        for (const QString& str : vec) {
            out << encryptString(str, key) << "\n";
        }
    }

    file.close();

    qDebug() << "Strings wurden erfolgreich in" << filePath << "geschrieben.";
}

void MainWindow::decryptPasswords() {
    QString filePath = "../res/passwords.txt";
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Fehler beim Öffnen der Datei zum Lesen:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    _passwordList.clear();
    bool keyPos = true;
    QString key;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QVector<QString> tempVec;
        if (keyPos) {
            key = line;
            keyPos = false;
            continue;
        }
        tempVec.push_back(decryptString(line, key));
        _passwordList.push_back(tempVec);
    }

    file.close();
    qDebug() << "Strings wurden erfolgreich aus" << filePath << "gelesen.";
}

QString MainWindow::encryptString(const QString &input, const QString &key) {
    QString output;
    output.resize(input.size());

    for (int i = 0; i < input.size(); ++i) {
        QChar currentChar = input.at(i);
        int index = allChars.indexOf(currentChar);
        if (index != -1) {
            output[i] = key.at(index);
        } else {
            output[i] = currentChar;
        }
    }
    return output;
}

QString MainWindow::decryptString(const QString &input, const QString &key) {
    QString output;
    output.resize(input.size());

    for (int i = 0; i < input.size(); ++i) {
        QChar currentChar = input.at(i);
        int index = key.indexOf(currentChar);
        if (index != -1) {
            output[i] = allChars.at(index);
        } else {
            output[i] = currentChar;
        }
    }
    return output;
}

void MainWindow::setupSidebar() {
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

    // Sidebar area
    _sidebarWidget = new QWidget(this);
    _sidebarWidget->setFixedWidth(buttonWidthSidebar);

    _sidebarLayout = new QVBoxLayout(_sidebarWidget);
    _sidebarLayout->setSpacing(spacingButtonSidebar);
    _sidebarLayout->setContentsMargins(spacingSide, spacingSide, spacingSide, spacingSide);

    _ButtonAddEntry = new QPushButton("Add Entry", _sidebarWidget);
    _ButtonAddEntry->setFixedSize(buttonWidthSidebar, buttonHeightSidebar);
    _sidebarLayout->addWidget(_ButtonAddEntry);

    _ButtonShowPasswords = new QPushButton("Show Passwords", _sidebarWidget);
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

    _ButtonOpenLockscreen = new QPushButton("Close Menu", _sidebarWidget);
    _ButtonOpenLockscreen->setFixedSize(buttonWidthSidebar, buttonHeightSidebar);
    _sidebarLayout->addWidget(_ButtonOpenLockscreen);

    _sidebarWidget->setLayout(_sidebarLayout);
    _sidebarWidget->setGeometry(spacingSide, logoHeight, logoWidth, global::screenHeight - logoHeight);
    _sidebarWidget->show();

    connect(_ButtonOpenLockscreen, &QPushButton::clicked, this, &MainWindow::lockScreen);
}

void MainWindow::setupTopbar() {
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

    _topBarWidget->setGeometry(210, 0, global::screenWidth - 210, 100);
    _topBarWidget->show();
}

void MainWindow::setupCenterPasswordList() {
    _centerPasswordList = new QWidget(this);
    _scrollArea = new QScrollArea(this);
    _gridLayout = new QGridLayout();

    populateGrid();

    QWidget *scrollWidget = new QWidget();
    scrollWidget->setLayout(_gridLayout);
    _scrollArea->setWidget(scrollWidget);
    _scrollArea->setWidgetResizable(true);
    _scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    _scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    QVBoxLayout *layout = new QVBoxLayout(_centerPasswordList);
    layout->addWidget(_scrollArea);

    _centerPasswordList->setLayout(layout);
    _centerPasswordList->setGeometry(210, 100, global::screenWidth - 210, global::screenHeight - 100);
    _centerPasswordList->show();
}

void MainWindow::populateGrid() {
    QFont font("Arial", 12);
    int row = 0;

    QLabel *headerWebsite = new QLabel("Website");
    QLabel *headerUsername = new QLabel("Username/Email");
    QLabel *headerPassword = new QLabel("Password");

    headerWebsite->setFont(font);
    headerUsername->setFont(font);
    headerPassword->setFont(font);

    _gridLayout->addWidget(headerWebsite, row, 0);
    _gridLayout->addWidget(headerUsername, row, 1);
    _gridLayout->addWidget(headerPassword, row, 2);

    for (int i = 0; i < _passwordList.size(); ++i) {
        row++;
        for (int j = 0; j < _passwordList[i].size(); ++j) {
            QLabel *label = new QLabel(_passwordList[i][j]);
            label->setFont(font);
            _gridLayout->addWidget(label, row, j);
        }
    }
}
