#include "stellariumtransceiver.h"
#include <QDebug>
#include <QByteArray>
#include <QDateTime>
#include <QtCore/qmath.h>

StellariumTransceiver::StellariumTransceiver(QObject *parent) :
    QObject(parent)
{

    qDebug() << "Inicializando";
    connect(&m_tcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));

    m_tcpServer.listen(QHostAddress::Any, 10001);
}

void StellariumTransceiver::slotNewConnection() {
    qDebug() << "Capturando uma nova conexão...";
    m_socket = m_tcpServer.nextPendingConnection();
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotSocketError()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(slotSocketDisconnected()));
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
}

void StellariumTransceiver::slotSocketDisconnected() {
    qDebug() << "Conexão perdida";
}

void StellariumTransceiver::slotReadyRead() {
    qDebug() << "Dados recebidos";
    quint16 messageSize;

    if (m_socket->bytesAvailable() < 2) {
        qDebug() << "Dados insuficientes";
        return;
    }

    QByteArray ba;
    ba = m_socket->peek(2);

    messageSize = ba[0] + (ba[1] << 8);
    //qDebug() << QString("Tamanho da mensagem: %1").arg(messageSize);
    if (m_socket->bytesAvailable() < messageSize) {
        qDebug() << "Dados insuficientes";
        return;
    }

    ba =  m_socket->read(messageSize);
    //qDebug() << "Packet: " << ba.toHex();
    //quint16 type;
    quint64 currentTimeRaw;
    quint32 raRaw;
    double RA;
    qint32 decRaw;
    double DEC;

    //type = ba[2] + (ba[3] << 8);

    currentTimeRaw = 0;
    for (int i=7; i>=0; i--) {
        //qDebug() << QString("Byte: 0x%1").arg((int)ba[i+4] & 0xFF, 2, 16, QChar('0'));
        //qDebug() << QString("Antes (%1): %2").arg(i).arg(currentTimeRaw);
        currentTimeRaw <<= 8;
        currentTimeRaw += (ba[i+4] & 0xFF);

        //qDebug() << QString("Depois (%1): %2").arg(i).arg(currentTimeRaw);
    }

    raRaw = 0;
    for (int i=3; i>=0; i--) {
        raRaw <<= 8;
        raRaw += (ba[i+12] & 0xFF);
    }

    decRaw = 0;
    for (int i=3;i>=0;i--) {
        decRaw <<= 8;
        decRaw += (ba[i+16] & 0xFF);
    }

    QDateTime currentTime = QDateTime::fromMSecsSinceEpoch(currentTimeRaw / 1000);
    RA = raRaw * 24.0 / (double)0xFFFFFFFF;
    DEC = decRaw * 180.0 / (double)0x80000000;

    //qDebug() << "Type: " << type;
    //qDebug() << "Time: " << currentTimeRaw << " -> " << currentTime;
    qDebug() << "Time: " << currentTime;
    qDebug() << "RA: " << raRaw << " -> "  << RA;
    qDebug() << "DEC: " << decRaw << " -> "  << DEC;

    QDateTime j2000 = QDateTime::fromString("2000-01-01T12:00:00+00:00", Qt::ISODate);
    //currentTime = QDateTime::fromString("1998-08-10T23:10:00+00:00", Qt::ISODate);

    qDebug() << "J2000: " << j2000;
    qDebug() << "CurrentTime: " << currentTime;

    qint64 dateDiff = j2000.msecsTo(currentTime);
    double daysFromJ2000 = dateDiff / 1000.0 / 60.0 / 60.0 / 24.0;
    //daysFromJ2000 = -508.53472;
    qDebug() << "d: " << daysFromJ2000;

    double decimalHours = currentTime.time().hour() + (currentTime.time().minute() / 60.0) + (currentTime.time().second() / 3600.0) + (currentTime.time().msec() / 3600000.0);
    qDebug() << "UT: " << decimalHours;

    double LATH = 22;
    double LATM = 1;
    double LAT = -1*(LATH+LATM/60.0); // -1 sul

    double LONGH = 47;
    double LONGM = 53;
    double LONG = -1*(LONGH+LONGM/60.0);// -1 west
    qDebug() << "Long: " << LONG;

    double LST = 100.46 + (0.985647 * daysFromJ2000) + LONG + (15 * decimalHours);

    while (LST < 0) {
        LST += 360.0;
    }
    while (LST > 360) {
        LST -= 360.0;
    }

    qDebug() << "LST: " << LST;

    double RADegrees = RA * 15.0;
    qDebug() << "RA degrees: " << RADegrees;

    double HA = LST - RADegrees;
    while (HA < 0) {
        HA += 360.0;
    }
    while (HA > 360) {
        HA -= 360.0;
    }

    qDebug() << "HA: " << HA;
    qDebug() << "DEC: " << DEC;
    qDebug() << "LAT: " << LAT;

    double ALT = qAsin( (qSin(DEC/57.2957795)*qSin(LAT/57.2957795)+qCos(DEC/57.2957795)*qCos(LAT/57.2957795)*qCos(HA/57.2957795))) * 57.2957795;

    qDebug() << "ALT: " << ALT;

    double A = qAcos( (qSin(DEC/57.2957795) - qSin(ALT/57.2957795)*qSin(LAT/57.2957795)) / (qCos(ALT/57.2957795)*qCos(LAT/57.2957795))) * 57.2957795;
    qDebug() << "A: " << A;

    double AZ = 0.0;
    if (qSin(HA/57.2957795) < 0)
        AZ = A;
    else AZ = 360 - A;

    qDebug() << "AZ: " << AZ;
}

void StellariumTransceiver::slotSocketError() {
    qDebug() << "Erro no socket";
}
