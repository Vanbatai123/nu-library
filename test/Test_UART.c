/**
 * @file Test_UART.c
 * @author Van_BasTai (taivb.6dof@gmail.com)
 * @brief Test UART read/write function
 * @version 0.1
 * @date 2025-04-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <include.h>
#include <N76_uart0.h>

void main(void)
{
    UART0_begin(BAUD_9600);
    UART0_attachInterrupt();
    UART0_println("START\r\n");
    sei();
    while (1)
    {
        // UART0_printNumln(123, DEC);
        if (UART0_available())
        {
            UART0_putChar(UART0_read());
            UART0_putChar('\r\n');
            _delay_ms(10);
        }
        _delay_ms(100);
    }
}
