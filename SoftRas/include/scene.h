#pragma once

#include <vector>

#include "context.h"

namespace SoftRas {
	class Material {
	public:
		vec3 diffuse;
		// phong: specular, shininess
		// pbr: roughness, metallic, emissive
		vec3 specular;

		int diff_tex = -1;
		int spec_tex = -1;
		//const char* diff_file = nullptr;
		//const char* spec_file = nullptr;
	};

	class Mesh {
	public:
		std::vector<Vertex> vertices;
		std::vector<uint> indices;
	};

	class Transform {
	public:
		vec3 trans;
		vec3 rotate;
		vec3 scale;

		mat4 computeMat();
	};

	class Camera {
	public:
		Camera();
		~Camera();

		vec3 pos;
		vec3 front;
		vec3 up;
		vec3 right;
		float pitch, yaw;
		float fov, aspect, nearz, farz;

		void init(vec3 position, vec3 target, vec3 worldup, float fov = 45.0f, float aspect = 1.0f, float near = 0.1f, float far = 10.0f);
		mat4 computeViewMat();
		mat4 computeProjMat();
		// 0,1,2,3,4,5 => forward,backward,left,right,up,down
		void move(uint8 direction, float distance);
		void update();
	};

	class DirLight {
	public:
		vec3 color; // intensity
		vec3 dir;
	};

	class PointLight {
	public:
		vec3 color; // intensity
		vec3 pos;
		vec3 dir;
		vec3 decay; // at distance d, intensity*=1.0/(decay.x+decay.y*d+decay.z*d*d)
	};

	class Scene {
	public:
		Scene() {};
		~Scene() {};

		void init();
		void clear();

		// demo scene
		void init_cube_scene();
		void init_nanosuit_scene();

		// change this to load your scene
		void load_floor();
		void load_cube();
		void load_nanosuit();
		void load_dirlight();
		void load_ptlight();
		void load_camera();
		// textures
		const char* src_texs[4] = {
			"../../resources/cube_scene/tile_diff.png",
			"../../resources/cube_scene/tile_spec.png",
			"../../resources/cube_scene/wood_diff.png",
			"../../resources/cube_scene/wood_spec.png"
		};
		const char* nanosuit_dir = "../../resources/nanosuit/";
		const char* nanosuit_obj = "../../resources/nanosuit/nanosuit.obj";
		const char* cubemap_path = "../../resources/skybox.png";

		struct Instance
		{
			uint mat_id;
			uint mesh_id;
			uint trans_id;
			const char* name;
		};

		std::vector<Instance> m_insts;
		std::vector<Material> m_mats;
		std::vector<Mesh> m_meshes;
		std::vector<Transform> m_trans;
		DirLight m_dirlight;
		PointLight m_ptlight;
		Camera m_camera;

		int m_skybox_id = -1;
		Mesh m_sky_cube;

		// scene option
		bool b_has_dirlight = true;
		bool b_has_ptlight = true;
	};
}