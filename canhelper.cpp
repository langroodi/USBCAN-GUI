#include "canhelper.h"

CanHelper::CanHelper()
{

}

QByteArray CanHelper::HexToArray(QString hexString)
{
    QByteArray _hexArray = hexString.toUtf8();
    QByteArray _result = QByteArray::fromHex(_hexArray);

    return _result;
}

unsigned char CanHelper::GetChecksum(QByteArray array, int offset)
{
    int sum = 0;

    for (int i = offset; i < array.length(); i++)
    {
        sum += array[i];
    }

    unsigned char _result = (unsigned char)sum;
    return _result;
}
