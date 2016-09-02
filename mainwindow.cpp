#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPoint>
#include <QLine>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QRect>
#include <QDesktopWidget>
#include <algorithm>
#include <QStringList>
#include <QInputDialog>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRect screen_=(QApplication::desktop())->screenGeometry();
    this->resize(screen_.width()/2,screen_.width()/2);
    state.clear();
    for (int i=0;i<15;++i){
        QString string_="";
        for (int j=0;j<15;++j) string_+="N";
        state.append(string_);
    }
    state[1][2]=QChar('B');
    state[1][3]=QChar('W');
    state[2][3]=QChar('R');
    network=new myNetwork;
    qDebug()<<"main thread:"<<QThread::currentThreadId();
    QThread *thread_for_network=new QThread(this);
    network->moveToThread(thread_for_network);

    connect(this,SIGNAL(toSetUpClient(QHostAddress,int)),
            network,SLOT(setUpClient(QHostAddress,int)));
    connect(this,SIGNAL(toSetUpServer()),
            network,SLOT(setUpServer()));

    emit toSetUpServer();

    connect(network,SIGNAL(clientSetUp(QHostAddress,int)),
            this,SLOT(clientSetUpAction(QHostAddress,int)));
    connect(network,SIGNAL(serverSetUp(QHostAddress,int)),
            this,SLOT(serverSetUpAction(QHostAddress,int)));


    //test_server;
    //myNetwork *network_=new myNetwork(this);
    /*connect(ui->pushButton,SIGNAL(clicked(bool)),
            network_,SLOT(setUpServer()));*/
    //connect(ui->pushButton,&QPushButton::clicked,&network_,&myNetwork::setUpServer);
    /*connect(ui->pushButton,SIGNAL(clicked()),
            &network_,SLOT(setUpServer()));*/
    /*connect(ui->pushButton,&QPushButton::clicked,[=](){
        qDebug()<<"clicked";
    });*/
    /*connect(network_,&myNetwork::serverSetUp,[=](QHostAddress address_,int port_){
        qDebug()<<address_<<" "<<port_;
    });
    connect(network_,	&myNetwork::connected,[=](){
        qDebug()<<"connected!";
    });
    connect(network_,&myNetwork::dataRead,[=](QString string_){
        qDebug()<<string_;
    });*/

    //end_test_server

    //test_client
    /*connect(this,SIGNAL(test_client(QHostAddress,int)),
            network_,SLOT(setUpClient(QHostAddress,int)));
    emit test_client(QHostAddress("127.0.0.1"),45500);
    connect(this,SIGNAL(test_client_write(QString)),
            network_,SLOT(writeData(QString)));
    connect(network_,&myNetwork::connected,[=](){
        qDebug()<<"connected";
        emit test_client_write("Hello GO!");
    });*/

    //end_test_client
}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;
    delete network;
}

void MainWindow::init(){
    QStringList items_;
    items_<<tr("Server Mode")<<tr("Client Mode");
    bool okay_;
    QString item_;
    item_=QInputDialog::getItem(this,tr("SELECT MODE"),tr("please select a mode:"),items_,0,false,&okay_);
    if (!( okay_ && item_.size() )) {
        qDebug()<<"close()";
    } else {
        qDebug()<<item_;
        game=new myGame(item_==tr("Server Mode")?0:1);
        if (item_==tr("Server Mode")){
            emit toSetUpServer();
        } else {

        }
    }
}

void MainWindow::paintEvent(QPaintEvent *event){
    int len_=std::min(this->height(),this->width())/16;
    QPoint left_top(len_,len_);
    QPoint right_bottom(len_*15,len_*15);
    QPoint right_top(len_*15,len_);
    QPoint left_bottom(len_,len_*15);
    QPainter painter_(this);
    painter_.setPen(QPen(Qt::black));
    for (int i=1;i<=15;++i){
        painter_.drawLine(QPoint(len_,len_*i),QPoint(len_*15,len_*i));
        painter_.drawLine(QPoint(len_*i,len_),QPoint(len_*i,len_*15));
    }
    cells.clear();
    QVector<QRect> vector_;
    int delta_=len_/8;
    for (int i=0;i<15;++i){
        vector_.clear();
        for (int j=0;j<15;++j){
            vector_.append(QRect(len_/2+len_*j+delta_,len_/2+len_*i+delta_,len_-delta_*2,len_-delta_*2));
        }
        cells.append(vector_);
    }
    for (int i=0;i<15;++i){
        for (int j=0;j<15;++j){
            if (state.at(i).at(j)==QChar('B')){
                painter_.setPen(QPen(Qt::black));
                painter_.setBrush(QBrush(Qt::black));
                painter_.drawEllipse(cells[i][j]);
            }
            if (state.at(i).at(j)==QChar('W')){
                painter_.setPen(QPen(Qt::black));
                painter_.setBrush(QBrush(Qt::white));
                painter_.drawEllipse(cells[i][j]);
            }
            if (state.at(i).at(j)==QChar('R')){
                painter_.setPen(QPen(Qt::red));
                painter_.setBrush(QBrush(Qt::transparent));
                painter_.drawEllipse(cells[i][j]);
            }
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if (event->button()==Qt::LeftButton){
        int x_=-1,y_=-1;
        bool flag_=false;
        for (int i=0;i<15;++i){
            for (int j=0;j<15;++j){
                if (cells[i][j].contains(event->pos())){
                    x_=i,y_=j;
                    flag_=true;
                    break;
                }
            }
            if (flag_) break;
        }
        qDebug()<<x_<<" "<<y_;
        if (x_!=-1 && y_!=-1){

        }
    }
    QMainWindow::mousePressEvent(event);
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}

void MainWindow::serverSetUpAction(QHostAddress address_, int port_){
    qDebug()<<"serverSetUpAction()";
    qDebug()<<address_;
    qDebug()<<port_;
}

void MainWindow::clientSetUpAction(QHostAddress address_, int port_){
    qDebug()<<address_;
    qDebug()<<port_;
}
