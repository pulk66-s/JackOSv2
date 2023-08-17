/* See COPYRIGHT for copyright information. */

#ifndef JOS_INC_ASSERT_H
#define JOS_INC_ASSERT_H

#include "console.h"


#define assert(x)		\
	do { if (!(x)) panic("assertion failed: "); } while (0)

// static_assert(x) will generate a compile-time error if 'x' is false.
#define static_assert(x)	switch (x) case 0: case (x):

#endif /* !JOS_INC_ASSERT_H */
