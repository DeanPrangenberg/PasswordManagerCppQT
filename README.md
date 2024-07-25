# QtC++ Password Manager
## Projektübersicht
**QtC++ Password Manager** ist ein eigenständiger Passwort-Manager, entwickelt mit C++ und dem Qt Framework. Dieses Projekt zeigt meine Fähigkeiten in der Softwareentwicklung und -gestaltung, insbesondere in der Anwendung von C++ und Qt.

## Hauptfunktionen
- Benutzeroberfläche: Vollständig in Qt erstellt, bietet die Anwendung eine intuitive 
- Benutzeroberfläche zum Verwalten von Passwörtern.
- Passwort-Generierung: Ermöglicht die Generierung starker Passwörter mit benutzerdefinierten Einstellungen für Zeichenarten und Länge.
- Datenverschlüsselung: Passwörter werden mit einer benutzerdefinierten Verschlüsselungstechnologie gesichert.
- Passwort-Management: Einfache Funktionen zum Hinzufügen, Bearbeiten und Löschen von Passworteinträgen.
## Technische Details
- Sprache: C++
- Framework: Qt 5/6
- Tools: CMake für das Build-System
## Beispielcode
**Datenhandling (dataHandeling.cpp)**
```
#include <QFile>
#include <QTextStream>
#include <QDebug>

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
```
**Benutzeroberfläche (setupUI.cpp)**
```
#include "MainWindow.h"

void MainWindow::setupMainWindow() {
    // UI Komponenten initialisieren
    _topBarLayout = new QHBoxLayout();
    _sideBarLayout = new QVBoxLayout();
    _centerLayout = new QVBoxLayout();

    _ButtonShowPasswords = new QPushButton("Passwörter anzeigen");
    _ButtonShowPasswordGen = new QPushButton("Passwort generieren");
    _ButtonAddEntry = new QPushButton("Eintrag hinzufügen");

    _topBarLayout->addWidget(_ButtonShowPasswords);
    _topBarLayout->addWidget(_ButtonShowPasswordGen);
    _topBarLayout->addWidget(_ButtonAddEntry);

    _sideBarLayout->addLayout(_topBarLayout);
    
    // Setze Layouts für das Hauptfenster
    QWidget *centralWidget = new QWidget();
    centralWidget->setLayout(_sideBarLayout);
    setCentralWidget(centralWidget);

    setWindowTitle("QtC++ Password Manager");
    resize(800, 600);
}
```

## Kontakt
Für Fragen oder Vorschläge können Sie mich unter prangenbergdean@gmai.com kontaktieren.
