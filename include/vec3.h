#ifndef _RM_VEC3_H
#define _RM_VEC3_H

#include "support/vector.h"

namespace react
{
	template <typename T>
	class vec3 : public support::vector<3, T>
	{
	public:
		// constructors
		vec3() : vector<3, T>() {}
		explicit vec3(const T& a) : vector(a) {}
		vec3(const vector& v) : vector(v) {}
		vec3(const T& x, const T& y, const T& z);

		// Utility functions
		const vec3<T> cross(const vec3<T>& v) const;
		const vec3<T> project_on_plane(const vec3<T>& normal) const;
		const vec3<T> reflect(const vec3<T>& normal) const;
		const vec3<T> slerp(const vec3<T>& b, const T& t) const;

		// Static utility functions
		static const vec3<T> cross(const vec3<T>& a, const vec3<T>& b);
		static const vec3<T> project_on_plane(const vec3<T>& v, const vec3<T>& normal);
		static const vec3<T> reflect(const vec3<T>& v, const vec3<T>& normal);
		static const vec3<T> slerp(const vec3<T>& a, const vec3<T>& b, const T& t);

		// Defaults
		static const vec3<T> FORWARD;
		static const vec3<T> BACK;
		static const vec3<T> UP;
		static const vec3<T> DOWN;
		static const vec3<T> LEFT;
		static const vec3<T> RIGHT;

	};

	template <typename T>
	vec3<T>::vec3(const T& x, const T& y, const T& z)
	{
		m_data[0] = x;
		m_data[1] = y;
		m_data[2] = z;
	}

	template <typename T>
	const vec3<T> vec3<T>::cross(const vec3<T>& v) const
	{
		return cross(*this, v);
	}

	template <typename T>
	const vec3<T> vec3<T>::project_on_plane(const vec3<T>& normal) const
	{
		return project_on_plane(*this, normal);
	}

	template <typename T>
	const vec3<T> vec3<T>::reflect(const vec3<T>& normal) const
	{
		return reflect(*this, normal);
	}

	template <typename T>
	const vec3<T> vec3<T>::slerp(const vec3<T>& b, const T& t) const
	{
		return slerp(*this, b, t);
	}

	template <typename T>
	const vec3<T> vec3<T>::cross(const vec3<T>& a, const vec3<T>& b)
	{
		return vec3<T>(a.m_data[1] * b.m_data[2] - a.m_data[2] * b.m_data[1], a.m_data[2] * b.m_data[0] - a.m_data[0] * b.m_data[2], a.m_data[0] * b.m_data[1] - a.m_data[1] * b.m_data[0]);
	}

	template <typename T>
	const vec3<T> vec3<T>::project_on_plane(const vec3<T>& v, const vec3<T>& normal)
	{
		return v - (v.dot(normal) * normal);
	}

	template <typename T>
	const vec3<T> vec3<T>::reflect(const vec3<T>& v, const vec3<T>& normal)
	{
		return v - 2 * v.dot(normal) * normal;
	}

	template <typename T>
	const vec3<T> vec3<T>::slerp(const vec3<T>& a, const vec3<T>& b, const T& t)
	{
		T dot = dot(a, b);
		T theta = acos(dot) * t;
		vec3<T> relative = (b - a * dot).normalize();
		return ((a * cos(theta)) + (relative * sin(theta)));
	}

	template <typename T>
	const vec3<T> vec3<T>::FORWARD(0, 0, -1);

	template <typename T>
	const vec3<T> vec3<T>::BACK(0, 0, 1);

	template <typename T>
	const vec3<T> vec3<T>::UP(0, 1, 0);

	template <typename T>
	const vec3<T> vec3<T>::DOWN(0, -1, 0);

	template <typename T>
	const vec3<T> vec3<T>::LEFT(-1, 0, 0);

	template <typename T>
	const vec3<T> vec3<T>::RIGHT(1, 0, 0);

#ifndef _REACT_NO_TYPEDEFS
	typedef vec3<float> vec3f;
	typedef vec3<bool> vec3b;
	typedef vec3<int> vec3i;
	typedef vec3<double> vec3d;
#endif
}

#endif