#include "Database.hpp"

int callback (void* data, int argc, char** argv, char** colName) {
    for (int i = 0; i < argc; i++) {
        std::cout 
            << colName [i] << ": "
            << (argv[i] ? argv[i] : "NULL")
            << " | ";
    } std::cout << "\n";
    return 0;
}

Database::Database (const char* _dbName) {
    strcpy(this->dbName, _dbName); 
}
Database::~Database () {
    CloseDB();
}

bool Database::Execute (const char* query) {
    int rc = sqlite3_exec(
        db,
        query,
        nullptr,
        nullptr,
        &err
    );
    if (rc != SQLITE_OK) {
        std::cerr << err << '\n';
        sqlite3_free(err);
        err = nullptr;
        return false; 
    } return true;
}

bool Database::InitDB () {
    int rc = sqlite3_open((this->dbName), &db);
    if (rc != SQLITE_OK) {
        std::cerr << this->err << '\n';
        sqlite3_free(this->err);
        return false; 
    } return true;
}

bool Database::MakeTable (const char* query) {
    return Execute(query);
}

bool Database::ReadData (const char* query) {
    char *errMsg = nullptr;
    int rc = sqlite3_exec(
        db,
        query,
        callback,
        nullptr,
        &errMsg
    );

    if (rc != SQLITE_OK) {
        std::cerr << errMsg << '\n';
        sqlite3_free(errMsg);
        return false;
    } return true;
}

bool Database::UpdateData (const char* query) {
    return Execute(query);
}

bool Database::ClearDB (const char* tableName) {
    const char* partOne = "DELETE FROM ";
    char query[200];
    snprintf(query, sizeof(query), "%s%s%c", partOne, tableName, ';'); 

    return Execute(query);
}

void Database::CloseDB () {
    sqlite3_close(db);
}
