//Material mat1{ vec3{0.0, 0.8, 0.8}, vec3{0.2, 0.0, 0.0} };
//Material mat2{ vec3{0.8, 0.8, 0.0}, vec3{0.2, 1.0, 0.0} };

/*Mesh n_mesh;
n_mesh.vertices = {
	{{-1, 1, 0.9}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0}},
	{{-1, -1, 0.9}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0}},
	{{0.0, 0.0, 0.9}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0}},

	{{-1, 0.0, -4}, {1.0, 1.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0}},
	{{0.0, 0.0, -4}, {1.0, 1.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0}},
	{{0.0, 1, -4}, {1.0, 1.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0}},
};
n_mesh.indices = {
	0,1,2,
	3,4,5
};
m_meshes.push_back(n_mesh);*/

/*Mesh ms_cube;
ms_cube.vertices = {
	{{-1, 0, 0}, {0.8, 0.8, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0}},
	{{0, 0, 1}, {0.8, 0.8, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0}},
	{{1, 0, 0}, {0.8, 0.8, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0}},
	{{0, 0, -1}, {0.8, 0.8, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0}},
	{{-1, 1.414, 0}, {0.8, 0.8, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0}},
	{{0, 1.414, 1}, {0.8, 0.8, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0}},
	{{1, 1.414, 0}, {0.8, 0.8, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0}},
	{{0, 1.414, -1}, {0.8, 0.8, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0}}
};
ms_cube.indices = {
	0,1,2,
	0,2,3,
	4,5,6,
	4,6,7,
	4,0,1,
	4,1,5,
	5,1,2,
	5,2,6,
	6,2,3,
	6,3,7,
	7,3,0,
	7,0,4
};
m_meshes.push_back(ms_cube);*/


/*vec3 f = normalize(target - pos);
vec3 s = normalize(cross(f, up));
vec3 u = cross(s, f);
return { {
	{s.x, u.x, f.x, 0},
	{s.y, u.y, f.y, 0},
	{s.z, u.z, f.z, 0},
	{-dot(s, pos), -dot(u, pos), -dot(f, pos), 1}
} };
vec3 f = normalize(target - pos);
vec3 r = normalize(cross(f, up));
vec3 u = cross(r, f);
return { {
	{r.x, r.y, r.z, -dot(r, pos)},
	{u.x, u.y, u.z, -dot(r, pos)},
	{-f.x, -f.y, -f.z, dot(f, pos)},
	{0, 0, 0, 1}
} };*/


/*float t_2f = tanf(fov / 2.0f);
return { {
	{1.0f / (aspect * t_2f), 0, 0, 0},
	{0, 1.0f / t_2f, 0, 0},
	{0, 0, -far / (far - near), -1},
	{0, 0, -(far * near) / (far - near), 0}
} };
float t_2f = tanf(fov / 2.0f);
return { {
	{1.0f / (aspect * t_2f), 0, 0, 0},
	{0, 1.0f / t_2f, 0, 0},
	{0, 0, near / (near - far), near * far / (near - far)},
	{0, 0, -1, 0}
} };*/

//fbo->setPixel(0, fs_in.frag_x, fs_in.frag_y, color_to_uint32(vec3{ uv.x, uv.y, 0.0 }));
//vec3 out_color{ fs_in.data[4] , fs_in.data[5] , fs_in.data[6] };
//fbo->setPixel(0, fs_in.frag_x, fs_in.frag_y, color_to_uint32(out_color));
//vec3 out_color{ fs_in.data[4] , fs_in.data[5] , fs_in.data[6] };

		/*if (diff_tex) {
			vec4 diff = diff_tex->sample(uv.x, uv.y);
			fbo->setPixel(0, fs_in.frag_x, fs_in.frag_y, color_to_uint32(vec3{ diff.x, diff.y, diff.z }));
			return;
		}*/

		// textures is initialized once before draw(if need textures) in external code
		// t is auto delete in ~Shader, this operation does not delete Texture object, but delete
		// but delete Texture* pointers used in your own shaders

			//reinterpret_cast<void**>(&SoftRas::g_ctx.getFramebuffer()->m_color_buffers[0].buffer),
		//FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		//SoftRas::g_ctx.testPaint();
		//rdr.draw();

