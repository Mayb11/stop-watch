/*
 * main.c

 *
 *  Created on: 2021Äê3ÔÂ18ÈÕ
 *      Author: haozhe
 */
// Include drivers.
#include "stopwatch/stopwatch.h"
#include "HPS_Watchdog/HPS_Watchdog.h"
// Select which displays to use.
#define DISPLAY 0

// Peripheral base addresses.
volatile unsigned int *key_ptr = (unsigned int *)0xFF200050;

volatile unsigned int *private_timer_load	   = (unsigned int *) 0xFFFEC600;
volatile unsigned int *private_timer_value	   = (unsigned int *) 0xFFFEC604;
volatile unsigned int *private_timer_control   = (unsigned int *) 0xFFFEC608;
volatile unsigned int *private_timer_interrupt = (unsigned int *) 0xFFFEC60C;

// Store the state of the keys last time we checked.
unsigned int key_last_value = 0;

unsigned int press_key() {

    // Store the current state of the keys.
    unsigned int key_current_value = *key_ptr;
    // If the key was down last cycle, and is up now, mark as pressed.
    unsigned int keys = (~key_current_value) & (key_last_value);
    // Save the key state for next time, so we can compare the next state to this.
    key_last_value = key_current_value;
    // Return result.
    return keys;
}


int main(void)
{
	volatile unsigned int *private_timer_load	   = (unsigned int *) 0xFFFEC600;
	//volatile unsigned int *private_timer_value	   = (unsigned int *) 0xFFFEC604;
	volatile unsigned int *private_timer_control   = (unsigned int *) 0xFFFEC608;
	volatile unsigned int *private_timer_interrupt = (unsigned int *) 0xFFFEC60C;

	unsigned int keys = 0;
	unsigned int counter = 0;
	unsigned int counter_s = 0;
	unsigned int load_value = 2250000;
	unsigned int mode = 0;

	//unsigned int value = 0;
	//unsigned int control_value = (0<<8)|(0<<2)|(1<<1)|(0<<0);
	//unsigned int interrupt_value = 0;
	// initial value of private_timer_load address of 2250000
	*private_timer_load	= load_value;
	// set initial value of private_timer_control,bit E>0,bit A>1,bit I>o,bit prescale>0
	*private_timer_control = (0<<8)|(0<<2)|(1<<1)|(0<<0);
	//initial showing function
	multi_show(DISPLAY,counter);
	//start_show(DISPLAY);
	while (1)
	{
		if (mode == 0)
		{
		// Corresponding value set to 1 when a key is pressed then released.
			keys = press_key();

		// show every times pointer changes
			multi_show(DISPLAY,counter);
		//if the F bit of private_timer_interrupt set to high, reset the F bit value and counter plus 1
			if (*private_timer_interrupt & 0x1)
			{
				*private_timer_interrupt = 0x1;
				counter ++;
			}
		// if key0 was pressed, enable the timer,start stopwatch
			else if (keys & 0x1)
			{
				*private_timer_control = (0<<8)|(0<<2)|(1<<1)|(1<<0);
			//third_show(DISPLAY,5678);

			}
		// if key1 was pressed, unable the timer, stop the stopwatch
			else if (keys & 0x2)
			{

				*private_timer_control = (0<<8)|(0<<2)|(1<<1)|(0<<0);
			}
		// if key2 was pressed, unable the timer and initial the value of counter,all back to the begining
			else if (keys & 0x4)
			{
			//counter = 0;
				*private_timer_control = (0<<8)|(0<<2)|(1<<1)|(0<<0);
				counter = 0;
			}

			else if (keys & 0x8)
				{
				//*private_timer_control = (0<<8)|(0<<2)|(1<<1)|(0<<0);
				mode = 1;
				*private_timer_control = (0<<8)|(0<<2)|(1<<1)|(0<<0);
				counter = 0;
				counter_s = 0;
				//start_show(DISPLAY);

				}
			HPS_ResetWatchdog();
		}
		else if (mode == 1)
		{
			// Corresponding value set to 1 when a key is pressed then released.
			keys = press_key();

			// show every times pointer changes
			//multi_show(DISPLAY,counter);
			//start_show();
			if (*private_timer_interrupt & 0x1)
			{
				*private_timer_interrupt = 0x1;
				counter_s ++;
			}
			else if (keys & 0x1)
			{
				*private_timer_control = (0<<8)|(0<<2)|(1<<1)|(1<<0);
			}
			else if (keys & 0x2)
			{
				multi_show(DISPLAY,counter_s);
			}
			else if (keys & 0x4)
			{
				*private_timer_control = (0<<8)|(0<<2)|(1<<1)|(0<<0);
				counter_s = 0;
				multi_show(DISPLAY,0);// show the current time
			}
			else if (keys & 0x8)
			{
			//*private_timer_control = (0<<8)|(0<<2)|(1<<1)|(0<<0);
				mode = 0;
				*private_timer_control = (0<<8)|(0<<2)|(1<<1)|(0<<0);
				counter = 0;
				counter_s = 0;
				//start_show(DISPLAY);
			}
			HPS_ResetWatchdog();
		}
		HPS_ResetWatchdog();
	}


}
