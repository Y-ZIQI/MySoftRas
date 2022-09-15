#include "context.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#ifdef SR_PARALLEL_RASTERIZE
#include <omp.h>
#endif

namespace SoftRas {
	Context g_ctx;

	Context::Context()
	{
		m_fbos.clear();
		m_shaders.clear();
		m_texs.clear();
	}

	Context::~Context()
	{
		for (auto fbo : m_fbos) {
			delete fbo;
		}
		for (auto shader : m_shaders) {
			delete shader;
		}
		for (auto tex : m_texs) {
			delete tex;
		}
		if (m_vs_out_block) {
			delete m_vs_out_block;
		}
		if (m_fs_in_block) {
			delete m_fs_in_block;
		}
		if (m_fs_out_block) {
			delete m_fs_out_block;
		}
	}

	void Context::init(uint window_width, uint window_height)
	{
		// init framebuffer
		uint fbo0 = createFramebuffer(window_width, window_height, 0, true);
		assert(fbo0 == 0);
		m_fbos[0]->addColorBuffer(SR_TYPE_NONE);
		bindFramebuffer(0);
		// init block buffer
		if (!m_vs_out_block) {
			m_vs_out_block = new float[4 * SR_MAX_VERTEX_OUT_SIZE]; // reserve 4 points since clip proc may generate a new point
		}
		if (!m_fs_in_block) {
#ifdef SR_PARALLEL_RASTERIZE
			m_fs_in_block = new float[SR_MAX_PARALLEL_SIZE * SR_MAX_VERTEX_OUT_SIZE];
#else
			m_fs_in_block = new float[SR_MAX_VERTEX_OUT_SIZE];
#endif
		}
		if (!m_fs_out_block) {
#ifdef SR_PARALLEL_RASTERIZE
			m_fs_out_block = new vec4[SR_MAX_PARALLEL_SIZE * SR_MAX_FRAGMENT_OUT_SIZE];
#else
			m_fs_out_block = new vec4[SR_MAX_FRAGMENT_OUT_SIZE];
#endif
		}
	}

	void Context::drawTrianglesIndexed(Vertex* vertices, uint* indices, uint amount)
	{
		float* vo_p[3];
		vo_p[0] = m_vs_out_block;
		vo_p[1] = m_vs_out_block + m_vs_out_size;
		vo_p[2] = m_vs_out_block + m_vs_out_size * 2;
		for (uint i = 0; i < amount; i++) {
			/* Vertex shader */
			uint& id0 = indices[i * 3];
			uint& id1 = indices[i * 3 + 1];
			uint& id2 = indices[i * 3 + 2];
			m_shader->vertexShader(vertices + id0, { vo_p[0] });
			m_shader->vertexShader(vertices + id1, { vo_p[1] });
			m_shader->vertexShader(vertices + id2, { vo_p[2] });
			vec4& v0 = *((vec4*)vo_p[0]);
			vec4& v1 = *((vec4*)vo_p[1]);
			vec4& v2 = *((vec4*)vo_p[2]);
			// clip proc (only clip z=0 plane)
			uint out_n = 0, out_v[2];
			if (v0.z < 0.0f) { out_v[out_n++] = 0; }
			if (v1.z < 0.0f) { out_v[out_n++] = 1; }
			if (v2.z < 0.0f) {
				if (out_n == 2) continue; // 3 point outside					
				out_v[out_n++] = 2;
			}
			if (out_n == 1) {
				uint in_v[2];
				in_v[0] = (out_v[0] + 1) % 3;
				in_v[1] = (out_v[0] + 2) % 3;
				float* v_buf = m_vs_out_block + m_vs_out_size * 3;
				float w10 = vo_p[out_v[0]][2] / (vo_p[out_v[0]][2] - vo_p[in_v[1]][2]), w11 = 1.0f - w10;
				for (uint i = 0; i < m_vs_out_size; i++) {
					v_buf[i] = w10 * vo_p[in_v[1]][i] + w11 * vo_p[out_v[0]][i];
				}
				float w00 = vo_p[out_v[0]][2] / (vo_p[out_v[0]][2] - vo_p[in_v[0]][2]), w01 = 1.0f - w00;
				for (uint i = 0; i < m_vs_out_size; i++) {
					vo_p[out_v[0]][i] = w00 * vo_p[in_v[0]][i] + w01 * vo_p[out_v[0]][i];
				}
				rasterTriangle(vo_p[out_v[0]], vo_p[in_v[0]], vo_p[in_v[1]]);
				rasterTriangle(vo_p[out_v[0]], vo_p[in_v[1]], v_buf);
				continue;
			}
			else if (out_n == 2) {
				uint in_v = 3 - out_v[0] - out_v[1];
				float w00 = vo_p[out_v[0]][2] / (vo_p[out_v[0]][2] - vo_p[in_v][2]), w01 = 1.0f - w00;
				float w10 = vo_p[out_v[1]][2] / (vo_p[out_v[1]][2] - vo_p[in_v][2]), w11 = 1.0f - w10;
				for (uint i = 0; i < m_vs_out_size; i++) {
					vo_p[out_v[0]][i] = w00 * vo_p[in_v][i] + w01 * vo_p[out_v[0]][i];
					vo_p[out_v[1]][i] = w10 * vo_p[in_v][i] + w11 * vo_p[out_v[1]][i];
				}
			}
			rasterTriangle(vo_p[0], vo_p[1], vo_p[2]);
		}
	}

