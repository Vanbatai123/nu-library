/**
 * @file Test_SPI.c
 * @author Van_BasTai (taivb.6dof@gmail.com)
 * @brief Test SPI using MAX7219
 * @version 0.1
 * @date 2025-04-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <include.h>
#include <N76_uart0.h>
#include <N76_SPI.h>

uint16_t value;

#define CODEB_MINUS     0x0A
#define CODEB_H         0x0B
#define CODEB_E         0x0C
#define CODEB_L         0x0D
#define CODEB_P         0x0E
#define CODEB_BLANK     0x0F
#define CODEB_DP        0xF0

#define DECODE_MODE     0x09
#define INTENSITY       0x0A
#define SCAN_LIMIT      0x0B
#define SHUTDOWN        0x0C
#define DISPLAY_TEST    0x0F

void MAX7219_begin(void);
void MAX7219_transferAll(int8_t chip, const uint8_t addr, const uint8_t data);
void MAX7219_transfer(uint8_t chip, const uint8_t addr, const uint8_t data);

void MAX7219_begin(void)
{
    SPI_begin(SPI_MODE_MASTER);

    MAX7219_transferAll(3, SCAN_LIMIT, 0x07);
    MAX7219_transferAll(3, DECODE_MODE, 0xFF);
    MAX7219_transferAll(3, SHUTDOWN, 0x01);
    MAX7219_transferAll(3, DISPLAY_TEST, 0x00);
    MAX7219_transferAll(3, INTENSITY, 0x01);
}

void MAX7219_transferAll(int8_t chip, const uint8_t addr, const uint8_t data)
{
    clrb(SPI_Px_SS, SPI_PIN_SS);
    while (chip--)
    {
        SPI_transfer(addr);
        SPI_transfer(data);
    }
    setb(SPI_Px_SS, SPI_PIN_SS);
}

void MAX7219_transfer(uint8_t chip, const uint8_t addr, const uint8_t data)
{
    uint8_t total = chip & 0x0F; // 8
    chip = chip >> 4;             // 3

    clrb(SPI_Px_SS, SPI_PIN_SS);
    // send first nops
    while (--total >= chip)
    {
        SPI_transfer(0x00);
        SPI_transfer(0x00);
    }

    // send address and data
    SPI_transfer(addr);
    SPI_transfer(data);

    // send last nops
    while (--chip >= 1)
    {
        SPI_transfer(0x00);
        SPI_transfer(0x00);
    }
    setb(SPI_Px_SS, SPI_PIN_SS);
}

void main(void)
{
    MAX7219_begin();
    while (1)
    {
        MAX7219_transfer(0x13, 1, 5);
        MAX7219_transfer(0x13, 2, 9);
        MAX7219_transfer(0x13, 3, 9);
        MAX7219_transfer(0x13, 4, 1);
        MAX7219_transfer(0x13, 5, 3 | CODEB_DP);
        MAX7219_transfer(0x13, 6, 0);
        MAX7219_transfer(0x13, 7, 3 | CODEB_DP);
        MAX7219_transfer(0x13, 8, 1);
    }
}
