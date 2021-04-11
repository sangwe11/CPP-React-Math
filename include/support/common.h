#ifndef _RM_MATRIX_H
#define _RM_MATRIX_H

#include <cassert>

namespace react
{
	namespace support
	{
		template<typename T>
		struct check_type
		{
			static_assert(std::is_arithmetic<T>::value, "T is arithmetic");
			using type = T;
		};

		template<typename T, size_t S>
		struct check_vec_dimension
		{
			static_assert(S >= 2, "vector dimension must be >= 2.");
			using type = T;
		};		
	}
}

#endif