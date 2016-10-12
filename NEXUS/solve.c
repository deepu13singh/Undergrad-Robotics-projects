#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


#define N 6


int rel[36][36],worked[36],proc[36],status[36][2],elem[10],top,workingnode;
int i,j;

void prepare4new()
{

for(i=0;i<N*N;i++)
 { status[i][0]=100;
 status[i][1]=0;
   worked[i]=0;
   proc[i]=0;
 }
}

void set_matvalues()
{

for(i=0;i<N*N;i++)
 for(j=0;j<N*N;j++)
   if(i==j)
     rel[i][j]=10;
     else rel[i][j]=0;
int a,b,c,d;
     for(i=0;i<N*N;i++)
     {   if(i==0)
           {a=1;b=c=0;d=6;
           }
           else if(i==5)
            {a=b=0;d=6;c=1;
           }
           else if(i==30)
            {a=1;b=6;c=d=0;
           }else if(i==35)
            {a=d=0;c=1;b=6;
           }
           else if(i/N==0)
                   {  a=c=1;d=6;b=0;    }
              else if( i%6 == 0)
                  {  c=0;a=1;b=d=6;  }
             else if( i%6 == N-1)
                 {   a=0;b=d=6;c=1;   }
            else if(i/N== N-1)
                  {      d=0;a=c=1;b=6; }
                 
rel[i][i+a]=1;
rel[i][i-b]=1;
rel[i][i-c]=1;
rel[i][i+d]=1;

rel[i+a][i]=1;
rel[i-b][i]=1;
rel[i-c][i]=1;
rel[i+d][i]=1;

         }
for(i=0;i<N*N;i++)
 for(j=0;j<N*N;j++)
   if(i==j)
     rel[i][j]=10;

}


void solve(int initial,int final)
{

status[initial][0]=0;
workingnode=initial;
while(1)
{
   

      top=-1;
for(i=0;i<N*N;i++)
  if( rel[workingnode][i] == 1 && worked[i] == 0 )
      elem[++top]=i;  //storing all the nearby nodes




for(i=0;i<=top;i++)
 { if(status[elem[i]][0] > status[workingnode][0] + 1 )
  { 
      status[elem[i]][0]=status[workingnode][0]+1;
      status[elem[i]][1]=workingnode;
  }

 proc[elem[i]]=1;
 }
 

int min=100,l=-23;






for(i=0;i<N*N;i++)
 if(  status[i][0] < min && worked[i] == 0 && proc[i]==1 )
     {  min = status[i][0]; l = i;  }
     worked[workingnode]=1;
     workingnode = l;
l=-23;
for(i=0;i<N*N;i++)
  if(worked[i]==0)
     l=2;
if(l==-23)
break;
}


 int  l=final;top=-1;
  while(1)
   {
      proc[++top]=l;
l=status[l][1];
if(l==initial )
      { 
    
proc[++top]=l;
break;
}

  }

}
