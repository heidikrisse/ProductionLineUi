#ifndef DB_MANAGER
#define DB_MANAGER
#include <QtSql>
#include "mqtt_client.h"

class Db_manager
{
  public:
    Db_manager() = default;
    bool create_connection();
    bool add_line_data(CurrentConveyerData data);
    bool add_camera_data(CurrentConveyerData data);
    void print_line_data();  //(const QString& selected_timestamp);

  private:
    QSqlDatabase db;
};

#endif
