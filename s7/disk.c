#include<sys/statvfs.h>
#include<stdio.h>
#include<string.h>
void main(int argc,char *argv[]){
  struct statvfs data;
  int i;
  char path[128];
  if(argc<2){
    printf("\n Error");
  }
  for(i=1;i<argc;i++){
    strcpy(path,argv[i]);
    if(statvfs(path,&data))
      printf("\nError");
    printf("\n Disk %d",i);
    printf("\n Block size %lu",data.f_bsize);
  }
}
