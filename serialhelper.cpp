#include "serialhelper.h"

SerialHelper::SerialHelper(QSerialPort *serialPort,
                           QTreeWidget *treeWidget,
                           ReadReadyCallback readReadyCallback,
                           QObject *parent) :
    QObject(parent)
{
    this->treeWidget = treeWidget;
    this->serialPort = serialPort;
    this->readReadyCallback = readReadyCallback;

    connect(
                serialPort, &QSerialPort::readyRead,
                this, &SerialHelper::onReadReady);
} //!< Constructor

void SerialHelper::onReadReady()
{
    QByteArray _readData = serialPort->readAll();
    (*readReadyCallback)(treeWidget, _readData);
}

bool SerialHelper::Write(QByteArray data)
{
    const qint64 _bytesWritten = serialPort->write(data);
    bool _result = (_bytesWritten == data.size());

    return _result;
}
