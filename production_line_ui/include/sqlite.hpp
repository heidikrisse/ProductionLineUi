#ifndef DB_MANAGER
#define DB_MANAGER
#include <QtSql>
#include "json_parser.h"

class Db_manager
{
  public:
    Db_manager();
    bool create_connection();
    bool add_data(json_data::parsed_json data_vector);
    void print_data_for_debugging(const QString timestamp);

  private:
    QSqlDatabase db;
};

#endif
