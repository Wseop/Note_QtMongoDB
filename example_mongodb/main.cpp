#include <QCoreApplication>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/options/client.hpp>

#include <bsoncxx/builder/stream/document.hpp>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    mongocxx::instance inst{};
    // set username & password for test
    const auto uri = mongocxx::uri{"mongodb+srv://<username>:<password>@cluster0.88yln.mongodb.net/?retryWrites=true&w=majority"};
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