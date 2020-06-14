#include "serialhelper.h"

SerialHelper::SerialHelper(
        QSerialPort *serialPort,
        void (*readReadyCallback)(QByteArray),
        void (*writeDoneCallback)(qint64),
        QObject *parent) :
    QObject(parent)
{
    this->serialPort = serialPort;
    this->readReadyCallback = readReadyCallback;
    this->writeDoneCallback = writeDoneCallback;

    connect(
                serialPort, &QSerialPort::readyRead,
                this, &SerialHelper::onReadReady);
    connect(
                serialPort, &QSerialPort::bytesWritten,
                this, &SerialHelper::onWriteDone);
} //!< Constructor

void SerialHelper::onReadReady()
{
    QByteArray _readData = serialPort->readAll();
    (*readReadyCallback)(_readData);
}

void SerialHelper::onWriteDone(qint64 bytes)
{
    (*writeDoneCallback)(bytes);
}

bool SerialHelper::Write(QByteArray data)
{
    const qint64 _bytesWritten = serialPort->write(data);
    bool _result = (_bytesWritten == data.size());

    return _result;
}
