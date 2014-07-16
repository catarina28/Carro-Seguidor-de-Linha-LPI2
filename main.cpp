Carro-Seguidor-de-Linha-LPI2
============================

#include "servo.h"
#include "Sensor.h"
#include "PID_Controller.h"
#include "Bluetooth.h"
#include "DCmotor.h"



int main(void)
{
	//Calibração do sensor
	/*configPWM();
	setServoAngle(0);
	while(1){
	}*/
	double dt = 0.0;
	double curr_err = 0;
	float PID_Input = 0;
	float PID_Output = 0;
	int i_PID_Input = 0;
	int i_Output = 0;
	char c_PID_Input[4];
	char c_Output[4];
	char c_adc_value[4];
	float gain = -20.0;
	
	
	ADC_config();
	ADC_Start();
	USART_config();
	
	configPWM();
	setServoAngle(0);
	ConfigSerie_BT();
	pid_start();
	pid_timer_config();
	configMotorPWM(500);
	setMotorDirection(1);
	duty_cycle = 10;
	while(1)
	{
		
		if(mode == 1)
		{
			
			if(all_read == 1)
			{
				
				PID_Input = Centroid_Algorithm();
				curr_err = (3.5 - PID_Input);
				dt = TCNT5;
				dt = (dt*16)/1000000;
				
				pid_update(ptr, curr_err,dt);
				PID_Output = PID.control;
				itoa(i_Output, c_Output, 10);
				SendString((char*)"\n-------------------\n");
				SendString((char*)"\nSaída_PID 1: ");
				SendString(c_Output);
				
			
				PID_Output = PID_Output*gain;
				if(PID_Output > 75)
					PID_Output = 75;
				if(PID_Output < -75)
					PID_Output = -75;
			
				setServoAngle(PID_Output);
			
				i_PID_Input = (int) PID_Input;
				i_Output = (int) PID_Output;
				itoa(i_PID_Input, c_PID_Input ,10);
				itoa(i_Output, c_Output, 10);
				SendString((char*)"\nLeituras: "); 
				for(int i = 0; i < 8; i++)
					{
						itoa(adc_value[i], c_adc_value, 10); 
						SendString(c_adc_value);
						UsartSendByte(' ');
					}
				SendString((char*)"\nEntrada PID: "); 
				SendString(c_PID_Input); 
				SendString((char*)"\nSaída_PID 2: "); 
				SendString(c_Output); 
				all_read = 0; 
				ADMUX &= 0XE0; //Limpa ADMUX 
				ADMUX |= channel; //Selecciona o canal 0 
				ADCSRA |= (1<<ADSC); //Inicia conversão
			}
		}
		if(mode == 0)
		{
			//
		}

	}
}
