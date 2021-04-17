#ifndef _RM_MAT2_H
#define _RM_MAT2_H

#include "support/matrix.h"

namespace react
{
	template <typename T>
	class mat2 : public support::matrix<2, 2, T>
	{
	public:
		// constructors
		mat2() : matrix() {}
		explicit mat2(const T& a) : matrix(a) {}
		explicit mat2(const T(&data)[4]) : matrix(data) {}

		template <size_t M, size_t N, typename T>
		mat2(const matrix<M, N, T>& m) : matrix(m) {}

		static const mat2<T> IDENTITY;
	};

	template <typename T>
	const mat2<T> mat2<T>::IDENTITY(mat2<T>::get_identity());

#ifndef _REACT_NO_TYPEDEFS
	typedef mat2<float> mat2f;
	typedef mat2<int> mat2i;
	typedef mat2<double> mat2d;
#endif
}

#endif