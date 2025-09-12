#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

#define NUM_SATELLITES 5      
#define NUM_ENGINEERS 3       
#define MAX_CONNECTION_TIME 5 
#define MIN_PRIORITY 1        
#define MAX_PRIORITY 5

typedef struct Satellite {
    int id;                
    int priority;           
    time_t arrival_time;   
    sem_t request_handled;  
} Satellite;

typedef struct QueueNode {
    Satellite* satellite;
    struct QueueNode* next;
} QueueNode;

typedef struct PriorityQueue{
    QueueNode* head;
} PriorityQueue;

pthread_mutex_t engineerMutex;  
sem_t newRequest;               
int availableEngineers;         
PriorityQueue requestQueue;
bool engineersActive = true;

void initQueue(PriorityQueue* queue) {
    queue->head = NULL;
}

void cleanupQueue(PriorityQueue* queue) {
    QueueNode* current = queue->head;
    while (current != NULL) {
        QueueNode* temp = current;
        current = current->next;
        free(temp);
    }
    queue->head = NULL;
}

void assignRandomPriority(Satellite* satellite) {

    satellite->priority = (rand() % MAX_PRIORITY) + 1;
    
    char* type;
    switch(satellite->priority) {
        case 5:
            type = "Military";
            break;
        case 4:
            type = "Emergency";
            break;
        case 3:
            type = "Air Traffic";
            break;
        case 2:
            type = "Communication";
            break;
        case 1:
            type = "Commercial";
            break;
        default:
            type = "Unknown";
    }
    
    printf("Satellite %d: %s priority is assigned (level: %d)\n", 
           satellite->id, type, satellite->priority);
}

void enqueue(PriorityQueue* queue, Satellite* satellite) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->satellite = satellite;
    
    if (queue->head == NULL) {
        newNode->next = NULL;
        queue->head = newNode;
        return;
    }
    
    if (satellite->priority > queue->head->satellite->priority) {
        newNode->next = queue->head;
        queue->head = newNode;
        return;
    }
    
    QueueNode* current = queue->head;
    while (current->next != NULL && 
           current->next->satellite->priority >= satellite->priority) {
        current = current->next;
    }
    
    newNode->next = current->next;
    current->next = newNode;
}

Satellite* dequeue(PriorityQueue* queue) {
    if (queue->head == NULL) {
        return NULL; 
    }
    
    QueueNode* topNode = queue->head;
    Satellite* satellite = topNode->satellite;
    
    queue->head = topNode->next;
    free(topNode);
    
    return satellite;
}

void* satellite(void* arg) {
    Satellite* sat = (Satellite*)arg;
    
    assignRandomPriority(sat);
    sat->arrival_time = time(NULL);
    
    printf("Satellite %d (priority: %d) requesting connection.\n", sat->id, sat->priority);
    
    sem_init(&(sat->request_handled), 0, 0);
    
    pthread_mutex_lock(&engineerMutex);
    
    enqueue(&requestQueue, sat);
    printf("Satellite %d added to queue.\n", sat->id);
    
    pthread_mutex_unlock(&engineerMutex);
    
    sem_post(&newRequest);
    
    struct timespec timeout;
    clock_gettime(CLOCK_REALTIME, &timeout);
    timeout.tv_sec += MAX_CONNECTION_TIME;
    
    int result = sem_timedwait(&(sat->request_handled), &timeout);
    
    if (result == -1) {
        printf("Satellite %d: Connection timeout! Update aborted.\n", sat->id);
    } else {
        printf("Satellite %d: Engineer assigned, performing update.\n", sat->id);
        
        sleep(rand() % 3 + 1);
        
        printf("Satellite %d: Update completed.\n", sat->id);
    }
    
    sem_destroy(&(sat->request_handled));
    
    return NULL;
}

void* engineer(void* arg) {
    int id = *((int*)arg);
    Satellite* sat;
    
    printf("Engineer %d ready.\n", id);
    
    while (engineersActive) {
        sem_wait(&newRequest);
        
        if (!engineersActive) {
            break;
        }
        
        pthread_mutex_lock(&engineerMutex);
        
        if (availableEngineers > 0) {
            sat = dequeue(&requestQueue);
            
            if (sat != NULL) {
                availableEngineers--;
                printf("Engineer %d handling Satellite %d (priority: %d).\n", 
                       id, sat->id, sat->priority);
                
                pthread_mutex_unlock(&engineerMutex);
                
                sleep(rand() % 3 + 2);
                
                sem_post(&(sat->request_handled));
                
                pthread_mutex_lock(&engineerMutex);
                availableEngineers++;
                printf("Engineer %d is available again.\n", id);
                pthread_mutex_unlock(&engineerMutex);
            } else {
                pthread_mutex_unlock(&engineerMutex);
            }
        } else {
            pthread_mutex_unlock(&engineerMutex);
        }
    }
    
    printf("Engineer %d shutting down.\n", id);
    return NULL;
}

int main() {
    srand(time(NULL));
    
    pthread_mutex_init(&engineerMutex, NULL);
    sem_init(&newRequest, 0, 0);
    availableEngineers = NUM_ENGINEERS;
    initQueue(&requestQueue);
    
    pthread_t satelliteThreads[NUM_SATELLITES];
    pthread_t engineerThreads[NUM_ENGINEERS];
    
    Satellite satellites[NUM_SATELLITES];
    
    int engineerIds[NUM_ENGINEERS];
    
    // Create engineer threads
    for (int i = 0; i < NUM_ENGINEERS; i++) {
        engineerIds[i] = i;
        pthread_create(&engineerThreads[i], NULL, engineer, &engineerIds[i]);
    }
    
    for (int i = 0; i < NUM_SATELLITES; i++) {
        satellites[i].id = i;
        pthread_create(&satelliteThreads[i], NULL, satellite, &satellites[i]);
        
    }
    
    for (int i = 0; i < NUM_SATELLITES; i++) {
        pthread_join(satelliteThreads[i], NULL);
    }
    
    engineersActive = false;
    for (int i = 0; i < NUM_ENGINEERS; i++) {
        sem_post(&newRequest); 
    }
    
    for (int i = 0; i < NUM_ENGINEERS; i++) {
        pthread_join(engineerThreads[i], NULL);
    }
    
    cleanupQueue(&requestQueue);
    pthread_mutex_destroy(&engineerMutex);
    sem_destroy(&newRequest);
    
    printf("All satellites processed. Exiting program.\n");
    
    return 0;
}