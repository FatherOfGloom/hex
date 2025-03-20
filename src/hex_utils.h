#ifndef HEX_UTILS_H_
#define HEX_UTILS_H_

#define __HEX_I64 long long

typedef signed char i8;
typedef unsigned char u8;
typedef short i16;
typedef unsigned short u16;
typedef int i32;
typedef unsigned u32;
typedef __HEX_I64 i64;
typedef unsigned __HEX_I64 u64;
typedef float f32;

#if !defined(_INC_STDLIB)
  #include <stdlib.h>
#endif

typedef size_t usize;

typedef int err_t;

#define discard (void)
#define return_defer(val) do { result = (val); goto defer; } while(0)

#define ERR -1
#define OK 0

#endif  // HEX_UTILS_H_