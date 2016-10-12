#include<avr/io.h> 
#include<util/delay.h> 
/*Macros definition*/ 

#define CHECKBIT(x,b) x&(1<<b)  	//Checks bit status 
#define SETBIT(x,b) x|=(1<<b)   	//Sets the particular bit 
#define CLEARBIT(x,b) x&=~(1<<b) 	//Sets the particular bit 
#define TOGGLEBIT(x,b) x^=(1<<b) 	//Toggles the particular bit 

void uart_init(void)
{
UCSRB = 0x18;
UCSRC = 0x86;
UBRRL = 25;
}




void trans(char data)
{
UDR = data;
while(!(CHECKBIT(UCSRA,UDRE)))
{
}
_delay_ms(10);
}




void transtring(char string[100])
{
unsigned int len=0;
while(string[len]!='\0')
{
trans(string[len]);
len++;
}
trans('\r');
trans('\n');
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



int main(void)
{DDRD=0xFF;
uart_init();

_delay_ms(1000);
trans('1');
_delay_ms(100);
trans('2');
_delay_ms(100);
trans('3');
_delay_ms(100);    //only required for rf transmission

unsigned int i=0;
char a,c[100];


char b='A';



trans(b);
return(0);
}
