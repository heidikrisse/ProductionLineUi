#include <QtSql>
#include "../include/sqlite.hpp"
#include "../include/json_parser.h"

Db_manager::Db_manager() {
    if (create_connection()) {
        qDebug() << "Db testing!";
    }
}

bool Db_manager::create_connection() {
    // Creates db to ~/Documents/production_line.db if it not exists
    db = QSqlDatabase::addDatabase("QSQLITE");
    //  Returns the directory containing user document files
    QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    db.setDatabaseName(path + "/production_line.db");

    if (!db.open()) {
        qDebug() << "Cannot open database";
//        QMessageBox::critical(nullptr, QObject::tr("Cannot open database.\nClick Cancel to exit."),
//                    QMessageBox::Cancel);
        return false;
    } else {
        qDebug() << "Opened database successfully";
    }

    // Creates table to database if it not exists
    QSqlQuery query(db);
    query.exec("CREATE TABLE IF NOT EXISTS line_data (timestamp TEXT PRIMARY KEY, "
               "conveyor_speed INT, heater1 INT, heater2 INT, heater3 INT, cooler INT, "
               "qc_camera INT, temp1 REAL, temp2 REAL, temp3 REAL, temp4 REAL, temp5 REAL, "
               "temp6 REAL, temp7 REAL, temp8 REAL, temp9 REAL, temp10 REAL)");
    return true;
}

bool Db_manager::add_data(json_data::parsed_json parsed_data) {
    // Should we add the check if data is correct?
    QSqlQuery query;
    query.prepare("INSERT INTO line_data (timestamp, conveyor_speed, heater1, heater2, heater3, "
                  "cooler, qc_camera, temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8, "
                  "temp9, temp10) "
                  // Placeholders for values
                  "VALUES (:timestamp, :conveyor_speed, :heater1, :heater2, :heater3, :cooler, "
                  ":qc_camera, :temp1, :temp2, :temp3, :temp4, :temp5, :temp6, :temp7, :temp8, "
                  ":temp9, :temp10)");

    // Binding placeholders and values
    query.bindValue(":timestamp", QString::fromStdString(parsed_data.timestamp));
    query.bindValue(":conveyor_speed", parsed_data.units_per_minute);
    query.bindValue(":heater1", parsed_data.heater1_status);
    query.bindValue(":heater2", parsed_data.heater2_status);
    query.bindValue(":heater3", parsed_data.heater3_status);
    query.bindValue(":cooler", parsed_data.cooler_status);
    query.bindValue(":qc_camera", parsed_data.qc_camera_status);
    query.bindValue(":temp1", parsed_data.heat_sensors[0]);
    query.bindValue(":temp2", parsed_data.heat_sensors[1]);
    query.bindValue(":temp3", parsed_data.heat_sensors[2]);
    query.bindValue(":temp4", parsed_data.heat_sensors[3]);
    query.bindValue(":temp5", parsed_data.heat_sensors[4]);
    query.bindValue(":temp6", parsed_data.heat_sensors[5]);
    query.bindValue(":temp7", parsed_data.heat_sensors[6]);
    query.bindValue(":temp8", parsed_data.heat_sensors[7]);
    query.bindValue(":temp9", parsed_data.heat_sensors[8]);
    query.bindValue(":temp10", parsed_data.heat_sensors[9]);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Adding data to database failed:"
               << query.lastError();
        return false;
    }
}

void Db_manager::print_data_for_debugging(const QString selected_timestamp) {
    QSqlQuery query(db);
    query.setForwardOnly(true);
    // Querying some data out
    query.prepare("SELECT timestamp, conveyor_speed, heater1, cooler, temp3, temp10 FROM line_data WHERE timestamp = :timestamp");
    query.bindValue(":timestamp", selected_timestamp);
    if (!query.exec()) {
        qDebug() << "SQL query error:" << query.lastError().text();
    }
    while(query.next()) {
        QString time = query.value(0).toString();
        int speed = query.value(1).toInt();
        int heat1 = query.value(2).toInt();
        int cool = query.value(3).toInt();
        float t3 = query.value(4).toFloat();
        float t10 = query.value(5).toFloat();
        qDebug() << "Time:" << time << ", conveyor speed:" << speed << ", heater1 is turned on:" << std::boolalpha << heat1
                 << ", cooler is turned on:" << std::boolalpha << cool << ", temp.sensor 3:" << t3 << "temp.sensor 10:" << t10;
    }
}
