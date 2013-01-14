#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/stat.h>
#define MEMSIZE 27
void main(){
  key_t key;
  pid_t pid;
  int seg_id;
  int *shm_child,*shm_parent;
  int a,b,c,d,e,f,res1,res2;
  pid=fork();
  if(pid>0){//parent
    sleep(10);
    printf("\nEnter the value of a: ");
    scanf("  %d",&a);
    printf("\nEnter the value of b: ");
    scanf("  %d",&b);

    e=a*b;
    seg_id= shmget(key,MEMSIZE,IPC_CREAT|0666);
    if(seg_id==-1){
      printf("\nError in getting shm..");
    }
    printf("\n Got shm... :)");
    if((shm_parent=shmat(seg_id,NULL,0))==(int *)-1){
      printf("\nError in attatching  ");
    }
    *shm_parent = e;
    printf("\n The product a*b = %d ",*shm_parent);
    sleep(3);
  }else{//child
    
    printf("\nEnter the value of c : ");
    scanf("  %d",&c);
    printf("\nEnter the value of d : ");
    scanf("  %d",&d);
    f=c*d;
    printf(" \n product c*d = %d\n",f);
    sleep(10);
    seg_id = shmget(key,MEMSIZE,IPC_CREAT|0666);
    if(seg_id==-1){
       printf("\nError in getting shm..");
     }
    //sleep(4);
    if((shm_child = shmat(seg_id,NULL,0))==(int *)-1){
      printf("\nError in attatching ");
    }
    //sleep(5);
    //*shm_child = c*d;
    
    sleep(5);
    printf("\nThe result is a*b + c*d = %d\n",f+(*shm_child));
  }

}
