#include"sys/socket.h"
#include"netinet/in.h"
#include"stdio.h"
#include"string.h"
#include"stdlib.h"
int main(){
char buf[100];
int k;
int sock_desc;
 struct sockaddr_in client,server;

 printf("\n Enter the data to be transmitted:");
 gets(buf);
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
 k = send(sock_desc,buf,100,0); 
 if(k==-1){
   printf("\n Errror in sending..");
   exit(0);
 }
 close(sock_desc);
}
