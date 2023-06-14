#include "startmenu.h"
#include "ui_startmenu.h"
#include <iostream>
StartMenu::StartMenu(QWidget *parent)
    : QMainWindow{parent}, ui(new Ui::StartMenu)
{
  ui->setupUi(this);
  connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(transition()));
  this->setWindowIcon(QIcon(":/resources/queen.svg"));
  t= new QTimer();
  t->start(50);
   connect(t,SIGNAL(timeout()),this,SLOT(moveQueen()));
  sc = new QGraphicsScene;
  ui->graphicsView->setScene(sc);
  photo = sc->addPixmap(QPixmap(":/resources/queen.svg").scaled(QSize(ui->graphicsView->height(),ui->graphicsView->height())));
  ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void StartMenu::transition(){
    int boardSize = ui->spinBox->value();
    //Initializing the board
    bool** board = new bool*[boardSize];
    for(int i = 0 ; i < boardSize ; i++)
        board[i] = new bool[boardSize];


    //setting all the board to zeroes
    for(int i = 0 ; i < boardSize ; i++){
        for(int j = 0 ; j < boardSize ; j++)
            board[i][j] = 0;
    }

    menu = new MainWindow(0,boardSize,board);
    menu -> customShow();
    this->hide();


}

void StartMenu::moveQueen(){

   photo->moveBy(75,0);
   if(photo->x() > width())
       photo->setPos(0,0);
   ui->graphicsView->update();



}


