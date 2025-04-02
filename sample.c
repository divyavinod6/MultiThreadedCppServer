#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>


void* sample(void* arg) {
    printf("Hello from thread!\n");
    sleep(1);
    printf("End from thread!\n");
}

int main(void){
    
    pthread_t tid,tid_1;
    pthread_create(&tid,NULL,&sample,NULL);
    pthread_create(&tid_1,NULL,&sample,NULL);
    pthread_join(tid,NULL);
    pthread_join(tid_1,NULL);
    
    return 0;
    
    /*
    pthread_t thread;
    if (pthread_create(&thread, NULL, thread_function, NULL)) {
        printf("Error creating thread\n");
        return 1;
    }
    pthread_join(thread, NULL);
    return 0;
    
    s*/

}