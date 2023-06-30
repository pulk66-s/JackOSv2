#include "AString.hpp"
#include "kernel/VGA/VGA.hpp"

AString::AString(const char *str)
{
    this->length = this->strlen(str);
}

size_t AString::len() const
{
    return this->length;
}

size_t AString::strlen(const char *str) const
{
    size_t length = 0;

    for (size_t i = 0; str[i]; i++) {
        length++;
    }
    return length;
}

char *AString::strdup(const char *str) const
{
    size_t len = this->strlen(str);
    char *buff = (char *)this->alloc(len + 1);

    for (size_t i = 0; i < len; i++) {
        buff[i] = str[i];
    }
    buff[len] = '\0';
    return buff;
}

char *AString::c_str() const
{
    return this->str;
}