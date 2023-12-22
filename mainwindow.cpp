#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QRandomGenerator>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    hamleSayisiLabel = ui->HamleSayisi;
    //deneme = new etiket(this,this);
    showMaximized();   //Formu tam ekran aç
    int x = 50;
    int y = 50;
    int indexmain = 0;
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
            etiket *et = new etiket(this,this);
            et->setGeometry(x,y,150,150);
            //et->setScaledContents(true); // Resmi QLabel boyutuna sığdır
            QImage resim(":/res/"+QString::number(sayi)+".png");
            et->setPixmap(QPixmap::fromImage(resim));
            et->bulunduguindex = indexmain;
            et->resimIndex = sayi;
            et->show();
            qDebug() << sayi;
            puzzleParcalariList.push_back(et);
            resimList.push_back(sayi);
            x += 150;
            //qDebug() << indexmain;
            indexmain++;
        }
        x = 50;
        y += 150;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: HamleSayisiArttirma()
{
    int yedek = hamleSayisiLabel->text().toInt();
    qDebug() << yedek;
    yedek++;
    hamleSayisiLabel->setText(QString::number(yedek));
    qDebug() << hamleSayisiLabel->text().toInt();

}

