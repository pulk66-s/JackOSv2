#include <lib/string.h>

void *itoa(long long num, char *str)
{
    int i = 0;
    int neg = 0;

    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
    if (num < 0) {
        neg = 1;
        num = -num;
    }
    while (num != 0) {
        int rem = num % 10;
        str[i++] = rem + '0';
        num /= 10;
    }
    if (neg)
        str[i++] = '-';
    str[i] = '\0';
    for (int j = 0; j < i / 2; j++) {
        char tmp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = tmp;
    }
    return str;
}
