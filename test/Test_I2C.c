/*
 * test I2C project
 * Created: 2021/10/23
 * Author: taivb
 */

#include <include.h>
#include <N76_uart0.h>
#include <N76_I2C.h>

/* Địa chỉ của DS1307 */
const uint8_t DS1307 = 0x68;
/* Số uint8_t dữ liệu sẽ đọc từ DS1307 */
const uint8_t NumberOfFields = 7;

/* khai báo các biến thời gian */
int second, minute, hour, day, wday, month, year;

void readDS1307(void);
/* Chuyển từ format BCD (Binary-Coded Decimal) sang Decimal */
int bcd2dec(uint8_t num);
/* Chuyển từ Decimal sang BCD */
int dec2bcd(uint8_t num);
void digitalClockDisplay(void);
void printDigits(int digits);
/* cài đặt thời gian cho DS1307 */
void setTime(uint8_t hr, uint8_t min, uint8_t sec, uint8_t wd, uint8_t d, uint8_t mth, uint8_t yr);

void main(void)
{

    I2C_begin();
    /* cài đặt thời gian cho module */
    setTime(19, 37, 45, 5, 30, 3, 23); // 12:30:45 CN 08-02-2015
    UART0_begin(BAUD_115200);
    while (1)
    {
        /* Đọc dữ liệu của DS1307 */
        readDS1307();
        /* Hiển thị thời gian ra Serial monitor */
        digitalClockDisplay();
        _delay_ms(600);
    }
}

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
/* Chuyển từ format BCD (Binary-Coded Decimal) sang Decimal */
int bcd2dec(uint8_t num)
{
    return ((num / 16 * 10) + (num % 16));
}

/* Chuyển từ Decimal sang BCD */
int dec2bcd(uint8_t num)
{
    return ((num / 10 * 16) + (num % 10));
}

void digitalClockDisplay(void)
{
    // digital clock display of the time
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

void printDigits(int digits)
{
    // các thành phần thời gian được ngăn chách bằng dấu :
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
