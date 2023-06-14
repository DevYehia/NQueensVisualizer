#ifndef STARTMENU_H
#define STARTMENU_H

#include <QMainWindow>
#include "mainwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui { class StartMenu; }
QT_END_NAMESPACE
class StartMenu : public QMainWindow
{
    Q_OBJECT
public:
    explicit StartMenu(QWidget *parent = nullptr);

private:
    Ui::StartMenu *ui;
    MainWindow* menu;
    QTimer* t;
    QGraphicsScene* sc;
    QGraphicsPixmapItem* photo;
private slots:
    void transition();
    void moveQueen();

};

#endif // STARTMENU_H
