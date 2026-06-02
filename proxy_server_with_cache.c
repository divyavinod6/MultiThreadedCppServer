#include "proxy_parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>


#define MAX_CLIENTS 10
typedef struct cache_element cache_element;


struct cache_element{
    char* data;
    int len;
    char* url;
    time_t lru_time_track;
    cache_element* next;
};

cache_element* find(char* url ); // to find requested url in my Linkedlist cache
int add_cache_element(char* data, int size, char* url); // add new url in my LL cache
void remove_cache_element(); // delete least reused url from LL

int port_number = 8080;
int proxy_socketID;
pthread_t tid[MAX_CLIENTS]; // every client request, we create a thread and in it a socket to return response 
sem_t semaphore;
pthread_mutex_t lock;
cache_element* head;
int cache_size;

int main(int argc,char* argv[]){
    int client_socketId,client_len;
    struct sockaddr server_addr,client_addr;
    sem_init(&semaphore,0,MAX_CLIENTS);
    pthread_mutex_init(&lock,NULL);

    if(argv == 2){
        // argv[] = {./proxy, 9090} then run server on this port
        port_number = atoi(argv[1]); // extracting 9090
    }else{
        printf("Too few arguments \n");
        exit(1); // to exist system call
    }

    printf("starting Proxy server at port : %d\n",port_number);

    // creating socketid for proxy server
    proxy_socketID = socket(AF_INET,SOCK_STREAM,0); // socket returns a file descriptor which returns negetive if communitcation unsuccessfull
    if(proxy_socketID <0){
        perror("FAILED TO CREATE A SOCKET\n");
    }
    int reuse = 1;
    if(setsockopt(proxy_socketID,SOL_SOCKET,SO_REUSEADDR,(const char*)&reuse,sizeof(reuse))<0){
        perror("setSocOpt failed\n");
    }
    // all variables hold garbage value so we have to clean it be setting it back to 0
    bzero((char*)&server_addr, sizeof(server_addr));
    // to continue building from here
}