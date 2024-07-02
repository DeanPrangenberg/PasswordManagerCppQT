#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->setGeometry(50, 50, _screenWidth, _screenHeight);
    this->setFixedSize(_screenWidth, _screenHeight);
    /*
    fillPasswords();
    encryptPasswords();
    */



    // get passwords from file
    checkIfFirstStart();
    decryptPasswords();
    _showPasswordList = _passwordList;

    // setup all widgets
    setupLockscreen();
    setupSidebar();
    setupTopbar();
    setupCenterPasswordList();
    setupPasswordGen();
    setupEditMaster();
    setupAddPassword();
    setupPasswordDel();
    setupPasswordEdit();
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
    encryptPasswords();
}

void MainWindow::changeSort() {
    // Implement sorting logic here
}

void MainWindow::newEntry() {
    // Implement new entry logic here
}

void MainWindow::showPasswords() {
    hideAll();
    showStdMenu();
    _passwordOutput->clear();
    _passwordLengthInput->setText("16");
}

void MainWindow::showPasswordGen() {
    hideAll();
    showBars();
    _centerPasswordGen->show();
}

void MainWindow::showMasterPasswordEdit() {
    hideAll();
    showBars();
    _centerMasterPasswordEdit->show();
}

void MainWindow::delPassword() {
    // Implement delete password logic hier
}

void MainWindow::showEditPassword() {
    hideAll();
    showBars();
    _centerNormPasswordEdit->show();
}

void MainWindow::checkChangeMasterPassword() {
    if (_inputOldMasterPassword->text() == _masterPassword) {
        _masterPassword = _inputNewMasterPassword->text();
        QMessageBox::information(this, "Master Password", "Das Master Password wurde auf " + _masterPassword + " geändert!");
        qDebug() << "== Das neue Masterpassword ist: " << _masterPassword;
    } else {
        qDebug() << "Old Master password input: " << _oldMasterPasswordLabel;
        qDebug() << "Real Master password: " << _masterPassword;
        QMessageBox::warning(this, "Fehler", "Das aktuelle Master-Passwort ist nicht korrekt.");
        _inputOldMasterPassword->clear();
    }
    encryptPasswords();
}

void MainWindow::onAllowLowAlphabetToggled(bool checked) {
    _allowLowAlphabetChecked = checked;
}

void MainWindow::onAllowUpAlphabetToggled(bool checked) {
    _allowUpAlphabetChecked = checked;
}

void MainWindow::onAllowNumbersToggled(bool checked) {
    _allowNumbersChecked = checked;
}

void MainWindow::onAllowSymbolsToggled(bool checked) {
    _allowSymbolsChecked = checked;
}

void MainWindow::startPasswordGen() {
    updateAllowedCharacters();
    bool ok = false;
    int passwordLength = _passwordLengthInput->text().toInt(&ok);
    if (!ok) {
        qDebug() << "Invalid password length input!";
        return;
    }
    QString Password = genPassword(passwordLength, _allowedCharsPasswordGen);
    _passwordOutput->setText(Password);
}

void MainWindow::searchRow() {
    bool ok;
    int indexChangePassword = _inputRow->text().toInt(&ok) - 1;
    if (!ok || indexChangePassword >= _passwordList.size() || indexChangePassword < 0) {
        QMessageBox::warning(this, "Wrong Input", "Please only enter a number between 1 and " + QString::number(_passwordList.size()));
    } else {
        _showOldName->setText(_showPasswordList[indexChangePassword][0]);
        _showOldUsername->setText(_showPasswordList[indexChangePassword][1]);
        _showOldPassword->setText(_showPasswordList[indexChangePassword][2]);

        _inputNewName->setText(_showPasswordList[indexChangePassword][0]);
        _inputNewUsername->setText(_showPasswordList[indexChangePassword][1]);
        _inputNewPassword->setText(_showPasswordList[indexChangePassword][2]);
    }
}


void MainWindow::transferValues() {
    _showNewName->setText(_inputNewName->text());
    _showNewUsername->setText(_inputNewUsername->text());
    _showNewPassword->setText(_inputNewPassword->text());
}

