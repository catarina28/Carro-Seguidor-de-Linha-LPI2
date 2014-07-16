Carro-Seguidor-de-Linha-LPI2
============================
#ifndef SENSOR_H
#define SENSOR_H


#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#define FOSC 16000000
#define BAUDRATE 9600
#define _UBRR_ (((((FOSC * 10)/(16L*BAUDRATE))+5)/10)-1)

extern volatile unsigned char channel;
extern volatile int adc_value[8];
extern volatile char all_read;


void USART_config();
void UsartSendByte(char ch);
void SendString(char* str);

void ADC_config();
void ADC_Start();
float Centroid_Algorithm();

#endif
