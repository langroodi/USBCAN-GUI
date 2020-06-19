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
//! \def Data Type Packet
#define DATA_TYPE_BYTE 0x01
//! \def Standard Frame Byte
#define STANDARD_FRMAE_BYTE 0x01
//! \def Extended Frame Byte
#define EXTENDED_FRAME_BYTE 0x02
//! \def Data Frame Byte
#define DATA_FRAME_BYTE 0x01
//! \def Remote Frame Byte
#define REMOTE_FRAME_BYTE 0x02

//! \class CAN Message Frame
class CanFrame
{
    //! \private
private:
    bool isExtended; //!< Is Extended
    bool isRtr; //!< Is RTR
    unsigned char dlc; //!< DLC
    unsigned int id; //!< Message ID
    QByteArray data; //!< Data Frame
    QByteArray serializeVarLength(); //!< Variable Length Object Serialization
    QByteArray serializeConstLength(); //!< Constant Length Object Serialization

    //! \public
public:
    CanFrame(
            const bool isExtended /*!< [in] Is extended or standard */,
            const bool isRtr /*!< [in] Is RTR or not */,
            const unsigned int id /*!< [in] Message ID */,
            const QByteArray data /*!< [in] Data frame */); //!< Constructor
    bool IsExtended(); //!< Get Is Extended
    bool IsRtr(); //!< Get Is Remote Transmission Request (RTR)
    unsigned char Dlc(); //!< Get Data Length Code (DLC)
    unsigned int Id(); //!< Get Message ID
    QByteArray Data(); //!< Get Data Frame
    QByteArray Serialize(const bool constantLength); //!< Serialize the CAN Frame instance
    static CanFrame Deserialize(QByteArray array /*!< [in] Message Array */); //!< Deserialize message array
};

#endif // CANFRAME_H
