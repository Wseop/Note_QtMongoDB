#ifndef MYDB_H
#define MYDB_H

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/options/client.hpp>

class MyDB
{
private:
    MyDB();
    ~MyDB();

public:
    static MyDB* getInst();
    static void destroyInst();

    void connect();

private:
    // this should be done only once;
    mongocxx::instance inst{};
    // singleton pattern
    static MyDB* m_pDb;

public:
    mongocxx::database db;
    mongocxx::collection collection;
};

#endif // MYDB_H
