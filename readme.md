## Github项目地址

https://github.com/zzidun-pavo/WordCounter

## 预计耗费的时间&实际耗费的时间

| PSP                                     | Personal Software Process Stages        | 预估耗时（分钟） | 实际耗时（分钟） |
| --------------------------------------- | --------------------------------------- | ---------------- | ---------------- |
| Planning                                | 计划                                    | 10               | 13               |
| · Estimate                              | · 估计这个任务需要多少时间              | 10               | 13               |
| Development                             | 开发                                    |                  |                  |
| · Analysis                              | · 需求分析 (包括学习新技术)             | 30               | 40               |
| · Design Spec                           | · 生成设计文档                          | 30               | 30               |
| · Design Review                         | · 设计复审 (和同事审核设计文档)         | 30               | 10               |
| · Coding Standard                       | · 代码规范 (为目前的开发制定合适的规范) | 30               | 15               |
| · Design                                | · 具体设计                              | 50               | 20               |
| · Coding                                | · 具体编码                              | 200              | 120              |
| · Code Review                           | · 代码复审                              | 100              | 20               |
| · Test                                  | · 测试（自我测试，修改代码，提交修改）  | 60               | 30               |
| Reporting                               | 报告                                    |                  | 37               |
| · Test Report                           | · 测试报告                              | 40               | 20               |
| · Size Measurement                      | · 计算工作量                            | 20               | 5                |
| · Postmortem & Process Improvement Plan | · 事后总结, 并提出过程改进计划          | 30               | 12               |
| 合计                                    |                                         |                  |                  |

## 解题思路

