#include<avr/io.h>
#include<util/delay.h>


#define P1 PINA
#define P2 PORTC
void fastpwm_mode(unsigned int duty_fpwm)
{
TCCR2|=((1<<COM21)|(1<<WGM21)|(1<<WGM20)|(1<<CS21));	//  WGM mode : Fastpwm, 
					//O/P compare mode: Non inverting(clear OC2 on compare match,set OC2 on bottom), clk/8
OCR2=duty_fpwm;	

		//setting PD7 (OC2)as o/p pin
}
int s;
void delay(int b,int a)
		{
	         for(;a>0;a--)
		    _delay_ms(b);
		}
void port1()
{
DDRA=0x00;PORTA=0xFF;
DDRC=0xFF;DDRD|=0b10100000;
DDRD&=0b10111111;
}

void right()
{
fastpwm_mode(100);
P2=0b11111101;
fastpwm_mode(255);
}
void right2() 
{
P2=0b11111001;
}
void left()
{fastpwm_mode(100);
P2=0b11110111;
fastpwm_mode(255);
}
void left2()
{
P2=0b11110110;
}
void str()
{
P2=0b11110101;

}
stop()
{
P2=0xFF;
}


void back()
{
P2=0b11111010;

}



void turnleft()
{str();
delay(1,130);
left2();
delay(1,300);


}

void turnright()
{
str();
delay(1,130);
right2();
delay(1,300);


}

void turnback()
{
while(1)
{

left2();
 if(PINA&0b00000010)
 break;
 }
stop();


}


white_move()
{

while(1)
{
if(PINA==0b11111111)
str();
else break;

}
stop();

//str();	delay(1,300);


}

int follow()
{
int a=0;
while(1)
{
if((PINA & 0b00011111)==0b00011111)
{



back();
delay(1,30);
stop();
s=1;
break;

}


else if((PINA & 0b00011111)==0b00000111)
{



str();
s=1;



}
else if((PINA & 0b00011111)==0b00000000)
{



back();
delay(1,30);
stop();
s=0;
break;
}

else if((PINA & 0b00011111)==0b00000100)
str();

else if((PINA & 0b00011111)==0b00000010)
left();

else if((PINA & 0b00011111)==0b00001000)
right();
   else if((PINA & 0b00011111)==0b00011000)
right();

else if((PINA & 0b00011111)==0b00001100)
right();
else if((PINA & 0b00011111)==0b00000011)
left();

else if((PINA & 0b00011111)==0b00000110)
left();
else str();

}
return a;

}


void stop_left()
{

while(1)
{
if((PINA & 0b00011111)==0b00011111)
{



back();
delay(1,30);
stop();
s=1;
break;

}
else if((PINA & 0b00011111)==0b00000000)
{



back();
delay(1,30);
stop();
s=0;
break;
}
else if((PINA & 0b00011111)==0b00000111)
{stop();break;
}

else if((PINA & 0b00011111)==0b00001111)
{stop();break;
}

else if((PINA & 0b00011111)==0b00000100)
str();

else if((PINA & 0b00011111)==0b00000010)
left();

else if((PINA & 0b00011111)==0b00001000)
right();
   else if((PINA & 0b00011111)==0b00011000)
right();

else if((PINA & 0b00011111)==0b00001100)
right();
else if((PINA & 0b00011111)==0b00000011)
left();

else if((PINA & 0b00011111)==0b00000110)
left();
else str();

}

}



void stop_right()
{

while(1)
{
if((PINA & 0b00011111)==0b00011111)
{



back();
delay(1,30);
stop();
s=1;
break;

}
else if((PINA & 0b00011111)==0b00000000)
{



back();
delay(1,30);
stop();
s=0;
break;
}
else if((PINA & 0b00011111)==0b00011100)
{stop();break;
}

else if((PINA & 0b00011111)==0b00011110)
{stop();break;
}

else if((PINA & 0b00011111)==0b00000100)
str();

else if((PINA & 0b00011111)==0b00000010)
left();

else if((PINA & 0b00011111)==0b00001000)
right();
   else if((PINA & 0b00011111)==0b00011000)
right();

else if((PINA & 0b00011111)==0b00001100)
right();
else if((PINA & 0b00011111)==0b00000011)
left();

else if((PINA & 0b00011111)==0b00000110)
left();
else str();

}

}



