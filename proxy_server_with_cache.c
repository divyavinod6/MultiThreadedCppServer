#include "proxy_parse.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h> 
#include <pthread.h>

//configured phread.h
#define MAX_CLIENTS 10
typedef struct cache_element cache_element;


struct cache_element{
    char* data;
    int len;
    char* url;
    time_t lru_time_track;
    cache_element* next;
};

cache_element* find(char* url );
int add_cache_element(char* data, int size, char* url);
void remove_cache_element();

int port_number = 8080;
int proxy_socketID;
pthread_t tid[MAX_CLIENTS];
//sem_t semaphore;
pthread_mutex_t lock;