> wc.exe 是一个常见的工具，它能统计文本文件的字符数、单词数和行数。这个项目要求写一个命令行程序，模仿已有wc.exe 的功能，并加以扩充，给出某程序设计语言源文件的字符数、单词数和行数。
>
> 实现一个统计程序，它能正确统计程序文件中的字符数、单词数、行数，以及还具备其他扩展功能，并能够快速地处理多个文件。
> 具体功能要求：
>
> 实现一个统计程序，它能正确统计程序文件中的字符数、单词数、行数，以及还具备其他扩展功能，并能够快速地处理多个文件。
>
> **空行：**本行全部是空格或格式控制字符，如果包括代码，则只有不超过一个可显示的字符，例如“{”。
>
> **代码行：**本行包括多于一个字符的代码。
>
> **注释行：**本行不是代码行，并且本行包括注释。一个有趣的例子是有些程序员会在单字符后面加注释：



程序处理用户需求的模式为：

```shell
wc.exe [parameter] [file_name]
```

| 功能列表 | 功能                                                         |
| -------- | ------------------------------------------------------------ |
| -c       | 返回文件的字符数                                             |
| -w       | 返回文件的词的数目                                           |
| -l       | 返回文件的行数                                               |
| -s       | 递归处理目录下符合条件的文件                                 |
| -a       | 返回更复杂的数据（代码行 / 空行 / 注释行）                   |
| -x       | 这个参数单独使用。如果命令行有这个参数，则程序会显示图形界面，用户可以通过界面选取单个文件，程序就会显示文件的字符数、行数等全部统计信息。 |

统计字符数和行数的操作,可以使用`readLine()`之类的行数来实现,非常简单.

统计单词数的操作,比较麻烦.

首先需要考虑什么样的文本算"一个单词",我这样定义:

- 一个变量名(如a,b,c等)
- 一个操作数,运算符不算(如a=b+c含有三个单词)
- 一个函数名(如main,printf等)
- 一个修饰词(如void,static等)
- 一个关键字(如if,else,return等)

显然,不会有横跨多行的一个单词,所以我决定每次读取一行,编写一个函数,用来判断一些标志的能隔开两个单词的符号(如空格,括号,运算符),以判断到底有多少个单词.

图形界面则使用qt.

递归查找,分析注释等等功能暂时先搁置.

## 设计实现过程

![](https://img2020.cnblogs.com/blog/1597450/202003/1597450-20200320140715912-754498758.jpg)

## 代码说明

- main函数

根据输入的参数,来确定应该执行的操作

```c++
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Window w;//图形界面

    QStringList arguments = QApplication::arguments();
    if(arguments.count() < 2)
    {
        //没有输入参数
        qDebug() << QString("输入参数有误").toUtf8().data() << endl;
    }else if(arguments.at(1).compare("-x") == 0){
        //参数只有一个-x
        w.show();
        return a.exec();
    }else if(arguments.count() < 3){
        //没有输入文件名
        qDebug() << QString("没有输入文件或者参数有误").toUtf8().data() << endl;
    }else if(arguments.at(1).compare("-c") == 0){
        //计算字符数
        qDebug() << countChar(arguments.at(2)).toUtf8().data() << endl;
    }else if(arguments.at(1).compare("-w") == 0){
        //计算单词数
        qDebug() << countWord(arguments.at(2)).toUtf8().data() << endl;
    }else if(arguments.at(1).compare("-l") == 0){
        //计算行数
        qDebug() << countLine(arguments.at(2)).toUtf8().data() << endl;
    }

    return 0;
}
```

- countChar函数

逐行读取,统计每一行的字符数

```C++
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
```

- countWord函数

统计单词数,先读取每一行,然后在每一行中找出所有非英语或者数字或者下划线的字符.

这些字符一般都是两个单词的分割点.

```c++
bool isSpliter(char x)
{
    //判断某字符能不能分割两个单词
    return  !(x == '_'
            || (x >= '0' && x <= '9')
            || (x >= 'a' && x <= 'z')
            || (x >= 'A' && x <= 'Z'));
}

int splitWord(char *str, int len){
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
```

- countLine函数

非常简单,就是每次读取一行,看能读取多少次

```C++
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
```

- 图形界面的设置

有两个控件,一个是下拉框,用来选择一种操作,每次下拉框内容发生变化的时候,改变一下变量`op`的值.

另一个是按钮,按下之后调用文件对话跨,让用户选择一个文件来进行统计,操作的类型由`op`的值来定.

```C++
void Window::on_buttonSelect_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, "打开", "../");
    if(file.isEmpty() == false)
    {
        switch(op)
        {
        case 1: QMessageBox::about(this, "提示", countChar(file));    break;
        case 2: QMessageBox::about(this, "提示", countWord(file));    break;
        case 3: QMessageBox::about(this, "提示", countLine(file));    break;
        default: QMessageBox::about(this, "提示", "你还没有选择要执行的操作"); break;
        }
    }
}

void Window::on_comboBox_currentIndexChanged(int index)
{
    op = ui->comboBox->currentIndex();
}

```



## 测试运行

对于text文件夹下的各个文件的操作,结果如下.

- text1

![](https://img2020.cnblogs.com/blog/1597450/202003/1597450-20200324221022060-211601890.jpg)



- text2

![](https://img2020.cnblogs.com/blog/1597450/202003/1597450-20200324221028568-1568027695.jpg)



- text3

![](https://img2020.cnblogs.com/blog/1597450/202003/1597450-20200324221034498-1996299924.jpg)



- text4

![](https://img2020.cnblogs.com/blog/1597450/202003/1597450-20200324221041608-456969268.jpg)



- text5
![](https://img2020.cnblogs.com/blog/1597450/202003/1597450-20200324221046982-1826622459.jpg)




- text6


![](https://img2020.cnblogs.com/blog/1597450/202003/1597450-20200324221051970-1315646710.jpg)


## 项目小结

我觉得我这次做的虎头蛇尾.

原本觉得是一个很水的项目,但是出现的问题也很多.

一开始写的程序很简单粗暴,结果运行时统计出来的结果非常诡异,才发现自己的想法太想当然.

而且很多操作都以前学习的时候都只是随便看一下,心里觉得"这么简单,我肯定记住了"

然后在用到的时候才发现其实上面都不记得.



## 记录自己的学习进度条(每周追加)

| 第N周 | 新增代码(行) | 累计代码(行) | 本周学习耗时(小时) | 累计学习耗时(小时) | 重要成长                |
| ----- | ------------ | ------------ | ------------------ | ------------------ | ----------------------- |
| 1     | 0            | 0            | 2                  | 2                  | 学习了git的用法         |
| 2     | 170          | 170          | 4                  | 6                  | 完成了基本功能          |
| 3     | 50           | 220          | 3                  | 9                  | 修改了部分功能,并且记录 |

