#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
int expanding=0;
char deftab[80][30],line[100];
int dtop=0,argi=0,namei=0,sindex,dindex,di=0,ni=0;
char * dectohex(int a);
void assemble();
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
char c;
    f1=fopen("mplusainput.txt","r");
    f2=fopen("macrooutput1.txt","w");
    while(!feof(f1))
    {
	getline();
	processline();
    }
    fclose(f1);
    fclose(f2);
scanf("%c",&c);
assemble();
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
    char a[100],*t,tem[15],c,lab[15];
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
    c=0;
    i=0;
    while(c!='\t')
    {
	sscanf(line+i,"%c",&c);
	lab[i++]=c;
    }
    lab[i]='\0';
    fprintf(f2,".");
    fprintf(f2,"%s\n",line);
if(line[0]!='*')
     fprintf(f2,"%s\t*\n",lab);
    while(count++<dindex-2)
    {
	getline();
	processline();
    }
    expanding=0;
    }
void assemble()
{
 char opcode[10],optab1[20][10],symtab[20][10],symbol[10],operand[20],forw[20][10],ch,optab3[20][20],op1[5],c,opp[5],*loc,lo[5],val[5];
    int op,optab2[20],i=0,j=0,locctr=1000,k=0,value[20],opval,d,o=0,ii,lon,f=-1,kk,l,bl;
    FILE *prg,*optab,*out,*sym,*inter;
    prg=fopen("macrooutput1.txt","r");
    optab=fopen("optab","r");
    inter=fopen("pass2input.txt","w");
    out=fopen("mplusaoutput.txt","w+");
    sym=fopen("symbol","w");
    fclose(sym);
    sym=fopen("symbol","a");
    while(!feof(optab))
    {
	fscanf(optab,"%s",optab1[i]);
	fscanf(optab,"%s",optab3[i]);
	i++;
    }
    
    if(!feof(prg))
    {
	fscanf(prg,"%s",&symbol);
	fprintf(inter,"%s\t",symbol);
	if(strcmp("*",symbol))
	{
	    fscanf(prg,"%s",opcode);
	    fprintf(inter,"%s\t",opcode);
	}
	if(!strcmp("START",opcode))
	{
	    fscanf(prg,"%s",&lo);
	    locctr=hextodec(lo);
	    fprintf(inter,"%s",lo);
	}
	else
	{
	    printf("Error start");
	    exit(0);
	}
    }
    while(!feof(prg))
    {
	
	fscanf(prg,"%s",symbol);
	if(symbol[0]=='.')
	{
	    fgets(symbol,100,prg);
	    continue;
	}
	fprintf(inter,"\n%s\t",dectohex(locctr));
	fprintf(inter,"%s\t",symbol);
	if(strcmp("*",symbol))
	{
	    strcpy(symtab[k],symbol);
	    value[k]=locctr;
	    k++;
	    fprintf(sym,"%s\t%d",symtab[k-1],value[k-1]);
	}
	fscanf(prg,"%s",opcode);
fprintf(inter,"%s\t",opcode);
if(!strcmp(opcode,"*"))
{
continue;
}
	
        if(!strcmp("RESW",opcode))
	{
	    fscanf(prg,"%s",&val);
	    fprintf(inter,"%s",val);
	    locctr+=hextodec(val);
	}
else if(!strcmp("RESB",opcode))
	{
	     fscanf(prg,"%s",&val);
	    fprintf(inter,"%s",val);
	    locctr+=hextodec(val);
	}
	else if(!strcmp("WORD",opcode))
	{
	     fscanf(prg,"%s",&val);
	    fprintf(inter,"%s",val);
	    locctr+=3;
	}
	else if(!strcmp("BYTE",opcode))
	{
	    fscanf(prg,"%s",&val);
	    if(val[0]=='C')
		locctr+=strlen(val)-3;
	    else if(val[0]=='X')
		locctr+=(strlen(val)-3)/2;
		    fprintf(inter,"%s",val);  
	}

	 else if(!strcmp("END",opcode))
	{
	    break;
	}
	else
	{
	    
	    locctr+=3;
	    fscanf(prg,"%s",operand);
	    	fprintf(inter,"%s",operand);
	}
    }

    fclose(prg);
    fclose(inter);
    prg=fopen("pass2input.txt","r+");
    if(!feof(prg))
    {
	fprintf(out,"0000\t");
	fscanf(prg,"%s",&symbol);
	if(strcmp("*",symbol))
	{
	    fprintf(out,"%s\t",symbol);
	    fscanf(prg,"%s",opcode);
	    fprintf(out,"%s\t",opcode);
	}
	if(!strcmp("START",opcode))
	{
	    fscanf(prg,"%s",&lo);
	    locctr=hextodec(lo);
	}
	else
	{
	    printf("Error Start");
	    exit(0);
	}
	fprintf(out,"0\t");
    }

    while(!feof(prg))
    {
	fprintf(out,"\n");
	fscanf(prg,"%s",&lo);
	sprintf(opp,"%s",lo);
	l=strlen(opp);
	for(kk=0;kk<4-l;kk++)	    
	    fprintf(out,"%c",'0');
	fprintf(out,"%s\t",lo);
	fscanf(prg,"%s",symbol);
	fprintf(out,"%s\t",symbol);
	if(strcmp("*",symbol))
	{
	    fprintf(sym,"%s\t%d\n",symbol,locctr);
	}
	fscanf(prg,"%s",opcode);
	fprintf(out,"%s\t",opcode);
       
        if(!strcmp("RESW",opcode))
	{
	    fscanf(prg,"%s",&val);
	  	    fprintf(out,"%s\t*\t",val);
	}
	else if(!strcmp("RESB",opcode))
	{
	    fscanf(prg,"%s",&val);
	    fprintf(out,"%s",val);
	    continue;
	}
	else if(!strcmp("WORD",opcode))
	{
	    fscanf(prg,"%s",&val);
	    fprintf(out,"%s",val);
	    fprintf(out,"\t%6s",val);
	    continue;
	}
	else if(!strcmp("BYTE",opcode))
	{
	    fscanf(prg,"%s",&val);
	    fprintf(out,"%s\t",val);
	    l=strlen(val);
	    kk=0;
	    if(val[0]=='C')
	    {
		for(bl=2;bl<l-1;bl++)
		{  
		    fprintf(out,"%s",dectohex(val[bl]));   
		}
	    }
	    else if(val[0]=='X')
	    {
		for(bl=2;bl<l-1;bl++)
		{
		    fprintf(out,"%c",val[bl]);
		}
	    }
	    
	}
	else if(!strcmp("END",opcode))
	{
	    fprintf(out,"*\t*\t");
	    break;
	}
else if(!strcmp(opcode,"*"))
continue;
	else
	{
	    for(j=0;j<i;j++)
	    {
		if(!strcmp(optab1[j],opcode))
		{
		    strcpy(op1,optab3[j]);
		    break;
		}
	    }
	    if(j==i)
	    {
		printf("Error opcode\t%s\n",opcode);
		exit(0);
	    }
	    	    fscanf(prg,"%s",operand);

	    fprintf(out,"%s\t",operand);
	    fprintf(out,"%s",op1);
	    for(j=0;j<k;j++)
	    {
		if(!strcmp(symtab[j],operand))
		    break;
	    }
	    if(j==k)
	    {
		if(!strcmp(operand,"*"))
		{
		    fprintf(out,"0000");
		   continue;
		}
		printf("Error operand\t%s\n",operand);
		exit(0);
	    }
	    opval=value[j];
	    loc=dectohex(opval);
	    sprintf(opp,"%s",loc);
	    l=strlen(opp);
	    for(kk=0;kk<4-l;kk++)	    
		fprintf(out,"%c",'0');
	    fprintf(out,"%s",loc);
		
	}
    }
   
    fclose(sym);
    fclose(out);
exit(0);
}
char * dectohex(int a)
{
    int i=0,t=a,j,l;
    static char h[10];
    char c;
if(a==0)
{
h[0]='0';
h[1]='\0';
return h;
}
    while(t>0)
    {
	j=t%16;
	t/=16;
	if(j<10)
	    h[i++]=j+48;
	else
	    h[i++]=j+55;
    }
    h[i]='\0';
    for(l=0;l<i/2;l++)
    {
	c=h[l];
	h[l]=h[i-l-1];
	h[i-l-1]=c;
    }
    return h;
}
hextodec(char a[])
{
    int i,l,v=0;
    l=strlen(a);
    for(i=l-1;i>=0;i--)
    {
	if(a[i]<58)
	    v+=(a[i]-48)*pow(16,l-1-i);
	else
	    v+=(a[i]-55)*pow(16,l-1-i);
    }
    return v;
}
	    
	
		
		
	
    
    


	    
	
		
		
	
    

    
	
    
