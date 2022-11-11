#include "mydb.h"

#include <QSettings>

MyDB* MyDB::m_pDb = nullptr;

MyDB::MyDB()
{

}

MyDB::~MyDB()
{

}

MyDB *MyDB::getInst()
{
    if (!m_pDb)
    {
        m_pDb = new MyDB();
    }
    return m_pDb;
}

void MyDB::destroyInst()
{
    if (!m_pDb)
    {
        return;
    }
    delete m_pDb;
    m_pDb = nullptr;
}

void MyDB::connect()
{
    QSettings config("../../config.ini", QSettings::Format::IniFormat);
    QString userName = config.value("database/user_name").toString();
    QString password = config.value("database/password").toString();

    QString dbUri = QString("mongodb+srv://%1:%2@cluster0.88yln.mongodb.net/?retryWrites=true&w=majority").arg(userName, password);
    mongocxx::client client{mongocxx::uri{dbUri.toStdString()}};
    mongocxx::database db = client["db_test"];
    mongocxx::collection coll = db["collection_test"];
}
