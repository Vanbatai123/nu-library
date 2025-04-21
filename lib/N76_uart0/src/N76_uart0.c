/**
 * @file N76_uart0.c
 * @author Van_BasTai (taivb.6dof@gmail.com)
 * @brief Nuvoton N76/MS51 uart0 library
 * @version 0.1
 * @date 2022-02-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <include.h>
#include <stdio.h>
#include <N76_uart0.h>

uint8_x _rx_buffer_head;                   // head of rx buffer
uint8_x _rx_buffer_tail;                   // tail of rx buffer
uint8_x _rx_buffer[SERIAL_RX_BUFFER_SIZE]; // rx buffer

//-----------------------------------------------------------------------------------------------------------
void UART0_begin(uint8_t baud)
{
    P06_Quasi_Mode; // Setting UART pin as Quasi mode for transmit
    P07_Quasi_Mode; // Setting UART pin as Quasi mode for transmit

    TH1 = baud;         // set baudrate
    SCON = (1 << REN);  // UART0 Mode1,REN=1
    set_M1_T1;          // Mode 2: 8-bit Timer/Counter with auto-reload from TH1
    set_SMOD;           // UART0 Double Rate Enable
    set_T1M;
    clr_BRCK; // Serial port 0 baud rate clock source = Timer1
    set_TR1;
    set_TI; // For printf function must setting TI = 1
}
//-----------------------------------------------------------------------------------------------------------
void UART0_putChar(uint8_t val)
{
    clr_TI;
    SBUF = val;
    while (inbit(SCON, TI) == 0)
        ; // wait until transfer complete
}
//-----------------------------------------------------------------------------------------------------------
void UART0_print(char *str)
{
    uint8_t i = 0;
    while (str[i] != '\0')
        UART0_putChar(str[i++]);
}
//-----------------------------------------------------------------------------------------------------------
void UART0_println(char *str)
{
    UART0_print(str);
    UART0_print("\r\n");
}
//-----------------------------------------------------------------------------------------------------------
void UART0_printNum(int32_t num, uint8_t base)
{
    uint8_x dis[20];          // array of converted number
    int8_t max = 0, negFlag = false; // max: index of dis array, negFlag: = 1 if negative

    if (num == 0) // input 0
    {
        dis[max++] = '0';
    }
    else if (num < 0) // negative number
    {
        num = 0 - num;
        negFlag = true;
    }
    while (num > 0) // convert to base number and add to dis array
    {
        if (num % base >= 10)
            dis[max] = num % base + 55; // for hex ABCDEF
        else
            dis[max] = num % base + 48; // number 0

        num = num / base;
        max++;
    }

    if (base == HEX) // add 0x for HEX and 0B for BIN
    {
        if (max % 2 == 1)
            dis[max++] = '0';

        dis[max++] = 'x';
        dis[max++] = '0';
    }
    else if (base == BIN)
    {
        dis[max++] = 'B';
        dis[max++] = '0';
    }

    if (negFlag == true) // add minus to negative number
        dis[max++] = '-';

    for (uint8_t i = 0; i < max / 2; i++) // revert dis array
    {
        dis[max] = dis[i];
        dis[i] = dis[max - 1 - i];
        dis[max - 1 - i] = dis[max];
    }
    dis[max] = '\0';  // end string character
    UART0_print(dis); // print dis
}
//-----------------------------------------------------------------------------------------------------------
void UART0_printNumln(long num, uint8_t base)
{
    UART0_printNum(num, base);
    UART0_println("");
}
//-----------------------------------------------------------------------------------------------------------
int UART0_available(void)
{
    return ((unsigned int)(SERIAL_RX_BUFFER_SIZE + _rx_buffer_head - _rx_buffer_tail)) % SERIAL_RX_BUFFER_SIZE;
}
//-----------------------------------------------------------------------------------------------------------
int UART0_read(void)
{
    // if the head isn't ahead of the tail, we don't have any characters
    if (_rx_buffer_head == _rx_buffer_tail)
    {
        return -1;
    }
    else
    {
        uint8_t c = _rx_buffer[_rx_buffer_tail];
        _rx_buffer_tail = (uint8_t)(_rx_buffer_tail + 1) % SERIAL_RX_BUFFER_SIZE;
        return c;
    }
}
//-----------------------------------------------------------------------------------------------------------
void UART0_attachInterrupt(void)
{
    set_REN;
    set_ES; // enable UART0 interrupt
}
//-----------------------------------------------------------------------------------------------------------
void UART0_detachInterrupt(void)
{
    clr_REN;
    clr_ES; // disable UART0 interrupt
}
//-----------------------------------------------------------------------------------------------------------
ISR(UART0_INT_FUCTION, INTERRUPT_UART0)
{
    if (SCON & 0x01 != 0x00) // check if SCON, RI == 1
    {                        /* if reception occur */
        clr_RI;              /* clear reception flag for next reception */

        uint8_t c = SBUF;
        uint8_t i = (unsigned int)(_rx_buffer_head + 1) % SERIAL_RX_BUFFER_SIZE;

        // if we should be storing the received character into the location
        // just before the tail (meaning that the head would advance to the
        // current location of the tail), we're about to overflow the buffer
        // and so we don't write the character or advance the head.
        if (i != _rx_buffer_tail)
        {
            _rx_buffer[_rx_buffer_head] = c;
            _rx_buffer_head = i;
        }
    }
}
//-----------------------------------------------------------------------------------------------------------
