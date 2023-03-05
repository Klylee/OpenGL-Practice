#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->openGLWidget, SIGNAL(camera_Coordinate_Changed(char)), this, SLOT(onCoordinateChanged(char)));


    float x=ui->openGLWidget->cam.x;
    float y=ui->openGLWidget->cam.y;
    float z=ui->openGLWidget->cam.z;
    ui->textEdit_x->setText(QString::number(x));
    ui->textEdit_y->setText(QString::number(y));
    ui->textEdit_z->setText(QString::number(z));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->openGLWidget->stopTimer();
}


void MainWindow::on_pushButton_2_clicked()
{
     ui->openGLWidget->startTimer();
}


void MainWindow::on_textEdit_x_textChanged()
{
}

void MainWindow::onCoordinateChanged(char msg)
{
    if(msg == 'x')
    {
        float x=ui->openGLWidget->cam.x;
        ui->textEdit_x->setText(QString::number(x));
    }
    else if(msg == 'y')
    {
        float y=ui->openGLWidget->cam.y;
        ui->textEdit_y->setText(QString::number(y));
    }
    else if(msg == 'z')
    {
        float z=ui->openGLWidget->cam.z;
        ui->textEdit_z->setText(QString::number(z));
    }
}


