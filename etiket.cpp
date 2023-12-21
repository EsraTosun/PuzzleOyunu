#include "etiket.h"
#include <QMimeData>   //MimeData sınıfının alt metotlarına erişmemizi sağlar
//Sürükle bırak işlemlerini yapar
#include <QDrag>
#include <QDebug>

#include "mainwindow.h"

etiket::etiket(QWidget *parent) : QLabel(parent)
{
    setFrameShape(QFrame :: Box);  //Nesnenin görünmesini sağlar
    setScaledContents(true);  //Labelımız ne kadar büyükse resmi o kadar ölçeklendirilir
    setAcceptDrops(true);  //Sürükle bırak özelliği verilir.
    //Formun accepsDropu false olacak . Bu nesnenin sürükle bırakılmasını sağlar
}

/*etiket::etiket(MainWindow *frm,QWidget *parent) : QLabel(parent)
{
    anafrm = frm;
}  */

void etiket::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}

void etiket::dropEvent(QDropEvent *event)
{
    ////ÖNEMLİ !!!!!!!!!!!!!!!
    etiket *gelen = qobject_cast<etiket*>(event->source());
    // qobject_cast=> Bu method sayesinde farklı dosya yolu olur ise istediğimiz şekilde yazmasını sağlar
    // etiket sınıfından oluşan nesnelerin gelmesini sağlarız
    // event->source() => Sadece sürüklenen nesnenin yolunu almamızı sağlar


    int kontrol = 0;

    if(gelen && gelen != this)   //gelen adres dolu ise ve kendi adresinden farklı ise bu işlemi gerçekleştir deriz.
    {
        if((gelen->bulunduguindex / 5) == (bulunduguindex / 5))  //Aynı satırdalar mı kontrol
        {
            if((gelen->bulunduguindex == bulunduguindex-1 || gelen->bulunduguindex == bulunduguindex+1))  //Yanında mı
            {
                kontrol = 1;
            }
        }

        else if((gelen->bulunduguindex / 5) == (bulunduguindex / 5 + 1) )  //Üst satırı var mı ve index o satırdaki bir eleman mı kontrolü
        {
            if((gelen->bulunduguindex - 6 == bulunduguindex || gelen->bulunduguindex - 5 == bulunduguindex || gelen->bulunduguindex - 4 == bulunduguindex)) //Satırın üstünden bir eleman mı
            {
                kontrol = 2;
            }
        }
        else if((gelen->bulunduguindex / 5) == (bulunduguindex / 5 - 1) )  //Alt satırı var mı ve index o satırdaki bir eleman mı kontrolü
        {
            if(gelen->bulunduguindex == bulunduguindex - 6 || gelen->bulunduguindex == bulunduguindex - 5 || gelen->bulunduguindex == bulunduguindex - 4) //Satırın üstünden bir eleman mı
            {
                kontrol = 3;
            }
        }
        qDebug() << "Gelen İndex:";
        qDebug() << gelen->bulunduguindex;
        qDebug() << "İndex:";
        qDebug() << bulunduguindex;

        qDebug() << "Kontrol:";
        qDebug() << kontrol;

        int yedek;
        if(kontrol!= 0)
        {
            yedek = bulunduguindex;
            bulunduguindex = gelen->bulunduguindex;
            gelen->bulunduguindex = yedek;
            QImage birakilan(pixmap()->toImage());  //Bulunduğu(Sürüklenip bırakılan label) nesnenin imageni alırız
            setPixmap(QPixmap::fromImage(gelen->pixmap()->toImage()));
            gelen->setPixmap(QPixmap::fromImage(birakilan));
            //return;
        }
        qDebug() << "Gelen İndex:";
        qDebug() << gelen->bulunduguindex;
        qDebug() << "İndex:";
        qDebug() << bulunduguindex;

    }
}

void etiket::mouseMoveEvent(QMouseEvent *event)
{
    QMimeData *mdata = new QMimeData();
    mdata->setImageData(pixmap()->toImage());  //Sürüklenen nesne
    QDrag *suruklenen = new QDrag(this);  //neyin sürüklendiğini this vererek öğreniriz.
    suruklenen->setMimeData(mdata);
    suruklenen->setPixmap(mdata->imageData().value<QPixmap>());
    suruklenen->exec(Qt::MoveAction);   //drag işleminin başlamasını sağlar
    //Hareket oldukça çalışsın.
}
