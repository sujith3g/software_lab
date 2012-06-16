#include<stdio.h>
#include<string.h>
#include<ctype.h>
FILE *f3;
int issymbol(char a[50][3],int n,char c[3])
{
    int i;
    for(i=0;i<n;i++)
    {
	if(!strcmp(a[i],c))
	    return 1;
    }
    return 0;
}

main()
{
    FILE *f1,*f2,*f4;
    char key[50][15],sym[50][3],e[15],c,symb,symbol[3],string[100];
    int n=0,i,m=0,fnum=0;
    f1=fopen("keyword.txt","r+");
    f2=fopen("1pass.c","r+");
    f3=fopen("lanalyzeroutput.txt","w");
    f4=fopen("specialsymbols.txt","r+");
    while(!feof(f1))
    {
	fscanf(f1,"%s",&key[n]);
	n++;
    }
    while(!feof(f4))
    {
	fscanf(f4,"%s",&sym[m++]);
    }
    while(!feof(f2))
    {
	i=0;
	fscanf(f2,"%c",&c);
	if(c==EOF)
	    break;
	if(isalpha(c))
	{
	    e[i++]=c;
	    fscanf(f2,"%c",&c);
	    while(isalpha(c)||isdigit(c))
	    {		
		e[i++]=c;
		fscanf(f2,"%c",&c);
	    }
	    symb=c;
	    symbol[0]=c;
	    symbol[1]='\0';
	    e[i]='\0';
	    if(!issymbol(sym,m,symbol)&&!isspace(c)&&c!='\n'&&c!=0)
	    {
		printf("Error variable \t%s\t%d",symbol,symbol[0]);
		break;
	    }
	   
	    for(i=0;i<n;i++)
	    {
		if(!strcmp(key[i],e))
		{
		    printf("Keyword\t%s\n",key[i]);
		    fprintf(f3,"%s\tKeyword\n",e);
		    break;	    
		}
	    }
	    if(i==n)
	    {
		fprintf(f3,"%s\tVariable\n",e);
	    }
	}
	else
	{
	    while(isdigit(c))
	    {
		fnum=1;
		e[i++]=c;
		fscanf(f2,"%c",&c);
	    }
	    symb=c;
	    symbol[0]=c;
	    symbol[1]='\0';
	    e[i]='\0';
	    if(!issymbol(sym,m,symbol)&&!isspace(c)&&c!='\n'&&c!=0)
	    {
		printf("Error symbol \t%s\t%d",symbol,symbol[0]);
		break;
	    }
	    if(fnum)
	    {
		if(c!='+'&&c!='-'&&c!='/'&&c!='*'&&c!=';'&&c!=','&&c!=']'&&c!=')'&&c!='\''&&!isspace(c)||isalpha(c))
		{
		    printf("Error number\t%s\t%c\n",e,c);
		    exit(0);
		}
		fnum=0;
		fprintf(f3,"%s\tNumber\n",e);
		i=0;
	    }
	}
	if(!isspace(symb))
	{
	    if(symb=='"')
	    {
		fprintf(f3,"%c\tSymbol\n",symbol[0]);
		i=0;
		do
		{
		    fscanf(f2,"%c",&e[i++]);
		}
		while(e[i-1]!='"');
		e[i-1]='\0';
		fprintf(f3,"%s\tText\n",e);
		fprintf(f3,"\"\tSymbol\n");
		continue;
	    }
	    if(symb==';'||symb=='{'||symb=='}'||symb=='('||symb==')'||symb=='['||symb==']'||symb==','||symb=='\''||symb=='*')
	    {
		fprintf(f3,"%c\tSymbol\n",symbol[0]);
		continue;
	    }
	    fscanf(f2,"%c",&c);
	    symbol[1]=c;
	    symbol[2]='\0';
	    if(issymbol(sym,m,symbol))
		fprintf(f3,"%s\tSymbol\n",symbol);
	    else
	    {
		if(!isalpha(c)&&!isdigit(c)&&!isspace(c)&&c!='='&&symbol[0]!='='&&c!='\'')
		    
		{
		    printf("Error 2 n symbol\t%s\n",symbol);
		    exit(0);
		}
		fprintf(f3,"%c\tSymbol\n",symbol[0]);
		fseek(f2,-1,SEEK_CUR);
	    }	   
	}	 
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);   
}


	 
	
	    
	    
		      
	    
	    

    
