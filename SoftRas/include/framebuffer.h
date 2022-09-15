#pragma once

#include <vector>

#include "maths.h"

namespace SoftRas {
	class Framebuffer {
	public:
		Framebuffer();
		~Framebuffer();

		struct Attach {
			uint32* buffer;
			uint8 type;
		};

		void init(uint id, uint width, uint height);

		uint getWidth();
		uint getHeight();

		void addColorBuffer(uint8 type, uint32* ext_buffer = nullptr);
		void addDepthBuffer(float* ext_buffer = nullptr);
		Attach getColorBuffer(uint id);
		float* getDepthBuffer();
		uint getColorBufferCount();
		bool hasDepthBuffer();

		uint32 readPixel(uint id, uint x, uint y);
		void setPixel(uint id, uint x, uint y, uint32 value);
		void blendPixel(uint id, uint x, uint y, uint32 value);
		float readDepth(uint x, uint y);
		void setDepth(uint x, uint y, float value);

		void clear(uint id, uint32 value);
		void clearDepth(float value = 1.0f);

		void addMSAADepthBuffer(float* ext_buffer = nullptr);
		float* getMSAADepthBuffer();
		bool hasMSAADepthBuffer();
		float readMSAADepth(uint x, uint y, uint8 index);
		void setMSAADepth(uint x, uint y, uint8 index, float value);
		void setMSAAFlag(uint x, uint y, uint8 index);

		// use external buffer data(assume Attach.type=SR_TYPE_NONE)
		void applyExternalBuffer(uint id, uint32* ext_buffer);

	private:
		uint m_id;
		uint m_width, m_height;
		std::vector<Attach> m_color_buffers;
		float* m_depth_buffer = nullptr;
		// for msaa
		uint8* m_msaa_flag_buffer = nullptr;
		float* m_msaa_depth_buffer = nullptr;
	};

}