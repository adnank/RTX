
#include <stdio.h>
#include <stdlib.h>
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
		//initialize fields
		free_mem_Q.enqueue(env_ptr);
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
void initialization_table()
{
	int i;

	for(i = 0; i < NUM_OF_PROC; i++)
	{
		switch(i)
		    {
				case 0:
		            init_table[i].process_id = PROC_A;
		            init_table[i].priority = 4;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = IPROC;
		            init_table[i].proc_address= kbd_handler;//(void*)(&kbd_handler);
		        break;
		        case 1:
		            init_table[i].process_id = PROC_B;
		            init_table[i].priority = 4;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = IPROC;
		            init_table[i].proc_address= disp_handler;//(void*)(&disp_handler);
		        break;
		        case 2:
		            init_table[i].process_id = PROC_C;
		            init_table[i].priority = 4;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = IPROC;
		            init_table[i].proc_address= timer_handler;//(void*)(&timer_handler);
		        break;
		        case 3:
		            init_table[i].process_id = PROC_TST1;
		            init_table[i].priority = 3;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = IPROC;
		            init_table[i].proc_address= p_Null;//(void*)(&p_Null);
		        break;
		        case 4:
		            init_table[i].process_id = PROC_TST1;
		            init_table[i].priority = 0;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = READY;
		            init_table[i].proc_address= shell;//(void*)(&shell);
		        break;
		        case 5:
		            init_table[i].process_id = PROC_TST2;
		            init_table[i].priority = 0;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = READY;
		            init_table[i].proc_address= set_priority;//(void*)(&set_priority);
		        break;
		        case 6:
		            init_table[i].process_id = PROC_TST3;
		            init_table[i].priority = 1;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = BLK_ON_REC;
		            init_table[i].proc_address= process_a;//(void*)(&process_a);
		        break;
		        case 7:
		            init_table[i].process_id = PROC_TST4;
		            init_table[i].priority = 1;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = BLK_ON_REC;
		            init_table[i].proc_address= process_b;//(void*)(&process_b);
		        break;
		        case 8:
		            init_table[i].process_id = PROC_TST5;
		            init_table[i].priority = 1;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = BLK_ON_REC;
		            init_table[i].proc_address= process_c;//(void*)(&process_c);
		        break;
		        case 9:
		            init_table[i].process_id = PROC_TST6;
		            init_table[i].priority = 2;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = READY;
		            init_table[i].proc_address= test_proc_1;//(void*)(&test_proc_1);
		        break;
		        case 10:
		            init_table[i].process_id = KBD_I;
		            init_table[i].priority = 2;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = READY;
		            init_table[i].proc_address= test_proc_2;//(void*)(&test_proc_2);
		        break;
		        case 11:
		            init_table[i].process_id = DISP_I;
		            init_table[i].priority = 2;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = READY;
		            init_table[i].proc_address= test_proc_3;//(void*)(&test_proc_3);
		        break;
		        case 12:
		            init_table[i].process_id = TIMER_I;
		            init_table[i].priority = 2;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = READY;
		            init_table[i].proc_address= test_proc_4;//(void*)(&test_proc_4);
		        break;
		        case 13:
		            init_table[i].process_id = PROC_CCI;
		            init_table[i].priority = 2;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = READY;
		            init_table[i].proc_address= test_proc_5;//(void*)(&test_proc_5);
		        break;
		        case 13:
		        	init_table[i].process_id = PROC_SET_PRIORITY;
		        	init_table[i].priority = 2;
		        	init_table[i].stack_size = MAX_STACKSIZE;
		        	init_table[i].proc_status = READY;
		        	init_table[i].proc_address= test_proc_5;//(void*)(&test_proc_5);
		        	break;
		        case 14:
		            init_table[i].process_id = PROC_WALL_CLK;
		            init_table[i].priority = 2;
		            init_table[i].stack_size = MAX_STACKSIZE;
		            init_table[i].proc_status = READY;
		            init_table[i].proc_address= test_proc_5;//(void*)(&test_proc_5);
		    }
	}
	printf("initialization table created!\n");
}



