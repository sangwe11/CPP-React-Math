#ifndef _RM_QUAT_H
#define _RM_QUAT_H

#include "vec3.h"
#include "vec4.h"

namespace react
{
	template <typename T>
	class quat : private vec4<T>
	{
	private:
		typename support::check_type_floating<T>::type ctf{};
		typedef vec4<T> super;

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
		quat(const vec3<T>& xyz, const T& w);
		quat(const vec4<T>& xyzw);
		quat(const mat3<T>& m);
		quat(const vec3<T>& eulers);

		inline const vec3<T> xyz() const;

		const quat<T> conjugate() const;
		const T dot(const quat<T>& b) const;		
		const quat<T> inverse() const;
		const quat<T> normalized() const;
		const vec3<T> rotate(const vec3<T> v) const;
		const void toAxisAngle(vec3<T>& axis_out, T& angle_out);
		const vec3<T> toEulers() const;
		const mat3<T> toMat3() const;

		quat<T>& normalize();

		
		const static T dot(const quat<T>& a, const quat<T>& b);
		const static quat<T> conjugate(const quat<T>& a);
		const static quat<T> inverse(const quat<T>& a);
		const static quat<T> normalized(const quat<T>& a);
		const static vec3<T> rotate(const quat<T>& q, const vec3<T>& v);

		const static quat<T> fromAxisAngle(const vec3<T>& axis, const T& angle);
		const static void toAxisAngle(const quat<T> &q, vec3<T>& axis_out, T& angle_out);

		const static quat<T> fromEulers(const vec3<T>& e);
		const static vec3<T> toEulers(const quat<T>& q);

		const static quat<T> fromMat3(const mat3<T>& m);
		const static mat3<T> toMat3(const quat<T>& q);

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
	quat<T>::quat(const vec3<T>& xyz, const T& w)
	{
		m_data[0] = xyz[0];
		m_data[1] = xyz[1];
		m_data[2] = xyz[2];
		m_data[3] = w;
	}

	template <typename T>
	quat<T>::quat(const vec4<T>& xyzw)
	{
		m_data[0] = xyzw[0];
		m_data[1] = xyzw[1];
		m_data[2] = xyzw[2];
		m_data[3] = xyzw[3];
	}

	template <typename T>
	quat<T>::quat(const mat3<T>& m)
	{
		T trace = m(0, 0) + m(1, 1) + m(2, 2); // sum of the diagonal

		if (trace > 0)
		{
			T s = sqrt(trace + static_cast<T>(1)) * static_cast<T>(2);
			x() = (m(2, 1) - m(1, 2)) / s;
			y() = (m(0, 2) - m(2, 0)) / s;
			z() = (m(1, 0) - m(0, 1)) / s;
			w() = s / static_cast<T>(4);
		}
		else
		{
			if (m(0, 0) > m(1, 1) && m(0, 0) > m(2, 2))
			{
				T s = static_cast<T>(2) * sqrt(static_cast<T>(1) + m(0, 0) - m(1, 1) - m(2, 2));
				x() = s / static_cast<T>(4);
				y() = (m(0, 1) + m(1, 0)) / s;
				z() = (m(0, 2) + m(2, 0)) / s;
				w() = (m(2, 1) - m(1, 2)) / s;
			}
			else if (m(1, 1) > m(2, 2))
			{
				T s = static_cast<T>(2) * sqrt(static_cast<T>(1) + m(1, 1) - m(0, 0) - m(2, 2));

				x() = (m(0,1) + m(1, 0)) / s;
				y() = s / static_cast<T>(4);
				z() = (m(1,2) + m(2, 1)) / s;
				w() = (m(0,2) + m(2, 0)) / s;
			}
			else
			{
				T s = static_cast<T>(2) * sqrt(static_cast<T>(1) + m(2, 2) - m(0, 0) - m(1, 1));

				x() = (m(0, 2) + m(2, 0)) / s;
				y() = (m(1, 2) + m(2, 1)) / s;
				z() = s / static_cast<T>(4);
				w() = (m(1, 0) - m(0, 1)) / s;
			}
		}
	}

