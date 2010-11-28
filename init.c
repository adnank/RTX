#include "rtx.h"

//creates and initialises free envelope queue
void init_free_env_Q()
{
	//msg_env_Q *Free_Env_Queue;   declared in header file
	Free_Env_Queue = (msg_env_Q*)malloc(sizeof(msg_env_Q));
	if(timeout_Q == NULL)
	{
		printf("Error allocating memory for timeout_Q\n");
		free(timeout_Q);
	}
	Free_Env_Queue->free_msg_counter = 0;
	Free_Env_Queue->head = NULL;
	Free_Env_Queue->tail = NULL;
}

//creates and initialises timeout queue
void init_timeout_Q()
{
	//msg_env_Q *timeout_Q;   declared in header file
	timeout_Q = (msg_env_Q*)malloc(sizeof(msg_env_Q));
	if(timeout_Q == NULL)
	{
		printf("Error allocating memory for timeout_Q\n");
		free(timeout_Q);
	}
	timeout_Q->free_msg_counter = 0;
	timeout_Q->head = NULL;
	timeout_Q->tail = NULL;
}

//following functions allocates memory for message envelopes and initialises them
void init_env()
{
	Envelope *env_ptr;
	init_free_env_Q();		//creates and initializes free envelope queue
	int i;
	for(i = 0; i < NUM_OF_ENVELOPES; i++)
	{
		env_ptr = (Envelope *) malloc(sizeof(Envelope));
		if(env_ptr == NULL)
		{
			printf("error allocating memory for envelope!\n");
			goto cleanup;
		}
		int j;
		for (j=0;j<MSG_DATA;j++)
			env_ptr->Data[j] = NULL;				//need to check
		env_ptr->DestinationID = 0;
		env_ptr->Msg_Type = INITIAL;
		env_ptr->Next = NULL;
		env_ptr->Previous = NULL;
		env_ptr->SenderID = 0;
		env_ptr->clockticks = 0;
		env_ptr->kernelpt_next = NULL;
		env_ptr->kernelpt_previous = NULL;

		K_Enqueue_MsgEnv (env_ptr, Free_Env_Queue);
	}
	printf("memory allocated\n");

cleanup:
		free(env_ptr);
}

void init_rpq()
{
	//QueuePCB *ReadyQueue [NUM_OF_PRIORITY]; declared in header file

	int i,j;
	for(i = 0; i < NUM_OF_PRIORITY; i++)
	{
		ReadyQueue[i] = (QueuePCB*) malloc(sizeof(QueuePCB));
		if(ReadyQueue[i] == NULL)
		{
			printf("error allocating memory for ready Queue!\n");
			for(j = i-1; j >= 0; j--)
				free(ReadyQueue[j]);
			break;
		}
		ReadyQueue[i]->Head = NULL;
		ReadyQueue[i]->Tail = NULL;
	}
	printf("Ready Process Queue Created and Initialized!\n");
}

//creates and initialises Blocked_On_Resource queue
void init_blkOnRsc_Q()
{
	//QueuePCB *Blocked_On_Resources [NUM_OF_PRIORITY]; declared in header file

	int i,j;
	for(i = 0; i < NUM_OF_PRIORITY; i++)
	{
		Blocked_On_Resources[i] = (QueuePCB*) malloc(sizeof(QueuePCB));
		if(Blocked_On_Resources[i] == NULL)
		{
			printf("error allocating memory for Blocked_On_Resources Queue!\n");
			for(j = i-1; j >= 0; j--)
				free(Blocked_On_Resources[j]);
			break;
		}
		Blocked_On_Resources[i]->Head = NULL;
		Blocked_On_Resources[i]->Tail = NULL;
	}
	printf("Blocked_On_Resources Queue Created and Initialized!\n");
}

//creates and initialises Blocked_On_Envelope queue
void init_blkOnEnv_Q()
{
	//QueuePCB *Blocked_On_Envelope [NUM_OF_PRIORITY]; declared in header file

	int i,j;
	for(i = 0; i < NUM_OF_PRIORITY; i++)
	{
		Blocked_On_Envelope[i] = (QueuePCB*) malloc(sizeof(QueuePCB));
		if(Blocked_On_Envelope[i] == NULL)
		{
			printf("error allocating memory for Blocked_On_Resources Queue!\n");
			for(j = i-1; j >= 0; j--)
				free(Blocked_On_Envelope[j]);
			break;
		}
		Blocked_On_Envelope[i]->Head = NULL;
		Blocked_On_Envelope[i]->Tail = NULL;
	}
	printf("Blocked_On_Envelope Queue Created and Initialized!\n");
}

