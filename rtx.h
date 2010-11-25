/*will include all structs, globally defined variables, function definitions*/
#ifndef RTX_H_
#define RTX_H_

#define NUM_OF_ENVELOPES 50
#define NUM_OF_PROC 3

typedef void (*start_address)(void);	//occurence of proc_address

									//****PROCESS RECORD****
typedef struct proc_record{
	int process_id;
	int priority;
	int stack_size;
	int proc_status;
	start_address proc_address;			//start address of the process code
}proc_record;
proc_record *init_table[NUM_OF_PROC];
									//****MESSAGE ENVELOPE****
typedef struct Envelope{
	struct Envelope *kernelpt; 	//used for creating the list of envelopes
	struct Envelope *Next; 		// used to put the queue in different lists
	int SenderID; 			// who sent the message
	int DestinationID; 		//where the message will be sent
	int clockticks; 		// for waking,sleeping and ualarm functions
	int Msg_Type[50];		//type of message
							/* wakeup_code =1
							 * display_acknowledgement =2
							 * console_input=3
							 */
	char Data [256]; //pointer to an array of characters
}Envelope;

								//****PROCESS CONTROL BLOCK****

typedef struct NEWPCB {
	struct NEWPcb * Kernel_ptr;
	int State; 					//for the state of the process
								/* Ready=1
								 * Blocked on Envelope =2  blocked due to lack of free envelopes
								 * Blocked on Resources =3 blocked due to lack in receieved messages
								 * Executing =4
								 * Interupted =5
								 */
	int ProcID; 				//process id of the process
	struct NewPcb *Next; 				//pointer to put the PCB in the lists it is supposed to be in
	int Priority; 				//priority of the process
	struct NEWPCB *kernelpt; 			//allows kernel to keep a list of all the processes
	Envelope *head; 			//head for the list of the envelopes that the process owns
	Envelope *tail; 			//tail for the list of the envelopes that the process owns //FOR WHAT ????
	Envelope *recievelist; 		//list of envelopes recieved
	int jbContext; 				//used by setjump and longjump, not sure if returntype=int. ?????????????
}NewPCB;

//****FREE MESSAGE ENVELOPE QUEUE****
typedef struct free_env_Q{

}free_env_Q;

//timeout queue











#endif /* RTX_H_ */
