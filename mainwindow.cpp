#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QRandomGenerator>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();   //Formu tam ekran aç
    int x = 50;
    int y = 50;
    int sayi;
    int deger = 0;
    for(int i=0 ;i<5 ;i++)
    {
        for(int k=0 ;k<5 ;k++)
        {
            do //while(deger > 0)
            {
                deger = 0;
                sayi =QRandomGenerator::global()->bounded(25);
                for(int m =0;m< resimList.length();m++)
                {
                    if(sayi == resimList[m])
                    {
                        deger++;
                    }
                }
            } while(deger > 0);
            etiket *et = new etiket(this);
            et->setGeometry(x,y,150,150);
            //et->setScaledContents(true); // Resmi QLabel boyutuna sığdır
            QImage resim(":/res/"+QString::number(sayi)+".png");
            et->setPixmap(QPixmap::fromImage(resim));
            et->show();
            qDebug() << sayi;
            resimList.push_back(sayi);
            x += 150;
        }
        x = 50;
        y += 150;
    }}

MainWindow::~MainWindow()
{
    delete ui;
}
