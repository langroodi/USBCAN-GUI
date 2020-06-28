/*!
 *  \brief     CAN Communication Helper Header File
 *  \author    Armin K. Langroodi
 *  \version   1.0
 *  \date      2020
 *  \copyright GNU Public License.
 */

#ifndef CANHELPER_H
#define CANHELPER_H

//! \include Algorithm
#include <algorithm>
//! \include Qt Byte Array
#include <QByteArray>
//! \include Qt String
#include <QString>

//! \def Packet Header MSB
#define PACKET_HEADER_MSB 0xAA
//! \def Packet Header LSB
#define PACKET_HEADER_LSB 0x55
//! \def Packet Reserved Byte
#define PACKET_RESERVED_ZERO 0x00
//! \def Packet CRC Byte Offset
#define PACKET_CRC_OFFSET 2
//! \def Standard CAN ID Frame Size
#define STANDARD_ID_SIZE 2
//! \def EXtended CAN ID Frame Size
#define EXTENDED_ID_SIZE 4

//! \class CAN Communication Helper
class CanHelper
{
public:
    static QByteArray HexToArray(const QString &hexString /*!< [in] Hexadecimal String */); //!< Convert Hex String to Byte Array
    static QByteArray IdToArray(const QString &id /*!< [in] CAN ID String */); //!< Convert CAN ID String to Byte Array
    static QByteArray IdToArray(
            const unsigned int &id /*!< [in] CAN ID */,
            const bool &isExtended /*!< [in] Is the ID Extended or Standard */,
            const bool &bigEndian /*!< [in] Is the ID Big Endian or Little Endian */); //!< Convert CAN ID String to Byte Array
    static unsigned int ArrayToId(
            const QByteArray &idArray /*!< [in] CAN ID Byte Array */,
            const bool &isExtended /*!< [in] Is the ID Extended or Standard */); //!< Convert Byte Array to CAN ID
    static QByteArray ArrayToData(
            const QByteArray &array /*!< [in] Serialized CAN Packet Byte Array */,
            const bool &isExtended /*!< [in] Is the CAN Packet Extended or Standard */); //!< Convert Byte Array to Data Frame
    static unsigned char GetChecksum(
            QByteArray &array /*!< [in] Byte Array */,
            int offset = 0 /*!< [in] Offset */); //!< Compute Checksum
    static QByteArray GetConfigPacket(
            const unsigned char &speed /*!< [in] CAN Bus Speed */,
            const unsigned char &frame /*!< [in] CAN Frame Extended or Standard */,
            const QByteArray &filter /*!< [in] CAN ID Filter */,
            const QByteArray &mask /*!< [in] CAN ID Filtering Mask */,
            const unsigned char &mode /*!< [in] USB Analyzer Operation Mode */); //!< Generate USB Analyzer Config Packet
    static QString GetSplittedHex(const QString &hexString /*!< [in] Hexadecimal String */); //!< Get Hex String with Space Padding
};

#endif // CANHELPER_H
