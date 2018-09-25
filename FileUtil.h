#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QString>

class FileUtil
{
public:
    FileUtil();
    static QString readTextFile(QString filePath);
    static int writeTextFile(QString filePath, QString str);
    static QStringList getFileNames(const QString &path);
};

#endif // FILEUTIL_H
