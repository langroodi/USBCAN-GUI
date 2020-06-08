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

QByteArray CanHelper::IdToArray(QString id)
{
    QByteArray _result = HexToArray(id);
    std::reverse(_result.begin(), _result.end());

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

QByteArray CanHelper::GetConfigPacket(
        unsigned char speed, unsigned char frame, int filter, int mask, unsigned char mode)
{
    QByteArray _result;
    _result.resize(CONFIG_PACKET_LENGTH);

    const unsigned char CONFIG_TYPE = 0x12;
    const unsigned char CONFIG_RESERVED = 0x01;
    const unsigned char CONFIG_ZERO = 0x00;

    int pointer = 0;
    // Header
    _result[pointer++] = PACKET_HEADER_MSB;
    _result[pointer++] = PACKET_HEADER_LSB;
    _result[pointer++] = CONFIG_TYPE;

    _result[pointer++] = speed;
    _result[pointer++] = frame;

    // Filter
    _result[pointer++] = CONFIG_TYPE;
    _result[pointer++] = CONFIG_TYPE;
    _result[pointer++] = CONFIG_TYPE;
    _result[pointer++] = CONFIG_TYPE;

    // Mask
    _result[pointer++] = CONFIG_TYPE;
    _result[pointer++] = CONFIG_TYPE;
    _result[pointer++] = CONFIG_TYPE;
    _result[pointer++] = CONFIG_TYPE;

    _result[pointer++] = mode;
    _result[pointer++] = CONFIG_RESERVED;
    _result[pointer++] = CONFIG_ZERO;
    _result[pointer++] = CONFIG_ZERO;
    _result[pointer++] = CONFIG_ZERO;
    _result[pointer++] = PACKET_RESERVED_BYTE;

    // CRC
    unsigned char _crc = GetChecksum(_result, PACKET_CRC_OFFSET);
    _result[pointer++] = _crc;

    return _result;
}
