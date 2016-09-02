#ifndef ABSTRACT_GAME_H
#define ABSTRACT_GAME_H

#include <QObject>
#include <QVector>
#include <QString>

class abstractGame:public QObject{

    Q_OBJECT

public:
    abstractGame(QObject *parent=0):QObject(parent){

    }
    ~abstractGame()=default;

protected slots:
    virtual void gameStart(const QVector<QString> &strings_)=0;
    virtual void gameOperate(const QVector<QString> &strings_)=0;
    virtual void getGameState(QVector<QString> &strings_)=0;
    //virtual void getGameResult(QVector<QString> &strings_)=0;
    virtual void setGameState(const QVector<QString> &strings_)=0;

signals:
    void gameStarted();
    void gameOperated();
    void gameStateGotten();
    void gameEnd(const QVector<QString>&);
    void gameStateChange(const QVector<QString>&);
    void gameStateSet();

};

#endif // ABSTRACTGAME_H
