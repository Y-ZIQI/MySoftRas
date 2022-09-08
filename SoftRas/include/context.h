#pragma once

#include "math.h"

namespace SoftRas {
	class Context {
	public:
		Context() {};
		~Context() {};

		void init();
		uint32*& getDefaultFramebuffer();

		void testPaint();

		uint32* m_framebuffer;
	};

	extern Context g_ctx;
}