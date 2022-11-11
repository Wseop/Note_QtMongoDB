#include <QCoreApplication>
#include <QSettings>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/options/client.hpp>

#include <bsoncxx/builder/stream/document.hpp>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSettings settings("../../config.ini", QSettings::Format::IniFormat);
    QString userName = settings.value("database/user_name").toString();
    QString password = settings.value("database/password").toString();

    mongocxx::instance inst{};
    // set username & password for test
    const auto uri = mongocxx::uri{QString("mongodb+srv://%1:%2@cluster0.88yln.mongodb.net/?retryWrites=true&w=majority").arg(userName, password).toStdString()};
    mongocxx::options::client client_options;
    auto api = mongocxx::options::server_api{mongocxx::options::server_api::version::k_version_1};
    client_options.server_api_opts (api);
    mongocxx::client conn{uri, client_options};
    // set db name
    mongocxx::database db = conn["db_test"];
    // set collection name
    mongocxx::collection collection = db.collection("collection_test");

    // insert document
    bsoncxx::builder::stream::document document{};
    document << "TestKey" << "TestValue";
    collection.insert_one(document.view());

    return a.exec();
}
