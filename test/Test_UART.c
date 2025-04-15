/*
 * default Test UART
 * Created: 2023/03/27
 * Author: taivb
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
