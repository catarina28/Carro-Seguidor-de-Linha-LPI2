Carro-Seguidor-de-Linha-LPI2
============================

#include "DCmotor.h"

volatile int8_t duty_cycle;

void configMotorPWM(int freq)
{
	TCCR3A|=(1<<COM3A1)|(1<<COM3B1)|(1<<WGM31);        //NON Inverted PWM
	TCCR3B|=(1<<WGM33)|(1<<WGM32)|(1<<CS31); //PRESCALER=8 MODE 14(FAST PWM)
	ICR3=freq*2;  //fPWM=50Hz (Period = 20ms Standard).
	DDRE|=(1<<PE3);   //PWM Pins as Out
	DDRH|=(1<<PH5)|(1<<PH6);   //PWM Pins as Out
}

bool setMotorDuty(int8_t duty)
{
	if(duty>=0 && duty <=100)
		OCR3A = (duty*ICR3)/100;
	else return 0;
	return 1;
}

void setMotorDirection(int8_t direction)
{ //1-forward 0-stop -1-reverse
	if(direction==1){
		PORTH|=(1<<PH5);
		PORTH|=~(1<<PH6);
	}
	else if(direction==0){
		PORTH|=~(1<<PH5);
		PORTH|=~(1<<PH6);
	}
	else if(direction==1){
		PORTH|=(1<<PH6);
		PORTH|=~(1<<PH5);
	}
}
