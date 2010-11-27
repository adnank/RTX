/*
 * userProcesses.c
 *
 *  Created on: Nov 22, 2010
 *      Author: Owner
 */

/*Process_A()
{
		Envelope* A = receive_message();//receive a message // sent by CCI in response to a “s” from the keyboard
		int B = release_msg_envelope(A);//deallocate the received message envelope
		num <- 0
		loop forever
			get a message envelope
			set the message_type field to “count_report”
			set the msg_data[1] field to num
			send the envelope to process B
			num<- num + 1
		release_processor
		endloop */

void ProcessA()
{
	Envelope* A = receive_message();
	int B = release_msg_envelope(A);
	Msg_Env *message;
	static int num = 0;
	do
	{
		message = request_msg_env();
		message->set_type(num);
		send(B_PID,message);
		num++;
		return_to_dispatcher();
	}
	while (1);
}

/*Process B:
	loop forever
		receive a message
		send the message to process C
	endloop*/
void ProcessB()
{
	Msg_Env *message;
	do
	{
		message = receive();
		send(C_PID,message);
	}
	while(1);
}
/*
Process C:
		perform any needed initialization
		loop forever
			if (local message queue is empty)
					then receive a message
					else dequeue the first message from the local message queue
			if msg_type == “count_report”
			then if msg_data[1] is evenly divisible by 20
				then send "Process C" to display using msg envelope
						wait for display_ack
						go_passive for 10 seconds
				endif
			endif
			deallocate message envelope
			release_processor
		endloop
		//The line "go_passive for 10 seconds" may be further expanded as:
		//request a 10 second delay with wakeup_code set to “wakeup10”
		loop
			receive a message //block and let other processes execute
			if (message_type == “wakeup10”)
			then exit this loop
			else put message on the local message queue for later processing
			endloop
			// Examples of user processes A, B and C
			// Not complete, but give basic idea

			// Msg_Env is a class.  For example:
			class Msg_Env {
				private:
					int type;
				public:
					char data[MSG_ENV_DATA_SIZE];
					Msg_Env();  // constructor
					void set_type(int msg_type) {type = msg_type;};
					int get_type() {return(type);};
				};*/
void ProcessC()
{
	Msg_Env *message;
	do
	{
	// check for message on local queue first
		message = local_dequeue();
		if (message == NULL)
			message = receive();
		if ((message->get_type()) % 20 == 0)
			{
				strcpy(message->data,"Process C\n");
				message->set_type(MSG);
				send_console_characters(message);
				message = receive();
					while( message->get_type() != MSG )
						{
							local_enqueue(message);  // save message on the local queue
							message = receive();
						}
					request_delay(1000, WAKEUP, message); // 1000 = 10 seconds
					message = receive();
						while( message->get_type() != WAKEUP)
							{
								local_enqueue(message);  // save message on the local queue
								message = receive();
							}
			}
		release_msg_env(message);
		return_to_dispatcher();
	}
	while(1);
}











