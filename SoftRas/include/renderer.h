#pragma once

#include "context.h"
#include "scene.h"

namespace SoftRas {
	class Renderer {
	public:
		Renderer() {};
		~Renderer() {};

		void init();
		void draw();
		void tick(float duration);

		void keyDown(uint8 key);
		void keyUp(uint8 key);
		void mouseDown(uint8 button);
		void mouseUp(uint8 button);
		void mouseMove(int x, int y);

		Scene m_scene;
		// 0: forward shader
		// 1: shadowmap shader
		uint m_shader_id[10];
		// 0: shadowmap
		uint m_fbo_id[10];
		// 0: shadowmap texture
		uint m_tex_id[10];

		// status
		uint m_frames;
		bool b_enable_shadow = true;
		bool b_soft_shadow = true;
		int m_control_obj;
		bool m_keys_down[256];
		bool m_mouse_moving;
		int m_mouse_x, m_mouse_y;
		int m_mouse_dx, m_mouse_dy;
		bool m_mouse_down[2];
	};

}