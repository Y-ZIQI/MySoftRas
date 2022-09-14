#pragma once

#include "defines.h"

namespace SoftRas {
	struct vec4
	{
		float x, y, z, w;
		vec4 operator+(const vec4& a)const;
		vec4 operator-(const vec4& a)const;
		vec4 operator*(const vec4& a)const;
		vec4 operator/(const vec4& a)const;
	};
	struct vec3
	{
		float x, y, z;
		vec3 operator+(const vec3& a)const;
		vec3 operator-(const vec3& a)const;
		vec3 operator*(const vec3& a)const;
		vec3 operator/(const vec3& a)const;
	};
	struct vec2
	{
		float x, y;
		vec2 operator+(const vec2& a)const;
		vec2 operator-(const vec2& a)const;
		vec2 operator*(const vec2& a)const;
		vec2 operator/(const vec2& a)const;
	};
	struct ivec4
	{
		int32 x, y, z, w;
		ivec4 operator+(const ivec4& a)const;
		ivec4 operator-(const ivec4& a)const;
		ivec4 operator*(const ivec4& a)const;
		ivec4 operator/(const ivec4& a)const;
	};
	struct ivec3
	{
		int32 x, y, z;
		ivec3 operator+(const ivec3& a)const;
		ivec3 operator-(const ivec3& a)const;
		ivec3 operator*(const ivec3& a)const;
		ivec3 operator/(const ivec3& a)const;
	};
	struct ivec2
	{
		int32 x, y;
		ivec2 operator+(const ivec2& a)const;
		ivec2 operator-(const ivec2& a)const;
		ivec2 operator*(const ivec2& a)const;
		ivec2 operator/(const ivec2& a)const;
	};
	struct uvec4
	{
		uint32 x, y, z, w;
		uvec4 operator+(const uvec4& a)const;
		uvec4 operator-(const uvec4& a)const;
		uvec4 operator*(const uvec4& a)const;
		uvec4 operator/(const uvec4& a)const;
	};
	struct uvec3
	{
		uint32 x, y, z;
		uvec3 operator+(const uvec3& a)const;
		uvec3 operator-(const uvec3& a)const;
		uvec3 operator*(const uvec3& a)const;
		uvec3 operator/(const uvec3& a)const;
	};
	struct uvec2
	{
		uint32 x, y;
		uvec2 operator+(const uvec2& a)const;
		uvec2 operator-(const uvec2& a)const;
		uvec2 operator*(const uvec2& a)const;
		uvec2 operator/(const uvec2& a)const;
	};

	struct mat4 
	{
		float m[4][4];
		mat4 operator+(const mat4& a)const;
		mat4 operator-(const mat4& a)const;
		mat4 operator*(const mat4& a)const;
		mat4 operator/(const mat4& a)const;
		mat4 matmul(const mat4& a)const;
		vec4 dot(const vec4& a)const;
		vec3 dot(const vec3& a)const;
		mat4 transpose()const;
	};

	struct mat3
	{
		float m[3][3];
		mat3 operator+(const mat3& a)const;
		mat3 operator-(const mat3& a)const;
		mat3 operator*(const mat3& a)const;
		mat3 operator/(const mat3& a)const;
		mat3 matmul(const mat3& a)const;
		vec3 dot(const vec3& a)const;
		mat3 transpose()const;
	};

	struct AABB
	{
		vec3 bb_min;
		vec3 bb_max;

		bool is_legal();
		void include(vec3 n_point);
		void clamp(vec3 min, vec3 max);
	};
	struct AABB2
	{
		vec2 bb_min;
		vec2 bb_max;

		bool is_legal();
		void include(vec2 n_point);
		void clamp(vec2 min, vec2 max);
	};

	struct Vertex {
		vec3 pos;
		vec3 color;
		vec3 norm;
		vec2 uv;
	};

