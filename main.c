#include "tm4c123gh6pm.h"
#include <stdint.h>

void UART0Tx (uint8_t c);
void delayMs (uint32_t n);

int main(void)
{
    SYSCTL_RCGCUART_R |= 1; // provide clock for UART0;
    SYSCTL_RCGC2_R |= 1; // enable clock to port A

    UART0_CTL_R = 0; // disable UART0
    UART0_IBRD_R = 104; // integer divisor baud rate, for 16 MHz and 9600 baud rate
    UART0_FBRD_R = 11; // fraction part
    UART0_CC_R = 0; // use the system clock for UART0
    UART0_LCRH_R = 0x60; // 8bit, no parity, 1stop bit, no FIFO
    UART0_CTL_R = 0x301; // enable UART0. TXE, RXE

    GPIO_PORTA_DEN_R = 0x03; // Make PA0 and PA1 as digital
    GPIO_PORTA_AFSEL_R = 0x03; // Use PA0, PA1 alternate function
    GPIO_PORTA_PCTL_R = 0x11; // Configure PA0 and PA1 for UART

    delayMs(1);

    for(;;)
    {
        UART0Tx('H');
        UART0Tx('E');
        UART0Tx('L');
        UART0Tx('L');
        UART0Tx('O');

        UART0Tx(' ');
    }
	return 0;
}

void UART0Tx (uint8_t character)
{
    while((UART0_FR_R & 0x20) != 0);
    UART0_DR_R = character;
}

void delayMs (uint32_t n)
{
    uint32_t i, j;
    for(i=0; i<n ; i++)
    {
        for(j=0; j<3180 ; j++)
        {

        }
    }
}
