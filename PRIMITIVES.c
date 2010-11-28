/*
 * PRIMITIVES.c
 *
 *  Created ON: 2010-11-18
 *      Author: abubakar
 */

#include "rtx.h"
/*
int send_message(int Destination_pid, Envelope *msg_envelope)
{
	atomic (ON);
	int return_val;
	return_val=K_send_message (Destination_pid, msg_envelope);
	return return_val;
	atomic (OFF);
}

Envelope * recieve_message ()
{
	atomic (ON);
	K_recieve_message();
	atomic (OFF):
}

Envelope * request_msg_Env()
{
	atomic (ON);
	K_request_msg_Env ();
	atomic (OFF);
}

int release_msg_env (Envelope * msg_envelope)
{
	atomic (ON);
	int return_val;
	return_val=K_release_msg_env (msg_envelope);
	return return_val;
	atomic (OFF);
}

int release_processor()
{
	atomic (ON);
	int return_val;
	return_val=K_release_processor ();
	return return_val;
	atomic (OFF);
}

int request_process_status (Envelope* msg_env_ptr)
{
	atomic (ON);
	int return_val;
	return_val=K_request_process_status (msg_env_ptr);
	return return_val;
	atomic (OFF);
}

int terminate ()
{
	atomic (ON);
	return K_terminate ();
}

int change_priority(int new_priority,int target_process_id)
{
	atomic (ON);
	int return_val;
	return_val=K_change_priority (new_priority, target_process_id);
	return return_val;
	atomic (OFF);
}

int request_delay(int time_delay, int wakeup_code, Envelope * message_envelope)
{
	atomic (ON);
	int return_val;
	return_val=K_request_delay (time_delay, wakeup_code, message_envelope);
	return return_val;
	atomic (OFF);
}

int send_cONsole_chars (Envelope * message_envelope)
{
	atomic (ON);
	int return_val;
	return_val=K_send_cONsole_chars(message_envelope);
	return return_val;
	atomic (OFF);
}

int get_cONsole_chars(Envelope* message_envelope)
{
	atomic (ON);
	int return_val;
	return_val=K_get_cONsole_chars(message_envelope);
	return return_val;
	atomic (OFF);
}

int get_trace_buffers(Envelope * message_envelope)
{
	atomic (ON);
	int return_val;
	return_val=K_get_trace_buffers (message_envelope);
	return return_val;
	atomic (OFF);
}
*/
