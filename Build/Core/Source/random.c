#include "random.h"

u64_t random_seed = 0;

LKA_API void random_init(u64_t seed)
{
    random_seed = seed;
}

LKA_API u64_t random_u64()
{
    return random_seed = (u64_t)((LPRIME_1 * random_seed + LPRIME_2) % U64_MAX);
}

LKA_API u32_t random_u32()
{
	return random_seed = (u32_t)((LPRIME_1 * random_seed + LPRIME_2) % U32_MAX);
}

LKA_API i64_t random_i64()
{
    return (i64_t)(random_seed = (u64_t)((LPRIME_1 * random_seed + LPRIME_2) % I64_MAX));
}

LKA_API i32_t random_i32()
{
    return (i32_t)(random_seed = (u64_t)((LPRIME_1 * random_seed + LPRIME_2) % I32_MAX));
}

LKA_API f32_t random_f32()
{
    u32_t result = (u32_t)(LPRIME_1 * random_seed) + LPRIME_2;
    random_seed = result % U32_MAX;
	return (f32_t)result / (f32_t)U32_MAX;
}

LKA_API f64_t random_f64()
{
    u64_t result = LPRIME_1 * random_seed + LPRIME_2;
    random_seed = result % U64_MAX;
	return (f64_t)result / (f64_t)U64_MAX;
}


