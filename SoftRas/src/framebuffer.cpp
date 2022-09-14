#include "framebuffer.h"

namespace SoftRas {
	Framebuffer::Framebuffer()
	{
		m_color_buffers.clear();
		m_depth_buffer = nullptr;
	}
	Framebuffer::~Framebuffer()
	{
		for (auto attach : m_color_buffers) {
			if (attach.type != SR_TYPE_NONE) {
				delete attach.buffer;
			}
		}
		if (hasDepthBuffer()) {
			delete m_depth_buffer;
		}
	}
	void Framebuffer::init(uint id, uint width, uint height)
	{
		m_id = id;
		m_width = width;
		m_height = height;
	}
	void Framebuffer::addColorBuffer(uint8 type, uint32* ext_buffer)
	{
		if (type == SR_TYPE_NONE) {
			m_color_buffers.push_back({ ext_buffer, type });
		}
		else if (type == SR_TYPE_RGBA8) {
			m_color_buffers.push_back({ new uint32[m_width * m_height], type });
		}
		else {
			// TODO: other types
			/*if (type == SR_TYPE_RGBA32F) {
				m_color_buffers[a_id].buffer = (uint32*)(new float[m_width * m_height * 4]);
			}*/
		}
	}
	void Framebuffer::addDepthBuffer(float* ext_buffer)
	{
		if (!m_depth_buffer) {
			if (ext_buffer) {
				m_depth_buffer = ext_buffer;
			}
			else {
				m_depth_buffer = new float[m_width * m_height];
			}
		}
	}
	Framebuffer::Attach Framebuffer::getColorBuffer(uint id)
	{
		if (id < m_color_buffers.size()) {
			return m_color_buffers[id];
		}
	}
	float* Framebuffer::getDepthBuffer()
	{
		return m_depth_buffer;
	}
	uint Framebuffer::getColorBufferCount()
	{
		return uint(m_color_buffers.size());
	}
	bool Framebuffer::hasDepthBuffer()
	{
		return m_depth_buffer != nullptr;
	}
	uint Framebuffer::getWidth()
	{
		return m_width;
	}
	uint Framebuffer::getHeight()
	{
		return m_height;
	}
	uint32 Framebuffer::readPixel(uint id, uint x, uint y)
	{
		if (id < m_color_buffers.size() && y < m_height && x < m_width) {
			return m_color_buffers[id].buffer[y * m_width + x];
		}
		return 0;
	}
	void Framebuffer::setPixel(uint id, uint x, uint y, uint32 value)
	{
		if (id < m_color_buffers.size() && y < m_height && x < m_width) {
			m_color_buffers[id].buffer[y * m_width + x] = value;
		}
	}
	float Framebuffer::readDepth(uint x, uint y)
	{
		if (hasDepthBuffer() && y < m_height && x < m_width) {
			return m_depth_buffer[y * m_width + x];
		}
		return 1.0;
	}
	void Framebuffer::setDepth(uint x, uint y, float value)
	{
		if (hasDepthBuffer() && y < m_height && x < m_width) {
			m_depth_buffer[y * m_width + x] = value;
		}
	}
	void Framebuffer::clear(uint id, uint32 value)
	{
		if (id < m_color_buffers.size()) {
			for (uint i = 0; i < m_height * m_width; i++) {
				m_color_buffers[id].buffer[i] = value;
			}
		}
	}
	void Framebuffer::clearDepth(float value)
	{
		if (hasDepthBuffer()) {
			for (uint i = 0; i < m_height * m_width; i++) {
				m_depth_buffer[i] = value;
			}
		}
	}
	void Framebuffer::applyExternalBuffer(uint id, uint32* ext_buffer)
	{
		if (id < m_color_buffers.size() && m_color_buffers[id].type == SR_TYPE_NONE) {
			m_color_buffers[id].buffer = ext_buffer;
		}
	}
}