#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS  4 //Numero de threads

// Variaveis globais
int x = 0;    //Variável correspondente a primeira condição
int y = 0;    //Variável correspondente a segunda condição
pthread_mutex_t mutex_x , mutex_y;  
pthread_cond_t cond1 , cond2;

// Thread 1 
void *a () {
    pthread_mutex_lock(&mutex_x);
    if(x==0){
        pthread_cond_wait(&cond1, &mutex_x);
    }
    printf("Fique a vontade.\n");
    pthread_mutex_unlock(&mutex_x);
    pthread_mutex_lock(&mutex_y);
    y++;
    if(y==2){
        pthread_cond_signal(&cond2);
    }
    pthread_mutex_unlock(&mutex_y);
    pthread_exit(NULL);
}

// Thread 2
void *b () {
    printf("Seja bem-vindo!\n");
    pthread_mutex_lock(&mutex_x);
    x++;
    pthread_cond_broadcast(&cond1);
    pthread_mutex_unlock(&mutex_x);
    pthread_exit(NULL);
}

// Thread 3
void *c (){
    pthread_mutex_lock(&mutex_y);
    if(y<2){
        pthread_cond_wait(&cond2,&mutex_y);
    }
    printf("Volte sempre!\n");
    pthread_mutex_unlock(&mutex_y);
    pthread_exit(NULL);
}

// Thread 4
void *d (){
    pthread_mutex_lock(&mutex_x);
    if(x==0){
        pthread_cond_wait(&cond1, &mutex_x);
    }
    printf("Sente-se por favor.\n");
    pthread_mutex_unlock(&mutex_x);
    pthread_mutex_lock(&mutex_y);
    y++;
    if(y==2){
        pthread_cond_signal(&cond2);
    }
    pthread_mutex_unlock(&mutex_y);
    pthread_exit(NULL);
}

// Funcao principal 
int main() {
  pthread_t threads[NTHREADS];

  // Inicializando os mutex e as condições que serão utilizados
  pthread_mutex_init(&mutex_x, NULL);
  pthread_mutex_init(&mutex_y, NULL);
  pthread_cond_init (&cond1, NULL);
  pthread_cond_init (&cond2, NULL);

  // Criando as Threads
  pthread_create(&threads[0], NULL, a, NULL);
  pthread_create(&threads[1], NULL, b, NULL);
  pthread_create(&threads[2], NULL, c, NULL);
  pthread_create(&threads[3], NULL, d, NULL);

  // Aguardando o término das threads
  for (int i = 0; i < NTHREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  // Desalocando variáveis e encerrando o programa
  pthread_mutex_destroy(&mutex_y);
  pthread_mutex_destroy(&mutex_y);
  pthread_cond_destroy(&cond1);
  pthread_cond_destroy(&cond2);
  return 0;
}
