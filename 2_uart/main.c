#include "uart.h"
#include "gpio.h"

int main(){

    uart_init();
	int sleep = 0;

    for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[BUTTON_A_PIN] = 0;
	GPIO->PIN_CNF[BUTTON_B_PIN] = 0;



	while(1){

		/* Check if button B is pressed;
		 * turn on LED matrix if it is. */

		if (!(GPIO->IN & (1 << BUTTON_B_PIN))){
			GPIO->OUT |= (1 << 13) | (1 << 14) | (1 << 15);
            uart_send('b');
		}


		/* Check if button A is pressed;
		 * turn off LED matrix if it is. */
		if (!(GPIO->IN & (1 << BUTTON_A_PIN))){
			GPIO->OUTCLR |=  (1 << 13) | (1 << 14) | (1 << 15);
            uart_send('a');

		}


		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
