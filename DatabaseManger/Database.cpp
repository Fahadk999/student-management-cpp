#include "Database.hpp"

Database::Database (const char* _dbName) {
    strcpy(this->dbName, _dbName); 
}

bool Database::InitDB () {
    int result = sqlite3_open((this->dbName), &db);

    if (result != SQLITE_OK) {
        return false; 
    } return true;
}

bool Database::MakeTable (const char* query) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(
        db,
        query,
        nullptr,
        nullptr,
        &errMsg
    );

    if (rc != SQLITE_OK) {
        return false;
        sqlite3_free(errMsg);
    } return true;
}