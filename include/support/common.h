#ifndef _RM_COMMOM_H
#define _RM_COMMON_H

#include <cassert>

namespace react
{
	namespace support
	{
		template <typename T>
		struct check_type
		{
			static_assert(std::is_arithmetic<T>::value, "T is arithmetic");
			using type = T;
		};

		template <typename T>
		struct check_type_floating
		{
			static_assert(std::numeric_limits<T>::is_iec559, "'check_type_floating' only accepts floating-point types");
			using type = T;
		};

		template <typename T, size_t S>
		struct check_vec_dimension
		{
			static_assert(S >= 2, "vector dimension must be >= 2.");
			using type = T;
		};

		template <typename T, size_t M, size_t N>
		struct check_mat_dimension
		{
			static_assert(M >= 1 && N >= 1, "matrix dimension must be >= 1 x 1");
			using type = T;
		};		
	}

	namespace math
	{
		template<typename T>
		constexpr T pi()
		{
			static_assert(std::numeric_limits<T>::is_iec559, "'pi' only accepts floating-point inputs");
			return static_cast<T>(3.14159265358979323846264338327950288);
		}

		template<typename T>
		constexpr T half_pi()
		{
			static_assert(std::numeric_limits<T>::is_iec559, "'pi' only accepts floating-point inputs");
			return static_cast<T>(3.14159265358979323846264338327950288 / 2.0);
		}

		template<typename T>
		constexpr T pi2()
		{
			static_assert(std::numeric_limits<T>::is_iec559, "'pi' only accepts floating-point inputs");
			return static_cast<T>(3.14159265358979323846264338327950288 * 3.14159265358979323846264338327950288);
		}

		template<typename T>
		constexpr T pi_sqrt()
		{
			static_assert(std::numeric_limits<T>::is_iec559, "'pi' only accepts floating-point inputs");
			return static_cast<T>(sqrt(3.14159265358979323846264338327950288));
		}

		template <typename T>
		const T degrees(const T& radians)
		{
			return radians * (static_cast<T>(180) / pi<T>());
		}

		template <template<typename> class T, typename TT>
		const T<TT> degrees(const typename T<TT>& radians)
		{
			return radians * (static_cast<TT>(180) / pi<TT>());
		}

		template <typename T>
		const T radians(const T& degrees)
		{
			return degrees / (static_cast<T>(180) / pi<T>());
		}

		template <template<typename> class T, typename TT>
		const T<TT> radians(const typename T<TT>& degrees)
		{
			return degrees / (static_cast<TT>(180) / pi<TT>());
		}
	}
}

#endif