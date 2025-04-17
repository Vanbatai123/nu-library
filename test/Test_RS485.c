/**
 * @file Test_RS485.c
 * @author Van_BasTai (taivb.6dof@gmail.com)
 * @brief Test RS485 function
 * @version 0.1
 * @date 2025-04-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <include.h>
#include <N76_uart0.h>
#include <N76_RS485.h>

void fWrite(const byte what)
{
    UART0_putChar(what);
}

int fAvailable(void)
{
    return UART0_available();
}

int fRead(void)
{
    return UART0_read();
}

byte old_level = 0;

byte msg[] = {
    1, // thiết bị 1
    2, // bật đèn sáng
    3  // mức mấy
};
void main(void)
{
    UART0_begin(BAUD_9600); // rs485.begin(28800);
    P05_PushPull_Mode;      // cho phép truyền
    UART0_attachInterrupt();
    sei();

    byte buf[2];
    buf[1] = 0;
    while (1)
    {
        if (buf[1] == 1)
        {
            msg[2] = 250;
        }
        else if (buf[1] == 251)
        {
            msg[2] = 0;
        }

        // gửi đến slave
        setb(P0, 5);
        sendMsg(fWrite, msg, sizeof msg);
        clrb(P0, 5);

        _delay_ms(10);

        byte received = recvMsg(fAvailable, fRead, buf, 2, 50000U);
        // chỉ gửi 1 lần cho 1 lần thay đổi
        // while (msg[1] != 3);
    }
}
