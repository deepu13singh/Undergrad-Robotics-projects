#include<avr/io.h>
#include<util/delay.h>
#define P1 PORTC   //data port
#define P2 PORTD   //controlling port
#define P3 DDRC   //data DDR
#define P4 DDRD	//control DDR
#define rs 3
#define rw 4
#define e  5 
 


  /********************************           ***************************************/



/*********************************	delay(time to be delayed by b,b)	****************************************************************/
/*********************************	act();  sets e=1 then e=0	 ***********************************************************************/
/*********************************	dmode();  sets rs to 1	      **************************************************************************/
/*********************************	imode();  sets rs to 0	      **************************************************************************/
/*********************************	data(char d); gives data d to the pins 	       *********************************************************/
/*********************************	instruction(char i);  sets instruction i on the pins	     *******************************************/
/*********************************	wmode();  sets rw to 0	      **************************************************************************/
/*********************************	rmode();  sets rw to 1        **************************************************************************/
/*********************************	pos(int row , int column)	 ***********************************************************************/
/*********************************	character(char c);  sets character c to the pins       	************************************************/
/*********************************	number(int n);  displays number n to the screen	        ************************************************/
/*********************************	initiate();  used t initiate the LCD   	    ************************************************************/
/*********************************      string(char c[],int d); where d is the delay between each character of the string***********************/
/*********************************	 number2(float n,int p);  displays floating number n to the screen to p places***************************/	        

        void initalise(void)
		{
		_delay_ms(20);	//Wait for abour 20mS	

		data(0x30);	//Send the first init value (0x30)	
		_delay_ms(10);	//Wait for about 10mS	

		data(0x30);	//Send second init value (0x30)	

		_delay_ms(1);	//Wait for about 1mS		

		data(0x30);	//Send third init value (0x30)	

		_delay_ms(1);	//Wait for 1mS	

		instruction(0x28);	//Select bus width (0x30 - for 8-bit and 0x20 for 4-bit)		
		_delay_ms(1);	//Wait for 1mS  	
		}
                   

		void delay(int a,int b)
		{
	         for(;a>0;a--)
		    _delay_ms(b);
		}


		void port()
		{ 
		   P3=0xFF;
		   P4=0xFF;
		   P1=0x00;
		   P2=0x00;
		}


		void act()                  //Enables and disables
		{
		   P2|=(1<<e);//e=1
		   _delay_ms(2);
		   P2&=~(1<<e);//e=0
		   _delay_ms(2);
		}


		void dmode()                  //    rs=1                
		{
		  P2|=(1<<rs);
		}

		void imode()
		{  
		  P2&=~(1<<rs);           //rs=0
		}

		void data(char d)
		{ 
		  dmode();
  		  P1=d;
		  act();
		}


		void instruction(char i)
		{
 		  imode();
		  P1=i;
		  act();
		}
		

		void wmode()
		{
		  P2&=~(1<<rw);    //wmode
		}


		void rmode()
		{
		  P2|=(1<<rw); 
		} 


		void pos(short int r,short int c)                 //sets position of the cursor to the Rth roe and Cth column
		{  
	     	  if(r==1)
    	           {  imode(); P1=(127+c);act();  
	  	   }
    	  	  if(r==2)
   		   { imode();P1=(191+c);act();
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
		 	 instruction(0xC0);dmode();
			}
		      character(*c++);_delay_ms(d);i++;
     
		    }

 		}


		void digit(short int a)
		{
		   dmode();P1=(48+a);act();
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
  		     number(a);character(".");
  		     number(n);
   

		}

		void initiate()
		{
  		    imode();
 		    wmode();
		    P1=0x01;act();       
		    P1=0x38;act();   	 
		    P1=0X0C;act();	
		    P1=0x06;act();     
		    P1=0x80;act();	

		}    



