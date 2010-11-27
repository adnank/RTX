/*
 * RTXProcesses.c
 *
 *  Created on: 2010-11-18
 *      Author: abubakar
 */

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

void Create_MSG (Envelope* env, int Sender_ID)
{
	env->SenderID=Sender_ID;
	env->DestinationID = 0;
	env->Next = NULL;
	env->Previous = NULL;
	env->clockticks = 3;
	env->Msg_Type=0;
}
int Make_PCBList(NewPCB * Temp, QueuePCB *List)
{
	if (Temp==NULL)
		return 0;
	if (List->Head==NULL)
	{
		List->Head=Temp;
		List->Tail=Temp;
		Temp->Kernelpt_Next=NULL;
		Temp->Kernelpt_Previous=NULL;
		return 1;
	}
	else
	{
		NewPCB *A=List->Tail;
		List->Tail = Temp;
		Temp->Kernelpt_Previous = A;
		Temp->Kernelpt_Next=NULL;
		A->Kernelpt_Next = Temp;
		return 1;
	}
	return 0;
}



int main() {
	NewPCB* Temp;
	Temp = (NewPCB *) malloc(sizeof(NewPCB));
	Temp->Kernelpt_Next = NULL;
	Temp->Kernelpt_Previous = NULL;
	Temp->Next = NULL;
	Temp->Previous = NULL;
	Temp->State = 1;
	Temp->ProcID = 100; //process id of the process
	Temp->Priority = 1; //priority of the process
	Temp->recievelist = (QueueEnv*) malloc (sizeof(QueueEnv));//list of envelopes recieved
	Temp->Own = (QueueEnv*) malloc (sizeof(QueueEnv)); //List of envelopes that the process owns
/*	Temp->Stack=((char*)malloc(char))+size-STK_OFFSET;
//	Temp->jbContext = 0; //used by setjump and longjump, not sure if returntype=int. ?????????????
//	Temp->StartAdd=5 //STARTING ADDRESS OF PROCESS
	if (setjmp(jbContext)==0)
	{
		jmpsp=Temp->Stack;
		if (setjmp(Temp->jbContext)== 0)
			longjmp(Temp->jbContext,1);
		else
		{
			void (*tmp_fn) ();
			tmp_fn=(void*) current_process->StartAdd;
			tmp_fn();
		}

	}
*/

	NewPCB* Temp2;
	Temp2 = (NewPCB *) malloc(sizeof(NewPCB));
	Temp2->Kernelpt_Next = NULL;
	Temp2->Kernelpt_Previous = NULL;
	Temp2->Next = NULL;
	Temp2->Previous = NULL;
	Temp2->State = 2;
	Temp2->ProcID = 300; //process id of the process
	Temp2->Priority = 2; //priority of the process
	Temp2->recievelist = (QueueEnv*) malloc (sizeof(QueueEnv)); //list of envelopes recieved
	Temp2->Own = (QueueEnv*) malloc (sizeof(QueueEnv)); //List of envelopes that the process owns
//	Temp2->jbContext = 0; //used by setjump and longjump, not sure if returntype=int. ?????????????

	NewPCB* Temp3;
	Temp3 = (NewPCB *) malloc(sizeof(NewPCB));
	Temp3->Kernelpt_Next = NULL;
	Temp3->Kernelpt_Previous = NULL;
	Temp3->Next = NULL;
	Temp3->Previous = NULL;
	Temp3->State = 3;
	Temp3->ProcID = 500; //process id of the process
	Temp3->Priority = 3; //priority of the process
	Temp3->recievelist = (QueueEnv*) malloc (sizeof(QueueEnv));//list of envelopes recieved
	Temp3->Own = (QueueEnv*) malloc (sizeof(QueueEnv)); //List of envelopes that the process owns
//	Temp3->jbContext = 0; //used by setjump and longjump, not sure if returntype=int. ?????????????

	NewPCB* CRT;
	CRT = (NewPCB *) malloc(sizeof(NewPCB));
	CRT->Kernelpt_Next = NULL;
	CRT->Kernelpt_Previous = NULL;
	CRT->Next = NULL;
	CRT->Previous = NULL;
	CRT->State = 4;
	CRT->ProcID = 1000; //process id of the process
	CRT->Priority = 10; //priority of the process
	CRT->recievelist = (QueueEnv*) malloc (sizeof(QueueEnv));//list of envelopes recieved
	CRT->Own = (QueueEnv*) malloc (sizeof(QueueEnv)); //List of envelopes that the process owns

	NewPCB* KB;
	KB = (NewPCB *) malloc(sizeof(NewPCB));
	KB->Kernelpt_Next = NULL;
	KB->Kernelpt_Previous = NULL;
	KB->Next = NULL;
	KB->Previous = NULL;
	KB->State = 4;
	KB->ProcID = 3000; //process id of the process
	KB->Priority = 10; //priority of the process
	KB->recievelist = (QueueEnv*) malloc (sizeof(QueueEnv));//list of envelopes recieved
	KB->Own = (QueueEnv*) malloc (sizeof(QueueEnv)); //List of envelopes that the process owns
//	Temp3->jbContext = 0; //used by setjump and longjump, not sure if returntype=int. ?????????????


	int k;
	for (k=0; k<4; k++)
	{
		Blocked_On_Resources[k]=malloc(sizeof(QueuePCB));
		Blocked_On_Resources[k]->Head=NULL;
		Blocked_On_Resources[k]->Tail=NULL;
	}

	K_Enqueue_PCB(Temp3,Blocked_On_Resources[Temp3->Priority]);

//	QueuePCB* ARRAY=(QueuePCB) malloc (sizeof (QueuePCB));

//	ReadyQueue [0] = (QueuePCB*) malloc (sizeof(QueuePCB));
	int i;
	for (i=0; i<4; i++)
	{
		ReadyQueue[i]=malloc(sizeof(QueuePCB));
		ReadyQueue [i]->Head=NULL;
		ReadyQueue [i]->Tail=NULL;
	}
	int KJ;
	for (KJ=0;KJ<16;KJ++)
	{
		Send_Trace_Array[KJ]=malloc (sizeof(TraceArray));
		Send_Trace_Array[KJ]->DestintionID=0;
		Send_Trace_Array[KJ]->SenderID=0;
		Send_Trace_Array[KJ]->Msg_Type=0;
	}
	int KL;
	for (KL=0;KL<16;KL++)
	{
		Recieve_Trace_Array[KL]=malloc (sizeof(TraceArray));
		Recieve_Trace_Array[KL]->DestintionID=0;
		Recieve_Trace_Array[KL]->SenderID=0;
		Recieve_Trace_Array[KL]->Msg_Type=0;
	}
	int kL;
	for (kL=0; kL<4; kL++)
	{
		Blocked_On_Envelope[kL]=malloc(sizeof(QueuePCB));
		Blocked_On_Envelope[kL]->Head=NULL;
		Blocked_On_Envelope[kL]->Tail=NULL;
	}
	K_Enqueue_PCB(Temp2,Blocked_On_Envelope[Temp2->Priority]);

	printf("Test\n");

	PCBList = (QueuePCB*) malloc(sizeof(QueuePCB));
	Make_PCBList(Temp,PCBList);
	Make_PCBList(Temp2,PCBList);
//	printf (" Head node in PCBList %d\n", PCBList->Head->ProcID);
	Make_PCBList(Temp3,PCBList);
	Make_PCBList(CRT,PCBList);
	Make_PCBList(KB,PCBList);
//	printf (" Middle node in PCBList %d\n", PCBList->Head->Kernelpt_Next->ProcID);
//	printf (" Tail node in PCBList %d\n", PCBList->Tail->ProcID);
	Free_Env_Queue = malloc(sizeof(QueueEnv));
	Free_Env_Queue->Head=NULL;
	Free_Env_Queue->Tail=NULL;
	Free_Env_Queue->free_msg_ctr=0;



	Envelope* msg_1 = malloc (sizeof (Envelope));
	Create_MSG(msg_1, 10);
	printf ("Created msg_1 with ClockTicks %d\n", msg_1->clockticks);

	Envelope* msg_2 = malloc (sizeof (Envelope));
	Create_MSG(msg_2, 20);
	msg_2->clockticks=5;
	printf ("Created msg_2 with ClockTicks %d\n", msg_2->clockticks);

	Envelope* msg_3 = malloc (sizeof (Envelope));
	Create_MSG(msg_3,15);
	msg_3->clockticks=7;
	printf ("Created msg_3 with ClockTicks %d\n", msg_3->clockticks);

	Timeout_List=(QueueEnv*) malloc(sizeof(QueueEnv));
	Timeout_List->Head=NULL;
	Timeout_List->Tail=NULL;
	Timeout_List->free_msg_ctr=0;

	K_Sort_Envelope_Enqueue(msg_1);
//	printf("1st envelope has ticks %d \n",Timeout_List->Head->clockticks);
//	printf("1st envelope has ticks %d \n",Timeout_List->Tail->clockticks);

	K_Sort_Envelope_Enqueue(msg_2);
//	printf("1st envelope has ticks %d \n",Timeout_List->Tail->Previous->clockticks);
//	printf("2st envelope has ticks %d \n",Timeout_List->Tail->clockticks);

	K_Sort_Envelope_Enqueue(msg_3);
//	printf("1st envelope has ticks %d \n",Timeout_List->Tail->Previous->Previous->clockticks);
//	printf("2st envelope has ticks %d \n",Timeout_List->Tail->Previous->clockticks);
//	printf("3st envelope has ticks %d \n",Timeout_List->Tail->clockticks);

	i_buffer=(input_buffer*) malloc (sizeof(input_buffer));
	o_buffer=(output_buffer*) malloc (sizeof(output_buffer));


	current_process=(NewPCB*) malloc(sizeof (NewPCB));

	current_process=Temp;
	K_Enqueue_MsgEnv(msg_1,Free_Env_Queue);
	K_Enqueue_MsgEnv(msg_2,Free_Env_Queue);
	K_Enqueue_PCB(Temp,ReadyQueue[Temp->Priority]);
	K_request_msg_env();

	Temp->Own->Head->Data[0]='a';
//	Temp->Own->Head->Data[1]='b';
//	Temp->Own->Head->Data[2]='c';
//	Temp->Own->Head->Data[3]='d';
	int KHG;
	KHG=K_send_message(KB->ProcID,Temp->Own->Head);
	printf("%d\n",KHG);
	current_process=KB;
//	printf("%c\n",KB->recievelist->Head->Data[0]);
	i_process_kb();
//	current_process=Temp;
	if (Temp->recievelist!=NULL)
			printf("msg recieved\n");
//	printf("iprocess sent me an envelope which has sender id %d\n",current_process->recievelist->Head->SenderID);
//	printf("FUK MY LIFE\n");
//	current_process=Temp;

//	current_process=CRT;
//	i_process_crt();

//	Envelope* MON;
//	MON=K_recieve_message();


//	K_request_msg_env();
//	Send_Trace_Array_Counter=0;
//	Recieve_Trace_Array_Counter=0;
//	K_send_message(Temp2->ProcID,Temp->Own->Head);



//	printf("message i got has sender id %d \n", Temp2->recievelist->Head->SenderID);

//	printf("envelope info added to Send trace array %d %d \n", Send_Trace_Array[Send_Trace_Array_Counter-1]->SenderID,Send_Trace_Array[Send_Trace_Array_Counter-1]->DestintionID);
	/*	K_send_message(Temp3->ProcID,Temp->Own->Head);
	printf("envelope info added to Send trace array %d %d \n", Send_Trace_Array[Send_Trace_Array_Counter-1]->SenderID,Send_Trace_Array[Send_Trace_Array_Counter-1]->DestintionID);
	current_process=Temp2;
	Envelope* ABC=K_recieve_message();
	printf("envelope info added to Recieve trace array %d %d \n", Recieve_Trace_Array[Recieve_Trace_Array_Counter-1]->SenderID,Recieve_Trace_Array[Recieve_Trace_Array_Counter-1]->DestintionID);
	current_process=Temp3;
	K_recieve_message();
	printf("envelope info added to Recieve trace array %d %d \n", Recieve_Trace_Array[Recieve_Trace_Array_Counter-1]->SenderID,Recieve_Trace_Array[Recieve_Trace_Array_Counter-1]->DestintionID);

*/
	//	printf("envelope in the free queue has sender PID %d \n",Free_Env_Queue->Head->SenderID);
//	printf("envelope in the free queue has sender PID %d \n",Free_Env_Queue->Tail->SenderID);
//	K_release_msg_envelope(Temp->Own->Head);
/*
	printf ("first node in PCBList %d\n", PCBList->Head->ProcID);

	printf (" tail node in PCBList %d\n", PCBList->Tail->ProcID);
	printf (" Middle node in PCBList %d\n", PCBList->Tail->Kernelpt_Previous->ProcID);
	printf (" Head node in PCBList %d\n", PCBList->Tail->Kernelpt_Previous->Kernelpt_Previous->ProcID);
*/

//	K_change_priority(2,100);
//	printf("the new Priority %d \n",Temp->Priority);
//	printf("the new PID %d \n",ReadyQueue[Temp->Priority]->Head->ProcID);
//	K_change_priority(3,300);
//	printf("the new PID %d \n",Temp2->Priority);
//	printf("I have envelopes with head PID %d \n Tail PID %d\n",Temp->Own->Head->SenderID,Temp->Own->Tail->SenderID);
//	K_release_msg_envelope(Temp->Own->Head);
//	K_request_process_status(Temp->Own->Head);
//	printf("%c",Temp->Own->Head->Data[0]);
//	printf("%c",Temp->Own->Head->Data[1]);
//	printf("%c\n",Temp->Own->Head->Data[2]);
//	printf("free env head PID %d \n Tail PID %d\n",Free_Env_Queue->Head->SenderID,Free_Env_Queue->Tail->SenderID);
//	if (Temp->Own->Tail==NULL && Temp->Own->Head==NULL)
//		printf("FUCK U TOO\n");
//	printf("Temp2 has envelope with PID %d \n",Temp2->Own->Head->SenderID);
//	K_request_msg_env();
//	printf("envelope in the free queue has sender PID %d \n",Free_Env_Queue->Head->SenderID);
//	printf("the acquired head has the sender PID %d\n and Tail has Sender ID %d\n",Temp->Own->Head->SenderID,Temp->Own->Tail->SenderID);

//	current_process=Temp2;
//	K_request_msg_env();

//	printf ("the blocked process has PID %d \n and State %d \n",Blocked_On_Resources[Temp->Priority]->Head->ProcID,Blocked_On_Resources[Temp->Priority]->Head->State);
	//current_process=Temp;
	//printf("Current Process PID %d\n", current_process->ProcID);

	//K_send_message(Temp2->ProcID,msg_1);
	//printf ("sender ID %d \nDestinationID %d\n", Temp2->recievelist->Head->SenderID,Temp2->recievelist->Head->DestinationID);
/*
	current_process=Temp2;
	K_send_message(Temp3->ProcID,msg_2);
	printf ("sender ID %d \nDestinationID %d\n", Temp3->recievelist->Head->SenderID,Temp3->recievelist->Head->DestinationID);

	current_process=Temp;
	K_send_message(Temp3->ProcID,msg_1);
	printf ("sender ID %d \nDestinationID %d\n", Temp3->recievelist->Head->SenderID,Temp3->recievelist->Head->DestinationID);
*/

/*	current_process=Temp3;
	Envelope *ABC=K_recieve_message();
	printf ("message recieved has a sender PID %d and a destination PID %d \n",ABC->SenderID,ABC->DestinationID);
	Envelope *KBC=K_recieve_message();
	printf ("message recieved has a sender PID %d and a destination PID %d \n",KBC->SenderID,KBC->DestinationID);

	Envelope *KLBC=K_recieve_message();

	printf ("Process in Blocked_on_Resources queue has PID %d \n",Blocked_On_Resources[Temp3->Priority]->Head->ProcID);
*/

	return (0);

}

