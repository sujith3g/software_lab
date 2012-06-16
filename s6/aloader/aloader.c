#include<stdio.h>
#include<math.h>
#include<string.h>
char *dectohex(int a);
main()
{
    FILE *f1,*f2;
    char a[100],c,*p,fl[12],*t;
    int i,l,loc,ploc,lc=0,f,d;
    f1=fopen("aloaderinput.txt","r+");
    f2=fopen("aloaderoutput.txt","w+");
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
	for(i=0;i<l/3;i++)
	{
		p=strtok(NULL,"^");
		t=dectohex(lc);
		fprintf(f2,"%s: %s\n",t,p);
		lc+=strlen(p)/2;
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
		    
		
		   
	    
	    
   
	    
		
		
    
    
