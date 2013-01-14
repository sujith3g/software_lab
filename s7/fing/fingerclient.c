#include<rpc/rpc.h>
#include<stdio.h>
#include "fing.h"
void err_quit(char *msg){
  printf("\n%s\n",msg);
  exit(1);
}
void main(int argc,char *argv[]){
  CLIENT *c1;
  finger_out *outp;
  if(argc!=2){
    err_quit("Error in usage");
    // printf("\nError..");
    // exit(0);
  }
  c1 = clnt_create(argv[1],FINGER,FINGER_VERSION,"tcp");
  if((outp = myfinger_1(NULL,c1))==NULL)
    err_quit("err1");
    //printf("\n error");
  printf("\n %s",outp->message);
}
