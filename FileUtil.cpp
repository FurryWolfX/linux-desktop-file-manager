#include <QDebug>
#include <QFile>
#include <QDir>
#include <QByteArray>

#include "FileUtil.h"

FileUtil::FileUtil()
{

}

/**
 * @brief 读文本文件
 * @param filePath
 * @return
 */
QString FileUtil::readTextFile(QString filePath) {
    QFile file(filePath);
    QString displayString;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!file.atEnd())
        {
            QByteArray line = file.readLine();
            QString str(line);
            qDebug() << str;
            displayString += str;
        }
        file.close();
    } else {
        displayString = "ERROR: no file found!";
    }
    return displayString;
}

/**
 * @brief 写文本文件，不存在则创建
 * @param filePath
 * @param str
 * @return
 */
int FileUtil::writeTextFile(QString filePath, QString str) {
    QFile f(filePath);
    if(!f.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "open file failed";
        return -1;
    }
    else
    {
        QByteArray content = str.toUtf8();
        f.write(content);
        f.close();
        qDebug() << "write file success";
        return 0;
    }
}

/**
 * @brief 获取当前目录下的所有文件名
 * @param path
 * @return
 */
QStringList FileUtil::getFileNames(const QString &path)
{
    QDir dir(path);
    QStringList nameFilters;
//    nameFilters << "*.jpg" << "*.png";
    nameFilters << "*.desktop" << "*.txt";
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    return files;
}
