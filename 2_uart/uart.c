#include "uart.h"
#include "gpio.h"



void uart_init(){

    /* Configure UART-pins as input or output 
        0 - input
        1 - output
    */ 

    /* Configure TXD pin as output pin */
    GPIO->DIR |= (1 << TGT_TXD_PIN);

    /* Configure RXD pin as input pin
     */
    GPIO->DIR &= ~(1 << TGT_RXD_PIN);

    /* Configure txd and rxd pin for uart module */
    UART->PSELTXD = TGT_TXD_PIN;
    UART->PSELRXD = TGT_RXD_PIN;

    /* Set baudrate 9600 */
    UART->BAUDRATE = 0x00275000;

    /* Disable CTS and RTS */
    UART->PSELRTS = 0xffffffff;
    UART->PSELCTS = 0xffffffff;

    /* Enable UART */
    UART->ENABLE = 4;
    
    /* Start UART Receiver */
    UART->STARTRX = 1;
}

void uart_send(char letter){
   
    UART->STARTTX = 1;  // Trigger STARTTX Task 

    UART->TXD = letter; // Write byte to be transmitted to TXD register
    while(!(UART->TXDRDY)){
        // wait
    }

    UART->TXDRDY = 0; //Set interrupt register low again
    UART->STOPTX = 1; // Trigger STOPTX task to stop UART Transmission


}