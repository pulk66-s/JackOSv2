typedef unsigned long long  uint64_t;
typedef uint64_t            size_t;

size_t strlen(const char *str);

int main(void)
{
    char *str = "Hello, world!";

    strlen(str);
    return 0;
}