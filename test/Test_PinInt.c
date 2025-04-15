/*
 * test Pin interrupt
 * Created: 2021/10/23
 * Author: taivb
 */

#include <include.h>
// #include <N76_PinInt.h>

#define LED_PIN 6
#define LED_PORT P0

#define BTN_PIN 4
#define BTN_PORT P0

void main(void)
{
    CKDIV = 0x00; // 16MHz
    pinMode(BTN_PORT, BTN_PIN, OUTPUT_PP);
    pinMode(LED_PORT, LED_PIN, OUTPUT_PP);

    // Pin interrupt
    // setb(PICON, PIT45); // PIT:1/0 Edge trigger/ Level trigger
    // setb(PINEN, BTN_PIN); // enable falling edge
    // clrb(PIPEN, BTN_PIN); // disable rasing edge
    Enable_INT_Port0;
    Enable_BIT4_FallEdge_Trig;

    // setb(EIE , EPI); // set external interrupt 0 at falling edge
    set_EPI;
    sei(); // Enable global interrupt

    while (1)
    {
        
    }
}

ISR(PIN_INT_FUCTION, INTERRUPT_PIN)
{
    if (inbit(PIF, PIF4))
    {
        daobit(LED_PORT, LED_PIN);
        _delay_ms(100);
    }
    PIF = 0x00; // clear interrupt flag
}