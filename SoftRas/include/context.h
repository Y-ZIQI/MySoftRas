#pragma once

#include "framebuffer.h"
#include "shader.h"
#include "texture.h"

namespace SoftRas {
	class Context {
	public:
		Context();
		~Context();

		void init(uint window_width, uint window_height);

		void preDraw();
		void drawTrianglesIndexed(Vertex* vertices, uint* indices, uint amount);
		void postDraw();

		void bindFramebuffer(uint id);
		Framebuffer* getFramebuffer();
		Framebuffer* getFramebuffer(uint id);
		uint createFramebuffer(uint width, uint height, uint color_attachs, bool has_depth);

		// shader is initialized in external code, while framebuffer and texture is initialized by Context
		void bindShader(uint id);
		Shader* getShader();
		Shader* getShader(uint id);
		uint addShader(Shader* shader);

		Texture* getTexture(uint id);
		int createTexture(uint width, uint height, uint comp = 4);
		int createImage(const char* path);

		bool check(uint8 flag);
		void enable(uint8 flag);
		void disable(uint8 flag);

		uvec4 getViewport();
		void setViewport(uvec4 viewport);

	private:
		/* Current status */
		Framebuffer* m_framebuffer = nullptr;
		Shader* m_shader = nullptr;

		/* Pipeline status */
		bool b_depth_test;
		bool b_cull_back;
		bool b_cull_front;
		uvec4 m_viewport; // x0, y0, width, height, (0, 0) means left-top

		/* Global resources */
		std::vector<Framebuffer*> m_fbos;
		std::vector<Shader*> m_shaders;
		std::vector<Texture*> m_texs;

		/* for rasterize */
		uint m_vs_out_size;
		float* m_vs_out_block = nullptr;
		float* m_fs_in_block = nullptr;
		bool rasterTriangle(float* v0_buf, float* v1_buf, float* v2_buf);
	};

	extern Context g_ctx;
}