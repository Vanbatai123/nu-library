/**
 * @file Test_GPIO.c
 * @author Van_BasTai (taivb.6dof@gmail.com)
 * @brief Test GPIO/UART function
 * @version 0.1
 * @date 2025-04-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <include.h>
#include <N76_uart0.h>

int a = 0;

/**
 * @brief Main function
 * 
 */
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