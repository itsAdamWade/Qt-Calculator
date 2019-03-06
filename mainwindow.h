#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool divTrigger = false;
    bool multTrigger = false;
    bool addTrigger = false;
    bool subTrigger = false;
    bool caretTrigger = false;
    bool decimalTrigger = false;
    double calcNum = 0.0;

private:
    Ui::MainWindow *ui;

private slots:
    void num_pressed();
    void math_pressed();
    void equal_pressed();
    void change_num_sign();
    void clear_pressed();
    void back_pressed();
};

#endif // MAINWINDOW_H
