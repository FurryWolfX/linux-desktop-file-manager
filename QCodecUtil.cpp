#include "QCodecUtil.h"
#include <QTextCodec>

QCodecUtil::QCodecUtil()
{

}

/**
 * @brief 自动判断GBK，返回Unicode
 * @param ba
 * @return
 */
QString QCodecUtil::getCorrectUnicode(const QByteArray &ba)
{
    QTextCodec::ConverterState state;
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString text = codec->toUnicode(ba.constData(), ba.size(), &state);
    if (state.invalidChars > 0) {
        text = QTextCodec::codecForName("GBK")->toUnicode(ba);
    } else {
        text = ba;
    }
    return text;
}
