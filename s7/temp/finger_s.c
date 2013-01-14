#include <stdio.h>
#include <stdlib.h>
#include "finger.h"
#include <rpc/rpc.h>

finger_out* myfinger_1_svc(void *dummy, struct svc_req *rqstp)
{
	static finger_out fo;
	char buffer[1024];
	system("finger > result.txt");
	FILE *fp = fopen("result.txt", "r");
	int i=0;
	while( !feof(fp) ){
		buffer[i++] = fgetc(fp);
	}
	buffer[i] = '\0';
	strcpy(fo.message, buffer);
	system("rm -f result.txt");
	return &fo;
}

