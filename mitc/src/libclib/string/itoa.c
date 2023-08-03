/**
 * @file    itoa.c
 * @brief   itoa function implementation
 * 
 * @details
 * The itoa() function converts the integer num to a string pointed to by buff.
*/

#include <include/clib/string.h>

/**
 * @brief       convert an int to a string
 * @param num   The number to convert
 * @param buff  The buffer to store the string in. It must be at least 
 *              MAX_INT_SIZE + 1 bytes long to store the string and the null terminator.
 *              It will be filled with 0s.
 * @return      The string representation of the number
*/
void itoa(int num, char *buff) {
    uint8_t sign = 0;               // 1 = negative, 0 = positive
    size_t digit = 0;
    size_t index = 0;

    for (size_t i = 0; i < MAX_INT_SIZE; buff[i++] = '\0');
    if (num < 0) {
        sign = 1;
        num = -num;
        buff[index++] = '-';
    }
    while (num > 0) {
        digit = num % 10;
        num /= 10;
        buff[index++] = digit + '0';
    }
    revstr(buff + sign);
}
