/*!
 *  \brief     CAN Communication Helper Source File
 *  \author    Armin K. Langroodi
 *  \version   1.0
 *  \date      2020
 *  \copyright GNU Public License.
 */

//! \include CAN Helper Header File
#include "canhelper.h"

QByteArray CanHelper::HexToArray(const QString &hexString)
{
    QByteArray _hexArray = hexString.toUtf8();
    QByteArray _result = QByteArray::fromHex(_hexArray);

    return _result;
}

QByteArray CanHelper::IdToArray(const QString &id)
{
    QByteArray _result = HexToArray(id);
    std::reverse(_result.begin(), _result.end());

    return _result;
}

QByteArray CanHelper::IdToArray(const unsigned int &id, const bool &isExtended, const bool &bigEndian)
{
    QByteArray _result;

    int _arraySize;
    if (isExtended)
    {
        _arraySize = EXTENDED_ID_SIZE;
    }
    else
    {
        _arraySize = STANDARD_ID_SIZE;
    }

    int _offset;
    int _gain;

    if (bigEndian)
    {
        _offset = (_arraySize - 1)* 8;
        _gain = -1;
    }
    else
    {
        _offset = 0;
        _gain = 1;
    }

    for (int i = 0; i < _arraySize; i++)
    {
        int _pointer = _offset + _gain * (i * 8);
        unsigned char _byte = (unsigned char)(id >> _pointer);
        _result.append(_byte);
    }

    return _result;
}

unsigned int CanHelper::ArrayToId(const QByteArray &idArray,
                                  const bool &isExtended)
{
    unsigned int _result = 0;

    int _endItr;
    if (isExtended)
    {
        _endItr = EXTENDED_ID_SIZE + PACKET_CRC_OFFSET;
    }
    else
    {
        _endItr = STANDARD_ID_SIZE + PACKET_CRC_OFFSET;
    }

    for (int i = PACKET_CRC_OFFSET; i < _endItr; i++)
    {
        int _pointer = (i - PACKET_CRC_OFFSET) * 8;
        unsigned int _decimal = (unsigned int)(idArray[i] << _pointer);
        _result |= _decimal;
    }

    return _result;
}

QByteArray CanHelper::ArrayToData(
        const QByteArray &array,
        const bool &isExtended)
{
    QByteArray _result;

    int _begin;
    if (isExtended)
    {
        _begin = EXTENDED_ID_SIZE + PACKET_CRC_OFFSET;
    }
    else
    {
        _begin = STANDARD_ID_SIZE + PACKET_CRC_OFFSET;
    }
    int  _length = array.count() - _begin - 1;

    _result = array.mid(_begin, _length);

    return _result;
}

unsigned char CanHelper::GetChecksum(QByteArray &array, int offset)
{
    int sum = 0;

    for (int i = offset; i < array.length(); i++)
    {
        sum += array[i];
    }

    unsigned char _result = (unsigned char)sum;
    return _result;
}

QByteArray CanHelper::GetConfigPacket(const unsigned char &speed,
        const unsigned char &frame,
        const QByteArray &filter,
        const QByteArray &mask,
        const unsigned char &mode)
{
    QByteArray _result;

    const unsigned char CONFIG_TYPE = 0x12;
    const unsigned char CONFIG_RESERVED = 0x01;
    const unsigned char CONFIG_ZERO = 0x00;

    // Header
    _result.append(PACKET_HEADER_MSB);
    _result.append(PACKET_HEADER_LSB);
    _result.append(CONFIG_TYPE);

    _result.append(speed);
    _result.append(frame);

    // Filter
    _result.append(filter);

    // Mask
    _result.append(mask);

    _result.append(mode);
    _result.append(CONFIG_RESERVED);
    _result.append(CONFIG_ZERO);
    _result.append(CONFIG_ZERO);
    _result.append(CONFIG_ZERO);
    _result.append(CONFIG_ZERO);

    // CRC
    unsigned char _crc = GetChecksum(_result, PACKET_CRC_OFFSET);
    _result.append(_crc);

    return _result;
}

QString CanHelper::GetSplittedHex(const QString &hexString)
{
    int _count = hexString.count();
    QString _result = hexString;

    int _offset = 0;
    for(int i = 2; i < _count; i+= 2){
        _result.insert(i + _offset++, ' ');
    }

    return _result;
}
