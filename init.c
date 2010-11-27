#include "rtx.h"


//following functions allocates memory for message envelopes
void init_env()
{
	Envelope *env_ptr;
	int i;
	for(i = 0; i < NUM_OF_ENVELOPES; i++)
	{
		env_ptr = (Envelope *) malloc(sizeof(Envelope));
		if(env_ptr == NULL)
		{
			printf("error allocating memory for envelope!\n");
			goto cleanup;
		}

		env_ptr->Data = NULL;				//need to check
		env_ptr->DestinationID = 0;
		env_ptr->Msg_Type = INITIAL;
		env_ptr->Next = NULL;
		env_ptr->Previous = NULL;
		env_ptr->SenderID = 0;
		env_ptr->clockticks = 0;
		env_ptr->kernelpt = NULL;

		K_Enqueue_MsgEnv (env_ptr, Free_Env_Queue);
	}
	printf("memory allocated\n");

cleanup:
		free(env_ptr);
}


//following function allocates memory for the pcb
void init_pcb()
{
	NewPCB *pcb_list[NUM_OF_PROC];
	int x,y;
	for(x = 0; x < NUM_OF_PROC; x++)
	{
		pcb_list[x] = (NewPCB*)malloc(sizeof(NewPCB));
		if(pcb_list[x] == NULL)
		{
			printf("error allocating memory for pcb!\n");
			for(y = x-1; y >= 0; y--)
				free(pcb_list[y]);
			break;
		}
		//initialize fields
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
		            init_table[i].proc_address= add_ptst3;		//(void*)(&add_ptst3);
		        break;
		        case 7:
		            init_table[i].process_id = PROC_TST4;
		            init_table[i].priority = P_P2;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = READY;
		            init_table[i].proc_address= add_ptst4;		//(void*)(&add_ptst4);
		        break;
		        case 8:
		            init_table[i].process_id = PROC_TST5;
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

//selecting highest priority process from the Ready_Q and putting it to execution
void select_first_process()
{

}



