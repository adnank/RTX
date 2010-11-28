/*
 * KPrimitives.c
 *
 *  Created on: 2010-11-18
 *      Author: abubakar
 */


#include "rtx.h"


//HELPER FUNCTION - to be used with the kernel primitive, not with KB and CRT proccesses


NewPCB * get_PCB (int process_id)
{
	if (PCBList->Head==NULL){

		return NULL;
	}

	NewPCB* Temp = PCBList->Head;

	if (process_id==Temp->ProcID)
			return Temp;
	while (process_id !=Temp->ProcID)
	{
		if (Temp->Kernelpt_Next==NULL)
			return NULL;
		Temp=Temp->Kernelpt_Next;
	}
	return Temp;
}

int K_Sort_Envelope_Enqueue (Envelope * msg_env)
{
	if (timeout_Q->head==NULL && timeout_Q->free_msg_counter==0) //List contains nothing
	{
		K_Enqueue_MsgEnv(msg_env,timeout_Q);
		timeout_Q->free_msg_counter++;
		return 1;
	}
	else
	{
		if (timeout_Q->free_msg_counter==1)
		{
			Envelope* Temp=timeout_Q->head;
			if (msg_env->clockticks>=Temp->clockticks) //list contains 1  add to TAIL
			{
				timeout_Q->tail=msg_env;
				Temp->Next=msg_env;
				msg_env->Previous=Temp;
				timeout_Q->free_msg_counter++;
				return 1;
			}
			else //List contains 1  add to HEAD
			{
				Temp->Previous=msg_env;
				msg_env->Next=Temp;
				timeout_Q->head=msg_env;
				timeout_Q->tail=Temp;
				timeout_Q->free_msg_counter++;
				return 1;
			}
		}
		else //List contains more than 1
		{
			Envelope* A=timeout_Q->head; //1st one
			Envelope* B=timeout_Q->head->Next; //2nd one
			if (msg_env->clockticks<A->clockticks)
			{
				A->Previous=msg_env;
				msg_env->Next=A;
				timeout_Q->head=msg_env;
				timeout_Q->free_msg_counter++;
				return 1;
			}
			else if (msg_env->clockticks>timeout_Q->head->clockticks && msg_env->clockticks<timeout_Q->tail->clockticks)
			{
				int i;
				for (i=0;i<timeout_Q->free_msg_counter;i++)
				{
					if (msg_env->clockticks<B->clockticks && msg_env->clockticks>A->clockticks)
						break;
					A=A->Next;
					B=B->Next;
				}
				A->Next=msg_env;
				msg_env->Next=B;
				B->Previous=msg_env;
				msg_env->Previous=A;
				timeout_Q->free_msg_counter++;
				return 1;
			}
			else if (msg_env->clockticks>timeout_Q->tail->clockticks)
			{
				Envelope* Last=timeout_Q->tail;
				Last->Next=msg_env;
				msg_env->Previous=Last;
				timeout_Q->tail=msg_env;
				timeout_Q->free_msg_counter++;
				return 1;

			}
		}
	}
}

int K_Enqueue_PCB (NewPCB* Temp,QueuePCB* List)
{
	if (Temp==NULL)
			return 0;
	if (List->Head==NULL && List->Tail==NULL)
	{
//		printf("hello\n");
		List->Head=Temp;
		List->Tail=Temp;
		Temp->Next=NULL;
		Temp->Previous=NULL;
		return 1;
	}
	else
	{
		NewPCB *A=List->Tail;
		List->Tail = Temp;
		Temp->Previous = A;
		A->Next = Temp;
		return 1;
	}
	return 0;
}

int K_Enqueue_MsgEnv (Envelope *Temp, msg_env_Q * List) //List=head of the list on which envelope is to be enqueued
{
	if (Temp==NULL)
		return 0;
	else
	{
		if (List->head!=NULL && List->tail!=NULL)
		{
			Envelope *A=List->tail;
			List->tail->Next=Temp;
			Temp->Next=NULL;
			Temp->Previous=A;
			List->tail=Temp;
			return 1;
		}
		else
		{
			List->head=Temp;
			List->tail=Temp;
			Temp->Next=NULL;
			Temp->Previous=NULL;
			return 1;
		}
	}
}