	template <typename T>
	quat<T>::quat(const vec3<T>& eulers)
	{
		T cos_x = cos(eulers.x() / static_cast<T>(2));
		T sin_x = sin(eulers.x() / static_cast<T>(2));
		T cos_y = cos(eulers.y() / static_cast<T>(2));
		T sin_y = sin(eulers.y() / static_cast<T>(2));
		T cos_z = cos(eulers.z() / static_cast<T>(2));
		T sin_z = sin(eulers.z() / static_cast<T>(2));

		T cos_y_cos_z = cos_y * cos_z;
		T sin_y_sin_z = sin_y * sin_z;

		x() = cos_y_cos_z * sin_x + sin_y_sin_z * cos_x;
		y() = sin_y * cos_z * cos_x + cos_y * sin_z * sin_x;
		z() = cos_y * sin_z * cos_x - sin_y * cos_z * sin_x;
		w() = cos_y_cos_z * cos_x - sin_y_sin_z * sin_x;
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
	const void quat<T>::toAxisAngle(vec3<T>& axis_out, T& angle_out)
	{
		return toAxisAngle(*this, axis_out, angle_out);
	}

	template <typename T>
	const vec3<T> quat<T>::toEulers() const
	{
		return toEulers(*this);
	}

	template <typename T>
	const mat3<T> quat<T>::toMat3() const
	{
		return toMat3(*this);
	}

	template <typename T>
	quat<T>& quat<T>::normalize()
	{
		return *this *= (static_cast<T>(1) / length());
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
	const quat<T> quat<T>::fromAxisAngle(const vec3<T>& axis, const T& angle)
	{
		T s = sin(angle * static_cast<T>(0.5));

		return quat<T>(axis * s, cos(angle * static_cast<T>(0.5)));
	}

	template <typename T>
	const void quat<T>::toAxisAngle(const quat<T>& quat_in, vec3<T>& axis_out, T& angle_out)
	{
		quat<T> q = quat_in;

		if (q.w() > static_cast<T>(1))
			q.normalize();

		angle_out = static_cast<T>(2) * acos(q.w());

		T s = sqrt(static_cast<T>(1) - q.w() * q.w());
		T s2 = sin(angle_out / static_cast<T>(2));

		if (s < std::numeric_limits<T>::epsilon())
		{
			axis_out.x() = q.x();
			axis_out.y() = q.y();
			axis_out.z() = q.z();
		}
		else
		{
			axis_out.x() = q.x() / s;
			axis_out.y() = q.y() / s;
			axis_out.z() = q.z() / s;
		}
	}

	template <typename T>
	const quat<T> quat<T>::fromEulers(const vec3<T>& e)
	{
		return quat<T>(e);
	}

	template <typename T>
	const vec3<T> quat<T>::toEulers(const quat<T>& q)
	{
		vec3<T> tmp;

		T sqx = q.x() * q.x();
		T sqy = q.y() * q.y();
		T sqz = q.z() * q.z();
		T sqw = q.w() * q.w();

		T unit = sqx + sqy + sqz + sqw;
		T test = q.x() * q.y() + q.z() * q.w();

		if (test > 0.499 * unit)
		{ // singularity at north pole
			tmp.x() = static_cast<T>(0);
			tmp.y() = static_cast<T>(2) * atan2(q.x(), q.w());
			tmp.z() = react::math::half_pi<T>();

			return tmp;
		}

		if (test < -0.499 * unit)
		{ // singularity at south pole
			tmp.x() = static_cast<T>(0);
			tmp.y() = static_cast<T>(-2) * atan2(q.x(), q.w());
			tmp.z() = -react::math::half_pi<T>();

			return tmp;
		}

		tmp.x() = atan2(static_cast<T>(2) * q.x() * q.w() - static_cast<T>(2) * q.y() * q.z(), -sqx + sqy - sqz + sqw);
		tmp.y() = atan2(static_cast<T>(2) * q.y() * q.w() - static_cast<T>(2) * q.x() * q.z(), sqx - sqy - sqz + sqw);
		tmp.z() = asin(static_cast<T>(2) * test / unit);

		return tmp;
	}

	template <typename T>
	const quat<T> quat<T>::fromMat3(const mat3<T>& m)
	{
		return quat<T>(m);
	}

	template <typename T>
	const mat3<T> quat<T>::toMat3(const quat<T>& q)
	{
		mat3<T> tmp;

		T x2 = q.x() * q.x();
		T y2 = q.y() * q.y();
		T z2 = q.z() * q.z();
		T w2 = q.w() * q.w();

		T xy = q.x() * q.y();
		T xz = q.x() * q.z();
		T yz = q.y() * q.z();

		T wx = q.w() * q.x();
		T wy = q.w() * q.y();
		T wz = q.w() * q.z();

		tmp(0, 0) = 1 - 2 * y2 - 2 * z2;
		tmp(0, 1) = 2 * xy - 2 * wz;
		tmp(0, 2) = 2 * xz + 2 * wy;
		tmp(1, 0) = 2 * xy + 2 * wz;
		tmp(1, 1) = 1 - 2 * x2 - 2 * z2;
		tmp(1, 2) = 2 * yz - 2 * wx;
		tmp(2, 0) = 2 * xz - 2 * wy;
		tmp(2, 1) = 2 * yz + 2 * wx;
		tmp(2, 2) = 1 - 2 * x2 - 2 * y2;

		return tmp;
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