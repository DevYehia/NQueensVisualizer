#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QGraphicsScene>
#include <QMainWindow>
#include <QLabel>
#include <QGraphicsPixmapItem>
#include <windows.h>
#include <QKeyEvent>
#include <QTimer>
#include <QEventLoop>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr,int size = 8,bool** grid = NULL);
    ~MainWindow();
    bool solve(int boardSize,int colCounter = 0);
    void customShow();
private:
    bool isSafe(bool **arr,int row,int col,int boardSize);
    void addQueen(int row , int col);
    void removeQueen(int row , int col);
    void updateView(int row,int col);
private slots:
    void terminate();
private:
    Ui::MainWindow *ui;
    QGraphicsScene* boardScene;
    int size = 8;
    bool** board;
    QGraphicsPixmapItem*** photos;
    QEventLoop* loop;
    bool started;

protected:
    void keyPressEvent(QKeyEvent* event);
};
#endif // MAINWINDOW_H
