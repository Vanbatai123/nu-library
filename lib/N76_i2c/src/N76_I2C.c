/**
 * @file N76_I2C.c
 * @author Van_BasTai (taivb.6dof@gmail.com)
 * @brief Nuvoton N76/MS51 I2C library
 * @version 0.1
 * @date 2022-02-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <include.h>
#include <N76_I2C.h>

uint8_x t = 0;                    // variable for timeout

uint8_x rxBufferIndex;            // rx buffer index
uint8_x rxBufferLength;           // rx buffer length
uint8_x rxBuffer[I2C_BUFFER_LEN]; // rx buffer array

uint8_x txBufferIndex;            // tx buffer length
uint8_x txBufferLength;           // tx buffer length
uint8_x txBuffer[I2C_BUFFER_LEN]; // tx buffer array

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief I2C time out function
 * 
 * @return uint8_t 
 */
uint8_t timeOut(void)
{
    _delay_us(100);
    if (++t > timeout_count)
        return true;
    return false;
}
//-----------------------------------------------------------------------------------------------------------
void I2C_begin(void)
{
    P13_OpenDrain_Mode; // Open drain for SDA
    P14_OpenDrain_Mode; // Open drain for SCL
    I2CLK = I2C_CLOCK;  // Set I2C clock rate - I2C clock = Fsys/(4*(I2CLK+1))
    set_I2CEN;          // Enable I2C
}
//-----------------------------------------------------------------------------------------------------------
uint8_t I2C_beginTransmission(uint8_t addr)
{
    txBufferIndex = 0;
    txBufferLength = 0;
    
    // Check if I2C is busy
    while(inbit(I2CON, SI) != 0) // If SI still keep 1
    {
        if (I2STAT != I2C_BUS_RELEASE || I2STAT != I2C_BUS_ERROR) // Check bus status if bus error，first send stop
        {
            set_STO; // Check bus status if bus error，first send stop
        }
        clr_SI;
        if(inbit(I2CON, SI) != 0) // If SI still keep 1
        {
            clr_I2CEN; // please first disable I2C.
            set_I2CEN; // Then enable I2C for clear SI.
            clr_SI;
            clr_I2CEN; // At last disable I2C for next a new transfer
        } 
    }

    // send START
    set_STA;
    clr_SI;

    t = 0; // reset timeout
    // wait start condittion is sent
    while (inbit(I2CON, SI) == 0)
        if (timeOut())
            break;
    if (I2STAT != I2C_START) // Check status value after every step
        return I2STAT;

    // Send slave address
    I2DAT = (addr << 1) | I2C_WRITE;

    t = 0; // reset timeout
    // wait slave address is sent
    clr_STA;
    clr_SI;
    while (inbit(I2CON, SI) == 0)
        if (timeOut())
            break;
    if (I2STAT != I2C_M_Tx_ADDR_ACK) // Check status value after every step
        return I2STAT;
    
    return I2C_OK;
}
//-----------------------------------------------------------------------------------------------------------
void I2C_write(uint8_t data)
{
    txBuffer[txBufferIndex++] = data;
    txBufferLength = txBufferIndex;
}
//-----------------------------------------------------------------------------------------------------------
void I2C_writeBuffer(uint8_t *data, uint8_t len)
{
    uint8_t i = 0;
    for (; i < len; ++i)
    {
        I2C_write(data[i]);
    }
}
//-----------------------------------------------------------------------------------------------------------
uint8_t I2C_endTransmission(void)
{
    uint8_t i;

    for (i = 0; i < txBufferLength; ++i)
    {
        // send 1 byte data register address to read
        I2DAT = txBuffer[i];

        // wait until the transfer finished - EV 8_2
        t = 0; // reset timeout
        clr_STA;
        clr_SI;
        while (inbit(I2CON, SI) == 0)
            if (timeOut())
                break;
        if (I2STAT != I2C_M_Tx_DATA_ACK) // Check transmitted data ACK status
            return I2STAT;
    }

    // set stop condition
    set_STO;
    clr_SI;

    // Wait to make sure that STOP control bit has been cleared
    t = 0; // reset timeout
    while (inbit(I2CON, STO) == 1)
        if (timeOut())
            return I2C_STOP_FAIL;

    return I2C_OK;
}
//-----------------------------------------------------------------------------------------------------------
uint8_t I2C_requestFrom(uint8_t addr, uint8_t len)
{
    uint8_t i;
    rxBufferLength = len;
    rxBufferIndex = 0;

    // start condittion - S
    set_STA;
    clr_SI;

    // wait start condittion is sent
    t = 0; // reset timeout
    while (inbit(I2CON, SI) == 0)
        if (timeOut())
            break;
    if (I2STAT != I2C_START) // Check start sent status
        return I2STAT;

    // send slave address
    I2DAT = (addr << 1) | I2C_READ;
    clr_STA;
    clr_SI;

    // Wait on ADDR flag to be set (ADDR is still not cleared at this level)
    t = 0; // reset timeout
    while (inbit(I2CON, SI) == 0)
        if (timeOut())
            break;
    if (I2STAT != I2C_M_Rx_ADDR_ACK) // Check address send ack status
        return I2STAT;

    // receive len - 1 byte
    for (i = 0; i < rxBufferLength - 1; i++)
    {
        // Poll RXNE
        set_AA;
        clr_SI;

        t = 0; // reset timeout
        while (inbit(I2CON, SI) == 0)
            if (timeOut())
                break;
        if (I2STAT != I2C_M_Rx_DATA_ACK) // Check received data ACK status
            return I2STAT;
        rxBuffer[i] = I2DAT;
    }

    // clear ACK
    clr_AA;
    clr_SI;
    // Poll RXNE
    t = 0; // reset timeout
    while (inbit(I2CON, SI) == 0)
        if (timeOut())
            break;
    if (I2STAT != I2C_M_Rx_DATA_NACK) // Check received data NACK status
        return I2STAT;
    // read last byte
    rxBuffer[rxBufferLength - 1] = I2DAT;

    // set stop after ADDR is cleared
    set_STO;
    clr_SI;

    // Wait to make sure that STOP control bit has been cleared
    t = 0; // reset timeout
    while (inbit(I2CON, STO) == 1)
        if (timeOut())
            return I2C_STOP_FAIL;

    return I2C_OK;
}
//-----------------------------------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------------------------------------
int16_t I2C_available(void)
{
    return rxBufferLength - rxBufferIndex;
}
//-----------------------------------------------------------------------------------------------------------
