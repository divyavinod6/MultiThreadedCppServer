#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <pthread.h>

void * sample(){
    printf("Thread sample.\n");
    sleep(1);
    printf("End Thread.\n");
}

int main(void){
    pthread_t tid,tid_1;
    pthread_create(&tid,NULL,&sample,NULL);
    pthread_create(&tid_1,NULL,&sample,NULL);
    pthread_join(tid,NULL);
    pthread_join(tid_1,NULL);

    return 0;
}