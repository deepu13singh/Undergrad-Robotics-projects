
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>



unsigned char ADC_Conversion(unsigned char);
unsigned char ADC_Value;
char first_row[] = " POT1 POT2 POT3 ";


//Function to configure LCD port


//ADC pin configuration
void adc_pin_config (void)
{
 DDRF = 0x00;           //set PORTF direction as input
 PORTF = 0x00;          //set PORTF pins floating
}

//Function to Initialize PORTS


//Function to Initialize ADC
void adc_init()
{
 ADCSRA = 0x00;
 ADCSRB = 0x00;		//MUX5 = 0
 ADMUX = 0x20;		//Vref=5V external --- ADLAR=1 --- MUX4:0 = 0000
 ACSR = 0x80;
 ADCSRA = 0x86;		//ADEN=1 --- ADIE=1 --- ADPS2:0 = 1 1 0
}


//This Function accepts the Channel Number and returns the corresponding Analog Value 
unsigned char ADC_Conversion(unsigned char Ch)
{
 unsigned char a;

 Ch = Ch & 0x07;  			
 ADMUX= 0x20| Ch;	   		
 ADCSRA = ADCSRA | 0x40;		//Set start conversion bit
 while((ADCSRA&0x10)==0);	    //Wait for ADC conversion to complete
 a = ADCH;
 ADCSRA = ADCSRA|0x10;          //clear ADIF (ADC Interrupt Flag) by writing 1 to it
 ADCSRB = 0x00;
 return a;
}

// This Function prints the Analog Value Of Corresponding Channel No. at required Row
// and Coloumn Location. 
int print_sensor( char channel)
{
 ADC_Value = ADC_Conversion(channel);
 return ADC_Value;
}

void init_devicesadc (void)
{
 cli(); //Clears the global interrupts
 adc_pin_config();
 adc_init();
 sei(); //Enables the global interrupts
}
