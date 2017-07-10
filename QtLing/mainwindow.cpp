#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include <QStandardItemModel>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <stdio.h>
#include <QDir>
#include "WordCollection.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{   QString abspath("/Users/johngoldsmith/projects/QtLing/QtLing/QtLing");
    if (!QDir::setCurrent(abspath))
    {
        qDebug() << "Could not change to home directory";
    }
    QString filename = "./browncorpus.dx1";
    QFile file(filename);
    if (! file.exists()){
        qDebug() << filename << "File does not exist.";
    }else
    {
        qDebug() << "File exists at least.";
    }
//    file.open(QFile::Text);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "rippp";
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        line.simplified();
        QStringList words = line.split (" ");
        QString word = words[0];
        Words[word] = 1;

    }


//    CWordCollection wordCollection;

//    QList<QString> list;
//    list << "red" << "blue" << "green" << "yellow" << "purple" << "orange";
//    int count = list.count();
//    for (i = 0; i < count; i++) {
//        qDebug() << list.at(i);
//        wordCollection.operator <<( list.at(i) );
//    }
//     qSort(wordCollection.m_WordList);

    QMapIterator<QString,int> iter(Words);

    QStandardItemModel *model = new QStandardItemModel(Words.size(),1,this); //n Rows and 3 Columns
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Column1 Header")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Column2 Header")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Column3 Header")));

    ui->tableView->setModel(model);
    int rowno = 0;
    while (iter.hasNext()) {
        iter.next();
        QStandardItem *ithRow = new QStandardItem(iter.key());
        model->setItem(rowno,0,ithRow);
        rowno++;
    }
}