	float minimum(float f1, float f2);
	vec4 minimum(vec4 v1, vec4 v2);
	vec3 minimum(vec3 v1, vec3 v2);
	vec2 minimum(vec2 v1, vec2 v2);
	float maximum(float f1, float f2);
	vec4 maximum(vec4 v1, vec4 v2);
	vec3 maximum(vec3 v1, vec3 v2);
	vec2 maximum(vec2 v1, vec2 v2);
	float clamp(float x, float min, float max);
	vec4 clamp(vec4 x, float min, float max);
	vec3 clamp(vec3 x, float min, float max);
	vec2 clamp(vec2 x, float min, float max);
	vec4 clamp(vec4 x, vec4 min, vec4 max);
	vec3 clamp(vec3 x, vec3 min, vec3 max);
	vec2 clamp(vec2 x, vec2 min, vec2 max);
	float dot(vec4 x, vec4 y);
	float dot(vec3 x, vec3 y);
	float dot(vec2 x, vec2 y);
	float lerp(float x0, float x1, float w);
	vec4 lerp(vec4 x0, vec4 x1, float w);
	vec3 lerp(vec3 x0, vec3 x1, float w);
	vec2 lerp(vec2 x0, vec2 x1, float w);
	float interpolate(vec3 w, float attr0, float attr1, float attr2);
	vec4 interpolate(vec3 w, vec4 attr0, vec4 attr1, vec4 attr2);
	vec3 interpolate(vec3 w, vec3 attr0, vec3 attr1, vec3 attr2);
	vec2 interpolate(vec3 w, vec2 attr0, vec2 attr1, vec2 attr2);
	vec3 cross(vec3 a, vec3 b);
	float length(vec4 v);
	float length(vec3 v);
	float length(vec2 v);
	vec4 normalize(vec4 v);
	vec3 normalize(vec3 v);
	vec2 normalize(vec2 v);

	uint32 color_to_uint32(vec3 color);
	uint32 color_to_uint32(uint8 r, uint8 g, uint8 b);

	bool insideTriangle(vec2 p, vec2 v0, vec2 v1, vec2 v2);
	bool insideTriangleVectors(vec2 p, vec2 v0, vec2 v1, vec2 v2, vec2 v01, vec2 v12, vec2 v20);
	vec3 barycentric2D(vec2 p, vec2 A, vec2 B, vec2 C);

	vec4 toVec4(float x);
	vec3 toVec3(float x);
	vec2 toVec2(float x);
	mat3 toMat3(mat4 mt);
	mat4 toMat4(mat3 mt);
	float radians(float angle);
	mat4 translateM(vec3 trans);
	mat4 scaleM(vec3 sc);
	mat4 rotateXM(float degree);
	mat4 rotateYM(float degree);
	mat4 rotateZM(float degree);
	mat3 rotateXM3(float degree);
	mat3 rotateYM3(float degree);
	mat3 rotateZM3(float degree);
	mat4 lookAt(vec3 pos, vec3 target, vec3 up);
	mat4 perspective(float fov, float aspect, float near, float far);
	mat4 ortho(float left, float right, float bottom, float top, float near, float far);
	
	vec3 F_Shlick(vec3 f0, vec3 f90, float u);
	float D_GGX(float ggxAlpha, float NdotH);
	float G_SmithGGX(float NdotL, float NdotV, float roughness);
	vec3 GGX_BRDF(vec3 F0, float roughness, float NdotH, float NdotL, float NdotV, float LdotH);
	float ACESTonemapping(float x);
	vec3 ACESTonemapping(vec3 color);
	float random(float seed);
	// 0,1,2,3,4,5 => forward,backward,left,right,up,down
	vec3 mmove(vec3 pos, uint8 dir, float dist, vec3 front = { 0.0f, 0.0f, -1.0f }, vec3 right = { 1.0f, 0.0f, 0.0f }, vec3 up = { 0.0f, 1.0f, 0.0f });
}