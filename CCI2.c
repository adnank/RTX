/*
 * CCI2.c
 *
 *  Created on: 2010-11-28
 *      Author: abubakar
 */

/*
#include "rtx.h"

void CCI_process ()
{
	Envelope * temp = K_recieve_message ();
	//Envelope * temp = K_request_msg_env();
	int A = K_get_console_chars (temp);
	char tempstring[256] =  temp->Data[MSG_DATA];
	char x;
	int y;
	double z;
	fscanf(tempstring, "%2s %i %4d", x, y, z);
		 //store the context field of message_envelope into a temperory string
		 //variable
	if(x =='s')
		CCI_s();
	if(x == 'ps')
		CCI_ps();
	if(x == 'b')
		CCI_b();
	if(x == 't')//if(fscanf(tempstring, "t") == 0)
		CCI_t();
	if(x == 'n')//if(fscanf(tempstring, "%s %i %d", s, i, d)
		CCI_n(y,z);
	if(x == 'c')//if(fscanf(tempstring, "c") == 0)
		CCI_c();
	if(x == 'cd')//if(fscanf(tempstring, "cd") == 0)
		CCI_cd();
	if(x == 'ct')//if(fscanf(tempstring, "ct") == 0)
		CCI_ct();
	else	printf("Wrong command input\n");

		 //compare the string from the temperory string variable with the
		 //characters of the CCI functions (using strcmp function)
	//call the appropriate CCI function depending on the comparison and pass
	//the appropriate paramters to the function
}


//CCI sends message envelope to user process A. This causes the user demonstration process to
//begin execution since user Process A is blocked_on_receiveat start up
//CCI: s <cr>
void CCI_s()
{
	Envelope * empty_env = K_request_msg_env (); //Envelope * get an empty message envelope by
			//calling the function
	int B = K_send_message (0001, empty_env);
	//int B= message_send (process_id for process A, empty_env)current_process->ProcID
	if(B == 1)
		printf("message was sent\n");
	else
		printf("message was not sent due to Process A pointing to NULL\n");
}


//Displays the status, priority and process id of all known processes in a tabular form
//CCI: ps <cr>
void CCI_ps()
{
	//MsgEnv* data = request_msg_env //get an empty envelope
	Envelope * data = K_request_msg_env ();
	int A = K_request_process_status (data);
	//int A = request_process_status (data)
	if(A == 1)
		printf("SUCCESS\n");//SUCCESS
	else
		printf("ERROR\n");//ERROR


	//call the CRT i-process for the printing of the text field of the data
	printf("%s\n",data->Data);
}





//Displays the current contents of the send and receive trace buffers
//CCI:b <cr>
void CCI_b()
{
	//isplay the contents of send_trace_array and the recieve_trace_array
	//using the CRT i-process
}


//Terminates all processes and stops execution of the RTX
//CCI:t <cr>
void CCI_t()
{
	//int A=terminate()
	//deallocate A
}


//Changes the proiority of the specified process to new_priority
//CCI: n new_priority process_id <cr>
void CCI_n(y,z)
{

	int A = K_change_priority (y, z);
	//int A = change_priority (new_priority, process_id)
	if(A == 1)
		printf("PRIORITY SUCCESFULLY CHANGED\n");//print in console window: PRIORITY SUCCESFULLY CHANGED
	else
		printf("ERROR, PRIORITY CANNOT BE CHANGED\n");//print in the console window: ERROR, PRIORITY CANNOT BE CHANGED
}


//Sets the CCI wall clock to the hours, minutes and seconds specified using 24 hour format
//(hh:mm:ss)
//CCI: c hh:mm:ss <cr>
void CCI_c()
{
	printf( "Enter your the hour, minute and second value.\n" );
	scanf( "%d %d %d", &hh, &mm, &ss );
	//separate the string  inputed by the user into 3 different sets of
	//integer variables(e.g. hh, mm, ss)
	if((hh>23) || (hh<0))
		printf( "Not a valid Hour(s) Input\n" );//return error;
	if((mm>59) || (mm<0))
		printf( "Not a valid Minute(s) Input\n" );//return error;
	if((ss>59) || (ss<0))
		printf( "Not a valid Second(s) Input\n" );//return error;
    	else
		//time1(hh,mm,ss);
    	time_change(hh,mm,ss);
    	//set the wall clock value by placing the original string value
    	//inputted by the user in the TX shared memory and update using
    			//ualarm() for 1 second interval
}


//Allows the display of the wall clock on system console
//CCI: cd <cr>
void CCI_cd()
{
	Display_WALLCLOCK=1;
	HIDE_WALLCLOCK=0;

//     display the wall clock (still being updated every second)
}



//Stops the display of the wall clock on system console
//CCI: ct <cr>
void CCI_ct()
{
	HIDE_WALLCLOCK=1;
	Display_WALLCLOCK=0;
}
*/
