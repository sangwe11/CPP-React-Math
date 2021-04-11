#ifndef _RM_VECTOR_H
#define _RM_VECTOR_H

#include <iostream>
#include <type_traits>
#include <cstring>
#include <limits>
#include <cassert>
#include <algorithm>

#include "common.h"

namespace react
{
	namespace support
	{
		template <size_t S, typename T = float>
		class vector
		{
		private:
			typename check_vec_dimension<T, S>::type cd{};
			typename check_type<T>::type ct{};

		public:
			static const size_t DIMENSION = S;
			using type = T;

			// SFINAE
			template <typename TT>
			using enable_from_vec2 = typename std::enable_if<S >= 2, TT>::type;

			template <typename TT>
			using enable_from_vec3 = typename std::enable_if<S >= 3, TT>::type;

			template <typename TT>
			using enable_from_vec4 = typename std::enable_if<S >= 4, TT>::type;

			// constructors
			vector() : m_data() {}
			explicit vector(const T& a);

			template <typename TT = enable_from_vec4<T>>
			vector(const T& x, const T& y, const T& z, const T& w);

			// element accessors
			inline T& x();
			inline const T& x() const;

			template <typename TT = enable_from_vec2<T>>
			inline T& y();

			template <typename TT = enable_from_vec2<T>>
			inline const T& y() const;

			template <typename TT = enable_from_vec3<T>>
			inline T& z();

			template <typename TT = enable_from_vec3<T>>
			inline const T& z() const;

			template <typename TT = enable_from_vec4<T>>
			inline T& w();

			template <typename TT = enable_from_vec4<T>>
			inline const T& w() const;

			// color accessors
			inline T& r();
			inline const T& r() const;

			template <typename TT = enable_from_vec2<T>>
			inline T& g();

			template <typename TT = enable_from_vec2<T>>
			inline const T& g() const;

			template <typename TT = enable_from_vec3<T>>
			inline T& b();

			template <typename TT = enable_from_vec3<T>>
			inline const T& b() const;

			template <typename TT = enable_from_vec4<T>>
			inline T& a();

			template <typename TT = enable_from_vec4<T>>
			inline const T& a() const;

			// Utility functions
			const T angle(const vector<S, T>& b) const;
			const T dot(const vector<S, T>& v) const;
			const T distance(const vector<S, T>& v) const;
			const T length_squared() const;
			const T length() const;
			const vector<S, T> lerp(const vector<S, T>& b, const T& t) const;
			const vector<S, T> normalized() const;
			const vector<S, T> project(const vector<S, T>& v) const;

			// Modifiers
			vector<S, T>& normalize();

			// Static utility functions
			static const T angle(const vector<S, T>& a, const vector<S, T>& b);
			const static T dot(const vector<S, T>& a, const vector<S, T>& b);
			const static T distance(const vector<S, T>& a, const vector<S, T>& b);
			const static T length_squared(const vector<S, T>& v);
			const static T length(const vector<S, T>& v);
			const static vector<S, T> lerp(const vector<S, T>& a, const vector<S, T>& b, const T& t);
			const static vector<S, T> max(const vector<S, T>& a, const vector<S, T>& b);
			const static vector<S, T> min(const vector<S, T>& a, const vector<S, T>& b);
			const static vector<S, T> normalized(const vector<S, T>& a);
			const static vector<S, T> project(const vector<S, T>& a, const vector<S, T>& b);
			const static vector<S, T> random(const T& min, const T& max);

			// Operators
			inline T& operator[](size_t index);
			const T& operator[](size_t index) const;

			const bool operator==(const vector<S, T>& v) const;
			const bool operator!=(const vector<S, T>& v) const;

			vector<S, T>& operator++();
			vector<S, T>& operator--();

			vector<S, T>& operator+=(const vector<S, T>& v);
			vector<S, T>& operator-=(const vector<S, T>& v);
			vector<S, T>& operator*=(const vector<S, T>& v);
			vector<S, T>& operator/=(const vector<S, T>& v);

			vector<S, T>& operator*=(const T& c);
			vector<S, T>& operator/=(const T& c);

