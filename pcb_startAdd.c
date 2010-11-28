/*
 * pcb_startAdd.c
 *
 *  Created on: 2010-11-28
 *      Author: adnan
 */

#include <rtx.h>

void add_procA()
{
    while(1)
    {
		printf("I am Process A\n");
		sleep(1);
		release_processor();
    }
}

void add_procB()
{
    while(1)
    {
		printf("I am Process B\n");
		sleep(1);
		release_processor();
    }
}

void add_procC()
{
    while(1)
    {
		printf("I am Process C\n");
		sleep(1);
		release_processor();
    }
}

void add_pNull()
{
    while(1)
    {
		printf("NULL Process Here!\n");
		sleep(1);
		release_processor();
    }
}

void add_ptst1()
{
    while(1)
    {
		printf("I am test process 1\n");
		sleep(1);
		release_processor();
    }
}

void add_ptst2()
{
    while(1)
    {
		printf("I am test process 2\n");
		sleep(1);
		release_processor();
    }
}

void add_ptst3()
{
    while(1)
    {
		printf("I am test process 3\n");
		sleep(1);
		release_processor();
    }
}

void add_ptst4()
{
    while(1)
    {
		printf("I am test process 4\n");
		sleep(1);
		release_processor();
    }
}

void add_ptst5()
{
    while(1)
    {
		printf("I am test process 5\n");
		sleep(1);
		release_processor();
    }
}

void add_ptst6()
{
    while(1)
    {
		printf("I am test process 6\n");
		sleep(1);
		release_processor();
    }
}

void add_PRTY()
{
    while(1)
    {
		printf("process priority\n");
		sleep(1);
		release_processor();
    }
}

void add_KBD()
{
    while(1)
    {
		printf("I am KBD process\n");
		sleep(1);
		release_processor();
    }
}

void add_CRT()
{
    while(1)
    {
		printf("I am CRT process\n");
		sleep(1);
		release_processor();
    }
}

void add_TIMER()
{
    while(1)
    {
		printf("I am the TIMER\n");
		sleep(1);
		release_processor();
    }
}

void add_CCI()
{
    while(1)
    {
		printf("CCI here!\n");
		sleep(1);
		release_processor();
    }
}

void add_CLK()
{
    while(1)
    {
		printf("process CLK\n");
		sleep(1);
		release_processor();
    }
}



