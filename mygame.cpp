#include "mygame.h"

int myGame::BLACK_PLAYER=0;
int myGame::WHITE_PLAYER=1;

QChar myGame::BLACK_CHESS='B';
QChar myGame::WHITE_CHESS='W';
QChar myGame::WARNING='R';
QChar myGame::NOTHING='N';

myGame::myGame(int player_,QObject *parent):abstractGame(parent),player(player_){
    width=height=15;
    initPointer();
    QString string_="";
    for (int i=0;i<height;++i) string_+=NOTHING;
    state->clear();
    for (int i=0;i<width;++i) state->append(string_);
}

myGame::~myGame(){
    deletePointer();
}

void myGame::initPointer(){
    state=new QVector<QString>;
}

void myGame::deletePointer(){
    delete state;
}

void myGame::gameStart(const QVector<QString> &strings_){
    for (int i=0;i<width;++i){
        for (int j=0;j<height;++j){
            (*state)[i][j]=NOTHING;
        }
    }
    emit gameStateChange(*state);
    emit gameStarted();
}

void myGame::checkDirection(int x_, int y_, int dx_, int dy_,int &len_,int &cnt_){
    len_=cnt_=0;
    for (int i=1;;++i){
        int px_=x_+dx_*i;
        int py_=y_+dy_*i;
        if (px_<0 || px_>=width || py_<0 || py_>=height) break;
        if (state->at(px_).at(py_)!=state->at(x_).at(y_)) {
            if (state->at(px_).at(py_)==NOTHING || state->at(px_).at(py_)==WARNING) ++cnt_;
            break;
        }
        ++len_;
    }
    for (int i=1;;++i){
        int px_=x_-dx_*i;
        int py_=y_-dy_*i;
        if (px_<0 || px_>=width || py_<0 || py_>=height) break;
        if (state->at(px_).at(py_)!=state->at(x_).at(y_)) {
            if (state->at(px_).at(py_)==NOTHING || state->at(px_).at(py_)==WARNING) ++cnt_;
            break;
        }
        ++len_;
    }
}

bool myGame::checkWarningDirection(int x_, int y_, int dx_, int dy_){
    int len_,cnt_;
    checkDirection(x_,y_,dx_,dy_,len_,cnt_);
    if (len_==3 && cnt_>=2) return true;
    if (len_==4 && cnt_>=1) return true;
    return false;
}

bool myGame::checkWarningState(QChar chess_to_check_){
    bool flag_[width][height];
    for (int i=0;i<width;++i){
        for (int j=0;j<height;++j){
            flag_[i][j]=true;
        }
    }
    int cnt_=0;
    for (int x_=0;x_<width;++x_){
        for (int y_=0;y_<height;++y_){
            if (flag_[x_][y_] && state->at(x_).at(y_)==chess_to_check_){
                if (checkWarningDirection(x_,y_,1,0)) ++cnt_;
                if (checkWarningDirection(x_,y_,0,1)) ++cnt_;
                if (checkWarningDirection(x_,y_,1,1)) ++cnt_;
                if (checkWarningDirection(x_,y_,1,-1)) ++cnt_;
            }
        }
    }
    return cnt_>=2;
}

void myGame::setWarningPoint(){
    for (int i=0;i<width;++i){
        for (int j=0;j<height;++j){
            if (state->at(i).at(j)==WARNING){
                (*state)[i][j]=NOTHING;
            }
        }
    }
    QChar chess_to_check_=player==WHITE_PLAYER?BLACK_CHESS:WHITE_CHESS;
    for (int i=0;i<width;++i){
        for (int j=0;j<height;++j){
            if (state->at(i).at(j)==NOTHING){
                (*state)[i][j]=chess_to_check_;
                if (checkWarningState(chess_to_check_)){
                    (*state)[i][j]=WARNING;
                } else (*state)[i][j]=NOTHING;
            }
        }
    }
}

bool myGame::checkResultDirection(int x_, int y_, int dx_, int dy_){
    int len_,cnt_;
    checkDirection(x_,y_,dx_,dy_,len_,cnt_);
    if (len_>=5) return true;
}

void myGame::checkGameResult(int x_,int y_){
    bool flag=false;
    if (checkResultDirection(x_,y_,1,0)) flag=true;
    if (checkResultDirection(x_,y_,0,1)) flag=true;
    if (checkResultDirection(x_,y_,1,1)) flag=true;
    if (checkResultDirection(x_,y_,1,-1)) flag=true;
    if (flag){
        QVector<QString> strings_;
        emit gameEnd(strings_);
    }
}

void myGame::gameOperate(const QVector<QString> &strings_){
    int x_=strings_.at(0).toInt();
    int y_=strings_.at(1).toInt();
    if (x_<0 || x_>=width) return ;
    if (y_<0 || y_>=height) return ;
    QChar the_state_=state->at(x_).at(y_);
    if (the_state_==BLACK_CHESS || the_state_==WHITE_CHESS) return ;
    if (player==BLACK_PLAYER){
        (*state)[x_][y_]=BLACK_CHESS;
    } else {
        (*state)[x_][y_]=WHITE_CHESS;
    }
    setWarningPoint();
    checkGameResult(x_,y_);
    emit gameStateChange(*state);
    emit gameOperated();
}

void myGame::getGameState(QVector<QString> &strings_){
    strings_=*state;
    emit gameStateGotten();
}
/*
void myGame::getGameResult(QVector<QString> &strings_){

}*/

void myGame::setGameState(const QVector<QString> &strings_){
    (*state)=strings_;
    emit gameStateSet();
}
