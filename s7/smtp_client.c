#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>
#include<string.h>
int main(){
  char buf[100];
  int k,i=1;
  int sock_desc; 
  struct sockaddr_in server;

  memset(&server,0,sizeof(server));
  sock_desc = socket(AF_INET,SOCK_DGRAM,0);
  if(sock_desc==-1){
    printf("\n Error in creating socket..");
    exit(0);
  }
  server.sin_family=AF_INET;
  server.sin_addr.s_addr=inet_addr("127.0.0.1");
  server.sin_port=3002;
  //  while(1){
  printf("\n MAIL to:");
  gets(buf);
  //sprintf(buf,"Data packet %d",i);
    k=sendto(sock_desc,buf,100,0,(struct sockaddr *)&server,sizeof(server));
    if(k == -1){
      printf("\nError in sending data...");
      exit(0);
    }
    strcpy(buf,"\0");
    printf("\nMAIL from:");
    gets(buf);
    k=sendto(sock_desc,buf,100,0,(struct sockaddr *)&server,sizeof(server));
    if(k == -1){
      printf("\nError in sending data...");
      exit(0);
    }
    strcpy(buf,"\0");
    printf("\nSUBJECT:");
    gets(buf);
    k=sendto(sock_desc,buf,100,0,(struct sockaddr *)&server,sizeof(server));
    if(k == -1){
      printf("\nError in sending data...");
      exit(0);
    }
    strcpy(buf,"\0");
    printf("\nMessage Body:");
    while(strcmp(buf,".")!=0){
      strcpy(buf,"\0");
      gets(buf);
      k=sendto(sock_desc,buf,100,0,(struct sockaddr *)&server,sizeof(server));
      if(k == -1){
	printf("\nError in sending data...");
	exit(0);
      }
    }
    /*sleep(1);
    if(i>=5){
      strcpy(buf,"end");
      k=sendto(sock_desc,buf,100,0,(struct sockaddr *)&server,sizeof(server));
      break;
    }
    i++;*/
    //}
  close(sock_desc);
  printf("\n client socket closed...");
  exit(0);
  
}
