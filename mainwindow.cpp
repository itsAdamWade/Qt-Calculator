#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcNum));

    QPushButton *numButtons[10];

    for(int i = 0; i < 10; i++)
    {
        QString butName = "pushButton_" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(num_pressed()));
    }

    connect(ui->Plus, SIGNAL(released()), this, SLOT(math_pressed()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(math_pressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(math_pressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(math_pressed()));
    connect(ui->Caret, SIGNAL(released()), this, SLOT(math_pressed()));
    connect(ui->Decimal, SIGNAL(released()), this, SLOT(math_pressed()));

    connect(ui->pushButton_Equals, SIGNAL(released()), this, SLOT(equal_pressed()));
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(change_num_sign()));
    connect(ui->Clear, SIGNAL(released()), this, SLOT(clear_pressed()));
    connect(ui->Backspace, SIGNAL(released()), this, SLOT(back_pressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::num_pressed()
{
    QPushButton *button = dynamic_cast<QPushButton *>(sender());
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    if((displayVal.toDouble() == 0.0) || (displayVal.toDouble() == 0.0))
    {
        ui->Display->setText(butVal);
    }
    else
    {
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }
}

void MainWindow::math_pressed()
{
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    caretTrigger = false;
    decimalTrigger = false;

    QString displayVal = ui->Display->text();
    calcNum = displayVal.toDouble();

    QPushButton *button = dynamic_cast<QPushButton *>(sender());
    QString butVal = button->text();

    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0)
    {
        divTrigger = true;
    }
    if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0)
    {
        multTrigger = true;
    }
    if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0)
    {
        addTrigger = true;
    }
    if(QString::compare(butVal, "-", Qt::CaseInsensitive) == 0)
    {
        subTrigger = true;
    }
    if(QString::compare(butVal, "^", Qt::CaseInsensitive) == 0)
    {
        caretTrigger = true;
    }
    if(QString::compare(butVal, ".", Qt::CaseInsensitive) == 0)
    {
        decimalTrigger = true;
    }

    ui->Display->setText("");
}

void MainWindow::equal_pressed()
{
    double solution = 0.0;

    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();

    if(addTrigger || subTrigger || multTrigger || divTrigger || caretTrigger || decimalTrigger)
    {
        if(addTrigger)
        {
            solution = calcNum + dblDisplayVal;
        }
        else if(subTrigger)
        {
            solution = calcNum - dblDisplayVal;
        }
        else if(multTrigger)
        {
            solution = calcNum * dblDisplayVal;
        }
        else if(caretTrigger)
        {
            solution = pow(calcNum, dblDisplayVal);
        }
        else if(decimalTrigger)
        {
            solution = calcNum * .1;
        }
        else
        {
            solution = calcNum / dblDisplayVal;
        }
    }
    ui->Display->setText(QString::number(solution));
}

void MainWindow::change_num_sign()
{
    QString displayVal = ui->Display->text();

    QRegExp reg("[-]?[0-9.]*");

    if(reg.exactMatch(displayVal))
    {
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;

        ui->Display->setText(QString::number(dblDisplayValSign));
    }
}

void MainWindow::clear_pressed()
{
    calcNum = 0.0;
    ui->Display->setText(QString::number(calcNum));
}

void MainWindow::back_pressed()
{
    ui->Display->backspace();
}
