#pragma once

//#define SR_PARALLEL_RASTERIZE

#ifdef SR_PARALLEL_RASTERIZE
#define SR_MAX_PARALLEL_SIZE 1024
#endif

#define SR_MAX_VERTEX_OUT_SIZE 20

#define SR_TYPE_NONE 0x0000
#define SR_TYPE_RGBA8 0x0001
#define SR_TYPE_RGBA32F 0x0002

#define SR_FLAG_DEPTH 0x0000
#define SR_FLAG_CULL_BACK 0x0001
#define SR_FLAG_CULL_FRONT 0x0002

#define SR_KEY_SPACE 0x20

namespace SoftRas {
	typedef unsigned char uint8;
	typedef unsigned short uint16;
	typedef unsigned int uint32;
	typedef unsigned int uint;
	typedef int int32;
	typedef long long int64;
	typedef unsigned char uchar;

	const float m_eps = 1e-8f;
	const float m_pi = 3.14159265359f;
	const float m_1_pi = 0.318309886184f;
}