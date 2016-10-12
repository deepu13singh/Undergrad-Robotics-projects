/*----------------------------------------------------------------
--------------------------HEADER FILES----------------------------
-----------------------------------------------------------------*/

#include<avr/io.h>
#include<util/delay.h>
#include <math.h>
#include<adc.c>
#include<lcd_deep.c>

#define 	Kp   		0.12
#define 	Kd   		1.1
#define 	Ki  		0.04
//#define	   set_angle  	0

#define data_in_port 	PINA		//ADC.0,1,2 are used
#define ddr_in_port 	DDRA
#define data_out_port 	PORTB
#define ddr_out_port 	DDRB

void pwm0(int);
void pwm2(int);
void stop(void);
void go_forward(void);
void go_backward(void);

int main()
{

float xaccl_vol,yaccl_vol,gyro_vol,omega;		//,torque,torque_max
float xaccl_angle,yaccl_angle,accl_angle,angle,gyro_angle;
float x,y,g;
float set_angle=0;

DDRC=0xFF;
ddr_out_port=0xFF;

//float prev_error=0,curr_error=0,sum_error=0,d_error=0,gyro_angle_sum=0;
 while(1)
 {
	adc_init();
	ADCSRA|=(1<<ADSC);     //starts conversion
	
	x=adc_read(2);
	y=adc_read(5);

	xaccl_vol=x*5/1024;		// AREF=5V from Aref

		xaccl_angle= asin((xaccl_vol-2.13)/0.312)*180/3.141;	// for both forward n backward, 0g reading= 2.13

	yaccl_vol=y*5/1024;	
	
		yaccl_angle= asin((yaccl_vol-2.45)/0.312)*180/3.141;	// 0g reading= 2.45, +ve: forward motion, -ve: backward motion
	
	/* since accelerometer axis is more sensitive when it is parallel to earth surface, now we will use only 
		y axis reading.
		
	if(yaccl_angle<0)
		xaccl_angle=-xaccl_angle;
		
	else 
		xaccl_angle=xaccl_angle;*/
		
	accl_angle= yaccl_angle;     //(xaccl_angle+yaccl_angle)/2;		// +ve: forward motion, -ve: backward motion
	
	g=adc_read(3);
	
	gyro_vol=(float)g*5/1024;	//AREF=AVCC or 5V from outside
	
	omega=(2.5-gyro_vol)/0.015;	// +ve: forward motion, -ve: backward motion
	
	gyro_angle=omega*0.00002;		// dt=0.00002  (theta=omega*dt)
	
	//gyro_angle_sum+=gyro_angle;		//gyro_angle_sum must be 0 for equillibrium
	
	//angle=(accl_angle+gyro_angle)/2;	//if angle<0 :backward motion,angle>0 :forward motion, angle=0 :stable state
	
	angle=accl_angle;
	
	PORTC=(int)angle;
	/*if(gyro_angle_sum!=0)
	{
	  curr_error = angle - set_angle;
	
		d_error = curr_error - prev_error;
		
		prev_error = curr_error;
		
		if(torque >= torque_max)
			torque = torque_max;
			
		else if(torque <= -torque_max)
			torque = -torque_max;
			
		else
		{	
			sum_error+=curr_error;
			torque=Kp*curr_error-Kd*d_error+Ki*sum_error;
		}
				
	}
	else
		stop();*/
		
 }	
 
 if(angle>=set_angle)
	go_forward();
	
 else if(angle<set_angle)
	go_backward();
 
 //else
	//stop();
	
 return (0);
	
}

void pwm0(int pwm_0)//oc0 connected to L298
{

	
	OCR0=pwm_0;
	TCCR0=0x68;
	TCCR0|=0x05;
}

void pwm2(int pwm_2)//oc0 connected to L298
{


	OCR2=pwm_2;
	TCCR2=0x68;
	TCCR2|=0x05;
}	
	
void stop()
{
	data_out_port=0xF0;
}

void go_forward()
{
	pwm0(50);
	data_out_port=0xA0;
}
	
void go_backward()
{
	pwm0(50);
	data_out_port=0x50;
}