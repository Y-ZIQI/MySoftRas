#include "scene.h"

namespace SoftRas {
	void Scene::init()
	{
		m_meshes.clear();
		Mesh n_mesh;
		n_mesh.vertices = {
			{{-0.5, 0.5, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0}},
			{{-0.5, -0.5, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0}},
			{{0.5, -0.5, 0.0}, {1.0, 1.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0}},
			{{0.5, 0.5, 0.0}, {1.0, 1.0, 1.0}, {0.0, 0.0, 0.0}, {0.0, 0.0}},
		};
		n_mesh.indices = {
			0,1,2,
			0,2,3
		};
	}
}