Envelope* K_Dequeue_MsgEnv(msg_env_Q* List)
{
	if (List->head!= NULL && List->tail!=NULL)
	{
		Envelope *A=List->head;
		if (List->head->Next!=NULL)
		{
			List->head=List->head->Next;
			List->head->Previous=NULL;
			A->Next=NULL;
			return A;
		}
		else
		{
			printf("TEST2\n");
			List->head=NULL;
			List->tail=NULL;
			return A;
		}
	}
	else
		return NULL; //ERROR as A will point to NULL

}

NewPCB* K_Search_Dequeue (int PID,QueuePCB * List)
{
	if (List->Head!=NULL)
	{
		NewPCB *A=List->Head;
		while (PID!=A->ProcID)
		{
			if (A->Next==NULL)
				return NULL;
			A=A->Next;
		}
		if (A->Next==NULL && A->Previous!=NULL)
		{
			NewPCB* Temp=A->Previous;
			A->Previous=NULL;
			Temp->Next=NULL;
			return A;
		}
		else if (A->Previous==NULL && A->Next!=NULL)
		{
			NewPCB* Temp=A->Next;
			Temp->Previous=NULL;
			A->Next=NULL;
			return A;
		}
		else if (A->Next==NULL && A->Previous==NULL)
		{
			List->Head=NULL;
			List->Tail=NULL;
			return A;
		}
		else
		{
			NewPCB* Temp=A->Next;
			NewPCB* Temp2=A->Previous;
			A->Next=NULL;
			A->Previous=NULL;
			Temp2->Next=Temp;
			Temp->Previous=Temp2;
			return A;
		}
	}
	else
		return NULL;
}

NewPCB * K_Dequeue_PCB (msg_env_Q* List)
{

	if (List->head!=NULL && List->tail!=NULL)
	{
		printf("Entered If statement\n");
		NewPCB *Temp=List->head;
		if (List->head->Next==NULL)
		{
			List->head=NULL;
			List->tail=NULL;
			return Temp;
		}
		else
		{
			List->head=List->head->Next;
			List->head->Previous=NULL;
			Temp->Next=NULL;
		}


		return Temp;
	}
	else
		return NULL; //ERROR

}



//CONTEXT SWITCH

void context_switch (jmp_buf *previous, jmp_buf *next)    //check parameter ???????????
{
	int return_val =setjmp(previous);
	if (return_val==0)
		longjmp(next,1);
	longjmp (previous,return_val);
}

//PROCESS_SWITCH

void process_switch() //NEED RELEASE PROCESSOR ??????????
{
	int i;
	for (i=0;i<4;i++)
	{
		if (ReadyQueue[i]->Head!=NULL)
			break;
	}
	NewPCB*NEXT=K_Dequeue_PCB (ReadyQueue[i]);
//	context_swtich (current_process->jbContext,NEXT->jbContext);
	current_process->State=1;
	K_Enqueue_PCB (current_process,ReadyQueue[current_process->Priority]);
	current_process=NEXT;
	current_process->State=4;
	NEXT=NULL;
}

//TRACE ARRAYS

void K_add_to_trace_array (int trace_type, int sender_id, int destination_id, int message_type)
{
	// trace_type=1 means SEND and trace_type=0 means recieve
	if (trace_type==1)
	{
		if (Send_Trace_Array_Counter <=15)
		{
			Send_Trace_Array[Send_Trace_Array_Counter]->SenderID=sender_id;
			Send_Trace_Array[Send_Trace_Array_Counter]->DestintionID=destination_id;
//			Send_Trace_Array [Send_Trace_Array_Counter][2]=time(NULL); //??????????????
			Send_Trace_Array[Send_Trace_Array_Counter]->Msg_Type=message_type;
			Send_Trace_Array_Counter++;

		}
		else
		{
			Send_Trace_Array_Counter =0;
			K_add_to_trace_array (trace_type, sender_id, destination_id, message_type);
		}
	}
	else
	{
		if (Recieve_Trace_Array_Counter <=15)
		{
			Recieve_Trace_Array[Recieve_Trace_Array_Counter]->SenderID=sender_id;
			Recieve_Trace_Array[Recieve_Trace_Array_Counter]->DestintionID=destination_id;
//			Recieve_Trace_Array [Recieve_Trace_Array_Counter][2]=time(NULL); //???????????
			Recieve_Trace_Array[Recieve_Trace_Array_Counter]->Msg_Type=message_type;
			Recieve_Trace_Array_Counter++;
		}
		else
		{
			Recieve_Trace_Array_Counter =0;
			K_add_to_trace_array (trace_type, sender_id, destination_id, message_type);
		}
	}
}

