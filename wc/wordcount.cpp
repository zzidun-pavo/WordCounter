#include "wordcount.h"


QString countChar(QString f)
{
    QFile file(f);
    if(!file.open(QFile::ReadOnly | QFile::Text))
        return "文件打开失败";

    int cnt = 0;
    QTextStream in(&file);
    QString tmp;

    while(in.atEnd() == 0)
    {
        tmp = in.readLine();
        cnt += tmp.length();
    }

    file.close();

    return "这个文件总共有"+QString::number(cnt, 10)+"个字符";
}

QString countWord(QString f)
{
    QFile file(f);
    if(!file.open(QFile::ReadOnly | QFile::Text))
        return "文件打开失败";

    int cnt = 0;
    QTextStream in(&file);
    QString tmp;

    while(in.atEnd() == 0)
    {
        tmp = in.readLine();
        cnt += tmp.split(" ").count();
    }

    file.close();
    return "这个文件共有"+QString::number(cnt, 10)+"个单词";
}

QString countLine(QString f)
{
    QFile file(f);
    if(!file.open(QFile::ReadOnly | QFile::Text))
            return "文件打开失败";

    int cnt = 0;
    QTextStream in(&file);
    QString tmp;

    while(in.atEnd() == 0)
    {
        tmp = in.readLine();
        cnt ++;
    }

    file.close();

    return "这个文件共有"+QString::number(cnt, 10)+"行";
}
