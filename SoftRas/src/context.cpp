#include "context.h"

namespace SoftRas {
	Context g_ctx;

	void Context::init()
	{
	}

	uint32*& Context::getDefaultFramebuffer()
	{
		return m_framebuffer;
	}

	void Context::testPaint()
	{
		for (int i = 100; i < 500; i++) {
			for (int j = 300; j < 310; j++) {
				m_framebuffer[i * 800 + j] = color_to_uint32({ 1.0, 0.0, 0.0 });
			}
		}
		for (int i = 100; i < 500; i++) {
			for (int j = 310; j < 320; j++) {
				m_framebuffer[i * 800 + j] = color_to_uint32({ 0.0, 1.0, 0.0 });
			}
		}
		for (int i = 100; i < 500; i++) {
			for (int j = 320; j < 330; j++) {
				m_framebuffer[i * 800 + j] = color_to_uint32({ 0.0, 0.0, 1.0 });
			}
		}
	}
}