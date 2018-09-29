#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QString>
#include <QJsonObject>

class QFileUtil
{
public:
    QFileUtil();
    static QString readTextFile(const QString filePath);
    static int writeTextFile(const QString filePath, const QString str);
    static QStringList getFileNames(const QString &path);
    static QJsonObject readJsonFile(const QString filePath);
};

#endif // FILEUTIL_H
