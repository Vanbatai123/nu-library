/**
 * @file N76_uart0.h
 * @author Van_BasTai (taivb.6dof@gmail.com)
 * @brief Nuvoton N76/MS51 uart0 library
 * @version 0.1
 * @date 2022-02-03
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef N76_UART0_H
#define N76_UART0_H

// Baudrate definition
#define BAUD_4800               0x30
#define BAUD_9600               0x98
#define BAUD_19200              0xCC
#define BAUD_38400              0xE6
#define BAUD_57600              0xEF
#define BAUD_115200             0xF7

#define SERIAL_RX_BUFFER_SIZE   16U // Max rx buffer

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief
 *
 * @param baud BAUD_4800/9600/19200/38400/57600/115200
 */
void UART0_begin(uint8_t baud);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief uart0 transfer 1 character
 *
 * @param val
 */
void UART0_putChar(uint8_t val);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief uart0 transfer char array
 *
 * @param str
 */
void UART0_print(char *str);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief uart0 transfer char array with newline
 *
 * @param str
 */
void UART0_println(char *str);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief uart0 transfer a number
 *
 * @param num number to be transfered
 * @param base BIN, DEC, HEX
 */
void UART0_printNum(int32_t num, uint8_t base);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief uart0 transfer a number with newline
 *
 * @param num number to be transfered
 * @param base BIN, DEC, HEX
 */
void UART0_printNumln(long num, uint8_t base);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief check data in tx buffer
 *
 * @return int - number of byte in buffer
 */
int UART0_available(void);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief uart0 read 1 byte in data buffer
 *
 * @return int - byte data return
 */
int UART0_read(void);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief uart0 enable interrupt
 *
 */
void UART0_attachInterrupt(void);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief uart0 disable interrupt
 *
 */
void UART0_detachInterrupt(void);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief uart0 interrupt function
 *
 */
ISR(UART0_INT_FUCTION, INTERRUPT_UART0);

//-----------------------------------------------------------------------------------------------------------

#endif
