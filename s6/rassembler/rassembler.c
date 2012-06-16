#include<stdio.h>
#include<string.h>
#include<math.h>
char * dectohex(int a);
main()
{
    char opcode[10],optab1[20][10],symtab[20][10],symbol[10],operand[20],forw[20][10],ch,optab3[20][20],op1[5],c,opp[5],*loc,lo[5],val[5],head[25],text[99],end[10],sa[6],mod[100],ts[6];
    int op,optab2[20],i=0,j=0,locctr=1000,k=0,value[20],opval,d,o=0,ii,lon,f=-1,kk,l,cc,ti,pl=0,bl,mi=0,modi,b1;
    FILE *prg,*optab,*out,*sym,*inter,*ass;
    prg=fopen("rassemblerinput.txt","r");
    optab=fopen("optab","r");
    ass=fopen("rassembleroutput.txt","w");
    inter=fopen("pass2input.txt","w");
    out=fopen("assembleroutput.txt","w");
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
	    locctr+=3*hextodec(val);
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
	    strcpy(sa,lo);
	     fprintf(ass,"H^%6s^%6s^000000\n",symbol,lo);
	    locctr=hextodec(lo);
	}
	else
	{
	    printf("Error Start");
	    exit(0);
	}
	fprintf(out,"0\t");
    }
    text[0]='T';
    text[1]='^';
    cc=0;
    ti=16;
    while(!feof(prg))
    {
	fprintf(out,"\n");
	fscanf(prg,"%s",&lo);
	sprintf(opp,"%s",lo);
	if(ti==16)
	    strcpy(ts,lo);
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
	    continue;
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
	    if(ti+6>76+cc)
	    {
		text[ti-1]='\0';
		pl+=ti-16-cc;
		sprintf(text+2,"%6s",ts);
		text[8]='^';
		sprintf(text+9,"%2s",dectohex((ti-16-cc)/2));
		text[11]='^';
		for(b1=mi;b1<12;b1++)
		    mod[b1]='0';
		mod[b1]='\0';
		modi=bintodec(mod);
		sprintf(text+12,"%3s",dectohex(modi));
		text[15]='^';
		fprintf(ass,"%s\n",text);
		ti=16;
		cc=0;
		mi=0;
		strcpy(ts,lo);
	    }
	    l=strlen(val);
	    for(kk=0;kk<6-l;kk++)
	    {
		fprintf(out,"%c",'0');
		sprintf(text+ti++,"%c",'0');
	    }
	    sprintf(text+ti,"%s^",val);
	    ti=ti+l+1;
	    cc++;
	    mod[mi++]='0';
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
		    sprintf(op1+kk,"%s",dectohex(val[bl]));
		    kk+=2;
		}
	    }
	    else if(val[0]=='X')
	    {
		for(bl=2;bl<l-1;bl++)
		{
		    kk+=1;
		    fprintf(out,"%c",val[bl]);
		    sprintf(op1+kk-1,"%c",val[bl]);
		}
	    }
	    if(ti+kk>76+cc)
	    {
		text[ti-1]='\0';
		pl+=ti-16-cc;
		sprintf(text+2,"%6s",ts);
		text[8]='^';
		sprintf(text+9,"%2s",dectohex((ti-16-cc)/2));
		text[11]='^';
		for(b1=mi;b1<12;b1++)
		    mod[b1]='0';
		mod[b1]='\0';
		modi=bintodec(mod);
		sprintf(text+12,"%3s",dectohex(modi));
		text[15]='^';
		fprintf(ass,"%s\n",text);
		ti=16;
		cc=0;
		mi=0;
		strcpy(ts,lo);
	    } 
	    sprintf(text+ti,"%s^",op1);
	    ti=ti+strlen(op1)+1;
	    cc++;
	    mod[mi++]='0';
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
		printf("Error opcode: %s\n",opcode);
		exit(0);
	    }
	    fscanf(prg,"%s",operand);
	    fprintf(out,"%s\t",operand);
	    fprintf(out,"%s",op1);
	    if(ti+6>76+cc)
	    {
		text[ti-1]='\0';
		pl+=ti-16-cc;
		sprintf(text+2,"%6s",ts);
		text[8]='^';
		sprintf(text+9,"%2s",dectohex((ti-16-cc)/2));
		text[11]='^';
		for(b1=mi;b1<12;b1++)
		    mod[b1]='0';
		mod[b1]='\0';
		modi=bintodec(mod);
		sprintf(text+12,"%3s",dectohex(modi));
		text[15]='^';
		fprintf(ass,"%s\n",text);
		ti=16;
		cc=0;
		mi=0;
		strcpy(ts,lo);
	    }
	    sprintf(text+ti,"%s",op1);
	    ti=ti+strlen(op1);
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
		    {
			sprintf(text+ti,"0000");		
			ti=ti+5;
			text[ti-1]='^';
			cc++;
			mod[mi++]='0';
		    }
		    continue;
		}
		printf("Error Operand %s\n",operand);
		exit(0);
	    }
	    opval=value[j];
	    loc=dectohex(opval);
	    sprintf(opp,"%s",loc);
	    l=strlen(opp);
	    mod[mi++]='1';
	    for(kk=0;kk<4-l;kk++)
	    {
		fprintf(out,"%c",'0');
		sprintf(text+ti++,"%c",'0');
	    }
	    fprintf(out,"%s",loc);
	    sprintf(text+ti,"%s",loc);
	    ti=ti+strlen(loc)+1;
	    text[ti-1]='^';
	    cc++;
	}
    }
    text[ti-1]='\0';
    pl+=ti-16-cc;
    sprintf(text+2,"%6s",ts);
    text[8]='^';
    sprintf(text+9,"%2s",dectohex((ti-16-cc)/2));
    text[11]='^';
    for(b1=mi;b1<12;b1++)
	mod[b1]='0';
    mod[b1]='\0';
    modi=bintodec(mod);
    sprintf(text+12,"%s",dectohex(modi));
    text[15]='^';
    fprintf(ass,"%s\n",text);
    fprintf(ass,"E^%s\n",sa);
    fseek(ass,16,0);
    fprintf(ass,"%6s",dectohex(pl/2));
    fclose(ass);
    fclose(sym);
    fclose(out);
    fclose(prg);
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
bintodec(char *a)
{
    int v=0,i=0,l;
    l=strlen(a);
    for(i=0;i<l;i++)
	v+=(a[l-i-1]-48)*pow(2,i);
    return v;
}
	
	    
	
		
		
	
    
    
