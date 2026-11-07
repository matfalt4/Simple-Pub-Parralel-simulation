#include<stdio.h>
#include<pthread.h>
#include<unistd.h> // header including sleep() func.
 
#define NUM_OF_CUST 10
#define NUM_OF_MUGS 5
#define NUM_OF_TAPS 3
#define BEERS_PER_CUST 2

int free_mugs = NUM_OF_MUGS;

pthread_mutex_t mutex_mugs = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_taps[NUM_OF_TAPS];

void* customer(void* arg){

    int id = *(int*)arg;

    printf("customer %d walked into the pub.\n", id);

    while(1){

        pthread_mutex_lock(&mutex_mugs);

        if(free_mugs > 0){
            free_mugs--;
            printf("Customer %d took a mug. Free mugs: %d\n", id, free_mugs);
            pthread_mutex_unlock(&mutex_mugs);
            break;
        }

        pthread_mutex_unlock(&mutex_mugs);
    }

    // Searching for a free tap
    int tap_id = -1;

    while(tap_id == -1){
        for(int i = 0; i < NUM_OF_TAPS; i++){

            if(pthread_mutex_trylock(&mutex_taps[i]) == 0){
                tap_id = i;
                break;
            }
        }
    }

    printf("Customer %d occupied tap %d.\n", id, tap_id);
    printf("Customer %d is pouring beer from tap %d.\n", id, tap_id);
    sleep(2); // pauses executing thread for a certain time in seconds

    pthread_mutex_unlock(&mutex_taps[tap_id]);
    printf("Customer %d realesed tap %d.\n", id, tap_id);

    printf("Customer %d is drinking beer.\n", id);
    sleep(3);

    pthread_mutex_lock(&mutex_mugs);

    free_mugs++;
    printf("Customer %d returned a mug. Free mugs: %d\n", id, free_mugs);

    pthread_mutex_unlock(&mutex_mugs);

    return NULL;
}

int main(void)
{

    pthread_t threads[NUM_OF_CUST];
    int ids[NUM_OF_CUST];

    for(int i = 0; i < NUM_OF_CUST; i++) ids[i] = i;

    for(int i = 0; i < NUM_OF_TAPS; i++)
        pthread_mutex_init(&mutex_taps[i], NULL);

    for(int i = 0; i < NUM_OF_CUST; i++)
        pthread_create(&threads[i], NULL, customer, &ids[i]);

    for(int i = 0; i < NUM_OF_CUST; i++)
        pthread_join(threads[i], NULL);

    printf("Every client finished the visit");

    for(int i = 0; i < NUM_OF_TAPS; i++)
        pthread_mutex_destroy(&mutex_taps[i]);

    return 0;
}
