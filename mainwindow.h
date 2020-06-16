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
    void updateSerialPorts();
    static void addMessage(QTreeWidget *treeWidget, CanFrame *canFrame, bool isIncoming);
    QSerialPort serialPort;
    SerialHelper *serialHelper;
    static void readReadyCallback(QTreeWidget *treeWidget, QByteArray data);
};

#endif // MAINWINDOW_H
