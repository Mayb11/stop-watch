/*
 * stopwatch.c
 *
 *  Created on: 2021Äê3ÔÂ17ÈÕ
 *      Author: haozhe
 */

#include "stopwatch.h"

//Add the base addresses of the seven segment display peripherals.
volatile unsigned char *sevenseg_base_lo_ptr=(unsigned char *)0xFF200020;
volatile unsigned char *sevenseg_base_hi_ptr=(unsigned char *)0xFF200030;


//There are four HEX displays attached to the low (first) address.
#define SEVENSEG_N_DISPLAYS_LO 4
#define SEVENSEG_N_DISPLAYS_HI 2

//There are two HEX displays attached to the high (second) address.
void counter_wirte (unsigned int display, unsigned char current_time)
{
	// Select between the two addresses so that the higher level functions
    // have a seamless interface.
	if (display < SEVENSEG_N_DISPLAYS_LO)
	{
		// If we are targeting a low address, use byte addressing to access
	    // directly.
		sevenseg_base_lo_ptr[display] = current_time;
	}
	else
	{
		// If we are targeting a high address, shift down so byte addressing
		// works.
		display = display - SEVENSEG_N_DISPLAYS_LO;
		sevenseg_base_hi_ptr[display] = current_time;
	}
}

void first_show(unsigned int display, unsigned int current_time)
{
		//This is the display function of a single-column display.
	    //Depending on the entered value, different numbers are displayed.
		if (current_time==0){
			counter_wirte(display,0x3F);// light segment 0,1,2,3,4,5
		}
		if (current_time==1){
			counter_wirte(display,0x06);//  light segment 1,2
		}
		if (current_time==2){
			counter_wirte(display,0x5B);// light segment 0,1,3,4,6
		}
		if (current_time==3){
			counter_wirte(display,0x4F);// light segment 0,1,2,3,6
		}
		if (current_time==4){
			counter_wirte(display,0x66);// light segment 1,2,5,6
		}
		if (current_time==5){
			counter_wirte(display,0x6D);// light segment 0,2,3,5,6
		}
		if (current_time==6){
			counter_wirte(display,0x7D);// light segment 0,2,3,4,5,6
		}
		if (current_time==7){
			counter_wirte(display,0x07);//light segment 0,1,2
		}
		if (current_time==8){
			counter_wirte(display,0x7F);// light all segment
		}
		if (current_time==9){
			counter_wirte(display,0x67);// light segment 0,1,2,5,6
		}

}

void multi_show(unsigned int display, unsigned int current_time)
{
	//This is a theme display function that integrates a single-column display function.
	//The data is displayed by calling different numbers of displays in different intervals through the input value.
	if  (0 <= current_time &&  current_time <= 99)
	{
		unsigned int current_timE=current_time;
		unsigned int current_timE_1=current_timE%10;// take the first bit of the input number
		unsigned int current_timE_2=current_timE/10;// take the second bit of the input number

		first_show(display, current_timE_1);// light the first bit number
		first_show(display+1, current_timE_2);// light the 2nd bit number
		first_show(display+2,0);// unused display
		first_show(display+3,0);// unused display
		first_show(display+4,0);// unused display
		first_show(display+5,0);// unused display
	}
	else if (100 <= current_time && current_time <= 5999)
	{
		unsigned int current_tiMe=current_time;
		unsigned int current_tiMe_1=(current_tiMe%100)%10;// take the first bit of the input number
		unsigned int current_tiMe_2=(current_tiMe%100)/10;// take the 2nd bit of the input number
		unsigned int current_tiMe_3=(current_tiMe/100)%10;// take the 3rd bit of the input number
		unsigned int current_tiMe_4=(current_tiMe/100)/10;// take the 4th bit of the input number

		first_show(display,current_tiMe_1);// light the first bit number
		first_show(display+1,current_tiMe_2);// light the 2nd bit number
		first_show(display+2,current_tiMe_3);// light the 3rd bit number
		first_show(display+3,current_tiMe_4);// light the 4th bit number
		first_show(display+4,0);// unused display
		first_show(display+5,0);// unused display

	}
	else if (6000 <= current_time && current_time <= 359999)
	{
		unsigned int current_tIme=current_time;
		unsigned int current_tIme_1=(current_tIme%100)%10;// take the first bit of the input number
		unsigned int current_tIme_2=(current_tIme%100)/10;// take the 2nd bit of the input number
		unsigned int current_tIme_3=((current_tIme/100)%60)%10;// take the 3rd bit of the input number
		unsigned int current_tIme_4=((current_tIme/100)%60)/10;// take the 4th bit of the input number
		unsigned int current_tIme_5=((current_tIme/100)/60)%10;// take the 5th bit of the input number
		unsigned int current_tIme_6=((current_tIme/100)/60)/10;// take the 6th bit of the input number

		first_show(display,current_tIme_1);// light the first bit number
		first_show(display+1,current_tIme_2);// light the 2nd bit number
		first_show(display+2,current_tIme_3);// light the 3rd bit number
		first_show(display+3,current_tIme_4);// light the 4th bit number
		first_show(display+4,current_tIme_5);// light the 5th bit number
		first_show(display+5,current_tIme_6);// light the 6th bit number
	}

	else if (360000 <= current_time && current_time <= 35999999 )
	{
		unsigned int current_Time=current_time/100;
		unsigned int current_Time_1=(current_Time%60)%10;// take the first bit of the input number(current_Time)
		unsigned int current_Time_2=(current_Time%60)/10;// take the 2nd bit of the input number(current_Time)
		unsigned int current_Time_3=((current_Time/60)%60)%10;// take the 3rd bit of the input number(current_Time)
		unsigned int current_Time_4=((current_Time/60)%60)/10;// take the 4th bit of the input number(current_Time)
		unsigned int current_Time_5=((current_Time/60)/60)%10;// take the 5th bit of the input number(current_Time)
		unsigned int current_Time_6=((current_Time/60)/60)/10;// take the 6th bit of the input number(current_Time)

		first_show(display,current_Time_1);// light the first bit number (current_Time)
		first_show(display+1,current_Time_2);// light the 2nd bit number(current_Time)
		first_show(display+2,current_Time_3);// light the 3rd bit number(current_Time)
		first_show(display+3,current_Time_4);// light the 4th bit number(current_Time)
		first_show(display+4,current_Time_5);// light the 5th bit number(current_Time)
		first_show(display+5,current_Time_6);// light the 6th bit number(current_Time)

	}
}
void start_show(unsigned int display)
{
	first_show(display,0x0000000);// light the first bit number (current_Time)
	first_show(display+1,0x1101110);// light the 2nd bit number(current_Time)
	first_show(display+2,0x0011110);// light the 3rd bit number(current_Time)
	first_show(display+3,0x1110111);// light the 4th bit number(current_Time)
	first_show(display+4,0x1111001);// light the 5th bit number(current_Time)
	first_show(display+5,0x1110111);// light the 6th bit number(current_Time)
}
