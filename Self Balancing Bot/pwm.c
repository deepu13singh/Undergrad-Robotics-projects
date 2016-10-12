#include<avr/io.h>
#include<util/delay.h>

/*******FUNCTION DEFINATION**********/
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

main()
{
int i;
	while(1)
	{
	ctc_mode(210);
	
	for(i=0;i<10;i++)
		_delay_ms(1000);
		
	ctc_mode(80);
	
	for(i=0;i<5;i++)
		_delay_ms(1000);
		
	fastpwm_mode(150);
	
	for(i=0;i<10;i++)
		_delay_ms(1000);
		
	fastpwm_mode(60);
	
	for(i=0;i<5;i++)
		_delay_ms(1000);
	}

	return (0);
}

