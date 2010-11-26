/*
 * structures.h
 *
 *  Created on: 2010-11-18
 *      Author: abubakar
 */

#ifndef STRUCTURES_H_
#define STRUCTURES_H_
#include <string.h>
#include <setjmp.h>

typedef struct Envelope{
	struct Envelope *kernelpt; //used for creating the list of envelopes
	struct Envelope *Next; // used to put the queue in different lists
	struct Envelope *Previous; //used to point to the previous message envelope in the list
	int SenderID; // who sent the message
	int DestinationID; //where the message will be sent
	int clockticks; // for waking,sleeping and ualarm functions
	int Msg_Type; //type of message
	/* NOTHING at initialization=0
	 * wakeup_code =1
	 * display_acknowledgement =2
	 * console_out=3
	 * KB_input=4
	 * request_delay=5
	 * CRT_ack=6
	 */

	char *Data [256]; //pointer to an array of characters
}Envelope;

typedef struct QueueEnv{
	Envelope *Head; //pointer to te first PCB in the list
	Envelope *Tail; //pointer to the last PCB in the list
	int free_msg_ctr;//keept track of number of free msgs
}QueueEnv;

typedef struct NewPCB {
	struct NewPCB * Kernel_ptr;
	int State; //for the state of the process
	/* Ready=1
	 * Blocked on Envelope =2  blocked due to lack of free envelopes
	 * Blocked on Resources =3 blocked due to lack in receieved messages
	 * Executing =4
	 * Interupted =5
	 */
	int ProcID; //process id of the process
	struct NewPCB *Kernelpt_Next; //used for making the Process list
	struct NewPCB *Kernelpt_Previous; //used for making the Process List
	struct NewPCB *Next; //pointer to put the PCB in the lists it is supposed to be in
	struct NewPCB *Previous; // pointer that points to the previous PCB in the list
	int Priority; //priority of the process
	struct QueueEnv *Own; //list of envelopes that a process owns
//	Envelope *head; //head for the list of the envelopes that the process owns
//	Envelope *tail; //tail for the list of the envelopes that the process owns //FOR WHAT ????
	struct QueueEnv *recievelist; //list of envelopes recieved
	char * Stack;
	int StartAdd;
	jmp_buf jbContext; //used by setjump and longjump, not sure if returntype=int. ?????????????

}NewPCB;

typedef struct QueuePCB{
	NewPCB *Head; //pointer to te first PCB in the list
	NewPCB *Tail; //pointer to the last PCB in the list
}QueuePCB;

QueuePCB *ReadyQueue [4];
QueuePCB *Blocked_On_Resources [4]; //lack of recieved messages
QueuePCB *Blocked_On_Envelope [4]; //(free envleopes)pointer that points to the head of the blocked on Envelope queue
QueuePCB *Blocked_On_interupt [4]; //pointer that points to the head of the blocked on interrupt queue

QueueEnv *Free_Env_Queue; //pointing to the head and tail of the envelopes in the free envleope queue
QueuePCB* PCBList; //used to make the list of the processes, this pointer points to the first process in the list

typedef struct TraceArray{
	int SenderID;
	int DestintionID;
	int Msg_Type;

}TraceArray;

char * Status_Array [250]; //index represents number of processes


TraceArray* Send_Trace_Array [16];
int Send_Trace_Array_Counter; // counter to keep track how much array is filled
TraceArray* Recieve_Trace_Array [16];
int Recieve_Trace_Array_Counter; // counter to keep track how much array is filled

NewPCB *current_process; //pointer that points to the PCB of the currently executing process


NewPCB* Executing;//pointer that points to the pcb of the currently executing process






















#endif /* STRUCTURES_H_ */
