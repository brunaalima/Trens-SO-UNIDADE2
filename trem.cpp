#include "trem.h"
#include "semaphore.h"
#include "mainwindow.h"
#include <QtCore>
#include <QDebug>


#define regiao_crit_d 1
#define regiao_crit_f1 2
#define regiao_crit_f2 3
#define regiao_crit_g 4
#define regiao_crit_b 5
#define regiao_crit_i 6
#define regiao_crit_n 7
#define regiao_livre 8


sem_t S[7];
sem_t mutex;

//array de status dos trens

int status_trens[5];

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
}
void Trem::setVelocidade(int v){
    velocidade=v;
}

int Trem::getX(){
    return x;
}
int Trem::getY(){
    return y;
}
void Trem::inicializacao(){
    for(int i= 0; i < 7;i++ ){
            sem_init(&S[i], 0, 1);
        }
    sem_init(&mutex, 0, 1);
}
bool Trem::regiao_b(int tremID){
    if(tremID == 1){
        if(status_trens[3] != regiao_crit_b){ //verifica se trem 4 esta na regiao critica
            sem_wait(&mutex);
            sem_wait(&S[0]);
            status_trens[0] = regiao_crit_b; //trem 1 entra na area critica
            return true;
        }
        else{
            return false;
        }
    }
    else{
        if(status_trens[0] != regiao_crit_b){ //verifica se trem 1 esta na regiao critica
            sem_wait(&mutex);
            sem_wait(&S[3]);
            status_trens[3] = regiao_crit_b; //trem 4 entra na area critica
            return true;
        }
        else{
            return false;
        }
    }
}
bool Trem::regiao_d(int tremID){
    //Trem1 = tremID-1(0) e Trem2 = tremID(1)
    if(status_trens[tremID] != regiao_crit_d){ //verifica se trem 2 esta na regiao critica
        sem_wait(&mutex);
        sem_wait(&S[tremID-1]);
        status_trens[tremID-1] = regiao_crit_d; //trem 1 entra na area critica
        return true;
    }
    else{
        return false;
    }
}
bool Trem::regiao_f1(int tremID){
    if(tremID == 2){
        if(status_trens[3] != regiao_crit_f1){ //verifica se trem 4 esta na regiao critica
            sem_wait(&mutex);
            sem_wait(&S[1]);
            status_trens[1] = regiao_crit_f1; //trem 2 entra na area critica
            return true;
        }
        else{
            return false;
        }
    }
    else{
        if(status_trens[1] != regiao_crit_f1){ //verifica se trem 2 esta na regiao critica
            sem_wait(&mutex);
            sem_wait(&S[3]);
            status_trens[3] = regiao_crit_f1; //trem 4 entra na area critica
            return true;
        }
        else{
            return false;
        }
    }
}
bool Trem::regiao_f2(int tremID){
    if(tremID == 2){
        if(status_trens[4] != regiao_crit_f2){ //verifica se trem 5 esta na regiao critica
            sem_wait(&mutex);
            sem_wait(&S[1]);
            status_trens[1] = regiao_crit_f2; //trem 2 entra na area critica
            return true;
        }
        else{
            return false;
        }
    }
    else{
        if(status_trens[1] != regiao_crit_f2){ //verifica se trem 2 esta na regiao critica
            sem_wait(&mutex);
            sem_wait(&S[4]);
            status_trens[4] = regiao_crit_f2; //trem 5 entra na area critica
            return true;
        }
        else{
            return false;
        }
    }
}
bool Trem::regiao_g(int tremID){
    if(tremID == 2){
        if(status_trens[2] != regiao_crit_g){ //verifica se trem 3 esta na regiao critica
            sem_wait(&mutex);
            sem_wait(&S[1]);
            status_trens[1] = regiao_crit_g; //trem 2 entra na area critica
            return true;
        }
        else{
            return false;
        }
    }
    else{
        if(status_trens[1] != regiao_crit_g){ //verifica se trem 2 esta na regiao critica
            sem_wait(&mutex);
            sem_wait(&S[2]);
            status_trens[2] = regiao_crit_g; //trem 3 entra na area critica
            return true;
        }
        else{
            return false;
        }
    }
}
bool Trem::regiao_i(int tremID){
    if(tremID == 3){
        if(status_trens[4] != regiao_crit_i){ //verifica se trem 5 esta na regiao critica
            sem_wait(&mutex);
            sem_wait(&S[2]);
            status_trens[2] = regiao_crit_i; //trem 3 entra na area critica
            return true;
        }
        else{
            return false;
        }
    }
    else{
        if(status_trens[2] != regiao_crit_i){ //verifica se trem 3 esta na regiao critica
            sem_wait(&mutex);
            sem_wait(&S[4]);
            status_trens[4] = regiao_crit_i; //trem 5 entra na area critica
            return true;
        }
        else{
            return false;
        }
    }
}
bool Trem::regiao_n(int tremID){
    if(tremID == 4){
        if(status_trens[4] != regiao_crit_n){ //verifica se trem 5 esta na regiao critica
            sem_wait(&mutex);
            sem_wait(&S[3]);
            status_trens[3] = regiao_crit_n; //trem 4 entra na area critica
            return true;
        }
        else{
            return false;
        }
    }
    else{
        if(status_trens[3] != regiao_crit_n){ //verifica se trem 4 esta na regiao critica
            sem_wait(&mutex);
            sem_wait(&S[4]);
            status_trens[4] = regiao_crit_n; //trem 5 entra na area critica
            return true;
        }
        else{
            return false;
        }
    }
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1:     //Trem 1
            if (y == 30 && x <330){
               if(x != 310) x+=10;
               else{
                    if(regiao_d(ID)) x+=10;
                    }

            }
            else if (x == 330 && y < 150)
                y+=10;
            else if (x > 60 && y == 150){
                x-=10;
                if(x == 320){
                    status_trens[ID-1] = regiao_crit_b;
                    sem_post(&mutex);
                    sem_post(&S[ID-1]);
                }
            }
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: //Trem 2
            if (y == 30 && x <600){
                x+=10;
                if(x == 340){
                   status_trens[ID-1] = regiao_livre;
                   sem_post(&mutex);
                   sem_post(&S[ID-1]);
                }
            }
            else if (x == 600 && y < 150)
                y+=10;
            else if (x > 330 && y == 150)
                if(x != 350) x-=10;
                else{
                    if(regiao_d(ID)) x-=10;
                }
            else{
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3: //Trem 3
            if (y == 30 && x < 850)
                x+=10;
            else if (x == 850 && y < 150)
                y+=10;
            else if (x > 600 && y == 150)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4: //Trem 4
            if (y == 150 && x <460)
                x+=10;
            else if (x == 460 && y < 270)
                y+=10;
            else if (x > 190 && y == 270)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5: //Trem 5
            if (y == 150 && x <710)
                x+=10;
            else if (x == 710 && y < 270)
                y+=10;
            else if (x > 460 && y == 270)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        default:
            break;
        }
        msleep(velocidade);
    }
}




