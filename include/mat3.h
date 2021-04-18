#ifndef _RM_MAT3_H
#define _RM_MAT3_H

#include "support/matrix.h"

namespace react
{
#ifndef _REACT_NO_TYPEDEFS
	template <typename T>
	using mat3 = support::matrix<3, 3, T>;

	typedef mat3<double> mat3d;
	typedef mat3<float> mat3f;
	typedef mat3<int> mat3i;

	template <typename T>
	using mat3x2 = support::matrix <3, 2, T>;

	typedef mat3x2<double> mat3x2d;
	typedef mat3x2<float> mat3x2f;
	typedef mat3x2<int> mat3x2i;

	template <typename T>
	using mat3x4 = support::matrix<3, 4, T>;

	typedef mat3x4<double> mat3x4d;
	typedef mat3x4<float> mat3x4f;
	typedef mat3x4<int> mat3x4i;
#endif
}

#endif