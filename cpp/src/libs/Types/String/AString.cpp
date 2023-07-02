#include "Types/String/AString.hpp"

void AString::init(const char *str) {
    this->_len = this->strlen(str);
    this->str = this->strdup(str);
}

void AString::init(int value)
{
    char *str = this->itoa(value);

    this->init(str);
}

size_t AString::strlen(const char *str) {
    size_t len = 0;

    while (str[len] != '\0') {
        len++;
    }
    return len;
}

char *AString::strdup(const char *str) {
    size_t len = strlen(str);
    char *dup = (char *)this->alloc(len + 1);

    for (size_t i = 0; i < len; i++) {
        dup[i] = str[i];
    }
    dup[len] = '\0';
    return dup;
}

char AString::operator[](size_t index) {
    if (index >= this->_len) {
        return '\0';
    }
    return this->str[index];
}

size_t AString::len() {
    return this->_len;
}

const char *AString::c_str() {
    return this->str;
}

char *AString::itoa(int value)
{
    char *str = (char *)this->alloc(12);
    int i = 0;

    if (value == 0) {
        str[0] = '0';
        str[1] = '\0';
        return str;
    }
    if (value < 0) {
        str[0] = '-';
        value = -value;
        i++;
    }
    while (value != 0) {
        str[i] = (value % 10) + '0';
        value /= 10;
        i++;
    }
    str[i] = '\0';
    this->revstr(str[0] == '-' ? str + 1 : str);
    return str;
}

void AString::revstr(char *str)
{
    size_t len = strlen(str);
    size_t i = 0;
    size_t j = len - 1;
    char tmp;

    while (i < j) {
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        i++;
        j--;
    }
}