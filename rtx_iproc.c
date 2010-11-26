#include "rtx.h"
#include <signal.h>

int signal;
NewPCB *current_process;


context_switch(prevprocess, nextprocess){
if (prevprocess == NULL || nextprocess == NULL){
	//terminate()
}
else
	current_process = nextprocess;
if(setjump(prevprocess)==0){
	longjmp (nextprocess,1)
}
longjmp(previous, setjmp(previous))
}

//The interrupt handler decides which i processes
//is called based on the signal function

interrupt_handler(signal)
{
	// save current_process context
	current_process->state = INTERRUPT;
atomic(on);
	//select i process based on interrupt source
	switch(signal){

	case (SIGALRM) : // i_process_timer;
	current_process = i_process_timer;
	//i_process_timer state is set as executing
	context_switch(current_process, )
	//restore i_process_timer context;
	//invoke i_process_timer handler;
	break;

	case (SIGUSR1) : // i_process_kb
	current_process = i_process_kb;
	//i_process_kb state is set as executing
	context_switch(current_process, )
	//restore i_process_kb context;
	//invoke i_process_kb handler;
	break;

	case (SIGUSR2) : // i_process_crt;
	current_process = i_process_crt;
	//i_process_crt state is set as executing
	context_switch(current_process, )
	//restore i_process_crt context;
	//invoke i_process_crt handler;
	break;

	case D: // i_process_terminate
	}

//I-Process Functions
save context of interrupt handler
current_process = save_PCB
save_PCB = NULL
set state of current_process to executing
restore current_process context
}

// timer process is triggered every 100ms
i_process_timer()
	{
		msg_env *timeout_request
		int temp_sender_pid
		timeout_request = receive_message()
		while (timeout_request != NULL)
		{
			sort msg_env into the timeout_list;
			timeout_request = receive_message();
		}
		if (timeout_list != 0)
		{
			tick_count--;
			of first msg_env in the timeout_list
			timeout_request = head_of_timeout_list
			while(timeout_request[tick_field] is zero)
				{
				msg_env *temp
				timeout_request = dequeue(timeout_list)
				timeout_request->receiver_pid=timeout_request->
				sender_pid
				timeout_request->sender_pid->timeout_i_process_pid;
				temp = timeout_request;
				dequeue message envelope from timeout_list
				return envelope to requesting process
		increment timeout_request to point to next message envelope
		send_message(temp->dest_process_id,temp)
				}
		}
}

i_process_kb()
{
Envelope *input;
int i;

	while(1) // endless loop
		if (current_process->recievelist->head != NULL)
		{
			input = K_recieve_message();

			for (i=0;i<inputbuffer;i++)
			{
				input->Data[i] = inputbuffer->bufdata[i];
			}
//Store the string of characters from the kb buffer into msg_env
//Set msg_env message subject field to console_input send message envelope to invoking process
		input->DestinationID = input->SenderID;
		input->SenderID = KBD_I;
		input->Msg_Type = KB_INPUT;
		k_send_message(input->DestinationID, input);
		}
		else{
			inputbuffer->length = 0;
			inputbuffer->wait_flag = 0;
			context_switch(current_process,interupted_process);
		}
}
i_process_crt()
{
Envelope *output;
int i;

	while(1) // endless loop
			if (current_process->recievelist->head != NULL)
			{


			}
}

}

