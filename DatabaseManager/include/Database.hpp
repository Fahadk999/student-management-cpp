#pragma once

#include <sqlite3.h>
#include <iostream>
#include <cstring>
#include <cstdio>

int callback (void*, int, char**, char**);

class Database {
private:
    char dbName[35];
    sqlite3* db;
    char* err{nullptr};

public:
    Database (const char*);
    ~Database ();
    bool InitDB ();
    bool MakeTable (const char*);
    bool ReadData (const char*);
    bool UpdateData (const char*);
    bool ClearDB (const char*); 
    void CloseDB ();
    bool Execute (const char*);
};

