#include <QCoreApplication>
#include <QApplication>
#include "stellariumTransceiver.h"
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StellariumTransceiver stellariumtransceiver(0);
    qDebug() << "Aguardando Conexão...";
    return a.exec();
}
