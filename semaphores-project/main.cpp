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
#include <ctime>
using namespace std;
#define TRUE 1

// functions used by threads to start exeucution
void *parent(void *);
void *producer(void *);
void *consumer(void *);

// Define Semaphore reference variables
sem_t empty;
sem_t full;
sem_t s;

// Buffer
string buffer = "";


int main(int argc, const char * argv[]) {
    srand(time(NULL));
    
    // Define parent thread
    pthread_t parent_id;
    
    // Initialize Semaphores
    sem_init(&empty, 0, 3);
    sem_init(&full, 0, 0);
    sem_init(&s, 0, 1);
    
    // Create Parent thread
    if(pthread_create(&parent_id, NULL, parent, (void *)NULL)) {
        printf("Error Creating Parent Thread\n");
    } else {
        printf("Parent Thread Created\n");
    }
    
    // Join Parent thread
    if(pthread_join(parent_id, NULL)) {
        printf("Error Joining Parent Thread\n");
    } else {
        printf("Parent Thread Joined");
    }
    
    // Destroy Semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&s);

    return 0;
}

void *parent(void *) {
    pthread_t producer_id, consumer_id;
    
    if(pthread_create(&producer_id, NULL, producer, NULL)) {
        printf("Error Creating Producer Thread\n");
    } else {
        printf("Producer Thread Created");
    }
    
    if(pthread_create(&consumer_id, NULL, consumer, NULL)) {
        printf("Error Creating Consumer Thread\n");
    } else {
        printf("Consumer Thread Created");
    }
    
    if(pthread_join(producer_id, NULL)) {
        printf("Error Joining Producer Thread\n");
    } else {
       printf("Producer Thread Joined\n");
    }
    
    if(pthread_join(consumer_id, NULL)) {
        printf("Error Joining Consumer Thread\n");
    } else {
        printf("Consumer Thread Joined\n");
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
    do {
        int num = rand() % 26;
        char letter = static_cast<char>('A' + num);
        printf("Producer produced: %c\n", letter);
        
        sem_wait(&empty);
        sem_wait(&s);
        
        buffer.push_back(letter);
        

        sem_post(&s);
        sem_post(&full);
        
        
    }while(TRUE);
    
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
    string c;
    do {
        sem_wait(&full);
        sem_wait(&s);
        
        
        c = buffer.back();
        int position = static_cast<int>(buffer.back()) - 64;
        buffer.pop_back();

        sem_post(&s);
        sem_post(&empty);
        
        if(position % 2 != 0){
            printf("Consumer consumed: %s\n", c.c_str());
        }
        if(position % 2 == 0 && position != -64) {
            printf("Consumer consumed: %s at position %d\n", c.c_str(), position);
        }
    }while(TRUE);
    

    return NULL;
}
























