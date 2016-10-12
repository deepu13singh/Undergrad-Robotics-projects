#include<lcd4.c>
#include<avr/io.h> 
#include<util/delay.h> 
/*Macros definition*/ 

#define CHECKBIT(x,b) x&(1<<b)  	//Checks bit status 
#define SETBIT(x,b) x|=(1<<b)   	//Sets the particular bit 
#define CLEARBIT(x,b) x&=~(1<<b) 	//Sets the particular bit 
#define TOGGLEBIT(x,b) x^=(1<<b) 	//Toggles the particular bit 

		
		
	void ctc_mode(unsigned int duty_ctc)
{
TCCR0 |= ((1<<COM00)|(1<<WGM01)|(1<<CS01));	//  WGM mode : CTC, O/P compare mode: Toggle on compare, Clk/8
OCR0=duty_ctc;	

DDRB|=(1<<PB3);		//setting PB3 (OC0)as o/p pin
}

void fastpwm_mode(unsigned int duty_fpwm)
{
TCCR2|=((1<<COM21)|(1<<WGM21)|(1<<WGM20)|(1<<CS21));	//  WGM mode : Fastpwm, 
					//O/P compare mode: Non inverting(clear OC2 on compare match,set OC2 on bottom), clk/8
OCR2=duty_fpwm;	

DDRD|=(1<<PD7);		//setting PD7 (OC2)as o/p pin
}
	
		
int i,c,stkt[20],t1=-1,dt[11][11],current,cu,a[9][9],mdir=3,stk[20],top=-1,numbers=0;
       void lforward()
{  int p,flag=-1;
   for(p=t1;p>=0;p--)
 if(stkt[p]==current)
{  flag=1;break; }
    if(flag==1)
t1=p;
else stkt[++t1]=current;



}



       int min_val(int o)
   {
		int min=100;
		if(dt[o/10+2][o%10+1]==1)
	if(min>a[o/10+1][o%10])
	   min=a[o/10+1][o%10];


	      if(dt[o/10+1][o%10+2]==1)
	   if(min>a[o/10][o%10+1])
	   min=a[o/10][o%10+1];

	      if(dt[o/10][o%10+1]==1)
	   if(min>a[o/10-1][o%10])
	   min=a[o/10-1][o%10];

	      if(dt[o/10+1][o%10]==1)
	   if(min>a[o/10][o%10-1])
	   min=a[o/10][o%10-1];
	   return min;
   }

      void update()
   {int i,c;
   stk[++top]=current;

		while(top!=-1)
	{     i=stk[top--];
		      c=min_val(i);
		   if(a[i/10][i%10]!=c+1)
		 {
		     a[i/10][i%10]=c+1;
		     if(dt[i/10+1][i%10]==1)
		     stk[++top]=i-1;
		     if(dt[i/10][i%10+1]==1)
		     stk[++top]=i-10;
		     if(dt[i/10+1][i%10+2]==1)
		      stk[++top]=i+1;
		     if(dt[i/10+2][i%10+1]==1)
		    stk[++top]=i+10;

		 }
	    }
   }
     int assign(int q,int w)
   {
   if(q<0)
   q=-q;
   if(w<0)
   w=-w;
   return q+w;
   }


void go_frm_to(int initial,int final)
{t1=-1;int dir=1;









   

    for(i=0;i<9;i++)
   for(c=0;c<9;c++)
   a[i][c]=assign(final/10-i,final%10-c);

 






   current=initial;
stkt[++t1]=current;
   while(current!=final)
   {

   update();  
   i=a[current/10][current%10]-1;
   if(dir==1)
       {
	  if(dt[current/10+1][current%10+2]==1 && a[current/10][current%10+1]==i) {current+=1;lforward();}//1
	 else  if(dt[current/10+2][current%10+1]==1 && a[current/10+1][current%10]==i) {dir=4;}//4
	 else if(dt[current/10][current%10+1]==1 && a[current/10-1][current%10]==i) {dir=2;}//2
		 else if(dt[current/10+1][current%10]==1 && a[current/10][current%10-1]==i) {dir=3;}//3
      }

     if(dir==2)
      {  if(dt[current/10][current%10+1]==1 && a[current/10-1][current%10]==i) {current-=10;lforward();}//2
	else if(dt[current/10+1][current%10+2]==1 && a[current/10][current%10+1]==i) {dir=1;}//1
	else if(dt[current/10+1][current%10]==1 && a[current/10][current%10-1]==i) {dir=3;}//3
	else if(dt[current/10+2][current%10+1]==1 && a[current/10+1][current%10]==i) {dir=4;}//4

      }

    if(dir==3)
      { if(dt[current/10+1][current%10]==1 && a[current/10][current%10-1]==i) {current-=1;lforward();}//3
       else if(dt[current/10][current%10+1]==1 && a[current/10-1][current%10]==i) {dir=2;}//2
       else if(dt[current/10+2][current%10+1]==1 && a[current/10+1][current%10]==i) {dir=4;}//4
	   else if(dt[current/10+1][current%10+2]==1 && a[current/10][current%10+1]==i) {dir=1;}//1



      }
    if(dir==4)
      {	if(dt[current/10+2][current%10+1]==1 && a[current/10+1][current%10]==i) {current+=10;lforward();}//4
	    else if(dt[current/10+1][current%10]==1 && a[current/10][current%10-1]==i) {dir=3;}//3
	else if(dt[current/10+1][current%10+2]==1 && a[current/10][current%10+1]==i) {dir=1;}//1
	    else if(dt[current/10][current%10+1]==1 && a[current/10-1][current%10]==i) {dir=2;}//2
      }
   }  //while
   }             


