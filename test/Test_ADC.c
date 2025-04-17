/**
 * @file Test_ADC.c
 * @author Van_BasTai (taivb.6dof@gmail.com)
 * @brief Test ADC function of Nuvoton N76/MS51
 * @version 0.1
 * @date 2025-04-17
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <include.h>
#include <N76_uart0.h>

uint16_t value;

/**
 * @brief Main function
 *
 */
void main(void)
{
    // P11_Input_Mode;
    Enable_ADC_AIN7;
    // Enable_ADC_Interrupt; // uncomment when using interrupt

    UART0_begin(BAUD_115200);
    sei(); // Enable global interrupt

    while (1)
    {
        // convert ADC manual
        clr_ADCF;
        set_ADCS; // ADC start trig signal
        // clrb(ADCCON0, ADCF); // clear ADC interrupt flag
        // setb(ADCCON0, ADCS); // start ADC convertion
        while (ADCF == 0)
            ;
        value = (ADCRH << 4) | ADCRL;
        _delay_ms(500);
        UART0_printNum(value, DEC);
        UART0_print("\r\n");
    }
    while (0)
    {
        // convert ADC using interrupt
        set_ADCS; // start ADC convertion
        _delay_ms(500);
        UART0_printNum(value, DEC);
        UART0_print("\r\n");
    }
}

/**
 * @brief ADC interrupt function
 *
 */
ISR(ADC_INT_FUCTION, INTERRUPT_ADC)
{
    value = (ADCRH << 4) | ADCRL;
    clr_ADCF; // clear ADC interrupt flag
}