			vector<S, T> operator+(const vector<S, T>& v) const;
			vector<S, T> operator-(const vector<S, T>& v) const;
			vector<S, T> operator*(const vector<S, T>& v) const;
			vector<S, T> operator/(const vector<S, T>& v) const;

			vector<S, T> operator*(const T& c) const;
			vector<S, T> operator/(const T& c) const;

			friend std::ostream& operator<<(std::ostream& out, const vector<S, T>& v)
			{
				for (int i = 0; i < v.DIMENSION; ++i)
					out << v.m_data[i] << ' ';

				return out;
			}

			// General vec defaults
			static const vector<S, T> ONE;
			static const vector<S, T> ZERO;
			static const vector<S, T> INF;
			static const vector<S, T> NEG_INF;

		public:
			T m_data[S];
		};

		template <size_t S, typename T>
		vector<S, T>::vector(const T& a)
		{
			for (int i = 0; i < this->DIMENSION; ++i)
				m_data[i] = a;
		}

		template <size_t S, typename T>
		template <typename TT>
		vector<S, T>::vector(const T& x, const T& y, const T& z, const T& w)
		{
			m_data[0] = x;
			m_data[1] = y;
			m_data[2] = z;
			m_data[3] = w;
		}

		template <size_t S, typename T>
		inline T& vector<S, T>::x()
		{
			return m_data[0];
		}

		template <size_t S, typename T>
		inline const T& vector<S, T>::x() const
		{
			return m_data[0];
		}

		template <size_t S, typename T>
		template <typename TT>
		inline T& vector<S, T>::y()
		{
			return m_data[1];
		}

		template <size_t S, typename T>
		template <typename TT>
		inline const T& vector<S, T>::y() const
		{
			return m_data[1];
		}

		template <size_t S, typename T>
		template <typename TT>
		inline T& vector<S, T>::z()
		{
			return m_data[2];
		}

		template <size_t S, typename T>
		template <typename TT>
		inline const T& vector<S, T>::z() const
		{
			return m_data[2];
		}

		template <size_t S, typename T>
		template <typename TT>
		inline T& vector<S, T>::w()
		{
			return m_data[3];
		}

		template <size_t S, typename T>
		template <typename TT>
		inline const T& vector<S, T>::w() const
		{
			return m_data[3];
		}

		template <size_t S, typename T>
		inline T& vector<S, T>::r()
		{
			return x();
		}

		template <size_t S, typename T>
		inline const T& vector<S, T>::r() const
		{
			return x();
		}

		template <size_t S, typename T>
		template <typename TT>
		inline T& vector<S, T>::g()
		{
			return y();
		}

		template <size_t S, typename T>
		template <typename TT>
		inline const T& vector<S, T>::g() const
		{
			return y();
		}


		template <size_t S, typename T>
		template <typename TT>
		inline T& vector<S, T>::b()
		{
			return z();
		}

		template <size_t S, typename T>
		template <typename TT>
		inline const T& vector<S, T>::b() const
		{
			return z();
		}

		template <size_t S, typename T>
		template <typename TT>
		inline T& vector<S, T>::a()
		{
			return w();
		}

		template <size_t S, typename T>
		template <typename TT>
		inline const T& vector<S, T>::a() const
		{
			return w();
		}

		template <size_t S, typename T>
		inline T& vector<S, T>::operator[](size_t index)
		{
#ifndef _REACT_NO_SAFE_ACCESSORS
			assert(S > index);
#endif
			return m_data[index];
		}

		template <size_t S, typename T>
		const T& vector<S, T>::operator[](size_t index) const
		{
#ifndef _REACT_NO_SAFE_ACCESSORS
			assert(S > index);
#endif
			return m_data[index];
		}

		template <size_t S, typename T>
		const bool vector<S, T>::operator==(const vector<S, T>& other) const
		{
			return std::memcmp(m_data, other.m_data, sizeof(m_data)) == 0;
		}

		template <size_t S, typename T>
		const bool vector<S, T>::operator!=(const vector<S, T>& other) const
		{
			return !(*this == other);
		}

