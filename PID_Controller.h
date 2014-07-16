Carro-Seguidor-de-Linha-LPI2
============================
#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

struct PID_C{
	double windup_guard;
	double proportional_gain;
	double integral_gain;
	double derivative_gain;
	double prev_error;
	double int_error;
	double control;
};


extern struct PID_C PID;
extern struct PID_C *ptr;

void pid_start();
void pid_zeroize(PID_C* pid);
void pid_update(PID_C* pid, double curr_error, double dt);
void pid_timer_config();


#endif
