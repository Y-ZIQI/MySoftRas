#include "maths.h"

#include <math.h>

namespace SoftRas {
	vec4 vec4::operator+(const vec4& a) const
	{
		return { x + a.x, y + a.y, z + a.z, w + a.w };
	}
	vec4 vec4::operator-(const vec4& a) const
	{
		return { x - a.x, y - a.y, z - a.z, w - a.w };
	}
	vec4 vec4::operator*(const vec4& a) const
	{
		return { x * a.x, y * a.y, z * a.z, w * a.w };
	}
	vec4 vec4::operator/(const vec4& a) const
	{
		return { x / a.x, y / a.y, z / a.z, w / a.w };
	}
	vec3 vec3::operator+(const vec3& a) const
	{
		return { x + a.x, y + a.y, z + a.z };
	}
	vec3 vec3::operator-(const vec3& a) const
	{
		return { x - a.x, y - a.y, z - a.z };
	}
	vec3 vec3::operator*(const vec3& a) const
	{
		return { x * a.x, y * a.y, z * a.z };
	}
	vec3 vec3::operator/(const vec3& a) const
	{
		return { x / a.x, y / a.y, z / a.z };
	}
	vec2 vec2::operator+(const vec2& a) const
	{
		return { x + a.x, y + a.y };
	}
	vec2 vec2::operator-(const vec2& a) const
	{
		return { x - a.x, y - a.y };
	}
	vec2 vec2::operator*(const vec2& a) const
	{
		return { x * a.x, y * a.y };
	}
	vec2 vec2::operator/(const vec2& a) const
	{
		return { x / a.x, y / a.y };
	}
	ivec4 ivec4::operator+(const ivec4& a) const
	{
		return { x + a.x, y + a.y, z + a.z, w + a.w };
	}
	ivec4 ivec4::operator-(const ivec4& a) const
	{
		return { x - a.x, y - a.y, z - a.z, w - a.w };
	}
	ivec4 ivec4::operator*(const ivec4& a) const
	{
		return { x * a.x, y * a.y, z * a.z, w * a.w };
	}
	ivec4 ivec4::operator/(const ivec4& a) const
	{
		return { x / a.x, y / a.y, z / a.z, w / a.w };
	}
	ivec3 ivec3::operator+(const ivec3& a) const
	{
		return { x + a.x, y + a.y, z + a.z };
	}
	ivec3 ivec3::operator-(const ivec3& a) const
	{
		return { x - a.x, y - a.y, z - a.z };
	}
	ivec3 ivec3::operator*(const ivec3& a) const
	{
		return { x * a.x, y * a.y, z * a.z };
	}
	ivec3 ivec3::operator/(const ivec3& a) const
	{
		return { x / a.x, y / a.y, z / a.z };
	}
	ivec2 ivec2::operator+(const ivec2& a) const
	{
		return { x + a.x, y + a.y };
	}
	ivec2 ivec2::operator-(const ivec2& a) const
	{
		return { x - a.x, y - a.y };
	}
	ivec2 ivec2::operator*(const ivec2& a) const
	{
		return { x * a.x, y * a.y };
	}
	ivec2 ivec2::operator/(const ivec2& a) const
	{
		return { x / a.x, y / a.y };
	}
	uvec4 uvec4::operator+(const uvec4& a) const
	{
		return { x + a.x, y + a.y, z + a.z, w + a.w };
	}
	uvec4 uvec4::operator-(const uvec4& a) const
	{
		return { x - a.x, y - a.y, z - a.z, w - a.w };
	}
	uvec4 uvec4::operator*(const uvec4& a) const
	{
		return { x * a.x, y * a.y, z * a.z, w * a.w };
	}
	uvec4 uvec4::operator/(const uvec4& a) const
	{
		return { x / a.x, y / a.y, z / a.z, w / a.w };
	}
	uvec3 uvec3::operator+(const uvec3& a) const
	{
		return { x + a.x, y + a.y, z + a.z };
	}
	uvec3 uvec3::operator-(const uvec3& a) const
	{
		return { x - a.x, y - a.y, z - a.z };
	}
	uvec3 uvec3::operator*(const uvec3& a) const
	{
		return { x * a.x, y * a.y, z * a.z };
	}
	uvec3 uvec3::operator/(const uvec3& a) const
	{
		return { x / a.x, y / a.y, z / a.z };
	}
	uvec2 uvec2::operator+(const uvec2& a) const
	{
		return { x + a.x, y + a.y };
	}
	uvec2 uvec2::operator-(const uvec2& a) const
	{
		return { x - a.x, y - a.y };
	}
	uvec2 uvec2::operator*(const uvec2& a) const
	{
		return { x * a.x, y * a.y };
	}
	uvec2 uvec2::operator/(const uvec2& a) const
	{
		return { x / a.x, y / a.y };
	}

