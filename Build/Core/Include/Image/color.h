#pragma once

#include "types.h"

#define RED_MASK		0x00ff0000
#define GREEN_MASK		0x0000ff00
#define BLUE_MASK		0x000000ff
#define BLACK_MASK		0x00000000
#define WHITE_MASK		0x00ffffff
#define YELLOW_MASK		RED_MASK  |  GREEN_MASK
#define MAGENTA_MASK	RED_MASK  |  BLUE_MASK
#define CYAN_MASK		BLUE_MASK |  GREEN_MASK

struct __RGBA32_t
{
	i8_t red;
	i8_t green;
	i8_t blue;
	i8_t alpha;
};

typedef struct __RGBA32_t RGBA32_t;
