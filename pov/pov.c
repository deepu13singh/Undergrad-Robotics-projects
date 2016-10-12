//   #################### PRINT CHARACTER  :  LED PATTERN FOR COMMON CHARACTERS
#include<util/delay.h>
#include<avr/io.h>

void character(char a,float t)
{

   switch(a)	
{   case 'A':          	    	 PORTB=0b01111000;
	  			 _delay_ms(t);
	   			 PORTB=0b00010100;
	  			 _delay_ms(t);
	  			 PORTB=0b00010010;
	  			 _delay_ms(t);
	  			 PORTB=0b00010001;
	 			  _delay_ms(t);
	  			 PORTB=0b00010010;
	   			_delay_ms(t);
	   			PORTB=0b00010100;
	   			_delay_ms(t);
       				 PORTB=0b01111000;
	  			 _delay_ms(t);
	   			   PORTB=0b00000000;
	  			 _delay_ms(2.5*t);


case 'B':             	         PORTB=0b01111111;
	  			 _delay_ms(t);
	  			 PORTB=0b01001001;
	   			 _delay_ms(t);
	   			 PORTB=0b01001001;
	  			 _delay_ms(t);
	   			 PORTB=0b01001001;
	  			 _delay_ms(t);
	   			 PORTB=0b01001001;
	   			 _delay_ms(t);
	   			 PORTB=0b01001001;
	   			 _delay_ms(t);
        			 PORTB=0b00110110;
	  			 _delay_ms(t);
	   	  		 PORTB=0b00000000;
	   			 _delay_ms(2.5*t);

case 'C':                        PORTB=0b00011100;
	                         _delay_ms(t);
	                         PORTB=0b00100010;
	  			 _delay_ms(t);
	  			 PORTB=0b01000001;
	  			 _delay_ms(4*t);
	 			 PORTB=0b00100010;
	  			 _delay_ms(t);
	  			 PORTB=0b00000000;
	  			 _delay_ms(2.5*t);break;
      
       case 'D':                 PORTB=0b01111111;
	  			 _delay_ms(t);
	  			 PORTB=0b01000001;
	  			 _delay_ms(4*t);
	  			 PORTB=0b00100010;
	   			 _delay_ms(t);
	  			 PORTB=0b00011100;
	   			 _delay_ms(t);
	   			 
	   	 		 PORTB=0b00000000;
	 			 _delay_ms(2.5*t);break;
  	
	case 'E' :               PORTB=0b01111111;
	  			 _delay_ms(t);
	  			 PORTB=0b01001001;
	  			 _delay_ms(6*t);
	  			
	   	 		 PORTB=0b00000000;
	 			 _delay_ms(2.5*t);break;
	
         case 'F' :              PORTB=0b01111111;
	  			 _delay_ms(t);
	  			 PORTB=0b00001001;
	  			 _delay_ms(5*t);
	  			 PORTB=0b00000001;
	   			 _delay_ms(t);
	  			 PORTB=0b00000000;
	 			 _delay_ms(2.5*t);break;

	case 'G':                 PORTB=0b00111110;
	  			 _delay_ms(t);
	  			 PORTB=0b01000001;
	  			 _delay_ms(t);
	  			 PORTB=0b01001001;
	  			 _delay_ms(t);
	   			 PORTB=0b01001001;
	   			 _delay_ms(t);
	  			  PORTB=0b01001001;
	  			 _delay_ms(t);
	  			 PORTB=0b01111010;
	  			 _delay_ms(t);
       				 PORTB=0b00000000;
	 			  _delay_ms(t);
	   			 PORTB=0b00000000;
	   			 _delay_ms(2.5*t);break;	
	
     case 'Y':			 PORTB=0b00000001;
	  			 _delay_ms(t);
	  			 PORTB=0b00000010;
	  			 _delay_ms(t);
	 			  PORTB=0b00000100;
	  			 _delay_ms(t);
	  			 PORTB=0b01111000;
	  			 _delay_ms(t);
	  			 PORTB=0b00000100;
	  			 _delay_ms(t);
	   			 PORTB=0b00000010;
	  			 _delay_ms(t);
       				 PORTB=0b00000001;
	   			 _delay_ms(t);
	   	 		  PORTB=0b00000000;
	  			 _delay_ms(2.5*t);break;

	case 'O':                PORTB=0b00011100;
	  			 _delay_ms(t);
	  			 PORTB=0b00100010;
	  			 _delay_ms(t);
	  			 PORTB=0b01000001;
	   			 _delay_ms(t);
	  			 PORTB=0b01000001;
	  			 _delay_ms(t);
	  			 PORTB=0b01000001;
	   			 _delay_ms(t);
	  			 PORTB=0b00100010;
	  			 _delay_ms(t);
       				 PORTB=0b00011100;
				 _delay_ms(t);
	   			 PORTB=0b00000000;
	  			 _delay_ms(2.5*t);break;

case 'R':                        PORTB=0b01111111;
	  			 _delay_ms(t);
	  			 PORTB=0b00001001;
	  			 _delay_ms(t);
	  			 PORTB=0b00001001;
	  			 _delay_ms(t);
	  			 PORTB=0b00011001;
	  			 _delay_ms(t);
	 			  PORTB=0b00101001;
	  			 _delay_ms(t);
	 			  PORTB=0b01000110;
	  			 _delay_ms(t);
        			PORTB=0b01000000;
	  			 _delay_ms(t);
	   			   PORTB=0b00000000;
				_delay_ms(2.5*t);	break;

case '@':                           PORTB=0b00111110;
	  				 _delay_ms(t);
	 			  PORTB=0b01000001;
	  			 _delay_ms(t);
	 			  PORTB=0b01011101;
	 			  _delay_ms(t);
	  			 PORTB=0b01010101;
	  			 _delay_ms(t);
	  			 PORTB=0b01011101;
	  			 _delay_ms(t);
	  			 PORTB=0b01010001;
	  			 _delay_ms(t);
        			PORTB=0b00001110;
				   _delay_ms(t);
	  		 	   PORTB=0b00000000;
				_delay_ms(2.5*t);break;	  

case 'N':                       PORTB=0b01111111;
	 		      _delay_ms(t);
	 			  PORTB=0b00000010;
	 			  _delay_ms(t);
	  			 PORTB=0b00000100;
	  			 _delay_ms(t);
	  			 PORTB=0b00001000;
	  			 _delay_ms(t);
	  			 PORTB=0b00010000;
	   			_delay_ms(t);
	  			 PORTB=0b00100000;
	  			 _delay_ms(t);
       				 PORTB=0b01111111;
	 			  _delay_ms(t);
	 	  	        PORTB=0b00000000;
			       _delay_ms(2.5*t);break;	   

case 'I':                        PORTB=0b01000001;
	  			 _delay_ms(3*t);
	  			 
	  			
	  			 PORTB=0b01111111;
	  			 _delay_ms(t);
	  			 PORTB=0b01000001;
	  			 _delay_ms(3*t);
        			
	  		 	   PORTB=0b00000000;
				_delay_ms(2.5*t);	break;  

case 'T':                         PORTB=0b00000001;
	  			 _delay_ms(3*t);
	   			PORTB=0b01111111;
	  			 _delay_ms(t);
	  			 PORTB=0b00000001;
	  			 _delay_ms(3*t);
	  			 
	 		  	   PORTB=0b00000000;
				_delay_ms(2.5*t);	break;  

case 'L':                        PORTB=0b01111111;
	  				 _delay_ms(t);
	  			 PORTB=0b01000000;
	  			 _delay_ms(6*t);
	  			
	   		  	 PORTB=0b00000000;
				_delay_ms(2.5*t);	break;   
	  		    

case 'K':                      PORTB=0b01111111;
	  			 _delay_ms(t);
	  			 PORTB=0b00001000;
	  			 _delay_ms(t);
	  			 PORTB=0b00011100;
	 			  _delay_ms(t);
	 			  PORTB=0b00010100;
	 			  _delay_ms(t);
	 			  PORTB=0b00100010;
	  			 _delay_ms(t);
	  			 PORTB=0b01000001;
	  			 _delay_ms(t);
       				 PORTB=0b0000000;
	  			 _delay_ms(t);
	  		 	   PORTB=0b00000000;
				_delay_ms(2.5*t);	break;  

case 'S':                	  PORTB=0b01001110;
	  			 _delay_ms(t);
	  			 PORTB=0b01001001;
	  			 _delay_ms(5*t);
	  			 PORTB=0b00110001;
	  			 _delay_ms(t);
	  			 
	   	 		  PORTB=0b00000000;
				_delay_ms(2.5*t);break;	


case '*':                    PORTB=0b00100010;
	   _delay_ms(t);
	   PORTB=0b00010100;
	   _delay_ms(t);
	   PORTB=0b00001000;
	   _delay_ms(t);
	   PORTB=0b01111111;
	   _delay_ms(t);
	   PORTB=0b00001000;
	   _delay_ms(t);
	   PORTB=0b00010100;
	   _delay_ms(t);
        PORTB=0b00100010;
	   _delay_ms(t);
	   	   PORTB=0b00000000;
	_delay_ms(2.5*t);	   break;   

case '!':      PORTB=0b00000000;
	   _delay_ms(3*t);
	   PORTB=0b01011111;
	   _delay_ms(t);
	  
	   PORTB=0b00000000;
	   _delay_ms(3*t);
	  PORTB=0b00000000;
	  _delay_ms(2.5*t);	   break; 
case ' ':    PORTB=0b00000000;
	  _delay_ms(9.5*t);break;
}
}