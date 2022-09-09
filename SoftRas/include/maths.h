#pragma once

#include "defines.h"

namespace SoftRas {
	struct vec3
	{
		float x, y, z;
	};
	struct vec2
	{
		float x, y;
	};
	struct ivec3
	{
		int32 x, y, z;
	};
	struct ivec2
	{
		int32 x, y;
	};
	struct uvec3
	{
		uint32 x, y, z;
	};
	struct uvec2
	{
		uint32 x, y;
	};

	struct Vertex {
		vec3 pos;
		vec3 color;
		vec3 norm;
		vec2 uv;
	};

	uint32 color_to_uint32(vec3 color);
	uint32 color_to_uint32(uint8 r, uint8 g, uint8 b);
}