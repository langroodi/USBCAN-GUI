/*!
 *  \brief     Serial Helper Source File
 *  \author    Armin K. Langroodi
 *  \version   1.0
 *  \date      2020
 *  \copyright GNU Public License.
 */

//! \include Serial Helper Header
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

    //! \remark QT Signal Binding
    connect(
                serialPort, &QSerialPort::readyRead,
                this, &SerialHelper::onReadReady);
}

void SerialHelper::onReadReady()
{
    QByteArray _readData = serialPort->readAll();
    (*readReadyCallback)(treeWidget, _readData);
}

bool SerialHelper::Write(const QByteArray &data)
{
    const qint64 _bytesWritten = serialPort->write(data);
    bool _result = (_bytesWritten == data.size());

    return _result;
}