		template <size_t S, typename T>
		vector<S, T>& vector<S, T>::operator++()
		{
			for (int i = 0; i < this->DIMENSION; ++i)
				m_data[i]++;

			return *this;
		}

		template <size_t S, typename T>
		vector<S, T>& vector<S, T>::operator--()
		{
			for (int i = 0; i < this->DIMENSION; ++i)
				m_data[i]--;

			return *this;
		}

		template <size_t S, typename T>
		vector<S, T>& vector<S, T>::operator+=(const vector<S, T>& v)
		{
			for (int i = 0; i < this->DIMENSION; ++i)
				m_data[i] += v.m_data[i];

			return *this;
		}

		template <size_t S, typename T>
		vector<S, T>& vector<S, T>::operator-=(const vector<S, T>& v)
		{
			for (int i = 0; i < this->DIMENSION; ++i)
				m_data[i] -= v.m_data[i];

			return *this;
		}

		template <size_t S, typename T>
		vector<S, T>& vector<S, T>::operator*=(const vector<S, T>& v)
		{
			for (int i = 0; i < this->DIMENSION; ++i)
				m_data[i] *= v.m_data[i];

			return *this;
		}

		template <size_t S, typename T>
		vector<S, T>& vector<S, T>::operator/=(const vector<S, T>& v)
		{
			for (int i = 0; i < this->DIMENSION; ++i)
				m_data[i] /= v.m_data[i];

			return *this;
		}

		template <size_t S, typename T>
		vector<S, T>& vector<S, T>::operator*=(const T& c)
		{
			for (int i = 0; i < this->DIMENSION; ++i)
				m_data[i] *= c;

			return *this;
		}

		template <size_t S, typename T>
		vector<S, T>& vector<S, T>::operator/=(const T& c)
		{
			for (int i = 0; i < this->DIMENSION; ++i)
				m_data[i] /= c;

			return *this;
		}

		template <size_t S, typename T>
		vector<S, T> vector<S, T>::operator+(const vector<S, T>& v) const
		{
			vector<S, T> tmp = v;
			tmp += *this;
			return tmp;
		}

		template <size_t S, typename T>
		vector<S, T> vector<S, T>::operator-(const vector<S, T>& v) const
		{
			vector<S, T> tmp = v;
			tmp -= *this;
			return tmp;
		}

		template <size_t S, typename T>
		vector<S, T> vector<S, T>::operator*(const vector<S, T>& v) const
		{
			vector<S, T> tmp = v;
			tmp *= *this;
			return tmp;
		}

		template <size_t S, typename T>
		inline vector<S, T> operator*(const T& c, const vector<S, T>& v)
		{
			return v * c;
		}

		template <size_t S, typename T>
		vector<S, T> vector<S, T>::operator/(const vector<S, T>& v) const
		{
			vector<S, T> tmp = v;
			tmp /= *this;
			return tmp;
		}

		template <size_t S, typename T>
		vector<S, T> vector<S, T>::operator*(const T& c) const
		{
			vector<S, T> tmp = *this;
			tmp *= c;
			return tmp;
		}

		template <size_t S, typename T>
		vector<S, T> vector<S, T>::operator/(const T& c) const
		{
			vector<S, T> tmp = *this;
			tmp /= c;
			return tmp;
		}

		template <size_t S, typename T>
		const T vector<S, T>::angle(const vector<S, T>& b) const
		{
			return angle(*this, b);
		}

		template <size_t S, typename T>
		const T vector<S, T>::dot(const vector& v) const
		{
			return dot(*this, v);
		}

		template <size_t S, typename T>
		const T vector<S, T>::distance(const vector<S, T>& v) const
		{
			return distance(*this, v);
		}

		template <size_t S, typename T>
		const T vector<S, T>::length_squared() const
		{
			return length_squared(*this);
		}

		template <size_t S, typename T>
		const T vector<S, T>::length() const
		{
			return length(*this);
		}

		template <size_t S, typename T>
		const vector<S, T> vector<S, T>::lerp(const vector<S, T>& b, const T& t) const
		{
			return lerp(*this, b, t);
		}

