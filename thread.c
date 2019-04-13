#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct {
    pthread_t thread;
    int number;
} myT;

void * thread_function( void *ptr )
{   
    //int id = pthread_self(); outro metodo de pegar o id
    myT * mthread = (myT *) ptr;
    pthread_t thread = mthread->thread; 
    printf("Eu sou a Thread%d e meu id e: %u \n", mthread->number, (unsigned int) thread);

    return NULL;
}

int main()
{
    int N;
    printf("Digite o numero de threads:\n ");
    scanf("%d", &N);
    myT * threads = malloc(sizeof(myT) * N);
    
    for(int i = 0; i < N; i++){
        threads[i].number = i + 1;
        pthread_create(&threads[i].thread, NULL, thread_function, (void *) &threads[i]);
    }

    for(int i = 0; i < N; i++){
        pthread_join(threads[i].thread, NULL);
    }

    free(threads);
    exit(0);
}
