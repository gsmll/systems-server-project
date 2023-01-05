#ifndef UTILTYPE_H
#define UTILTYPE_H

#include <bits/stdint-intn.h>
#include <bits/stdint-uintn.h>
#include <stdint.h> 
#include <sys/types.h>
#include <stdbool.h> 

typedef int8_t   i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32; 
typedef uint64_t u64;

typedef intptr_t isize; 
typedef uintptr_t usize;

typedef u8* str;

#define ASSERT(condition) condition ? true : false 
#define ASSERT_EQ(x, y) x == y ? true : false

#endif
