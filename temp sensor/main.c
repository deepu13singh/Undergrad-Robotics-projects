#include<avr/io.h>
#include<util/delay.h>
#include<adc.c>

void number(int num,int pos)
{
pos-=1;
PORTD=0xFF;
PORTD&=~(1<<pos);

switch(num)
{
case 1: PORTC=0b01000001;   break;
case 2:  PORTC=0b00111011;   break;
case 3: PORTC=0b01101011;   break; 
case 4: PORTC=0b01001101;   break;
case 5: PORTC=0b01101110;   break;
case 6: PORTC=0b01111110;   break;
case 7: PORTC=0b01000011;   break;
case 8: PORTC=0b01111111;   break;
case 9: PORTC=0b01101111;   break;
case 0: PORTC=0b01110111;   break;
default : PORTC|=(1<<7);
}

}


void main()
{int val,a,b,c;
float vin,temp;
DDRD=0xFF;
DDRC=0xFF;
PORTC=0x00;
PORTD=0x00;
number(12,3);
adc_init();
while(1)
{
val=adc_read(0);
vin=val*2.57/1024;
temp=vin/.01;
val=temp;
temp-=val;
temp*=10;
b=val%10;
val/=10;
a=val%10;
val=temp;
c=val;

number(a,1);
_delay_ms(.5);
number(b,2);
number(34,2);
_delay_ms(.5);
number(c,3);
_delay_ms(.5);
}


}