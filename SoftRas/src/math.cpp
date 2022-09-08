#include "math.h"

namespace SoftRas {
	uint32 color_to_uint32(vec3 color) {
		return color_to_uint32((uint8)(255.0 * color.x), (uint8)(255.0 * color.y), (uint8)(255.0 * color.z));
	}

	uint32 color_to_uint32(uint8 r, uint8 g, uint8 b){
		return ((uint32)r << 16) | ((uint32)g << 8) | b;
	}
}