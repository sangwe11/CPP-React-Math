#ifndef _RM_QUAT_H
#define _RM_QUAT_H

#include "vec3.h"
#include "vec4.h"

namespace react
{
	template <typename T>
	class quat : private support::vector<4, T>
	{
	private:
		typename support::check_type_floating<T>::type ctf{};
		typedef support::vector<4, T> super;

	public:
		using super::type;
		using super::x;
		using super::y;
		using super::z;
		using super::w;
		using super::length;
		using super::length_squared;
		using super::operator[];
		using super::m_data;

		quat() { w() = 1; }
		quat(const T& x, const T& y, const T& z, const T& w);
		quat(const support::vector<3, T>& xyz, const T& w);
		quat(const support::vector<4, T>& xyzw);

		inline const vec3<T> xyz() const;

		const quat<T> conjugate() const;
		const T dot(const quat<T>& b) const;
		const quat<T> inverse() const;
		const quat<T> normalized() const;
		const vec3<T> rotate(const vec3<T> v) const;

		quat<T>& normalize();

		const static quat<T> axisAngle(const vec3<T>& axis, const T& angle);
		const static T dot(const quat<T>& a, const quat<T>& b);
		const static quat<T> conjugate(const quat<T>& a);
		const static quat<T> inverse(const quat<T>& a);
		const static quat<T> normalized(const quat<T>& a);
		const static vec3<T> rotate(const quat<T>& q, const vec3<T>& v);

		const bool operator==(const quat<T>& b) const;
		const bool operator!=(const quat<T>& b) const;

		quat<T>& operator*=(const T& c);
		quat<T>& operator/=(const T& c);

		quat<T> operator*(const T& c) const;
		quat<T> operator/(const T& c) const;

		quat<T>& operator*=(const quat<T>& b);
		quat<T>& operator+=(const quat<T>& b);
		quat<T>& operator-=(const quat<T>& b);

		quat<T> operator*(const quat<T>& b) const;
		quat<T> operator+(const quat<T>& b) const;
		quat<T> operator-(const quat<T>& b) const;

		friend std::ostream& operator<<(std::ostream& out, const quat<T>& q)
		{
			out << "Quat(" << q.x() << ", " << q.y() << ", " << q.z() << ", " << q.w() << ")";

			return out;
		}

		static const quat<T> ZERO;
		static const quat<T> ONE;
		static const quat<T> IDENTITY;
	};

	template <typename T>
	quat<T>::quat(const T& x, const T& y, const T& z, const T& w)
	{
		m_data[0] = x;
		m_data[1] = y;
		m_data[2] = z;
		m_data[3] = w;
	}

	template <typename T>
	quat<T>::quat(const support::vector<3, T>& xyz, const T& w)
	{
		m_data[0] = xyz[0];
		m_data[1] = xyz[1];
		m_data[2] = xyz[2];
		m_data[3] = w;
	}

	template <typename T>
	quat<T>::quat(const support::vector<4, T>& xyzw)
	{
		m_data[0] = xyzw[0];
		m_data[1] = xyzw[1];
		m_data[2] = xyzw[2];
		m_data[3] = xyzw[3];
	}

	template <typename T>
	const vec3<T> quat<T>::xyz() const
	{
		return vec3<T>(x(), y(), z());
	}

	template <typename T>
	const quat<T> quat<T>::conjugate() const
	{
		return conjugate(*this);
	}

	template <typename T>
	const T quat<T>::dot(const quat<T>& b) const
	{
		return dot(*this, b);
	}

	template <typename T>
	const quat<T> quat<T>::inverse() const
	{
		return inverse(*this);
	}

	template <typename T>
	const quat<T> quat<T>::normalized() const
	{
		return normalized(*this);
	}

	template <typename T>
	const vec3<T> quat<T>::rotate(const vec3<T> v) const
	{
		return rotate(*this, v);
	}

	template <typename T>
	quat<T>& quat<T>::normalize()
	{
		return *this *= (static_cast<T>(1) / length());
	}

	template <typename T>
	const quat<T> quat<T>::axisAngle(const vec3<T>& axis, const T& angle)
	{
		T s = sin(angle * static_cast<T>(0.5));

		return quat<T>(axis * s, cos(angle * static_cast<T>(0.5)));
	}

