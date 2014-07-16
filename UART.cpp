Carro-Seguidor-de-Linha-LPI2
============================
#include <avr/io.h>
#include <stdlib.h>
#include <stdbool.h>
#include "CONSOLE.h"
#include "RINGBUFFER.h"
#include "UART.h"

ringBuffer TXBuffer(TXBufferSize, 1);

ISR(USART0_RX_vect){
	RXEvent();
}

ISR(USART0_UDRE_vect){
	if(!TXBuffer.isBufEmpty())
		UDR0=TXBuffer.popFromBuf();
	else
		UCSR0B &= ~(1 << UDRIE0);
}

void configSerie(int baudRate)
{
	const int _UBRR_ = freqOsc/16/baudRate-1;
	UCSR0A=0;
	UCSR0B=(1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	
	UCSR0C=(1<<UPM01)|(1<<UCSZ01)|(1<<UCSZ00);
	
	UBRR0 = _UBRR_;
	sei();
	return;
}

void sendByte(char datae)
{
	// Disable interrupts to get exclusive access to ring_buffer_out.
	cli();
	if (TXBuffer.isBufEmpty()) {
		// First data in buffer, enable data ready interrupt
		UCSR0B |=  (1 << UDRIE0);
	}
	if(TXBuffer.isBufFull()){
		sei();
		while(!TXBuffer.pushToBuf(datae));}
	else{
		TXBuffer.pushToBuf(datae);
		sei();}
}

void sendString(char s[]){
	int i=0;
	while(s[i]!='\0')
	{
		sendByte(s[i]);
		i++;
	}
	return;
}
