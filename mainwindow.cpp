#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    updateSerialPorts();
    serialHelper =
            new SerialHelper(
                &serialPort, ui->messageTreeWidget, readReadyCallback);
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
    delete serialHelper;
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
    bool _isExtended = (ui->typeComboBox->currentIndex() == 1);
    bool _isRtr = ui->remoteCheckBox->isChecked();
    unsigned int _id = ui->idTextBox->text().toUInt(nullptr, 16);
    QByteArray _data = CanHelper::HexToArray(ui->dataTextBox->text());

    CanFrame _frame(_isExtended, _isRtr, _id, _data);
    QByteArray _serializedFrame =
            _frame.Serialize(ui->constantCheckBox->isChecked());

    serialHelper->Write(_serializedFrame);

    addMessage(ui->messageTreeWidget, _frame, false);
}

void MainWindow::on_startButton_clicked()
{
    if (serialPort.isOpen()) {
        serialPort.close();
        ui->startButton->setText("Start");
        ui->sendGroupBox->setEnabled(false);
        ui->canGroupBox->setEnabled(true);
        ui->serialGroupBox->setEnabled(true);
    }
    else {
        serialPort.setPortName(ui->comboBox->currentText());
        serialPort.setParity(QSerialPort::NoParity);
        serialPort.setDataBits(QSerialPort::Data8);
        serialPort.setStopBits(QSerialPort::OneStop);
        serialPort.setFlowControl(QSerialPort::NoFlowControl);
        const int _baudRate = (ui->rateTextBox->text().toInt());
        serialPort.setBaudRate(_baudRate);

        bool _succeed = serialPort.open(QIODevice::ReadWrite);

        if (_succeed)
        {
            unsigned char _speed =
                    12 - (unsigned char)(ui->speedComboBox->currentIndex());
            unsigned char _frame =
                    (unsigned char)(ui->typeComboBox->currentIndex()) + 1;
            unsigned char _mode =
                    (unsigned char)(ui->modeComboBox->currentIndex());
            QByteArray _filter =
                    CanHelper::HexToArray(ui->filterTextBox->text());
            QByteArray _mask =
                    CanHelper::HexToArray(ui->maskTextBox->text());

            QByteArray _configPack =
                    CanHelper::GetConfigPacket(
                        _speed, _frame, _filter, _mask, _mode);

            serialHelper->Write(_configPack);

            ui->startButton->setText("Stop");
            ui->sendGroupBox->setEnabled(true);
            ui->canGroupBox->setEnabled(false);
            ui->serialGroupBox->setEnabled(false);
        }
        else
        {
            QMessageBox _msgBox;
            _msgBox.setText(serialPort.errorString());
            _msgBox.exec();
        }
    }
}

void MainWindow::addMessage(QTreeWidget *treeWidget, const CanFrame &canFrame, const bool &isIncoming)
{
    QTreeWidgetItem *_item = new QTreeWidgetItem(treeWidget);
    int _index = 0;

    //! \remark Timestamp
    QString _time = QTime::currentTime().toString("hh:mm:ss");
    _item->setText(_index++, _time);

    //! \remark Direction
    QString _direction = isIncoming ? "Incoming" : "Outgoing";
    _item->setText(_index++, _direction);

    //! \remark Type
    QString _type = canFrame.IsExtended() ? "Yes" : "No";
    _item->setText(_index++, _type);

    //! \remark ID
    unsigned int _id = canFrame.Id();
    QString _idStr = QString::number(_id);
    _item->setText(_index++, _idStr);

    //! \remark RTR
    QString _rtr = canFrame.IsRtr() ? "Yes" : "No";
    _item->setText(_index++, _rtr);

    //! \remark DLC
    QString _dlc = QString::number(canFrame.Dlc());
    _item->setText(_index++, _dlc);

    //! \remark Data
    QString _data = canFrame.Data().toHex().toUpper();
    _data = CanHelper::GetSplittedHex(_data);
    _item->setText(_index++, _data);

    treeWidget->addTopLevelItem(_item);
}

void MainWindow::readReadyCallback(QTreeWidget *treeWidget, const QByteArray &data)
{
    CanFrame _frame;
    bool _succeed = CanFrame::TryDeserialize(data, _frame);

    if (_succeed)
    {
        addMessage(treeWidget, _frame, true);
    }
}
