#pragma once

#include <stdio.h>
#include "core.h"
#include "types.h"

#define I32_MAX 0x7fffffff
#define I64_MAX 0x7fffffffffffffff

#define U32_MAX 0xffffffffff
#define U64_MAX 0xffffffffffffffff

#define LPRIME_1 0x1a421de49c2b
#define LPRIME_2 0xda0105c5

LKA_API void random_init(u64_t seed);

// Generates a random integer between 0 and MAX (defined above)
LKA_API u64_t random_u64();
LKA_API u32_t random_u32();
LKA_API i64_t random_i64();
LKA_API i32_t random_i32();

// Generates a random real number between 0.0 and 1.0
LKA_API f32_t random_f32();
LKA_API f64_t random_f64();