void MainWindow::changePasswordEntry() {
    if (_showNewName->text().isEmpty() || _showNewUsername->text().isEmpty() ||_showNewPassword->text().isEmpty()) {
        QMessageBox::warning(this, "Wrong Inputs", "Please press the transfare Button and check your changes before saving!");
    } else {
        bool ok;
        int indexChangePassword = _inputRow->text().toInt(&ok) - 1;
        if (!ok || indexChangePassword >= _passwordList.size() || indexChangePassword < 0) {
            QMessageBox::warning(this, "Wrong Input", "Please only enter a number between 1 and " + QString::number(_passwordList.size()));
        } else {
            QString newName = _showNewName->text();
            QString newUsername = _showNewUsername->text();
            QString newPassword = _showNewPassword->text();

            _passwordList[indexChangePassword][0] = newName;
            _passwordList[indexChangePassword][1] = newUsername;
            _passwordList[indexChangePassword][2] = newPassword;

            encryptPasswords();
            decryptPasswords();
            _showPasswordList = _passwordList;
            populateGrid();
            QMessageBox::information(this, "Password change", "Your changes has been done!");
            _inputRow->clear();
            _inputNewName->clear();
            _inputNewUsername->clear();
            _inputNewPassword->clear();
            _showOldName->clear();
            _showOldUsername->clear();
            _showOldPassword->clear();
            _showNewName->clear();
            _showNewUsername->clear();
            _showNewPassword->clear();
        }
    }

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
    _centerNormPasswordEdit->hide();
}

void MainWindow::showBars() {
    _sideBarWidget->show();
    _topBarWidget->show();
    _LabelLogo->show();
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

    out << key << "\n";
    out << encryptString(_masterPassword, key) << "\n";

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
        QMessageBox::warning(this, "Fehler", "Die Passwortdatei konnte nicht geöffnet werden.");
        return;
    }

    QTextStream in(&file);
    _passwordList.clear();

    QString key = in.readLine().trimmed();
    if (key.isEmpty()) {
        qDebug() << "Fehler: Der Entschlüsselungsschlüssel ist leer.";
        QMessageBox::warning(this, "Fehler", "Die Passwortdatei ist ungültig oder beschädigt.");
        file.close();
        return;
    }

    _masterPassword = decryptString(in.readLine().trimmed(), key);
    if (_masterPassword.isEmpty()) {
        qDebug() << "Fehler: Das Master-Passwort konnte nicht entschlüsselt werden.";
        QMessageBox::warning(this, "Fehler", "Das Master-Passwort konnte nicht entschlüsselt werden.");
        file.close();
        return;
    }

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
    qDebug() << "Strings wurden erfolgreich aus" << filePath << "gelesen und entschlüsselt.";
}

