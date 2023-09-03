#pragma once

#include <stdio.h>
#include "core.h"
#include "types.h"

#define U32_MAX 4294967295
#define U64_MAX 18446744073709551615

#define LPRIME_1 28871271685163
#define LPRIME_2 3657500101

LKA_API u64_t random_u64(u64_t seed);
LKA_API u32_t random_u32(u64_t seed);
LKA_API f32_t random_f32(u64_t seed);
LKA_API f64_t random_f64(u64_t seed);
