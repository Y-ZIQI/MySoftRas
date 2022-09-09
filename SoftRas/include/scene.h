#pragma once

#include <vector>

#include "maths.h"

namespace SoftRas {
	class Mesh {
	public:
		std::vector<Vertex> vertices;
		std::vector<uint> indices;
	};

	class Camera {
	public:
		vec3 pos;
		vec3 front;
		vec3 up;
		vec3 right;
	};

	class Scene {
	public:
		Scene() {};
		~Scene() {};

		void init();

		std::vector<Mesh> m_meshes;
		Camera m_camera;
	};

}