/**
 * @file N76_Flash.h
 * @author Van_BasTai (taivb.6dof@gmail.com)
 * @brief Nuvoton N76 APROM library
 * @version 0.1
 * @date 2025-04-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef N76_UART0_H
#define N76_UART0_H

#define CID_READ            0x0B
#define DID_READ            0x0C
#define CFG_READ            0xC0
#define CFG_ERASE           0xE2

#define PAGE_ERASE_AP       0x22
#define BYTE_READ_AP        0x00
#define BYTE_PROGRAM_AP     0x21

#define BYTE_PROGRAM_CFG    0xE1
#define BYTE_READ_CFG       0xC0

#define PAGE_SIZE           128U
#define BLOCK_SIZE          64U

#define APROM_SIZE          17408 // N76: 18KB, MS51: 14KB
#define APROM_START_ADDR    0x0000

#define ERASE_FAIL          0x70
#define PROGRAM_FAIL        0x71
#define IAPFF_FAIL          0x72
#define IAP_PASS            0x00

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief read an APROM byte
 * 
 * @param u16_addr address to be read
 * @return uint8_t 
 */
uint8_t APROM_read_byte(uint16_t u16_addr);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief read 2 APROM bytes
 * 
 * @param u16_addr address to be read
 * @return uint16_t 
 */
uint16_t APROM_read_2byte(uint16_t u16_addr);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief write 1 APROM byte
 * 
 * @param addr address to be written
 * @param data value to be write
 */
void APROM_write_byte(uint16_t addr, uint8_t data);

//-----------------------------------------------------------------------------------------------------------
/**
 * @brief erase 1 APROM byte
 * 
 * @param addr address to be erased
 */
void Erase_APROM(uint16_t addr);

//-----------------------------------------------------------------------------------------------------------

#endif
