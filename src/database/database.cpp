//
// Created by prang on 27.04.2024.
//

#include <iostream>
#include "sqlite3.h" // SQLite Header

int database() {
    sqlite3* db; // SQLite-Datenbank-Handle
    char* errMsg = nullptr; // Fehlermeldung-Handle

    // SQLite-Datenbank öffnen oder erstellen
    int rc = sqlite3_open("passwords.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return 1; // Fehler beim Öffnen der Datenbank
    }

    // Tabellen für Benutzernamen und Passwörter erstellen
    const char* createUsersTableSQL = "CREATE TABLE IF NOT EXISTS Users (ID INTEGER PRIMARY KEY, Username TEXT);";
    const char* createPasswordsTableSQL = "CREATE TABLE IF NOT EXISTS Passwords (ID INTEGER PRIMARY KEY, Password TEXT);";
    rc = sqlite3_exec(db, createUsersTableSQL, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1; // Fehler beim Erstellen der Benutzertabelle
    }
    rc = sqlite3_exec(db, createPasswordsTableSQL, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1; // Fehler beim Erstellen der Passworttabelle
    }

    // Benutzereingabe für Benutzername und Passwort erfassen
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    // Daten in die Benutzer- und Passworttabellen einfügen
    std::string insertUserSQL = "INSERT INTO Users (Username) VALUES ('" + username + "');";
    std::string insertPasswordSQL = "INSERT INTO Passwords (Password) VALUES ('" + password + "');";
    rc = sqlite3_exec(db, insertUserSQL.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1; // Fehler beim Einfügen des Benutzernamens
    }
    rc = sqlite3_exec(db, insertPasswordSQL.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1; // Fehler beim Einfügen des Passworts
    }

    // Datenbank schließen
    sqlite3_close(db);

    std::cout << "Data inserted successfully." << std::endl;

    return 0; // Programm erfolgreich beendet
}