//INTERPROCESS COMMUNICATION

int K_send_message (int destination_pid, Envelope * msg_Envelope)
{
	if (msg_Envelope!=NULL)
	{
		NewPCB *Temp=get_PCB(destination_pid);
		if (Temp!=NULL)
		{
			msg_Envelope->SenderID=current_process->ProcID;
			printf("%d\n",msg_Envelope->SenderID);
			msg_Envelope->DestinationID=Temp->ProcID;
			printf("%d\n",msg_Envelope->DestinationID);
		K_add_to_trace_array (1,current_process->ProcID, msg_Envelope->DestinationID,msg_Envelope->Msg_Type); //message_type ??????????
		Envelope* AB=K_Dequeue_MsgEnv(current_process->Own);

			int A;
			A=K_Enqueue_MsgEnv (AB, Temp->recievelist);
			printf("sender id %d dest id%d\n",Temp->recievelist->head->SenderID,Temp->recievelist->head->DestinationID);
			if (Temp->State==3)
			{
				Temp->State=1;
				int B;
				B=K_Enqueue_PCB(Temp, ReadyQueue[Temp->Priority]);
				return (A && B);
			}
			return A;
		}
		else
			return 0; //ERROR
	}

	else
	{
		//DISPLAY ERROR
		return 0;
	}
}

Envelope* K_recieve_message ()
{
//	printf("FUCK U SANJITH\n");
	if (current_process->recievelist->head!=NULL)
	{
		Envelope *Temp=K_Dequeue_MsgEnv(current_process->recievelist);
		if (Temp!=NULL)
		{
			K_add_to_trace_array (0,Temp->SenderID, Temp->DestinationID,Temp->Msg_Type); //message_type ?????????
			if (current_process->State==3)
			{
				K_Enqueue_PCB(current_process, ReadyQueue[current_process->Priority]);
				current_process->State=1;
			}
			return Temp;
		}
		else
			return NULL;
	}
	else
	{
		current_process->State=3;
		K_Enqueue_PCB(current_process,Blocked_On_Resources[current_process->Priority]);
		return NULL;
	}
}

//MESSAGE MANAGEMENT

Envelope * K_request_msg_env ()
{
	if (Free_Env_Queue->head==NULL)
	{
//		if (current_process->Priority==i-process-PRIORITY) //check for i-process using the PID ????????
//			return NULL;
//		else
//		{
			int A;
			A=K_Enqueue_PCB (current_process,Blocked_On_Envelope[current_process->Priority]);
//			process_switch ();
			current_process->State=2;
			return NULL;
//		}
	}

	else
	{
		Envelope* Temp=K_Dequeue_MsgEnv(Free_Env_Queue);
		K_Enqueue_MsgEnv(Temp,current_process->Own);
		Free_Env_Queue->free_msg_counter--;
		if (current_process->State==2)
		{
			current_process->State=1;
			NewPCB* A=K_Dequeue_PCB(Blocked_On_Envelope[current_process->Priority]);
			K_Enqueue_PCB(current_process,ReadyQueue[A->Priority]);

		}
		return Temp;
	}
}