	mat4 mat4::operator+(const mat4& a) const
	{
		return { {
			{m[0][0] + a.m[0][0], m[0][1] + a.m[0][1], m[0][2] + a.m[0][2], m[0][3] + a.m[0][3]},
			{m[1][0] + a.m[1][0], m[1][1] + a.m[1][1], m[1][2] + a.m[1][2], m[1][3] + a.m[1][3]},
			{m[2][0] + a.m[2][0], m[2][1] + a.m[2][1], m[2][2] + a.m[2][2], m[2][3] + a.m[2][3]},
			{m[3][0] + a.m[3][0], m[3][1] + a.m[3][1], m[3][2] + a.m[3][2], m[3][3] + a.m[3][3]}
		} };
	}
	mat4 mat4::operator-(const mat4& a) const
	{
		return { {
			{m[0][0] - a.m[0][0], m[0][1] - a.m[0][1], m[0][2] - a.m[0][2], m[0][3] - a.m[0][3]},
			{m[1][0] - a.m[1][0], m[1][1] - a.m[1][1], m[1][2] - a.m[1][2], m[1][3] - a.m[1][3]},
			{m[2][0] - a.m[2][0], m[2][1] - a.m[2][1], m[2][2] - a.m[2][2], m[2][3] - a.m[2][3]},
			{m[3][0] - a.m[3][0], m[3][1] - a.m[3][1], m[3][2] - a.m[3][2], m[3][3] - a.m[3][3]}
		} };
	}
	mat4 mat4::operator*(const mat4& a) const
	{
		return { {
			{m[0][0] * a.m[0][0], m[0][1] * a.m[0][1], m[0][2] * a.m[0][2], m[0][3] * a.m[0][3]},
			{m[1][0] * a.m[1][0], m[1][1] * a.m[1][1], m[1][2] * a.m[1][2], m[1][3] * a.m[1][3]},
			{m[2][0] * a.m[2][0], m[2][1] * a.m[2][1], m[2][2] * a.m[2][2], m[2][3] * a.m[2][3]},
			{m[3][0] * a.m[3][0], m[3][1] * a.m[3][1], m[3][2] * a.m[3][2], m[3][3] * a.m[3][3]}
		} };
	}
	mat4 mat4::operator/(const mat4& a) const
	{
		return { {
			{m[0][0] / a.m[0][0], m[0][1] / a.m[0][1], m[0][2] / a.m[0][2], m[0][3] / a.m[0][3]},
			{m[1][0] / a.m[1][0], m[1][1] / a.m[1][1], m[1][2] / a.m[1][2], m[1][3] / a.m[1][3]},
			{m[2][0] / a.m[2][0], m[2][1] / a.m[2][1], m[2][2] / a.m[2][2], m[2][3] / a.m[2][3]},
			{m[3][0] / a.m[3][0], m[3][1] / a.m[3][1], m[3][2] / a.m[3][2], m[3][3] / a.m[3][3]}
		} };
	}
	mat4 mat4::matmul(const mat4& a) const
	{
		return { {
			{
				m[0][0] * a.m[0][0] + m[0][1] * a.m[1][0] + m[0][2] * a.m[2][0] + m[0][3] * a.m[3][0],
				m[0][0] * a.m[0][1] + m[0][1] * a.m[1][1] + m[0][2] * a.m[2][1] + m[0][3] * a.m[3][1],
				m[0][0] * a.m[0][2] + m[0][1] * a.m[1][2] + m[0][2] * a.m[2][2] + m[0][3] * a.m[3][2],
				m[0][0] * a.m[0][3] + m[0][1] * a.m[1][3] + m[0][2] * a.m[2][3] + m[0][3] * a.m[3][3]
			},{
				m[1][0] * a.m[0][0] + m[1][1] * a.m[1][0] + m[1][2] * a.m[2][0] + m[1][3] * a.m[3][0],
				m[1][0] * a.m[0][1] + m[1][1] * a.m[1][1] + m[1][2] * a.m[2][1] + m[1][3] * a.m[3][1],
				m[1][0] * a.m[0][2] + m[1][1] * a.m[1][2] + m[1][2] * a.m[2][2] + m[1][3] * a.m[3][2],
				m[1][0] * a.m[0][3] + m[1][1] * a.m[1][3] + m[1][2] * a.m[2][3] + m[1][3] * a.m[3][3]
			},{
				m[2][0] * a.m[0][0] + m[2][1] * a.m[1][0] + m[2][2] * a.m[2][0] + m[2][3] * a.m[3][0],
				m[2][0] * a.m[0][1] + m[2][1] * a.m[1][1] + m[2][2] * a.m[2][1] + m[2][3] * a.m[3][1],
				m[2][0] * a.m[0][2] + m[2][1] * a.m[1][2] + m[2][2] * a.m[2][2] + m[2][3] * a.m[3][2],
				m[2][0] * a.m[0][3] + m[2][1] * a.m[1][3] + m[2][2] * a.m[2][3] + m[2][3] * a.m[3][3]
			},{
				m[3][0] * a.m[0][0] + m[3][1] * a.m[1][0] + m[3][2] * a.m[2][0] + m[3][3] * a.m[3][0],
				m[3][0] * a.m[0][1] + m[3][1] * a.m[1][1] + m[3][2] * a.m[2][1] + m[3][3] * a.m[3][1],
				m[3][0] * a.m[0][2] + m[3][1] * a.m[1][2] + m[3][2] * a.m[2][2] + m[3][3] * a.m[3][2],
				m[3][0] * a.m[0][3] + m[3][1] * a.m[1][3] + m[3][2] * a.m[2][3] + m[3][3] * a.m[3][3]
			}
		} };
	}
	vec4 mat4::dot(const vec4& a) const
	{
		return {
			m[0][0] * a.x + m[0][1] * a.y + m[0][2] * a.z + m[0][3] * a.w,
			m[1][0] * a.x + m[1][1] * a.y + m[1][2] * a.z + m[1][3] * a.w,
			m[2][0] * a.x + m[2][1] * a.y + m[2][2] * a.z + m[2][3] * a.w,
			m[3][0] * a.x + m[3][1] * a.y + m[3][2] * a.z + m[3][3] * a.w
		};
	}
	vec3 mat4::dot(const vec3& a) const
	{
		return {
			m[0][0] * a.x + m[0][1] * a.y + m[0][2] * a.z,
			m[1][0] * a.x + m[1][1] * a.y + m[1][2] * a.z,
			m[2][0] * a.x + m[2][1] * a.y + m[2][2] * a.z
		};
	}
	mat4 mat4::transpose() const
	{
		return { {
			{m[0][0], m[1][0], m[2][0], m[3][0]},
			{m[0][1], m[1][1], m[2][1], m[3][1]},
			{m[0][2], m[1][2], m[2][2], m[3][2]},
			{m[0][3], m[1][3], m[2][3], m[3][3]}
		} };
	}
	mat3 mat3::operator+(const mat3& a) const
	{
		return { {
			{m[0][0] + a.m[0][0], m[0][1] + a.m[0][1], m[0][2] + a.m[0][2]},
			{m[1][0] + a.m[1][0], m[1][1] + a.m[1][1], m[1][2] + a.m[1][2]},
			{m[2][0] + a.m[2][0], m[2][1] + a.m[2][1], m[2][2] + a.m[2][2]}
		} };
	}
	mat3 mat3::operator-(const mat3& a) const
	{
		return { {
			{m[0][0] - a.m[0][0], m[0][1] - a.m[0][1], m[0][2] - a.m[0][2]},
			{m[1][0] - a.m[1][0], m[1][1] - a.m[1][1], m[1][2] - a.m[1][2]},
			{m[2][0] - a.m[2][0], m[2][1] - a.m[2][1], m[2][2] - a.m[2][2]}
		} };
	}
	mat3 mat3::operator*(const mat3& a) const
	{
		return { {
			{m[0][0] * a.m[0][0], m[0][1] * a.m[0][1], m[0][2] * a.m[0][2]},
			{m[1][0] * a.m[1][0], m[1][1] * a.m[1][1], m[1][2] * a.m[1][2]},
			{m[2][0] * a.m[2][0], m[2][1] * a.m[2][1], m[2][2] * a.m[2][2]}
		} };
	}
	mat3 mat3::operator/(const mat3& a) const
	{
		return { {
			{m[0][0] / a.m[0][0], m[0][1] / a.m[0][1], m[0][2] / a.m[0][2]},
			{m[1][0] / a.m[1][0], m[1][1] / a.m[1][1], m[1][2] / a.m[1][2]},
			{m[2][0] / a.m[2][0], m[2][1] / a.m[2][1], m[2][2] / a.m[2][2]}
		} };
	}
	mat3 mat3::matmul(const mat3& a) const
	{
		return { {
			{
				m[0][0] * a.m[0][0] + m[0][1] * a.m[1][0] + m[0][2] * a.m[2][0],
				m[0][0] * a.m[0][1] + m[0][1] * a.m[1][1] + m[0][2] * a.m[2][1],
				m[0][0] * a.m[0][2] + m[0][1] * a.m[1][2] + m[0][2] * a.m[2][2]
			},{
				m[1][0] * a.m[0][0] + m[1][1] * a.m[1][0] + m[1][2] * a.m[2][0],
				m[1][0] * a.m[0][1] + m[1][1] * a.m[1][1] + m[1][2] * a.m[2][1],
				m[1][0] * a.m[0][2] + m[1][1] * a.m[1][2] + m[1][2] * a.m[2][2]
			},{
				m[2][0] * a.m[0][0] + m[2][1] * a.m[1][0] + m[2][2] * a.m[2][0],
				m[2][0] * a.m[0][1] + m[2][1] * a.m[1][1] + m[2][2] * a.m[2][1],
				m[2][0] * a.m[0][2] + m[2][1] * a.m[1][2] + m[2][2] * a.m[2][2]
			}
		} };
	}
	vec3 mat3::dot(const vec3& a) const
	{
		return {
			m[0][0] * a.x + m[0][1] * a.y + m[0][2] * a.z,
			m[1][0] * a.x + m[1][1] * a.y + m[1][2] * a.z,
			m[2][0] * a.x + m[2][1] * a.y + m[2][2] * a.z
		};
	}
	mat3 mat3::transpose() const
	{
		return { {
			{m[0][0], m[1][0], m[2][0]},
			{m[0][1], m[1][1], m[2][1]},
			{m[0][2], m[1][2], m[2][2]}
		} };
	}

