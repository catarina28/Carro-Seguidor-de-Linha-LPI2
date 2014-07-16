Carro-Seguidor-de-Linha-LPI2
============================
#include "servo.h"
#include "Sensor.h"

int angle = 0;

bool setServoAngle(float f_angle)
{
	angle = (int)f_angle;
	SendString((char*) "angulo : ");
	char c_angulo[5];
	itoa(angle, c_angulo, 10);
	SendString(c_angulo);
	if(angle>=-75 && angle <=75)
	OCR1A=(((((2450-700)/170)*(85+angle))+700)/4);
	else return 0;
	return 1;
}

void configPWM()
{
	TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11); //NON Inverted PWM
	TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM)
	ICR1=4999; //fPWM=50Hz (Period = 20ms Standard).
	DDRB|=(1<<PB5); //PWM Pins as Out
}

