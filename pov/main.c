#include<pov.c>
#include<avr/io.h>
#include<util/delay.h>

void main()
{        unsigned int p,l,r,i;char str[]="CYBORG @ NITRKL ROCKS !!!";
		
		for(l=1;l<=200;l++)
		   _delay_ms(100);        //Waiting for 20 sec after microcontroller starts


  DDRB=0xFF;                            //Output at PORTB
       
  TCCR1B|=0b10000000;			//noise cancellar
  TCCR1B|=0b01000000;			//falling edge selected
  TCCR1B|=0b00000011;			//cs10=1  cs11=1   
  TCCR1B&=0b11111011;			//cs12=0              Timer started at (8/64)Mhz


	while(ICR1==0b0000000000000000){}                     //waitingfor intrupt to occour

    ICR1=0b0000000000000000;
	TCNT1=0b0000000000000000;
      
	 _delay_ms(80);
	while(ICR1==0b0000000000000000){}                     //waitingfor intrupt to occoure

    p=ICR1L;
	p|=ICR1H<<8;                                    // Reading the Pulses
    l=25;r=400;float t;
    t=(float)(l*p*4)/(3141.5926*r);                         //Time calculated for each column of a character
   
	TCCR1B&=0b10111111;//edge sel
	TCNT1=0b0000000000000000;
        ICR1=0b0000000000000000;
    
   	while(1){
		while(ICR1==0b0000000000000000){}                //waitingfor intrupt to occoure
	
	     TCNT1=0b0000000000000000;
         ICR1=0b0000000000000000;
       
          for(i=0;i<25;i++)                                   //Printing one by one each char of str
            character(str[i],t);

     }  //while(1)   
   }//main