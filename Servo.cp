Carro-Seguidor-de-Linha-LPI2
============================
#include <avr/io.h>
#include "Sensor.h"

volatile unsigned char channel;
volatile int adc_value[8];
volatile char all_read;


void USART_config()
{
	UBRR0 = _UBRR_;
	UCSR0B = (1 << RXEN0)| (1 << TXEN0) | (1 << RXCIE0);
	UCSR0C = (3 << UCSZ00);
}

void UsartSendByte(char ch)
{ 
	UDR0 = ch; 
	while(!(UCSR0A & (1 << UDRE0))) ; 
} 
void SendString(char* str)
{ 
	while(*str != '\0')
	{ 
		UsartSendByte(*str); 
		str++; 
	} 
}

void ADC_config()
{
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));   //Set Prescaler to 128 to establish a 125Khz clock source
	ADMUX |= (1<<REFS0);
	ADCSRA |= (1<<ADEN)| (1<<ADIE);	//Power up the ADC
	sei();
}


void ADC_Start()
{
	ADMUX &= 0XE0; //limpa admux
	ADMUX |= channel;	//le do canal -> channel
	ADCSRA |= (1<<ADSC); //inicia conversao
}


float Centroid_Algorithm() 
{
	char c_sr_sum[10];
	float input = 0;
	float static input_ant = 0;
	int sr_sum = 0;
	int r_sum = 0;
	for(int i = 0; i < 8; i++) 
	{ 
		sr_sum += (adc_value[i]*(i)); //Somatório da multiplicação do indice de cada sensor pelo valor da sua leitura 
		r_sum += adc_value[i]; //Somatório das leituras de cada sensor 
	} 
	input = (sr_sum/1.0) / (r_sum/1.0); //Cálculo da variável de entrada do PID 
	if(r_sum < 400)
		input = input_ant;
	if(r_sum > 5300)
		input = input_ant;
	input_ant = input;
	itoa(sr_sum, c_sr_sum, 10);
		SendString(c_sr_sum);
	UsartSendByte(' ');
	itoa(r_sum, c_sr_sum, 10);
		SendString(c_sr_sum);
	return input;
}

ISR(ADC_vect)
{
	adc_value[channel] = ADC; //armazena valor no array
	channel++;		//altera o canal de leitura
	if(channel == 8) //canal 8 inutilizado
	{
		channel = 0;
		all_read = 1;
	}
	else{
		ADMUX &= 0XE0; //limpa ADMUX
		ADMUX |= channel; //atribui novo channel
		ADCSRA |= (1<<ADSC); //inicia conversao
	}
}
