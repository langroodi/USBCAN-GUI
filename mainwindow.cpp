#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    //msgBox.exec();

    unsigned int _sampleId = 19088743;
    auto _sampleArray = CanHelper::IdToArray(_sampleId, true);
    /*unsigned int _recoveredId = CanHelper::ArrayToId(_sampleArray, true);

    if (_sampleId == _recoveredId)
    {
        auto _sampleHex = _sampleArray.toHex().toUpper();
        QString _sampleText(_sampleHex);
        msgBox.setText(_sampleText);
        msgBox.exec();
    }*/

    CanFrame *_frame = new CanFrame(false, false, 10, ba);
    addMessage(*_frame, true);
    delete _frame;
}

void MainWindow::on_startButton_clicked()
{
    ui->sendGroupBox->setEnabled(true);
}

void MainWindow::addMessage(CanFrame canFrame, bool isIncoming)
{
    //! \todo STD Move

    QTreeWidgetItem *_item = new QTreeWidgetItem(ui->messageTreeWidget);
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

    ui->messageTreeWidget->addTopLevelItem(_item);
}
