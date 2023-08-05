/**
 * @file    format.c
 * @brief   This file handle all string format functions
 * 
 * @details
 * This file handle all string format functions in printf style. It's usefull
 * to split them because it's a lot of code and can be used in many differents
 * places and technologies.
 * 
 * !     This file is not finished yet, waiting for memory management
*/

// #include <include/clib/string.h>
// #include <include/clib/stdarg.h>

// /**
//  * @brief       Get the whole size of the final buffer
//  * @param fmt   The format string
//  * @param args  The arguments to the format string
//  * @return      The size of the final buffer
// */
// static inline size_t get_buff_size(const char *fmt, va_list args) {
//     size_t size = 0;

//     for (size_t i = 0; fmt[i]; i++) {
//         if (fmt[i] != '%') {
//             continue;
//         }
//         i++;
//         switch (fmt[i]) {
//             case 's':
//                 size += strlen(va_arg(args, char *));
//                 break;
//             default:
//                 break;
//         }
//     }
//     return size;
// }

// /**
//  * @brief       Get the final buffer
//  * @param fmt   The format string
//  * @param args  The arguments to the format string
//  * @param size  The size of the final buffer
//  * @return      The final buffer
// */
// static inline char *get_buff(const char *fmt, va_list args, size_t buff_size) {
//     char buff[buff_size] = {0};

//     for (size_t i = 0; fmt[i]; i++) {
//         if (fmt[i] != '%') {
//             buff[i] = fmt[i];
//             continue;
//         }
//         i++;
//         switch (fmt[i]) {
//             case 's':
//                 strcat(buff, va_arg(args, char *));
//                 break;
//             default:
//                 break;
//         }
//     }
//     return buff;
// }

// /**
//  * @brief       Format a string in printf style
//  * @param fmt   The format string
//  * @param args  The arguments to the format string
//  * @return      The formatted string
// */
// char *format_string(const char *fmt, va_list args) {
//     size_t buff_size = get_buff_size(fmt, args) + 1;
//     char buff[buff_size] = get_buff(fmt, args, buff_size);

//     return buff;
// }