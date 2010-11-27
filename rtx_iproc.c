#include "structures.h"
#include <signal.h>

//int signal;
//NewPCB *current_process;

/*
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
*/
//The interrupt handler decides which i processes
//is called based on the signal function
/*
interrupt_handler(signal)
{
	// save current_process context
	current_process->state = INTERRUPT;
	NewPCB* Prev_Proc=current_process;
atomic(on);
	//select i process based on interrupt source
	switch(signal){

	case (SIGALRM) : // i_process_timer;
	current_process = i_process_timer;
	//i_process_timer state is set as executing
	context_switch(current_process,)
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

//	case D: // i_process_terminate
	}

}
*/
// timer process is triggered every 100ms
i_process_timer()
{
		Envelope *timeout_request;
//		int temp_sender_pid;
		timeout_request = K_recieve_message();
		while (timeout_request != NULL)
		{
			K_Sort_Envelope_Enqueue(timeout_request);
			timeout_request = K_recieve_message();
		}
		if (Timeout_List->free_msg_ctr > 0)
		{
			Envelope* Temp=Timeout_List->Head;
			while (Temp->Next!=NULL)
			{
				Temp->clockticks--;
				Temp=Temp->Next;
			}
			Temp=Timeout_List->Head;
			while (Temp->clockticks==0)
			{
				Envelope* Send;				
				Send=K_Dequeue_MsgEnv(Timeout_List);
				Timeout_List->free_msg_ctr--;
				Send->Msg_Type=2;
				K_send_message (Send->SenderID,Send);
				Temp=Temp->Next;
			}
		}
}

i_process_kb()
{
char c;
int i;
for (i=0;i<i_buffer->Length;i++)
{
	c=getchar();
	i_buffer->buffer[i]=c; //context_switch(current_process,Prev_Proc); //NEED RELEASE PROCESSOR?????????????
}

Envelope *input;
int j;
i_buffer->Length=1;
	while(1) // endless loop
	{
		if (current_process->recievelist->Head != NULL)
		{
			input = K_recieve_message();
			for (j=0;j<i_buffer->Length;j++)
			{
				 input->Data[j]='K';// i_buffer->buffer[j];
			}
//Store the string of characters from the kb buffer into msg_env
//Set msg_env message subject field to console_input send message envelope to invoking process
		input->DestinationID = input->SenderID;
		input->SenderID = 3000; //PID of KB i-process
		input->Msg_Type = 4; //KB_INPUT
		K_Enqueue_MsgEnv(input,current_process->Own);
		K_send_message(input->DestinationID, input);
		}
		else{
			i_buffer->Length = 0;
//			context_switch(current_process,Prev_Proc); //NEED RELEASE PROCESSOR?????????????
		}
	}
}
i_process_crt()
{
Envelope *output;
int i;

	while(1){ // endless loop
			if (current_process->recievelist->Head != NULL)
			{
				i=0;
				output=K_recieve_message();
				o_buffer->Length=4;
				for(i;i<o_buffer->Length;i++)
				{
					o_buffer->buffer[i]=output->Data[i];
					printf("%c\n",o_buffer->buffer[i]);
				}
				o_buffer->Length=i+1;
			}
			else{
				o_buffer->Length=0;
//				context_switch(current_process,Prev_Proc); //NEED RELEASE PROCESSOR?????????????
			}
	}

}

