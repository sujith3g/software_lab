#include"sys/socket.h"
#include"netinet/in.h"
#include"stdio.h"
#include"string.h"
#include"stdlib.h"
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/sendfile.h>
int main(){
  char buf[100],length[100],line[100];
  int i,k,ch,filehandle,len;
int sock_desc;
 struct sockaddr_in client,server;

 //printf("\n Enter the data to be transmitted:");
 //gets(buf);
 memset(&client,0,sizeof(client));
 sock_desc = socket(AF_INET,SOCK_STREAM,0);
 if(sock_desc==-1){
   printf("\n Error creating socket..");
   exit(0);
 }
 client.sin_family = AF_INET;
 client.sin_addr.s_addr = INADDR_ANY;
 client.sin_port = 3001;
 k = connect(sock_desc,(struct sockaddr *)&client,sizeof(client));
 if(k == -1){
   printf("\n Error in conection..");
   exit(0);
 }
 while(1){
   printf("\nEnter your choice:\n1.LIST\n2.LOAD\n3.EXIT");
   scanf("%d",&ch);
   switch(ch){
   case 1:
     {
     strcpy(buf,"LIST");
     printf("\n LIST selected\n");
     k = send(sock_desc,buf,100,0); 
     if(k==-1){
       printf("\n Errror in sending..");
       exit(0);
     }
     k = recv(sock_desc,length,100,0); 
     if(k==-1){
       printf("\n Errror in sending..");
       exit(0);
     }
     len=atoi(length);
     filehandle = open("list2.txt",O_CREAT|O_RDWR,0700);
     while(i<len){
       k=recv(sock_desc,line,100,0);
       if(k==-1){
	 printf("\n Errror in recvng..");
	 exit(0);
       }
       write(filehandle,line,sizeof(line));
       system("cat list2.txt");
     }
     break;
   }
   }
 }

 k = send(sock_desc,buf,100,0); 
 if(k==-1){
   printf("\n Errror in sending..");
   exit(0);
 }
 close(sock_desc);
}
