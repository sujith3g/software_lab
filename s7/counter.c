#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/io.h>
void main(){
  int i,addr=0x378;
  ioperm(addr,5,1);
  for(i=0;i<8;i=i<<1){
    outb(i,addr);
    sleep(4);
  }
}
