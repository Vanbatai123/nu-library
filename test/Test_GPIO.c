/*
 * default main file
 * Created: 2023/03/26
 * Author: taivb
 */

#include <include.h>
#include <N76_uart0.h>

int a = 0;

void main(void)
{
    setb(P1, 6);
    P16_Input_Mode;
    P02_Input_Mode;
    UART0_begin(BAUD_115200);
    // pinMode(LED_PORT, LED_PIN, OUTPUT_PP);
    // pinMode(BTN_PORT, BTN_PIN, INPUT);
    while (1)
    {
        if (inbit(P1, 6) == 0)
        {
            UART0_printNumln(16, DEC);
        }
        if (inbit(P0, 2) == 0)
        {
            UART0_printNumln(2, DEC);
        }
        _delay_ms(10);
    }
}