#ifdef SR_OPTIMIZED_RASTER
uint v_out_size = m_shader->getVSOutSize();
float* v0_buf = new float[3 * v_out_size];
float* v1_buf = v0_buf + v_out_size;
float* v2_buf = v0_buf + v_out_size * 2;
for (uint i = 0; i < amount; i++) {
	/* Vertex shader */
	uint& id0 = indices[i * 3];
	uint& id1 = indices[i * 3 + 1];
	uint& id2 = indices[i * 3 + 2];
	m_shader->vertexShader(vertices + id0, { v0_buf });
	m_shader->vertexShader(vertices + id1, { v1_buf });
	m_shader->vertexShader(vertices + id2, { v2_buf });

	/* Rasterize */
	vec4& v0 = *((vec4*)v0_buf);
	vec4& v1 = *((vec4*)v1_buf);
	vec4& v2 = *((vec4*)v2_buf);
	// clip proc (only clip z=0 plane)
	uint out_n = 0, out_v[2];
	if (v0.z < 0.0f) {
		out_v[out_n++] = 0;
	}
	if (v1.z < 0.0f) {
		out_v[out_n++] = 1;
	}
	if (v2.z < 0.0f) {
		if (out_n == 2) // 3 point outside
			continue;
		out_v[out_n++] = 2;
	}
	if (out_n > 0) {
		float* pv[3] = { v0_buf , v1_buf , v2_buf };
		if (out_n == 1) {

		}
		else if (out_n == 2) {
			uint in_n = 3 - out_v[0] - out_v[1];
			float w00 = pv[out_v[0]][2] / (pv[out_v[0]][2] - pv[in_n][2]), w01 = 1.0f - w00;
			float w10 = pv[out_v[0]][2] / (pv[out_v[0]][2] - pv[in_n][2]), w11 = 1.0f - w10;
			for (uint i = 0; i < v_out_size; i++) {
				pv[out_v[0]][i] = w00 * pv[in_n][i] + w01 * pv[out_v[0]][i];
				pv[out_v[1]][i] = w10 * pv[in_n][i] + w11 * pv[out_v[1]][i];
			}
		}
	}
	// perspective divide
	v0 = vec4{ v0.x / v0.w, v0.y / v0.w, v0.z / v0.w, 1.0f / v0.w };
	v1 = vec4{ v1.x / v1.w, v1.y / v1.w, v1.z / v1.w, 1.0f / v1.w };
	v2 = vec4{ v2.x / v2.w, v2.y / v2.w, v2.z / v2.w, 1.0f / v2.w };
	// cull face
	vec2 v01 = vec2{ v1.x, v1.y } - vec2{ v0.x, v0.y };
	vec2 v02 = vec2{ v2.x, v2.y } - vec2{ v0.x, v0.y };
	float face_z = v01.x * v02.y - v01.y * v02.x;
	if (b_cull_back && face_z <= 0.0f || !b_cull_back && face_z >= 0.0f) {
		continue;
	}
	// clip space: [-1,1]*[-1,1]*[0,1]
	// (-1, -1) means left-bottom corner
	AABB tri_bb{ {v0.x, v0.y, v0.z}, {v0.x, v0.y, v0.z} };
	tri_bb.include({ v1.x, v1.y, v1.z });
	tri_bb.include({ v2.x, v2.y, v2.z });
	tri_bb.clamp({ -1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f });
	if (!tri_bb.is_legal()) {
		continue;
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
	float* f_buf = new float[v_out_size];
	for (float y = view_bb.bb_min.y; y < view_bb.bb_max.y; y += 1.0f) {
		for (float x = view_bb.bb_min.x; x < view_bb.bb_max.x; x += 1.0f) {
			f_buf[0] = x + 0.5f;
			f_buf[1] = y + 0.5f;
			vec2&& p{ f_buf[0], f_buf[1] };

			const vec3 b_cd = vec3{ p.x,p.x,p.x } *b_cd0 + vec3{ p.y,p.y,p.y } *b_cd1 + b_c0;
			if (b_cd.x < 0.0f || b_cd.y < 0.0f || b_cd.z < 0.0f) {
				continue;
			}
			f_buf[2] = interpolate(b_cd, v0_buf[2], v1_buf[2], v2_buf[2]);
			f_buf[3] = interpolate(b_cd, v0_buf[3], v1_buf[3], v2_buf[3]);
			if (f_buf[2] < 0.0f || f_buf[2] > 1.0f) {
				continue;
			}
			else if (b_depth_test) {
				// depth testing, f_buf[0,1,2] = (x,y,depth)
				if (f_buf[2] < m_framebuffer->readDepth((uint)p.x, (uint)p.y)) {
					m_framebuffer->setDepth((uint)p.x, (uint)p.y, f_buf[2]);
				}
				else {
					continue;
				}
			}
			const float persp = 1.0f / f_buf[3];
			vec3 persp3{ persp, persp, persp };
			persp3 = persp3 * b_cd * vec3{ v0_buf[3], v1_buf[3], v2_buf[3] };

			for (uint i = 3; i < v_out_size; i++) {
				f_buf[i] = interpolate(persp3, v0_buf[i], v1_buf[i], v2_buf[i]);
			}
			/* Fragment Shader */
			m_shader->fragmentShader({ f_buf, (uint)p.x, (uint)p.y }, m_framebuffer);
		}
	}
}
//#else
uint v_out_size = m_shader->getVSOutSize();
float* v0_buf = new float[3 * v_out_size];
float* v1_buf = v0_buf + v_out_size;
float* v2_buf = v0_buf + v_out_size * 2;
for (uint i = 0; i < amount; i++) {
	/* Vertex shader */
	uint& id0 = indices[i * 3];
	uint& id1 = indices[i * 3 + 1];
	uint& id2 = indices[i * 3 + 2];
	m_shader->vertexShader(vertices + id0, { v0_buf });
	m_shader->vertexShader(vertices + id1, { v1_buf });
	m_shader->vertexShader(vertices + id2, { v2_buf });

	// perspective divide and clip proc
	*(vec4*)v0_buf = vec4{ v0_buf[0] / v0_buf[3], v0_buf[1] / v0_buf[3], v0_buf[2] / v0_buf[3], 1.0f / v0_buf[3] };
	*(vec4*)v1_buf = vec4{ v1_buf[0] / v1_buf[3], v1_buf[1] / v1_buf[3], v1_buf[2] / v1_buf[3], 1.0f / v1_buf[3] };
	*(vec4*)v2_buf = vec4{ v2_buf[0] / v2_buf[3], v2_buf[1] / v2_buf[3], v2_buf[2] / v2_buf[3], 1.0f / v2_buf[3] };
	/* Rasterize */
	vec3& v0 = *((vec3*)v0_buf);
	vec3& v1 = *((vec3*)v1_buf);
	vec3& v2 = *((vec3*)v2_buf);
	// cull face
	vec2 v01 = vec2{ v1.x, v1.y } - vec2{ v0.x, v0.y };
	vec2 v02 = vec2{ v2.x, v2.y } - vec2{ v0.x, v0.y };
	float face_z = v01.x * v02.y - v01.y * v02.x;
	if (b_cull_back && face_z <= 0.0f || !b_cull_back && face_z >= 0.0f) {
		continue;
	}
	// clip space: [-1,1]*[-1,1]*[0,1]
	// (-1, -1) means left-bottom corner
	AABB tri_bb{ v0, v0 };
	tri_bb.include(v1);
	tri_bb.include(v2);
	tri_bb.clamp({ -1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f });
	if (!tri_bb.is_legal()) {
		continue;
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
	vec2 vpv01 = vpv1 - vpv0;
	vec2 vpv12 = vpv2 - vpv1;
	vec2 vpv20 = vpv0 - vpv2;
	// main proc
	float* f_buf = new float[v_out_size];
	for (float y = view_bb.bb_min.y; y < view_bb.bb_max.y; y += 1.0f) {
		for (float x = view_bb.bb_min.x; x < view_bb.bb_max.x; x += 1.0f) {
			vec2 p{ x + 0.5f, y + 0.5f };
			if (insideTriangleVectors(p, vpv0, vpv1, vpv2, vpv01, vpv12, vpv20)) {
				vec3 b_cd = barycentric2D(p, vpv0, vpv1, vpv2);
				for (uint i = 0; i < v_out_size; i++) {
					f_buf[i] = interpolate(b_cd, v0_buf[i], v1_buf[i], v2_buf[i]);
				}
				// depth testing, f_buf[0,1,2] = (x,y,depth)
				if (b_depth_test) {
					if (f_buf[2] < m_framebuffer->readDepth((uint)p.x, (uint)p.y)) {
						m_framebuffer->setDepth((uint)p.x, (uint)p.y, f_buf[2]);
					}
					else {
						continue;
					}
				}
				/* Fragment Shader */
				m_shader->fragmentShader({ f_buf, (uint)p.x, (uint)p.y }, m_framebuffer);
			}
		}
	}
}
#endif // SR_OPTIMIZED_RASTER