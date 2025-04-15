/**
 * N76_Flash.h
 * N76E read write flash
 * Created: 2022/06/02
 * Author: TaiVB
 */

#define CID_READ            0x0B
#define DID_READ            0x0C
#define CFG_READ            0xC0
#define CFG_ERASE           0xE2

#define PAGE_ERASE_AP       0x22
#define BYTE_READ_AP        0x00
#define BYTE_PROGRAM_AP     0x21

#define BYTE_PROGRAM_CFG    0xE1
#define BYTE_READ_CFG       0xC0

#define PAGE_SIZE           128
#define BLOCK_SIZE          64

#define APROM_SIZE          17408
#define APROM_START_ADDR    0x0820

#define ERASE_FAIL          0x70
#define PROGRAM_FAIL        0x71
#define IAPFF_FAIL          0x72
#define IAP_PASS            0x00

uint8_t APROM_read_byte(uint16_t u16_addr);
uint16_t APROM_read_2byte(uint16_t u16_addr);
void APROM_write_byte(uint16_t addr, uint8_t data);
void Erase_APROM(uint16_t addr);