		template <size_t S, typename T>
		const vector<S, T> vector<S, T>::normalized() const
		{
			return normalized(*this);
		}

		template <size_t S, typename T>
		const vector<S, T> vector<S, T>::project(const vector<S, T>& v) const
		{
			return project(*this, v);
		}

		template <size_t S, typename T>
		vector<S, T>& vector<S, T>::normalize()
		{
			T len = length;

			for (int i = 0; i < this->DIMENSION; ++i)
				m_data[i] /= len();

			return *this;
		}

		// Vector static declarations

		template <size_t S, typename T>
		const T vector<S, T>::angle(const vector<S, T>& a, const vector<S, T>& b)
		{
			return acos(a.dot(b) / (a.length() * b.length()));
		}

		template <size_t S, typename T>
		const T vector<S, T>::dot(const vector<S, T>& a, const vector<S, T>& b)
		{
			T tmp = 0;

			for (int i = 0; i < a.DIMENSION; ++i)
				tmp += a.m_data[i] * b.m_data[i];

			return tmp;
		}

		template <size_t S, typename T>
		const T vector<S, T>::distance(const vector<S, T>& a, const vector<S, T>& b)
		{
			return (a - b).length();
		}

		template <size_t S, typename T>
		const T vector<S, T>::length_squared(const vector<S, T>& v)
		{
			T tmp = 0;

			for (int i = 0; i < v.DIMENSION; ++i)
				tmp += v.m_data[i] * v.m_data[i];

			return tmp;
		}

		template <size_t S, typename T>
		const T vector<S, T>::length(const vector<S, T>& v)
		{
			return sqrt(length_squared(v));
		}

		template <size_t S, typename T>
		static const vector<S, T> vector<S, T>::lerp(const vector<S, T>& a, const vector<S, T>& b, const T& t)
		{
			vector<S, T> tmp;

			for (int i = 0; i < a.DIMENSION; ++i)
				tmp[i] = std::lerp(a.m_data[i], b.m_data[i], t);

			return tmp;
		}

		template <size_t S, typename T>
		static const vector<S, T> vector<S, T>::max(const vector<S, T>& a, const vector<S, T>& b)
		{
			vector<S, T> tmp;

			for (int i = 0; i < a.DIMENSION; ++i)
				tmp.m_data[i] = a.m_data[i] > b.m_data[i] ? a.m_data[i] : b.m_data[i];

			return tmp;
		}

		template <size_t S, typename T>
		static const vector<S, T> vector<S, T>::min(const vector<S, T>& a, const vector<S, T>& b)
		{
			vector<S, T> tmp;

			for (int i = 0; i < a.DIMENSION; ++i)
				tmp.m_data[i] = a.m_data[i] < b.m_data[i] ? a.m_data[i] : b.m_data[i];

			return tmp;
		}

		template <size_t S, typename T>
		const vector<S, T> vector<S, T>::normalized(const vector<S, T>& a)
		{
			return a / a.length();
		}

		template <size_t S, typename T>
		const vector<S, T> vector<S, T>::project(const vector<S, T>& a, const vector<S, T>& b)
		{
			return (a.dot(b) / a.length_squared()) * a;
		}

		template <size_t S, typename T>
		const vector<S, T> vector<S, T>::random(const T& min, const T& max)
		{
			vector<S, T> tmp;

			for (int i = 0; i < DIMENSION; ++i)
				tmp.m_data[i] = min + (max - min) * rand() / (RAND_MAX + 1);

			return tmp;			
		}

		template <size_t S, typename T>
		const vector<S, T> vector<S, T>::ONE(1);

		template <size_t S, typename T>
		const vector<S, T> vector<S, T>::ZERO(0);

		template <size_t S, typename T>
		const vector<S, T> vector<S, T>::INF(std::numeric_limits<T>::infinity());

		template <size_t S, typename T>
		const vector<S, T> vector<S, T>::NEG_INF(-std::numeric_limits<T>::infinity());
	}

}

#endif