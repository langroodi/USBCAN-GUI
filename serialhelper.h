#ifndef SERIALHELPER_H
#define SERIALHELPER_H

//! \include Serial Port
#include <QSerialPort>

//! \include Tree Widget
#include <QTreeWidget>

//! \typedef Read Ready Callback
typedef void (*ReadReadyCallback)(QTreeWidget*, QByteArray);

class SerialHelper : public QObject
{
    Q_OBJECT

    //! \public
public:
    explicit SerialHelper(QSerialPort *serialPort,
                          QTreeWidget *treeWidget,
                          ReadReadyCallback readReadyCallback,
                          QObject *parent = nullptr);
    bool Write(QByteArray data);

private slots:
    void onReadReady();

    //! \private
private:
    QSerialPort *serialPort; //!< Serial Port Pointer
    QTreeWidget* treeWidget;
    ReadReadyCallback readReadyCallback;
    void (*writeDoneCallback)(qint64);
};

#endif // SERIALHELPER_H
