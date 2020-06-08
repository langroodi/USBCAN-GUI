#ifndef CANFRAME_H
#define CANFRAME_H

//! \include Qt Byte Array
#include <QByteArray>

//! \include CAN Helper
#include "canhelper.h"

//! \def Message Frame Header Byte
#define MESSAGE_HEADER_BYTE 0xAA
//! \def Message Frame Type Byte
#define MESSAGE_TYPE_BYTE 0xC0
//! \def Message Frame Trailer Byte
#define MESSAGE_TRAILER_BYTE 0x55
//! \def Extended Mesage Byte
#define EXTENDED_MESSAGE_BYTE 0x20
//! \def Remote Message Byte
#define REMOTE_MESSAGE_BYTE 0x10
//! \def Standard Message Minimum Size
#define STANDARD_MESSAGE_SIZE 5
//! \def Extended Message Minimum Size
#define EXTENDED_MESSAGE_SIZE 7

//! \class CAN Message Frame
class CanFrame
{
//! \private
private:
    bool isExtended; //!< Is Extended
    bool isRtr; //!< Is RTR
    int dlc; //!< DLC
    QByteArray data; //!< Data Frame
    int frameSize; //!< Message Frame Size

//! \public
public:
    CanFrame(
            const bool isExtended /*!< [in] Is extended or standard */,
            const bool isRtr /*!< [in] Is RTR or not */,
            const QByteArray data /*!< [in] Data frame */); //!< Constructor
    bool IsExtended(); //!< Is Extended
    bool IsRtr(); //!< Is Remote Transmission Request (RTR)
    int Dlc(); //< Data Length Code (DLC)
    QByteArray Data(); //!< Data Frame
    QByteArray Serialize(); //!< Serialize the CAN Frame instance
};

#endif // CANFRAME_H
