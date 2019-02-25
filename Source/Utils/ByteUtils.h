#pragma once

namespace Derpy { namespace Utils {

	class Byteswap{
	public:
		static unsigned short byteswap(unsigned short num) { return ((num & 0xFF) << 8) | ((num & 0xFF00) >> 8); }
		static short byteswap(short num) { return ((num & 0xFF) << 8) | ((num & 0xFF00) >> 8); }
		static unsigned int byteswap(unsigned int num) { return ((num & 0x000000FF) << 24) | ((num & 0xFF000000) >> 24) | ((num & 0x0000FF00) << 8) | ((num & 0x00FF0000) >> 8); }
		static int byteswap(int num) { return ((num & 0x000000FF) << 24) | ((num & 0xFF000000) >> 24) | ((num & 0x0000FF00) << 8) | ((num & 0x00FF0000) >> 8); }
		static float byteswap(float num) { } // TODO
		static unsigned char byteswap(unsigned char num) { return num; }
		static char  byteswap(char  num) { return num; } 
	};


} }