	bool AABB::is_legal()
	{
		return bb_min.x <= bb_max.x && bb_min.y <= bb_max.y && bb_min.z <= bb_max.z;
	}
	void AABB::include(vec3 n_point)
	{
		bb_min = minimum(bb_min, n_point);
		bb_max = maximum(bb_max, n_point);
	}
	void AABB::clamp(vec3 min, vec3 max)
	{
		bb_min = maximum(bb_min, min);
		bb_max = minimum(bb_max, max);
	}
	bool AABB2::is_legal()
	{
		return bb_min.x <= bb_max.x && bb_min.y <= bb_max.y;
	}
	void AABB2::include(vec2 n_point)
	{
		bb_min = minimum(bb_min, n_point);
		bb_max = maximum(bb_max, n_point);
	}
	void AABB2::clamp(vec2 min, vec2 max)
	{
		bb_min = maximum(bb_min, min);
		bb_max = minimum(bb_max, max);
	}

	float minimum(float f1, float f2)
	{
		return f1 < f2 ? f1 : f2;
	}
	vec4 minimum(vec4 v1, vec4 v2)
	{
		return { minimum(v1.x, v2.x), minimum(v1.y, v2.y) , minimum(v1.z, v2.z), minimum(v1.w, v2.w) };
	}
	vec3 minimum(vec3 v1, vec3 v2)
	{
		return { minimum(v1.x, v2.x), minimum(v1.y, v2.y) , minimum(v1.z, v2.z) };
	}
	vec2 minimum(vec2 v1, vec2 v2)
	{
		return { minimum(v1.x, v2.x), minimum(v1.y, v2.y) };
	}
	float maximum(float f1, float f2)
	{
		return f1 < f2 ? f2 : f1;
	}
	vec4 maximum(vec4 v1, vec4 v2)
	{
		return { maximum(v1.x, v2.x), maximum(v1.y, v2.y) , maximum(v1.z, v2.z), maximum(v1.w, v2.w) };
	}
	vec3 maximum(vec3 v1, vec3 v2)
	{
		return { maximum(v1.x, v2.x), maximum(v1.y, v2.y) , maximum(v1.z, v2.z) };
	}
	vec2 maximum(vec2 v1, vec2 v2)
	{
		return { maximum(v1.x, v2.x), maximum(v1.y, v2.y) };
	}
	float clamp(float x, float min, float max)
	{
		return minimum(maximum(x, min), max);
	}
	vec4 clamp(vec4 x, float min, float max)
	{
		return minimum(maximum(x, { min, min, min, min }), { max, max, max, max });
	}
	vec3 clamp(vec3 x, float min, float max)
	{
		return minimum(maximum(x, { min, min, min }), { max, max, max });
	}
	vec2 clamp(vec2 x, float min, float max)
	{
		return minimum(maximum(x, { min, min }), { max, max });
	}
	vec4 clamp(vec4 x, vec4 min, vec4 max)
	{
		return minimum(maximum(x, min), max);
	}
	vec3 clamp(vec3 x, vec3 min, vec3 max)
	{
		return minimum(maximum(x, min), max);
	}
	vec2 clamp(vec2 x, vec2 min, vec2 max)
	{
		return minimum(maximum(x, min), max);
	}