	template <typename T>
	const quat<T> quat<T>::conjugate(const quat<T>& a)
	{
		return quat<T>(-a.x(), -a.y(), -a.z(), a.w());
	}

	template <typename T>
	const quat<T> quat<T>::inverse(const quat<T>& a)
	{
		return  a.conjugate() / a.length_squared();
	}

	template <typename T>
	const T quat<T>::dot(const quat<T>& a, const quat<T>& b)
	{
		T tmp = 0;

		for (int i = 0; i < a.DIMENSION; ++i)
			tmp += a.m_data[i] * b.m_data[i];

		return tmp;
	}

	template <typename T>
	const vec3<T> quat<T>::rotate(const quat<T>& q, const vec3<T>& v)
	{
		vec3<T> xyz = q.xyz();

		return v + static_cast<T>(2) * xyz.cross(xyz.cross(v) + q.w() * v);
	}

	template <typename T>
	const quat<T> quat<T>::normalized(const quat<T>& a)
	{
		return a * (static_cast<T>(1) / a.length());
	}

	template <typename T>
	const bool quat<T>::operator==(const quat<T>& b) const
	{
#ifndef _REACT_EXACT_COMPARISON
		for (int i = 0; i < DIMENSION; ++i)
			if (fabs(m_data[i] - b.m_data[i]) > std::numeric_limits<T>::epsilon())
				return false;

		return true;
#else
		return std::memcmp(m_data, b.m_data, sizeof(m_data)) == 0;
#endif
	}

	template <typename T>
	const bool quat<T>::operator!=(const quat<T>& b) const
	{
		return !(*this == b);
	}

	template <typename T>
	quat<T>& quat<T>::operator*=(const T& c)
	{
		x() *= c;
		y() *= c;
		z() *= c;
		w() *= c;

		return *this;
	}

	template <typename T>
	quat<T>& quat<T>::operator/=(const T& c)
	{
		x() /= c;
		y() /= c;
		z() /= c;
		w() /= c;

		return *this;
	}

	template <typename T>
	quat<T> quat<T>::operator*(const T& c) const
	{
		quat<T> tmp = *this;
		tmp *= c;
		return tmp;
	}

	template <typename T>
	inline quat<T> operator*(const T& c, const quat<T>& q)
	{
		return q * c;
	}

	template <typename T>
	quat<T> quat<T>::operator/(const T& c) const
	{
		quat<T> tmp = *this;
		tmp /= c;
		return tmp;
	}

	template <typename T>
	quat<T>& quat<T>::operator*=(const quat<T>& b)
	{
		quat<T> tmp;

		tmp.x() = x() * b.w() + y() * b.z() - z() * b.y() + w() * b.x();
		tmp.y() = -x() * b.z() + y() * b.w() + z() * b.x() + w() * b.y();
		tmp.z() = x() * b.y() - y() * b.x() + z() * b.w() + w() * b.z();
		tmp.w() = -x() * b.x() - y() * b.y() - z() * b.z() + w() * b.w();

		*this = tmp;

		return *this;
	}

	template <typename T>
	quat<T>& quat<T>::operator+=(const quat<T>& b)
	{
		x() += b.x();
		y() += b.y();
		z() += b.z();
		w() += b.w();

		return *this;
	}

	template <typename T>
	quat<T>& quat<T>::operator-=(const quat<T>& b)
	{
		x() -= b.x();
		y() -= b.y();
		z() -= b.z();
		w() -= b.w();

		return *this;
	}

	template <typename T>
	quat<T> quat<T>::operator*(const quat<T>& b) const
	{
		quat<T> tmp = *this;
		tmp *= b;
		return tmp;
	}

	template <typename T>
	quat<T> quat<T>::operator+(const quat<T>& b) const
	{
		quat<T> tmp = *this;
		tmp += b;
		return tmp;
	}

	template <typename T>
	quat<T> quat<T>::operator-(const quat<T>& b) const
	{
		quat<T> tmp = *this;
		tmp -= b;
		return tmp;
	}

	template <typename T>
	const quat<T> quat<T>::ZERO(0, 0, 0, 0);

	template <typename T>
	const quat<T> quat<T>::ONE(1, 1, 1, 1);

	template <typename T>
	const quat<T> quat<T>::IDENTITY(0, 0, 0, 1);

#ifndef _REACT_NO_TYPEDEFS
	typedef quat<float> quatf;
	typedef quat<double> quatd;
#endif
}

#endif