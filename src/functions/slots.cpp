//
// Created by prang on 07.07.2024.
//

#include "../MainWindow/MainWindow.h"

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

void MainWindow::deletePasswordEntry() {
    bool ok;
    int indexChangePassword = _inputRowDel->text().toInt(&ok) - 1;
    if (!ok || indexChangePassword >= _passwordList.size() || indexChangePassword < 0) {
        QMessageBox::warning(this, "Wrong Input",
                             "Please only enter a number between 1 and " + QString::number(_passwordList.size()));
    } else {
        _passwordList.removeAt(indexChangePassword);
        QMessageBox::information(this, "Deleted Password", "The Entry got deleted");
        _inputRowDel->clear();
        _showOldNameDel->clear();
        _showOldUsernameDel->clear();
        _showOldPasswordDel->clear();
        encryptPasswords();
        decryptPasswords();
        _showPasswordList = _passwordList;
        populateGrid();
    }
}

void MainWindow::showEditPassword() {
    hideAll();
    showBars();
    _centerNormPasswordEdit->show();
}

void MainWindow::showPasswordDel() {
    hideAll();
    showBars();
    _centerPasswordDel->show();
}

void MainWindow::showAddEntry() {
    hideAll();
    showBars();
    _centerAddPassword->show();
}

void MainWindow::checkChangeMasterPassword() {
    if (_inputOldMasterPassword->text() == _masterPassword) {
        _masterPassword = _inputNewMasterPassword->text();
        QMessageBox::information(this, "Master Password",
                                 "Das Master Password wurde auf " + _masterPassword + " geändert!");
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
    updateAllowedCharacters();
}

void MainWindow::onAllowUpAlphabetToggled(bool checked) {
    _allowUpAlphabetChecked = checked;
    updateAllowedCharacters();
}

void MainWindow::onAllowNumbersToggled(bool checked) {
    _allowNumbersChecked = checked;
    updateAllowedCharacters();
}

void MainWindow::onAllowSymbolsToggled(bool checked) {
    _allowSymbolsChecked = checked;
    updateAllowedCharacters();
}

void MainWindow::startPasswordGen() {
    updateAllowedCharacters();
    bool ok = false;
    int passwordLength = _passwordLengthInput->text().toInt(&ok);
    if (!ok) {
        qDebug() << "Invalid password length input!";
        return;
    }
    QString password = genPassword(passwordLength, _allowedCharsPasswordGen);
    _passwordOutput->setText(password);
}

void MainWindow::searchRowEdit() {
    bool ok;
    int indexChangePassword = _inputRowEdit->text().toInt(&ok) - 1;
    if (!ok || indexChangePassword >= _passwordList.size() || indexChangePassword < 0) {
        QMessageBox::warning(this, "Wrong Input",
                             "Please only enter a number between 1 and " + QString::number(_passwordList.size()));
    } else {
        _showOldName->setText(_showPasswordList[indexChangePassword][0]);
        _showOldUsername->setText(_showPasswordList[indexChangePassword][1]);
        _showOldPassword->setText(_showPasswordList[indexChangePassword][2]);

        _inputNewName->setText(_showPasswordList[indexChangePassword][0]);
        _inputNewUsername->setText(_showPasswordList[indexChangePassword][1]);
        _inputNewPassword->setText(_showPasswordList[indexChangePassword][2]);
    }
}

void MainWindow::searchRowDel() {
    bool ok;
    int indexChangePassword = _inputRowDel->text().toInt(&ok) - 1;
    if (!ok || indexChangePassword >= _passwordList.size() || indexChangePassword < 0) {
        QMessageBox::warning(this, "Wrong Input",
                             "Please only enter a number between 1 and " + QString::number(_passwordList.size()));
    } else {
        QVector<QString> entry = _passwordList.at(indexChangePassword);
        _showOldNameDel->setText(entry[0]);
        _showOldUsernameDel->setText(entry[1]);
        _showOldPasswordDel->setText(entry[2]);
    }
}

void MainWindow::transferValues() {
    _showNewName->setText(_inputNewName->text());
    _showNewUsername->setText(_inputNewUsername->text());
    _showNewPassword->setText(_inputNewPassword->text());
}

void MainWindow::changePasswordEntry() {
    if (_showNewName->text().isEmpty() || _showNewUsername->text().isEmpty() || _showNewPassword->text().isEmpty()) {
        QMessageBox::warning(this, "Wrong Inputs",
                             "Please press the transfare Button and check your changes before saving!");
    } else {
        bool ok;
        int indexChangePassword = _inputRowEdit->text().toInt(&ok) - 1;
        if (!ok || indexChangePassword >= _passwordList.size() || indexChangePassword < 0) {
            QMessageBox::warning(this, "Wrong Input",
                                 "Please only enter a number between 1 and " + QString::number(_passwordList.size()));
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
            _inputRowEdit->clear();
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

void MainWindow::addPasswordEntry() {
    QString newName = _inputAddName->text();
    QString newUsername = _inputAddUsername->text();
    QString newPassword = _inputAddPassword->text();

    if (newName.isEmpty() || newUsername.isEmpty() || newPassword.isEmpty()) {
        QMessageBox::warning(this, "Empty Fields", "Please fill in all fields before saving.");
        return;
    }

    // Add new entry to the password list
    QStringList newEntry = {newName, newUsername, newPassword};
    _passwordList.append(newEntry);

    encryptPasswords();
    decryptPasswords();
    _showPasswordList = _passwordList;
    populateGrid();

    QMessageBox::information(this, "Entry Added", "Your new entry has been added successfully!");

    // Clear the input fields and labels
    _inputAddName->clear();
    _inputAddUsername->clear();
    _inputAddPassword->clear();
    _showAddName->clear();
    _showAddUsername->clear();
    _showAddPassword->clear();
}

void MainWindow::searchInList() {
    hideAll();
    showStdMenu();
    QString searchInput = _inputSearch->text();

    if (searchInput.isEmpty()) {
        _showPasswordList = _passwordList;
        populateGrid();
        return;
    }

    _showPasswordList.clear();

    for (const QVector<QString> &strVec: _passwordList) {
        if (!strVec.isEmpty() && strVec[0].size() >= searchInput.size()) {
            bool match = true;
            for (int i = 0; i < searchInput.size(); ++i) {
                if (strVec[0][i] != searchInput[i]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                _showPasswordList.push_back(strVec);
            }
        }
    }

    populateGrid();
}

void MainWindow::reloadList() {
    decryptPasswords();
    _showPasswordList = _passwordList;
    populateGrid();
}