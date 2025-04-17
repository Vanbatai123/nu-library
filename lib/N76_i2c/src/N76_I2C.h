/**
 * @file N76_I2C.h
 * @author Van_BasTai (taivb.6dof@gmail.com)
 * @brief Nuvoton N76/MS51 I2C library
 * @version 0.1
 * @date 2022-02-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef N76_I2C_H
#define N76_I2C_H

// I2C direction
#define I2C_READ        1U
#define I2C_WRITE       0U

#define I2C_CLOCK       0x27 // Fclk = Fsys / (4*(prescalar + 1))
#define I2C_ACK         0U
#define I2C_NACK        1U
#define timeout_count   10U

// master
#define I2C_MT_START    0x01

#define I2C_BUFFER_LEN  32U

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief I2C configured as master
 *
 */
void I2C_begin(void);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief I2C prepare for transmission
 *
 * @param addr I2C address for transmission
 * @return uint8_t - error code
 */
uint8_t I2C_beginTransmission(uint8_t addr);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief I2C store 1 byte to tx buffer
 *
 * @param data
 */
void I2C_write(uint8_t data);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief I2C store an array to tx buffer
 *
 * @param data
 * @param len
 */
void I2C_writeBuffer(uint8_t *data, uint8_t len);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief I2C end transmission
 *
 * @return uint8_t - error code
 */
uint8_t I2C_endTransmission(void);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief I2C request to read data from address
 *
 * @param addr address to be read
 * @param len number of bytes
 * @return uint8_t - error code
 */
uint8_t I2C_requestFrom(uint8_t addr, uint8_t len);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief I2C read 1 byte from rx buffer
 *
 * @return uint8_t
 */
uint8_t I2C_read(void);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief I2C check rx buffer available
 *
 * @return int16_t - number of bytes in rx buffer
 */
int16_t I2C_available(void);

//-----------------------------------------------------------------------------------------------------------

#endif
