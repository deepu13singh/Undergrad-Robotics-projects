#include <avr/eeprom.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "solve.c"
#include "adc.c" 
#include "LCD.c"     //lcd include
#include "SERVO.c"  // angle_servo3(34);
#include "MOTOR_CONTROL.c"  //motor
const int L_ADD = 5;
#define P1 PINK
#define P2 PING
#define tcount 16
int fcount =8;

int HIGH ;
int MID ;
int LOW ;
int cas=0,ca=0,dan,dir=0;
char arr[6][6];
int count=0;

void init()
{
DDRK=0x00;
DDRH=0x00;
PORTK=0x00;
PORTH=0xFF;
}

void line(int what)
{ 
//cli();
sei();
int t=0,temp=0,cd;


while(1)
{



if(what==1)
{cd=0;
//if((P2&0b11) ==0b11 && count > 26)
if(P1&0b1) cd++; if(P1&0b10) cd++;if(P1&0b100) cd++; if(P2&0b10) cd++;if(P2&0b1) cd++; if(P1&0b10000000) cd++; if(P1&0b1000000) cd++;if(P1&0b100000) cd++; if(P1&0b10000) cd++; if(P1&0b1000) cd++; 
if(cd>6 && count> 20)
{stop(); break;}
}
//what =3 follow right bridge
if(what==3)
{
if(P2&0b1 && count > 33)
temp=23;

if(temp==23 && P1&0b10000000)
{stop();break;}

}


//what =4 follow left bridge
if(what==4)
{
if(P2&0b10 && count > 36)
temp=23;

if(temp==23 && P1&0b1)
{stop();break;}

}

if(what>5)
{
if(count>what)
{stop();break;}
}

if(what==-1)// line follow till block
{
if(PINH & 0b01000000)
{stop();break;}
}

if((P1 & 0b11111111) == 0b00011000 && (P2 & 0b11) == 0b00 ) //1
  {   t=1; 
  set_PWM_value(HIGH);
   forward();// lcd_cursor(1,1); lcd_string("0000XX0000");
                 
  }
if((P1 & 0b11111111) == 0b00001100 && (P2 & 0b11) == 0b00 ) //2
  {   t=1;
  set_PWM_value(LOW);
   soft_right();  //  lcd_cursor(1,1); lcd_string("00000XX000");
  				  
  }
if((P1 & 0b11111111) == 0b00110000 && (P2 & 0b11) == 0b00 ) //3
  {   t=1; 
  set_PWM_value(LOW);
  soft_left();      //    lcd_cursor(1,1); lcd_string("000XX00000"); 
  					
  }
if((P1 & 0b11111111) == 0b00001000 && (P2 & 0b11) == 0b00 ) //4
  {  t=1; 
  set_PWM_value(MID);
   soft_right();  
  				
  }
if((P1 & 0b11111111) == 0b00010000 && (P2 & 0b11) == 0b00 ) //5
  {   t=1; 
  set_PWM_value(MID);
    soft_left();    
  				
  }
if((P1 & 0b11111111) == 0b01110000 && (P2 & 0b11) == 0b00 ) //6
  {   t=1;    
  set_PWM_value(LOW);
  soft_left();
     
  			  
  }
if((P1 & 0b11111111) == 0b00001110 && (P2 & 0b11) == 0b00 )//7
  {     t=1;    
  set_PWM_value(LOW);
    soft_right();
    
  			    
  }
if((P1 & 0b11111111) == 0b01101100 && (P2 & 0b11) == 0b00 )//8
  {    t=1;    set_PWM_value(MID); 
  if(what==4)
    soft_left();
else 
   soft_right();    
                 
  			 
  }
  if((P1 & 0b11111111) == 0b11001100 && (P2 & 0b11) == 0b00 )//9
  {    t=1;    set_PWM_value(MID); 
   if(what==4)
    soft_left();
else  soft_right();    
                 //  lcd_cursor(1,1); lcd_string("0000XXXX00");  
  			 
  }
  if((P1 & 0b11111111) == 0b01001100 && (P2 & 0b11) == 0b00 )//10
  {    t=1;    set_PWM_value(MID); 
   if(what==4)
    soft_left();
else  soft_right();    
                 //  lcd_cursor(1,1); lcd_string("0000XXXX00");  
  			 
  }
  if((P1 & 0b11111111) == 0b10001100 && (P2 & 0b11) == 0b00 )//11
  {    t=1;    set_PWM_value(MID); 
   if(what==4)
    soft_left();
else  soft_right();    
                 //  lcd_cursor(1,1); lcd_string("0000XXXX00");  
  			 
  }
  if((P1 & 0b11111111) == 0b10001100 && (P2 & 0b11) == 0b10 )//12
  {    t=1;    set_PWM_value(MID); 
   if(what==4)
    soft_left();
else  soft_right();    
                 //  lcd_cursor(1,1); lcd_string("0000XXXX00");  
  			 
  }
  if((P1 & 0b11111111) == 0b11001100 && (P2 & 0b11) == 0b10 )//13
  {    t=1;    set_PWM_value(MID);
   if(what==4)
    soft_left();
else   soft_right();    
                 //  lcd_cursor(1,1); lcd_string("0000XXXX00");  
  			 
  }
    if((P1 & 0b11111111) == 0b11110000 && (P2 & 0b11) == 0b00 )//14
  {    t=1;     set_PWM_value(MID); soft_left();    
                  // lcd_cursor(1,1); lcd_string("00XXXX0000");  
  			    
  }
if((P1 & 0b11111111) == 0b00110110 && (P2 & 0b11) == 0b00 )//15
  {      t=1;        
                set_PWM_value(LOW);
				 if(what==3)
    soft_right();
else 
                soft_left();
				
				  // lcd_cursor(1,1); lcd_string("0000XX0XX0");  
  			  
  }
if((P1 & 0b11111111) == 0b10110000 && (P2 & 0b11) == 0b00 )//16
  {      t=1;        
               set_PWM_value(LOW);
                soft_left();
				
				  // lcd_cursor(1,1); lcd_string("0XX0XX0000");  
  			    
  }
if((P1 & 0b11111111) == 0b00110010 && (P2 & 0b11) == 0b00 )//17
  {       t=1;       
                set_PWM_value(LOW);
				 if(what==3)
   {  set_PWM_value(MID);soft_right();}
else 
  soft_left();
				 
				 //  lcd_cursor(1,1); lcd_string("0000XX00X0");  
  			   
  }
 if((P1 & 0b11111111) == 0b00110000 && (P2 & 0b11) == 0b01 )//18
  {       t=1;       
                set_PWM_value(LOW);
				 if(what==3)
   {  set_PWM_value(HIGH);soft_right();}
else 
  soft_left();
				
				 //  lcd_cursor(1,1); lcd_string("0X00XX0000");  
  			  
  }
 if((P1 & 0b11111111) == 0b00110100 && (P2 & 0b11) == 0b00 )//19
  {        t=1;      
                 set_PWM_value(LOW);
				  if(what==3)
   {  set_PWM_value(MID);soft_right();}
else 
  soft_left();
				 
				  // lcd_cursor(1,1); lcd_string("0000XX0X00");  
  			    
  }
if((P1 & 0b11111111) == 0b00110001 && (P2 & 0b11) == 0b01 )//20
  {       t=1;       
                set_PWM_value(LOW);
				 if(what==3)
   {  set_PWM_value(HIGH);soft_right();}
else 
  soft_left();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  if((P1 & 0b11111111) == 0b00110011 && (P2 & 0b11) == 0b00 )//21
  {        t=1;      
                 set_PWM_value(LOW);
				  if(what==3)
   {  set_PWM_value(MID);soft_right();}
else 
  soft_left();
				 
				  // lcd_cursor(1,1); lcd_string("0000XX00XX");  
  			    
  }
  if((P1 & 0b11111111) == 0b00110000 && (P2 & 0b11) == 0b10 )//22
  {       t=1;       
                set_PWM_value(LOW);
  soft_left();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }

  if((P1 & 0b11111111) == 0b01110000 && (P2 & 0b11) == 0b10 )//23
  {       t=1;       
                set_PWM_value(LOW);
  soft_left();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  if((P1 & 0b11111111) == 0b10110000 && (P2 & 0b11) == 0b10 )//24
  {       t=1;       
                set_PWM_value(LOW);
  soft_left();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  if((P1 & 0b11111111) == 0b00110111 && (P2 & 0b11) == 0b00 )//25
  {       t=1;       
                set_PWM_value(LOW);
				 if(what==3)
   {  set_PWM_value(MID);soft_right();}
else 
  soft_left();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  if((P1 & 0b11111111) == 0b00110011 && (P2 & 0b11) == 0b01 )//26
  {       t=1;       
                set_PWM_value(LOW);
				 if(what==3)
   {  set_PWM_value(MID);soft_right();}
else 
  soft_left();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  if((P1 & 0b11111111) == 0b00110001 && (P2 & 0b11) == 0b00 )//27
  {       t=1;       
                set_PWM_value(LOW);
				 if(what==3)
   {  set_PWM_value(MID);soft_right();}
else 
  soft_left();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  if((P1 & 0b11111111) == 0b01100011 && (P2 & 0b11) == 0b01 )//28
  {       t=1;       
                set_PWM_value(LOW);
				 if(what==3)
   {  set_PWM_value(MID);soft_right();}
else 
  soft_left();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  if((P1 & 0b11111111) == 0b01100011 && (P2 & 0b11) == 0b01 )//29
  {       t=1;       
                set_PWM_value(LOW);
				 if(what==3)
   {  set_PWM_value(MID);soft_right();}
else 
  soft_left();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  if((P1 & 0b11111111) == 0b01100111 && (P2 & 0b11) == 0b00 )//30
  {       t=1;       
                set_PWM_value(LOW);
				 if(what==3)
   {  set_PWM_value(MID);soft_right();}
else 
  soft_left();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  if((P1 & 0b11111111) == 0b00011011 && (P2 & 0b11) == 0b01 )//40
  {       t=1;       
                set_PWM_value(HIGH);
				 if(what==3)
   {  set_PWM_value(MID);soft_right();}
else 
  forward();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
    if((P1 & 0b11111111) == 0b00011001 && (P2 & 0b11) == 0b01 )//41
  {       t=1;       
                set_PWM_value(HIGH);
				 if(what==3)
   {  set_PWM_value(MID);soft_right();}
else 
  forward();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
    if((P1 & 0b11111111) == 0b00011101 && (P2 & 0b11) == 0b00 )//42
  {       t=1;       
                set_PWM_value(HIGH);
				 if(what==3)
   {  set_PWM_value(MID);soft_right();}
else 
  forward();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
    if((P1 & 0b11111111) == 0b00011001 && (P2 & 0b11) == 0b00 )//43
  {       t=1;       
                set_PWM_value(HIGH);
				 if(what==3)
   {  set_PWM_value(HIGH);soft_right();}
else 
  forward();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
    if((P1 & 0b11111111) == 0b00011000 && (P2 & 0b11) == 0b01 )//44
  {       t=1;       
                set_PWM_value(HIGH);
				 if(what==3)
   {  set_PWM_value(HIGH);soft_right();}
else 
  forward();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
    if((P1 & 0b11111111) == 0b00011010 && (P2 & 0b11) == 0b00 )//45
  {       t=1;       
                set_PWM_value(HIGH);
				 if(what==3)
   {  set_PWM_value(MID);soft_right();}
else 
  forward();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }


    if((P1 & 0b11111111) == 0b00001000 && (P2 & 0b11) == 0b01 )//60
  {       t=1;       
                set_PWM_value(MID);
  soft_right();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  if((P1 & 0b11111111) == 0b00001001 && (P2 & 0b11) == 0b01 )//61
  {       t=1;       
                set_PWM_value(MID);
  soft_right();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }

  if((P1 & 0b11111111) == 0b00001001 && (P2 & 0b11) == 0b00 )//62
  {       t=1;       
                set_PWM_value(MID);
  soft_right();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
 
  if((P1 & 0b11111111) == 0b00001011 && (P2 & 0b11) == 0b00 )//64
  {       t=1;       
                set_PWM_value(MID);
  soft_right();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  if((P1 & 0b11111111) == 0b00001011 && (P2 & 0b11) == 0b01 )//65
  {       t=1;       
                set_PWM_value(MID);
  soft_right();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  if((P1 & 0b11111111) == 0b00001100 && (P2 & 0b11) == 0b01 )//66
  {       t=1;       
                set_PWM_value(MID);
  soft_right();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  if((P1 & 0b11111111) == 0b00001111 && (P2 & 0b11) == 0b01 )//67
  {       t=1;       
                set_PWM_value(MID);
  soft_right();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  if((P1 & 0b11111111) == 0b00001101 && (P2 & 0b11) == 0b01 )//68
  {       t=1;       
                set_PWM_value(MID);
  soft_right();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  if((P1 & 0b11111111) == 0b00000110 && (P2 & 0b11) == 0b00 )//69
  {       t=1;       
                set_PWM_value(MID);
  soft_right();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  if((P1 & 0b11111111) == 0b00000010 && (P2 & 0b11) == 0b00 )//70
  {       t=1;       
                set_PWM_value(MID);
  soft_right();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  if((P1 & 0b11111111) == 0b00000011 && (P2 & 0b11) == 0b00 )//71
  {       t=1;       
                set_PWM_value(MID);
  soft_right();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  if((P1 & 0b11111111) == 0b00000011 && (P2 & 0b11) == 0b01 )//72
  {       t=1;       
                set_PWM_value(MID);
  soft_right();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  if((P1 & 0b11111111) == 0b00000100 && (P2 & 0b11) == 0b00 )//73
  {       t=1;       
                set_PWM_value(MID);
  soft_right();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  if((P1 & 0b11111111) == 0b00000001 && (P2 & 0b11) == 0b01 )//74
  {       t=1;       
                set_PWM_value(MID);
  soft_right();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }

   if((P1 & 0b11111111) == 0b00000000 && (P2 & 0b11) == 0b01 )//75
  {       t=1;       
                set_PWM_value(HIGH);
  soft_right();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }



 if((P1 & 0b11111111) == 0b01110000 && (P2 & 0b11) == 0b00 )//90
  {       t=1;       
                set_PWM_value(LOW);
  soft_left();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
   if((P1 & 0b11111111) == 0b01100000 && (P2 & 0b11) == 0b00 )//91
  {       t=1;       
                set_PWM_value(LOW);
  soft_left();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
   if((P1 & 0b11111111) == 0b00110000 && (P2 & 0b11) == 0b00 )//92
  {       t=1;       
                set_PWM_value(LOW);
  soft_left();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
   if((P1 & 0b11111111) == 0b00100000 && (P2 & 0b11) == 0b00 )//93
  {       t=1;       
                set_PWM_value(LOW);
  soft_left();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
   if((P1 & 0b11111111) == 0b11100000 && (P2 & 0b11) == 0b00 )//94
  {       t=1;       
                set_PWM_value(LOW);
  soft_left();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
   if((P1 & 0b11111111) == 0b11100000 && (P2 & 0b11) == 0b10 )//95
  {       t=1;       
                set_PWM_value(LOW);
  soft_left();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
   if((P1 & 0b11111111) == 0b11110000 && (P2 & 0b11) == 0b00 )//96
  {       t=1;       
                set_PWM_value(LOW);
  soft_left();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
   if((P1 & 0b11111111) == 0b00010000 && (P2 & 0b11) == 0b00 )//97
  {       t=1;       
                set_PWM_value(LOW);
  soft_left();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
   if((P1 & 0b11111111) == 0b00111110 && (P2 & 0b11) == 0b00 )//98
  {       t=1;       
                set_PWM_value(LOW);
				 if(what==3)
   {  set_PWM_value(MID);soft_right();}
else 
  soft_left();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
   if((P1 & 0b11111111) == 0b00100111 && (P2 & 0b11) == 0b01 )//99
  {       t=1;       
                set_PWM_value(LOW);
				 if(what==3)
   {  set_PWM_value(MID);soft_right();}
else 
  soft_left();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }

    if((P1 & 0b11111111) == 0b10000000 && (P2 & 0b11) == 0b00 )//100
  {       t=1;       
                set_PWM_value(HIGH);
  soft_left();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }

    if((P1 & 0b11111111) == 0b10000000 && (P2 & 0b11) == 0b10 )//101
  {       t=1;       
                set_PWM_value(HIGH);
  soft_left();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
    if((P1 & 0b11111111) == 0b00000000 && (P2 & 0b11) == 0b10 )//102
  {       t=1;       
                set_PWM_value(HIGH);
  soft_left();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
    if((P1 & 0b11111111) == 0b01000000 && (P2 & 0b11) == 0b00 )//103
  {       t=1;       
                set_PWM_value(HIGH);
  soft_left();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
    if((P1 & 0b11111111) == 0b11000000 && (P2 & 0b11) == 0b00 )//104
  {       t=1;       
                set_PWM_value(HIGH);
  soft_left();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }






  
    if((P1 & 0b11111111) == 0b00011100  && (P2&0b11) == 0b00 )//105
  {       t=1;       
                set_PWM_value(HIGH);
					 if(what==3)
   {  set_PWM_value(LOW);soft_right();}
else 
  forward();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  
    if((P1 & 0b11111111) == 0b00011110 && (P2 & 0b11) == 0b00 )//106
  {       t=1;       
                set_PWM_value(HIGH);
					 if(what==3)
   {  set_PWM_value(MID);soft_right();}
else 
  forward();
				 
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  
    if((P1 & 0b11111111) == 0b00111000 && (P2 & 0b11) == 0b00 )//107
  {       t=1;       
                set_PWM_value(HIGH);
					 if(what==4)
   {  set_PWM_value(LOW);soft_left();}
else 
  forward();
				 
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  
    if((P1 & 0b11111111) == 0b01111000 && (P2 & 0b11) == 0b00 )//108
  {       t=1;       
                set_PWM_value(HIGH);
					 if(what==4)
   {  set_PWM_value(MID);soft_left();}
else 
  forward();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  
    if((P1 & 0b11111111) == 0b00011000 && (P2 & 0b11) == 0b10 )//109
  {       t=1;       
               	 if(what==4)
   {  set_PWM_value(HIGH);soft_left();}
else 
  forward(); 
  			   
  }
  
    if((P1 & 0b11111111) == 0b10011000 && (P2 & 0b11) == 0b00 )//110
  {       t=1;       
                set_PWM_value(HIGH);	 if(what==4)
   {  set_PWM_value(HIGH);soft_left();}
else 
  forward();
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  
    if((P1 & 0b11111111) == 0b01011000 && (P2 & 0b11) == 0b00 )//111
  {       t=1;       
                set_PWM_value(HIGH);
  	 if(what==4)
   {  set_PWM_value(HIGH);soft_left();}
else 
  forward();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  
    if((P1 & 0b11111111) == 0b10011000 && (P2 & 0b11) == 0b10 )//112
  {       t=1;       
                set_PWM_value(HIGH);
  	 if(what==4)
   {  set_PWM_value(HIGH);soft_left();}
else 
  forward();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  
    if((P1 & 0b11111111) == 0b11011000 && (P2 & 0b11) == 0b00 )//113
  {       t=1;       
                set_PWM_value(HIGH);
  	 if(what==4)
   {  set_PWM_value(HIGH);soft_left();}
else 
  forward();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  
    if((P1 & 0b11111111) == 0b11011000 && (P2 & 0b11) == 0b10 )//114
  {       t=1;       
                set_PWM_value(HIGH);
 	 if(what==4)
   {  set_PWM_value(HIGH);soft_left();}
else 
  forward();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  
    if((P1 & 0b11111111) == 0b11000110 && (P2 & 0b11) == 0b00 )//115
  {       t=1;       
                set_PWM_value(HIGH);
 	 if(what==4)
   {  set_PWM_value(MID);soft_left();}
else 
  forward();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  
    if((P1 & 0b11111111) == 0b01100110 && (P2 & 0b11) == 0b00 )//116
  {       t=1;       
                set_PWM_value(HIGH);
  	 if(what==4)
   {  set_PWM_value(MID);soft_left();}
else 
  forward();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }
  
    if((P1 & 0b11111111) == 0b10000110 && (P2 & 0b11) == 0b10 )//117
  {       t=1;       
                set_PWM_value(HIGH);
  	 if(what==4)
   {  set_PWM_value(MID);soft_left();}
else 
  forward();
				 
				  // lcd_cursor(1,1); lcd_string("00X0XX0000");  
  			   
  }

  if(what==4)
  {
  if(P2&0b10)
   { t=1;set_PWM_value(HIGH);soft_left(); }
   if(P1&0b10000000)
   { t=1;set_PWM_value(HIGH);soft_left(); }
    if(P1&0b01000000)
   { t=1;set_PWM_value(MID);soft_left(); }
    if(P1&0b00100000)
   { t=1;set_PWM_value(LOW);soft_left(); }
  
  
  }

   if(what==3)
  {
  if(P2&0b1)
   { t=1;set_PWM_value(HIGH);soft_right(); }
   if(P1&0b00000001)
   { t=1;set_PWM_value(HIGH);soft_right(); }
    if(P1&0b00000010)
   { t=1;set_PWM_value(MID);soft_right(); }
    if(P1&0b00000100)
   { t=1;set_PWM_value(LOW);soft_right(); }
  
  
  }
  
   
    		   
  


  


  if(t==0)
 {//lcd_cursor(1,1); lcd_string("NOCONDITIO"); 
  set_PWM_value(MID);
 forward(); 
 }
 t=0;
 
} //while

 dan=0;
if( !(P1&0b1000) )
dan=4;


 if(!(P1&0b10000))
dan=4;

cas=8;
if(P2&0b10000)
cas=2;

if(P2&0b100000)
cas=3;


//_delay_ms(60);

if(P2&0b100)
cas=1;

if(P2&0b1000)
cas=0;


stop();
}


ISR(INT1_vect)
{

count++;
		
	//	lcd_string("N");
}
void enable()
{
DDRD  = DDRD & 0b11111101;  
 PORTD = PORTD | 0b00000010;

 //cli();  
 EIMSK |= (1<<INT1);            
	// EICRA &= ~(1<<ISC10);  EICRA &= ~(1<<ISC11); //low level
    
	 EICRA &= ~(1<<ISC10);  EICRA |= (1<<ISC11);//falling edge
    
//	EICRA |= (1<<ISC10) | (1<<ISC11); //rising edge 
//MCUCR = MCUCR | 0x08;
 
 //ICR = GICR | 0x80;   
	
		 //to Rx data from PC to MCU through serial comm
 sei();              //re-enable interrupts
 //all peripherals are now initialized

}
void turnleft(int a)

{
//cli();
count=0;
sei();
line(fcount);
set_PWM_value(MID);
left();count=0;



while(1 )
{
if(count > a && (P1&0b1000 || P1&0b10000 || P1&0b100000 || P1&0b100))
break;
}
stop();
}
void turnback(int a , int b )
{
count=0;
sei();
line(fcount);
if(b==10)
{
down();
_delay_ms(200);
release();
_delay_ms(200);
set_PWM_value(MID);
if(dir==0)
left();
else 
right();
count=0;
}
if(b==11)
{
down();
_delay_ms(200);
release();
_delay_ms(200);
set_PWM_value(MID);
if(dir==1)
left();
else 
right();
count=0;
}
if(b==2)
{right();
count=0;}



while( 1)
{
if(count > a && (P1&0b1000 || P1&0b10000 || P1&0b100000 || P1&0b100))
break;
}
stop();

}
void turnright(int a)

{
//cli();
count=0;
sei();
line(fcount);
set_PWM_value(MID);
right();count=0;


while( 1)
{
if(count > a && (P1&0b1000 || P1&0b10000 || P1&0b100000 || P1&0b100))
break;
}
stop();

}
void takediss2(int dest,int curr)
{
 if((dest - curr)==7)
 {
  if(dir==0)
   {
     if((arr[curr/6][curr%6+1]==2)||(arr[curr/6][curr%6+1]==6))
	{
		//break at right
count=0;

line(3);
 fcount=8;
dir=1;
	}
     else 
	{
	    	//turn right and break at left
	     turnright(tcount);
		 count=23;
		 line(4);
		 fcount=11;
dir=0;
	}
   }
 
 else if(dir==1)
   {
     if((arr[curr/6][curr%6+1]==2)||(arr[curr/6][curr%6+1]==6))
	{
		//turn left and break at right
		 turnleft(tcount);
		 count=23;
		
line(3);
 fcount=8;
dir=1;
	}
     else 
	{
		//break at left 
		count=0;

line(4);
fcount=11;
dir=0;
	}
   }

 }


 else if((dest - curr)== -5)
 {
  if(dir==0)
   {
     if((arr[curr/6][curr%6+1]==3)||(arr[curr/6][curr%6+1]==7))
	{
		//break at left
			count=0;

line(4);
fcount=11;
dir=3;
	}
     else 
	{
		//turn left and break at right
		turnleft(tcount);
		 count=23;
		
line(3);
fcount=8;
dir=0;
	}
   }
 
 else if(dir==3)
   {
     if((arr[curr/6][curr%6+1]==3)||(arr[curr/6][curr%6+1]==7))
	{
		//turn right break at left
		 turnright(tcount);
		 count=23;
		 
line(4);
fcount=11;
dir=3;
	}
     else 
	{
		//break at right
		count=0;

line(3);
fcount=8;
dir=0;
	}
   }

 }


 else if((dest - curr)== -7)
 {
  if(dir==2)
   {
     if((arr[curr/6][curr%6-1]==0)||(arr[curr/6][curr%6-1]==4))
	{
		//break at right
		count=0;

line(3);
fcount=8;
dir=3;
	}
     else 
	{
		//turn right and break at left
		 turnright(tcount);
		 count=23;
		
line(4);
fcount=11;
dir=2;
	}
   }
 
 else if(dir==3)
   {
     if((arr[curr/6][curr%6-1]==0)||(arr[curr/6][curr%6-1]==4))
	{
		//turn left and break at right
		turnleft(tcount);
		 count=23;
		
line(3);
fcount=8;
dir=3;
	}
     else 
	{
		//break at left
			count=0;

line(4);
fcount=11;
dir=2;
	}
   }

 }


 else if((dest - curr)== 5)
 {
  if(dir==2)
   {
     if((arr[curr/6][curr%6-1]==1)||(arr[curr/6][curr%6-1]==5))
	{
		//break at left
			count=0;

line(4);
fcount=11;
dir=1;
	}
     else 
	{
		//turn left and break at right
		turnleft(tcount);
		 count=23;
		
line(3);
fcount=8;
dir=2;
	}
   }
 
 else if(dir==1)
   {
     if((arr[curr/6][curr%6-1]==1)||(arr[curr/6][curr%6-1]==5))
	{
		//turn right and break at left
		 turnright(tcount);
		 count=23;
		 
line(4);
fcount=11;
dir=1;
	}
     else 
	{
		//break at right
		count=0;

line(3);
fcount=8;
dir=2;
	}
   }

 }



}

int takediss(int final,int current)
{
 if( final - current == 1 )  
           {  if(dir==1)
		       {  turnleft(tcount); count=23; }
			   if(dir==0)
			      count=0;
              if(dir==2)
			  { turnback(tcount*2 - 2,2); count=23;}
			  if(dir==3)
			  { turnright(tcount); count=23;}
			  dir= 0;
			   line(1);
			   fcount=8;
		   }
		   if( final - current == -1 )  
           {  if(dir==1)
		       {  turnright(tcount); count=23; }
			   if(dir==0)
			      {  turnback(tcount*2 - 2,2); count=23; }
              if(dir==2)
			  { count=0;}
			  if(dir==3)
			  { turnleft(tcount); count=23;}
			    dir= 2;
				 line(1);
				 fcount=8;
		   }
		    if( final - current == 6 )  
           {  if(dir==1)
		       {  count=0; }
			   if(dir==0)
			      { turnright(tcount); count=23; }
              if(dir==2)
			  { turnleft(tcount); count=23;}
			  if(dir==3)
			  {  turnback(tcount*2 - 2,2); count=23; }
			 
			    dir= 1;
				 line(1);
				 fcount=8;
			  
		   }

            if( final - current == -6 )  
           {  if(dir==1)
		       {   turnback(tcount*2 - 2,2); count=23; }
			   if(dir==0)
			      { turnleft(tcount);count=23; }
              if(dir==2)
			  { turnright(tcount); count=23;}
			  if(dir==3)
			  { count=0; }
			   dir= 3;
			    line(1);
				fcount=8;
		   }  
  }


void readfromeeprom()  //  READING FROM EEPROM
{
 for(int x=0;x<=5;x++)
   for(int y=0;y<=5;y++)
     arr[x][y] = (eeprom_read_byte(L_ADD+ 6*x+y) - 48);
clear();
lcd_string("DATA RETved FROM");
lcd_cursor(2,1);lcd_string("EEPROM");
_delay_ms(1000);
lcd_cursor(1,1); 
for(int x=0;x<=5;x++)
   for(int y=0;y<=5;y++)
   {
if(6*x+y == 16)
lcd_cursor(2,1);   

   lcd_wr_char(arr[x][y]+48);
     
   }
  
	 
	// if(!(PINH & 0b00000010))
	 

}

void updaterelmat()   // udating the relational matrix with arr values
{  clear();
  lcd_string("rel updating");

for(int x=0;x<=5;x++)
  for(int y=0;y<=5;y++)
  {
    if(arr[x][y] == 0 || arr[x][y] ==4 )
	{     rel[6*(x-1) + y][6*x+y+1]=1;  
	      rel[6*x+y+1][6*(x-1) + y]=1;
	}
	if(arr[x][y] == 1 || arr[x][y] ==5 )
	{     rel[6*(x) + y+1][6*(x+1) + y]=1;  
	      rel[6*(x+1) + y][6*(x) + y+1]=1;
	}
	if(arr[x][y] == 2 || arr[x][y] ==6 )
	{     rel[6*(x+1) + y][6*x+y-1]=1;  
	      rel[6*x+y-1][6*(x+1) + y]=1;
	}
	if(arr[x][y] == 3 || arr[x][y] ==7 )
	{     rel[6*(x-1) + y][6*x+y-1]=1;  
	      rel[6*x+y-1][6*(x-1) + y]=1;
	}
  
  for(int x=0;x<=5;x++)
  for(int y=0;y<=5;y++)
  if((arr[x][y] >=4 && arr[x][y] <=7) || arr[x][y] == 12 )
    {
	worked[6*x+y]=1;
	for(int i=0;i<=35;i++)
	{
	 rel[6*x+y][i]=0;
     rel[i][6*x+y]=0;  
	}
    rel[6*x+y][6*x+y]=10;
	}
  }


}


void main()
{    init_devicesadc(); //adc
    init_devices_lcd(); // LCD INITIALIZATION
	lcd_set_4bit();
	lcd_init();
  init();
	init_devices_servo();  // SERVO INITIALIZATION
enable();
release();
down();
//_delay_ms(2000);


//grab();
//_delay_ms(2000);
up();
	init_devices_motor (); // l293d initialization
	
	lcd_string("HIGH  MID  LOW ");
	
	
	


//cli();

while(1)
  {
	HIGH=print_sensor(0);
			
	MID=print_sensor(1);		
	LOW=print_sensor(2);
    lcd_number(2,1,HIGH,3);
    lcd_number(2,7,MID,3);
    lcd_number(2,13,LOW,3);
//	if(!(PINH & 0b10000000))		 
     break;
	 
  }

	count=0;
	//turnleft(30);
//	blankmove();
//	line(11);
//	turnleft(tcount);
//	count=21;
count=0;
//	line(1);
/*	linefor(12);
	turnleft(tcount);
	line();
	  lcd_cursor(1,1);

*/
//eeprom_write_byte  (get,'X');



//lcd_wr_char(eeprom_read_byte(get) );
clear(); lcd_string("EEPROM clear ??");

	if(!(PINH & 0b00000010))		 
     {  clear(); lcd_string("Clearing EEPROM"); 
	 for(int x=0;x<=45;x++)
	 eeprom_write_byte  (x,'x');
	  clear(); lcd_string("EEPROM CLEARED");_delay_ms(1000);
	 
	  }
	  if(!(PINH & 0b00000001))
	 { clear(); lcd_string("EXITING WITHOUT CLEARING");_delay_ms(1000);}
	 
	 
char st;
st=eeprom_read_byte(0);
if(st=='A')
{
clear(); lcd_string(" DATA FOUND..... ");
st=eeprom_read_byte(1);

if(st!='B') //keep 1st block
{  
readfromeeprom();
set_matvalues();
prepare4new();
updaterelmat();
lcd_cursor(2,1);
lcd_string("done");
solve(0,5);
lcd_string("done solving");
clear();
int i;
for( i=top;i>=0;i--)
  { lcd_number(1,1,proc[i],2);
  //_delay_ms(1000);
}
line(-1);
down();
_delay_ms(200);
grab();
_delay_ms(200);
up();
turnback(tcount*2,2);
count=23;
line(1);


for( i=top;i>0;i--)
{
takediss(proc[i-1],proc[i]);
takediss2(proc[i-1],proc[i]);
}
turnback(2*tcount,10);
dir=(dir+2)%4;

for( i=0;i<top;i++)
{
takediss(proc[i+1],proc[i]);
takediss2(proc[i+1],proc[i]);
}


eeprom_write_byte(1,'B');


}

st=eeprom_read_byte(2);
if(st!='C') //keep 2nd block
{  
readfromeeprom();
set_matvalues();
prepare4new();
updaterelmat();
solve(0,35);
for( i=top;i>=0;i--)
  { //lcd_number(1,1,proc[i],2);
 // _delay_ms(1000);
}
if(dir==3)
turnleft(tcount);
line(-1);
down();
_delay_ms(200);
grab();
_delay_ms(200);
up();
turnback(tcount*2,2);
dir=0;
count=23;
line(1);


for( i=top;i>0;i--)
{
takediss(proc[i-1],proc[i]);
takediss2(proc[i-1],proc[i]);
}
turnback(tcount*2 ,11);
dir=(dir+2)%4;

for( i=0;i<top;i++)
{
takediss(proc[i+1],proc[i]);
takediss2(proc[i+1],proc[i]);
}

}



}
else {

clear(); lcd_string(" DATA NOT FOUND..... ");
_delay_ms(1000);
clear(); lcd_string(" DRY RUN... ");
_delay_ms(1000);
int x,y,current=-1;
/*
lcd_cursor(1,1);
lcd_string("cas dir dan X Y");
lcd_cursor(1,1);
*/
for(x=0;x<=5;x++)
{
  for(y=0;y<=5;y++)
  {
         takediss(6*x+y,current);
 
  
 
  if(cas>=0 && cas<=3)
  arr[x][y]=(cas+dir)%4+dan;
  else arr[x][y]=cas+dan;
    

  current=6*x+y;
  
  
/*
lcd_number(2,2,cas,1);
 lcd_number(2,6,dir,1);
lcd_number(2,10,dan,1);
lcd_number(2,13,current/6,1);
lcd_number(2,15,current%6,1);*/
  //_delay_ms(2000);
  }
  x++;
  for(y=5;y>=0;y--)
  {
  
 takediss(6*x+y,current);
  
 
  if(cas>=0 && cas<=3)
  arr[x][y]=(cas+dir)%4+dan;
  else arr[x][y]=cas+dan;
  
  current=6*x+y;
 /* 
lcd_number(2,2,cas,1);
 lcd_number(2,6,dir,1);
lcd_number(2,10,dan,1);
lcd_number(2,13,current/6,1);
lcd_number(2,15,current%6,1);
*/
  //_delay_ms(2000);
  }
}




//writing in eeprom
for(x=0;x<=5;x++)
 for(y=0;y<=5;y++)
{eeprom_write_byte  (L_ADD+6*x+y,arr[x][y]+48);

}
PORTC |= 0b00001000;
_delay_ms(500);
PORTC &= 0b11110111;
clear();


eeprom_write_byte(0,'A')  ;
lcd_string("DRY RUN COMPLETE");
}

}
