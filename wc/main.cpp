#include "window.h"
#include "wordcount.h"

#include <QApplication>
#include <QDebug>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Window w;

    QStringList arguments = QApplication::arguments();
    if(arguments.count() < 2)
    {
        qDebug() << QString("输入参数有误").toUtf8().data() << endl;
    }else if(arguments.at(1).compare("-x") == 0){
        w.show();
        return a.exec();
    }else if(arguments.count() < 3){
        qDebug() << QString("没有输入文件或者参数有误").toUtf8().data() << endl;
    }else if(arguments.at(1).compare("-c") == 0){
        qDebug() << countChar(arguments.at(2)).toUtf8().data() << endl;
    }else if(arguments.at(1).compare("-w") == 0){
        qDebug() << countWord(arguments.at(2)).toUtf8().data() << endl;
    }else if(arguments.at(1).compare("-l") == 0){
        qDebug() << countLine(arguments.at(2)).toUtf8().data() << endl;
    }

    return 0;
}
