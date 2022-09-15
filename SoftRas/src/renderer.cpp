#include "renderer.h"

namespace SoftRas {
	void Renderer::init(uint window_width, uint window_height)
	{
		// init variables
		m_width = window_width;
		m_height = window_height;
		m_frames = 0;
		m_control_obj = 0;
		m_mouse_moving = false;
		memset(m_keys_down, 0, sizeof(m_keys_down));
		memset(m_mouse_down, 0, sizeof(m_mouse_down));

		// init resources
		m_scene.init();
		//m_scene.init_cube_scene();
		m_scene.init_nanosuit_scene();

		// init shader
		Shader* forward_shader = new ForwardShader(); // shader will be auto deleted by g_ctx
		m_shader_id[0] = g_ctx.addShader(forward_shader);
		m_fbo_id[1] = g_ctx.createFramebuffer(window_width, window_height, 0, true);
		m_tex_id[1] = g_ctx.createTexture(window_width, window_height, 4);
		g_ctx.getFramebuffer(m_fbo_id[1])->addColorBuffer(SR_TYPE_NONE, (uint32*)g_ctx.getTexture(m_tex_id[1])->m_data);

		Shader* shadowmap_shader = new ShadowMapShader();
		m_shader_id[1] = g_ctx.addShader(shadowmap_shader);
		m_fbo_id[0] = g_ctx.createFramebuffer(600, 600, 0, false);
		m_tex_id[0] = g_ctx.createTexture(600, 600, 4); // 4*uint8 reinterpret cast a float
		g_ctx.getFramebuffer(m_fbo_id[0])->addDepthBuffer((float*)g_ctx.getTexture(m_tex_id[0])->m_data);

		Shader* postprocess_shader = new PostprocessShader();
		m_shader_id[2] = g_ctx.addShader(postprocess_shader);

		Shader* skybox_shader = new SkyBoxShader();
		m_shader_id[3] = g_ctx.addShader(skybox_shader);

		// init status
		g_ctx.enable(SR_FLAG_DEPTH);
		g_ctx.enable(SR_FLAG_CULL_BACK);
		g_ctx.setViewport({ 0, 0, g_ctx.getFramebuffer(0)->getWidth(), g_ctx.getFramebuffer(0)->getHeight() });
	}
	void Renderer::draw()
	{
		// draw shadow map
		g_ctx.enable(SR_FLAG_CULL_FRONT);
		g_ctx.disable(SR_FLAG_CULL_BACK);
		g_ctx.bindShader(m_shader_id[1]);
		g_ctx.bindFramebuffer(m_fbo_id[0]);
		g_ctx.getFramebuffer()->clearDepth();
		g_ctx.setViewport({ 0, 0, 600, 600 });
		auto& light = m_scene.m_dirlight;
		mat4&& light_view = lookAt({ 0.0f, 0.0f, 0.0f }, light.dir, { 0.0f, 1.0f, 0.0f });
		mat4&& light_proj = ortho(-9.0f, 9.0f, -9.0f, 9.0f, -9.0f, 9.0f);
		mat4&& light_view_proj = light_proj.matmul(light_view);
		g_ctx.getShader()->getVars()->m4[1] = light_view_proj;
		for (auto& inst : m_scene.m_insts) {
			// model transform
			g_ctx.getShader()->getVars()->m4[0] = m_scene.m_trans[inst.trans_id].computeMat();
			// draw mesh
			auto& mesh = m_scene.m_meshes[inst.mesh_id];
			g_ctx.drawTrianglesIndexed(mesh.vertices.data(), mesh.indices.data(), mesh.indices.size() / 3);
		}
		
		// main draw
		g_ctx.enable(SR_FLAG_CULL_BACK);
		g_ctx.disable(SR_FLAG_CULL_FRONT);
		g_ctx.bindShader(m_shader_id[0]);
		if (b_postprocess) {
			g_ctx.bindFramebuffer(m_fbo_id[1]);
		}
		else {
			g_ctx.bindFramebuffer(0);
		}
		g_ctx.getFramebuffer()->clear(0, 0);
		g_ctx.getFramebuffer()->clearDepth();
		g_ctx.setViewport({ 0, 0, 800, 800 });

		Camera& cam = m_scene.m_camera;
		mat4&& view = cam.computeViewMat();
		mat4&& proj = cam.computeProjMat();
		g_ctx.getShader()->getVars()->b[0] = m_scene.b_has_dirlight && b_enable_dirlight;
		g_ctx.getShader()->getVars()->b[1] = m_scene.b_has_ptlight && b_enable_ptlight;
		g_ctx.getShader()->getVars()->b[2] = b_enable_shadow;
		g_ctx.getShader()->getVars()->b[3] = b_soft_shadow;
		g_ctx.getShader()->getVars()->m4[1] = proj.matmul(view);
		g_ctx.getShader()->getVars()->m4[2] = light_view_proj;
		g_ctx.getShader()->getVars()->f3[0] = cam.pos;
		g_ctx.getShader()->getVars()->f3[1] = cam.front;
		g_ctx.getShader()->getVars()->f3[2] = m_scene.m_dirlight.color;
		g_ctx.getShader()->getVars()->f3[3] = m_scene.m_dirlight.dir;
		g_ctx.getShader()->getVars()->f3[4] = m_scene.m_ptlight.color;
		g_ctx.getShader()->getVars()->f3[5] = m_scene.m_ptlight.pos;
		g_ctx.getShader()->getVars()->f3[6] = m_scene.m_ptlight.dir;
		g_ctx.getShader()->getVars()->f3[7] = m_scene.m_ptlight.decay;
		g_ctx.getShader()->getVars()->i1[2] = m_tex_id[0]; // shadowmap

		for (auto& inst : m_scene.m_insts) {
			// model transform
			g_ctx.getShader()->getVars()->m4[0] = m_scene.m_trans[inst.trans_id].computeMat();
			g_ctx.getShader()->getVars()->f3[8] = m_scene.m_trans[inst.trans_id].scale;
			// material
			g_ctx.getShader()->getVars()->f3[9] = m_scene.m_mats[inst.mat_id].diffuse;
			g_ctx.getShader()->getVars()->f3[10] = m_scene.m_mats[inst.mat_id].specular;
			g_ctx.getShader()->getVars()->i1[0] = m_scene.m_mats[inst.mat_id].diff_tex;
			g_ctx.getShader()->getVars()->i1[1] = m_scene.m_mats[inst.mat_id].spec_tex;
			// draw mesh
			auto& mesh = m_scene.m_meshes[inst.mesh_id];
			g_ctx.drawTrianglesIndexed(mesh.vertices.data(), mesh.indices.data(), mesh.indices.size() / 3);
		}

		// skybox
		//view = lookAt({ 0.0f, 0.0f, 0.0f }, cam.front, { 0.0f, 1.0f, 0.0f });
		//g_ctx.bindShader(m_shader_id[3]);
		//g_ctx.bindFramebuffer(0);
		//g_ctx.getShader()->getVars()->m4[0] = proj.matmul(view);
		//g_ctx.getShader()->getVars()->i1[0] = m_scene.m_skybox_id;
		//g_ctx.drawTrianglesIndexed(m_scene.m_sky_cube.vertices.data(), m_scene.m_sky_cube.indices.data(), m_scene.m_sky_cube.indices.size() / 3);

		// postprocess
		if (b_postprocess) {
			g_ctx.bindShader(m_shader_id[2]);
			g_ctx.bindFramebuffer(0);
			g_ctx.getShader()->getVars()->i1[0] = m_tex_id[1];
			g_ctx.getShader()->getVars()->i1[1] = m_postprocess_type;
			g_ctx.drawScreen();
		}
	}
	void Renderer::tick(float duration)
	{
		m_frames++;
		const char move_keys[] = "WSADEQ";
		if (m_control_obj == 0) {
			for (int i = 0; i < 6; i++) {
				if (m_keys_down[move_keys[i]]) {
					m_scene.m_camera.move(i, 2.0f * duration);
				}
			}
		}
		else {
			for (int i = 0; i < 6; i++) {
				if (m_keys_down[move_keys[i]]) {
					m_scene.m_trans[m_scene.m_insts[m_control_obj - 1].trans_id].trans = mmove(m_scene.m_trans[m_scene.m_insts[m_control_obj - 1].trans_id].trans, i, 2.0f * duration);
				}
			}
			if (m_keys_down['Z']) {				
				m_scene.m_trans[m_scene.m_insts[m_control_obj - 1].trans_id].rotate.y -= 9.0 * duration;
			}
			if (m_keys_down['X']) {
				m_scene.m_trans[m_scene.m_insts[m_control_obj - 1].trans_id].rotate.y += 9.0 * duration;
			}
		}
		m_scene.m_camera.yaw += 0.003f * (float)m_mouse_dx;
		m_scene.m_camera.pitch -= 0.003f * (float)m_mouse_dy;
		if (m_scene.m_camera.pitch >= radians(89.0f)) m_scene.m_camera.pitch = radians(89.0f);
		if (m_scene.m_camera.pitch <= radians(-89.0f)) m_scene.m_camera.pitch = radians(-89.0f);
		m_mouse_dx = m_mouse_dy = 0;
		m_scene.m_camera.update();
	}
	void Renderer::keyDown(uint8 key)
	{
		m_keys_down[key] = true;
	}
	void Renderer::keyUp(uint8 key)
	{
		m_keys_down[key] = false;
		if (key == SR_KEY_F1) {
			b_enable_shadow = !b_enable_shadow;
		}
		if (key == SR_KEY_F2) {
			if (b_enable_shadow)
				b_soft_shadow = !b_soft_shadow;
		}
		if (key == SR_KEY_F3) {
			b_postprocess = !b_postprocess;
		}
		if (key == SR_KEY_F4) {
			if (b_postprocess)
				m_postprocess_type = (m_postprocess_type + 1) % 2;
		}
		if (key == SR_KEY_F5) {
			b_enable_dirlight = !b_enable_dirlight;
		}
		if (key == SR_KEY_F6) {
			b_enable_ptlight = !b_enable_ptlight;
		}
		if (key >= '0' && key <= '9' && key - '0' <= m_scene.m_insts.size()) {
			m_control_obj = key - '0';
		}
	}
	void Renderer::mouseDown(uint8 button)
	{
		m_mouse_down[button] = true;
		if (button == 0) {
			m_mouse_moving = true;
			m_control_obj = 0;
		}
	}
	void Renderer::mouseUp(uint8 button)
	{
		m_mouse_down[button] = false;
		if (button == 0) {
			m_mouse_moving = false;
		}
	}
	void Renderer::mouseMove(int x, int y)
	{
		if (m_mouse_moving) {
			m_mouse_dx = x - m_mouse_x;
			m_mouse_dy = y - m_mouse_y;
		}
		m_mouse_x = x;
		m_mouse_y = y;
	}
}