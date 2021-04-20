#ifndef _RM_VEC2_H
#define _RM_VEC2_H

#include "support/vector.h"

namespace react
{
	template <typename T>
	class vec2 : public support::vector<2, T>
	{
	public:
		// constructors
		vec2() : vector<2, T>() {}
		explicit vec2(const T& a) : vector(a) {}
		vec2(const T& x, const T& y);

		template <size_t SS, typename TT>
		vec2(const vector<SS, TT>& v) : vector(v) {}

		static const vec2<T> UP;
		static const vec2<T> DOWN;
		static const vec2<T> LEFT;
		static const vec2<T> RIGHT;
	};

	template <typename T>
	vec2<T>::vec2(const T& x, const T& y)
	{
		m_data[0] = x;
		m_data[1] = y;
	}

	template <typename T>
	const vec2<T> vec2<T>::UP(0, 1);

	template <typename T>
	const vec2<T> vec2<T>::DOWN(0, -1);

	template <typename T>
	const vec2<T> vec2<T>::LEFT(-1, 0);

	template <typename T>
	const vec2<T> vec2<T>::RIGHT(1, 0);

#ifndef _REACT_NO_TYPEDEFS
	typedef vec2<float> vec2f;
	typedef vec2<bool> vec2b;
	typedef vec2<int> vec2i;
	typedef vec2<double> vec2d;
#endif
}

#endif