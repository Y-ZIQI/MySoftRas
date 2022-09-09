#include "framebuffer.h"

namespace SoftRas {
	void Framebuffer::init(uint id, uint width, uint height)
	{
		m_id = id;
		m_width = width;
		m_height = height;
		m_color_buffers.clear();
		m_depth_buffer = nullptr;
	}
	void Framebuffer::addColorBuffer(uint8 type)
	{
		uint a_id = m_color_buffers.size();
		m_color_buffers.push_back({ nullptr, type });
		if (type != SR_TYPE_NONE) {
			m_color_buffers[a_id].buffer = new uint32[m_width * m_height];
		}
		/*if (type == SR_TYPE_RGBA8) {
			m_color_buffers[a_id].buffer = (void*)(new uint32[m_width * m_height]);
		}
		else if (type == SR_TYPE_RGBA32F) {
			m_color_buffers[a_id].buffer = (void*)(new float[m_width * m_height * 4]);
		}*/
	}
	void Framebuffer::addDepthBuffer()
	{
		if (!m_depth_buffer) {
			m_depth_buffer = new float[m_width * m_height];
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
	uint32 Framebuffer::readPixel(uint id, uint row, uint column)
	{
		if (id < m_color_buffers.size() && row < m_height && column < m_width) {
			return m_color_buffers[id].buffer[row * m_width + column];
		}
		return 0;
	}
	void Framebuffer::setPixel(uint id, uint row, uint column, uint32 value)
	{
		if (id < m_color_buffers.size() && row < m_height && column < m_width) {
			m_color_buffers[id].buffer[row * m_width + column] = value;
		}
	}
	float Framebuffer::readDepth(uint row, uint column)
	{
		if (hasDepthBuffer() && row < m_height && column < m_width) {
			return m_depth_buffer[row * m_width + column];
		}
		return 1.0;
	}
	void Framebuffer::setDepth(uint row, uint column, float value)
	{
		if (hasDepthBuffer() && row < m_height && column < m_width) {
			m_depth_buffer[row * m_width + column] = value;
		}
	}
}