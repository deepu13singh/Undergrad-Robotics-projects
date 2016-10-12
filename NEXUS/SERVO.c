
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


unsigned char set_number = 0;           // selecting the ser of servo		
unsigned char angle_upper_byte = 0; 	// temprory storing upper byte of desired angle value 
unsigned char angle_lower_byte = 0; 	// temprory storing lower byte of desired angle value 
unsigned char degree = 0;                           
// final storing of temprory variable for individual servo as upper & lower bytes
unsigned char angle_upper_byte_servo2, angle_lower_byte_servo2, 
              angle_upper_byte_servo3, angle_lower_byte_servo3, 
			  angle_upper_byte_servo4, angle_lower_byte_servo4;
unsigned char angle_upper_byte_servo5, angle_lower_byte_servo5, 
			  angle_upper_byte_servo6, angle_lower_byte_servo6, 
			  angle_upper_byte_servo7, angle_lower_byte_servo7;

//--------------------------------------------------------------------------------
//port initialisation for Servos i/p's												
//--------------------------------------------------------------------------------																			
void servo_pin_config (void)
{ 
 DDRJ  = 0xFE;    //PJ 1,2,3,4,5,6,7 as output
 PORTJ = 0x00;
}

//--------------------------------------------------------------------------------
// reset & set function of servos
//--------------------------------------------------------------------------------
void reset_servo2 (void)
{ PORTJ = PORTJ & 0xFD; }

void set_servo2 (void)
{ PORTJ = PORTJ | 0x02; }

void reset_servo3 (void)
{ PORTJ = PORTJ & 0xFB; }

void set_servo3 (void)
{ PORTJ = PORTJ | 0x04; }

void reset_servo4 (void)
{ PORTJ = PORTJ & 0xF7; }

void set_servo4 (void)
{ PORTJ = PORTJ | 0x08; }

void reset_servo5 (void)
{ PORTJ = PORTJ & 0xEF; }

void set_servo5 (void)
{ PORTJ = PORTJ | 0x10; }
void reset_servo6 (void)
{ PORTJ = PORTJ & 0xDF; }

void set_servo6 (void)
{ PORTJ = PORTJ | 0x20; }

void reset_servo7 (void)
{ PORTJ = PORTJ & 0xBF; }

void set_servo7 (void)
{ PORTJ = PORTJ | 0x40; }

//--------------------------------------------------------------------------------
//TIMER1 initialize - prescale:1
// WGM: 0) Normal, TOP=0xFFFF
// desired value: 400Hz
// actual value: 400.007Hz (0.0%) = 2.5ms
//--------------------------------------------------------------------------------
void timer1_init(void)
{ 
 TCCR1B = 0x00; //stop
 TCNT1H = 0x70; //setup
 TCNT1L = 0x01;
 OCR1AH = 0x8F;
 OCR1AL = 0xFF;
 OCR1BH = 0x8F;
 OCR1BL = 0xFF;
 OCR1CH = 0x00;
 OCR1CL = 0x00;
 ICR1H  = 0x8F;
 ICR1L  = 0xFF;
 TCCR1A = 0x00;
 TCCR1C = 0x00;
 TCCR1B = 0x01; //start Timer
}

//--------------------------------------------------------------------------------
// timer1 comparatorA match with timer register ISR,
// This ISR used for reset servo on set number 
//--------------------------------------------------------------------------------
ISR(TIMER1_COMPA_vect)
{
 //compare occured TCNT1=OCR1A
 if (set_number == 0) { reset_servo2(); }
 if (set_number == 1) { reset_servo3(); }
}

//--------------------------------------------------------------------------------
// timer1 comparatorB match with timer register ISR,
// This ISR used for reset servo set number
//--------------------------------------------------------------------------------
ISR(TIMER1_COMPB_vect)
{
 //compare occured TCNT1=OCR1B
 if (set_number == 0) { reset_servo4(); }
 if (set_number == 1) { reset_servo5(); }
}

//--------------------------------------------------------------------------------
// timer1 comparatorC match with timer register ISR,
// This ISR used for reset servo set number
//--------------------------------------------------------------------------------
ISR(TIMER1_COMPC_vect)
{
 //compare occured TCNT1=OCR1c
 if (set_number == 0) { reset_servo6(); }
 if (set_number == 1) { reset_servo7(); }
}