void uart_init(void)
{
UCSRB = 0x18;
UCSRC = 0x86;
UBRRL = 25;
}
void stop2()
{PORTC&=0b00111111;

  

}

void stop3()
{
PORTC&=0b11001111;
  

}

void str()
{
  SETBIT(PORTC,0);
  CLEARBIT(PORTC,1);
  SETBIT(PORTC,2);
  CLEARBIT(PORTC,3);
}

void r()
{
  SETBIT(PORTC,0);
  CLEARBIT(PORTC,1);
  CLEARBIT(PORTC,2);
  CLEARBIT(PORTC,3);
}

void l()
{ CLEARBIT(PORTC,0);
  CLEARBIT(PORTC,1);
  SETBIT(PORTC,2);
  CLEARBIT(PORTC,3);
}

void r2()
{
  SETBIT(PORTC,0);
  CLEARBIT(PORTC,1);
  CLEARBIT(PORTC,2);
  SETBIT(PORTC,3);
}

void l2()
{
  CLEARBIT(PORTC,1);
  SETBIT(PORTC,3);
  SETBIT(PORTC,3);
  CLEARBIT(PORTC,2);
}

void back()
{
  CLEARBIT(PORTC,0);
  SETBIT(PORTC,1);
  CLEARBIT(PORTC,2);
  SETBIT(PORTC,3);
}

void stop()
{
  SETBIT(PORTC,0);
  SETBIT(PORTC,1);
  SETBIT(PORTC,2);
  SETBIT(PORTC,3);
}

void rel()
{
CLEARBIT(PORTC,4);
  SETBIT(PORTC,5);
delay(1,700);
stop3();
}
void grab()
{
CLEARBIT(PORTC,5);
  SETBIT(PORTC,4);
delay(1,700);
}
void down()
{
CLEARBIT(PORTC,6);
  SETBIT(PORTC,7);
delay(1,800);
stop2();
}

void up()
{
CLEARBIT(PORTC,7);
  SETBIT(PORTC,6);
delay(1,1000);
stop2();
}

void turnleft()
{

l();
delay(1,900);

}
void turnright()
{
r();
delay(1,900);
}
void turnback()
{
r2();
delay(1,800);

}

void normalmove_node()
{
int s=1;
while(1)
{ 


if((PINA & 0b00011111)==0b00000100)
str();

else if((PINA & 0b00011111)==0b00000010)
l();

else if((PINA & 0b00011111)==0b00001000)
r();

else if((PINA & 0b00011111)==0b00000001)
{ CLEARBIT(PORTC,0);
  SETBIT(PORTC,1);
 CLEARBIT(PORTC,2);
  CLEARBIT(PORTC,3);
  }

else if((PINA & 0b00011111)==0b00011000)
r();

else if((PINA & 0b00011111)==0b00001100)
r();

else if((PINA & 0b00011111)==0b00011100)
r();

else if((PINA & 0b00011111)==0b00000011)
l();
else if((PINA & 0b00011111)==0b00000000)
{}
else if((PINA & 0b00011111)==0b00000111)
l();

else if((PINA & 0b00011111)==0b00010000)
{CLEARBIT(PORTC,2);
  SETBIT(PORTC,3);
 CLEARBIT(PORTC,1);
  CLEARBIT(PORTC,0);}

else if((PINA & 0b00011111)==0b00000110)
l();


else if((PINA & 0b00011111)==0b00011111)
{

if(s==1)
{
back();
//delay(1,60);
stop();
break;
}
else s++;
}


else
str();
_delay_ms(75);
}

}
void white_move()
{

str();
delay(1,200);
}

