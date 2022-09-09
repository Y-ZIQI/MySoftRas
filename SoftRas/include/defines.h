#pragma once

#define SR_TYPE_NONE 0x0000
#define SR_TYPE_RGBA8 0x0001
#define SR_TYPE_RGBA32F 0x0002

namespace SoftRas {
	typedef unsigned char uint8;
	typedef unsigned short uint16;
	typedef unsigned int uint32;
	typedef unsigned int uint;
	typedef int int32;
	typedef long long int64;
	typedef unsigned char uchar;

	const float m_pi = 3.14159265359f;
}