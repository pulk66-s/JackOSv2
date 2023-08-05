/**
 * @file        stdarg.h
 * @brief       Variable argument handling macros
 * 
 * @details
 * This file contains all the variable argument handling macros.
*/

#ifndef __JOS_INCLUDE_STDARG_H__
#define __JOS_INCLUDE_STDARG_H__

#define va_list         __builtin_va_list
#define va_start(ap, p) __builtin_va_start(ap, p)
#define va_arg(ap, t)   __builtin_va_arg(ap, t)
#define va_end(ap)      __builtin_va_end(ap)

#endif