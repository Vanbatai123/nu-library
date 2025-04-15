/*
 * N76E_i2c.c
 * Created: 2022/02/03
 * Author: Van_BasTai
 */

#include <include.h>
#include <N76_I2C.h>

uint8_x t = 0; // variable for timeout

// rx buffer variable/array
uint8_x rxBufferIndex;
uint8_x rxBufferLength;
uint8_x rxBuffer[I2C_BUFFER_LEN];

// tx buffer variable/array
uint8_x txBufferIndex;
uint8_x txBufferLength;
uint8_x txBuffer[I2C_BUFFER_LEN];

uint8_x timeOut(void)
{
    _delay_us(100);
    if (++t > 10)
        return true;
    return false;
}

void I2C_begin(void)
{
    P13_OpenDrain_Mode;
    P14_OpenDrain_Mode;

    /* Set I2C clock rate */
    I2CLK = I2C_CLOCK; // I2C clock = Fsys/(4*(I2CLK+1))

    /* Enable I2C */
    set_I2CEN;
}

uint8_t I2C_beginTransmission(uint8_t addr)
{
    txBufferIndex = 0;
    txBufferLength = 0;

    // check I2C is free?
    /*t = 0;
    while (inbit(I2C_SR3, BUSY) == 1)
        if (timeOut())
            return 1;
*/
    // start condittion - S
    set_STA;
    clr_SI;

    t = 0;
    // wait start condittion is sent - EV5
    while (inbit(I2CON, SI) == 0)
        if (timeOut())
            return 2;
    ////I2C_SR1; // clear I2C_SR1, SB

    // send slave address
    I2DAT = (addr << 1) | I2C_WRITE;

    t = 0;
    // wait slave address is sent - EV6
    clr_STA;
    clr_SI;
    while (inbit(I2CON, SI) == 0)
        if (timeOut())
            return 3;

    return 0;
}

void I2C_write(uint8_t data)
{
    txBuffer[txBufferIndex++] = data;
    txBufferLength = txBufferIndex;
}

void I2C_writeBuffer(uint8_t *data, uint8_t len)
{
    uint8_t i = 0;
    for (; i < len; ++i)
    {
        I2C_write(data[i]);
    }
}

uint8_t I2C_endTransmission(void)
{
    uint8_t i;

    for (i = 0; i < txBufferLength; ++i)
    {
        // send 1 byte data register address to read
        I2DAT = txBuffer[i];

        // wait until the transfer finished - EV 8_2
        t = 0;
        clr_STA;
        clr_SI;
        while (inbit(I2CON, SI) == 0)
            if (timeOut())
                return 1;
    }

    // set stop condition
    set_STO;
    set_SI;

    // Wait to make sure that STOP control bit has been cleared
    t = 0;
    while (inbit(I2CON, STO) == 1)
        if (timeOut())
            return 3;

    // Re-Enable Acknowledgement to be ready for another reception
    ////setb(I2C_CR2, ACK); // Enable acknowledgement
    /////clrb(I2C_CR2, POS); // acknowledgement for current byte

    return 0;
}

uint8_t I2C_requestFrom(uint8_t addr, uint8_t len)
{
    uint8_t i;
    rxBufferLength = len;
    rxBufferIndex = 0;

    // check I2C is free?
    /*t = 0;
    while (inbit(I2C_SR3, BUSY) == 1)
        if (timeOut())
            return 1;
*/
    // start condittion - S
    set_STA;
    clr_SI;

    // wait start condittion is sent - EV5
    t = 0;
    while (inbit(I2CON, SI) == 0)
        if (timeOut())
            return 2;

    // send slave address
    I2DAT = (addr << 1) | I2C_READ;
    clr_STA;
    clr_SI;

    // Wait on ADDR flag to be set EV 6_3 (ADDR is still not cleared at this level
    t = 0;
    while (inbit(I2CON, SI) == 0)
        if (timeOut())
            return 3;

    // receive len - 1 byte
    for (i = 0; i < rxBufferLength - 1; i++)
    {
        // Poll RXNE
        set_AA;
        clr_SI;

        t = 0;
        while (inbit(I2CON, SI) == 0)
            if (timeOut())
                return 4;
        // rxBuffer[i] = I2DAT;
        rxBuffer[i] = I2DAT;
    }

    // clear ACK
    clr_AA;
    clr_SI;
    // Poll RXNE
    t = 0;
    while (inbit(I2CON, SI) == 0)
        if (timeOut())
            return 5;
    rxBuffer[rxBufferLength - 1] = I2DAT;

    // set stop after ADDR is cleared
    set_STO;
    clr_SI;

    // Wait to make sure that STOP control bit has been cleared
    t = 0;
    while (inbit(I2CON, STO) == 1)
        if (timeOut())
            return 6;
    // Re-Enable Acknowledgement to be ready for another reception
    // setb(I2C_CR2, ACK); // Enable acknowledgement
    // clrb(I2C_CR2, POS); // acknowledgement for current byte

    return 0;
}

uint8_t I2C_read(void)
{
    int8_t value = -1;
    // get each successive byte on each call
    if (rxBufferIndex < rxBufferLength)
    {
        value = rxBuffer[rxBufferIndex];
        ++rxBufferIndex;
    }
    return value;
}

int16_t I2C_available(void)
{
    return rxBufferLength - rxBufferIndex;
}
