#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();

private slots:
    void on_buttonSelect_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::Window *ui;

    int op;
};

#endif // WINDOW_H
