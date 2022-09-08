#pragma once

#include "defines.h"

namespace SoftRas {
	struct vec3
	{
		float x, y, z;
	};
	struct ivec3
	{
		int32 x, y, z;
	};
	struct uvec3
	{
		uint32 x, y, z;
	};

	uint32 color_to_uint32(vec3 color);
	uint32 color_to_uint32(uint8 r, uint8 g, uint8 b);
}