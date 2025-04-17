/**
 * @file Test_I2C.c
 * @author Van_BasTai (taivb.6dof@gmail.com)
 * @brief Test I2C with DS1307 show UART0
 * @version 0.1
 * @date 2025-04-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <include.h>
#include <N76_uart0.h>
#include <N76_I2C.h>

const uint8_t DS1307 = 0x68;                      // DS1307 address
const uint8_t NumberOfFields = 7;                 // bytes data will be read from DS1307
int second, minute, hour, day, wday, month, year; // time variable

void readDS1307(void);          // read data from DS1307
int bcd2dec(uint8_t num);       // convert from BCD (Binary-Coded Decimal) to Decimal
int dec2bcd(uint8_t num);       // convert from Decimal to BCD (Binary-Coded Decimal)
void digitalClockDisplay(void); // show clock into uart0
void printDigits(int digits);
// set up time for DS1307
void setTime(uint8_t hr, uint8_t min, uint8_t sec, uint8_t wd, uint8_t d, uint8_t mth, uint8_t yr);

void main(void)
{
    I2C_begin(); // start I2C

    // set up time for DS1307
    setTime(22, 40, 00, 2, 14, 4, 25); // 12:30:45 CN 08-02-2015
    UART0_begin(BAUD_115200); // setup uart0 baudrate
    while (1)
    {
        readDS1307();          // read data from DS1307
        digitalClockDisplay(); // show data into uart0
        _delay_ms(600);
    } // end while(1)
}

/**
 * @brief read data from DS1307
 * 
 */
void readDS1307(void)
{
    I2C_beginTransmission(DS1307);
    I2C_write((uint8_t)0x00);
    I2C_endTransmission();
    I2C_requestFrom(DS1307, NumberOfFields);

    second = bcd2dec(I2C_read() & 0x7f);
    minute = bcd2dec(I2C_read());
    hour = bcd2dec(I2C_read() & 0x3f); // chế độ 24h.
    wday = bcd2dec(I2C_read());
    day = bcd2dec(I2C_read());
    month = bcd2dec(I2C_read());
    year = bcd2dec(I2C_read());
    year += 2000;
}

/**
 * @brief Convert from BCD (Binary-Coded Decimal) to Decimal
 * 
 * @param num bcd value
 * @return int 
 */
int bcd2dec(uint8_t num)
{
    return ((num / 16 * 10) + (num % 16));
}

/**
 * @brief Convert from Decimal to BCD (Binary-Coded Decimal)
 * 
 * @param num dec number
 * @return int 
 */
int dec2bcd(uint8_t num)
{
    return ((num / 10 * 16) + (num % 10));
}

/**
 * @brief show clock into uart0
 * 
 */
void digitalClockDisplay(void)
{
    UART0_printNum(hour, DEC);
    printDigits(minute);
    printDigits(second);
    UART0_print(" ");
    UART0_printNum(day, DEC);
    UART0_print(" ");
    UART0_printNum(month, DEC);
    UART0_print(" ");
    UART0_printNum(year, DEC);
    UART0_println("");
}

/**
 * @brief 
 * 
 * @param digits 
 */
void printDigits(int digits)
{
    // split time value by ":"
    UART0_print(":");

    if (digits < 10)
        UART0_print("0");
    UART0_printNum(digits, DEC);
}

/* cài đặt thời gian cho DS1307 */
void setTime(uint8_t hr, uint8_t min, uint8_t sec, uint8_t wd, uint8_t d, uint8_t mth, uint8_t yr)
{
    I2C_beginTransmission(DS1307);
    I2C_write(0x00); // đặt lại pointer
    I2C_write(dec2bcd(sec));
    I2C_write(dec2bcd(min));
    I2C_write(dec2bcd(hr));
    I2C_write(dec2bcd(wd)); // day of week: Sunday = 1, Saturday = 7
    I2C_write(dec2bcd(d));
    I2C_write(dec2bcd(mth));
    I2C_write(dec2bcd(yr));
    I2C_endTransmission();
}
