/*!
 *  \brief     Serial Helper Header File
 *  \author    Armin K. Langroodi
 *  \version   1.0
 *  \date      2020
 *  \copyright GNU Public License.
 */

#ifndef SERIALHELPER_H
#define SERIALHELPER_H

//! \include Serial Port
#include <QSerialPort>
//! \include Tree Widget
#include <QTreeWidget>

//! \typedef Read Ready Callback
typedef void (*ReadReadyCallback)(QTreeWidget*, const QByteArray&);

//! \class Serial Communication Serial Helper
class SerialHelper : public QObject
{
    Q_OBJECT

    //! \public
public:
    explicit SerialHelper(QSerialPort *serialPort /*!< [in] Serial Port Pointer */,
                          QTreeWidget *treeWidget /*!< [in] Tree Widget Object */,
                          ReadReadyCallback readReadyCallback /*!< [in] Serial Reading Ready Callback */,
                          QObject *parent = nullptr /*!< UI Pattern */); //!< Constructor
    bool Write(const QByteArray &data /*!< [in] Data to be Written */); //!< Write Data to the Serial Port

private slots:
    void onReadReady(); //!< On Serial Port Read Ready Signal Slot

    //! \private
private:
    QSerialPort *serialPort; //!< Serial Port Pointer
    QTreeWidget* treeWidget; //!< Tree Widget Object
    ReadReadyCallback readReadyCallback; //!< Serial Reading Ready Callback
};

#endif // SERIALHELPER_H
