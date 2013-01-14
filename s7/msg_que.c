#include<stdio.h>
#include<string.h>
#include<sys/msg.h>
struct mydata{
  int mtype;
  char message[25];
}mq;
void main(){
  int id,i,j;
  char rev[25],msg[25];
  key_t key;
  pid_t pid;
  key = ftok("filepath",'a');
  pid = fork();
  if(pid>0){//parent -sender
    printf("\n in  parent (-sender)");
    mq.mtype=2;
    id = msgget(key,IPC_CREAT|0666);
    printf("\ne netre the msg:");
    gets(mq.message);
    msgsnd(id,&mq,sizeof(mq.message),0);
    printf("\n the message send...\n");
    msgrcv(id,&mq,sizeof(mq.message),2,0);
    printf("\nThe mesage recvd:%s",mq.message);
    
  }else{//recvr - child
    printf("\nin child (recvr)");
    id=msgget(key,0666);
    msgrcv(id,&mq,sizeof(mq.message),2,0);
    strcpy(msg,mq.message);
    printf("\nRecvd :%s  %d",msg,strlen(msg));
    for(i=strlen(msg)-1,j=0;i>=0;i--,j++){
      rev[j]=msg[i];
      printf("\n %c  %c\n",msg[i],rev[j]);
    }
    rev[strlen(msg)]='\0';
    printf("\n %dRevers send:%s  %c",strlen(rev),rev,rev[2]);
    strcpy(mq.message,rev);
    msgsnd(id,&mq,sizeof(mq.message),0);
    
  }
}
