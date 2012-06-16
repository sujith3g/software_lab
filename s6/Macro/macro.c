#include<stdio.h>
#include<string.h>
int expanding=0;
char deftab[80][30],line[100];
int dtop=0,argi=0,namei=0,sindex,dindex,di=0,ni=0;
FILE *f1,*f2;
typedef struct 
{
    char name[15];
    int start;
    int end;
} namt;
namt namtab[100];
typedef struct 
{
    char a[35][35];
}arg;
arg argtab[100];
main()
{
    f1=fopen("macroinput.txt","r");
    f2=fopen("macrooutput.txt","w");
    while(!feof(f1))
    {
	getline();
	processline();
    }
    fclose(f1);
    fclose(f2);
}
getline()
{
    char a[100],b[100],c;
    int p,i,t=0,l,l1,j;
    if(expanding)
    {
	strcpy(a,deftab[di++]);
	l=strlen(a);
	for(i=0;i<l;i++)
	{	    
	    if(a[i]=='?')
	    {
		p=a[++i]-49;
		l1=strlen(argtab[ni].a[p]);
		for(j=0;j<l1;j++)
		    b[t++]=argtab[ni].a[p][j];		
	    }
	    else
		b[t++]=a[i];
	}
	b[t]='\0';
	strcpy(line,b);
    }
    else
	do
	{
	    fgets(line,255,f1);
	}
	while(!feof(f1)&&line[0]==';');
}
processline()
{
    int i=0;
    char *t,linet[100];
    strcpy(linet,line); 
    t=strtok(linet,"\t");
    t=strtok(NULL,"\t");
    for(i=0;i<namei;i++)
    {
	if(!strcmp(namtab[i].name,t))
	{
	    sindex=namtab[i].start;
	    dindex=namtab[i].end;
	    di=sindex+1;
	    ni=i;
	    expand();
	    break;
	}
    }
    if(i==namei)
    {
	if(!strcmp(t,"MACRO"))
	    define();
	else
	    fputs(line,f2);
    }
}
define()
{
    char temp[35],proto[15][15],*t,opcode[15],c,tem[30],ar[10];
    int level=1,pi=0,l,i,j,k,l1;   
    sscanf(line,"%s",temp);
    l=strlen(temp);
    strcpy(namtab[namei].name,temp);
    namtab[namei].start=dtop;
    sscanf(line+l+1,"%s",temp);
    l1=strlen(temp);
    sscanf(line+l+1+l1,"%s",temp);
    strcpy(deftab[dtop++],temp);
    strcpy(tem,line+1+l1+1);
    l=strlen(tem);
    for(i=0;i<l;i++)
    {
	if(tem[i++]=='&')
	{
	    j=0;
	    while(isalpha(tem[i]))
		ar[j++]=tem[i++];
	    ar[j]='\0';
	    strcpy(proto[pi++],ar);
	}
    }
    while(level>0)
    {
	getline();
	if(line[0]==';')
	    continue;
	l=strlen(line);
	sscanf(line,"%s%s",opcode,opcode);
	k=0;	
	for(i=0;i<l;i++)
	{
	    if(line[i]=='&')
	    {
		j=0;
		i++;
		while(isalpha(line[i])||isdigit(line[i]))
		    temp[j++]=line[i++];
		i--;
		temp[j]='\0';		
		for(j=0;j<pi;j++)
		{
		    if(strcmp(proto[j],temp)==0)
			break;
		}
		deftab[dtop][k++]='?';
		deftab[dtop][k++]=j+49;
	    }
	    else
		deftab[dtop][k++]=line[i];
	}	
	dtop++;
	if(!strcmp(opcode,"MACRO"))
	    level++;
	else if(!strcmp(opcode,"MEND"))
	{
	    namtab[namei++].end=dtop;
	    level--;
	}
    }
}
expand()
{
    char a[100],*t,tem[15],c;
    int i=0,l,count=sindex,j=0,k;
    expanding=1;
    strcpy(a,deftab[sindex]);
    l=strlen(line);   
    while(line[i++]!='\t');
    while(line[i++]!='\t');
    k=0;
    for(;i<l;i++)
    {
	j=0;
	while(isalpha(line[i])||isdigit(line[i]))
	    tem[j++]=line[i++];
	i--;
	tem[j]='\0';
	strcpy(argtab[ni].a[k++],tem);
	i++;
    }
    fprintf(f2,".");
    fprintf(f2,"%s\n",line);
    while(count++<dindex-2)
    {
	getline();
	processline();
    }
    expanding=0;
}
    
	
    
    
		
	
	
	
    
    
    
    
    
    
    
    
    
    
		
		

	
	
	
	
	
	
	
	
    
