#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/sendfile.h>
#include<sys/stat.h>
#include<fcntl.h>
void main(){
  char buf[100],str[50],length[100],line[100];
  int k,sock_desc,temp_sock_desc,len,filehandle;
  struct sockaddr_in client,server;
  struct stat obj;
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
  while(1){
    k = recv(temp_sock_desc,buf,100,0);
    if(k==-1){
      printf("\n Error in receiving..");
      exit(0);
    }
    if(strcmp(buf,"LIST")==0){//case 1 LIST
      system("ls -al > list.txt");
      filehandle = open("list.txt",O_RDONLY);
      stat("list.txt",&obj);
      sprintf(length,"%d",(int)obj.st_size);
      k=send(temp_sock_desc,length,sizeof(length),0);
      if(k==-1){
	printf("\n Error in sending..");
	exit(0);
      }
      k=sendfile(temp_sock_desc,filehandle,NULL,obj.st_size);
      if(k==-1){
	printf("\n Error in send file..");
	exit(0);
      }
    }
  }
  //  printf("\n The message received in server is:%s",buf);

  close(temp_sock_desc);
  close(sock_desc);
}
