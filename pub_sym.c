#include<stdio.h>
#include<pthread.h>

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

    pthread_mutex_lock(&mutex_mugs);

    if(free_mugs > 0){
        free_mugs--;
        printf("Customer %d took a mug. Free mugs: %d\n", id, free_mugs);
    } else {
        printf("Customer %d found no free mugs.\n", id);
    }

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