#include "../include/sqlite.hpp"
#include "../include/mqtt_client.h"

#include <QtSql>
Db_manager::Db_manager() : db(QSqlDatabase::addDatabase("QSQLITE"))
{

}
bool Db_manager::create_connection()
{
    // Creates db to ~/Documents/production_line.db if it not exists
    //  Returns the directory containing user document files
    QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    db.setDatabaseName(path + "/production_line.db");

    if (!db.open())
    {
        qDebug() << "Cannot open database";

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
               "heater3 INT, cooler INT, qc_camera INT, non_passers INT, temp1 REAL, temp2 REAL, temp3 REAL, temp4 REAL, temp5 REAL, temp6 REAL, "
               "temp7 REAL, temp8 REAL, temp9 REAL, temp10 REAL)");
    return true;
}

bool Db_manager::add_line_data(CurrentConveyorData& parsed_data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO line_data (timestamp, conv_ctrl, heat1_ctrl, heat2_ctrl, "
                  "heat3_ctrl, cool_ctrl, conveyor_speed, heater1, heater2, heater3, cooler, "
                  "qc_camera, non_passers, temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8, temp9, "
                  "temp10) VALUES (:timestamp, :conv_ctrl, :heat1_ctrl, :heat2_ctrl, :heat3_ctrl, "
                  ":cool_ctrl, :conveyor_speed, :heater1, :heater2, :heater3, :cooler, "
                  ":qc_camera, :non_passers, :temp1, :temp2, :temp3, :temp4, :temp5, :temp6, :temp7, :temp8, :temp9, :temp10)");

    // Binding placeholders and values
    query.bindValue(":timestamp", QString::fromStdString(parsed_data.time_stamp));
    query.bindValue(":conveyor_speed", parsed_data.conveyor_upm);
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
    query.bindValue(":conv_ctrl", parsed_data.conveyor_manual_control);
    query.bindValue(":heat1_ctrl", parsed_data.heater1_manual_control);
    query.bindValue(":heat2_ctrl", parsed_data.heater2_manual_control);
    query.bindValue(":heat3_ctrl", parsed_data.heater3_manual_control);
    query.bindValue(":cool_ctrl", parsed_data.cooler_manual_control);
    query.bindValue(":non_passers", parsed_data.qc_camera_fails);

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

std::vector<CurrentConveyorData> Db_manager::get_all_dbData() {
    std::vector<CurrentConveyorData> data_vector{};
    QSqlQuery query(db);
    query.setForwardOnly(true);
    query.prepare("SELECT timestamp, conv_ctrl, heat1_ctrl, heat2_ctrl, heat3_ctrl, cool_ctrl, qc_camera, non_passers, conveyor_speed, heater1, heater2, heater3, cooler, temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8, temp9, temp10 FROM line_data");
    if (!query.exec()) {
        qDebug() << "Getting db-data failed:" << query.lastError().text();
    }
    while(query.next()) {
        CurrentConveyorData tmp_struct;
        tmp_struct.time_stamp = query.value(0).toString().toStdString();
        tmp_struct.conveyor_manual_control = query.value(1).toBool();
        tmp_struct.heater1_manual_control = query.value(2).toBool();
        tmp_struct.heater2_manual_control = query.value(3).toBool();
        tmp_struct.heater3_manual_control = query.value(4).toBool();
        tmp_struct.cooler_manual_control = query.value(5).toBool();
        tmp_struct.qc_camera_toggle = query.value(6).toBool();
        tmp_struct.qc_camera_fails = (query.value(7).toInt());
        tmp_struct.conveyor_upm = query.value(8).toInt();
        tmp_struct.heater1 = query.value(9).toBool();
        tmp_struct.heater2 = query.value(10).toBool();
        tmp_struct.heater3 = query.value(11).toBool();
        tmp_struct.cooler = query.value(12).toBool();

        float t1 = query.value(13).toFloat();
        float t2 = query.value(14).toFloat();
        float t3 = query.value(15).toFloat();
        float t4 = query.value(16).toFloat();
        float t5 = query.value(17).toFloat();
        float t6 = query.value(18).toFloat();
        float t7 = query.value(19).toFloat();
        float t8 = query.value(20).toFloat();
        float t9 = query.value(21).toFloat();
        float t10 = query.value(22).toFloat();

        std::array<float, 10> tmp_array{t1, t2, t3, t4, t5, t6, t7, t8, t9, t10};
        tmp_struct.temps = tmp_array;

        data_vector.push_back(tmp_struct);
    }
    return data_vector;
}

void Db_manager::print_line_data()
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
