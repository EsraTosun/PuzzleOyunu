#ifndef ETIKET_H
#define ETIKET_H

#include <QLabel>
#include <QDragEnterEvent>  //Sürüklememizi sağlayan sınıf
#include <QDropEvent>  // Bırakmamızı sağlayan sınıf
#include <QMouseEvent>

class etiket : public QLabel
{
    Q_OBJECT
public:
    explicit etiket(QWidget *parent = nullptr);

private:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:

};

#endif // ETIKET_H
