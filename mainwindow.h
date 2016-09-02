#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QHostAddress>
#include <QVector>
#include <QString>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QRect>

#include "mynetwork.h"
#include "mygame.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init();

private:
    Ui::MainWindow *ui;
    QVector<QString> state;
    QVector<QVector<QRect>> cells;
    myGame *game;
    myNetwork *network;

signals:
    //void test_client(QHostAddress,int);
    //void test_client_write(QString);
    void toSetUpServer();
    void toSetUpClient(QHostAddress,int);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private slots:
    void on_actionQuit_triggered();
    void serverSetUpAction(QHostAddress address_,int port_);
    void clientSetUpAction(QHostAddress address_,int port_);

};

#endif // MAINWINDOW_H
