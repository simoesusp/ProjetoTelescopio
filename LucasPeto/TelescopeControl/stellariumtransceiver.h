#ifndef STELLARIUMTRANSCEIVER_H
#define STELLARIUMTRANSCEIVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class StellariumTransceiver : public QObject
{
    Q_OBJECT

    public:
    StellariumTransceiver(QObject *parent = 0);

    private slots:
    void slotNewConnection();
    void slotSocketDisconnected();
    void slotReadyRead();
    void slotSocketError();

    private:
    QTcpServer m_tcpServer;
    QTcpSocket *m_socket;

};

#endif // STELLARIUMTRANSCEIVER_H
