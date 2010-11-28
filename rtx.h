/*will include all structs, globally defined variables, function definitions*/
#include <string.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <ucontext.h>
#include <signal.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/ipc.h>


#ifndef RTX_H_
#define RTX_H_

//Global Variables
#define NUM_OF_ENVELOPES	 50
#define NUM_OF_PROC 		 16
#define NUM_OF_PRIORITY 	 4
#define NUM_OF_CHILDREN		 2
#define MSG_DATA			 512
#define MAX_STACKSIZE		 16384 //(128^2)
#define BUFFER_SIZE			 512
#define TRACE_ARRAY			 16
#define ON					 1
#define OFF					 0

int ss, mm, hh;


//Process States
#define READY		11
#define BLK_ON_ENV	12
#define BLK_ON_RSC	13
#define INTERRUPT	14
#define EXECUTING	15
#define IPROCESS	16

//Process ID's
#define PROC_A            0001
#define PROC_B            0002
#define PROC_C            0003
#define PROC_TST1         0004
#define PROC_TST2         0005
#define PROC_TST3         0006
#define PROC_TST4         0007
#define PROC_TST5         0008
#define PROC_TST6         0009
#define KBD_I             0010
#define CRT_I             0011
#define TIMER_I           0012
#define NULL_PROC         0013
#define PROC_CCI          0014
#define PROC_SET_PRIORITY 0015
#define PROC_WALL_CLK	  0016

//Process Priorities
#define P_P0		0
#define P_P1		1
#define P_P2		2
#define P_P3		3
#define P_IPROCESS	4

//MESSAGE TYPES
#define INITIAL			0
#define WAKEUP_CODE		1
#define DISPLAY_ACK		2
#define CONSOLE_OUT		3
#define KB_INPUT		4
#define REQUEST_DELAY	5
#define CRT_ACK			6
#define COUNTER_REPORT 	7

typedef void (*start_address)(void);	//occurence of proc_address

//****PROCESS RECORD****
typedef struct proc_record{
	int process_id;
	int priority;
	int stack_size;
	int proc_status;
	start_address proc_address;			//start address of the process code
}proc_record;

proc_record init_table[NUM_OF_PROC];	//static array(initialization table)

//****MESSAGE ENVELOPE****
typedef struct Envelope{
	struct Envelope *kernelpt_next; //used for creating the list of envelopes
	struct Envelope *kernelpt_previous;
	struct Envelope *Next; // used to put the queue in different lists
	struct Envelope *Previous; //used to point to the previous message envelope in the list
	int SenderID; // who sent the message
	int DestinationID; //where the message will be sent
	int clockticks; // for waking,sleeping and ualarm functions
	int Msg_Type; //type of message
	char *Data [MSG_DATA]; //pointer to an array of characters
}Envelope;



//****MESSAGE ENVELOPE QUEUE****
typedef struct msg_env_Q{
	Envelope *head;
	Envelope *tail;
	int free_msg_counter;
}msg_env_Q;

msg_env_Q *timeout_Q;					//timeout queue used by timer handler
msg_env_Q *Free_Env_Queue; 				//pointing to the head and tail of the envelopes in the free envleope queue



//****PROCESS CONTROL BLOCK****
typedef struct NewPCB {
	int State; 							//for the state of the process
	int ProcID; 						//process id of the process
	struct NewPCB *Kernelpt_Next; 		//used for making the Process list
	struct NewPCB *Kernelpt_Previous; 	//used for making the Process List
	struct NewPCB *Next;				//pointer to put the PCB in the lists it is supposed to be in
	struct NewPCB *Previous; 			// pointer that points to the previous PCB in the list
	int Priority; 						//priority of the process
	msg_env_Q *Own; 				//list of envelopes that a process owns
	msg_env_Q *recievelist; 		//list of envelopes recieved
	char * Stack;
	start_address address;
	jmp_buf jbContext; 					//used by setjump and longjump, not sure if returntype=int. ?????????????
	//Envelope *head; 					//head for the list of the envelopes that the process owns
	//Envelope *tail; 					//tail for the list of the envelopes that the process owns //FOR WHAT ????
}NewPCB;


