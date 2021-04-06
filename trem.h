#ifndef TREM_H
#define TREM_H

#include <QThread>
#include "semaphore.h"


/*
 * Classe Trem herda QThread
 * Classe Trem passa a ser uma thread.
 * A função START inicializa a thread. Após inicializada, a thread irá executar a função RUN.
 * Para parar a execução da função RUN da thread, basta executar a função TERMINATE.
 *
*/
class Trem: public QThread{
 Q_OBJECT
public:
    Trem(int,int,int);  //construtor
    void run();         //função a ser executada pela thread
    void setVelocidade(int v);
    int getY();
    int getX();
    void inicializacao();
    bool regiao_d(int tremID);
    bool regiao_b(int tremID);
    bool regiao_f1(int tremID);
    bool regiao_f2(int tremID);
    bool regiao_g(int tremID);
    bool regiao_i(int tremID);
    bool regiao_n(int tremID);



//Cria um sinal
signals:
    void updateGUI(int,int,int);

private:
   int x;           //posição X do trem na tela
   int y;           //posição Y do trem na tela
   int ID;          //ID do trem
   int velocidade;  //Velocidade. É o tempo de dormir em milisegundos entre a mudança de posição do trem
};

#endif // TREM_H
