#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
void main(){
  char buf[100],str[50];
  int k,sock_desc,temp_sock_desc,len;
  struct sockaddr_in client,server;
  memset(&client,0,sizeof(client));
  memset(&server,0,sizeof(server));
  sock_desc = socket(AF_INET,SOCK_STREAM,0);
  if(sock_desc == -1){
    printf("\n Error socket creation..");
    exit(0);
  }
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_port=3001;
  k = bind(sock_desc,(struct sockaddr *)&server,sizeof(server));
  if(k==-1){
    printf("\n Error socket binding..");
    exit(0);
  }
  k = listen(sock_desc,20);
  if(k==-1){
    printf("\n Error socket listening..");
    exit(0);
  }
  len = sizeof(client);
  temp_sock_desc = accept(sock_desc,(struct sockaddr *)&client,&len);
  if(temp_sock_desc == -1){
    printf("\n Error socket accepting..");
    exit(0);
  }
  k = recv(temp_sock_desc,buf,100,0);
  if(k==-1){
    printf("\n Error in receiving..");
    exit(0);
  }
  printf("\n The message received in server is:%s",buf);
  close(temp_sock_desc);
  close(sock_desc);
}
