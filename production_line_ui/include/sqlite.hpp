#ifndef DB_MANAGER
#define DB_MANAGER
#include <QtSql>
#include <vector>
#include <array>
#include "mqtt_client.h"

class Db_manager
{
  public:
    Db_manager() = default;
    bool create_connection();
    bool add_line_data(CurrentConveyorData& data);
    std::vector<CurrentConveyorData> get_all_dbData();
    void print_line_data();

  private:
    QSqlDatabase db;
};

#endif