	float dot(vec4 x, vec4 y)
	{
		return x.x * y.x + x.y * y.y + x.z * y.z + x.w * y.w;
	}
	float dot(vec3 x, vec3 y)
	{
		return x.x * y.x + x.y * y.y + x.z * y.z;
	}
	float dot(vec2 x, vec2 y)
	{
		return x.x * y.x + x.y * y.y;
	}
	float lerp(float x0, float x1, float w)
	{
		return (1.0f - w) * x0 + w * x1;
	}
	vec4 lerp(vec4 x0, vec4 x1, float w)
	{
		float&& w0 = 1.0f - w;
		return { w0 * x0.x + w * x1.x, w0 * x0.y + w * x1.y, w0 * x0.z + w * x1.z, w0 * x0.w + w * x1.w };
	}
	vec3 lerp(vec3 x0, vec3 x1, float w)
	{
		float&& w0 = 1.0f - w;
		return { w0 * x0.x + w * x1.x, w0 * x0.y + w * x1.y, w0 * x0.z + w * x1.z };
	}
	vec2 lerp(vec2 x0, vec2 x1, float w)
	{
		float&& w0 = 1.0f - w;
		return { w0 * x0.x + w * x1.x, w0 * x0.y + w * x1.y };
	}
	float interpolate(vec3 w, float attr0, float attr1, float attr2)
	{
		return w.x * attr0 + w.y * attr1 + w.z * attr2;
	}
	vec4 interpolate(vec3 w, vec4 attr0, vec4 attr1, vec4 attr2)
	{
		return  attr0 * vec4{ w.x, w.x, w.x, w.x } + attr1 * vec4{ w.y, w.y, w.y, w.y } + attr2 * vec4{ w.z, w.z, w.z, w.z };
	}
	vec3 interpolate(vec3 w, vec3 attr0, vec3 attr1, vec3 attr2)
	{
		return attr0 * vec3{ w.x, w.x, w.x } + attr1 * vec3{ w.y, w.y, w.y } + attr2 * vec3{ w.z, w.z, w.z };
	}
	vec2 interpolate(vec3 w, vec2 attr0, vec2 attr1, vec2 attr2)
	{
		return attr0 * vec2{ w.x, w.x } + attr1 * vec2{ w.y, w.y } + attr2 * vec2{ w.z, w.z };
	}

