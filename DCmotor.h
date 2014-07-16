Carro-Seguidor-de-Linha-LPI2
============================
#ifndef DCMOTOR_H
#define DCMOTOR_H

#include <avr/io.h>
#include <stdbool.h>

void configMotorPWM(int freq);
bool setMotorDuty(int8_t duty);
void setMotorDirection(int8_t direction);
extern volatile int8_t duty_cycle;



#endif
