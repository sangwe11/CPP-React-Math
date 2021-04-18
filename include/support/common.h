#ifndef _RM_COMMOM_H
#define _RM_COMMON_H

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

		template<typename T, size_t M, size_t N>
		struct check_mat_dimension
		{
			static_assert(M >= 1 && N >= 1, "matrix dimension must be >= 1 x 1");
			using type = T;
		};		
	}
}

#endif