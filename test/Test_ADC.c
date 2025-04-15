/*
 * test ADC
 * Created: 2023/03/30
 * Author: Van_BasTai
 */

#include <include.h>
#include <N76_uart0.h>

uint16_t value;

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

ISR(ADC_INT_FUCTION, INTERRUPT_ADC)
{
    value = (ADCRH << 4) | ADCRL;
    clr_ADCF; // clear ADC interrupt flag
}
