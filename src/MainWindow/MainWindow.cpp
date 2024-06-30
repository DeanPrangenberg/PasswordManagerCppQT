#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->setGeometry(50, 50, _screenWidth, _screenHeight);
    /*
    fillPasswords();
    encryptPasswords();
    */

    // get passwords from file
    decryptPasswords();

    // setup all widgets
    setupLockscreen();
    setupSidebar();
    setupTopbar();
    setupCenterPasswordList();
}

///////////
// slots //
///////////

void MainWindow::ConfirmPassword() {
    QString passwordText = _inputField->text();
    if (!(passwordText.toStdString().empty())) {
        _passwordUserIn = passwordText;
        checkPassword();
    } else {
        _inputField->clear();
    }
}

void MainWindow::lockScreen() {
    hideAll();
    _lockscreenWidget->show();
    _inputField->clear();
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

///////////////
// off/on ui //
///////////////

void MainWindow::showStdMenu() {
    _sideBarWidget->show();
    _topBarWidget->show();
    _centerPasswordList->show();
    _LabelLogo->show();
    _lockscreenWidget->hide();
}

void MainWindow::hideAll() {
    _sideBarWidget->hide();
    _topBarWidget->hide();
    _centerPasswordList->hide();
    _LabelLogo->hide();
    _lockscreenWidget->hide();
}

///////////////////
// Data handling //
///////////////////

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

    qDebug() << "The Gen Key is:" << key;
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
    QString masterPassword = "gg";

    out << key << "\n";
    out << encryptString(masterPassword, key) << "\n";

    for (const QVector<QString>& tempVec : _passwordList) {
        for (const QString& str : tempVec) {
            QString encryptedStr = encryptString(str, key);
            out << encryptedStr << "\n";
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

    QString key = in.readLine().trimmed();
    _masterPassword = decryptString(in.readLine().trimmed(), key);

    QVector<QString> tempVec;
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty()) {
            QString decryptedStr = decryptString(line, key);
            tempVec.append(decryptedStr);
            if (tempVec.size() == 3) {
                _passwordList.append(tempVec);
                tempVec.clear();
            }
        }
    }

    if (!tempVec.isEmpty()) {
        qDebug() << "Warnung: Unvollständiger Datensatz gefunden.";
    }

    file.close();

    qDebug() << "Strings wurden erfolgreich aus" << filePath << "gelesen und entschluesselt.";
}

QString MainWindow::encryptString(const QString& input, const QString& key) {
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

QString MainWindow::decryptString(const QString& input, const QString& key) {
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
        if (_passwordList[i].size() == 3) {
            QLabel *websiteLabel = new QLabel(_passwordList[i][0]);
            QLabel *usernameLabel = new QLabel(_passwordList[i][1]);
            QLabel *passwordLabel = new QLabel(_passwordList[i][2]);

            websiteLabel->setFont(font);
            usernameLabel->setFont(font);
            passwordLabel->setFont(font);

            _gridLayout->addWidget(websiteLabel, row, 0);
            _gridLayout->addWidget(usernameLabel, row, 1);
            _gridLayout->addWidget(passwordLabel, row, 2);
        } else {
            qDebug() << "Warnung: Unvollständiger Datensatz in _passwordList an Index" << i;
        }
    }
}

void MainWindow::fillPasswords() {
    QVector<QVector<QString>> tempVec;

    for (int i = 0; i < 100; ++i) {
        QVector<QString> temp2Vec;
        for (int j = 0; j < 3; ++j) {
            switch (j) {
                case 0:
                    temp2Vec.push_back("example" + QString::number(i) + ".com");
                    break;
                case 1:
                    temp2Vec.push_back("user" + QString::number(i) + "@example.com");
                    break;
                case 2:
                    temp2Vec.push_back("password" + QString::number(i));
                    break;
                default:
                    qDebug() << "Unbekannter Fall im Switch: j = " << j;
                    break;
            }
        }
        tempVec.push_back(temp2Vec);
    }

    _passwordList = tempVec;
}

void MainWindow::checkPassword() {
    qDebug() << "== passwordUserIn is: " << _passwordUserIn << "| MasterPassword: " << _masterPassword;
    if (_passwordUserIn == _masterPassword) {
        qDebug() << "++ Password is correct!";
        showStdMenu();
    } else {
        _inputField->clear();
        qDebug() << "-- Password is wrong!";
        static int attemptsRemaining = 3;
        if (_passwordUserIn != _masterPassword) {
            attemptsRemaining--;
            if (attemptsRemaining == 0) {
                QMessageBox::critical(this, "Too many tries", "You have entered too many incorrect passwords. The application will be closed.");
                QCoreApplication::quit();
            } else {
                QMessageBox::warning(this, "Wrong Password", "The entered password is incorrect. " + QString::number(attemptsRemaining) + " attempt(s) remaining.");
            }
        }
    }
}

///////////
// setup //
///////////

