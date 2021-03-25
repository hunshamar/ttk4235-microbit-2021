#include <stdint.h>

#define GPIO_BASE_ADDRESS 0x50000000

#define GPIO ((NRF_GPIO_REGS*)GPIO_BASE_ADDRESS)

#define BUTTON_A_PIN 17
#define BUTTON_B_PIN 26

/*
	Knapp A: koblet til PO.17 - aktiv lav (trykket ned, går til jord)
	Knapp B: Koblet til PO.26 - ---||--

	GPIO -> 0x50000000

	Mellom DIRCLR og PIN_CNF -> 0x700_(16) - 0x520_(16) 
	=> 1792 - 1312 = 480 bytes
	480 / 4 = 120

*/


typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t RESERVED1[120];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[BUTTON_A_PIN] = 0;
	GPIO->PIN_CNF[BUTTON_B_PIN] = 0;

	int sleep = 0;
	while(1){

		/* Check if button B is pressed;
		 * turn on LED matrix if it is. */

		if (!(GPIO->IN & (1 << BUTTON_B_PIN))){
			GPIO->OUT |= (1 << 13) | (1 << 14) | (1 << 15);

		}


		/* Check if button A is pressed;
		 * turn off LED matrix if it is. */
		if (!(GPIO->IN & (1 << BUTTON_A_PIN))){
			GPIO->OUTCLR |=  (1 << 13) | (1 << 14) | (1 << 15);

		}



		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
