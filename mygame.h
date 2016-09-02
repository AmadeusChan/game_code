#ifndef MY_GAME_H
#define MY_GAME_H

#include "abstractgame.h"
#include <QChar>

class myGame:public abstractGame{

    Q_OBJECT

public:
    static int BLACK_PLAYER;
    static int WHITE_PLAYER;

    static QChar BLACK_CHESS;
    static QChar WHITE_CHESS;
    static QChar WARNING;
    static QChar NOTHING;

    myGame(int player_,QObject *parent=0);
    ~myGame();

private:
    QVector<QString> *state;
    int player,width,height;

    void initPointer();
    void deletePointer();
    void checkDirection(int x_,int y_,int dx_,int dy_,int &len_,int &cnt_);
    bool checkWarningDirection(int x_,int y_,int dx_,int dy_);
    bool checkWarningState(QChar chess_to_check_);
    void setWarningPoint();
    bool checkResultDirection(int x_,int y_,int dx_,int dy_);
    void checkGameResult(int x_,int y_);

protected slots:
    void gameStart(const QVector<QString> &strings_);
    void gameOperate(const QVector<QString> &strings_);
    void getGameState(QVector<QString> &strings_);
    //void getGameResult(QVector<QString> &strings_);
    void setGameState(const QVector<QString> &strings_);

};

#endif // MYGAME_H
