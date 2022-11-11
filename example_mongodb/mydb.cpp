#include "mydb.h"

#include <QSettings>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

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

void MyDB::findDocument()
{
    // find all documents
    mongocxx::cursor cursor = m_coll.find({});
    for (auto doc : cursor)
    {
        QString jsonDoc = bsoncxx::to_json(doc).c_str();
        QJsonObject jsonObj(QJsonDocument::fromJson(jsonDoc.toUtf8()).object());

        qDebug() << "Name :" << jsonObj.find("Name")->toString();
        qDebug() << "Level :" << jsonObj.find("Level")->toInt();
        qDebug() << "Attr :" << jsonObj.find("Attr")->toArray().at(0).toString();
        qDebug() << "Engrave :" << jsonObj.find("Engrave")->toObject().find("Name")->toString();
    }

    // find a document with condition
    auto result = m_coll.find_one(
                bsoncxx::builder::stream::document{}
                << "Name" << "쿠키" << bsoncxx::builder::stream::finalize);
    QString jsonDoc = bsoncxx::to_json(*result).c_str();
    QJsonObject jsonObj(QJsonDocument::fromJson(jsonDoc.toUtf8()).object());

    qDebug() << "Name :" << jsonObj.find("Name")->toString();
    qDebug() << "Level :" << jsonObj.find("Level")->toInt();
    qDebug() << "Attr :" << jsonObj.find("Attr")->toArray().at(0).toString();
    qDebug() << "Engrave :" << jsonObj.find("Engrave")->toObject().find("Name")->toString();
}
