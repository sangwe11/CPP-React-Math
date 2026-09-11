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
		vec3() : support::vector<3, T>() {}
		explicit vec3(const T& a) : support::vector<3, T>(a) {}
		vec3(const T& x, const T& y, const T& z);

		template <size_t SS, typename TT>
		vec3(const support::vector<SS, TT>& v) : support::vector<3, T>(v) {}

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
		this->m_data[0] = x;
		this->m_data[1] = y;
		this->m_data[2] = z;
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
		const T epsilon = std::numeric_limits<T>::epsilon() * static_cast<T>(10);
		const T a_length = a.length();
		const T b_length = b.length();

		// Spherical interpolation has no direction to interpolate from or to here.
		// Match Unity's forgiving behaviour and use ordinary linear interpolation.
		if (a_length <= epsilon || b_length <= epsilon)
			return a.lerp(b, t);

		const vec3<T> a_normalized = a / a_length;
		const vec3<T> b_normalized = b / b_length;
		const T dot_product = std::max(static_cast<T>(-1),
			std::min(static_cast<T>(1), a_normalized.dot(b_normalized)));
		const T length = a_length + (b_length - a_length) * t;

		// Nearly parallel directions are more accurately handled by lerp.
		if (dot_product >= static_cast<T>(1) - epsilon)
			return a.lerp(b, t);

		if (dot_product <= static_cast<T>(-1) + epsilon)
		{
			// Choose the least-aligned cardinal direction, producing a stable,
			// deterministic axis perpendicular to a_normalized.
			const T abs_x = std::fabs(a_normalized.x());
			const T abs_y = std::fabs(a_normalized.y());
			const T abs_z = std::fabs(a_normalized.z());
			const vec3<T> basis = abs_x <= abs_y && abs_x <= abs_z ? RIGHT :
				(abs_y <= abs_z ? UP : BACK);
			const vec3<T> axis = a_normalized.cross(basis).normalized();
			const T theta = math::pi<T>() * t;
			return (a_normalized * std::cos(theta) + axis.cross(a_normalized) * std::sin(theta)) * length;
		}

		const T theta = std::acos(dot_product);
		const T sin_theta = std::sin(theta);
		const T a_weight = std::sin((static_cast<T>(1) - t) * theta) / sin_theta;
		const T b_weight = std::sin(t * theta) / sin_theta;
		return (a_normalized * a_weight + b_normalized * b_weight) * length;
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
