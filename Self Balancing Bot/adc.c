

#include<avr/io.h>
#include<util/delay.h>



void adc_init()
{
	DDRA=0X00;
	ADMUX&=~(1<<ADLAR ); 							//Right Adjustment of Result
	ADMUX&=~(1<<REFS1); 
	ADMUX|= (1<<REFS0);							//Voltage Reference IS AVcc 
	
	ADCSRA|=((1<<ADPS1)|(1<<ADPS0));              //ADC Prescaler Selection   // divison factor is 8
	ADCSRA&=~(1<<ADPS2);			                //ADC Prescaler Selection
	ADCSRA&=~((1<<ADIF)|(1<<ADIE));     			//Disable Interrupts
	SFIOR&=~((1<<ADTS2)|(1<<ADTS1)|(1<<ADTS0));  //Free Running Mode
	ADCSRA|=((1<<ADEN) |(1<<ADATE)) ;             //ADC Enabled,Auto Trigger Enabled
	
}



float adc_read(int i)
{
	switch(i)			//Channel Selection
	{
		case 0:
		ADMUX&=~((1<<MUX0)|(1<<MUX1)|(1<<MUX2)|(1<<MUX3)|(1<<MUX4));
		break;
		case 1:
		ADMUX&=~((1<<MUX1)|(1<<MUX2)|(1<<MUX3)|(1<<MUX4));
		ADMUX|=(1<<MUX0);
		break;
		case 2:
		ADMUX&=~((1<<MUX0)|(1<<MUX2)|(1<<MUX3)|(1<<MUX4));
		ADMUX|=(1<<MUX1);
		break;
		case 3:
		ADMUX&=~((1<<MUX2)|(1<<MUX3)|(1<<MUX4));
		ADMUX|=((1<<MUX0)|(1<<MUX1));
		break;
		case 4:
		ADMUX&=~((1<<MUX0)|(1<<MUX1)|(1<<MUX3)|(1<<MUX4));
		ADMUX|=(1<<MUX2);
		break;
		case 5:
		ADMUX&=~((1<<MUX1)|(1<<MUX3)|(1<<MUX4));
		ADMUX|=((1<<MUX0)|(1<<MUX2));
		break;
		case 6:
		ADMUX&=~((1<<MUX0)|(1<<MUX3)|(1<<MUX4));
		ADMUX|=((1<<MUX1)|(1<<MUX2));
		break;
		case 7:
		ADMUX&=~((1<<MUX3)|(1<<MUX4));
		ADMUX|=((1<<MUX0)|(1<<MUX1)|(1<<MUX2));
	}
	//ADCSRA|=(1<<ADSC);     //starts conversion
	int adc=0;
	adc=ADCL;
	int hbite=ADCH;
	adc|=hbite<<8;
	/*float vol=adc*2.56/1024;
	return vol;*/
	return adc;
}
	



