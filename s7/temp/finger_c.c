#include <rpc/rpc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "finger.h"

void err_quit(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}
int main(int argc, char* argv[])
{
	CLIENT *c1;
	finger_out *outp;
	if(argc!=2)
		err_quit("usage: client <hostname>");
	
	c1 = clnt_create(argv[1], FINGER, FINGER_VERSION, "tcp");
	
	if( (outp=myfinger_1(NULL, c1))==NULL )
		err_quit(clnt_sperror(c1, argv[1]));

	printf("result: %s\n", outp->message);
	exit(0);
}

