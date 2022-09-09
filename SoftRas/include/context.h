#pragma once

#include "maths.h"
#include "framebuffer.h"

namespace SoftRas {
	class Context {
	public:
		Context() {};
		~Context() {};

		void init(uint window_width, uint window_height);

		void drawTrianglesIndexed(Vertex* vertices, uint* indices, uint amount);

		void bindFramebuffer(uint id);
		Framebuffer* getFramebuffer();
		Framebuffer* getFramebuffer(uint id);
		Framebuffer* createFramebuffer(uint width, uint height, uint color_attachs, bool has_depth);

		void testPaint();

		/* Current status */
		Framebuffer* m_framebuffer;

		/* Global resources */
		std::vector<Framebuffer*> m_fbos;
		//std::vector<Shader*> m_shaders;
		//std::vector<Texture*> m_texs;
	};

	extern Context g_ctx;
}