	vec3 cross(vec3 a, vec3 b)
	{
		return {
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		};
	}

	float length(vec4 v)
	{
		return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
	}
	float length(vec3 v)
	{
		return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	}
	float length(vec2 v)
	{
		return sqrtf(v.x * v.x + v.y * v.y);
	}

	vec4 normalize(vec4 v)
	{
		float len = maximum(length(v), 1e-10f);
		return { v.x / len, v.y / len, v.z / len, v.w / len };
	}
	vec3 normalize(vec3 v)
	{
		float len = maximum(length(v), 1e-10f);
		return { v.x / len, v.y / len, v.z / len };
	}
	vec2 normalize(vec2 v)
	{
		float len = maximum(length(v), 1e-10f);
		return { v.x / len, v.y / len };
	}

	uint32 color_to_uint32(vec4 color)
	{
		return color_to_uint32((uint8)(255.0 * color.x), (uint8)(255.0 * color.y), (uint8)(255.0 * color.z), (uint8)(255.0 * color.w));
	}
	uint32 color_to_uint32(vec3 color) {
		return color_to_uint32((uint8)(255.0 * color.x), (uint8)(255.0 * color.y), (uint8)(255.0 * color.z));
	}
	uint32 color_to_uint32(uint8 r, uint8 g, uint8 b, uint8 a)
	{
		return ((uint32)a << 24) || ((uint32)r << 16) | ((uint32)g << 8) | b;
	}
	uint32 color_to_uint32(uint8 r, uint8 g, uint8 b){
		return ((uint32)r << 16) | ((uint32)g << 8) | b;
	}
	vec3 uint32_to_color(uint32 n)
	{
		return vec3{
			(float)(n & 0x000000FF) / 255.0f,
			(float)((n & 0x0000FF00) >> 8) / 255.0f,
			(float)((n & 0x00FF0000) >> 16) / 255.0f
		};
	}

