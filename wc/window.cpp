#include "window.h"
#include "ui_window.h"
#include "wordcount.h"

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
}

Window::~Window()
{
    delete ui;
}


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
