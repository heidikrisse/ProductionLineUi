#include <QtSql>
#include "../include/sqlite.hpp"
#include "../include/mqtt_client.h"

bool Db_manager::create_connection()
{
    // Creates db to ~/Documents/production_line.db if it not exists
    db = QSqlDatabase::addDatabase("QSQLITE");
    //  Returns the directory containing user document files
    QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    db.setDatabaseName(path + "/production_line.db");

    if (!db.open())
    {
        qDebug() << "Cannot open database";
//        QMessageBox::critical(nullptr, QObject::tr("Cannot open database.\nClick Cancel to exit."),
//                    QMessageBox::Cancel);
        return false;
    }
    else
    {
        qDebug() << "Opened database successfully";
    }

    // Creates table to database if it not exists
    QSqlQuery query(db);
    query.exec("CREATE TABLE IF NOT EXISTS line_data (id INTEGER PRIMARY KEY AUTOINCREMENT, timestamp TEXT, conv_ctrl INT, "
               "heat1_ctrl INT, heat2_ctrl INT, heat3_ctrl INT, cool_ctrl INT, conveyor_speed INT, heater1 INT, heater2 INT, "
               "heater3 INT, cooler INT, qc_camera INT, temp1 REAL, temp2 REAL, temp3 REAL, temp4 REAL, temp5 REAL, temp6 REAL, "
               "temp7 REAL, temp8 REAL, temp9 REAL, temp10 REAL)");
    query.exec("CREATE TABLE IF NOT EXISTS camera_data (id INT PRIMARY KEY AUTOINCREMENT, timestamp TEXT, non_passers INT)");
    return true;
}

bool Db_manager::add_line_data(CurrentConveyerData& parsed_data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO line_data (timestamp, conv_ctrl, heat1_ctrl, heat2_ctrl, "
                  "heat3_ctrl, cool_ctrl, conveyor_speed, heater1, heater2, heater3, cooler, "
                  "qc_camera, temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8, temp9, "
                  "temp10) VALUES (:timestamp, :conv_ctrl, :heat1_ctrl, :heat2_ctrl, :heat3_ctrl, "
                  ":cool_ctrl, :conveyor_speed, :heater1, :heater2, :heater3, :cooler, "
                  ":qc_camera, :temp1, :temp2, :temp3, :temp4, :temp5, :temp6, :temp7, :temp8, :temp9, :temp10)");

    // Binding placeholders and values
    query.bindValue(":timestamp", QString::fromStdString(parsed_data.time_stamp));
    query.bindValue(":conveyor_speed", parsed_data.conveyer_upm);
    query.bindValue(":heater1", parsed_data.heater1);
    query.bindValue(":heater2", parsed_data.heater2);
    query.bindValue(":heater3", parsed_data.heater3);
    query.bindValue(":cooler", parsed_data.cooler);
    query.bindValue(":qc_camera", parsed_data.qc_camera_toggle);
    query.bindValue(":temp1", parsed_data.temps[0]);
    query.bindValue(":temp2", parsed_data.temps[1]);
    query.bindValue(":temp3", parsed_data.temps[2]);
    query.bindValue(":temp4", parsed_data.temps[3]);
    query.bindValue(":temp5", parsed_data.temps[4]);
    query.bindValue(":temp6", parsed_data.temps[5]);
    query.bindValue(":temp7", parsed_data.temps[6]);
    query.bindValue(":temp8", parsed_data.temps[7]);
    query.bindValue(":temp9", parsed_data.temps[8]);
    query.bindValue(":temp10", parsed_data.temps[9]);
    query.bindValue(":conv_ctrl", parsed_data.conveyer_manual_control);
    query.bindValue(":heat1_ctrl", parsed_data.heater1_manual_control);
    query.bindValue(":heat2_ctrl", parsed_data.heater2_manual_control);
    query.bindValue(":heat3_ctrl", parsed_data.heater3_manual_control);
    query.bindValue(":cool_ctrl", parsed_data.cooler_manual_control);

    if (query.exec())
    {
        return true;
    }
    else
    {
        qDebug() << "Adding data to database failed:"
               << query.lastError();
        return false;
    }
}

//bool Db_manager::add_camera_data(CurrentConveyerData parsed_data)
//{
//    QSqlQuery query;
//    query.prepare("INSERT INTO camera_data (timestamp, non_passers) "
//                  // Placeholders for values
//                  "VALUES (:timestamp, :non_passers");

//    // Binding placeholders and values
//    query.bindValue(":timestamp", QString::fromStdString(parsed_data.time_stamp));
//    query.bindValue(":non_passers", parsed_data.time_stamp);

//    if (query.exec())
//    {
//        return true;
//    }
//    else
//    {
//        qDebug() << "Adding data to database failed:"
//               << query.lastError();
//        return false;
//    }
//}

void Db_manager::print_line_data()  //(const QString& selected_timestamp)
{
    QSqlQuery query(db);
    query.setForwardOnly(true);
    // Querying some data out
    query.prepare("SELECT timestamp, conveyor_speed, heater1, cooler, temp3, temp10 FROM line_data");  // WHERE timestamp = :timestamp");
    //query.bindValue(":timestamp", selected_timestamp);
    if (!query.exec())
    {
        qDebug() << "SQL query error:" << query.lastError().text();
    }
    while(query.next())
    {
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
