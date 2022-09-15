#include "shader.h"

namespace SoftRas {
	Shader::Shader()
	{
	}
	Shader::~Shader()
	{
	}
	void Shader::init(uint vs_out_size)
	{
		m_vs_out_size = vs_out_size;
	}
	uint Shader::getVSOutSize()
	{
		return m_vs_out_size;
	}
	UniformBlock* Shader::getVars()
	{
		return m_vars;
	}

	ScreenShader::ScreenShader()
	{
		Shader::init(2); // screen uv
	}
	ScreenShader::~ScreenShader()
	{
	}

	// forward shader
	ForwardShader::ForwardShader()
	{
		// out: ndcpos.xyzw, worldpos.xyz, color.xyz, normal.xyz, texcoord.xy
		// out: 4+3+3+3+2=15
		Shader::init(15);
		m_vars = new UniformBlock;
		// model, viewproj, light viewproj
		m_vars->m4 = new mat4[3];
		// camera pos, camera dire
		// dirlight color, direction
		// pointlight color, position, direction, decay
		// scale(for normal transform)
		// diffuse, specular
		m_vars->f3 = new vec3[11];
		// diffuse, specular, shadowmap texture id
		m_vars->i1 = new int[3];
		// has dirlight, has pointlight
		// enable shadow, soft/hard shadow
		m_vars->b = new bool[4];
	}
	ForwardShader::~ForwardShader()
	{
		delete m_vars->m4;
		delete m_vars->f3;
		delete m_vars->i1;
		delete m_vars->b;
		delete m_vars;
	}
	void ForwardShader::vertexShader(Vertex* vertex, VSOut vs_out)
	{
		mat4& model = m_vars->m4[0];
		mat4& viewproj = m_vars->m4[1];
		vec3& sc = m_vars->f3[8];

		vec4 h_pos{ vertex->pos.x, vertex->pos.y, vertex->pos.z, 1.0f };
		vec4 h_world_pos = model.dot(h_pos);
		vec4 np = viewproj.dot(h_world_pos);

		vec4* out_ndc_pos = (vec4*)vs_out.data;
		vec3* out_world_pos = (vec3*)(vs_out.data + 4);
		vec3* out_color = (vec3*)(vs_out.data + 7);
		vec3* out_normal = (vec3*)(vs_out.data + 10);
		vec2* out_texcoord = (vec2*)(vs_out.data + 13);
		*out_ndc_pos = vec4{ np.x, np.y, np.z, np.w };
		*out_world_pos = vec3{ h_world_pos.x, h_world_pos.y, h_world_pos.z };
		*out_color = vertex->color;
		*out_normal = model.dot(vec3{ vertex->norm.x / (sc.x * sc.x), vertex->norm.y / (sc.y * sc.y), vertex->norm.z / (sc.z * sc.z) });
		*out_texcoord = vertex->uv;
	}
	void ForwardShader::fragmentShader(FSIn fs_in, FSOut fs_out)
	{
		vec3 pos{ fs_in.data[4], fs_in.data[5], fs_in.data[6] };
		vec3 norm = normalize(vec3{ fs_in.data[10], fs_in.data[11], fs_in.data[12] });
		vec2 uv{ fs_in.data[13], fs_in.data[14] };
		mat4& lt_viewproj	= m_vars->m4[2];
		vec3& cam_pos		= m_vars->f3[0];
		vec3& cam_dir		= m_vars->f3[1];
		vec3& dirlt_color	= m_vars->f3[2];
		vec3& dirlt_dir		= m_vars->f3[3];
		vec3& ptlt_color	= m_vars->f3[4];
		vec3& ptlt_pos		= m_vars->f3[5];
		vec3& ptlt_dir		= m_vars->f3[6];
		vec3& ptlt_decay	= m_vars->f3[7];
		vec3& diff_uni		= m_vars->f3[9];
		vec3& spec_uni		= m_vars->f3[10];
		int& diff_tex_id	= m_vars->i1[0];
		int& spec_tex_id	= m_vars->i1[1];
		int& shadowmap_id	= m_vars->i1[2];
		bool& has_dirlight	= m_vars->b[0];
		bool& has_ptlight	= m_vars->b[1];
		bool& enable_shadow = m_vars->b[2];
		bool& soft_shadow	= m_vars->b[3];
		Texture* diff_tex	= diff_tex_id >= 0 ? m_vars->t[diff_tex_id] : nullptr;
		Texture* spec_tex	= spec_tex_id >= 0 ? m_vars->t[spec_tex_id] : nullptr;
		Texture* shadowmap	= shadowmap_id >= 0 ? m_vars->t[shadowmap_id] : nullptr;

		vec3 diffuse;
		vec2 specular;
		float emissive = spec_uni.z;
		if (diff_tex) {
			vec4 diff = diff_tex->sample(uv.x, uv.y);
			diffuse = vec3{ diff.x, diff.y, diff.z };
		}
		else {
			diffuse = diff_uni;
		}
		if (spec_tex) {
			vec4 spec = spec_tex->sample(uv.x, uv.y);
			specular = vec2{ spec.x, spec.y };
		}
		else {
			specular = vec2{ spec_uni.x, spec_uni.y };
		}
		specular = vec2{ 1.0f - specular.x, (1.0f - specular.x) * (1.0f - specular.x) * 500.0f };

		vec3 irra{ 0.0f, 0.0f, 0.0f };
		float diff_term, spec_term;
		vec3 V = normalize(cam_pos - pos), L, H;
		if (has_dirlight) {
			// dir light
			const float ambi = 0.1f;
			L = normalize(vec3{ -dirlt_dir.x, -dirlt_dir.y, -dirlt_dir.z });
			diff_term = maximum(dot(norm, L), 0.0f);
			H = normalize(V + L);
			spec_term = powf(maximum(dot(norm, H), 0.0f), specular.y) * specular.x;
			// shadow
			float vis = 1.0f;
			if (enable_shadow && shadowmap) {
				const float bias = 1e-4f;
				vec4&& pos_lt = lt_viewproj.dot(vec4{ pos.x, pos.y, pos.z, 1.0f });
				vec2&& uv_lt = vec2{ pos_lt.x * 0.5f + 0.5f, pos_lt.y * 0.5f + 0.5f };
				if (uv_lt.x >= 0.0f || uv_lt.x <= 1.0f || uv_lt.y >= 0.0f || uv_lt.y < 1.0f) {
					float z_sm = shadowmap->sample_as_float(uv_lt.x, uv_lt.y);
					float z_lt = pos_lt.z / pos_lt.w;
					if (!soft_shadow) {
						if (z_lt > z_sm + bias) {
							vis = 0.0f;
						}
					}
					else {
						// pcss soft shadow
						// light size and sample amount can be changed
						const float light_size = 0.03f;
						const int sample_n1 = 18, sample_n2 = 36;
						const float angles = 12.9898f * m_pi;
						float blk_dep = 0.0f, dg0 = 2.0 * m_pi * random(pos.x + uv.y + diff_term * 100.0f);
						int blk_n = 0;
						for (int i = 0; i < sample_n1; i++) {
							float pc = (float)(i + 1) / (float)sample_n1;
							float dg = angles * pc + dg0;
							float dp = shadowmap->sample_as_float(uv_lt.x + light_size * pc * cosf(dg), uv_lt.y + light_size * pc * sinf(dg));
							if (z_lt > dp + bias) {
								blk_dep += dp;
								blk_n++;
							}
						}
						if (blk_n > 0) {
							blk_dep /= (float)blk_n;
							float penum = (z_lt - blk_dep) / blk_dep;
							if (penum > 0.01f) {
								penum = penum + m_eps;
							}
							float filter = maximum(penum * light_size, 0.003f);
							float nvis = 0.0f;
							for (int i = 0; i < sample_n2; i++) {
								float pc = (float)(i + 1) / (float)sample_n2;
								float dg = angles * pc + dg0;
								float dp = shadowmap->sample_as_float(uv_lt.x + filter * pc * cosf(dg), uv_lt.y + filter * pc * sinf(dg));
								if (z_lt <= dp + bias) {
									nvis += 1.0f;
								}
							}
							vis = nvis / (float)sample_n2;
						}
					}
				}
			}
			irra = irra + vec3{
				(ambi + vis * (diff_term + spec_term)) * dirlt_color.x,
				(ambi + vis * (diff_term + spec_term)) * dirlt_color.y,
				(ambi + vis * (diff_term + spec_term)) * dirlt_color.z
			};
		}
		if (has_ptlight) {
			// point light
			L = ptlt_pos - pos;
			float dist = length(L);
			float decay = ptlt_decay.x + dist * ptlt_decay.y + dist * dist * ptlt_decay.z;
			L = L / vec3{ dist, dist, dist };
			diff_term = maximum(dot(norm, L), 0.0f);
			H = normalize(V + L);
			spec_term = powf(maximum(dot(norm, H), 0.0f), specular.y) * specular.x;
			irra = irra + vec3{
				(diff_term + spec_term) * ptlt_color.x / decay,
				(diff_term + spec_term) * ptlt_color.y / decay,
				(diff_term + spec_term) * ptlt_color.z / decay
			};
		}

		vec3 out_color = (irra + toVec3(emissive)) * diffuse;
		out_color = ACESTonemapping(out_color);
		out_color = clamp(out_color, 0.0f, 1.0f);

		fs_out.data[0] = vec4{ out_color.x, out_color.y, out_color.z, 1.0f };
	}

