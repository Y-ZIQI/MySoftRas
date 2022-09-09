#include "renderer.h"

namespace SoftRas {
	void Renderer::init()
	{
		m_scene.init();
	}
	void Renderer::draw()
	{
		for (auto& mesh : m_scene.m_meshes) {
			g_ctx.drawTrianglesIndexed(mesh.vertices.data(), mesh.indices.data(), mesh.indices.size() / 3);
		}
	}
}