#include<avr/io.h>
#include<util/delay.h>
#include<line.c>

main()
{fastpwm_mode(255);
port1();

char turn[30];

int r,count=-1;
while(1)
{
follow();
if((PIND & 0b01000000))
   {break;
   }
turnright();
r=follow();
if(r==1)
turn[++count]='r';
else turn[++count]='l';
str();
delay(1,100);

turnback();
follow();
str();
delay(1,100);

turnback();
stop_left();
turnleft();


}

white_move();
follow();
stop();
PORTD|=0b00100000;
delay(1,3000);
PORTD&=0b11011111;
white_move();
follow();
white_move();
follow();
while(count!=-1)
{
if(turn[count]=='l')
  {
  turnright();stop_left();
  turnleft();follow();
  }
  else {
  turnleft();stop_right();
  turnright();follow();
  }
  count--;
  
  


}


}