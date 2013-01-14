#include"sys/socket.h"
#include"netinet/in.h"
#include"stdio.h"
#include"string.h"
#include"stdlib.h"
int main(){
  char buf[100],id[2];
  int k,i=1;
 int sock_desc,flag=0,num,pid;
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
 client.sin_addr.s_addr = inet_addr("127.0.0.1");
 client.sin_port = 3001;
 k = connect(sock_desc,(struct sockaddr *)&client,sizeof(client));
 if(k == -1){
   printf("\n Error in conection..");
   exit(0);
 }
 //while(1){
   if(flag==0 && i<2){
     printf("\nEnter the next packet number:");
     scanf("%d",&i);
   }else i++;
   if(i>2){
     //break;
     printf("\ne break ;");
   }
   printf("\nEnter data packet%d to be sent:",i);
   scanf("%s",buf);
   id[0]=i;
   id[1]='\0';
   k=send(sock_desc,id,sizeof(id),0);
   if(k==-1){
     printf("\n Errror in sending..");
     exit(0);
   }
   k=recv(sock_desc,id,sizeof(id),0);
   if(k==-1){
     printf("\n Errror in  receiving.......");
     exit(0);
   }
   if(id[0]=='~'){
     printf("\n recvd %s",id);
     k=send(sock_desc,buf,sizeof(buf),0);
     if(k==-1){
       printf("\n Errror in sending..");
       exit(0);
     }
     sleep(2);
     strcpy(buf,"\0");
     k=recv(sock_desc,buf,sizeof(buf),0);
     if(k==-1){
       printf("\n Errror in  receiving.......");
       exit(0);
     }
     printf("\n %s by server..",buf);
   }
   
   //}
 //k = send(sock_desc,buf,100,0); 
 
 close(sock_desc);
}
