#include<stdio.h>
#include<string.h>
#include<stdlib.h>
FILE *fin,*fout,*optab,*finter;
int sindex=0,start,locctr,exe;
struct node{
  unsigned int addrs;
  struct node *link;
}*ptr,*newptr,*tmp,*frwrd;
struct sym{
  char symbol[20];
  int val;
  struct node *link;
}symtab[99];
void insertSym(char s[],int val)
{
  strcpy(symtab[sindex].symbol,s);
  symtab[sindex].val = val;
  sindex++;
}
int readline(char *label,char*opcode,char *operand,char *l)
{
  char line[80];
  int fetch;
  label[0]='\0';
  opcode[0]='\0';
  operand[0]='\0';
  fgets(line,81,fin);
  strcpy(l,line);
  fetch = sscanf(line,"%s %s %s",label,opcode,operand);
  if(fetch == 1)
    {
      strcpy(opcode,label);
      return fetch;
    }
  if(fetch == 2)
    {
      strcpy(operand,opcode);
      strcpy(opcode,label);
      //address=0;
      return fetch;
    }
  else return fetch;
}
void addlinks(char symbol[],int value)
{
  int i=0;
  for(i=0;i<sindex;i++)
    if(strcmp(symtab[i].symbol,symbol)==0) break;
  newptr = (struct node*)malloc(sizeof(struct node));
  newptr->addrs=value;
  newptr->link=NULL;
  if(symtab[i].link==NULL) {
symtab[i].link=newptr;
// printf("\naddrs:%X\n",newptr->addrs);
  }
  else{

    ptr = symtab[i].link;
    for(tmp = ptr;tmp!=NULL;ptr=tmp,tmp=tmp->link);
    ptr->link=newptr;
  }
}
int searchsymtb(char *label)
{
  int i=0,f=0;
  for(i=0;i<99;i++)
    {
      if(strcmp(symtab[i].symbol,label)==0)
	{
	  return symtab[i].val;
	}
    }
  return -2;
}
struct node* setsymbol(char label[],int val)
{
  struct node *p;
  int i;
  for(i=0;i<sindex;i++)
    {
      if(strcmp(label,symtab[i].symbol)==0)
	{
	  symtab[i].val=val;
	  p = symtab[i].link;
	  symtab[i].link=NULL;
	  return p;
	}
     
    }
  return p;
}
void tohexa(char label[],unsigned int *hexa)
{
  sscanf(label,"%x",hexa);
  //printf("\n%x\n",*hexa);
  /* FILE *f1;
  f1 = fopen("tohexa.txt","r+w+");
  fprintf(f1,"%X",atoi(label));
  rewind(f1);
  fscanf(f1,"%X",hexa);
  fclose(f1);*/

}
void tostr(unsigned int hexa,char str[])
{

sprintf(str,"%.4X",hexa);

  /*FILE *f1;
 fprintf(f1,"%X",hexa);  rewind(f1);
  fscanf(f1,"%s",str);
  fclose(f1);*/
}
int searchoptb(char *op,char *mcode)
{
  char line[99],opcode[20];
  int flag=0;
  rewind(optab);
  while(!feof(optab))
    {
      fgets(line,99,optab);
      sscanf(line,"%s %s",opcode,mcode);
      if(strcmp(opcode,op)==0)
	{
	  flag =1;
	  return 1;
	}
    }
  if(flag==0)
    return -1;
}
main(int argc,char *argv[])
{
  
  int ch=1,addrs,fetch,eflag=0,searchI=0,exec=0;
  unsigned int tmp;
  char in[20],line[99],opcode[20],label[20],operand[20],mCode[20],infile[20],outfile[20];
  char proname[25],head[19],text[69],end[7],hexaval[10],objCode[15];
  strcpy(infile,"input.txt");
  strcpy(outfile,"output.txt");
  fin=fopen(infile,"r+");
  fout=fopen(outfile,"w+");
  finter = fopen("inter.txt","w+");
  optab = fopen("optab.txt","r+");
  fetch = readline(label,opcode,operand,line);

  //FOR reading in put from user to file
  /* do{ 
  gets(in);
  fputs(in,fin);
  fputs("\n",fin);

  }while(strcmp(in,"END")!=0);
  rewind(fin);*/
  
  if(fetch > 0)
    {
      if(fetch==2)
	{
	  strcpy(label,opcode);
	  strcpy(opcode,operand);
	}
      if(strcmp(opcode,"START")==0)
	{
	  strcpy(proname,label);
	  if(fetch==3)
	    {
	    tohexa(operand,&tmp);
	    locctr=tmp;
	    start = locctr;
	    }
	  else locctr=0x0;
	  /* fprintf(fout,"%s\n","                   ");
	  strcpy(head,"H");
	  strcat(head,proname);
	  strcat(head,"00");
	  //printf("\n%X %d\n",start,start);
	  tostr(start,hexaval);
	  strcat(head,hexaval);
	  printf("\n%s\n",head);*/
	  tostr(locctr,hexaval);
	  fprintf(finter,"\n%s ",hexaval);
	  fprintf(finter,"%s ",line);
	  fetch = readline(label,opcode,operand,line);
	  
	}
      
   while(strcmp(opcode,"END")!=0)
     {
 
       if(opcode[0]!='.')//if this is not a comment line
	 {
	   if(fetch==3)//there is a label
	     {
	       if(searchsymtb(label) != -2)//found in symtab
		 {
		   /*if(searchsymtb(label)== -1)
		     {
		       frwrd = setsymbol(label,locctr);
		       printf("\nfrwrd %s\n",text);
		       while(frwrd!=NULL)
			 {
			   strcpy(text,"T00");
			   tostr(frwrd->addrs,hexaval);
			   strcat(text,hexaval);
			   strcat(text,"02");
			   tostr(locctr,hexaval);
			   strcat(text,hexaval);
			   printf("\n%s\n",text);
			   text[0]='\0';
			   frwrd=frwrd->link;
			 }
			 }*/
		   eflag=1;
		   printf("error at %d ",locctr);
		 }
	       else{//if symbol not defined
		 // printf("not found");
		  if(eflag==0)
		    {
		      insertSym(label,locctr);
		      //strcpy(symtab[sindex].symbol,label);
		      //strcpy(symtab[sindex].val,operand);
		      // symtab[sindex++].addrs = locctr;
		    }
		  // printf("\n%s",symtab[sindex-1].symbol);
		  //printf(" \nopcode_srch:%d mcode:%s",searchoptb(opcode,mCode),mCode);
	       }
	     }//end if there is a label
	   if(searchoptb(opcode,mCode) == 1)//opcode found in optab
	     {
	       /*objCode[0]='\0';
	       exec++;
	       if(exec==1)
		 exe=locctr;
	       if(strlen(text)==69)
		 {
		   printf("\n%s\n",text);
		   text[0]='\0';
		   }*/
	       // printf("\nfound opcd:%s",mCode);
	       //strcpy(objCode,mCode);
	       /*if(fetch == 2 || fetch == 3)//there is an operand
		 {
		   searchI=searchsymtb(operand);
		   /* if( searchI != -2)//operand found in symtab
		     {
		       //if sym value not null replace opAddress with value
		       tostr(searchI,hexaval);
		       strcat(objCode,hexaval);
		       }
		   else{//operand not found in symtab
		     // strcat(objCode,"0000");
		     // insertSym(operand,-1);
		     //addlinks(operand,locctr+1);
		     // printf("\nadd link%d\n",symtab[sindex-1].link->addrs);
		     //insert operand to symtab
		     }*/
	       //}//end of if there is an operand
	       
	       //printf("\n%s\n",text);
	       locctr+=3;
	     } //end of if opcode found
	   else if(strcmp(opcode,"WORD")==0){ 
	     //eflag=1;
	     ///printf("\nUndefined opcode..");

	   }
	   else if(strcmp(opcode,"RESW")==0){
	    tostr(atoi(operand),hexaval);
	     tohexa(hexaval,&tmp);    
	     locctr+=tmp*3;
	   }
	   else if(strcmp(opcode,"RESB")==0){
	      tostr(atoi(operand),hexaval);
	     tohexa(hexaval,&tmp);    
	     locctr+=tmp;
	   }
	   else if(strcmp(opcode,"BYTE")==0){
	    
	   }
	   else{//opcode not found
	     eflag=1;
	   }
	 }//end of this is not a comment 
       else
	 {
	   //printf("%s",opcode);
	 }
       tostr(locctr,hexaval);
       fprintf(finter,"\n%s ",hexaval);
       fprintf(finter,"%s ",line);
       fetch = readline(label,opcode,operand,line);
     }//end of while not 'END'
   tostr(locctr,hexaval);
   fprintf(finter,"\n%s ",hexaval);
   fprintf(finter,"%s ",line);
   /* printf("\n%s\n",text);
   strcpy(end,"E00");
   tostr(exe,hexaval);
   strcat(end,hexaval);
   printf("\n%s\n",end);*/
    }//end of if(fetch>0       =========END OF PASS1==========
     //printf("locctr=%d",locctr);
  rewind(finter);
  fclose(fout);
  fclose(fin);
  fclose(finter);
}
/*main()
{

}*/
