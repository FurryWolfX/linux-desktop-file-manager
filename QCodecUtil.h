#ifndef CODECUTIL_H
#define CODECUTIL_H
#include <QByteArray>

class QCodecUtil
{
public:
    QCodecUtil();
    QString getCorrectUnicode(const QByteArray &ba);
};

#endif // CODECUTIL_H
