#include "wordcount.h"

bool isSpliter(char x)
{
    //判断某字符能不能分割两个单词
    return  !(x == '_'
            || (x >= '0' && x <= '9')
            || (x >= 'a' && x <= 'z')
            || (x >= 'A' && x <= 'Z'));
}

int splitWord(const char *str, int len){
    bool flg = 0;
    int cnt = 0;
    int i = 0;
    while(i < len)
    {
        if(isSpliter(str[i]))
        {
            if(flg == 1)
                flg = 0;

        }else{
            if(flg == 0)//出现一个新单词,cnt+1
                cnt++, flg = 1;
        }
        ++i;
    }
    return cnt;
}

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
        QString tmp = in.readLine();
        const char *Ctmp = tmp.toStdString().c_str();
        cnt += splitWord(Ctmp, tmp.length());
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
