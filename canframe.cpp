/*!
 *  \brief     CAN Frame Source File
 *  \author    Armin K. Langroodi
 *  \version   1.0
 *  \date      2020
 *  \copyright GNU Public License.
 */

//! \include CAN Frame Header
#include "canframe.h"

CanFrame::CanFrame(
        const bool isExtended,
        const bool isRtr,
        const unsigned int id,
        const QByteArray data)
{
    this->isExtended = isExtended;
    this->isRtr = isRtr;
    this->id = id;
    this->dlc = (unsigned char)data.count();
    this->data = data;
}

bool CanFrame::IsExtended() const
{
    return isExtended;
}

bool CanFrame::IsRtr() const
{
    return isRtr;
}

unsigned int CanFrame::Id() const
{
    return id;
}

unsigned char CanFrame::Dlc() const
{
    return dlc;
}

QByteArray CanFrame::Data() const
{
    return data;
}

QByteArray CanFrame::Serialize(const bool &constantLength)
{
    if (constantLength)
    {
        return serializeConstLength();
    }
    else
    {
        return serializeVarLength();
    }
}

QByteArray CanFrame::serializeVarLength()
{
    QByteArray _result;

    // Header
    _result.append(MESSAGE_HEADER_BYTE);

    // Type
    unsigned char _type = MESSAGE_TYPE_BYTE;
    if (isExtended)
    {
        _type |= EXTENDED_MESSAGE_BYTE;
    }
    if (isRtr)
    {
        _type |= REMOTE_MESSAGE_BYTE;
    }

    _type |= dlc;
    _result.append(_type);

    // ID
    QByteArray _idArray = CanHelper::IdToArray(id, isExtended, false);
    _result.append(_idArray);

    // Data
    _result.append(data);

    // Trailer
    _result.append(MESSAGE_TRAILER_BYTE);

    return _result;
}

QByteArray CanFrame::serializeConstLength()
{
    QByteArray _result;

    // Header
    _result.append(PACKET_HEADER_MSB);
    _result.append(PACKET_HEADER_LSB);
    _result.append(DATA_FRAME_BYTE);

    // Frame Type
    if (isExtended)
    {
        _result.append(EXTENDED_FRAME_BYTE);
    }
    else
    {
        _result.append(STANDARD_FRMAE_BYTE);
    }

    // Frame Format
    if (isRtr)
    {
        _result.append(REMOTE_FRAME_BYTE);
    }
    else
    {
        _result.append(DATA_FRAME_BYTE);
    }

    // ID
    QByteArray _idArray = CanHelper::IdToArray(id, isExtended, true);
    _result.append(_idArray);

    // DLC
    _result.append(dlc);

    // Data
    _result.append(data);

    // Trailer
    unsigned char _trailer = PACKET_RESERVED_ZERO;
    _result.append(_trailer);

    // CRC
    unsigned char _crc = CanHelper::GetChecksum(_result, PACKET_CRC_OFFSET);
    _result.append(_crc);

    return _result;
}

CanFrame CanFrame::Deserialize(const QByteArray &array /*!< [in] Message Array */)
{
    if ((array[MESSAGE_HEADER_OFFSET] == MESSAGE_HEADER_BYTE) &&
            ((array[MESSAGE_TYPE_OFFSET] & MESSAGE_TYPE_BYTE) == MESSAGE_TYPE_BYTE) &&
            (array[array.count() - MESSAGE_TRAILER_OFFSET] == MESSAGE_TRAILER_BYTE))
    {
        bool _isExtended =
                (array[1] & EXTENDED_MESSAGE_BYTE) == EXTENDED_MESSAGE_BYTE;
        bool _isRtr =
                (array[1] & REMOTE_MESSAGE_BYTE) == REMOTE_MESSAGE_BYTE;
        unsigned int _id = CanHelper::ArrayToId(array, _isExtended);
        QByteArray _data =  CanHelper::ArrayToData(array, _isExtended);

        CanFrame _result(_isExtended, _isRtr, _id, _data);
        return _result;
    }
    else
    {
        throw;
    }
}
