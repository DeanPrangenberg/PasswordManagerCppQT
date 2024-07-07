//
// Created by prang on 07.07.2024.
//

#include "../MainWindow/MainWindow.h"

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

    for (const QVector<QString> &tempVec: _passwordList) {
        for (const QString &str: tempVec) {
            QString encryptedStr = encryptString(str, key);
            out << encryptedStr << "\n";
        }
    }

    file.close();

    qDebug() << "Strings wurden erfolgreich in" << filePath << "geschrieben.";
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

    qDebug() << "The Gen Key is:" << key;
    return key;
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