/*
 * N76_W25Qxx.c
 * Created: 2023/05/28
 * Author: Van_BasTai
 */

#include <include.h>
#include <N76_SPI.h>
#include <N76_uart0.h>
#include <N76_W25Qxx.h>

//-----------------------------------------------------------------------------------------------------------
void SPI_Error(void)
{
    UART0_println("\n*  SPI Error, please check the connection between MCU and SPI Flash");
    while (1)
        ;
}
//-----------------------------------------------------------------------------------------------------------
void W25Qxx_begin(void)
{
    SPI_begin(SPI_MODE_MASTER);
    SPI_setBitOrder(MSBFIRST);
    SPI_setDataMode(SPI_MODE0);
    SPI_setClockDivider(SPI_CLOCK_DIV2);
    // return reset_flash();
}
//-----------------------------------------------------------------------------------------------------------
uint8_t W25Qxx_writeCmd(uint8_t cmd)
{
    uint8_t status = W25Qxx_OK;

    clrb(SPI_Px_SS, SPI_PIN_SS);
    status = SPI_transfer(cmd); // RESUME komutunu gönder
    setb(SPI_Px_SS, SPI_PIN_SS);

    if (status == W25Qxx_OK)
        return 1;
    else
        return 0;
}
//-----------------------------------------------------------------------------------------------------------
void W25Qxx_writeAddr(uint32_t addr)
{
    SPI_transfer((uint8_t)((addr >> 16) & 0xFF));
    SPI_transfer((uint8_t)((addr >> 8) & 0xFF));
    SPI_transfer((uint8_t)(addr & 0xFF));
}
//-----------------------------------------------------------------------------------------------------------
void W25Qxx_readMidDid(uint8_t *MFID, uint8_t *DID)
{
    clrb(SPI_Px_SS, SPI_PIN_SS);
    SPI_transfer(W25Q_CMD_READ_MANUFACTURER);
    SPI_transfer(0x00);
    SPI_transfer(0x00);
    SPI_transfer(0x00);
    *MFID = SPI_transfer(0xFF);
    *DID = SPI_transfer(0xFF);
    setb(SPI_Px_SS, SPI_PIN_SS);
}
//-----------------------------------------------------------------------------------------------------------
void W25Qxx_writeEnable(void)
{
    W25Qxx_writeCmd(W25Q_CMD_WRITE_ENABLE);
}
//-----------------------------------------------------------------------------------------------------------
void W25Qxx_writeDisable(void)
{
    W25Qxx_writeCmd(W25Q_CMD_WRITE_DISABLE);
}
//-----------------------------------------------------------------------------------------------------------
void W25Qxx_eraseChip(void)
{
    W25Qxx_writeEnable();
    W25Qxx_writeCmd(W25Q_CMD_CHIP_ERASE);
    W25Qxx_waitIdle();
    W25Qxx_writeDisable();
}
//-----------------------------------------------------------------------------------------------------------
uint8_t W25Qxx_eraseSectorBlock(uint8_t cmd, uint16_t num)
{
    uint32_t addr = 0;
    if (cmd == W25Q_CMD_SECTOR_ERASE_4K)
    {
        if (num >= SECTOR_SIZE_4K)
            return W25Qxx_ERR_PARAM;
        addr = SECTOR_BYTE_4K * num;
    }
    else if (cmd == W25Q_CMD_BLOCK_ERASE_32K)
    {
        if (num >= BLOCK_SIZE_32K)
            return W25Qxx_ERR_PARAM;
        addr = BLOCK_BYTE_32K * num;
    }
    else if (cmd == W25Q_CMD_BLOCK_ERASE_64K)
    {
        if (num >= BLOCK_SIZE_64K)
            return W25Qxx_ERR_PARAM;
        addr = BLOCK_BYTE_64K * num;
    }

    W25Qxx_writeEnable();

    clrb(SPI_Px_SS, SPI_PIN_SS);

    SPI_transfer(cmd);
    W25Qxx_writeAddr(addr);

    setb(SPI_Px_SS, SPI_PIN_SS);
    W25Qxx_waitIdle();
    W25Qxx_writeDisable();

    return W25Qxx_OK;
}
//-----------------------------------------------------------------------------------------------------------
void W25Qxx_waitIdle(void)
{
    uint8_t u8Status;

    clrb(SPI_Px_SS, SPI_PIN_SS);
    do
    {
        SPI_transfer(W25Q_CMD_READ_STATUS_REG1);
        u8Status = SPI_transfer(0xFF);
    } while (inbit(u8Status, REG1_BUSY) == 1);

    setb(SPI_Px_SS, SPI_PIN_SS);
}
//-----------------------------------------------------------------------------------------------------------
uint8_t W25Qxx_eraseVerify(void)
{
    uint16_t i;
    uint8_t u8Data;

    clrb(SPI_Px_SS, SPI_PIN_SS);

    SPI_transfer(W25Q_CMD_READ_DATA);
    SPI_transfer(0x00);
    SPI_transfer(0x00);
    SPI_transfer(0x00);

    for (i = 0; i < 256; i++)
    {
        u8Data = SPI_transfer(0x00);
        if (u8Data != 0xFF)
        {
            return W25Qxx_ERR;
        }
    }

    setb(SPI_Px_SS, SPI_PIN_SS);
    return W25Qxx_OK;
}
//-----------------------------------------------------------------------------------------------------------
void W25Qxx_writePage(uint32_t pageNum, uint8_t *data)
{
    uint32_t i;
    i = (uint32_t)pageNum * (uint32_t)PAGE_BYTE;

    W25Qxx_writeEnable();

    clrb(SPI_Px_SS, SPI_PIN_SS);
    SPI_transfer(W25Q_CMD_PAGE_PROGRAM);
    W25Qxx_writeAddr(i);

    /* Send the data to SPI_Flash buffer */
    for (i = 0; i < PAGE_BYTE; i++)
    {
        SPI_transfer((uint8_t)data[i]);
    }
    setb(SPI_Px_SS, SPI_PIN_SS);

    W25Qxx_waitIdle(); // wait ultil done
    W25Qxx_writeDisable();
}
//-----------------------------------------------------------------------------------------------------------
void W25Qxx_writeBuff(uint32_t addr, uint8_t *data, uint16_t len)
{
    uint16_t i;

    W25Qxx_writeEnable();
    clrb(SPI_Px_SS, SPI_PIN_SS);

    SPI_transfer(W25Q_CMD_PAGE_PROGRAM);
    W25Qxx_writeAddr(addr);

    /* Send the data to SPI_Flash buffer */
    for (i = 0; i < len; i++)
    {
        SPI_transfer((uint8_t)data[i]);
    }

    setb(SPI_Px_SS, SPI_PIN_SS);
    W25Qxx_waitIdle(); // wait ultil done
    W25Qxx_writeDisable();
}
//-----------------------------------------------------------------------------------------------------------
void W25Qxx_readPage(uint32_t pageNum, uint8_t *data)
{
    uint32_t i;
    i = pageNum * PAGE_BYTE;

    clrb(SPI_Px_SS, SPI_PIN_SS);
    SPI_transfer(W25Q_CMD_READ_DATA);
    W25Qxx_writeAddr(i);

    for (i = 0; i < PAGE_BYTE; i++)
    {
        data[i] = SPI_transfer(0x00);
    }
    setb(SPI_Px_SS, SPI_PIN_SS);
} //-----------------------------------------------------------------------------------------------------------
void W25Qxx_readBuff(uint32_t addr, uint8_t *data, uint32_t len)
{
    uint16_t i;

    clrb(SPI_Px_SS, SPI_PIN_SS);
    SPI_transfer(W25Q_CMD_READ_DATA);
    W25Qxx_writeAddr(addr);

    for (i = 0; i < len; i++)
    {
        data[i] = SPI_transfer(0x00);
    }
    setb(SPI_Px_SS, SPI_PIN_SS);
}
//-----------------------------------------------------------------------------------------------------------
uint8_t W25Qxx_writeVerify(void)
{
    uint16_t i;
    uint8_t u8Data;

    clrb(SPI_Px_SS, SPI_PIN_SS);

    SPI_transfer(W25Q_CMD_READ_DATA);
    SPI_transfer(0x00);
    SPI_transfer(0x00);
    SPI_transfer(0x00);

    for (i = 0; i < 256; i++)
    {
        u8Data = SPI_transfer(0x00);

        if (u8Data != (uint8_t)i)
        {
            return W25Qxx_ERR;
        }
    }
    setb(SPI_Px_SS, SPI_PIN_SS);

    return W25Qxx_OK;
}