	bool insideTriangle(vec2 p, vec2 v0, vec2 v1, vec2 v2)
	{
		vec2 v01 = v1 - v0;
		vec2 v12 = v2 - v1;
		vec2 v20 = v0 - v2;
		vec2 p0 = p - v0;
		vec2 p1 = p - v1;
		vec2 p2 = p - v2;
		float p01 = v01.x * p0.y - v01.y * p0.x;
		float p12 = v12.x * p1.y - v12.y * p1.x;
		float p20 = v20.x * p2.y - v20.y * p2.x;
		return (p01 >= 0.0f && p12 >= 0.0f && p20 >= 0.0f) || (p01 <= 0.0f && p12 <= 0.0f && p20 <= 0.0f);
	}
	bool insideTriangleVectors(vec2 p, vec2 v0, vec2 v1, vec2 v2, vec2 v01, vec2 v12, vec2 v20)
	{
		vec2 p0 = p - v0;
		vec2 p1 = p - v1;
		vec2 p2 = p - v2;
		float p01 = v01.x * p0.y - v01.y * p0.x;
		float p12 = v12.x * p1.y - v12.y * p1.x;
		float p20 = v20.x * p2.y - v20.y * p2.x;
		return (p01 >= 0.0f && p12 >= 0.0f && p20 >= 0.0f) || (p01 <= 0.0f && p12 <= 0.0f && p20 <= 0.0f);
	}
	vec3 barycentric2D(vec2 p, vec2 A, vec2 B, vec2 C)
	{
		vec3 cd{
			(-(p.x - B.x) * (C.y - B.y) + (p.y - B.y) * (C.x - B.x)) / (-(A.x - B.x) * (C.y - B.y) + (A.y - B.y) * (C.x - B.x)),
			(-(p.x - C.x) * (A.y - C.y) + (p.y - C.y) * (A.x - C.x)) / (-(B.x - C.x) * (A.y - C.y) + (B.y - C.y) * (A.x - C.x))
		};
		cd.z = 1.0f - cd.x - cd.y;
		return cd;
	}

