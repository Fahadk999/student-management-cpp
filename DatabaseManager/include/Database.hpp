#include <sqlite3.h>
#include <cstring>
#include <cstdio>

int callback (void*, int, char**, char**);

class Database {
private:
    char dbName[35];
    sqlite3* db;

public:
    Database (const char*);
    bool InitDB ();
    bool MakeTable (const char*);
    bool ShowData (const char*);
    bool ReadUser (const char*);
    bool UpdateUser (const char*);
    bool ClearDB ();
    void CloseDB ();
};

