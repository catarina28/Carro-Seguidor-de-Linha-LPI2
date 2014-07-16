Carro-Seguidor-de-Linha-LPI2
============================
#include "PID_Controller.h"
#include "Sensor.h"

struct PID_C PID;
struct PID_C *ptr;

void pid_start()
{
	ptr = &PID;
	PID.windup_guard = 3.5;
	PID.proportional_gain = 1;
	PID.integral_gain = 0;
	PID.derivative_gain = 0;
	PID.prev_error = 0;
	PID.int_error = 0;
	PID.control = 0;
}


void pid_timer_config()
{
	TCCR5B |= (1<<CS52);
	TCNT5H = 0;
	TCNT5L = 0;
}

void pid_zeroize(PID_C* pid)
{
	//reset aos valores de erro anterior e integral
	pid->prev_error = 0;
	pid->int_error = 0;
}

void pid_update(PID_C* pid, double curr_error, double dt)
{
	double diff;
	double p_term;
	double i_term;
	double d_term;
	
	// Calculo do erro integral com anti-windup
	pid->int_error += (curr_error*dt);
	if (pid->int_error < -(pid->windup_guard))
		pid->int_error = -(pid->windup_guard);
	else if (pid->int_error > pid->windup_guard)
	pid->int_error = pid->windup_guard;
	
	// Calculo do erro diferencial
	diff = ((curr_error - pid->prev_error)/dt);
	
	p_term = (pid->proportional_gain * curr_error);
	i_term = (pid->integral_gain     * pid->int_error);
	d_term = (pid->derivative_gain   * diff);
	
	// Calculo da variavel de controlo
	pid->control = p_term + i_term + d_term;
	
	// Guardar valor, para a próxima iteração
	pid->prev_error = curr_error;
	TCNT5H = 0;
	TCNT5L = 0;
}
