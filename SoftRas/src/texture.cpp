#include "texture.h"

#include <math.h>
#include <iostream>
namespace SoftRas {
	Texture::Texture()
	{
	}
	Texture::~Texture()
	{
		if (m_data) {
			delete m_data;
		}
	}
	void Texture::init(uint width, uint height, uint comp, uint8* data)
	{
		m_width = width;
		m_height = height;
		m_comp = comp;
		m_data = data;
	}
	vec4 Texture::sample(float u, float v)
	{
		// repeat pattern
		uint&& x = (uint)(u * m_width) % m_width;
		uint&& y = (uint)((1.0f - v) * m_height) % m_height;
		uint&& offset = (y * m_width + x) * m_comp;
		switch (m_comp)
		{
		case 3:
			return vec4{
				(float)m_data[offset] / 255.0f,
				(float)m_data[offset + 1] / 255.0f,
				(float)m_data[offset + 2] / 255.0f,
				0.0f
			};
		case 4:
			return vec4{
				(float)m_data[offset] / 255.0f,
				(float)m_data[offset + 1] / 255.0f,
				(float)m_data[offset + 2] / 255.0f,
				(float)m_data[offset + 3] / 255.0f
			};
		default:
			return vec4{ 0.0f,0.0f,0.0f,0.0f };
		}
	}
	float Texture::sample_as_float(float u, float v)
	{
		// repeat pattern
		uint&& x = (uint)(u * m_width) % m_width;
		uint&& y = (uint)((1.0f - v) * m_height) % m_height;
		uint&& offset = (y * m_width + x) * m_comp; // m_comp must be 4
		return *(reinterpret_cast<float*>((uint32*)(m_data + offset)));
	}
	vec4 Texture::sample_offset(float u, float v, int offset_x, int offset_y)
	{
		// repeat pattern
		uint&& x = ((uint)(u * m_width) + offset_x) % m_width;
		uint&& y = ((uint)((1.0f - v) * m_height) + offset_y) % m_height;
		uint&& offset = (y * m_width + x) * m_comp;
		switch (m_comp)
		{
		case 3:
			return vec4{
				(float)m_data[offset] / 255.0f,
				(float)m_data[offset + 1] / 255.0f,
				(float)m_data[offset + 2] / 255.0f,
				0.0f
			};
		case 4:
			return vec4{
				(float)m_data[offset] / 255.0f,
				(float)m_data[offset + 1] / 255.0f,
				(float)m_data[offset + 2] / 255.0f,
				(float)m_data[offset + 3] / 255.0f
			};
		default:
			return vec4{ 0.0f,0.0f,0.0f,0.0f };
		}
	}
}