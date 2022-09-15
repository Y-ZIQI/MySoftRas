#pragma once

//#define SR_PARALLEL_RASTERIZE

#ifdef SR_PARALLEL_RASTERIZE
#define SR_MAX_PARALLEL_SIZE 2048
#endif

#define SR_MAX_VERTEX_OUT_SIZE 20
#define SR_MAX_FRAGMENT_OUT_SIZE 10

#define SR_TYPE_NONE 0x0000
#define SR_TYPE_RGBA8 0x0001
#define SR_TYPE_RGBA32F 0x0002

#define SR_FLAG_DEPTH 0x0000
#define SR_FLAG_CULL_BACK 0x0001
#define SR_FLAG_CULL_FRONT 0x0002
#define SR_FLAG_MSAA 0x0003

#define SR_KEY_SPACE 0x20
#define SR_KEY_F1 0x70
#define SR_KEY_F2 0x71
#define SR_KEY_F3 0x72
#define SR_KEY_F4 0x73
#define SR_KEY_F5 0x74
#define SR_KEY_F6 0x75
#define SR_KEY_F7 0x76
#define SR_KEY_F8 0x77

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
	const float m_1_2pi = 0.1591549431f;
}