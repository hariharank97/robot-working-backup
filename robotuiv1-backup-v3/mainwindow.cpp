#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <QByteArray>

#define PORT "/dev/lp0"

//#include <QtPrintSupport/QPrinter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_6->setToolTip("<b>COMMAND:</b> Nest<br><b>SYNTAX:</b> NT<br><b>FUNCTION:</b> Returns Robot to mechanical origin");
    ui->pushButton_7->setToolTip("<b>COMMAND:</b> Gripper Close<br><b>SYNTAX:</b> GC<br><b>FUNCTION:</b> Closes Hand Grip");
    ui->pushButton_8->setToolTip("<b>COMMAND:</b> Gripper Open<br><b>SYNTAX:</b> GO<br><b>FUNCTION:</b> Opens Hand Grip");
    ui->pushButton_10->setToolTip("<b>COMMAND:</b> Origin<br><b>SYNTAX:</b> OG<br><b>FUNCTION:</b> Moves robot to the reference position in the cartesian co-ordinate system");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_Program_triggered()
{
    file_path_ = "";
    ui->textEdit->setText("");
}

void MainWindow::on_actionOpen_Program_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Open the file to execute");
    QFile file(file_name);
    file_path_ = file_name;
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
       QMessageBox::warning(this,"ALERT","No Files were opened!");
       return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionSave_Program_triggered()
{

}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionSave_Program_2_triggered()
{
    QFile file(file_path_);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,"ALERT!","Do 'Save As' First!");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow::on_actionSave_As_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this,"Save File as...");
      QFile file(file_name);
      file_path_ = file_name;
      if(!file.open(QFile::WriteOnly | QFile::Text))
      {
          QMessageBox::warning(this,"ALERT!","No Files were Saved!");
          return;
      }
      QTextStream out(&file);
      QString text = ui->textEdit->toPlainText();
      out << text;
      file.flush();
      file.close();
}

void MainWindow::on_actionAbout_this_Software_triggered()
{
    qDebug() << "About Button Pressed\n";
    QString about_text;
    about_text  = "Robot Control Software developed using 'Qt' GUI Development Tool and is a part of M.Tech Research Project titled 'Design and Development of Industrial IoT Gateway for Robotic Arm Control'\n\n";
    about_text += "Guided by Mr Rajesh M and Done by Hariharan K, M.Tech EDT,\n";
    about_text += "NIELIT-Calicut, Batch : 2018-2020";
    QMessageBox::about(this,"About this control software!",about_text);
}

void MainWindow::on_pushButton_5_clicked()              //SINGLE-SHOT: execute commands one-by-one continuously from textbox
{

    QString text = ui->textEdit->toPlainText();
    QTextStream str(&text, QIODevice::ReadOnly);
    QString line;
    for (int n = 0; !str.atEnd(); ++n)
        {
         //sleep(2);
         int fd;
         long ret;
         line = str.readLine();
         qDebug() << "Current line:" << line;
         line.append("\n");
         QByteArray ba = line.toLocal8Bit();
         fd = open(PORT, O_RDWR);
         ret = write(fd, ba.data(), ba.length());
         ::close(fd);
        }
    qDebug() << "This is outside of 'for' loop";
}


void MainWindow::on_pushButton_6_clicked()              //home position
{
    //system("echo NT >> /dev/lp0");

    int fd;
    char cmd[]="NT\n";
    long ret;
    fd = open(PORT, O_RDWR);
    qDebug() << "fd val for NT =\t" << fd;
    ret = write(fd,cmd,sizeof(cmd));
    qDebug() << "ret value for NT =" << ret;
    ::close(fd);
}

void MainWindow::on_pushButton_7_clicked()              //close the gripper
{
    //system("echo GC >> /dev/lp0");

    int fd;
    char cmd[]="GC\n";
    long ret;
    fd = open(PORT, O_RDWR);
    qDebug() << "fd value for GC =  \t" << fd;
    ret = write(fd,cmd,sizeof(cmd));
    qDebug() << "ret value for GO =" << ret;
    ::close(fd);
}


void MainWindow::on_pushButton_8_clicked()              //open the gripper
{
    //system("echo GO >> /dev/lp0");

    int fd;
    char cmd[]="GO\n";
    long ret;
    fd = open(PORT, O_RDWR);
    qDebug() << "fd val for GO =\t" << fd;
    ret = write(fd,cmd,sizeof(cmd));
    qDebug() << "ret value for GO =" << ret;
    ::close(fd);
}

void MainWindow::on_pushButton_10_clicked()            //Go to Origin
{
        int fd;
        char cmd[]="OG\n";
        long ret;
        fd = open(PORT, O_RDWR);
        qDebug() << "fd val for OG =\t" << fd;
        ret = write(fd,cmd,sizeof(cmd));
        qDebug() << "ret value for OG =" << ret;
        ::close(fd);
}