int K_release_msg_envelope (Envelope * msg_Envelope)
{
	int k,l;
	l=-1;
	for (k=0;k<4;k++)
	{
		l=l+1;
		if (Blocked_On_Envelope[l]->Head!=NULL)
			break;
	}
	if (Blocked_On_Envelope[l]->Head!=NULL)
	{

		NewPCB *Temp=K_Dequeue_PCB(Blocked_On_Envelope[l]);
		Temp->State=1;
		K_Dequeue_MsgEnv(current_process->Own);
		int A=K_Enqueue_MsgEnv(msg_Envelope,Temp->Own);
		int B=K_Enqueue_PCB(Temp,ReadyQueue[Temp->Priority]);
		return (A && B);
	}
	else
	{
		int A=K_Enqueue_MsgEnv (msg_Envelope, Free_Env_Queue);
		K_Dequeue_MsgEnv(current_process->Own);
		Free_Env_Queue->free_msg_counter++;
		return A;
	}
}

//PROCESSOR MANAGEMENT

int K_release_processor ()
{
	current_process->State=1;
	int A=K_Enqueue_PCB(current_process,ReadyQueue[current_process->Priority]);
	process_switch();
	return A;
}

//NULL PROCESS

void null_process()
{
	while (1);
	{
		K_release_processor();
	}
}
/*
int K_request_process_status (Envelope * msg_env_ptr)
{
	if (msg_env_ptr==NULL)
		return 0; //ERROR
	else
	{
		sprintf(Status_Array,"");
		int i;
		for (i=0;i<3;i++)
		{
			NewPCB *Temp;
			Temp=PCBList->head;
			char* tempchar[20];
			sprintf(tempchar,"%d %d %d,",Temp->ProcID,Temp->State,Temp->Priority);
			strcat(Status_Array,tempchar);
			Temp=Temp->Next;
			strcpy(msg_env_ptr->Data,Status_Array);
			return 1;
		}

	}
}
*/
//TERMINATE

//CHANGE PRIORITY

int K_change_priority (int new_Priority, int Target_Process_ID)
{
	NewPCB *ptr=get_PCB (Target_Process_ID);
	if (ptr!=NULL && new_Priority<=3)//&& ptr->ProcID!= ID of i-process && new_Priority <=3)
	{

		if (ptr->State ==1)
		{
			NewPCB* Temp=K_Search_Dequeue(ptr->ProcID,ReadyQueue[ptr->Priority]);
			printf("%d\n",Temp->Priority);
			Temp->Priority=new_Priority;
			int A=K_Enqueue_PCB (Temp,ReadyQueue[Temp->Priority]);
			return A;
		}
		else
		{
			ptr->Priority=new_Priority;
			return 1;
		}
	}
	else
	{
		ptr=NULL;
		return 0;
	}
}

int K_request_delay (int time_delay, int wakeup_code,Envelope* msg_env)
{
	msg_env->Msg_Type=wakeup_code;
	msg_env->clockticks=time_delay;
	K_send_message(5000,msg_env); //5000=TIMER PROCESS ID
	printf("message to requeust delay to timer process sent\n");
	return 1;
}
/*
int K_send_console_chars (Envelope * MsgEnv)
{
	if (MsgEnv!=NULL)
	{
		int A=MsgEnv->SenderID;
		int B;
		B=K_send_message (0011, MsgEnv); //0011 PID of CRT i-process
		if (B==1)
		{
			Envelope * Temp=K_recieve_message();
			if (Temp->Msg_Type==6) //CRT_akn=6
			{
				Temp->Msg_Type=2; //display_acknowledgement
				int C=K_send_message (A,Temp);
				if (C==1)
					return 1;
				else
					return 0;
			}
			else
				return 0;
		}
		else
			return 0;
	}
	else
		return 0;

}

int K_get_console_chars (Envelope * MsgEnv)
{
	if (MsgEnv!=NULL)
	{
		int return_val=K_send_message (3000,MsgEnv); // 3000=KB i process id???????????????????????/
		return return_val;
	}
	else
		return 0; //DISPLAY ERROR ?????????????
}

int K_get_trace_buffers (Envelope* MsgEnv)
{
	if (MsgEnv!=NULL)
	{

	}
	else
		return 0; //DISPLAY ERROR ????????????????
}
*/
