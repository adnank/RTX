
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
	NewPCB *pcb_ptr[NUM_OF_PROC];
	int x,y;
	for(x = 0; x < NUM_OF_PROC; x++)
	{
		pcb_ptr[x] = (NewPCB*)malloc(sizeof(NewPCB));
		if(pcb_ptr[x] == NULL)
		{
			printf("error allocating memory for pcb!\n");
			for(y = x-1; y >= 0; y--)
				free(pcb_ptr[y]);
			break;
		}
		//initialize fields
	}
}

//creates the initialization table
void initialization_table()
{
	int i,j;

	for(i = 0; i < NUM_OF_PROC; i++)
	{
		switch(i)
		    {

		    }
	}
	printf("initialization table created!\n");
}



