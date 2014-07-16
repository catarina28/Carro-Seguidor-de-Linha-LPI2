Carro-Seguidor-de-Linha-LPI2
============================
#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <avr/io.h>
#include <stdlib.h>
#include <stdbool.h>
#include <avr/interrupt.h>

#define FOSC 16000000
#define _UBRR2_ (((((FOSC * 10)/(16L*115200))+5)/10)-1)

ISR(USART1_RX_vect);
void ConfigSerie_BT();
extern volatile char mode;


#endif
