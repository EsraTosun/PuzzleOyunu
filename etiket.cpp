#include "etiket.h"
#include <QMimeData>   //MimeData sınıfının alt metotlarına erişmemizi sağlar
//Sürükle bırak işlemlerini yapar
#include <QDrag>

etiket::etiket(QWidget *parent) : QLabel(parent)
{
    setFrameShape(QFrame :: Box);  //Nesnenin görünmesini sağlar
    setScaledContents(true);  //Labelımız ne kadar büyükse resmi o kadar ölçeklendirilir
    setAcceptDrops(true);  //Sürükle bırak özelliği verilir.
    //Formun accepsDropu false olacak . Bu nesnenin sürükle bırakılmasını sağlar
}

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

    if(gelen && gelen != this)   //gelen adres dolu ise ve kendi adresinden farklı ise bu işlemi gerçekleştir deriz.
    {
        QImage birakilan(pixmap()->toImage());  //Bulunduğu(Sürüklenip bırakılan label) nesnenin imageni alırız
        setPixmap(QPixmap::fromImage(gelen->pixmap()->toImage()));
        gelen->setPixmap(QPixmap::fromImage(birakilan));
        return;
    }

    QList<QUrl> yollar = event->mimeData()->urls();  //Sürüklenen nesnenin yolları alınır
    if(yollar.isEmpty()) {
        return;  //Yollar boş ise return et;
    }
    QString yol = yollar.first().toLocalFile();
    //ilk yolu alarak toLocalFile => Yerel bir dosya olduğunu söyleriz
    QImage resim(yol);  //Yolu alarak image de göster.
    setPixmap(QPixmap::fromImage((resim)));
    //Sürükleyek bu resmin açılmasını sağlarız.
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