/*
 * NewPCB *Temp;
 NewPCB *Temp2;
 NewPCB *Temp3;
 Temp=(NewPCB*) malloc (sizeof(NewPCB));
 PCBList=Temp;
 Temp2=(NewPCB*) malloc (sizeof(NewPCB));
 Temp3=(NewPCB*) malloc (sizeof(NewPCB));
 Temp->Kernel_ptr=Temp2;
 Temp2->Kernel_ptr=Temp3;
 Temp3->Kernel_ptr=NULL;
 Temp->ProcID=3086;
 Temp2->ProcID=3966;
 Temp3->ProcID=3088;
 Temp->State=4; //EXECUTING
 Temp2->State=1; //READY
 Temp3->State=1; //READY
 Temp->Next=NULL;
 Temp2->Next=NULL;
 Temp3->Next=NULL;
 Temp->Priority=0;
 Temp2->Priority=1;
 Temp3->Priority=2;


 //	PriorityQueue[0]=(NewPCB*) malloc (sizeof (NewPCB));
 //	PriorityQueue[1]=(NewPCB*) malloc (sizeof (NewPCB));
 PriorityQueue[2]=(NewPCB*) malloc (sizeof (NewPCB));
 //	PriorityQueue[3]=(NewPCB*) malloc (sizeof (NewPCB));
 //	PriorityQueue[0]=NULL;
 //	PriorityQueue[1]=NULL;
 PriorityQueue[2]=NULL;
 //	PriorityQueue[3]=NULL;

 //	current_process=Temp;
 //	printf ("%d",current_process->head);

 int z;
 z=K_Enqueue_PCB (Temp3,PriorityQueue[2],1);
 //	printf("%d\n",Temp3->ProcID);
 //	printf("%d",PriorityQueue[2]->ProcID);
 //	printf("%d\n",PriorityQueue[2]->ProcID);
 //	printf("%d",PriorityQueue[3]->ProcID);

 //	Temp->head=NULL;
 //	Temp2->head=NULL;
 //	Temp3->head=NULL;
 //	Temp->recievelist=NULL;
 //	Temp2->recievelist=NULL;
 //	Temp3->recievelist=NULL;
 //
 //
 //	Envelope * Env;
 //	Envelope * Env2;
 //	Envelope * Env3;
 //	Env=(Envelope*) malloc (sizeof(Envelope));
 //	Env2=(Envelope*) malloc (sizeof(Envelope));
 //	Env3=(Envelope*) malloc (sizeof(Envelope));
 //	Free_Env_Queue=Env;
 //	Env->kernelpt=Env2;
 //	Env2->kernelpt=Env3;
 //	Env3->kernelpt=NULL;
 //	Env->Next=NULL;
 //	Env2->Next=NULL;
 //	Env3->Next=NULL;
 //	Env->DestinationID=0;
 //	Env2->DestinationID=0;
 //	Env3->DestinationID=0;
 //	Env->SenderID=0;
 //	Env2->SenderID=0;
 //	Env3->SenderID=0;
 //	Env->clockticks=0;
 //	Env2->clockticks=0;
 //	Env3->clockticks=0;
 //	Env->Msg_Type=0;
 //	Env2->Msg_Type=0;
 //	Env3->Msg_Type=0;

 //	NewPCB *A;
 //	A=get_PCB (3966);






 //INITIALIZE EVERYTHING USING THE THE INITIALIZATION FILE

 //PROCESS A

 //PROCESS B
 	while (true)
 {
 Envelope *A=recieve_message ();
 int B=send_message (C->ProcID, A);
 }
 */

