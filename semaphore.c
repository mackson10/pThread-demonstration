#define N 100
#include <stdlib.h>
#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h>
#include <time.h>

sem_t mutex;
int VET[N];

int primo(int numero){
    int i = 2, num = numero;
    while(i <= numero / 2){
        if(num % i == 0){
            num = num / i;
            return 0;
        }
        if(num % i != 0)
            i++;
    }
    return 1;
}

void moveVetorEsquerda(int start){
    for(int i = start - 1; i < N; i++){
        if(i == N - 1)
            VET[i] = 0;
        else
            VET[i] = VET[i + 1];
    }
}

void* retiraPar(void* arg) 
{
    sem_wait(&mutex);
    for(int i = 0; i < N && VET[i] != 0;){
        if(VET[i] % 2 == 0){
            moveVetorEsquerda(i + 1);
            
        }else{
            i++;
        }
    }
    sem_post(&mutex);
    return NULL;
}

void* retiraPrimo(void* arg)
{ 
    sem_wait(&mutex); 
    for(int i = 0; i < N && VET[i] != 0;){
        if(primo(VET[i]) == 1){
            moveVetorEsquerda(i + 1);
        }else{
            i++;
        }
    }
    sem_post(&mutex);
    return NULL; 
}

int main() 
{   
    srand(time(NULL));
    for(int i = 0; i < N; i++){
        VET[i] = 1 + rand() % 10;
    }
    
    //array antes 
    for(int i = 0;VET[i] != 0; i++){
        printf("%d - %d \n", VET[i], i);
    }
    printf("\n");

    sem_init(&mutex, 0, 1);
    pthread_t t1,t2;
    pthread_create(&t1, NULL, retiraPar, NULL);
    pthread_create(&t2, NULL, retiraPrimo, NULL); 
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    sem_destroy(&mutex);
    
    //array depois
    for(int i = 0;VET[i] != 0; i++){
	//if(VET[i] % 2 == 0 || primo(VET[i]) == 1)
        	printf("%d - %d \n", VET[i], i);
    }
    

    return 0;
}
