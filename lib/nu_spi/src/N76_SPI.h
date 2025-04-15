/*
 * N76E_SPI.h
 * Created: 2023/03/30
 * Author: Van_BasTai
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

// SPI_HAS_TRANSACTION means SPI has beginTransaction(), endTransaction(),
// usingInterrupt(), and SPISetting(clock, bitOrder, dataMode)
#define SPI_HAS_TRANSACTION         1

// SPI_HAS_NOTUSINGINTERRUPT means that SPI has notUsingInterrupt() method
#define SPI_HAS_NOTUSINGINTERRUPT   1

// SPI_ATOMIC_VERSION means that SPI has atomicity fixes and what version.
// This way when there is a bug fix you can check this define to alert users
// of your code if it uses better version of this library.
// This also implies everything that SPI_HAS_TRANSACTION as documented above is
// available too.
#define SPI_ATOMIC_VERSION          1

// Uncomment this line to add detection of mismatched begin/end transactions.
// A mismatch occurs if other libraries fail to use SPI.endTransaction() for
// each SPI.beginTransaction().  Connect an LED to this pin.  The LED will turn
// on if any mismatch is ever detected.
//#define SPI_TRANSACTION_MISMATCH_LED 5

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

// Initialize the SPI library

/// @brief default master: mode 0 div 2
/// @brief did not dev slave mode
/// @param spi_mode SPI_MODE_MASTER/SLAVE
void SPI_begin(uint8_t spi_mode);

/// @brief Tranfer 1 byte data to SPI_MOSI line
/// @brief and return 1 byte from SPI_MISO
/// @param data 
/// @return 
uint8_t SPI_transfer(uint8_t data);

/// @brief 
/// @param data 
/// @return 
uint16_t SPI_transfer16(uint16_t data);

/// @brief 
/// @param buf 
/// @param count 
void SPI_transferBuf(void *buf, uint16_t count);

/// @brief 
void SPI_end(void);


/// @brief set bit order of SPI line
/// @param bitOrder (MSB or LSB)
void SPI_setBitOrder(uint8_t bitOrder);

/// @brief set data mode of SPI
/// @param dataMode SPI_MODE0-3
void SPI_setDataMode(uint8_t dataMode);

/// @brief Set clock devider 
/// @param clockDiv SPI_CLOCK_DIV2/4/8/16
void SPI_setClockDivider(uint8_t clockDiv);

/// @brief 
void SPI_attachInterrupt(void);

/// @brief 
void SPI_detachInterrupt(void);


#endif