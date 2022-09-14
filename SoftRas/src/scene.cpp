#include "scene.h"

#include <math.h>

namespace SoftRas {
	mat4 Transform::computeMat()
	{
		return translateM(trans).matmul(toMat4(
			rotateZM3(radians(rotate.z)).matmul(rotateYM3(radians(rotate.y))).matmul(rotateXM3(radians(rotate.x)))
		)).matmul(scaleM(scale));
	}
	Camera::Camera()
	{
	}
	Camera::~Camera()
	{
	}
	void Camera::init(vec3 position, vec3 target, vec3 worldup, float fov, float aspect, float near, float far)
	{
		pos = position;
		front = normalize(target - position);
		up = normalize(worldup);
		right = cross(front, up);
		pitch = asinf(front.y);
		yaw = asinf(front.x / cosf(pitch));
		this->fov = fov;
		this->aspect = aspect;
		this->nearz = near;
		this->farz = far;
	}
	mat4 Camera::computeViewMat()
	{
		return lookAt(pos, pos + front, up);
	}
	mat4 Camera::computeProjMat()
	{
		return perspective(radians(fov), aspect, nearz, farz);
	}
	void Camera::move(uint8 direction, float distance)
	{
		pos = mmove(pos, direction, distance, front, right, up);
	}
	void Camera::update()
	{
		front = vec3{ cosf(pitch) * sinf(yaw), sinf(pitch), cosf(pitch) * -cosf(yaw) };
		right = normalize(cross(front, up));
	}

	void Scene::init()
	{
		// textures
		const char* texs[] = {
			"resources/tile_diff.png",
			"resources/tile_spec.png",
			"resources/wood_diff.png",
			"resources/wood_spec.png"
		};

		m_mats.clear();
		Material mat1{ vec3{0.1, 0.8, 0.8}, vec3{0.3, 0.0, 0.0}, g_ctx.createImage(texs[0]), g_ctx.createImage(texs[1]) };
		Material mat2{ vec3{0.8, 0.8, 0.1}, vec3{0.0, 1.0, 0.0}, g_ctx.createImage(texs[2]), g_ctx.createImage(texs[3]) };
		Material mat3{ vec3{1.0, 1.0, 1.0}, vec3{0.0, 1.0, 10.0} };
		m_mats.push_back(mat1);
		m_mats.push_back(mat2);
		m_mats.push_back(mat3);

		m_meshes.clear();
		Mesh ms_floor;
		ms_floor.vertices = {
			{{-6, -0.001, -6}, {0.8, 0.8, 0.8}, {0.0, 1.0, 0.0}, {0.0, 3.0}},
			{{-6, -0.001, 6}, {0.8, 0.8, 0.8}, {0.0, 1.0, 0.0}, {0.0, 0.0}},
			{{6, -0.001, 6}, {0.8, 0.8, 0.8}, {0.0, 1.0, 0.0}, {3.0, 0.0}},
			{{6, -0.001, -6}, {0.8, 0.8, 0.8}, {0.0, 1.0, 0.0}, {3.0, 3.0}}
		};
		ms_floor.indices = {
			0,1,2,
			0,2,3
		};
		m_meshes.push_back(ms_floor);

		Mesh ms_cube;
		ms_cube.vertices = {
			{{-1, 0, 0}, {0.8, 0.8, 0.0}, {0, -1, 0}, {0, 1}},
			{{0, 0, 1}, {0.8, 0.8, 0.0}, {0, -1, 0}, {0, 0}},
			{{1, 0, 0}, {0.8, 0.8, 0.0}, {0, -1, 0}, {1, 0}},
			{{0, 0, -1}, {0.8, 0.8, 0.0}, {0, -1, 0}, {1, 1}},

			{{-1, 1.414, 0}, {0.8, 0.8, 0.0}, {-1, 0, 1}, {0, 1}},
			{{-1, 0, 0}, {0.8, 0.8, 0.0}, {-1, 0, 1}, {0, 0}},
			{{0, 0, 1}, {0.8, 0.8, 0.0}, {-1, 0, 1}, {1, 0}},
			{{0, 1.414, 1}, {0.8, 0.8, 0.0}, {-1, 0, 1}, {1, 1}},

			{{0, 1.414, 1}, {0.8, 0.8, 0.0}, {1, 0, 1}, {0, 1}},
			{{0, 0, 1}, {0.8, 0.8, 0.0}, {1, 0, 1}, {0, 0}},
			{{1, 0, 0}, {0.8, 0.8, 0.0}, {1, 0, 1}, {1, 0}},
			{{1, 1.414, 0}, {0.8, 0.8, 0.0}, {1, 0, 1}, {1, 1}},

			{{1, 1.414, 0}, {0.8, 0.8, 0.0}, {1, 0, -1}, {0, 1}},
			{{1, 0, 0}, {0.8, 0.8, 0.0}, {1, 0, -1}, {0, 0}},
			{{0, 0, -1}, {0.8, 0.8, 0.0}, {1, 0, -1}, {1, 0}},
			{{0, 1.414, -1}, {0.8, 0.8, 0.0}, {1, 0, -1}, {1, 1}},

			{{0, 1.414, -1}, {0.8, 0.8, 0.0}, {-1, 0, -1}, {0, 1}},
			{{0, 0, -1}, {0.8, 0.8, 0.0}, {-1, 0, -1}, {0, 0}},
			{{-1, 0, 0}, {0.8, 0.8, 0.0}, {-1, 0, -1}, {1, 0}},
			{ {-1, 1.414, 0}, {0.8, 0.8, 0.0}, {-1, 0, -1}, {1, 1}},

			{{-1, 1.414, 0}, {0.8, 0.8, 0.0}, {0, 1, 0}, {0, 1}},
			{{0, 1.414, 1}, {0.8, 0.8, 0.0}, {0, 1, 0}, {0, 0}},
			{{1, 1.414, 0}, {0.8, 0.8, 0.0}, {0, 1, 0}, {1, 0}},
			{{0, 1.414, -1}, {0.8, 0.8, 0.0}, {0, 1, 0}, {1, 1}}
		};
		ms_cube.indices = {
			0,2,1,
			0,3,2,
			4,5,6,
			4,6,7,
			8,9,10,
			8,10,11,
			12,13,14,
			12,14,15,
			16,17,18,
			16,18,19,
			20,21,22,
			20,22,23
		};
		m_meshes.push_back(ms_cube);

		m_trans.clear();
		Transform trans1{ {0,0,0},{0,0,0},{1,1,1} };
		Transform trans2{ {0,0,0},{0,0.0,0},{1,1,1} };
		Transform trans3{ {4,4,0},{0,0,0},{0.2,0.2,0.2} };
		m_trans.push_back(trans1);
		m_trans.push_back(trans2);
		m_trans.push_back(trans3);

		m_insts = {
			{0, 0, 0, "floor"},
			{1, 1, 1, "cube"},
			{2, 1, 2, "point light"}
		};

		m_dirlight = { {0.6, 0.6, 0.6}, {1.0, -1.0, -0.5} };
		//m_dirlight = { {1.0, 1.0, 1.0}, {0.0, -1.0, 1.0} };
		m_ptlight = { {7.0f, 7.0f, 7.0f}, {4.0, 4.0, 0.0}, {-1.0, -1.0, 0.0}, {1.0, 1.0, 0.4} };

		m_camera.init({ 0.0, 2.0, 6.0 }, { 0.0, 2.0, 5.0 }, { 0.0, 1.0, 0.0 }, 90.0f, 1.0f, 0.1f, 100.0f);
	}
}