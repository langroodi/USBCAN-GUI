#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>

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
