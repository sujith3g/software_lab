#include"sys/socket.h"
#include"netinet/in.h"
#include"stdio.h"
#include"string.h"
#include"stdlib.h"
int main(){
char buf[100];
int k;
 int sock_desc,currWindow,firstTime=1,winSize=3;
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
 strcpy(buf,"REQUEST");
 k = send(sock_desc,buf,100,0); 
 if(k==-1){
   printf("\n Errror in sending..");
   exit(0);
 }
 printf("\n Request Send... ");
 do{
   recv(sock_desc,buf,100,0);
   currWindow = atoi(buf);
   printf("\n Got packet %d",currWindow);
   winSize--;
   if(!winSize){
     sprintf(buf,"A%d",currWindow);
     winSize=3;
     printf("\nSend ack :%s",buf);
     send(sock_desc,buf,100,0);
   }

 }while(currWindow!=9);
 close(sock_desc);
}
