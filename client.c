#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#include"header.h"

int main(int argc,char *argv[]){


    int queue = msgget(ftok(PATH,KEY),IPC_CREAT|0664);


    
    Mex mex = {1,'a'};

    msgsnd(queue,(void *)&mex,SIZEOF(msg),0);

    msgrcv(queue,(void *)&mex,SIZEOF(Mex),EXIT,0);

    printf("Termineted \n");

    msgctl(queue,IPC_RMID,0);


    return 0;
}
