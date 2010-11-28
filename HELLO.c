/*
 * HELLO.c
 *
 *  Created on: 2010-11-28
 *      Author: abubakar
 */

#include <stdlib.h>

#include "rtx.h"

//#include "rtx_iproc.c"

int main(){

	sigset(SIGINT, interrupt_handler);
	sigset(SIGUSR1, interrupt_handler);
	sigset(SIGUSR2, interrupt_handler);
	sigset(SIGALRM,interrupt_handler);
	ualarm(100000,100000);


//	int variablesignal=SIGALRM;
//	interrupt_handler(variablesignal);
//	time_initialize();
//	printf("%d%d%\n");
//	time_increment();
//	CCI_process();

	printf("FUCK THIS\n");
	return 0;
}