NewPCB *current_process; 				//pointer that points to the PCB of the currently executing process
NewPCB *Executing;						//pointer that points to the pcb of the currently executing process



//****PROCESS QUEUE****
typedef struct QueuePCB{
	NewPCB *Head; 						//pointer to the first PCB in the list
	NewPCB *Tail; 						//pointer to the last PCB in the list
}QueuePCB;

QueuePCB *ReadyQueue [NUM_OF_PRIORITY];
QueuePCB *Blocked_On_Resources [NUM_OF_PRIORITY]; 		//lack of recieved messages
QueuePCB *Blocked_On_Envelope [NUM_OF_PRIORITY]; 		//(free envleopes)pointer that points to the head of the blocked on Envelope queue
//QueuePCB *Blocked_On_interupt [NUM_OF_PRIORITY]; 		//pointer that points to the head of the blocked on interrupt queue

QueuePCB *PCBList; //keeps track of all PCB's



//****TRACE BUFFER****
typedef struct TraceArray{
	int SenderID;
	int DestintionID;
	int Msg_Type;
	int timestamp;
}TraceArray;

char * Status_Array [250]; 				//index represents number of processes
int Send_Trace_Array_Counter; 			// counter to keep track how much array is filled
int Recieve_Trace_Array_Counter; 		// counter to keep track how much array is filled
TraceArray* Recieve_Trace_Array [TRACE_ARRAY];
TraceArray* Send_Trace_Array [TRACE_ARRAY];


//****I/O BUFFERS****
typedef struct io_buffer{
	char buffer[BUFFER_SIZE]; //512
	int Length;
	int Read;
}io_buffer;


io_buffer *output_buffer;
io_buffer *input_buffer;

int hh,mm,ss;
int Display_WALLCLOCK;
int HIDE_WALLCLOCK;
void interrupt_handler (int variablesignal);
void CCI_process();

//process start address prototypes (PC)
void add_procA();
void add_procB();
void add_procC();
void add_ptst1();
void add_ptst2();
void add_ptst3();
void add_ptst4();
void add_ptst5();
void add_ptst6();
void add_CCI();
void add_PRTY();
void add_TIMER();
void add_KBD();
void add_CRT();
void add_pNull();
void add_CLK();

//FUNCTION PROTOTYPES
void context_switch(NewPCB *current, NewPCB * next_proc);
void init_ioBuffers();
void init_TraceArrays();
void initialize_table();
void init_processes();
void init_blkOnEnv_Q();
void init_blkOnRsc_Q();
void init_rpq();
void init_env();
void init_timeout_Q();
void init_free_env_Q();

//Primitives Prototypes
Envelope* K_Dequeue_MsgEnv(msg_env_Q* List);
Envelope* K_recieve_message();
NewPCB * get_PCB (int process_id);
int K_Sort_Envelope_Enqueue (Envelope * msg_env);
int K_Enqueue_PCB (NewPCB* Temp,QueuePCB* List);
int K_Enqueue_MsgEnv (Envelope *Temp, msg_env_Q * List);
//NewPCB* K_Search_Dequeue (int PID,QueuePCB * List);
//NewPCB * K_Dequeue_PCB (msg_env_Q* List);
void K_add_to_trace_array (int trace_type, int sender_id, int destination_id, int message_type);
int K_send_message (int destination_pid, Envelope * msg_Envelope);
Envelope * K_request_msg_env ();
int K_release_msg_envelope (Envelope * msg_Envelope);
int K_release_processor ();
void null_process();
int K_change_priority (int new_Priority, int Target_Process_ID);
int K_request_delay (int time_delay, int wakeup_code,Envelope* msg_env);


void atomic(int change);
void i_process_timer();
void i_process_kb();

#endif /* RTX_H_ */
