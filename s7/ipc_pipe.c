#include<stdio.h>
#include<stdlib.h>
void main(){
  int pipe_pointer[2];
  char message[25] ;
  pid_t pid;
  if(pipe(pipe_pointer)==-1){
    printf("\n error pipe error...");
  }
  if( (pid = fork())==-1){
    printf("\nError in fork...:(");
  }
  if(pid==0){//child
    printf("\nIn child\n");
    printf("\nEnter the message (sender):");
    scanf("%s",message);
    close(pipe_pointer[0]);//close read end
    write(pipe_pointer[1],message,sizeof(message));
    close(pipe_pointer[1]);
  }else{//parent
    close(pipe_pointer[1]);
    read(pipe_pointer[0],message,sizeof(message));
    printf("\nin paret (receiver):\n");
    printf("\nMessage received:%s",message);
    close(pipe_pointer[0]);
    
  }
}
