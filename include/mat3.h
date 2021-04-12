#ifndef _RM_MAT3_H
#define _RM_MAT3_H

#include "support/matrix.h"

namespace react
{
	template <typename T>
	class mat3 : public support::matrix<3, 3, T>
	{
	public:
		// constructors
		mat3() : matrix() {}
		explicit mat3(const T& a) : matrix(a) {}
		mat3(const matrix& m) : matrix(m) {}

		static const mat3<T> IDENTITY;
	};

	template <typename T>
	const mat3<T> mat3<T>::IDENTITY(mat3<T>::get_identity());

#ifndef _REACT_NO_TYPEDEFS
	typedef mat3<float> mat3f;
	typedef mat3<int> mat3i;
	typedef mat3<double> mat3d;
#endif
}

#endif