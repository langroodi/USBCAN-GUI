#ifndef CANHELPER_H
#define CANHELPER_H

#include <QByteArray>
#include <QString>

class CanHelper
{
public:
    CanHelper();
    static QByteArray HexToArray(QString hexString);
    static unsigned char GetChecksum(QByteArray array, int offset = 0);
};

#endif // CANHELPER_H
