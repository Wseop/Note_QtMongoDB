#include "mydb.h"

#include <QSettings>
#include <bsoncxx/builder/stream/document.hpp>

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
    m_client = {mongocxx::uri{dbUri.toStdString()}};
    m_db = m_client["db_test"];
    m_coll = m_db["collection_test"];
}

void MyDB::insertDocument()
{
    /*
     * insert below document
     *  {
     *      "Name": "쿠키",
     *      "Level": 1540,
     *      "Attr": ["특화", "신속"],
     *      "Engrave": {
     *          "Name": "원한",
     *          "Level": 3
     *      }
     *  }
     */
    bsoncxx::builder::stream::document document{};
    document << "Name" << "쿠키"
            << "Level" << 1540
            << "Attr" << bsoncxx::builder::stream::open_array
                << "특화" << "신속"
            << bsoncxx::builder::stream::close_array
            << "Engrave" << bsoncxx::builder::stream::open_document
                << "Name" << "원한"
                << "Level" << 3
            << bsoncxx::builder::stream::close_document;
    m_coll.insert_one(document.view());
}
