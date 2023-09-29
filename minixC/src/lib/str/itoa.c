#include <lib/string.h>

void itoa(uint64_t n, char *s, int b)
{
    size_t i = 0;
    int isneg = 0;
    size_t base_mod = 0;

    if (n < 0) {
        isneg = 1;
        n = -n;
    }
    while (n > 0) {
        base_mod = n % b;
        if (base_mod > 9) {
            s[i++] = 'A' + (base_mod - 10);
        } else {
            s[i++] = '0' + base_mod;
        }
        n /= b;
    }
    if (isneg) {
        s[i++] = '-';
    }
    s[i] = '\0';
    for (size_t j = 0; j < i / 2; j++) {
        char tmp = s[j];
        s[j] = s[i - j - 1];
        s[i - j - 1] = tmp;
    }
}
