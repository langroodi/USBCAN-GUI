#ifndef CANHELPER_H
#define CANHELPER_H

#include <algorithm>
#include <QByteArray>
#include <QString>

#define CONFIG_PACKET_LENGTH 20
#define PACKET_HEADER_MSB 0xAA
#define PACKET_HEADER_LSB 0x55
#define PACKET_RESERVED_BYTE 0x00
#define PACKET_CRC_OFFSET 2

class CanHelper
{
public:
    CanHelper();
    static QByteArray HexToArray(QString hexString);
    static QByteArray IdToArray(QString id);
    static unsigned char GetChecksum(QByteArray array, int offset = 0);
    static QByteArray GetConfigPacket(unsigned char speed, unsigned char frame, int filter, int mask, unsigned char mode);
};

#endif // CANHELPER_H
