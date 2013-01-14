#include<rpc/rpc.h>
#include<stdio.h>
#include"fing.h"
#include<stdlib.h>
finger_out * myfinger_1_svc(void *dummy, struct svc_req *rqstp){
  static finger_out fo;
  char buf[1024];
  int i=0;
  system("ls > result.txt");
  FILE *fp = fopen("result.txt","r");
  while(!feof(fp)){
    buf[i++]=fgetc(fp);
  }
  buf[i]='\0';
  strcpy(fo.message,buf);
  system("rm -f result.txt");
  return &fo;
}
