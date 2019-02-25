#pragma once

#include <iostream>

namespace Derpy { namespace System {

	inline void memset32(void* dest, const unsigned int value, unsigned int bytesize){
		unsigned int* target = (unsigned int*)dest;

		unsigned int i = bytesize >> (2 + 3);
		while (i){
			target[0] = value;
			target[1] = value;
			target[2] = value;
			target[3] = value;

			target[4] = value;
			target[5] = value;
			target[6] = value;
			target[7] = value;

			target += 8;
			i -= 1;
		}

		i = (bytesize >> 2) & 7;
		while (i){
			target[0] = value;
			target += 1;
			i -= 1;
		}
	}

} }