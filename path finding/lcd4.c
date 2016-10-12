                                                                     
                                                                     
                                                                     
                                             
#include<avr/io.h>
#include<util/delay.h>
#define P1 PORTB   //data port n controller

#define P3 DDRB  //data port

#define rs 4

#define e  5 
 
#define LCD_EN 1<<e
#define LCD_RS 1<<rs

  /********************************   data ports conneted to p1 0,p1 1,p1 2,p1 3        ***************************************/



/*********************************	delay(time to be delayed by b,b)	****************************************************************/

/*********************************	data(char d); gives data d to the pins 	       *********************************************************/
/*********************************	instruction(char i);  sets instruction i on the pins	     *******************************************/

/*********************************	pos(int row , int column)	 ***********************************************************************/
/*********************************	character(char c);  sets character c to the pins       	************************************************/
/*********************************	number(int n);  displays number n to the screen	        ************************************************/
/*********************************	initiate();  used t initiate the LCD   	    ************************************************************/
/*********************************      string(char c[],int d); where d is the delay between each character of the string***********************/
/*********************************	 number2(float n,int p);  displays floating number n to the screen to p places***************************/	        

                
                   

		void delay(int b,int a)
		{
	         for(;a>0;a--)
		    _delay_ms(b);
		}

           void port()
{

P3=0xFF;P1=0x00;
}



		

		

		void data (unsigned char dat)
{
P1 = (((dat >> 4) & 0x0F)|LCD_EN|LCD_RS);
P1 = (((dat >> 4) & 0x0F)|LCD_RS);

P1 = ((dat & 0x0F)|LCD_EN|LCD_RS);
P1 = ((dat & 0x0F)|LCD_RS);

_delay_us(200);
_delay_us(200);
}


		void instruction(char cmd)
{
P1= ((cmd >> 4) & 0x0F)|LCD_EN;
P1 = ((cmd >> 4) & 0x0F);

P1 = (cmd & 0x0F)|LCD_EN;
P1 = (cmd & 0x0F);

_delay_us(200);
_delay_us(200);
}
		





		void pos(short int r,short int c)                 //sets position of the cursor to the Rth roe and Cth column
		{  
	     	  if(r==1)
    	           {  instruction(127+c); 
	  	   }
    	  	  if(r==2)
   		   { instruction(191+c);
 		   }
		}


		void character(char c)
		{
		   data(c);  
	
		}


		void string(char c[],int d)
		{ 
		   short int i=0;
   		     while(*c)
	     	   { 
		        if(i==16)
			{ 
		 	 instruction(0xC0);
			}
		      character(*c++);_delay_ms(d);i++;
     
		    }

 		}


		void digit(int a)
		{
		  data(48+a);
		}


		void number(int num)
		{ 
 		   int str[5],c=0;
		   if(num==0)
		      digit(0);
		   else   
			   while(num)
			{   str[c]=(num%10);c++;num/=10;
			}
			   while(c!=0)
			{ c--;digit(str[c]);
			}

		}
 		 void number2(float n,int p)
		{    int a,c;
   	  	     a=n;
  		     n=n-a;
   		    for(c=1;c<=p;c++)
  		     n=n*10;
  		     number(a);character('.');
  		     number(n);
   

		}
void reset()
{
P1= 0xFF;
_delay_ms(20);
P1 = 0x03+LCD_EN;
P1 = 0x03;
_delay_ms(10);
P1 = 0x03+LCD_EN;
P1 = 0x03;
_delay_ms(1);
P1 = 0x03+LCD_EN;
P1 = 0x03;
_delay_ms(1);
P1 = 0x02+LCD_EN;
P1 = 0x02;
_delay_ms(1);
}
		void initiate()
{port();
reset(); // Call LCD reset
_delay_us(400);
instruction(0x28); // 4-bit mode - 2 line - 5x7 font.
instruction(0x0C); // Display no cursor - no blink.
instruction(0x06); // Automatic Increment - No Display shift.
instruction(0x80); // Address DDRAM with 0 offset 80h.
}   




