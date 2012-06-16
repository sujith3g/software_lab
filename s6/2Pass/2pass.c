#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
char * dectohex(int a);
main()
{
    char opcode[10],optab1[20][10],symtab[20][10],symbol[10],operand[20],forw[20][10],ch,optab3[20][20],op1[5],c,opp[5],*loc,lo[5],val[5];
    int op,optab2[20],i=0,j=0,locctr=1000,k=0,value[20],opval,d,o=0,ii,lon,f=-1,kk,l,bl;
    FILE *prg,*optab,*out,*sym,*inter;
    prg=fopen("2passinput.txt","r");
    optab=fopen("optab","r");
    inter=fopen("pass2input.txt","w");
    out=fopen("2passoutput.txt","w+");
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
//	    fscanf(prg,"%d",&locctr);
	    fscanf(prg,"%s",&lo);
	    locctr=hextodec(lo);
	    //printf("lo=%d\n",locctr);
	    fprintf(inter,"%s",lo);
	}
	else
	{
	    printf("Error");
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
	    printf("Error");
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
		printf("Error\n");
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
		printf("Error\n");
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
	    
	
		
		
	
    
    
