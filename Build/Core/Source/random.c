#include "random.h"

LKA_API u64_t random_u64(u64_t seed)
{
	return (u64_t)((LPRIME_1 * seed + LPRIME_2) % U64_MAX);
}

LKA_API u32_t random_u32(u64_t seed)
{
	return (u32_t)((LPRIME_1 * seed + LPRIME_2) % U32_MAX);
}

LKA_API f32_t random_f32(u64_t seed)
{
	return (f32_t)((LPRIME_1 * seed + LPRIME_2) % U32_MAX) / (f32_t)U32_MAX;
}

LKA_API f64_t random_f64(u64_t seed)
{
	return (f64_t)((LPRIME_1 * seed + LPRIME_2) % U64_MAX) / (f64_t)U64_MAX;
}


