//
// Created by prang on 07.07.2024.
//

#include "../MainWindow/MainWindow.h"

QString MainWindow::genPassword(int length, QString allowedChars) {
    QString password;
    for (int i = 0; i < length; ++i) {
        int randomInt = QRandomGenerator::global()->bounded(allowedChars.size());
        password += allowedChars[randomInt];
    }

    qDebug() << "Generated Password: " << password;
    return password;
}

void MainWindow::checkIfFirstStart() {
    QString filePath = "../res/passwords.txt";
    QFile file(filePath);
    if (!QFile::exists(filePath)) {
        qDebug() << "Datei nicht gefunden:" << filePath;
        QMessageBox::information(this, "Initialisierung",
                                 "Die Passwortdatei wurde nicht gefunden. Bitte geben Sie ein Master-Passwort ein, um die Datei zu erstellen.");

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
            QMessageBox::information(this, "Erfolg",
                                     "Das Master-Passwort wurde gesetzt und die Passwortdatei wurde erstellt.");
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
    QLineEdit *headerRowNum = new QLineEdit("Row");
    QLineEdit *headerWebsite = new QLineEdit("Name/Website");
    QLineEdit *headerUsername = new QLineEdit("Username/Email");
    QLineEdit *headerPassword = new QLineEdit("Password");

    headerRowNum->setFixedWidth(40);

    // Aussehen und Verhalten der Header einstellen
    auto configureLineEditAsLabel = [](QLineEdit *lineEdit, QFont font) {
        lineEdit->setReadOnly(true);
        lineEdit->setFrame(false);
        lineEdit->setAlignment(Qt::AlignCenter);
        lineEdit->setFont(font);
        lineEdit->setFixedHeight(30);
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
        temp2Vec.push_back("example" + QString::number(i) + ".com");
        temp2Vec.push_back("user" + QString::number(i) + "@example.com");
        temp2Vec.push_back("password" + QString::number(i));
        tempVec.push_back(temp2Vec);
    }

    _passwordList = tempVec;
    tempVec.clear();
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
                QMessageBox::critical(this, "Too many tries",
                                      "You have entered too many incorrect passwords. The application will be closed.");
                QCoreApplication::quit();
            } else {
                QMessageBox::warning(this, "Wrong Password",
                                     "The entered password is incorrect. " + QString::number(attemptsRemaining) +
                                     " attempt(s) remaining.");
            }
        }
    }
}

void MainWindow::updateAllowedCharacters() {
    QVector<QString> allowedCharsVec;
    _allowedCharsPasswordGen.clear();

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
        allowedCharsVec.push_back(_showAllowedSymbols->text());
    }

    for (const QString &str: allowedCharsVec) {
        _allowedCharsPasswordGen += str;
    }
}