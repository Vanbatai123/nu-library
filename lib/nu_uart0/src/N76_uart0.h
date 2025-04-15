/*
 * n76_uart.h
 * Created: 2021/05/13
 * Author: Van_BasTai
 */

#ifndef N76_UART0_H
#define N76_UART0_H

#define BAUD_4800               0x30
#define BAUD_9600               0x98
#define BAUD_19200              0xCC
#define BAUD_38400              0xE6
#define BAUD_57600              0xEF
#define BAUD_115200             0xF7

#define SERIAL_RX_BUFFER_SIZE   16U

void UART0_begin(uint8_t baud);
void UART0_putChar(uint8_t val);
void UART0_print(char *str);
void UART0_println(char *str);
void UART0_printNum(int32_t num, uint8_t base);
void UART0_printNumln(long num, uint8_t base);
void UART0_attachInterrupt(void);
void UART0_detachInterrupt(void);
int UART0_available(void);
int UART0_read(void);
ISR(UART0_INT_FUCTION, INTERRUPT_UART0);

#endif
