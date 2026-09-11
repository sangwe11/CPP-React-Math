#ifndef _RM_COMMON_H
#define _RM_COMMON_H

#include <cassert>
#include <algorithm>
#include <cmath>
#include <limits>
#include <random>
#include <type_traits>

namespace react
{
	namespace support
	{
		template <typename T>
		inline bool approximately_equal(const T& a, const T& b, const T& tolerance)
		{
			assert(tolerance >= 0);
			return std::fabs(a - b) <= tolerance;
		}

		template <typename T>
		inline bool is_unit_length(const T& length_squared)
		{
			return std::fabs(length_squared - static_cast<T>(1)) <=
				std::sqrt(std::numeric_limits<T>::epsilon());
		}

		template <typename T>
		struct check_type_arithmetic
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
		const T<TT> degrees(const T<TT>& radians)
		{
			return radians * (static_cast<TT>(180) / pi<TT>());
		}

		template <typename T>
		const T radians(const T& degrees)
		{
			return degrees / (static_cast<T>(180) / pi<T>());
		}

		template <template<typename> class T, typename TT>
		const T<TT> radians(const T<TT>& degrees)
		{
			return degrees / (static_cast<TT>(180) / pi<TT>());
		}

		inline std::random_device& random_device()
		{
			static std::random_device srd;

			return srd;
		}

		inline std::mt19937& mt19937()
		{
			static std::mt19937 smt(react::math::random_device()());

			return smt;
		}

		inline std::mt19937_64& mt19937_64()
		{
			static std::mt19937_64 smt(react::math::random_device()());

			return smt;
		}

		inline int random(const int& min, const int& max)
		{
			std::uniform_int_distribution<int> irand(min, max);

			return irand(react::math::mt19937());
		}

		inline float random(const float& min, const float& max)
		{
			std::uniform_real_distribution<float> frand(min, max);

			return frand(react::math::mt19937());
		}

		inline double random(const double& min, const double& max)
		{
			std::uniform_real_distribution<double> drand(min, max);

			return drand(react::math::mt19937_64());
		}

	}
}

#endif
