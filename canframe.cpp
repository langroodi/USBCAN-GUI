//! \include CAN Frame Header
#include "canframe.h"

CanFrame::CanFrame(
        const bool isExtended /*!< [in] Is extended or standard */,
        const bool isRtr /*!< [in] Is RTR or not */,
        const unsigned int id /*!< [in] Message ID */,
        const QByteArray data /*!< [in] Data frame */)
{
    this->isExtended = isExtended;
    this->isRtr = isRtr;
    this->id = id;
    this->dlc = (unsigned char)data.count();
    this->data = data;
} //!< Constructor

bool CanFrame::IsExtended()
{
    return isExtended;
} //!< Is Extended
bool CanFrame::IsRtr()
{
    return isRtr;
} //!< Is Remote Transmission Request (RTR)

unsigned int CanFrame::Id()
{
    return id;
} //!< Message ID

unsigned char CanFrame::Dlc()
{
    return dlc;
} //< Data Length Code (DLC)

QByteArray CanFrame::Data()
{
    return data;
} //!< Data Frame

QByteArray CanFrame::Serialize()
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
    QByteArray _idArray = CanHelper::IdToArray(id, isExtended);
    _result.append(_idArray);

    // Data
    _result.append(data);

    // Trailer
    _result.append(MESSAGE_TRAILER_BYTE);

    return _result;
} //!< Serialize the CAN Frame instance

CanFrame CanFrame::Deserialize(
        QByteArray array /*!< [in] Message Array */)
{
    if ((array[0] == MESSAGE_HEADER_BYTE) &&
            ((array[1] & MESSAGE_TYPE_BYTE) == MESSAGE_TYPE_BYTE) &&
            (array[array.count() - 1] == MESSAGE_TRAILER_BYTE))
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
} //!< Deserialize message array
