#define _CRT_SECURE_NO_WARNINGS
#include "scene.h"

#include <math.h>
#include <vector>
#include <string>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

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
		/*
		m_sky_cube.vertices = {
			{{1.0,1.0,1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{-1.0,1.0,-1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{1.0,1.0,-1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{-1.0,1.0,1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{-1.0,1.0,-1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{1.0,1.0,1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},

			{{1.0,1.0,1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{1.0,1.0,-1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{1.0,-1.0,1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{1.0,-1.0,1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{1.0,1.0,-1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{1.0,-1.0,-1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},

			{{-1.0,1.0,1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{1.0,1.0,1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{-1.0,-1.0,1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{-1.0,-1.0,1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{1.0,1.0,1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{1.0,-1.0,1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},

			{{1.0,-1.0,1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{1.0,-1.0,-1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{-1.0,-1.0,-1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{1.0,-1.0,1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{-1.0,-1.0,-1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{-1.0,-1.0,1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},

			{{-1.0,-1.0,1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{-1.0,-1.0,-1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{-1.0,1.0,-1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{-1.0,-1.0,1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{-1.0,1.0,-1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{-1.0,1.0,1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},

			{{-1.0,-1.0,-1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{1.0,-1.0,-1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{1.0,1.0,-1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{-1.0,-1.0,-1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{1.0,1.0,-1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}},
			{{-1.0,1.0,-1.0}, {0, 0, 0}, {0, 0, 0}, {0, 0}}
		};
		m_sky_cube.indices = {
			0,1,2,
			3,4,5,
			6,7,8,
			9,10,11,
			12,13,14,
			15,16,17,
			18,19,20,
			21,22,23,
			24,25,26,
			27,28,29,
			30,31,32,
			33,34,35
		};
		m_skybox_id = g_ctx.createImage(cubemap_path);
		*/
	}
	void Scene::clear()
	{
		m_meshes.clear();
		m_mats.clear();
		m_trans.clear();
		m_insts.clear();
	}
	void Scene::init_cube_scene()
	{
		clear();
		load_camera();
		load_dirlight();
		load_ptlight();
		load_floor();
		load_cube();
	}
	void Scene::init_nanosuit_scene()
	{
		clear();
		load_camera();
		load_dirlight();
		load_ptlight();
		load_floor();
		load_cube();
		load_nanosuit();
	}
	void Scene::load_floor()
	{
		uint ms_id = m_meshes.size(), mat_id = m_mats.size(), tr_id = m_trans.size();
		Mesh ms_floor;
		ms_floor.vertices = {
			{{-9, -0.001, -9}, {0.8, 0.8, 0.8}, {0.0, 1.0, 0.0}, {0.0, 4.5}},
			{{-9, -0.001, 9}, {0.8, 0.8, 0.8}, {0.0, 1.0, 0.0}, {0.0, 0.0}},
			{{9, -0.001, 9}, {0.8, 0.8, 0.8}, {0.0, 1.0, 0.0}, {4.5, 0.0}},
			{{9, -0.001, -9}, {0.8, 0.8, 0.8}, {0.0, 1.0, 0.0}, {4.5, 4.5}}
		};
		ms_floor.indices = { 0,1,2,0,2,3 };
		m_meshes.push_back(ms_floor);
		Transform trans{ {0,0,0},{0,0,0},{1,1,1} };
		m_trans.push_back(trans);
		Material mat{ vec3{0.8, 0.8, 0.8}, vec3{0.3, 0.0, 0.0}, g_ctx.createImage(src_texs[0]), g_ctx.createImage(src_texs[1]) };
		m_mats.push_back(mat);
		Instance n_inst{ mat_id, ms_id, tr_id, "floor" };
		m_insts.push_back(n_inst);
	}
	void Scene::load_cube()
	{
		uint ms_id = m_meshes.size(), mat_id = m_mats.size(), tr_id = m_trans.size();
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
		Transform trans{ {-1.5,0,0},{0,20.0,0},{1,1,1} };
		m_trans.push_back(trans);
		Material mat{ vec3{0.8, 0.8, 0.1}, vec3{0.0, 1.0, 0.0}, g_ctx.createImage(src_texs[2]), g_ctx.createImage(src_texs[3]) };
		m_mats.push_back(mat);
		Instance n_inst{ mat_id, ms_id, tr_id, "cube1" };
		m_insts.push_back(n_inst);

		// point light cube
		if (b_has_ptlight) {
			Transform trans2{ {-4,4,0},{0,0,0},{0.2,0.2,0.2} };
			m_trans.push_back(trans2);
			Material mat2{ vec3{1.0, 1.0, 1.0}, vec3{0.0, 1.0, 10.0} };
			m_mats.push_back(mat2);
			Instance n_inst2{ mat_id + 1, ms_id, tr_id + 1, "light cube" };
			m_insts.push_back(n_inst2);
		}
	}
	void Scene::load_nanosuit()
	{
		uint ms_id = m_meshes.size(), mat_id = m_mats.size(), tr_id = m_trans.size();
		// load nanosuit
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn, err;
		std::string dir(nanosuit_dir);
		std::string obj_file = dir + nanosuit_obj;
		tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, obj_file.c_str(), dir.c_str());

		Transform trans{ {0.5,0,0},{0,-30,0},{0.25,0.25,0.25} };
		m_trans.push_back(trans);
		for (int i = 0; i < materials.size(); i++) {
			auto& mat = materials[i];
			Material n_mat;
			n_mat.diffuse = vec3{ mat.diffuse[0], mat.diffuse[1] , mat.diffuse[2] };
			n_mat.specular = vec3{ mat.specular[0], mat.specular[1] , 0.0f };
			std::string diff_file = dir + mat.diffuse_texname;
			std::string spec_file = dir + mat.specular_texname;
			if (!mat.diffuse_texname.empty()) {
				n_mat.diff_tex = g_ctx.createImage(diff_file.c_str());
			}
			if (!mat.specular_texname.empty()) {
				n_mat.spec_tex = g_ctx.createImage(spec_file.c_str());
			}
			m_mats.push_back(n_mat);
		}
		for (int i = 0; i < shapes.size(); i++) {
			auto& shape = shapes[i];
			Mesh n_mesh;
			for (int j = 0; j < shape.mesh.indices.size(); j++) {
				auto& idx = shape.mesh.indices[j];
				Vertex v{};
				v.pos = {
					attrib.vertices[3 * idx.vertex_index],
					attrib.vertices[3 * idx.vertex_index + 1],
					attrib.vertices[3 * idx.vertex_index + 2]
				};
				v.color = { 0.0f, 0.0f, 0.0f };
				v.norm = {
					attrib.normals[3 * idx.normal_index],
					attrib.normals[3 * idx.normal_index + 1],
					attrib.normals[3 * idx.normal_index + 2]
				};
				v.uv = {
					attrib.texcoords[2 * idx.texcoord_index],
					attrib.texcoords[2 * idx.texcoord_index + 1],
				};
				n_mesh.vertices.push_back(v);
				n_mesh.indices.push_back(j);
			}
			m_meshes.push_back(n_mesh);
			Instance n_inst;
			n_inst.mesh_id = ms_id + i;
			n_inst.trans_id = tr_id;
			n_inst.mat_id = mat_id + shape.mesh.material_ids[0];
			n_inst.name = strcpy((char*)malloc(shape.name.length() + 1), shape.name.c_str());
			m_insts.push_back(n_inst);
		}
	}
	void Scene::load_dirlight()
	{
		b_has_dirlight = true;
		m_dirlight = { {0.6, 0.6, 0.6}, {1.0, -1.0, -0.5} };
	}
	void Scene::load_ptlight()
	{
		b_has_ptlight = true;
		m_ptlight = { {7.0f, 7.0f, 7.0f}, {-4.0, 4.0, 0.0}, {1.0, -1.0, 0.0}, {1.0, 1.0, 0.4} };
	}
	void Scene::load_camera()
	{
		m_camera.init({ 1.139, 4.678, 3.108 }, { 0.838, 4.211, 2.276 }, { 0.0, 1.0, 0.0 }, 90.0f, 1.0f, 0.5f, 20.0f);
	}
}