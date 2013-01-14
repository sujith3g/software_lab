#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>
pthread_mutex_t chopstick[10];
pthread_t philosopher[10];
int n;
void *func(int i){
  printf("\n phil %d is thinking ",i+1);
  pthread_mutex_lock(&chopstick[i]);
  pthread_mutex_lock(&chopstick[(i+1)%n]);
  printf("\nphilo %d started eating",i+1);
  sleep(1);
  printf("\n phil %d finished eating",i+1);
  pthread_mutex_unlock(&chopstick[i]);
  pthread_mutex_unlock(&chopstick[(i+1)%n]);

}
void main(){
  
  int k,i;
  void *msg;
  ///printf("\nEnter the number of philosophers");
  n=5;
  for(i=0;i<n;i++)
    k=pthread_mutex_init(&chopstick[i],NULL);
  for(i=0;i<n;i++)
    k=pthread_create(&philosopher[i],NULL,(void*)func,(int *)i);
  for(i=0;i<n;i++)
    k = pthread_join(philosopher[i],&msg);
  for(i=0;i<n;i++)
    k = pthread_mutex_destroy(&chopstick[i]);
}