//following function allocates memory for the pcb
void init_processes()
{
	int i, size;
	//QueuePCB *PCBList;  declared in header file
	jmp_buf kernel_buf;

	PCBList = (QueuePCB*) malloc(sizeof(QueuePCB));

	init_rpq();
	NewPCB *pcb_ptr;(NewPCB*)malloc(sizeof(NewPCB));
	for(i=0; i < NUM_OF_PROC; i++)
	{
		pcb_ptr = (NewPCB*)malloc(sizeof(NewPCB));
		if(pcb_ptr == NULL)
		{
			printf("Error allocating memory for PCB\n");
			free(pcb_ptr);
		}

		pcb_ptr->Kernelpt_Next = NULL;
		pcb_ptr->Kernelpt_Previous = NULL;
		pcb_ptr->Next = NULL;
		pcb_ptr->Previous = NULL;
		pcb_ptr->Own = (msg_env_Q*)malloc(sizeof(msg_env_Q));
//		pcb_ptr->jbContext = NULL;
		pcb_ptr->recievelist = (msg_env_Q*)malloc(sizeof(msg_env_Q));
		pcb_ptr->Priority = init_table[i].priority;
		pcb_ptr->ProcID = init_table[i].process_id;
		pcb_ptr->State = init_table[i].proc_status;
		pcb_ptr->address = init_table[i].proc_address;
		size = init_table[i].stack_size;
//		pcb_ptr->Stack = ((char *) malloc(size))+ size - STK_OFFSET; 	//stacks grow down

		//head and tail of 'Own' which is a msg_env_Q struct
		pcb_ptr->Own->head = NULL;
		pcb_ptr->Own->tail = NULL;
		//head and tail of 'recievelist' which is a msg_env_Q struct
		pcb_ptr->recievelist->head = NULL;
		pcb_ptr->recievelist->tail = NULL;

		K_Enqueue_PCB(pcb_ptr, PCBList);

		//setup buffers and choose first process to run

		if(pcb_ptr->State == READY)
		{
			//enqueue on ready process queue
		}
		else if(pcb_ptr->State == BLK_ON_ENV)
		{
			//enqueue on blocked on envelope queue
		}

	}

}


//creates the initialization table
void initialize_table()
{
	int i;
	for(i = 0; i < NUM_OF_PROC; i++)
	{
		switch(i)
		    {
				case 0:
		            init_table[i].process_id = PROC_A;
		            init_table[i].priority = P_P1;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = BLK_ON_ENV;
		            init_table[i].proc_address= add_procA;		//(void*)(&add_procA);
		        break;
		        case 1:
		            init_table[i].process_id = PROC_B;
		            init_table[i].priority = P_P1;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = READY;
		            init_table[i].proc_address= add_procB;		//(void*)(&add_procB);
		        break;
		        case 2:
		            init_table[i].process_id = PROC_C;
		            init_table[i].priority = P_P1;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = READY;
		            init_table[i].proc_address= add_procC;		//(void*)(&add_procC);
		        break;
		        case 3:
		            init_table[i].process_id = NULL_PROC;
		            init_table[i].priority = P_P3;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = READY;
		            init_table[i].proc_address= add_pNull;		//(void*)(&add_pNull);
		        break;
		        case 4:
		            init_table[i].process_id = PROC_TST1;
		            init_table[i].priority = P_P2;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = READY;
		            init_table[i].proc_address= add_ptst1;		//(void*)(&add_ptst1);
		        break;
		        case 5:
		            init_table[i].process_id = PROC_TST2;
		            init_table[i].priority = P_P2;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = READY;
		            init_table[i].proc_address= add_ptst2;		//(void*)(&add_ptst2);
		        break;
		        case 6:
		            init_table[i].process_id = PROC_TST3;
		            init_table[i].priority = P_P2;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = READY;
//		            init_table[i].proc_address= add_ptst3;		//(void*)(&add_ptst3);
		        break;
		        case 7:
		            init_table[i].process_id = PROC_TST4;
		            init_table[i].priority = P_P2;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = READY;
		            init_table[i].proc_address= add_ptst4;		//(void*)(&add_ptst4);
		        break;
		        case 8:
//		            init_table[i].process_id = PROC_TST5;
		            init_table[i].priority = P_P2;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = READY;
		            init_table[i].proc_address= add_ptst5;		//(void*)(&add_ptst5);
		        break;
		        case 9:
		            init_table[i].process_id = PROC_TST6;
		            init_table[i].priority = P_P2;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = READY;
		            init_table[i].proc_address= add_ptst6;		//(void*)(&add_ptst6);
		        break;
		        case 10:
		            init_table[i].process_id = KBD_I;
		            init_table[i].priority = P_IPROCESS;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = IPROCESS;
		            init_table[i].proc_address= add_KBD;		//(void*)(&add_KBD);
		        break;
		        case 11:
		            init_table[i].process_id = CRT_I;
		            init_table[i].priority = P_IPROCESS;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = IPROCESS;
		            init_table[i].proc_address= add_CRT;		//(void*)(&add_CRT);
		        break;
		        case 12:
		            init_table[i].process_id = TIMER_I;
		            init_table[i].priority = P_IPROCESS;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = IPROCESS;
		            init_table[i].proc_address= add_TIMER;		//(void*)(&add_TIMER);
		        break;
		        case 13:
		            init_table[i].process_id = PROC_CCI;
		            init_table[i].priority = P_P0;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = READY;
		            init_table[i].proc_address= add_CCI;		//(void*)(&add_CCI);
		        break;
		        case 14:
		        	init_table[i].process_id = PROC_SET_PRIORITY;
		        	init_table[i].priority = P_P0;
		        	init_table[i].stack_size = MAX_STACKSIZE;
		        	init_table[i].proc_status = READY;
		        	init_table[i].proc_address= add_PRTY;		//(void*)(&add_PRTY);
		        	break;
		        case 15:
		            init_table[i].process_id = PROC_WALL_CLK;
		            init_table[i].priority = P_P0;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = READY;
		            init_table[i].proc_address= add_CLK;		//(void*)(&add_CLK);
		    }
	}
	printf("initialization table created!\n");
}


