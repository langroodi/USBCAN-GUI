#ifndef CANHELPER_H
#define CANHELPER_H

#include <algorithm>
#include <QByteArray>
#include <QString>

#define PACKET_HEADER_MSB 0xAA
#define PACKET_HEADER_LSB 0x55
#define PACKET_CRC_OFFSET 2
#define STANDARD_ID_SIZE 2
#define EXTENDED_ID_SIZE 4

class CanHelper
{
public:
    CanHelper();
    static QByteArray HexToArray(QString hexString);
    static QByteArray IdToArray(QString id);
    static QByteArray IdToArray(unsigned int id, bool isExtended);
    static unsigned int ArrayToId(const QByteArray idArray, const bool isExtended);
    static QByteArray ArrayToData(const QByteArray array, const bool isExtended);
    static unsigned char GetChecksum(QByteArray array, int offset = 0);
    static QByteArray GetConfigPacket(unsigned char speed, unsigned char frame, QByteArray filter, QByteArray mask, unsigned char mode);
    static QString GetSplittedHex(const QString hexString);
};

#endif // CANHELPER_H
