#include <QtSql>
#include "../include/sqlite.hpp"

Db_manager::Db_manager() {
    db = QSqlDatabase::addDatabase("SQLITE");
    QString path{QStandardPaths::DocumentsLocation + "/production_line.db"};
    db.setDatabaseName(path);  //Jos resourcesiin ei saa laitettua db:a, vaihtoehto: QStandardPaths::AppDataLocation

    if (!db.open()) {
        qDebug() << "Connection with database failed!";
    } else {
        qDebug() << "Opened database successfully";
    }
}
