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

#include <include.h>
#include <N76_SPI.h>

//-----------------------------------------------------------------------------------------------------------
void SPI_begin(uint8_t spi_mode)
{
    setb(SPSR, DISMODF); // SS pin user define
    clrb(SPCR, SSOE);    // SS pin user define
    if (spi_mode == SPI_MODE_MASTER)
    {
        SPCR |= (1 << SPIEN) | (1 << MSTR);
        // SPIE: interrupt, SPE: enable, MSTR: Master mode, CPHA: Phase, SPR1:0: pre-scaler = 128

        // CLK,MOSI,SS Push pull mode
        // MISO Opendrain
        setb(SPI_Px_SS, SPI_PIN_SS);

        clrb(SPI_PxM1_CLK, SPI_PIN_CLK);
        clrb(SPI_PxM1_MOSI, SPI_PIN_MOSI);
        setb(SPI_PxM1_MISO, SPI_PIN_MISO);
        clrb(SPI_PxM1_SS, SPI_PIN_SS);

        setb(SPI_PxM2_CLK, SPI_PIN_CLK);
        setb(SPI_PxM2_MOSI, SPI_PIN_MOSI);
        setb(SPI_PxM2_MISO, SPI_PIN_MISO);
        setb(SPI_PxM2_SS, SPI_PIN_SS);
    }
    else if (spi_mode == SPI_MODE_SLAVE)
    {
        // #warning not define yet

        // CLK,MOSI,SS Opendrain
        // MISO Push_pull mode
        // setb(SPI_PxM1_CLK, SPI_PIN_CLK);
        // setb(SPI_PxM1_MOSI, SPI_PIN_MOSI);
        // setb(SPI_PxM1_MISO, SPI_PIN_MISO);
        // setb(SPI_PxM1_SS, SPI_PIN_SS);

        // setb(SPI_PxM2_CLK, SPI_PIN_CLK);
        // setb(SPI_PxM2_MOSI, SPI_PIN_MOSI);
        // clrb(SPI_PxM2_MISO, SPI_PIN_MISO);
        // setb(SPI_PxM2_SS, SPI_PIN_SS);
        // SPCR |= (1 << SPIE) | (1 << SPIE); // enable spi & interrupt for slave
    }
}
//-----------------------------------------------------------------------------------------------------------
uint8_t SPI_transfer(uint8_t data)
{
    SPDR = data;
    // __asm__("nop");
    while (inbit(SPSR, SPIF) == 0)
        ; // wait
    clrb(SPSR, SPIF);
    return SPDR;
}
//-----------------------------------------------------------------------------------------------------------
// uint16_t SPI_transfer16(uint16_t data)
// {
//      return 0;
// }
// void SPI_transferBuf(void *buf, uint16_t count)
// {
//-----------------------------------------------------------------------------------------------------------
// }
//-----------------------------------------------------------------------------------------------------------
// void SPI_end()
// {

// }
//-----------------------------------------------------------------------------------------------------------
void SPI_setBitOrder(uint8_t bitOrder)
{
    if (bitOrder == LSBFIRST)
        setb(SPCR, LSBFE);
    else
        clrb(SPCR, LSBFE);
}
//-----------------------------------------------------------------------------------------------------------
void SPI_setDataMode(uint8_t dataMode)
{
    SPCR = (SPCR & ~SPI_MODE_MASK) | dataMode;
}
//-----------------------------------------------------------------------------------------------------------
void SPI_setClockDivider(uint8_t clockDiv)
{
    SPCR = (SPCR & ~SPI_CLOCK_MASK) | (clockDiv & SPI_CLOCK_MASK);
}
//-----------------------------------------------------------------------------------------------------------
void SPI_attachInterrupt(void)
{

}
//-----------------------------------------------------------------------------------------------------------
void SPI_detachInterrupt(void)
{

}
//-----------------------------------------------------------------------------------------------------------
