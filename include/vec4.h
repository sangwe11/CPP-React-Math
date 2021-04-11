#ifndef _RM_VEC4_H
#define _RM_VEC4_H

#include "support/vector.h"

namespace react
{
	template <typename T>
	class vec4 : public support::vector<4, T>
	{
	public:
		// constructors
		vec4() : vector<4, T>() {}
		explicit vec4(const T& a) : vector(a) {}
		vec4(const vector& v) : vector(v) {}
		vec4(const T& x, const T& y, const T& z);
		vec4(const T& x, const T& y, const T& z, const T& w);
	};

	template <typename T>
	vec4<T>::vec4(const T& x, const T& y, const T& z)
	{
		m_data[0] = x;
		m_data[1] = y;
		m_data[2] = z;
	}

	template <typename T>
	vec4<T>::vec4(const T& x, const T& y, const T& z, const T& w)
	{
		m_data[0] = x;
		m_data[1] = y;
		m_data[2] = z;
		m_data[3] = w;
	}

#ifndef _REACT_NO_TYPEDEFS
	typedef vec4<float> vec4f;
	typedef vec4<bool> vec4b;
	typedef vec4<int> vec4i;
	typedef vec4<double> vec4d;
#endif
}

#endif