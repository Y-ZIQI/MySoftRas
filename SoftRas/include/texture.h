#pragma once

#include "maths.h"

namespace SoftRas {
	class Texture {
	public:
		Texture();
		~Texture();

		void init(uint width, uint height, uint comp = 4, uint8* data = nullptr);
		vec4 sample(float u, float v);
		float sample_as_float(float u, float v);
		vec4 sample_offset(float u, float v, int offset_x, int offset_y);

	//private:
		uint m_width, m_height;
		uint m_comp;
		uint8* m_data = nullptr;
	};

}