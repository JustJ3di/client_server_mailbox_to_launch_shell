#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<pthread.h>

#include"header.h"

void *run_termina(void *q){

    int *queue = (int*)q;

    Mex m= {EXIT,'A'};

    msgsnd(*queue,(void *)&m,SIZEOF(Mex),0);

    pthread_exit(NULL);

}

void *run_esegui(void *p){

    execlp("sh","sh",NULL);  

    pthread_exit(NULL);

}


int main(int argc,char *argv[]){


    int queue = msgget(ftok(PATH,KEY),IPC_CREAT|0664);

    int *pqueue = &queue;

    pthread_t termina;
    pthread_t esegui;
    
    Mex mex;

    msgrcv(queue,(void *)&mex,SIZEOF(msg),0,0);



    pthread_create(&termina,NULL,run_termina,(void *)pqueue);

    pthread_create(&esegui,NULL,run_esegui,NULL);

    pthread_join(esegui,NULL);  
        
    pthread_join(termina,NULL);


    return 0;
}
