#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
void main(){
  int k,sock_desc,len,filehandle;
  char buf[100],length[100],line[100];
  struct sockaddr_in client;
  struct stat obj;

  client.sin_family = AF_INET;
  client.sin_port = 3001;
  sock_desc = socket();
}
