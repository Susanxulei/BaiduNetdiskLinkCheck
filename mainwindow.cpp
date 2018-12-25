#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_dialog.h"
#include "dialog.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include "CurlWrapper/include/NetworkWrapper.h"
#include "json.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
using namespace nlohmann;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->resize(600,480);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName;
    fileName=QFileDialog::getOpenFileName(this,tr("文件"),"",tr("text(*.txt)"));
    if(!fileName.isNull()){
        //fileName是选择的文件名
        QFile file(fileName);
        if(!file.open(QFile::ReadOnly|QFile::Text)){
            QMessageBox::warning(this,tr("Error"),tr("read file error:&1").arg(file.errorString()));
            return;
        }
        QTextStream filename(&fileName);
        ui->textEdit->setPlainText(filename.readAll());
    }
    else{
        qDebug()<<"取消";//点的是取消
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    /*
    string vastr;
    string unstr;
    vector<string> errdic;
        do{
            ifstream ifs("strings_utf8.json");
            string str,tmp;
            while(getline(ifs,tmp)) str.append(tmp);
            json j=json::parse(str);
            vastr=j["ValidContent"];
            unstr=j["UnknownContent"];
            for(auto& s:j["ErrorContent"])
            {
                errdic.push_back(s["content"].get<string>());
            }
        }while(0);
    */

    QString url=ui->lineEdit->text();
    if(url==nullptr){
        QString fileName=ui->textEdit->toPlainText();
        if(fileName==nullptr){
            QFile file("D:/desktop/666.txt");
            if(!file.open(QFile::ReadOnly|QFile::Text)){
                QMessageBox::warning(this,tr("Error"),tr("read file error:&1").arg(file.errorString()));
                return;
            }
            QTextStream in(&file);
            QApplication::setOverrideCursor(Qt::WaitCursor);
            dialog=new Dialog(this);//新建一个窗口对象，this指定了新窗口的父对象是mainwindow
            dialog->setModal(false);//modal属性决定了将弹出的dialog窗口为非模态
            dialog->ui->textEdit->setPlainText(in.readAll());
            QApplication::restoreOverrideCursor();
            dialog->show();
        }
        else {
            QFile file(fileName);
            if(!file.open(QFile::ReadOnly|QFile::Text)){
                QMessageBox::warning(this,tr("Error"),tr("read file error:&1").arg(file.errorString()));
                return;
            }
            QTextStream in(&file);
            QApplication::setOverrideCursor(Qt::WaitCursor);
            dialog=new Dialog(this);//新建一个窗口对象，this指定了新窗口的父对象是mainwindow
            dialog->setModal(false);//modal属性决定了将弹出的dialog窗口为非模态
            dialog->ui->textEdit->setPlainText(in.readAll());
            QApplication::restoreOverrideCursor();
            dialog->show();
        }
    }
    else {
        QTextStream in(&url);
        QApplication::setOverrideCursor(Qt::WaitCursor);
        dialog=new Dialog(this);//新建一个窗口对象，this指定了新窗口的父对象是mainwindow
        dialog->setModal(false);//modal属性决定了将弹出的dialog窗口为非模态
        dialog->ui->textEdit->setPlainText(in.readAll());
        QApplication::restoreOverrideCursor();
        dialog->show();
    }
}
