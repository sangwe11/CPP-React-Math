#ifndef _RM_MAT4_H
#define _RM_MAT4_H

#include "support/matrix.h"

namespace react
{
	template <typename T>
	class mat4 : public support::matrix<4, 4, T>
	{
	public:
		// constructors
		mat4() : matrix() {}
		explicit mat4(const T& a) : matrix(a) {}
		explicit mat4(const T(&data)[16]) : matrix(data) {}

		template <size_t M, size_t N, typename T>
		mat4(const matrix<M, N, T>& m) : matrix(m) {}

		static const mat4<T> IDENTITY;
	};

	template <typename T>
	const mat4<T> mat4<T>::IDENTITY(mat4<T>::get_identity());

#ifndef _REACT_NO_TYPEDEFS
	typedef mat4<float> mat4f;
	typedef mat4<int> mat4i;
	typedef mat4<double> mat4d;
#endif
}

#endif