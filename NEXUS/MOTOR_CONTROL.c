
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void port_init_motor (void)
{
 DDRA = DDRA | 0x0F;    //set direction of the PORTA 3 to PORTA 0 pins as output
 PORTA = PORTA & 0xF0;  // set initial value of the PORTA 3 to PORTA 0 pins to logic 0
 DDRL = DDRL | 0x18;    //Setting PL3 and PL4 pins as output for PWM generation
 PORTL = PORTL | 0x18;  //PL3 and PL4 pins are for velocity control using PWM
}

//Function to initialize ports


//TIMER5 initialize - prescale:1024
// WGM: 5) PWM 8bit fast, TOP=0x00FF
// timer5 value: 56.250Hz
void timer5_init(void)
{
 TCCR5B = 0x00; //stop
 TCNT5H = 0xFF; //setup
 TCNT5L = 0x01;
 OCR5AH = 0x00;
 OCR5AL = 0xFF;
 OCR5BH = 0x00;
 OCR5BL = 0xFF;
 OCR5CH = 0x00;
 OCR5CL = 0xFF;
 ICR5H  = 0x00;
 ICR5L  = 0xFF;
 TCCR5A = 0xA9;
 TCCR5C = 0x00;
 TCCR5B = 0x0D; //start Timer
}

// Function for robot velocity control
void set_PWM_value(unsigned char value) 	//set 8 bit PWM value
{
 OCR5AH = 0x00;
 OCR5AL = value;
 OCR5BH = 0x00;
 OCR5BL = value;
}

//Function used for setting motor's direction
void motion_set (unsigned char Direction)
{
 unsigned char PortARestore = 0;

 Direction &= 0x0F; 			// removing upper nibbel as it is not needed
 PortARestore = PORTA; 			// reading the PORTA's original status
 PortARestore &= 0xF0; 			// setting lower direction nibbel to 0
 PortARestore |= Direction; 	// adding lower nibbel for direction command and restoring the PORTA status
 PORTA = PortARestore; 			// setting the command to the port
}

void forward (void) 		//both inputs forward
{  	
  motion_set(0b00000110);//0b00000110
}
void back (void) 			//both inputs backward
{ 
  motion_set(0b00001001); //0b00001001
}

void left (void) 			//input12 backward, input34 forward
{	

 motion_set(0b00000101); // 0b00000101;
}

void right (void) 			//input34 backward, input12 forward
{	

  motion_set(0b00001010); //0b00001010
}

void soft_left (void) 		//input12 stationary, input34 forward
{	
 motion_set(0b00000111); //0b00000100
}

void soft_right (void)      //input12 forward, input34 stationary
{	
 motion_set(0b00001110);//0b00000010
}

void soft_left_2 (void)     //input12 backward, input34 stationary
{	
 motion_set(0b00001101); //0b00000001
}

void soft_right_2 (void)    //input12 stationary, input34 backward
{	
 motion_set(0b00001011); //0b00001000
}

void stop (void)            // both input stationary
{
  motion_set(0x0F);
}

void init_devices_motor (void)
{
 cli(); //Clears the global interrupts
 port_init_motor();
 timer5_init();
 sei(); //Enables the global interrupts
}


//Main 

