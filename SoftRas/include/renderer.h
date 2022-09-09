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

		Scene m_scene;
	};

}