	vec4 toVec4(float x)
	{
		return { x, x, x, x };
	}
	vec3 toVec3(float x)
	{
		return { x, x, x };
	}
	vec2 toVec2(float x)
	{
		return { x, x };
	}
	mat3 toMat3(mat4 mt)
	{
		return { {
			{mt.m[0][0], mt.m[0][1], mt.m[0][2]},
			{mt.m[1][0], mt.m[1][1], mt.m[1][2]},
			{mt.m[2][0], mt.m[2][1], mt.m[2][2]}
		} };
	}
	mat4 toMat4(mat3 mt)
	{
		return { {
			{mt.m[0][0], mt.m[0][1], mt.m[0][2], 0.0f},
			{mt.m[1][0], mt.m[1][1], mt.m[1][2], 0.0f},
			{mt.m[2][0], mt.m[2][1], mt.m[2][2], 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}
		} };
	}
	float radians(float angle)
	{
		return angle * 0.01745329252f;
	}
	mat4 translateM(vec3 trans)
	{
		return { {
			{1.0f, 0.0f, 0.0f, trans.x},
			{0.0f, 1.0f, 0.0f, trans.y},
			{0.0f, 0.0f, 1.0f, trans.z},
			{0.0f, 0.0f, 0.0f, 1.0f}
		} };
	}
	mat4 scaleM(vec3 sc)
	{
		return { {
			{sc.x, 0.0f, 0.0f, 0.0f},
			{0.0f, sc.y, 0.0f, 0.0f},
			{0.0f, 0.0f, sc.z, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}
		} };
	}
	mat4 rotateXM(float degree)
	{
		return { {
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, cosf(degree), -sinf(degree), 0.0f},
			{0.0f, sinf(degree), cosf(degree), 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}
		} };
	}
	mat4 rotateYM(float degree)
	{
		return { {
			{cosf(degree), 0.0f, sinf(degree), 0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{-sinf(degree), 0.0f, cosf(degree), 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}
		} };
	}
	mat4 rotateZM(float degree)
	{
		return { {
			{cosf(degree), -sinf(degree), 0.0f, 0.0f},
			{sinf(degree), cosf(degree), 0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}
		} };
	}
	mat3 rotateXM3(float degree)
	{
		return { {
			{1.0f, 0.0f, 0.0f},
			{0.0f, cosf(degree), -sinf(degree)},
			{0.0f, sinf(degree), cosf(degree)}
		} };
	}
	mat3 rotateYM3(float degree)
	{
		return { {
			{cosf(degree), 0.0f, sinf(degree)},
			{0.0f, 1.0f, 0.0f},
			{-sinf(degree), 0.0f, cosf(degree)}
		} };
	}
	mat3 rotateZM3(float degree)
	{
		return { {
			{cosf(degree), -sinf(degree), 0.0f},
			{sinf(degree), cosf(degree), 0.0f},
			{0.0f, 0.0f, 1.0f}
		} };
	}
	mat4 lookAt(vec3 pos, vec3 target, vec3 up)
	{
		vec3 f = normalize(target - pos);
		vec3 r = normalize(cross(f, up));
		vec3 u = cross(r, f);
		return { {
			{r.x, r.y, r.z, -dot(r, pos)},
			{u.x, u.y, u.z, -dot(u, pos)},
			{f.x, f.y, f.z, -dot(f, pos)},
			{0.0f, 0.0f, 0.0f, 1.0f}
		} };
	}
	mat4 perspective(float fov, float aspect, float near, float far)
	{
		float t_2f = tanf(fov / 2.0f);
		return { {
			{1.0f / (aspect * t_2f), 0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f / t_2f, 0.0f, 0.0f},
			{0.0f, 0.0f, far / (far - near), near * far / (near - far)},
			{0.0f, 0.0f, 1.0f, 0.0f}
		} };
	}
	mat4 ortho(float left, float right, float bottom, float top, float near, float far)
	{
		return { {
			{2.0f / (right - left), 0.0f, 0.0f, -(right + left) / (right - left)},
			{0.0f, 2.0f / (top - bottom), 0.0f, -(top + bottom) / (top - bottom)},
			{0.0f, 0.0f, 1.0f / (far - near), -near / (far - near)},
			{0.0f, 0.0f, 0.0f, 1.0f}
		} };
	}

	vec3 F_Shlick(vec3 f0, vec3 f90, float u)
	{
		return f0 + (f90 - f0) * toVec3(powf(1.0f - u, 5.0f));
	}
	float D_GGX(float ggxAlpha, float NdotH)
	{
		float a2 = ggxAlpha * ggxAlpha;
		float d = ((NdotH * a2 - NdotH) * NdotH + 1.0f);
		return m_1_pi * (a2 + m_eps) / (d * d + m_eps);
	}
	float G_SmithGGX(float NdotL, float NdotV, float roughness)
	{
		float r = roughness + 1.0f;
		float k = r * r * 0.125f;
		float GL = NdotL / (NdotL * (1.0f - k) + k);
		float GV = NdotV / (NdotV * (1.0f - k) + k);
		return GL * GV;
	}
	vec3 GGX_BRDF(vec3 F0, float roughness, float NdotH, float NdotL, float NdotV, float LdotH)
	{
		float ggxAlpha = maximum(0.0064, roughness * roughness);
		float D = D_GGX(ggxAlpha, NdotH);
		float G = G_SmithGGX(NdotL, NdotV, roughness);
		vec3 F = F_Shlick(F0, toVec3(1.0f), LdotH);
		return F * toVec3(D * G / (4.0f * NdotL * NdotV + m_eps));
	}
	float ACESTonemapping(float x) {
		return (x * (2.51f * x + 0.03f)) / (x * (2.43f * x + 0.59f) + 0.14f);
	}
	vec3 ACESTonemapping(vec3 color)
	{
		return vec3{ ACESTonemapping(color.x), ACESTonemapping(color.y), ACESTonemapping(color.z) };
	}
	float random(float seed)
	{
		float&& y = sinf(seed * 12.9898f) * 43758.5453123f;
		return y - floorf(y);
	}
	vec3 mmove(vec3 pos, uint8 dir, float dist, vec3 front, vec3 right, vec3 up)
	{
		vec3&& dist3 = vec3{ dist, dist, dist };
		switch (dir)
		{
		case 0: return pos + front * dist3;
		case 1: return pos - front * dist3;
		case 2: return pos - right * dist3;
		case 3: return pos + right * dist3;
		case 4: return pos + up * dist3;
		case 5: return pos - up * dist3;
		}
	}

	vec2 Halton4[4]{
		{0.125f, 0.375f},
		{0.375f, 0.875f},
		{0.625f, 0.125f},
		{0.875f, 0.625f}
	};
}