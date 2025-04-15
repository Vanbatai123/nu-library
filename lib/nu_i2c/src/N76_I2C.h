/*
 * N76E_i2c.h
 * Created: 2022/02/03
 * Author: Van_BasTai
*/

#ifndef N76_I2C_H
#define N76_I2C_H

// I2C direction
#define I2C_READ        1
#define I2C_WRITE       0

#define I2C_CLOCK       0x27 // Fclk = Fsys / (4*(prescalar + 1))
#define I2C_ACK         0
#define I2C_NACK        1
#define timeout_count   1000

// master
#define I2C_MT_START    0x01

#define I2C_BUFFER_LEN  32

void I2C_begin(void);
uint8_t I2C_beginTransmission(uint8_t addr);
void I2C_write(uint8_t data);
uint8_t I2C_endTransmission(void);
void I2C_writeBuffer(uint8_t *data, uint8_t len);
uint8_t I2C_requestFrom(uint8_t addr, uint8_t len);
uint8_t I2C_read(void);
int16_t I2C_available(void);

#endif