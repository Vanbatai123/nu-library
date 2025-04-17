/**
 * @file N76_SPI.h
 * @author Van_BasTai (taivb.6dof@gmail.com)
 * @brief Nuvoton N76/MS51 SPI library
 * @version 0.1
 * @date 2023-03-30
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef N76_SPI_H
#define N76_SPI_H


#define SPI_PIN_SS      1
#define SPI_PIN_CLK     0
#define SPI_PIN_MISO    1
#define SPI_PIN_MOSI    0

#define SPI_Px_SS       P1
#define SPI_Px_CLK      P1
#define SPI_Px_MISO     P0
#define SPI_Px_MOSI     P0

#define SPI_PxM1_SS     P1M1
#define SPI_PxM1_CLK    P1M1
#define SPI_PxM1_MISO   P0M1
#define SPI_PxM1_MOSI   P0M1

#define SPI_PxM2_SS     P1M2
#define SPI_PxM2_CLK    P1M2
#define SPI_PxM2_MISO   P0M2
#define SPI_PxM2_MOSI   P0M2


#define LSBFIRST            0
#define MSBFIRST            1

#define SPI_CLOCK_DIV2      0x00
#define SPI_CLOCK_DIV4      0x01
#define SPI_CLOCK_DIV8      0x02
#define SPI_CLOCK_DIV16     0x03

#define SPI_MODE0           0x00
#define SPI_MODE1           0x04
#define SPI_MODE2           0x08
#define SPI_MODE3           0x0C

#define SPI_MODE_MASTER     0x00
#define SPI_MODE_SLAVE      0x01

#define SPI_MODE_MASK       0x0C  // CPOL = bit 3, CPHA = bit 2 on SPCR
#define SPI_CLOCK_MASK      0x03  // SPR1 = bit 1, SPR0 = bit 0 on SPCR
#define SPI_2XCLOCK_MASK    0x01  // SPI2X = bit 0 on SPSR


//-----------------------------------------------------------------------------------------------------------
/**
 * @brief  default master: mode 0 div 2\
 * @brief did not dev slave mode
 * @param spi_mode SPI_MODE_MASTER/SLAVE
 */
void SPI_begin(uint8_t spi_mode);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief Tranfer 1 byte data to SPI_MOSI line\
 * @brief and return 1 byte from SPI_MISO
 * @param data 
 * @return uint8_t 
 */
uint8_t SPI_transfer(uint8_t data);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief 
 * 
 * @param data 
 * @return uint16_t 
 */
uint16_t SPI_transfer16(uint16_t data);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief 
 * 
 * @param buf 
 * @param count 
 */
void SPI_transferBuf(void *buf, uint16_t count);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief stop SPI
 * 
 */
void SPI_end(void);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief  set bit order of SPI line
 * 
 * @param bitOrder MSB/LSB
 */
void SPI_setBitOrder(uint8_t bitOrder);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief set data mode of SPI
 * 
 * @param dataMode SPI_MODE0-3
 */
void SPI_setDataMode(uint8_t dataMode);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief Set clock devider 
 * 
 * @param clockDiv SPI_CLOCK_DIV2/4/8/16
 */
void SPI_setClockDivider(uint8_t clockDiv);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief 
 * 
 */
void SPI_attachInterrupt(void);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief 
 * 
 */
void SPI_detachInterrupt(void);

//-----------------------------------------------------------------------------------------------------------

#endif
