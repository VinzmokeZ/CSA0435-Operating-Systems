#include <stdio.h> 
#include <pthread.h> 
 
#define NUM_THREADS 3 
 
void *thread_function(void *thread_id) {     
long tid = (long)thread_id;    
printf("Thread %ld created.\n", tid);    
pthread_exit(NULL); 
} 
 
int main() {    
pthread_t threads[NUM_THREADS]; 
    int i; 
 
    for (i = 0; i < NUM_THREADS; i++) {        
    pthread_create(&threads[i], NULL, thread_function, (void *)(intptr_t)(i + 1)); 
    } 
 
    for (i = 0; i < NUM_THREADS; i++) {       
    pthread_join(threads[i], NULL);        
    printf("Thread %d terminated.\n", i + 1); 
    } 
 
    return 0; 
}
