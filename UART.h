Carro-Seguidor-de-Linha-LPI2
============================
#include <stdlib.h>
#include <avr/interrupt.h>
#ifndef UART_H
#define UART_H

#define freqOsc 16000000
#define TXBufferSize 255

void configSerie(int baudRate);
void sendByte(char datae);
void sendString(char s[]);
ISR(USART0_RX_vect);
ISR(USART0_UDRE_vect);

#endif
