#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
//#include <QtPrintSupport/QPrinter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

    QString about_text;
    about_text  = "Robot Control Software developed using 'Qt' GUI Development Tool and is a part of M.Tech Research Project titled 'Design and Development of Industrial IoT Gateway for Robotic Arm Control'\n\n";
    about_text += "Guided by Mr Rajesh M and Done by Hariharan K, M.Tech EDT,\n";
    about_text += "NIELIT-Calicut, Batch : 2018-2020";
    QMessageBox::about(this,"About this control software!",about_text);
}

void MainWindow::on_pushButton_5_clicked()
{
    /*QPrinter printer;
      printer.setPrinterName("desierd printer name");
      QPrintDialog dialog(&printer,this);
      if(dialog.exec() == QDialog::Rejected) return;
      ui->textEdit->print(&printer);*/
}