	// forward shader
	ShadowMapShader::ShadowMapShader()
	{
		// out: ndcpos.xyzw
		Shader::init(4);
		m_vars = new UniformBlock;
		// model, viewprojection
		m_vars->m4 = new mat4[2];
	}
	ShadowMapShader::~ShadowMapShader()
	{
		delete m_vars->m4;
		delete m_vars;
	}
	void ShadowMapShader::vertexShader(Vertex* vertex, VSOut vs_out)
	{
		mat4& model = m_vars->m4[0];
		mat4& viewproj = m_vars->m4[1];

		vec4 h_pos{ vertex->pos.x, vertex->pos.y, vertex->pos.z, 1.0f };
		vec4 np = viewproj.dot(model.dot(h_pos));

		vec4* out_ndc_pos = (vec4*)vs_out.data;
		*out_ndc_pos = vec4{ np.x, np.y, np.z, np.w };
	}
	void ShadowMapShader::fragmentShader(FSIn fs_in, FSOut fs_out)
	{
	}

	PostprocessShader::PostprocessShader()
	{
		m_vars = new UniformBlock;
		// screen tex, process type
		m_vars->i1 = new int[2];
	}
	PostprocessShader::~PostprocessShader()
	{
		delete m_vars->i1;
		delete m_vars;
	}
	void PostprocessShader::fragmentShader(FSIn fs_in, FSOut fs_out)
	{
		vec2 uv{ fs_in.data[0], fs_in.data[1] };
		int& screen_tex_id = m_vars->i1[0];
		int& type = m_vars->i1[1];
		Texture* screen_tex = screen_tex_id >= 0 ? m_vars->t[screen_tex_id] : nullptr;

		vec3 n_color;
		if (type == 0) {
			// blur image
			vec4 color{ 0.0f,0.0f,0.0f,0.0f };
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					color = color + screen_tex->sample_offset(uv.x, uv.y, i, j);
				}
			}
			// texture read order BGRA
			n_color = vec3{ color.z, color.y, color.x } *toVec3(1.0f / 9.0f);
		}
		else if (type == 1) {
			// gray image
			vec4 color = screen_tex->sample(uv.x, uv.y);
			n_color = toVec3(dot(vec3{ color.z, color.y, color.x }, vec3{ 0.2, 0.7, 0.1 }));
		}
		else {
			vec4 color = screen_tex->sample(uv.x, uv.y);
			n_color = vec3{ color.z, color.y, color.x };
		}

		fs_out.data[0] = vec4{ n_color.x, n_color.y, n_color.z, 1.0f };
	}

	SkyBoxShader::SkyBoxShader()
	{
		// out: ndcpos.xyzw, worldpos.xyz
		// out: 4+3=7
		Shader::init(7);
		m_vars = new UniformBlock;
		// viewprojection
		m_vars->m4 = new mat4[1];
		// skybox id
		m_vars->i1 = new int[1];
	}
	SkyBoxShader::~SkyBoxShader()
	{
		delete m_vars->m4;
		delete m_vars->i1;
		delete m_vars;
	}
	void SkyBoxShader::vertexShader(Vertex* vertex, VSOut vs_out)
	{
		mat4& viewproj = m_vars->m4[0];

		vec4 h_pos{ vertex->pos.x, vertex->pos.y, vertex->pos.z, 1.0f };
		vec4 np = viewproj.dot(h_pos);

		vec4* out_ndc_pos = (vec4*)vs_out.data;
		vec3* out_world_pos = (vec3*)(vs_out.data + 4);
		*out_ndc_pos = vec4{ np.x, np.y, np.w - 0.0001f, np.w };
		*out_world_pos = vec3{ h_pos.x, h_pos.y, h_pos.z };
	}
	void SkyBoxShader::fragmentShader(FSIn fs_in, FSOut fs_out)
	{
		vec3 pos{ fs_in.data[4], fs_in.data[5], fs_in.data[6] };
		int& skybox_id = m_vars->i1[0];
		Texture* skybox = skybox_id >= 0 ? m_vars->t[skybox_id] : nullptr;

		vec4 out_color;
		if (skybox) {
			vec2 yaw_pitch{ atanf(pos.x / -pos.z), asin(normalize(pos).y) };
			vec2 uv = yaw_pitch * vec2{ m_1_2pi, m_1_pi } + toVec2(0.5f);
			out_color = skybox->sample(uv.x, uv.y);
		}
		else {
			out_color = { 0.0f, 0.0f, 0.0f, 0.0f };
		}

		fs_out.data[0] = vec4{ out_color.x, out_color.y, out_color.z, 1.0f };
	}
}