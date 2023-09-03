#include "random.h"

LKA_API u64_t random_u64(u64_t seed)
{
	return (u64_t)((28871271685163 * seed + 3657500101) % 18446744073709551615);
}

LKA_API u32_t random_u32(u64_t seed)
{
	return (u32_t)((28871271685163 * seed + 3657500101) % 4294967295);
}

LKA_API f32_t random_f32(u64_t seed)
{
	return (f32_t)((28871271685163 * seed + 3657500101) % 4294967295) / (f32_t)4294967295;
}

LKA_API f64_t random_f64(u64_t seed)
{
	return (f64_t)((28871271685163 * seed + 3657500101) % 18446744073709551615) / (f64_t)18446744073709551615;
}


