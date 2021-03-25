


#ifndef UART_H
#define UART_H

#include <stdint.h>

#define TGT_RXD_PIN 25
#define TGT_TXD_PIN 24

#define UART_BASE_ADDRESS 0x40002000 // table 274 i datablad

#define UART ((NRF_UART_REG*)UART_BASE_ADDRESS)

typedef struct {
    /*Tasks*/
    volatile uint32_t STARTRX; //Start UART reciever
    volatile uint32_t STOPRX; //Stop UART reciever
    volatile uint32_t STARTTX; //Start UART transmitter
    volatile uint32_t STOPTX; //Stop UART transmitter
    volatile uint32_t RESERVED[3]; 
    volatile uint32_t SUSPEND; //Suspend UART 
    volatile uint32_t RESERVED1[56];
    /*Events*/
    volatile uint32_t CTS; //CTS is activated (set low). Clear to send
    volatile uint32_t NCTS; //CTS is deactivated (set high). Not clear to send
    volatile uint32_t RXDRDY; //Data recieved in RXD
    volatile uint32_t RESERVED2[4];
    volatile uint32_t TXDRDY; //Data sendt from TXD
    volatile uint32_t RESERVED3[1];
    volatile uint32_t ERROR; //Error detected
    volatile uint32_t RESERVED4[7];
    volatile uint32_t RXTO; //Reciever timeout
    volatile uint32_t RESERVED5[110];
    /*Registers*/
    volatile uint32_t INTEN; //Enable or disable interrupt
    volatile uint32_t INTENSET; //Enable interrupt
    volatile uint32_t INTENCLR; //Disable interrupt
    volatile uint32_t RESERVED6[93];  
    volatile uint32_t ERRORSCR; //Error source
    volatile uint32_t RESERVED7[31];
    volatile uint32_t ENABLE; //Enable UART 
    volatile uint32_t RESERVED8[1];
    volatile uint32_t PSELRTS; //Pin select for RTS
    volatile uint32_t PSELTXD; //Pin select for TXD
    volatile uint32_t PSELCTS; //Pin select for CTS    
    volatile uint32_t PSELRXD; //Pin select for RXD
    volatile uint32_t RXD; //RXD register
    volatile uint32_t TXD; //TXD register
    volatile uint32_t RESERVED9[1];
    volatile uint32_t BAUDRATE; //Baud rate
    volatile uint32_t RESERVED10[17];
    volatile uint32_t CONFIG; //Configuration of parity and hardware flow control
} NRF_UART_REG;

void uart_init();
void uart_send(char letter);
char uart_read();



#endif