int normalmove_box()
{int s=1;

while(1)
{ if(PIND & 0b01000000)
{back();
 back();
delay(1,60);
stop();

return 1;
}
else if((PINA & 0b00011111)==0b00000000)
{}
else
if((PINA & 0b00011111)==0b00000100)
{str();s=1;}

else if((PINA & 0b00011111)==0b00000010)
{l();s=1;}

else if((PINA & 0b00011111)==0b00001000)
{r();s=1;}

else if((PINA & 0b00011111)==0b00000001)
{ CLEARBIT(PORTC,0);
  SETBIT(PORTC,1);
 CLEARBIT(PORTC,2);
  CLEARBIT(PORTC,3);
  }

else if((PINA & 0b00011111)==0b00011000)
{r();s=1;}
else if((PINA & 0b00011111)==0b00010000)
{CLEARBIT(PORTC,2);
  SETBIT(PORTC,3);
 CLEARBIT(PORTC,1);
  CLEARBIT(PORTC,0);}
else if((PINA & 0b00011111)==0b00001100)
{r();s=1;}

else if((PINA & 0b00011111)==0b00011100)
{r();s=1;}

else if((PINA & 0b00011111)==0b00000011)
{l();s=1;}

else if((PINA & 0b00011111)==0b00000111)
{l();s=1;}



else if((PINA & 0b00011111)==0b00000110)
{l();s=1;}


else if((PINA & 0b00011111)==0b00011111 )

if(s==1)
{back();

stop();

return 0;
}

else if((PINA & 0b00011111)==0b0001111 )

if(s==1)
{back();

stop();

return 0;
}

else if((PINA & 0b00011111)==0b00011110 )

if(s==1)
{back();

stop();

return 0;
}


else
str();
_delay_ms(0);
}

}

void trans(char data)
{
UDR = data;
while(!(CHECKBIT(UCSRA,UDRE)))
{
}
_delay_ms(10);
}





char recv(void)
{
while(!(CHECKBIT(UCSRA,RXC)))
{
}
_delay_ms(5);
char atad = UDR;
return (atad);
}
void bot_move(int q,int fin)
{int g;
while(q<fin)
{ g=stkt[q];
  c=stkt[q+1];
  
  if(mdir==4 && c==g+10 || mdir==1 && c==g+1 || mdir==2 && c==g-10 || mdir==3 && c==g-1 )
       {white_move();normalmove_node();}
  else if(mdir==3 && c==g+10 || mdir==4 && c==g+1 || mdir==1 && c==g-10 || mdir==2 && c==g-1 )
        {  turnleft();normalmove_node(); mdir+=1;
		    if(mdir==5)
			   mdir=1;
		}
  else if(mdir==1 && c==g+10 || mdir==2 && c==g+1 || mdir==3 && c==g-10 || mdir==4 && c==g-1 )
        {  turnright();normalmove_node();mdir-=1;
		    if(mdir==0)
			   mdir=4;
		}
   else if(mdir==2 && c==g+10 || mdir==3 && c==g+1 || mdir==4 && c==g-10 || mdir==1 && c==g-1 )
        {  turnback(); normalmove_node();mdir-=2;
		    if(mdir==0)
			   mdir=4;
			if(mdir==-1)
			   mdir=3;

		}
		q++;

}
}
void reverse()
{
int r,temp;
for(r=0;r<=t1/2;r++)
{
temp=stkt[r];
stkt[r]=stkt[t1-r];
stkt[t1-r]=temp;

}

}



