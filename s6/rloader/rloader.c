#include<stdio.h>
#include<math.h>
#include<string.h>
char *dectobin(int a);
char *dectohex(int a);
main()
{
    FILE *f1,*f2;
    char a[100],c,*p,fl[12],*t;
    int i,l,loc,ploc,sloc=4096,lc=0,f,d;
    f1=fopen("rloaderinput.txt","r+");
    f2=fopen("rloaderoutput.txt","w+");
    fgets(a,100,f1);
    p= strtok(a,"^");
    if(a[0]=='H')
    {
	p=strtok(NULL,"^");
	fprintf(f2,"Program Name: %s\n",p);
	p=strtok(NULL,"^");
	loc=ploc=lc=hextodec(p);
	fprintf(f2,"Program Starting Address: %s\n",p);
	fprintf(f2,"Program Length: %s\n\n",strtok(NULL,"\n"));
    }
    fgets(a,100,f1);
    strtok(a,"^");
    while(a[0]!='E')
    {
	p=strtok(NULL,"^");
	loc=hextodec(p);
	while(loc>lc)
	    lc++;   
	l=hextodec(strtok(NULL,"^"));
	f=hextodec(strtok(NULL,"^"));
	strcpy(fl,dectobin(f));
	for(i=0;i<l/3;i++)
	{
	    if(fl[i]==48)
	    {
		p=strtok(NULL,"^");
		fprintf(f2,"%s: %s\n",dectohex(lc),p);
		lc+=strlen(p)/2;
	    }
	    else
	    {
		p=strtok(NULL,"^");
		t=dectohex(lc+sloc);
		fprintf(f2,"%s: %s\n",t,p);
		lc+=strlen(p)/2;
	    }
	}
	fgets(a,100,f1);  
	strtok(a,"^");
    }
    fclose(f1);
    fclose(f2);
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
	if(a[i]<58&&a[i]>47)
	    v+=(a[i]-48)*pow(16,l-1-i);
	else if(a[i]>58)
	    v+=(a[i]-55)*pow(16,l-1-i);
    }
    return v;
}
char *dectobin(int a)
{
    int v=0,i=0,l;
    char c;
    static char b[100];
    if(a==0)
    {
	b[0]='0';
	b[1]='\0';
	return b;
    }
    while(a>0)
    {
	b[i++]=a%2+48;
	a=a/2;
    }
    b[i]='\0';
    for(v=0;v<i/2;v++)
    {
	c=b[v];
	b[v]=b[i-v-1];
	b[i-v-1]=c;
    }
    return b;
}
	
  
	    
		    
		
		   
	    
	    
   
	    
		
		
    
    