void MainWindow::checkIfFirstStart() {
    QString filePath = "../res/passwords.txt";
    QFile file(filePath);
    if (!QFile::exists(filePath)) {
        qDebug() << "Datei nicht gefunden:" << filePath;
        QMessageBox::information(this, "Initialisierung", "Die Passwortdatei wurde nicht gefunden. Bitte geben Sie ein Master-Passwort ein, um die Datei zu erstellen.");

        bool ok;
        QString masterPassword = QInputDialog::getText(this, tr("Initialisiere Master-Passwort"),
                                                       tr("Master-Passwort:"), QLineEdit::Password,
                                                       "", &ok);

        if (ok && !masterPassword.isEmpty()) {
            // Save the master password and create an empty password file
            _masterPassword = masterPassword;
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                qDebug() << "Fehler beim Öffnen der Datei zum Schreiben:" << file.errorString();
                QMessageBox::warning(this, "Fehler", "Die Passwortdatei konnte nicht erstellt werden.");
                return;
            }
            QTextStream out(&file);
            QString key = genKey();
            out << key << "\n";
            out << encryptString(_masterPassword, key) << "\n";
            file.close();
            qDebug() << "Neue Passwortdatei wurde erstellt.";
            QMessageBox::information(this, "Erfolg", "Das Master-Passwort wurde gesetzt und die Passwortdatei wurde erstellt.");
            fillPasswords();
            decryptPasswords();
            return;
        } else {
            qDebug() << "Initialisierung des Master-Passworts abgebrochen.";
            QMessageBox::warning(this, "Fehler", "Initialisierung des Master-Passworts abgebrochen.");
            return;
        }
        return;
    }
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

    // Vorhandene Widgets im _gridLayout löschen
    QLayoutItem *child;
    while ((child = _gridLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    // Header erstellen
    QLineEdit *headerWebsite = new QLineEdit("Website");
    QLineEdit *headerUsername = new QLineEdit("Username/Email");
    QLineEdit *headerPassword = new QLineEdit("Password");
    QLineEdit *headerRowNum = new QLineEdit("Row");

    headerRowNum->setFixedWidth(40);

    // Aussehen und Verhalten der Header einstellen
    auto configureLineEditAsLabel = [](QLineEdit* lineEdit, QFont font) {
        lineEdit->setReadOnly(true);
        lineEdit->setFrame(false);
        lineEdit->setAlignment(Qt::AlignCenter);
        lineEdit->setFont(font);
        lineEdit->setFixedHeight(30);
        lineEdit->setStyleSheet("QLineEdit { background: transparent; border: none; }");
    };

    configureLineEditAsLabel(headerRowNum, font);
    configureLineEditAsLabel(headerWebsite, font);
    configureLineEditAsLabel(headerUsername, font);
    configureLineEditAsLabel(headerPassword, font);

    _gridLayout->addWidget(headerRowNum, row, 0);
    _gridLayout->addWidget(headerWebsite, row, 1);
    _gridLayout->addWidget(headerUsername, row, 2);
    _gridLayout->addWidget(headerPassword, row, 3);

    // Datenzeilen hinzufügen
    for (int i = 0; i < _showPasswordList.size(); ++i) {
        ++row;
        if (_showPasswordList[i].size() == 3) {
            QLineEdit *RowNum = new QLineEdit(QString::number(row));
            QLineEdit *websiteLabel = new QLineEdit(_showPasswordList[i][0]);
            QLineEdit *usernameLabel = new QLineEdit(_showPasswordList[i][1]);
            QLineEdit *passwordLabel = new QLineEdit(_showPasswordList[i][2]);

            RowNum->setFixedSize(40, 15);

            configureLineEditAsLabel(RowNum, font);
            configureLineEditAsLabel(websiteLabel, font);
            configureLineEditAsLabel(usernameLabel, font);
            configureLineEditAsLabel(passwordLabel, font);

            _gridLayout->addWidget(RowNum, row, 0);
            _gridLayout->addWidget(websiteLabel, row, 1);
            _gridLayout->addWidget(usernameLabel, row, 2);
            _gridLayout->addWidget(passwordLabel, row, 3);
        } else {
            qDebug() << "Warnung: Unvollständiger Datensatz in _showPasswordList an Index" << i;
        }
    }

    // Update des Layouts
    _gridLayout->update();
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
    encryptPasswords();
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

void MainWindow::updateAllowedCharacters() {
    QVector<QString> allowedCharsVec;

    if (_allowLowAlphabetChecked) {
        allowedCharsVec.push_back("abcdefghijklmnopqrstuvwxyz");
    }

    if (_allowUpAlphabetChecked) {
        allowedCharsVec.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    }

    if (_allowNumbersChecked) {
        allowedCharsVec.push_back("0123456789");
    }

    if (_allowSymbolsChecked) {
        allowedCharsVec.push_back("!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~");
    }

    for (QString str : allowedCharsVec) {
        _allowedCharsPasswordGen += str;
    }
}

///////////
// setup //
///////////

void MainWindow::setupPasswordEdit() {
    int textLabelWidth = 100;

    _centerNormPasswordEdit = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(_centerNormPasswordEdit);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    // Top section for input and search
    QGroupBox *inputGroup = new QGroupBox("Edit Password Entry", this);
    inputGroup->setStyleSheet("QGroupBox { font-weight: bold; font-size: 18px; }");
    QVBoxLayout *inputLayout = new QVBoxLayout(inputGroup);

    // Row number input and search button
    QHBoxLayout *rowLayout = new QHBoxLayout();
    QLabel *rowLabel = new QLabel("Row Number:", this);
    _inputRow = new QLineEdit(this);
    QPushButton *searchRowButton = new QPushButton("Search", this);

    rowLayout->addWidget(rowLabel);
    rowLayout->addWidget(_inputRow);
    rowLayout->addWidget(searchRowButton);

    // New name, username, and password inputs
    QHBoxLayout *nameInputLayout = new QHBoxLayout();
    QLabel *newNameLabel = new QLabel("Name:", this);
    _inputNewName = new QLineEdit(this);

    nameInputLayout->addWidget(newNameLabel);
    nameInputLayout->addWidget(_inputNewName);

    QHBoxLayout *usernameInputLayout = new QHBoxLayout();
    QLabel *newUsernameLabel = new QLabel("Username:", this);
    _inputNewUsername = new QLineEdit(this);

    usernameInputLayout->addWidget(newUsernameLabel);
    usernameInputLayout->addWidget(_inputNewUsername);

    QHBoxLayout *passwordInputLayout = new QHBoxLayout();
    QLabel *newPasswordLabel = new QLabel("Password:", this);
    _inputNewPassword = new QLineEdit(this);

    passwordInputLayout->addWidget(newPasswordLabel);
    passwordInputLayout->addWidget(_inputNewPassword);

    // Add layouts to input group
    inputLayout->addLayout(rowLayout);
    inputLayout->addLayout(nameInputLayout);
    inputLayout->addLayout(usernameInputLayout);
    inputLayout->addLayout(passwordInputLayout);

    // New button to transfer values to the display section
    QPushButton *transferValuesButton = new QPushButton("Transfer Values", this);
    inputLayout->addWidget(transferValuesButton);

    // Set fixed widths and styles for top section
    rowLabel->setFixedWidth(textLabelWidth);
    newNameLabel->setFixedWidth(textLabelWidth);
    newUsernameLabel->setFixedWidth(textLabelWidth);
    newPasswordLabel->setFixedWidth(textLabelWidth);

    rowLabel->setStyleSheet("font-size: 16px;");
    newNameLabel->setStyleSheet("font-size: 16px;");
    newUsernameLabel->setStyleSheet("font-size: 16px;");
    newPasswordLabel->setStyleSheet("font-size: 16px;");
    searchRowButton->setStyleSheet("font-size: 16px;");
    transferValuesButton->setStyleSheet("font-size: 16px;");

    _inputRow->setFixedHeight(40);
    _inputNewName->setFixedHeight(40);
    _inputNewUsername->setFixedHeight(40);
    _inputNewPassword->setFixedHeight(40);
    searchRowButton->setFixedHeight(40);
    transferValuesButton->setFixedHeight(40);

    // Bottom section for displaying old and new values and save button
    QGroupBox *displayGroup = new QGroupBox("Old and New Values", this);
    displayGroup->setStyleSheet("QGroupBox { font-weight: bold; font-size: 18px; }");
    QVBoxLayout *displayLayout = new QVBoxLayout(displayGroup);

    QHBoxLayout *oldNameLayout = new QHBoxLayout();
    QLabel *oldNameLabel = new QLabel("Old Name:", this);
    _showOldName = new QLabel(this);
    QLabel *newNameDisplayLabel = new QLabel("New Name:", this);
    _showNewName = new QLabel(this);

    oldNameLayout->addWidget(oldNameLabel);
    oldNameLayout->addWidget(_showOldName);
    oldNameLayout->addWidget(newNameDisplayLabel);
    oldNameLayout->addWidget(_showNewName);

    QHBoxLayout *oldUsernameLayout = new QHBoxLayout();
    QLabel *oldUsernameLabel = new QLabel("Old Username:", this);
    _showOldUsername = new QLabel(this);
    QLabel *newUsernameDisplayLabel = new QLabel("New Username:", this);
    _showNewUsername = new QLabel(this);

    oldUsernameLayout->addWidget(oldUsernameLabel);
    oldUsernameLayout->addWidget(_showOldUsername);
    oldUsernameLayout->addWidget(newUsernameDisplayLabel);
    oldUsernameLayout->addWidget(_showNewUsername);

    QHBoxLayout *oldPasswordLayout = new QHBoxLayout();
    QLabel *oldPasswordLabel = new QLabel("Old Password:", this);
    _showOldPassword = new QLabel(this);
    QLabel *newPasswordDisplayLabel = new QLabel("New Password:", this);
    _showNewPassword = new QLabel(this);

    oldPasswordLayout->addWidget(oldPasswordLabel);
    oldPasswordLayout->addWidget(_showOldPassword);
    oldPasswordLayout->addWidget(newPasswordDisplayLabel);
    oldPasswordLayout->addWidget(_showNewPassword);

    // Save changes button
    _saveChangesNormPasswordEdit = new QPushButton("Save Changes", this);
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(_saveChangesNormPasswordEdit);

    // Add layouts to display group
    displayLayout->addLayout(oldNameLayout);
    displayLayout->addLayout(oldUsernameLayout);
    displayLayout->addLayout(oldPasswordLayout);
    displayLayout->addLayout(buttonLayout);

    // Set fixed styles for bottom section
    _showOldName->setStyleSheet("font-size: 16px;");
    _showOldUsername->setStyleSheet("font-size: 16px;");
    _showOldPassword->setStyleSheet("font-size: 16px;");
    _showNewName->setStyleSheet("font-size: 16px;");
    _showNewUsername->setStyleSheet("font-size: 16px;");
    _showNewPassword->setStyleSheet("font-size: 16px;");
    _saveChangesNormPasswordEdit->setStyleSheet("font-size: 16px;");
    _saveChangesNormPasswordEdit->setFixedHeight(40);

    // Add groups to main layout
    mainLayout->addWidget(inputGroup);
    mainLayout->addWidget(displayGroup);

    _centerNormPasswordEdit->setLayout(mainLayout);
    _centerNormPasswordEdit->setGeometry(210, 100, _screenWidth - 210, _screenHeight - 100);
    _centerNormPasswordEdit->hide();

    // Connect signals and slots
    connect(searchRowButton, SIGNAL(clicked()), this, SLOT(searchRow()));
    connect(_saveChangesNormPasswordEdit, SIGNAL(clicked()), this, SLOT(changePasswordEntry()));
    connect(transferValuesButton, SIGNAL(clicked()), this, SLOT(transferValues()));
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

    connect(_ButtonShowPasswordGen, SIGNAL(clicked()), this, SLOT(showPasswordGen()));
    connect(_ButtonOpenLockscreen, SIGNAL(clicked()), this, SLOT(lockScreen()));
    connect(_ButtonShowPasswords, SIGNAL(clicked()), this, SLOT(showPasswords()));
    connect(_ButtonChangeMasterPassword, SIGNAL(clicked()), this, SLOT(showMasterPasswordEdit()));
    connect(_ButtonEditPassword, SIGNAL(clicked()), this, SLOT(showEditPassword()));

    _sideBarWidget->hide();
    _LabelLogo->hide();
}

void MainWindow::setupCenterPasswordList() {
    _centerPasswordList = new QWidget(this);
    _scrollArea = new QScrollArea(this);
    _gridLayout = new QGridLayout();

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

void MainWindow::setupPasswordGen() {
    _allowLowAlphabet = new QCheckBox("Include Lowercase Alphabet (a-z)");
    _allowUpAlphabet = new QCheckBox("Include Uppercase Alphabet (A-Z)");
    _allowNumbers = new QCheckBox("Include Numbers (0-9)");
    _allowSymbols = new QCheckBox("Include Symbols");

    connect(_allowLowAlphabet, &QCheckBox::toggled, this, &MainWindow::onAllowLowAlphabetToggled);
    connect(_allowUpAlphabet, &QCheckBox::toggled, this, &MainWindow::onAllowUpAlphabetToggled);
    connect(_allowNumbers, &QCheckBox::toggled, this, &MainWindow::onAllowNumbersToggled);
    connect(_allowSymbols, &QCheckBox::toggled, this, &MainWindow::onAllowSymbolsToggled);

    _allowLowAlphabetChecked = true;
    _allowUpAlphabetChecked = true;
    _allowNumbersChecked = true;
    _allowSymbolsChecked = true;

    _centerPasswordGen = new QWidget(this);
    QVBoxLayout *genLayout = new QVBoxLayout(_centerPasswordGen);
    genLayout->setSpacing(10);
    genLayout->setContentsMargins(20, 20, 20, 20);

    QGroupBox *optionsGroup = new QGroupBox("Password Generation Options", this);
    QVBoxLayout *optionsLayout = new QVBoxLayout(optionsGroup);

    _showLowAlphabet = new QLabel("Include Lowercase Alphabet (a-z):", this);
    _allowLowAlphabet = new QCheckBox(this);
    _allowLowAlphabet->setChecked(true);
    optionsLayout->addWidget(_showLowAlphabet);
    optionsLayout->addWidget(_allowLowAlphabet);

    _showUpAlphabet = new QLabel("Include Uppercase Alphabet (A-Z):", this);
    _allowUpAlphabet = new QCheckBox(this);
    _allowUpAlphabet->setChecked(true);
    optionsLayout->addWidget(_showUpAlphabet);
    optionsLayout->addWidget(_allowUpAlphabet);

    _showNumbers = new QLabel("Include Numbers (0-9):", this);
    _allowNumbers = new QCheckBox(this);
    _allowNumbers->setChecked(true);
    optionsLayout->addWidget(_showNumbers);
    optionsLayout->addWidget(_allowNumbers);

    QLabel *showSymbols = new QLabel("Include Symbols:", this);
    _allowSymbols = new QCheckBox(this);
    _allowSymbols->setChecked(true);
    optionsLayout->addWidget(showSymbols);
    optionsLayout->addWidget(_allowSymbols);

    QLabel *allowedSymbolsLabel = new QLabel("Allowed Symbols:", this);
    _showAllowedSymbols = new QLineEdit(this);
    _showAllowedSymbols->setPlaceholderText("Enter your symbols");
    _showAllowedSymbols->setText("!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~");
    optionsLayout->addWidget(allowedSymbolsLabel);
    optionsLayout->addWidget(_showAllowedSymbols);

    QLabel *passwordLengthLabel = new QLabel("Password Length:", this);
    _passwordLengthInput = new QLineEdit(this);
    _passwordLengthInput->setPlaceholderText("Enter password length (1-20)");
    _passwordLengthInput->setText("16");
    _passwordLengthInput->setValidator(new QIntValidator(1, 20, this));
    optionsLayout->addWidget(passwordLengthLabel);
    optionsLayout->addWidget(_passwordLengthInput);

    optionsGroup->setLayout(optionsLayout);
    genLayout->addWidget(optionsGroup);

    QGroupBox *outputGroup = new QGroupBox("Generated Password", this);
    QVBoxLayout *outputLayout = new QVBoxLayout(outputGroup);

    _passwordOutput = new QLineEdit(this);
    _passwordOutput->setReadOnly(true);
    _passwordOutput->setStyleSheet("background-color: #252526; color: #ffffff;");
    _passwordOutput->setAlignment(Qt::AlignCenter);
    _passwordOutput->setFixedHeight(30);
    outputLayout->addWidget(_passwordOutput);

    _startPasswordGen = new QPushButton("Generate Password", this);
    _startPasswordGen->setFixedHeight(40);
    outputLayout->addWidget(_startPasswordGen);

    outputGroup->setLayout(outputLayout);
    genLayout->addWidget(outputGroup);

    _centerPasswordGen->setLayout(genLayout);
    _centerPasswordGen->setGeometry(210, 100, _screenWidth - 210, _screenHeight - 100);
    _centerPasswordGen->hide();

    bool ok = false;
    int passwordLenght = _passwordLengthInput->text().toInt(&ok);
    connect(_startPasswordGen, &QPushButton::clicked, this, &MainWindow::startPasswordGen);
}

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

void MainWindow::setupEditMaster() {
    _centerMasterPasswordEdit = new QWidget(this);
    QVBoxLayout *editLayout = new QVBoxLayout(_centerMasterPasswordEdit);
    editLayout->setSpacing(10);
    editLayout->setContentsMargins(20, 20, 20, 20);

    QGroupBox *editGroup = new QGroupBox("Edit Master Password", this);
    QVBoxLayout *groupLayout = new QVBoxLayout(editGroup);

    _oldMasterPasswordLabel = new QLabel("Old Master Password:", this);
    _inputOldMasterPassword = new QLineEdit(this);

    _newMasterPasswordLabel = new QLabel("New Master Password:", this);
    _inputNewMasterPassword = new QLineEdit(this);

    groupLayout->addWidget(_oldMasterPasswordLabel);
    groupLayout->addWidget(_inputOldMasterPassword);
    groupLayout->addWidget(_newMasterPasswordLabel);
    groupLayout->addWidget(_inputNewMasterPassword);

    _changeMasterPassword = new QPushButton("Change Master Password", this);
    groupLayout->addWidget(_changeMasterPassword);

    editGroup->setLayout(groupLayout);
    editLayout->addWidget(editGroup);

    _centerMasterPasswordEdit->setLayout(editLayout);
    _centerMasterPasswordEdit->setGeometry(210, 100, _screenWidth - 210, _screenHeight - 100);
    _centerMasterPasswordEdit->hide();

    connect(_changeMasterPassword, SIGNAL(clicked()), this, SLOT(checkChangeMasterPassword()));
}

void MainWindow::setupPasswordDel() {

}

void MainWindow::setupAddPassword() {

}
