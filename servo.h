Carro-Seguidor-de-Linha-LPI2
============================
#ifndef SERVO_H
#define SERVO_H

#define F_CPU 16000000L
#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>


void configPWM();
bool setServoAngle(float f_angle);


#endif
