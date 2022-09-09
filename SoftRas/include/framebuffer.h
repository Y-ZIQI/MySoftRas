#pragma once

#include <vector>

#include "maths.h"

namespace SoftRas {
	class Framebuffer {
	public:
		Framebuffer() {};
		~Framebuffer() {};

		struct Attach {
			//void* buffer;
			uint32* buffer;
			uint8 type;
		};

		void init(uint id, uint width, uint height);
		void addColorBuffer(uint8 type);
		void addDepthBuffer();
		Attach getColorBuffer(uint id);
		float* getDepthBuffer();
		uint getColorBufferCount();
		bool hasDepthBuffer();

		uint32 readPixel(uint id, uint row, uint column);
		void setPixel(uint id, uint row, uint column, uint32 value);
		float readDepth(uint row, uint column);
		void setDepth(uint row, uint column, float value);

		uint m_id;
		uint m_width, m_height;
		std::vector<Attach> m_color_buffers;
		float* m_depth_buffer;
	};

}