	bool Context::rasterTriangle(float* v0_buf, float* v1_buf, float* v2_buf)
	{
		// perspective divide
		vec4 v0{ v0_buf[0] / v0_buf[3], v0_buf[1] / v0_buf[3], v0_buf[2] / v0_buf[3], 1.0f / v0_buf[3] };
		vec4 v1{ v1_buf[0] / v1_buf[3], v1_buf[1] / v1_buf[3], v1_buf[2] / v1_buf[3], 1.0f / v1_buf[3] };
		vec4 v2{ v2_buf[0] / v2_buf[3], v2_buf[1] / v2_buf[3], v2_buf[2] / v2_buf[3], 1.0f / v2_buf[3] };
		// cull face
		vec2 v01 = vec2{ v1.x, v1.y } - vec2{ v0.x, v0.y };
		vec2 v02 = vec2{ v2.x, v2.y } - vec2{ v0.x, v0.y };
		float face_z = v01.x * v02.y - v01.y * v02.x;
		if (b_cull_back && face_z <= 0.0f || b_cull_front && face_z >= 0.0f) {
			return false;
		}
		// clip space: [-1,1]*[-1,1]*[0,1]
		// (-1, -1) means left-bottom corner
		AABB tri_bb{ {v0.x, v0.y, v0.z}, {v0.x, v0.y, v0.z} };
		tri_bb.include({ v1.x, v1.y, v1.z });
		tri_bb.include({ v2.x, v2.y, v2.z });
		tri_bb.clamp({ -1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f });
		if (!tri_bb.is_legal()) {
			return false;
		}
		// viewport transform
		uvec4 vp = getViewport();
		AABB2 view_bb{
			{floorf((float)vp.x + (float)vp.z * (tri_bb.bb_min.x + 1.0f) / 2.0f), floorf((float)vp.y + (float)vp.w * (1.0f - tri_bb.bb_max.y) / 2.0f) },
			{ceilf((float)vp.x + (float)vp.z * (tri_bb.bb_max.x + 1.0f) / 2.0f), ceilf((float)vp.y + (float)vp.w * (1.0f - tri_bb.bb_min.y) / 2.0f) }
		};
		view_bb.clamp({ (float)vp.x, (float)vp.y }, { (float)vp.x + (float)vp.z, (float)vp.y + (float)vp.w });
		vec2 vpv0{ (float)vp.x + (float)vp.z * (v0.x + 1.0f) / 2.0f, (float)vp.y + (float)vp.w * (1.0f - v0.y) / 2.0f };
		vec2 vpv1{ (float)vp.x + (float)vp.z * (v1.x + 1.0f) / 2.0f, (float)vp.y + (float)vp.w * (1.0f - v1.y) / 2.0f };
		vec2 vpv2{ (float)vp.x + (float)vp.z * (v2.x + 1.0f) / 2.0f, (float)vp.y + (float)vp.w * (1.0f - v2.y) / 2.0f };
		// pre-interpolate barycentric2D
		const float denom = 1 / ((vpv0.x - vpv2.x) * (vpv1.y - vpv0.y) - (vpv0.x - vpv1.x) * (vpv2.y - vpv0.y));
		const vec3 denom3{ denom, denom, denom };
		const vec3 b_cd0 = denom3 * vec3{ vpv1.y - vpv2.y, vpv2.y - vpv0.y, vpv0.y - vpv1.y };
		const vec3 b_cd1 = denom3 * vec3{ vpv2.x - vpv1.x, vpv0.x - vpv2.x, vpv1.x - vpv0.x };
		const vec3 b_c0 = denom3 * vec3{
			vpv1.x * vpv2.y - vpv2.x * vpv1.y,
			vpv2.x * vpv0.y - vpv0.x * vpv2.y,
			vpv0.x * vpv1.y - vpv1.x * vpv0.y
		};
		// main proc
#ifdef SR_PARALLEL_RASTERIZE
		int miny = (int)(view_bb.bb_min.y + m_eps), maxy = (int)(view_bb.bb_max.y + m_eps);
		#pragma omp parallel for
		for (int iy = miny; iy < maxy; iy++) {
			float y = (float)iy;
			float* f_buf = m_fs_in_block + (uint)(y + m_eps) * m_vs_out_size;
			vec4* f_out_buf = m_fs_out_block + (uint)(y + m_eps) * m_framebuffer->getColorBufferCount();
#else
		float* f_buf = m_fs_in_block;
		vec4* f_out_buf = m_fs_out_block;
		for (float y = view_bb.bb_min.y; y < view_bb.bb_max.y; y += 1.0f) {
#endif
			bool has_inter = false;
			for (float x = view_bb.bb_min.x; x < view_bb.bb_max.x; x += 1.0f) {
				if (b_msaa && b_depth_test && m_framebuffer->hasMSAADepthBuffer()) { // so far MSAA must combine with depth test
					float wt = 0.0f, src_wt = 1.0f;
					for (int n = 0; n < 4; n++) {
						f_buf[0] = x + Halton4[n].x;
						f_buf[1] = y + Halton4[n].y;
						vec2&& p{ f_buf[0], f_buf[1] };
						const vec3 b_cd = vec3{ p.x,p.x,p.x } *b_cd0 + vec3{ p.y,p.y,p.y } *b_cd1 + b_c0;
						if (b_cd.x >= 0.0f && b_cd.y >= 0.0f && b_cd.z >= 0.0f) {
							f_buf[2] = interpolate(b_cd, v0.z, v1.z, v2.z);
							f_buf[3] = interpolate(b_cd, v0.w, v1.w, v2.w);
							if (f_buf[2] >= 0.0f || f_buf[2] <= 1.0f) {
								if (f_buf[2] < m_framebuffer->readMSAADepth((uint)p.x, (uint)p.y, n)) {
									m_framebuffer->setMSAADepth((uint)p.x, (uint)p.y, n, f_buf[2]);
									wt += 0.25f;
									src_wt -= 0.25f;
								}
							}
						}
					}
					if (wt <= m_eps) {
						if (has_inter)
							break;
						continue;
					}
					else {
						has_inter = true;
					}
					f_buf[0] = x + 0.5f;
					f_buf[1] = y + 0.5f;
					vec2&& p{ f_buf[0], f_buf[1] };
					// first interpolate frag.zw then depth test
					const vec3 b_cd = vec3{ p.x,p.x,p.x } *b_cd0 + vec3{ p.y,p.y,p.y } *b_cd1 + b_c0;
					f_buf[2] = interpolate(b_cd, v0.z, v1.z, v2.z);
					f_buf[3] = interpolate(b_cd, v0.w, v1.w, v2.w);
					// interpolate remain props with fixed-barycentric2D
					const float persp = 1.0f / f_buf[3];
					vec3 persp3{ persp, persp, persp };
					persp3 = persp3 * b_cd * vec3{ v0.w, v1.w, v2.w };
					for (uint i = 4; i < m_vs_out_size; i++) {
						f_buf[i] = interpolate(persp3, v0_buf[i], v1_buf[i], v2_buf[i]);
					}
					/* Fragment Shader */
					m_shader->fragmentShader({ f_buf, (uint)p.x, (uint)p.y }, { f_out_buf });
					for (uint n = 0; n < m_framebuffer->getColorBufferCount(); n++) {
						vec3 write_color{ f_out_buf[n].x * f_out_buf[n].w, f_out_buf[n].y * f_out_buf[n].w, f_out_buf[n].z * f_out_buf[n].w };
						vec3 old_color = uint32_to_color(m_framebuffer->readPixel(n, (uint)p.x, (uint)p.y));
						write_color = write_color * toVec3(wt) + old_color * toVec3(src_wt);
						m_framebuffer->setPixel(n, (uint)p.x, (uint)p.y, color_to_uint32(write_color));
					}
				}
				else { // No MSAA
					f_buf[0] = x + 0.5f;
					f_buf[1] = y + 0.5f;
					vec2&& p{ f_buf[0], f_buf[1] };
					// first interpolate frag.zw then depth test
					const vec3 b_cd = vec3{ p.x,p.x,p.x } *b_cd0 + vec3{ p.y,p.y,p.y } *b_cd1 + b_c0;
					if (b_cd.x < 0.0f || b_cd.y < 0.0f || b_cd.z < 0.0f) {
						if (has_inter)
							break;
						continue;
					}
					else {
						has_inter = true;
					}
					f_buf[2] = interpolate(b_cd, v0.z, v1.z, v2.z);
					f_buf[3] = interpolate(b_cd, v0.w, v1.w, v2.w);
					if (f_buf[2] < 0.0f || f_buf[2] > 1.0f) {
						continue;
					}
					else if (b_depth_test && m_framebuffer->hasDepthBuffer()) {
						// depth testing, f_buf[0,1,2] = (x,y,depth)
						if (f_buf[2] < m_framebuffer->readDepth((uint)p.x, (uint)p.y)) {
							m_framebuffer->setDepth((uint)p.x, (uint)p.y, f_buf[2]);
						}
						else {
							continue;
						}
					}
					// interpolate remain props with fixed-barycentric2D
					const float persp = 1.0f / f_buf[3];
					vec3 persp3{ persp, persp, persp };
					persp3 = persp3 * b_cd * vec3{ v0.w, v1.w, v2.w };
					for (uint i = 4; i < m_vs_out_size; i++) {
						f_buf[i] = interpolate(persp3, v0_buf[i], v1_buf[i], v2_buf[i]);
					}
					/* Fragment Shader */
					m_shader->fragmentShader({ f_buf, (uint)p.x, (uint)p.y }, { f_out_buf });
					for (uint n = 0; n < m_framebuffer->getColorBufferCount(); n++) {
						vec3 write_color{ f_out_buf[n].x * f_out_buf[n].w, f_out_buf[n].y * f_out_buf[n].w, f_out_buf[n].z * f_out_buf[n].w };
						m_framebuffer->setPixel(n, (uint)p.x, (uint)p.y, color_to_uint32(write_color));
					}
				}
			}
		}
		return true;
	}

	void Context::drawScreen()
	{
		uvec4 vp = getViewport();
#ifdef SR_PARALLEL_RASTERIZE
		#pragma omp parallel for
		for (int y = vp.y; y < vp.y + vp.w; y++) {
			float* f_buf = m_fs_in_block + (uint)(y + m_eps) * m_vs_out_size;
			vec4* f_out_buf = m_fs_out_block + (uint)(y + m_eps) * m_framebuffer->getColorBufferCount();
#else
		float* f_buf = m_fs_in_block;
		vec4* f_out_buf = m_fs_out_block;
		for (int y = vp.y; y < vp.y + vp.w; y++) {
#endif
			for (int x = vp.x; x < vp.x + vp.z; x++) {
				vec2&& p{ (float)x + 0.5f, (float)y + 0.5f };
				// frag.xy
				f_buf[0] = (p.x - (float)vp.x) / (float)vp.z;
				f_buf[1] = 1.0f - (p.y - (float)vp.y) / (float)vp.w;
				m_shader->fragmentShader({ f_buf, (uint)p.x, (uint)p.y }, { f_out_buf });
				for (uint n = 0; n < m_framebuffer->getColorBufferCount(); n++) {
					vec3 write_color{ f_out_buf[n].x * f_out_buf[n].w, f_out_buf[n].y * f_out_buf[n].w, f_out_buf[n].z * f_out_buf[n].w };
					m_framebuffer->setPixel(n, (uint)p.x, (uint)p.y, color_to_uint32(write_color));
				}
			}
		}
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

	uint Context::createFramebuffer(uint width, uint height, uint color_attachs, bool has_depth)
	{
		uint n_id = m_fbos.size();
		Framebuffer* n_fbo = new Framebuffer;
		n_fbo->init(n_id, width, height);
		for (uint i = 0; i < color_attachs; i++) {
			n_fbo->addColorBuffer(SR_TYPE_RGBA8);
		}
		if (has_depth) {
			n_fbo->addDepthBuffer();
		}
		m_fbos.push_back(n_fbo);
		return n_id;
	}

	void Context::bindShader(uint id)
	{
		if (id < m_shaders.size()) {
			m_shader = m_shaders[id];
			m_vs_out_size = m_shader->getVSOutSize();
			// this line make shader can access m_texs
			m_shader->getVars()->t = m_texs.data();
		}
	}

	Shader* Context::getShader()
	{
		return m_shader;
	}

	Shader* Context::getShader(uint id)
	{
		if (id < m_shaders.size()) {
			return m_shaders[id];
		}
		return nullptr;
	}

	uint Context::addShader(Shader* shader)
	{
		uint id = m_shaders.size();
		m_shaders.push_back(shader);
		return id;
	}

	Texture* Context::getTexture(uint id)
	{
		if (id < m_texs.size()) {
			return m_texs[id];
		}
		return nullptr;
	}

	int Context::createTexture(uint width, uint height, uint comp)
	{
		int id = m_texs.size();
		uint8* data = new uint8[width * height * comp];
		Texture* n_tex = new Texture;
		n_tex->init(width, height, comp, data);
		m_texs.push_back(n_tex);
		return id;
	}

	int Context::createImage(const char* path)
	{
		int id = m_texs.size();
		int width, height, comp;
		uint8* data = stbi_load(path, &width, &height, &comp, 0);
		Texture* n_tex = new Texture;
		n_tex->init(width, height, comp, data);
		m_texs.push_back(n_tex);
		return id;
	}

	bool Context::check(uint8 flag)
	{
		switch (flag) {
		case SR_FLAG_DEPTH:
			return b_depth_test;
		case SR_FLAG_CULL_BACK:
			return b_cull_back;
		case SR_FLAG_CULL_FRONT:
			return b_cull_front;
		case SR_FLAG_MSAA:
			return b_msaa;
		}
	}

	void Context::enable(uint8 flag)
	{
		switch (flag) {
		case SR_FLAG_DEPTH:
			b_depth_test = true; break;
		case SR_FLAG_CULL_BACK:
			b_cull_back = true; break;
		case SR_FLAG_CULL_FRONT:
			b_cull_front = true; break;
		case SR_FLAG_MSAA:
			b_msaa = true; break;
		}
	}

	void Context::disable(uint8 flag)
	{
		switch (flag) {
		case SR_FLAG_DEPTH:
			b_depth_test = false; break;
		case SR_FLAG_CULL_BACK:
			b_cull_back = false; break;
		case SR_FLAG_CULL_FRONT:
			b_cull_front = false; break;
		case SR_FLAG_MSAA:
			b_msaa = false; break;
		}
	}

	uvec4 Context::getViewport()
	{
		return m_viewport;
	}

	void Context::setViewport(uvec4 viewport)
	{
		m_viewport = viewport;
	}
}