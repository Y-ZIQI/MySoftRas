#pragma once

#include "framebuffer.h"
#include "texture.h"

namespace SoftRas {
	struct VSOut {
		float* data;
	};

	struct FSIn
	{
		float* data;
		uint frag_x, frag_y;
	};

	struct FSOut {
		vec4* data;
	};

	struct UniformBlock {
		/**
		* data alloc and free should be done in Construct and Decontruct function in your shader
		*/
		float* f1;
		vec2* f2;
		vec3* f3;
		vec4* f4;
		int* i1;
		ivec2* i2;
		ivec3* i3;
		ivec4* i4;
		uint* u1;
		uvec2* u2;
		uvec3* u3;
		uvec4* u4;
		mat3* m3;
		mat4* m4;
		bool* b;
		// assign t to g_ctx.m_texs is a dangerous method, so t and *t and **t must be read-only
		Texture** t;
	};

	class Shader {
	public:
		Shader();
		~Shader();

		virtual void init(uint vs_out_size);
		/**
		* vertex shader:
		* input vertex defined in maths.h
		* output written in `float* data`, with length m_vs_out_size
		* especially, data[0,1,2,3] is ndc coordinate (x,y,z,w) (like glPosition)
		*/
		virtual void vertexShader(Vertex* vertex, VSOut vs_out) = 0;
		/**
		* fragment shader:
		* input interpolated values `float* data` with length m_vs_out_size
		* especially, data[0,1,2] is ndc coordinate in [-1,1]*[-1,1]*[0,1], data[3] is 1/w
		* then write output value in fbo, it is better to only write (frag_x,frag_y) pixel in fbo
		*/
		//virtual void fragmentShader(FSIn fs_in, Framebuffer* fbo) = 0;
		virtual void fragmentShader(FSIn fs_in, FSOut fs_out) = 0;

		uint getVSOutSize();
		UniformBlock* getVars();

	protected:
		uint m_vs_out_size;
		UniformBlock* m_vars;
	};

	class ScreenShader : public Shader {
	public:
		ScreenShader();
		~ScreenShader();
		/**
		* screen shader does not need a vertex shader
		* FSIn `float* data` contain screen uv, length is 2
		*/
		void vertexShader(Vertex* vertex, VSOut vs_out) final {};
		virtual void fragmentShader(FSIn fs_in, FSOut fs_out) = 0;
	};

	// specified shaders

	class ForwardShader : public Shader {
	public:
		ForwardShader();
		~ForwardShader();
		void vertexShader(Vertex* vertex, VSOut vs_out) override;
		void fragmentShader(FSIn fs_in, FSOut fs_out) override;
	};

	class ShadowMapShader : public Shader {
	public:
		ShadowMapShader();
		~ShadowMapShader();
		void vertexShader(Vertex* vertex, VSOut vs_out) override;
		void fragmentShader(FSIn fs_in, FSOut fs_out) override;
	};

	class PostprocessShader : public ScreenShader {
	public:
		PostprocessShader();
		~PostprocessShader();
		void fragmentShader(FSIn fs_in, FSOut fs_out) override;
	};

	class SkyBoxShader : public Shader {
	public:
		SkyBoxShader();
		~SkyBoxShader();
		void vertexShader(Vertex* vertex, VSOut vs_out) override;
		void fragmentShader(FSIn fs_in, FSOut fs_out) override;
	};
}