#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
char * dectohex(int a);
struct listv
{
    int x;
    struct listv *next;
};
typedef struct listv lst;

struct list
{
    char a[50];
    struct  listv *next;
}listt[50];

main()
{
    char opcode[10],optab1[20][10],symtab[20][10],symbol[10],operand[20],forw[20][10],ch,optab3[20][20],op1[5],c,opp[5],*loc,lo[5],val[5];
    int op,optab2[20],i=0,j=0,locctr=1000,k=0,value[20],opval,d,o=0,ii,lon,f=-1,kk,l,bl;
    lst *tem;
    FILE *prg,*optab,*out,*sym;
    prg=fopen("1passinput.txt","r");
    optab=fopen("optab","r");
    out=fopen("1passoutput.txt","w+");
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
	fprintf(out,"0000\t");
	fscanf(prg,"%s",&symbol);
	fprintf(out,"%s\t",symbol);
	if(strcmp("*",symbol))
	{
	    fscanf(prg,"%s",opcode);
	    fprintf(out,"%s\t",opcode);
	}
	if(!strcmp("START",opcode))
	{ 
	fscanf(prg,"%s",&lo);
	    locctr=hextodec(lo);

	    fprintf(out,"%s\t",lo);
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
	
	fscanf(prg,"%s",symbol);
	if(symbol[0]=='.')
	{
	    fgets(symbol,100,prg);
	    continue;
	}
	fprintf(out,"\n%s\t",dectohex(locctr));
	fprintf(out,"%s\t",symbol);
	if(strcmp("*",symbol))
	{
	    strcpy(symtab[k],symbol);
	    value[k]=locctr;
	    k++;
	    fprintf(sym,"%s\t%d\n",symtab[k-1],value[k-1]);
	}
	fscanf(prg,"%s",opcode);
	fprintf(out,"%s\t",opcode);
        if(!strcmp("RESW",opcode))
	{
	    fscanf(prg,"%s",&val);
	    locctr+=hextodec(val);
	    fprintf(out,"%s\t*\t",val);
	}
	else if(!strcmp("RESB",opcode))
	{
	     fscanf(prg,"%s",&val);
	    fprintf(out,"%s",val);
	    locctr+=hextodec(val);
	}
	else if(!strcmp("WORD",opcode))
	{
	     fscanf(prg,"%s",&val);
	    fprintf(out,"%s",val);
	    fprintf(out,"\t%6s",val);
	     locctr+=3;

	}
	else if(!strcmp("BYTE",opcode))
	{
	    fscanf(prg,"%s",&val);
	    fprintf(out,"%s",val);
	    if(val[0]=='C')
	    {
		for(bl=2;bl<l-1;bl++)
		{  
		    fprintf(out,"%s",dectohex(val[bl]));   
		}
		locctr+=strlen(val)-3;
	    }
	    else if(val[0]=='X')
	    {
		for(bl=2;bl<l-1;bl++)
		{
		    fprintf(out,"%c",val[bl]);
		}
		locctr+=(strlen(val)-3)/2;
	    }
	}
	 else if(!strcmp("END",opcode))
	{
	    fprintf(out,"*\t*\t");
	    break;
	}
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
		printf("Error Opcode\t%s\n",opcode);
		exit(0);
	    }
	    locctr+=3;
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
		for(ii=0;ii<o;ii++)
		{
		    if(!strcmp(listt[ii].a,operand))
			break;
		}
		if(ii==o)
		{
		    strcpy(listt[o++].a,operand);
		    lon=ftell(out);
		    listt[o-1].next=(lst*)malloc(sizeof(lst));
		    (listt[o-1].next)->x=lon;
		    (listt[o-1].next)->next=NULL;
		}
		else
		{
		    tem=listt[o-1].next;
		     lon=ftell(out);
		    while(tem->next!=NULL)
			tem=tem->next;
		    tem->next=(lst*)malloc(sizeof(lst));
		    tem->next->x=lon;
		    tem->next->next=NULL;
		}
		fprintf(out,"0000");
		continue;
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
    for(j=0;j<o;j++)
    {
	for(k=0;k<i;k++)
	{
	    if(!strcmp(symtab[k],listt[j].a))
	    {
		tem=listt[j].next;
		loc=dectohex(value[k]);
		while(tem!=NULL)
		{
		    fseek(out,tem->x,SEEK_SET);
		    sprintf(opp,"%s",loc);
		    l=strlen(opp);
		    for(kk=0;kk<4-l;kk++)
			fprintf(out,"%c",'0');
		    fprintf(out,"%s",loc);
		    strcpy(opp,"");		   
		    tem=tem->next;
		}
		break;
	    }
	}
	if(k==i)
	{
	    printf("Error\t%s\n",listt[j].a);
	    exit(0);
	}
    }
    fclose(sym);
    fclose(out);
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
	
