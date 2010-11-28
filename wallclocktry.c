/*
 * wallclocktry.c
 *
 *  Created on: 2010-11-28
 *      Author: abubakar
 */


#include "rtx.h"

//THINGS TO DO
//===================================================================
//need to initialize the clock when the rtx starts
//need to initialize the values hh,mm,ss
//need to initialize the sigalarm to occur every 100ms using ualarm

/*
void time_intialize()
{
	int hh, mm, ss;
	ss = 0;
	mm = 0;
	hh = 0;
	while (hh <= 22)
	{
		while (mm <= 58)
			{
				while (ss <= 58)
					{
						usleep(1000000);
						ss++;
						printf("%d : %d : %d\n",hh,mm,ss);
					}
				ss=0;
				usleep(1000000);
				mm++;
				printf("%d : %d : %d\n",hh,mm,ss);
			}
		mm=0;
		ss=0;
		usleep(1000000);
		hh++;
		printf("%d : %d : %d\n",hh,mm,ss);
	}
}
*/
void time_initialize(){
	ss=00;
	mm=00;
	hh=00;
	printf("%d:%d:%d\n",hh,mm,ss);
}
void time_increment(){
	ss++;
	if (ss==60){
		ss=0;
		mm++;
		if(mm==60){
			mm=0;
			hh++;
			if(hh==24){
				hh=0;
			}
		}
	}
	printf("%d : %d : %d\n",hh,mm,ss);
}

void time_change(hh,mm,ss){
	printf("Time has been changed to %d : %d : %d\n",hh,mm,ss);
}
