/*will include all structs, globally defined variables, function definitions*/
#ifndef RTX_H_
#define RTX_H_

//Global Variables
#define NUM_OF_ENVELOPES	 50
#define NUM_OF_PROC 		 15
#define NUM_OF_PRIORITY 	 4
#define NUM_OF_CHILDREN		 2
#define MSG_DATA			 512
#define MAX_STACKSIZE		 16384 //(128^2) 262144(512^2)

//Process States
#define READY		11
#define BLK_ON_ENV	12
#define BLK_ON_RSC	13
#define INTERRUPT	14
#define RUNNING		15
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
#define P_IPROCESS	0  //highest priority
#define P_P1		1
#define P_P2		2
#define P_P3		3
#define P_P4		4
#define P_NULL		5

#define INITIAL			0
#define WAKEUP_CODE		1
#define DISPLAY_ACK		2
#define CONSOLE_OUT		3
#define KB_INPUT		4
#define REQUEST_DELAY	5

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
	struct Envelope *kernelpt; 	//used for creating the list of envelopes
	struct Envelope *Next; 		// used to put the queue in different lists
	int SenderID; 			// who sent the message
	int DestinationID; 		//where the message will be sent
	int clockticks; 		// for waking,sleeping and ualarm functions
	int Msg_Type[50];		//type of message
	char Data [MSG_DATA]; //pointer to an array of characters
}Envelope;

//****PROCESS CONTROL BLOCK****
typedef struct NEWPCB {
	struct NEWPcb * Kernel_ptr;
	int State; 					//for the state of the process
	int ProcID; 				//process id of the process
	struct NewPcb *Next; 				//pointer to put the PCB in the lists it is supposed to be in
	int Priority; 				//priority of the process
	struct NEWPCB *kernelpt; 			//allows kernel to keep a list of all the processes
	Envelope *head; 			//head for the list of the envelopes that the process owns
	Envelope *tail; 			//tail for the list of the envelopes that the process owns //FOR WHAT ????
	Envelope *recievelist; 		//list of envelopes recieved
	int jbContext; 				//used by setjump and longjump, not sure if returntype=int. ?????????????
}NewPCB;

//****MESSAGE ENVELOPE QUEUE****
typedef struct msg_env_Q{
	Evelope *head;
	Envelope *tail;
}msg_env_Q;

//****PROCESS QUEUE****
typedef struct Process_Q{
	NewPCB *Head;
	NewPCB *Tail;
}Proc_Q;



//timeout queue











#endif /* RTX_H_ */
