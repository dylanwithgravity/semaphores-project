//
//  main.cpp
//  semaphores-project
//
//  Created by Dylan Williamson on 11/10/17.
//  Copyright © 2017 Dylan Williamson. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

void *parent(void *);
void *producer(void *);
void *consumer(void *);

sem_t empty = 3;
sem_t full = 0;
sem_t mutex = 1;
char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

int main(int argc, const char * argv[]) {
    
    pthread_t parent_id;
    
    if(pthread_create(&parent_id, NULL, parent, (void *)NULL)) {
       // printf("Error Creating Parent Thread\n");
    } else {
       // printf("Parent Thread Created\n");
    }
    
    if(pthread_join(parent_id, NULL)) {
        //printf("Error Joining Parent Thread\n");
    } else {
        //printf("Parent Thread Joined");
    }
    
    int n = rand() % 26;
    char c = (char)(n+65);
    cout << c << "\n";
    
    return 0;
}

void *parent(void *) {
    pthread_t producer_id, consumer_id;
    
    if(pthread_create(&producer_id, NULL, producer, NULL)) {
        //printf("Error Creating Producer Thread\n");
    } else {
       // printf("Producer Thread Created");
    }
    
    if(pthread_create(&consumer_id, NULL, consumer, NULL)) {
       // printf("Error Creating Consumer Thread\n");
    } else {
        //printf("Consumer Thread Created");
    }
    
    if(pthread_join(producer_id, NULL)) {
        //printf("Error Joining Producer Thread\n");
    } else {
       //printf("Producer Thread Joined\n");
    }
    
    if(pthread_join(consumer_id, NULL)) {
       // printf("Error Joining Consumer Thread\n");
    } else {
       // printf("Consumer Thread Joined\n");
    }
    
    return NULL;
}

void *producer(void *) {
/*
 Repeat
        .
        .
        Produce an item
        P(empty)
        P(mutex)
            .
            .
            Add item to buffer
            .
        V(mutex)
        V(full)
 Until false
 */
    
    return NULL;
}

void *consumer(void *) {
/*
 Repeat
     .
     .
     P(full)
     P(mutex)
     .
     .
     Remove item to buffer
     .
     V(mutex)
     V(empty)
        consume next item in buffer
Until false
     */

    return NULL;
}






















