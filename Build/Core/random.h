#pragma once

#include <stdio.h>
#include "core.h"
#include "types.h"

LKA_API u64_t random_u64(u64_t seed);
LKA_API u32_t random_u32(u64_t seed);
LKA_API f32_t random_f32(u64_t seed);
LKA_API f64_t random_f64(u64_t seed);
