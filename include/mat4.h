#ifndef _RM_MAT4_H
#define _RM_MAT4_H

#include "support/matrix.h"

namespace react
{
#ifndef _REACT_NO_TYPEDEFS
	template <typename T>
	using mat4 = support::matrix<4, 4, T>;

	typedef mat4<double> mat4d;
	typedef mat4<float> mat4f;
	typedef mat4<int> mat4i;
	
	template <typename T>
	using mat4x2 = support::matrix<4, 2, T>;

	typedef mat4x2<double> mat4x2d;
	typedef mat4x2<float> mat4x2f;
	typedef mat4x2<int> mat4x2i;

	template <typename T>
	using mat4x3 = support::matrix<4, 3, T>;

	typedef mat4x3<double> mat4x3d;
	typedef mat4x3<float> mat4x3f;
	typedef mat4x3<int> mat4x3i;
#endif
}

#endif