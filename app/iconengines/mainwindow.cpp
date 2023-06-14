#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
MainWindow::MainWindow(QWidget *parent,int size,bool** grid)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->size = size;
    board = grid;
    started = false;

    loop = new QEventLoop();
    connect(ui->generator,SIGNAL(clicked()),loop,SLOT(quit()));

    photos = new QGraphicsPixmapItem**[size];
    for(int i = 0 ; i < size ; i++)
        photos[i] = new QGraphicsPixmapItem*[size];

    boardScene = new QGraphicsScene(this);

}

bool MainWindow::isSafe(bool **arr,int row,int col,int boardSize){
    for(int i = 0 ; i < col ; i++){
        if(arr[row][i] == 1)return 0;
    }
    for(int i = row-1,j = col-1;i>=0&&j>=0;i--,j--)
        if(arr[i][j] == 1)return 0;


    for(int i = row+1,j = col-1;i<boardSize&&j>=0;i++,j--)
        if(arr[i][j] == 1)return 0;

    return 1;
}

bool MainWindow::solve(int boardSize,int colCounter){
    if(colCounter == boardSize){  //Solution Found

            return 1;
    }


    for(int i = 0 ; i < boardSize ; i++){
        addQueen(i,colCounter);
        QTimer::singleShot(100,loop,&QEventLoop::quit);
        loop -> exec();
        if (!isSafe(board,i,colCounter,boardSize))
        {
            removeQueen(i,colCounter);
        }
        else{
            if (solve(boardSize,colCounter+1))
            {
                ui->generator->setVisible(1);
                loop->exec();
                ui->generator->setVisible(0);
            }
            removeQueen(i,colCounter);
        }


    }
    return 0;
}

void MainWindow::addQueen(int row,int col){
    board[row][col] = 1;
   updateView(row,col);

}

void MainWindow::removeQueen(int row,int col){
    board[row][col] = 0;
updateView(row,col);

}

void MainWindow::updateView(int row,int col){
    float widthInc = ui->chessBoard->width()/size;
    float heightInc = ui ->chessBoard->height()/size;
    float startX = 0;
    float startY = 0;
    if(board[row][col] == 1){

        photos[row][col] = boardScene->addPixmap(QPixmap(":/resources/queen.svg").scaled(QSize(widthInc,widthInc)));
        photos[row][col]->setPos(startX+widthInc*col,startY+heightInc*row);

    }
    else{
        boardScene->removeItem(photos[row][col]);
        delete photos[row][col];
    }



}

void MainWindow::terminate(){
    exit(0);
}

void MainWindow::customShow(){

    QWidget::showFullScreen();



    float cutOff = (width()-height())/2;
    float boardWidth = width() - 2*cutOff;
    ui->chessBoard -> setGeometry(cutOff,0,boardWidth,height());
    ui->chessBoard->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->chessBoard->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->chessBoard ->setScene(boardScene);

    ui->generator->setGeometry(cutOff+boardWidth+cutOff/2 - ui->generator->width()/2,
                               height()/2,
                               ui->generator->width(),
                               ui-> generator -> height() );
    ui->generator->setVisible(0);

    ui->quitter->setGeometry(+cutOff/2 - ui->quitter->width()/2,
                               height()/2,
                               ui->quitter->width(),
                               ui-> quitter -> height() );


    ui -> pressLabel -> setGeometry((width() - ui -> pressLabel->width())/2,
                                    (height() - ui -> pressLabel->height())/2,
                                    ui -> pressLabel -> width(),
                                    ui -> pressLabel -> height()
                                    );




    connect(ui ->quitter,SIGNAL(clicked()),SLOT(terminate()));

    float startX = 0;
    float startY = 0;
    bool flag = true;
    for(int i = 0 ; i < size ; i++){
        for(int j = 0 ; j < size ; j++){
            QGraphicsRectItem* rect = new QGraphicsRectItem(startX,startY,boardWidth/size,boardWidth/size);
            rect -> setBrush(flag ? QBrush(QColor(0,89,0)) : QBrush(QColor(Qt::white)));
            rect -> setPen(QPen(QColor(Qt::black)));
            boardScene->addItem(rect);
            flag = !flag;
            startX+=boardWidth/size;
        }
        if(!(size&1))
        flag = !flag;
        startX = 0;
        startY+=boardWidth/size;

    }


}

void MainWindow::keyPressEvent(QKeyEvent* event){

        if(event -> key() == Qt::Key_Q && !started){
            started = true;
            ui->pressLabel->setVisible(0);
            solve(size);
            started = false;
            ui->pressLabel->setVisible(1);
        }
};




MainWindow::~MainWindow()
{
    delete ui;
}

