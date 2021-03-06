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
        printf("Parent Thread Joined\n");
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
        printf("Producer Thread Created\n");
    }
    
    if(pthread_create(&consumer_id, NULL, consumer, NULL)) {
        printf("Error Creating Consumer Thread\n");
    } else {
        printf("Consumer Thread Created\n");
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
        char ran_letter = static_cast<char>('A' + num);
        printf("Producer produced: %c\n", ran_letter);
        
        sem_wait(&empty);
        sem_wait(&s);
        
        buffer.push_back(ran_letter);
        

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
            printf("Consumer: %s\n", c.c_str());
        }
        if(position % 2 == 0 && position != -64) {
            char letter = c.front();
            string s;
            string t;
            char v1 = ' ';
            char v2 = ' ';

            int v1_distance;
            int v2_distance;
            
            
            
            switch(letter) {
                case 'B':
                case 'D':
                    v1 = 'A';
                    v2 = 'E';
                    break;
                case 'F':
                case 'H':
                    v1 = 'E';
                    v2 = 'I';
                    break;
                case 'J':
                case 'L':
                case 'N':
                    v1 = 'I';
                    v2 = 'O';
                    break;
                case 'P':
                case 'R':
                case 'T':
                    v1 = 'O';
                    v2 = 'U';
                    break;
                case 'V':
                case 'X':
                case 'Z':
                    v1 = 'U';
                    v2 = 'A';
                    break;
                    
            }
            
            s.push_back(v1);
            s += letter;
            s.push_back(v2);
            
            v1_distance = (static_cast<int>(letter) - 64) - (static_cast<int>(v1) - 64);
            v2_distance = (static_cast<int>(v2) - 64) - (static_cast<int>(letter) - 64);
            
            if(letter == 'V' || letter == 'X' || letter == 'Z'){
                int vowelA = 27;
                v2_distance = vowelA - (static_cast<int>(letter) - 64);
                
            }
            if(v1_distance == v2_distance) {
                t.push_back(v2);
                t += s;
                t.push_back(v2);
                printf(" c: %c, v1: %c, v2: %c, S: %s, T: %s, Distance of c from v1: %d, Distance of c from v2: %d, Distance are the same\n", letter, v1, v2, s.c_str(), t.c_str(), v1_distance, v2_distance);
            }else if(v1_distance < v2_distance) {
                t.push_back(v2);
                t += s;
                t.push_back(v2);
                printf(" c: %c, v1: %c, v2: %c, S: %s, T: %s, Distance of c from v1: %d, Distance of c from v2: %d, Larger of the two %c\n", letter, v1, v2, s.c_str(), t.c_str(), v1_distance, v2_distance, v2);
            }else {
                t.push_back(v1);
                t += s;
                t.push_back(v1);
                printf(" c: %c, v1: %c, v2: %c, S: %s, T: %s, Distance of c from v1: %d, Distance of c from v2: %d, Larger of the two %c\n", letter, v1, v2, s.c_str(), t.c_str(), v1_distance, v2_distance, v1);
            }
        }
    }while(TRUE);
    

    return NULL;
}
























