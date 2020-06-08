#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canhelper.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    updateSerialPorts();
}

void MainWindow::on_pushButton_clicked()
{
    updateSerialPorts();
}

void MainWindow::updateSerialPorts()
{
    ui->comboBox->clear();
    QList<QSerialPortInfo> comPorts = QSerialPortInfo::availablePorts();

    foreach (QSerialPortInfo comPort, comPorts) {
        ui->comboBox->addItem(comPort.systemLocation());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_remoteCheckBox_clicked()
{
    //! \remark Data field is not allowed during RTR (Remote Transmission Request)
    bool _isChecked =(ui->remoteCheckBox->checkState() == Qt::Checked);
    ui->dataTextBox->setEnabled(!_isChecked);
}

void MainWindow::on_sendButton_clicked()
{
    QString _data = ui->dataTextBox->text();

    QByteArray _array = CanHelper::HexToArray(_data);
    QByteArray _hexArr = _array.toHex().toUpper();
    QString _text(_hexArr);
    QMessageBox msgBox;
    msgBox.setText(_text);
    //msgBox.exec();

    QByteArray ba;
    ba.resize(5);
    ba[0] = 0x3c;
    ba[1] = 0xb8;
    ba[2] = 0x64;
    ba[3] = 0x18;
    ba[4] = 0xca;

    auto checksum = CanHelper::GetChecksum(ba);

    ba.resize(6);
    ba[5] = checksum;
    _text = ba.toHex().toUpper();
    msgBox.setText(_text);
    //msgBox.exec();

    QString _filter = ui->filterTextBox->text();
    auto _id = CanHelper::IdToArray(_filter);
    _text = _id.toHex().toUpper();
    msgBox.setText(_text);
    msgBox.exec();
}


void MainWindow::on_startButton_clicked()
{
    ui->sendGroupBox->setEnabled(true);
}
