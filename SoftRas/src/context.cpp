#include "context.h"

namespace SoftRas {
	Context g_ctx;

	void Context::init(uint window_width, uint window_height)
	{
		m_fbos.clear();
		Framebuffer* default_fbo = createFramebuffer(window_width, window_height, 0, true);
		default_fbo->addColorBuffer(SR_TYPE_NONE);
		m_fbos.push_back(default_fbo);
		bindFramebuffer(0);
	}

	void Context::drawTrianglesIndexed(Vertex* vertices, uint* indices, uint amount)
	{
		/* Vertex shader */
		/* Rasterize */
		/* Fragment Shader */
	}

	void Context::bindFramebuffer(uint id)
	{
		if (id < m_fbos.size()) {
			m_framebuffer = m_fbos[id];
		}
	}

	Framebuffer* Context::getFramebuffer()
	{
		return m_framebuffer;
	}

	Framebuffer* Context::getFramebuffer(uint id)
	{
		if (id < m_fbos.size()) {
			return m_fbos[id];
		}
		return nullptr;
	}

	Framebuffer* Context::createFramebuffer(uint width, uint height, uint color_attachs, bool has_depth)
	{
		Framebuffer* n_fbo = new Framebuffer;
		n_fbo->init(m_fbos.size(), width, height);
		for (uint i = 0; i < color_attachs; i++) {
			n_fbo->addColorBuffer(SR_TYPE_RGBA8);
		}
		if (has_depth) {
			n_fbo->addDepthBuffer();
		}
		return n_fbo;
	}

	void Context::testPaint()
	{
		for (int i = 100; i < 500; i++) {
			for (int j = 300; j < 310; j++) {
				m_framebuffer->setPixel(0, i, j, color_to_uint32({ 1.0, 0.0, 0.0 }));
			}
		}
		for (int i = 100; i < 500; i++) {
			for (int j = 310; j < 320; j++) {
				m_framebuffer->setPixel(0, i, j, color_to_uint32({ 0.0, 1.0, 0.0 }));
			}
		}
		for (int i = 100; i < 500; i++) {
			for (int j = 320; j < 330; j++) {
				m_framebuffer->setPixel(0, i, j, color_to_uint32({ 0.0, 0.0, 1.0 }));
			}
		}
	}
}