#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QTreeWidget>
#include "canframe.h"
#include "serialhelper.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_remoteCheckBox_clicked();

    void on_sendButton_clicked();

    void on_startButton_clicked();

private:
    Ui::MainWindow *ui;
    void updateSerialPorts(); //!< Update Serial Port List
    static void addMessage(
            QTreeWidget *treeWidget /*!< [in] Tree Widget */,
            const CanFrame &canFrame /*!< [in] CAN Frame Object */,
            const bool &isIncoming /*!< [in] Is the Message Incoming or Outgoing */); //!< Add a CAN Message to a Tree Widget
    QSerialPort serialPort; //!< Serial Port Instance
    SerialHelper *serialHelper; //!< Serial Port Helper
    static void readReadyCallback(QTreeWidget *treeWidget /*!< [in] Tree Widget */,
            const QByteArray &data /*!< [in] Recieved Data*/); //!< Read Ready Callback
};

#endif // MAINWINDOW_H