//creating and initialising Trace Arrays
void init_TraceArrays()
{
	int i,j;
	for(i = 0; i < TRACE_ARRAY; i++)
	{
		Recieve_Trace_Array[i] = (TraceArray*) malloc(sizeof(TraceArray));
		Send_Trace_Array[i] = (TraceArray*) malloc(sizeof(TraceArray));
		if(Recieve_Trace_Array[i] == NULL)
		{
			printf("error allocating memory for Receive Trace array!\n");
			for(j = i-1; j >= 0; j--)
				free(Recieve_Trace_Array[j]);
			break;
		}
		Recieve_Trace_Array[i]->DestintionID = 0;
		Recieve_Trace_Array[i]->Msg_Type = 0;
		Recieve_Trace_Array[i]->SenderID = 0;
		Recieve_Trace_Array[i]->timestamp = 0;

		if(Send_Trace_Array[i] == NULL)
		{
			printf("error allocating memory for Send Trace array!\n");
			for(j = i-1; j >= 0; j--)
				free(Recieve_Trace_Array[j]);
			break;
		}
		Send_Trace_Array[i]->DestintionID = 0;
		Send_Trace_Array[i]->Msg_Type = 0;
		Send_Trace_Array[i]->SenderID = 0;
		Send_Trace_Array[i]->timestamp = 0;
	}
	printf("Trace Arrays Created and Initialized!\n");
}

//creating and initialising I/O Buffers
void init_ioBuffers()
{
	int i,j;
	//io_buffer *output_buffer;		//declared in header file
	//io_buffer *input_buffer;		//declared in header file
	output_buffer = (io_buffer*) malloc(sizeof(io_buffer));
	input_buffer = (io_buffer*) malloc(sizeof(io_buffer));

	if(output_buffer == NULL)
	{
		printf("Error allocating memory for output buffer\n");
		free(output_buffer);
	}

	//output_buffer->buffer = '0';
	output_buffer->Length = 0;

	if(input_buffer == NULL)
	{
		printf("Error allocating memory for input buffer\n");
		free(input_buffer);
	}

	//input_buffer->buffer = '0';
	input_buffer->Length = 0;
}

//CONTEXT SWITCH
void context_switch(NewPCB *current, NewPCB * next_proc)
{
	int return_val = setjmp(current->jbContext);
	if(return_val == 0)
	{
		current_process = next_proc;
		longjmp(next_proc->jbContext, 1);
	}
}



