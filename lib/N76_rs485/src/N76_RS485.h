/*
 * N76_RS485.h
 * Created: 2023/08/23
 * Author: Van_BasTai
 */

#ifndef N76_RS485_H
#define N76_RS485_H

typedef void (*WriteCallback)(const byte what); // send a byte to serial port
typedef int (*AvailableCallback)(void);         // return number of bytes available
typedef int (*ReadCallback)(void);              // read a byte from serial port

void sendMsg(WriteCallback fSend,
             const byte *data, const byte length);
byte recvMsg(AvailableCallback fAvailable, ReadCallback fRead,
             byte *data, const byte length,
             uint32_t timeout);

#endif