void MainWindow::setupLockscreen() {
    int widgetWidth = 200;
    int widgetHeight = 120;

    int buttonHeight = 30;

    _lockscreenWidget = new QWidget(this);
    _lockscreenLayout = new QVBoxLayout(_lockscreenWidget);
    _lockscreenWidget->setLayout(_lockscreenLayout);

    _inputField = new QLineEdit(_lockscreenWidget);
    _inputField->setFixedHeight(buttonHeight);

    _buttonConfirm = new QPushButton("Confirm", _lockscreenWidget);
    _buttonConfirm->setFixedHeight(buttonHeight);

    _lockscreenLayout->addWidget(_inputField);
    _lockscreenLayout->addWidget(_buttonConfirm);

    _lockscreenWidget->setGeometry(_middleWidthScreen - widgetWidth / 2, _middleHeightScreen - widgetHeight / 2, widgetWidth, widgetHeight);
    _lockscreenWidget->show();

    connect(_buttonConfirm, SIGNAL(clicked()), this, SLOT(ConfirmPassword()));
}

void MainWindow::setupSidebar() {
    // Geometric
    int logoHeight = 100;
    int logoWidth = 210;
    int spacingButtonSidebar = 10;
    int spacingSide = 10;
    int buttonsInSideBar = 7;
    int buttonWidthSidebar = logoWidth - spacingSide;
    int buttonHeightSidebar = (_screenHeight - logoHeight - spacingButtonSidebar * (buttonsInSideBar + 1)) / buttonsInSideBar;

    // Logo
    _LabelLogo = new QLabel(this);
    QPixmap pixmap("../res/password-manager-logo-img.png");
    pixmap = pixmap.scaled(logoWidth, logoHeight, Qt::KeepAspectRatio);
    _LabelLogo->setPixmap(pixmap);
    _LabelLogo->setAlignment(Qt::AlignCenter);
    _LabelLogo->setFixedSize(logoWidth, logoHeight);

    // Sidebar area
    _sideBarWidget = new QWidget(this);
    _sideBarWidget->setFixedWidth(buttonWidthSidebar);

    _sideBarLayout = new QVBoxLayout(_sideBarWidget);
    _sideBarLayout->setSpacing(spacingButtonSidebar);
    _sideBarLayout->setContentsMargins(spacingSide, spacingSide, spacingSide, spacingSide);

    _ButtonAddEntry = new QPushButton("Add Entry", _sideBarWidget);
    _ButtonAddEntry->setFixedSize(buttonWidthSidebar, buttonHeightSidebar);
    _sideBarLayout->addWidget(_ButtonAddEntry);

    _ButtonShowPasswords = new QPushButton("Show Passwords", _sideBarWidget);
    _ButtonShowPasswords->setFixedSize(buttonWidthSidebar, buttonHeightSidebar);
    _sideBarLayout->addWidget(_ButtonShowPasswords);

    _ButtonShowPasswordGen = new QPushButton("Password Gen", _sideBarWidget);
    _ButtonShowPasswordGen->setFixedSize(buttonWidthSidebar, buttonHeightSidebar);
    _sideBarLayout->addWidget(_ButtonShowPasswordGen);

    _ButtonDelPassword = new QPushButton("Delete Password", _sideBarWidget);
    _ButtonDelPassword->setFixedSize(buttonWidthSidebar, buttonHeightSidebar);
    _sideBarLayout->addWidget(_ButtonDelPassword);

    _ButtonEditPassword = new QPushButton("Edit Password", _sideBarWidget);
    _ButtonEditPassword->setFixedSize(buttonWidthSidebar, buttonHeightSidebar);
    _sideBarLayout->addWidget(_ButtonEditPassword);

    _ButtonChangeMasterPassword = new QPushButton("Change Master", _sideBarWidget);
    _ButtonChangeMasterPassword->setFixedSize(buttonWidthSidebar, buttonHeightSidebar);
    _sideBarLayout->addWidget(_ButtonChangeMasterPassword);

    _ButtonOpenLockscreen = new QPushButton("Close Menu", _sideBarWidget);
    _ButtonOpenLockscreen->setFixedSize(buttonWidthSidebar, buttonHeightSidebar);
    _sideBarLayout->addWidget(_ButtonOpenLockscreen);

    _sideBarWidget->setLayout(_sideBarLayout);
    _sideBarWidget->setGeometry(spacingSide, logoHeight, logoWidth, _screenHeight - logoHeight);

    connect(_ButtonOpenLockscreen, SIGNAL(clicked()), this, SLOT(lockScreen()));

    _sideBarWidget->hide();
    _LabelLogo->hide();
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

    _topBarWidget->setGeometry(210, 0, _screenWidth - 210, 100);

    _topBarWidget->hide();
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
    _centerPasswordList->setGeometry(210, 100, _screenWidth - 210, _screenHeight - 100);

    _centerPasswordList->hide();
}

void setupPasswordGen() {

}

void setupPasswordEdit() {

}

void setupPasswordDel() {

}

void setupAddPassword() {

}

void setupEditMaster() {

}