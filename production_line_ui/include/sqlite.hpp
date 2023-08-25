#ifndef DB_MANAGER
#define DB_MANAGER
#include <QtSql>

class Db_manager
{
  public:
    Db_manager();
  private:
    QSqlDatabase db;
};

#endif
