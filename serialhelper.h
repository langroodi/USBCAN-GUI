#ifndef SERIALHELPER_H
#define SERIALHELPER_H

//! \include Serial Port
#include <QSerialPort>

class SerialHelper : public QObject
{
    Q_OBJECT

    //! \public
public:
    explicit SerialHelper(QSerialPort *serialPort,
            void (*readReadyCallback)(QByteArray),
            void (*writeDoneCallback)(qint64),
            QObject *parent = nullptr);
    bool Write(QByteArray data);

private slots:
    void onReadReady();
    void onWriteDone(qint64 bytes);

    //! \private
private:
    QSerialPort *serialPort; //!< Serial Port Pointer
    void (*readReadyCallback)(QByteArray);
    void (*writeDoneCallback)(qint64);
};

#endif // SERIALHELPER_H
