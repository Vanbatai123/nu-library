/**
 * @file I2C_scanDevice.c
 * @author Van_BasTai (taivb.6dof@gmail.com)
 * @brief Nuvoton example code for I2C scan device
 * @version 0.1
 * @date 2021-02-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <include.h>
#include <N76_uart0.h>
#include <N76_I2C.h>

void main(void)
{
    uint8_t i = 0;
    uint8_t error = 0;
    
    I2C_begin(); // start I2C
    UART0_begin(BAUD_115200); // setup uart0 baudrate
    while (1)
    {
        UART0_println("I2C scan device: ");
        for (i = 1; i < 127; i++)
        {
            error = I2C_beginTransmission(i);
            I2C_endTransmission();
            if (error == I2C_OK)
            {
                UART0_printNum(i, HEX);
                UART0_println(" ");
            }
        }
        UART0_println("");
        _delay_ms(2000);
    } // end while(1)
}
