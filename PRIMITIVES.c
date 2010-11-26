/*
 * PRIMITIVES.c
 *
 *  Created on: 2010-11-18
 *      Author: abubakar
 */

#include "structures.h"
/*
int send_message(int Destination_pid, Envelope *msg_envelope)
{
	atomic (on);
	int return_val;
	return_val=K_send_message (Destination_pid, msg_envelope);
	return return_val;
	atomic (off);
}

Envelope * recieve_message ()
{
	atomic (on);
	K_recieve_message();
	atomic (off):
}

Envelope * request_msg_Env()
{
	atomic (on);
	K_request_msg_Env ();
	atomic (off);
}

int release_msg_env (Envelope * msg_envelope)
{
	atomic (on);
	int return_val;
	return_val=K_release_msg_env (msg_envelope);
	return return_val;
	atomic (off);
}

int release_processor()
{
	atomic (on);
	int return_val;
	return_val=K_release_processor ();
	return return_val;
	atomic (off);
}

int request_process_status (Envelope* msg_env_ptr)
{
	atomic (on);
	int return_val;
	return_val=K_request_process_status (msg_env_ptr);
	return return_val;
	atomic (off);
}

int terminate ()
{
	atomic (on);
	return K_terminate ();
}

int change_priority(int new_priority,int target_process_id)
{
	atomic (on);
	int return_val;
	return_val=K_change_priority (new_priority, target_process_id);
	return return_val;
	atomic (off);
}

int request_delay(int time_delay, int wakeup_code, Envelope * message_envelope)
{
	atomic (on);
	int return_val;
	return_val=K_request_delay (time_delay, wakeup_code, message_envelope);
	return return_val;
	atomic (off);
}

int send_console_chars (Envelope * message_envelope)
{
	atomic (on);
	int return_val;
	return_val=K_send_console_chars(message_envelope);
	return return_val;
	atomic (off);
}

int get_console_chars(Envelope* message_envelope)
{
	atomic (on);
	int return_val;
	return_val=K_get_console_chars(message_envelope);
	return return_val;
	atomic (off);
}

int get_trace_buffers(Envelope * message_envelope)
{
	atomic (on);
	int return_val;
	return_val=K_get_trace_buffers (message_envelope);
	return return_val;
	atomic (off);
}
*/
