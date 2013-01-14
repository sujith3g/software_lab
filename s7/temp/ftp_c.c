#include "sys/socket.h"
#include "netinet/in.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"sys/sendfile.h"
#include"fcntl.h"

int main()
{	
	int sock_desc;
	int k,c,len,l,fh;
	char buff[100];
	char fil[100];
	struct sockaddr_in client;
	printf("[Client] Start . Next gets()\n");	
	strcpy(buff,"melwin");

	printf("[Client] initialisation OK . Next memset()\n");	
	memset(&client,0,sizeof(client));
	printf("[Client] memset() OK . Next socket()\n");	
	sock_desc=socket(AF_INET,SOCK_STREAM,0);
	printf("[Client] socket() OK . Next connet()\n");	
	client.sin_family=AF_INET;
	client.sin_addr.s_addr=INADDR_ANY;
	client.sin_port=3001;
	k=connect(sock_desc,(struct sockaddr *)&client,sizeof(client));
	printf("[Client] connet() OK . Next recv()\n");		
	k=recv(sock_desc,buff,100,0);
	printf("[Client] send() OK . Next close() %s \n",buff);
	

	fh=open("file.txt",O_RDWR|O_CREAT,0700);
	len=atoi(buff);
	c=0;
	while(c<len)
	{	l=read(sock_desc,fil,strlen(fil));
		if(l==0) break;
		write(fh,fil,strlen(fil));
	}
	
	close(sock_desc);
	exit(0);
	return 0;
}