//--------------------------------------------------------------------------------
// timer1 overflow ISR,
// This ISR can be used to load the PWM value. Here Servo motors move between 0 to
// 180 degrees proportional to the pulse train with the on time of 1 to 2 ms with
// the frequency between 40 to 60 Hz. ie. 400Hz/8 = 50Hz
//--------------------------------------------------------------------------------
ISR(TIMER1_OVF_vect)
{
 //TIMER1 has overflowed
 TCNT1H = 0x70; //reload counter high value	for 400Hz	
 TCNT1L = 0x01; //reload counter low value for 400Hz

 set_number ++;

 if (set_number>7)     				// 400Hz/8 = 50Hz
 {
  	set_number = 0;
 }

 if (set_number == 0)               // 1st set of servo motor
 {
  set_servo2(); 
  set_servo4(); 
  set_servo6();
  OCR1AH = angle_upper_byte_servo2;
  OCR1AL = angle_lower_byte_servo2;
  OCR1BH = angle_upper_byte_servo4;
  OCR1BL = angle_lower_byte_servo4;
  OCR1CH = angle_upper_byte_servo6;
  OCR1CL = angle_lower_byte_servo6;
 }
 
 if (set_number == 1)               // 2nd set of servo motor   
 {
  set_servo3(); 
  set_servo5(); 
  set_servo7();
  OCR1AH = angle_upper_byte_servo3;
  OCR1AL = angle_lower_byte_servo3;
  OCR1BH = angle_upper_byte_servo5;
  OCR1BL = angle_lower_byte_servo5;
  OCR1CH = angle_upper_byte_servo7;
  OCR1CL = angle_lower_byte_servo7;
 }
 
}

//--------------------------------------------------------------------------------
// function for angular movement calculation
//--------------------------------------------------------------------------------
void angle_value_calculation (void)
{
 unsigned int angle_value = 0;
 unsigned int temp = 0;

 if (degree > 180)
 degree = 180; // limiting the scope of the servo rotation

 //angle_value = 0xA240 + (89 * (unsigned char) degree); //for 1ms to 2 ms for 0 to 180degree  //16MHz
 //angle_value = 41536 + (89 * (unsigned char) degree);  //for 1ms to 2 ms for 0 to 180degree//16MHz
													     // actual constant is 88.88  
 //angle_value = 0xA999 + (81 * (unsigned char) degree); //for 1ms to 2 ms for 0 to 180degree // 14.4756MHz
 angle_value = 43417 + (81 * (unsigned char) degree);    //for 1ms to 2 ms for 0 to 180degree // 14.4756MHz
													     //actual constant is 81.91
														  
 angle_lower_byte = (unsigned char) angle_value;         //separating the lower byte
 
 temp = angle_value >> 8;
 angle_upper_byte = (unsigned char) temp;                //separating the upper byte
}


//---------------------.-----------------------------------------------------------
// Function for individual servo angle calculation call with degree as parameter & 
// store into respective variables. 
//--------------------------------------------------------------------------------

void angle_servo2 (unsigned char angle)                // for servo2 
{
 degree = angle;
 angle_value_calculation();
 angle_upper_byte_servo2 = angle_upper_byte;
 angle_lower_byte_servo2 = angle_lower_byte;
}

void angle_servo3 (unsigned char angle)                // for servo3 
{
 degree = angle;
 angle_value_calculation();
 angle_upper_byte_servo3 = angle_upper_byte;
 angle_lower_byte_servo3 = angle_lower_byte;
}

void angle_servo4 (unsigned char angle)                // for servo4 
{
 degree = angle;
 angle_value_calculation();
 angle_upper_byte_servo4 = angle_upper_byte;
 angle_lower_byte_servo4 = angle_lower_byte;
}

void angle_servo5 (unsigned char angle)                // for servo5 
{
 degree = angle;
 angle_value_calculation();
 angle_upper_byte_servo5 = angle_upper_byte;
 angle_lower_byte_servo5 = angle_lower_byte;
}

void angle_servo6 (unsigned char angle)                // for servo6 
{
 degree = angle;
 angle_value_calculation();
 angle_upper_byte_servo6 = angle_upper_byte;
 angle_lower_byte_servo6 = angle_lower_byte;
}

void angle_servo7 (unsigned char angle)                // for servo7
{
 degree = angle;
 angle_value_calculation();
 angle_upper_byte_servo7 = angle_upper_byte;
 angle_lower_byte_servo7 = angle_lower_byte;
}

//--------------------------------------------------------------------------------
//call this routine to initialize all peripherals
//--------------------------------------------------------------------------------
void init_devices_servo(void)
{
 //stop errant interrupts until set up
 cli();                                // disable all interrupts

 servo_pin_config();                   // servo configuration 
 timer1_init();                        // initilize timer1

 TIMSK1 = 0x0F;                        // timer1 interrupt sources
 
 sei(); //re-enable interrupts
 //all peripherals are now initialized
}


void down()
{
angle_servo2(164);
angle_servo3(164);
}
void up()
{
 angle_servo2(120); 
 angle_servo3(120);
}
void release()
{
angle_servo4(0);
 angle_servo5(180);
}
void grab()
{
 angle_servo4(140);
  angle_servo6(30);
  angle_servo5(30);
}