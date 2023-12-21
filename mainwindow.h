#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "etiket.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector<etiket*> puzzleParcalariList;
    QList<int> resimList;
    etiket *deneme;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
