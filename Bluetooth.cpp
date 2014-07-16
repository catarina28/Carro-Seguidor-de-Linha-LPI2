
#include "Bluetooth.h"
#include "PID_Controller.h"
#include "Sensor.h"
#include "Servo.h"
#include "DCmotor.h"

volatile char mode;


ISR(USART1_RX_vect)
{ 
	char code = UDR1;
	float static angle = 0;
	static char motor_direction = 0;
	
	switch(code){ 
		
		case 0:	
				UsartSendByte(code);			// Stop 
				angle = 0;
				duty_cycle = 0;
				motor_direction = 0;
				setMotorDirection(motor_direction);
				setMotorDuty(duty_cycle);
				setServoAngle(angle);
				
				break;
				
		case 1: 
				UsartSendByte(code + 48);			// automatic/manual 
				duty_cycle = 0;
				motor_direction = 0;
				setMotorDirection(motor_direction);
				setMotorDuty(duty_cycle);
				setServoAngle(angle);
				if(mode == 0) 
					mode = 1;
				else
					mode = 0;
				break;
				
		case 2: 
				UsartSendByte(code + 48);// frente
				angle = 0;
				//duty_cycle = 30;
				motor_direction = 1;
				setMotorDirection(motor_direction);
				setMotorDuty(duty_cycle);
				setServoAngle(angle);
				break;
						 
		case 3: 
				UsartSendByte(code + 48);// frente esquerda	
				angle = 60;					
				//duty_cycle = 30;
				motor_direction = 1;
				setMotorDirection(motor_direction);
				setMotorDuty(duty_cycle);
				setServoAngle(angle);
				break;
				
		case 4: 
				UsartSendByte(code + 48);//frente direita
				angle = -60;					
				//duty_cycle = 40;
				motor_direction = 1; 
				setMotorDirection(motor_direction);
				setMotorDuty(duty_cycle);
				setServoAngle(angle);
				break;
				
		case 5: 
				UsartSendByte(code + 48);// para trás				
				angle = 0;						
				//duty_cycle = 50;
				motor_direction = -1;
				setMotorDirection(motor_direction);
				setMotorDuty(duty_cycle);
				setServoAngle(angle);
				break;
				
		case 6: 
				UsartSendByte(code + 48);
				angle = -60;
				//duty_cycle = 40;
				motor_direction = -1;
				setMotorDirection(motor_direction);
				setMotorDuty(duty_cycle);
				setServoAngle(angle);
				break;		
				
				
		case 7: 
				UsartSendByte(code + 48);// para trás dir
				angle = 60;
				//duty_cycle = 40;
				motor_direction = -1;
				setMotorDirection(motor_direction);
				setMotorDuty(duty_cycle);
				setServoAngle(angle);
				break;
		case 8:
				UsartSendByte(code + 48);
				PID.proportional_gain += 0.2;
				break;
		case 9:
				UsartSendByte(code + 48);
				PID.integral_gain += 0.2;
				break;
		case 10:
				UsartSendByte(code + 48);
				PID.derivative_gain += 0.2;
				break;
		case 11:
				UsartSendByte(code + 48);
				PID.proportional_gain -= 0.2;
				break;
		case 12:
				UsartSendByte(code + 48);
				PID.integral_gain -= 0.2;
				break;
		case 13:
				UsartSendByte(code + 48);
				PID.derivative_gain -= 0.2;
				break;
		case 14:
				duty_cycle = duty_cycle + 5;
				setMotorDuty(duty_cycle);
				break;
		case 15:
				duty_cycle = duty_cycle - 5;
				setMotorDuty(duty_cycle);
				break;	
		} 
}	

void ConfigSerie_BT()
{ 	
	mode = 0;
	UBRR1 = _UBRR2_; // Enable receiver and transmitter
	UCSR1B = (1 << RXEN1)| (1 << TXEN1) | (1 << RXCIE1);
	UCSR1C = (3 << UCSZ10);
}
