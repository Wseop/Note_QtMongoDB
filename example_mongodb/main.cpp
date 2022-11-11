#include <QCoreApplication>

#include "mydb.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyDB* pDb = MyDB::getInst();

    pDb->connect();

    pDb->insertDocument();
    pDb->findDocument();

    pDb->updateDocument();
    pDb->findDocument();

    return a.exec();
}
