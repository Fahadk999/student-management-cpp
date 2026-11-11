#include <sqlite3.h>
#include <cstring>

class Database {
private:
    char dbName[15];
    sqlite3* db;

    bool InitDB ();
public:
    Database (const char*);
    bool MakeTable (const char*);
    bool ShowData (const char*);
};
