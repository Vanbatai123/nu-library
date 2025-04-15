/*
 * N76_W25Qxx.h
 * Created: 2023/05/28
 * Author: Van_BasTai
 */

#ifndef N76_W25Qxx_H
#define N76_W25Qxx_H

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


// w25q32 definition
#define FLASH_BYTE      4194304 // 4MB
#define BLOCK_BYTE_64K  65536   // 64kb
#define BLOCK_BYTE_32K  32768   // 32kb
#define SECTOR_BYTE_4K  4096    // 4kb
#define PAGE_BYTE       256     // 256byte


#define PAGE_SIZE        (FLASH_BYTE / PAGE_BYTE) //((1) * 1024) //1024*256 = 4mb
#define SECTOR_SIZE_4K   (FLASH_BYTE / SECTOR_BYTE_4K)
#define BLOCK_SIZE_64K   (FLASH_BYTE / BLOCK_BYTE_64K)
#define BLOCK_SIZE_32K   (FLASH_BYTE / BLOCK_BYTE_32K)

#define W25Q_CMD_WRITE_ENABLE                   0x06    /**< write enable */
#define W25Q_CMD_VOLATILE_SR_WRITE_ENABLE       0x50    /**< sr write enable */
#define W25Q_CMD_WRITE_DISABLE                  0x04    /**< write disable */
#define W25Q_CMD_READ_STATUS_REG1               0x05    /**< read status register-1 */
#define W25Q_CMD_READ_STATUS_REG2               0x35    /**< read status register-2 */
#define W25Q_CMD_READ_STATUS_REG3               0x15    /**< read status register-3 */
#define W25Q_CMD_WRITE_STATUS_REG1              0x01    /**< write status register-1 */
#define W25Q_CMD_WRITE_STATUS_REG2              0x31    /**< write status register-2 */
#define W25Q_CMD_WRITE_STATUS_REG3              0x11    /**< write status register-3 */
#define W25Q_CMD_CHIP_ERASE                     0xC7    /**< chip erase */
#define W25Q_CMD_ERASE_PROGRAM_SUSPEND          0x75    /**< erase suspend */
#define W25Q_CMD_ERASE_PROGRAM_RESUME           0x7A    /**< erase resume */
#define W25Q_CMD_POWER_DOWN                     0xB9    /**< power down */
#define W25Q_CMD_RELEASE_POWER_DOWN             0xAB    /**< release power down */
#define W25Q_CMD_READ_MANUFACTURER              0x90    /**< manufacturer */
#define W25Q_CMD_JEDEC_ID                       0x9F    /**< jedec id */
#define W25Q_CMD_GLOBAL_BLOCK_SECTOR_LOCK       0x7E    /**< global block lock */
#define W25Q_CMD_GLOBAL_BLOCK_SECTOR_UNLOCK     0x98    /**< global block unlock */
#define W25Q_CMD_ENTER_QSPI_MODE                0x38    /**< enter spi mode */
#define W25Q_CMD_ENABLE_RESET                   0x66    /**< enable reset */
#define W25Q_CMD_RESET_DEVICE                   0x99    /**< reset device */
#define W25Q_CMD_READ_UNIQUE_ID                 0x4B    /**< read unique id */
#define W25Q_CMD_PAGE_PROGRAM                   0x02    /**< page program */
#define W25Q_CMD_QUAD_PAGE_PROGRAM              0x32    /**< quad page program */
#define W25Q_CMD_SECTOR_ERASE_4K                0x20    /**< sector erase */
#define W25Q_CMD_BLOCK_ERASE_32K                0x52    /**< block erase */
#define W25Q_CMD_BLOCK_ERASE_64K                0xD8    /**< block erase */
#define W25Q_CMD_READ_DATA                      0x03    /**< read data */
#define W25Q_CMD_FAST_READ                      0x0B    /**< fast read */
#define W25Q_CMD_FAST_READ_DUAL_OUTPUT          0x3B    /**< fast read dual output */
#define W25Q_CMD_FAST_READ_QUAD_OUTPUT          0x6B    /**< fast read quad output */
#define W25Q_CMD_READ_SFDP_REGISTER             0x5A    /**< read SFDP register */
#define W25Q_CMD_ERASE_SECURITY_REGISTER        0x44    /**< erase security register */
#define W25Q_CMD_PROGRAM_SECURITY_REGISTER      0x42    /**< program security register */
#define W25Q_CMD_READ_SECURITY_REGISTER         0x48    /**< read security register */
#define W25Q_CMD_INDIVIDUAL_BLOCK_LOCK          0x36    /**< individual block lock */
#define W25Q_CMD_INDIVIDUAL_BLOCK_UNLOCK        0x39    /**< individual block unlock */
#define W25Q_CMD_READ_BLOCK_LOCK                0x3D    /**< read block lock */
#define W25Q_CMD_FAST_READ_DUAL_IO              0xBB    /**< fast read dual I/O */
#define W25Q_CMD_DEVICE_ID_DUAL_IO              0x92    /**< device id dual I/O */
#define W25Q_CMD_SET_BURST_WITH_WRAP            0x77    /**< set burst with wrap */
#define W25Q_CMD_FAST_READ_QUAD_IO              0xEB    /**< fast read quad I/O */
#define W25Q_CMD_WORD_READ_QUAD_IO              0xE7    /**< word read quad I/O */
#define W25Q_CMD_OCTAL_WORD_READ_QUAD_IO        0xE3    /**< octal word read quad I/O */
#define W25Q_CMD_DEVICE_ID_QUAD_IO              0x94    /**< device id quad I/O */


// STATUS REG1's bit
#define REG1_SRP            7
#define REG1_SEC            6
#define REG1_TB             5
#define REG1_BP2            4
#define REG1_BP1            3
#define REG1_BP0            2
#define REG1_WEL            1
#define REG1_BUSY           0

// status
#define W25Qxx_BUSY         1
#define W25Qxx_IDLE         0

#define W25Qxx_OK           0
#define W25Qxx_ERR          1
#define W25Qxx_ERR_PARAM    2

void SPI_Error(void);
void W25Qxx_begin(void);
uint8_t W25Qxx_writeCmd(uint8_t cmd);
void W25Qxx_writeAddr(uint32_t addr);

void W25Qxx_readMidDid(uint8_t *MFID, uint8_t *DID);
void W25Qxx_writeEnable(void);
void W25Qxx_writeDisable(void);
void W25Qxx_eraseChip(void);
uint8_t W25Qxx_eraseSectorBlock(uint8_t cmd, uint16_t num);
void W25Qxx_waitIdle(void);
uint8_t W25Qxx_eraseVerify(void);
void W25Qxx_writePage(uint32_t pageNum, uint8_t *data);
void W25Qxx_writeBuff(uint32_t addr, uint8_t *data, uint16_t len);
void W25Qxx_readBuff(uint32_t addr, uint8_t *data, uint32_t len);
void W25Qxx_readPage(uint32_t pageNum, uint8_t *data);
uint8_t W25Qxx_writeVerify(void);

#endif