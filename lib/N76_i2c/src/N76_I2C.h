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

// I2C buffer length
#define I2C_BUFFER_LEN  32U

// I2C error code
#define I2C_OK                  0x00
#define I2C_WRITE_FAIL          0x01
#define I2C_START_FAIL          0x02
#define I2C_SLAVE_ADDR_FAIL     0x03
#define I2C_READ_FAIL           0x04
#define I2C_READ_ACK_FAIL       0x05
#define I2C_STOP_FAIL           0x06

// I2CSTAT value
#define I2C_BUS_ERROR           0x00 // Bus Error
#define I2C_START               0x08 // Start
#define I2C_M_Tx_RESTART        0x10 // Master Repeat Start
#define I2C_M_Tx_ADDR_ACK       0x18 // Master Transmit Address ACK
#define I2C_M_Tx_ADDR_NACK      0x20 // Master Transmit Address NACK
#define I2C_M_Tx_DATA_ACK       0x28 // Master Transmit Data ACK
#define I2C_M_Tx_DATA_NACK      0x30 // Master Transmit Data NACK
#define I2C_M_ARB_LOST          0x38 // Master Arbitration Lost
#define I2C_M_Rx_ADDR_ACK       0x40 // Master Receive Address ACK
#define I2C_M_Rx_ADDR_NACK      0x48 // Master Receive Address NACK
#define I2C_M_Rx_DATA_ACK       0x50 // Master Receive Data ACK
#define I2C_M_Rx_DATA_NACK      0x58 // Master Receive Data NACK
#define I2C_S_Tx_RESTART_RESTOP 0xA0 // Slave Transmit Repeat Start or Stop
#define I2C_S_Tx_ADDR_ACK       0xA8 // Slave Transmit Address ACK
#define I2C_S_Tx_ARB_LOST       0xB0 // Slave Transmit Arbitration Lost
#define I2C_S_Tx_DATA_ACK       0xB8 // Slave Transmit Data ACK
#define I2C_S_Tx_DATA_NACK      0xC0 // Slave Transmit Data NACK
#define I2C_S_Tx_LAST_ADDR_ACK  0xC8 // Slave Transmit Last Data ACK
#define I2C_S_Rx_ADDR_ACK       0x60 // Slave Receive Address ACK
#define I2C_S_Rx_ARB_LOST       0x68 // Slave Receive Arbitration Lost
#define I2C_S_Rx_DATA_ACK       0x80 // Slave Receive Data ACK
#define I2C_S_Rx_DATA_NACK      0x88 // Slave Receive Data NACK
#define I2C_GC_ADDR_ACK         0x70 // GC mode Address ACK
#define I2C_GC_ARB_LOST         0x78 // GC mode Arbitration Lost
#define I2C_GC_DATA_ACK         0x90 // GC mode Data ACK
#define I2C_GC_DATA_NACK        0x98 // GC mode Data NACK
#define I2C_BUS_RELEASE         0xF8 // Bus Release


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