void actual_move()
{
int count=0;

for(count;count<=t1;count++)
{
if(stkt[count]/10==1 || stkt[count]/10==7 || stkt[count]%10==1 || stkt[count]%10==7)
break;

}
bot_move(0,count-1);
recv();trans('a');
recv();SETBIT(PORTD,5);
recv();
CLEARBIT(PORTD,5);
recv();
bot_move(count-1,count);
trans('s');
bot_move(count,t1);
back();
delay(1,350);
stop();
down();
rel();
back();
while(PINA!=0b11111111)
{}
stop();
reverse();
count=t1-count;
bot_move(1,count);

if(stkt[count]-stkt[count+1]==10)
{
if(mdir==2)
{str();delay(1,400);trans('a');normalmove_node();   }
else if(mdir==1)
{turnleft();trans('a');normalmove_node();}
else if(mdir==4)
{turnback();trans('a');normalmove_node();}
else if(mdir==3)
{turnright();trans('a');normalmove_node();}
mdir=2;
}
else if(stkt[count]-stkt[count+1]==-1)
{
if(mdir==1)
{str();delay(1,600);trans('a');normalmove_node();   }
else if(mdir==4)
{turnleft();trans('a');normalmove_node();}
else if(mdir==3)
{turnback();trans('a');normalmove_node();}
else if(mdir==2)
{turnright();trans('a');normalmove_node();}
mdir=1;
}if(numbers==2)
 while(1)
{ stop();
}
bot_move(count+1,t1);


}




 main()
{

uart_init();
DDRD=0b10111111;
PORTD=0b10000000;
DDRC=0xff;	
PORTC=0x00;
DDRA=0x00;
PORTA=0xFF;
//fastpwm_mode(200000);

_delay_ms(1000);
trans('5');
_delay_ms(100);
trans('9');
_delay_ms(100);
trans('4');
_delay_ms(100);


for(i=1;i<=9;i++)
{dt[1][i]=1;
  dt[2][i]=1;
  dt[8][i]=1;
  dt[9][i]=1;
  dt[i][1]=1;
  dt[i][2]=1;
  dt[i][8]=1;
  dt[i][9]=1;
  
}
mdir=3;
int x,y,dist[2],point=0,bo;
cu=66;

recv();

for(x=6;x>=2;x--)
{for(y=6;y>=2;y--)
  {                           
      
	   if(10*x+y-cu==1)
	   {
	   if(mdir==1)
	   white_move();
	   else if(mdir==2)
	      turnright();
	   else if(mdir==3)
	      turnback();
	   else if(mdir==4)
	      turnleft();
	   mdir=1;
	   }
	  else if(10*x+y-cu==-10)
	   {
	   if(mdir==2)
	   white_move();
	   else if(mdir==3)
	      turnright();
	   else if(mdir==4)
	      turnback();
	   else if(mdir==1)
	      turnleft();
		  
		  mdir=2;
	   }
	   else if(10*x+y-cu==-1)
	   {
	   if(mdir==3)
	   white_move();
	   else if(mdir==4)
	      turnright();
	   else if(mdir==1)
	      turnback();
	   else if(mdir==2)
	      turnleft();
	   mdir=3;
	   }
      else if(10*x+y-cu==10)
	   {
	   if(mdir==4)
	   white_move();
	   else if(mdir==1)
	      turnright();
	   else if(mdir==2)
	      turnback();
	   else if(mdir==3)
	      turnleft();
	   mdir=4;
	   }
     cu=10*x+y;
	 dt[x+1][y+1]=1;
   bo=normalmove_box();
   
   if(bo==1)
    { numbers++;  grab();up(); normalmove_node();
       if(point==84)
	     { go_frm_to(cu,40);actual_move(); dt[5][1]=0; }
		 else if(point==40)
		 {go_frm_to(cu,84);actual_move();dt[9][5]=0;}
		 else {  go_frm_to(cu,4);dist[0]=t1; go_frm_to(cu,84);dist[1]=t1;
                  if(dist[0]<dist[1])
				   { point=40;go_frm_to(cu,40); actual_move(); dt[5][1]=0;}
				   else {point=84;actual_move();dt[9][5]=0;}

               }
     


    }
	
            
    }
   x--;
for(y=2;y<=6;y++)
   {   if(10*x+y-cu==1)
	   {
	   if(mdir==1)
	   white_move();
	   else if(mdir==2)
	      turnright();
	   else if(mdir==3)
	      turnback();
	   else if(mdir==4)
	      turnleft();
	   mdir=1;
	   }
	  else if(10*x+y-cu==-10)
	   {
	   if(mdir==2)
	   white_move();
	   else if(mdir==3)
	      turnright();
	   else if(mdir==4)
	      turnback();
	   else if(mdir==1)
	      turnleft();
		  
		  mdir=2;
	   }
	   else if(10*x+y-cu==-1)
	   {
	   if(mdir==3)
	   white_move();
	   else if(mdir==4)
	      turnright();
	   else if(mdir==1)
	      turnback();
	   else if(mdir==2)
	      turnleft();
	   mdir=3;
	   }
      else if(10*x+y-cu==10)
	   {
	   if(mdir==4)
	   white_move();
	   else if(mdir==1)
	      turnright();
	   else if(mdir==2)
	      turnback();
	   else if(mdir==3)
	      turnleft();
	   mdir=4;
	   }
     cu=10*x+y;
	 dt[x+1][y+1]=1;
   bo=normalmove_box();
   
  if(bo==1)
    { numbers++;  grab();up(); normalmove_node();
       if(point==84)
	     { go_frm_to(cu,40);actual_move(); dt[5][1]=0; }
		 else if(point==40)
		 {go_frm_to(cu,84);actual_move();dt[9][5]=0;}
		 else {  go_frm_to(cu,40);dist[0]=t1; go_frm_to(cu,84);dist[1]=t1;
                  if(dist[0]<dist[1])
				   { point=40;go_frm_to(cu,40); actual_move(); dt[5][1]=0;}
				   else {point=84;actual_move();dt[9][5]=0;}

               }
     


    }

	}
}


string("hikn",0);pos(2,4);number2(123.4,4);
while(1)
{}
}
