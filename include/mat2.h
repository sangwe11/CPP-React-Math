#ifndef _RM_MAT2_H
#define _RM_MAT2_H

#include "support/matrix.h"

namespace react
{
#ifndef _REACT_NO_TYPEDEFS
	template <typename T>
	using mat2 = support::matrix<2, 2, T>;

	typedef mat2<double> mat2d;
	typedef mat2<float> mat2f;
	typedef mat2<int> mat2i;

	template <typename T>
	using mat2x3 = support::matrix<2, 3, T>;

	typedef mat2x3<double> mat2x3d;
	typedef mat2x3<float> mat2x3f;
	typedef mat2x3<int> mat2x3i;

	template <typename T>
	using mat2x4 = support::matrix<2, 4, T>;

	typedef mat2x4<double> mat2x4d;
	typedef mat2x4<float> mat2x4f;
	typedef mat2x4<int> mat2x4i;
#endif
}

#endif