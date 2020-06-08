//! \include CAN Frame Header
#include "canframe.h"

CanFrame::CanFrame(
        const bool isExtended /*!< [in] Is extended or standard */,
        const bool isRtr /*!< [in] Is RTR or not */,
        const QByteArray data /*!< [in] Data frame */)
{
    this->isExtended = isExtended;
    this->isRtr = isRtr;
    this->data = data;

    dlc = data.count();

    if (isExtended)
    {
        frameSize = EXTENDED_MESSAGE_SIZE + dlc;
    }
    else
    {
        frameSize = STANDARD_MESSAGE_SIZE + dlc;
    }
} //!< Constructor

bool CanFrame::IsExtended()
{
    return isExtended;
} //!< Is Extended
bool CanFrame::IsRtr()
{
    return isRtr;
} //!< Is Remote Transmission Request (RTR)

int CanFrame::Dlc()
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
    _result.resize(frameSize);

    int _pointer = 0;
    // Header
    _result[_pointer++] = MESSAGE_HEADER_BYTE;

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
    unsigned char _dlcByte = (unsigned char)dlc;
    _type |= dlc;
    _result[_pointer++] = _type;

    //! \todo ADD ID PLEASE

    _result[_pointer++] = MESSAGE_HEADER_BYTE;
    _result[_pointer++] = MESSAGE_HEADER_BYTE;

} //!< Serialize the CAN Frame instance
