interrupt_handler();
{
	save current_process context;
	current_process->status = blocked_on_interrupt;
	select interrupt source;
	switch(signal);

	{
	A: i_process_timer;
	current_process = i_process_timer;
	i_process_timer state is set as executing;
	restore i_process_timer context;
	invoke i_process_timer handler;
	break;

	B: i_process_crt;
	current_process = i_process_crt;
	i_process_crt state is set as executing;
	restore i_process_crt context;
	invoke i_process_crt handler;
	break;

	C: i_process_kb;
	current_process = i_process_kb;
	i_process_kb state is set as executing;
	restore i_process_kb context;
	invoke i_process_kb handler;
	break;
	}

	D: i_process_terminate;
save context of interrupt handler
current_process = save_PCB
save_PCB = NULL
set state of current_process to executing
restore current_process context
}

i_process_timer:
	{
		msg_env *timeout_request
		int temp_sender_pid
		timeout_request = receive_message()
		while (timeout_request != NULL)
		{
			sort msg_env into the timeout_list;
			timeout_request = receive_message();
		}
		if (timeout_list is not empty)
		{
			decrement tick count of first msg_env in the timeout_list
			timeout_request = head_of_timeout_list
			while(timeout_request[tick_field] is zero)
				{
				msg_env *temp
				timeout_request = dequeue(timeout_list)
				timeout_request->receiver_pid=timeout_request->
				sender_pid
				timeout_request->sender_pid->timeout_i_process_pid;
				temp = timeout_request;
				dequeue message envelope from timeout_list
				return envelope to requesting process
		increment timeout_request to point to next message envelope
		send_message(temp->dest_process_id,temp)
				}
		}
}

iprocess_crt: { MessageEnv* disp = message_receive();
Message is loaded into the TX memory Set status bit to 1 //something is there to be displayed Call appropriate Unix CRT function to read shared memory send message envelope back to the invoking process }
}
iprocess_kb: { if (recieves a message from get_console_chars) Store the string of characters from the kb buffer into msg_env Set msg_env message subject field to console_input send message envelope to invoking process else CCI_process() }
