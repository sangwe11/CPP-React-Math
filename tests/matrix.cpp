#include <boost/test/unit_test.hpp>

#include <React-Math.h>

BOOST_AUTO_TEST_SUITE(matrix)

BOOST_AUTO_TEST_CASE(matrix_default_constructor)
{
	react::mat3f mat;
	// 0  0  0
	// 0  0  0
	// 0  0  0

	float truth[] = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	// 1  0  0
	// 0  1  0
	// 0  0  1 

	BOOST_CHECK_EQUAL_COLLECTIONS(mat.m_data, mat.m_data + 9, truth, truth + 9);
}

BOOST_AUTO_TEST_CASE(matrix_constant_constructor)
{
	react::mat3f mat(3.0f);
	// 3  3  3
	// 3  3  3
	// 3  3  3

	float truth[] = { 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f };
	// 3  3  3
	// 3  3  3
	// 3  3  3

	BOOST_CHECK_EQUAL_COLLECTIONS(mat.m_data, mat.m_data + 9, truth, truth + 9);
}

BOOST_AUTO_TEST_CASE(matrix_zero_constructor)
{
	react::mat3f A = react::mat3f::ZERO;
	// 0  0  0
	// 0  0  0
	// 0  0  0

	float truth[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	// 0  0  0
	// 0  0  0
	// 0  0  0

	BOOST_CHECK_EQUAL_COLLECTIONS(A.m_data, A.m_data + 9, truth, truth + 9);
}

BOOST_AUTO_TEST_CASE(matrix_one_constructor)
{
	react::mat3f A = react::mat3f::ONE;
	// 1  1  1
	// 1  1  1
	// 1  1  1

	float truth[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
	// 1  1  1
	// 1  1  1
	// 1  1  1

	BOOST_CHECK_EQUAL_COLLECTIONS(A.m_data, A.m_data + 9, truth, truth + 9);
}

BOOST_AUTO_TEST_CASE(matrix_identity_constructor)
{
	react::mat3f A = react::mat3f::IDENTITY;
	// 1  0  0
	// 0  1  0
	// 0  0  1

	float truth[] = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	// 1  0  0
	// 0  1  0
	// 0  0  1

	BOOST_CHECK_EQUAL_COLLECTIONS(A.m_data, A.m_data + 9, truth, truth + 9);
}

BOOST_AUTO_TEST_CASE(matrix_from_matrix_constructor)
{
	react::mat3f A = react::mat3f::IDENTITY;
	// 1  0  0
	// 0  1  0
	// 0  0  1

	react::mat2f B(A);
	// 1  0
	// 0  1

	react::mat4f C(A);
	// 1  0  0  X
	// 0  1  0  X
	// 0  0  1  X
	// X  X  X  X

	float B_truth[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	// 1  0
	// 0  1

	float C_truth[] = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	// 1  0  0  0
	// 0  1  0  0
	// 0  0  1  0
	// 0  0  0  1

	BOOST_CHECK_EQUAL_COLLECTIONS(B.m_data, B.m_data + 4, B_truth, B_truth + 4);
	BOOST_CHECK_EQUAL_COLLECTIONS(C.m_data, C.m_data + 16, C_truth, C_truth + 16);
}

BOOST_AUTO_TEST_CASE(matrix_from_array_constructor)
{
	react::mat4f A({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f });
	// 1  4  7
	// 2  5  8
	// 3  6  9

	float truth[] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
	// 1  4  7
	// 2  5  8
	// 3  6  9
	
	BOOST_CHECK_EQUAL_COLLECTIONS(A.m_data, A.m_data + 9, truth, truth + 9);
}

BOOST_AUTO_TEST_CASE(matrix_compare)
{
	react::mat3f A({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f });
	// 1   4   7
	// 2   5   8
	// 3   6   9

	react::mat3f B({ 9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f });
	// 9   6   3
	// 8   5   2
	// 7   4   1

	react::mat3f C({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f });
	// 1   4   7
	// 2   5   8
	// 3   6   9

	react::mat4f D(A);

	bool A_eq_B = (A == B); // false
	bool A_eq_C = (A == C); // true
	bool A_eq_D = (A == D); // false
	bool A_neq_B = (A != B); // true
	bool A_neq_C = (A != C); // false
	bool A_neq_D = (A != D); // true

	BOOST_CHECK(A_eq_B == false);
	BOOST_CHECK(A_eq_C == true);
	BOOST_CHECK(A_eq_D == false);
	BOOST_CHECK(A_neq_B == true);
	BOOST_CHECK(A_neq_C == false);
	BOOST_CHECK(A_neq_D == true);
}

BOOST_AUTO_TEST_CASE(matrix_product_mat3)
{
	react::mat3f A({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f });
	// 1   4   7
	// 2   5   8
	// 3   6   9

	react::mat3f B({ 9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f });
	// 9   6   3
	// 8   5   2
	// 7   4   1

	auto C = A * B;

	react::mat3f truth({ 90.0f, 114.0f, 138.0f, 54.0f, 69.0f, 84.0f, 18.0f, 24.0f, 30.0f });
	// 90    54   18
	// 114   69   24
	// 138   84   30

	BOOST_CHECK(C == truth);
}

BOOST_AUTO_TEST_CASE(matrix_product_mat3x2)
{
	react::mat3x2f A({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f });
	// 1   3   5
	// 2   4   6

	react::mat2x3f B({ 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f });
	// 6   3
	// 5   2
	// 4   1

	auto C = A * B;

	react::mat2f truth({ 41.0f, 56.0f, 14.0f, 20.0f });
	// 41   14
	// 56   20

	BOOST_CHECK(C == truth);
}

BOOST_AUTO_TEST_CASE(matrix_product3_mat3x4)
{
	react::mat3x4f A({ 1.0f, 2.0f, 3.0f,4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f });
	// 1   5   9
	// 2   6   10
	// 3   7   11
	// 4   8   12

	react::mat4x3f B({ 12.0f, 11.0f, 10.0f, 9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f });
	// 12   9   6   3
	// 11   8   5   2
	// 10   7   4   1

	auto C = A * B;

	react::mat4f truth({ 157.0f, 190.0f, 223.0f, 256.0f, 112.0f, 136.0f, 160.0f, 184.0f, 67.0f, 82.0f, 97.0f, 112.0f, 22.0f, 28.0f, 34.0f, 40.0f });
	//157   112   67    22
	//190   136   82    28
	//223   160   97    34
	//256   184   112   40

	bool check = (C == truth);

	BOOST_CHECK(C == truth);
}

BOOST_AUTO_TEST_CASE(matrix_determinant_mat3)
{
	react::mat3f A({ 6.0f, 4.0f, 2.0f, 1.0f, -2.0f, 8.0f, 1.0f, 5.0f, 7.0f });
	// 6   1   1
	// 4  -2   5
	// 2   8   7

	float B = A.determinant();

	float truth = -306.0f;

	BOOST_CHECK(B == truth);
}

BOOST_AUTO_TEST_CASE(matrix_determinant_mat4)
{
	react::mat4f A({ 1.0f, 2.0f, -1.0f, 2.0f, 0.0f, 5.0f, 2.0f, 1.0f, 4.0f, 0.0f, 3.0f, -2.0f, -6.0f, 3.0f, 5.0f, 3.0f });
	//  1   0   4  -6
	//  2   5   0   3
	// -1   2   3   5
	//  2   1  -2   3

	float B = A.determinant();

	float truth = 318.0f;

	BOOST_CHECK(B == truth);
}

BOOST_AUTO_TEST_CASE(matrix_inverse_mat3)
{
	react::mat3f A({ 1.0f, -2.0f, 1.0f, 2.0f, 0.0f, -1.0f, -1.0f, 1.0f, 0.0f });
	//  1   2  -1
	// -2   0   1
	//  1  -1   0

	react::mat3f B = A.inverse();

	react::mat3f truth({ 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 3.0f, 2.0f, 1.0f, 4.0f });
	// 1   1   2
	// 1   1   1
	// 2   3   4

	BOOST_CHECK(B == truth);
}

BOOST_AUTO_TEST_CASE(matrix_inverse_mat4)
{
	react::mat4f A({ 1.0f, 2.0f, 0.0f, -1.0f, -1.0f, 1.0f, 3.0f, -2.0f, 3.0f, 0.0f, -1.0f, 1.0f, -1.0f, 2.0f, 0.0f, 1.0f });
	//  1  -1   3  -1
	//  2   1   0   2
	//  0   3  -1   0
	// -1  -2   1   1

	react::mat4f B = A.inverse();

	react::mat4f truth({ 1.0f/36.0f, 1.0f/9.0f, 1.0f/3.0f, -(1.0f/12.0f), 1.0f/4.0f, 0.0f, 0.0f, 1.0f/4.0f, -(7.0f/18.0f), 4.0f/9.0f, 1.0f/3.0f, 1.0f/6.0f, -(17.0f/36.0f), 1.0f/9.0f, 1.0f/3.0f, 5.0f/12.0f });
	//  1/36   1/4   -7/18   -17/36
	//  1/9    0      4/9      1/9
	//  1/3    0      1/3      1/3
	// -1/12   1/4    1/6      5/12

	BOOST_CHECK(B == truth);
}

BOOST_AUTO_TEST_CASE(matrix_transpose)
{
	react::mat3f A({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f });
	// 1   4   7
	// 2   5   8
	// 3   6   9

	react::mat4x3f B({ 12.0f, 11.0f, 10.0f, 9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f });
	// 12   9   6   3
	// 11   8   5   2
	// 10   7   4   1

	auto A_t = A.transpose();
	auto B_t = B.transpose();

	react::mat3f A_truth({ 1.0f, 4.0f, 7.0f, 2.0f, 5.0f, 8.0f, 3.0f, 6.0f, 9.0f });
	// 1   2   3
	// 4   5   6
	// 7   8   9

	react::mat3x4f B_truth({ 12.0f, 9.0f, 6.0f, 3.0f, 11.0f, 8.0f, 5.0f, 2.0f, 10.0f, 7.0f, 4.0f, 1.0f });
	// 12   11   10
	// 9    8    9
	// 6    6    4
	// 3    2    1

	BOOST_CHECK(A_t == A_truth);
	BOOST_CHECK(B_t == B_truth);
}

BOOST_AUTO_TEST_CASE(matrix_addition)
{
	react::mat4f A({ 1.0f, 2.0f, 1.0f, 2.0f, 2.0f, 1.0f, 2.0f, 1.0f, 1.0f, 2.0f, 1.0f, 2.0f, 2.0f, 1.0f, 2.0f, 1.0f });
	// 1  2  1  2
	// 2  1  2  1
	// 1  2  1  2
	// 2  1  2  1

	react::mat4f B({ 2.0f, 1.0f, 2.0f, 1.0f, 1.0f, 2.0f, 1.0f, 2.0f, 2.0f, 1.0f, 2.0f, 1.0f, 1.0f, 2.0f, 1.0f, 2.0f });
	// 2  1  2  1
	// 1  2  1  2
	// 2  1  2  1
	// 1  2  1  2

	auto C = A + B;
	auto D = B + A;

	react::mat4f truth({ 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f });
	// 3  3  3  3
	// 3  3  3  3
	// 3  3  3  3
	// 3  3  3  3

	BOOST_TEST(C == truth);
	BOOST_TEST(D == truth);
}

BOOST_AUTO_TEST_CASE(matrix_subtraction)
{
	react::mat4f A({ 1.0f, 2.0f, 1.0f, 2.0f, 2.0f, 1.0f, 2.0f, 1.0f, 1.0f, 2.0f, 1.0f, 2.0f, 2.0f, 1.0f, 2.0f, 1.0f });
	// 1  2  1  2
	// 2  1  2  1
	// 1  2  1  2
	// 2  1  2  1

	react::mat4f B({ 2.0f, 1.0f, 2.0f, 1.0f, 1.0f, 2.0f, 1.0f, 2.0f, 2.0f, 1.0f, 2.0f, 1.0f, 1.0f, 2.0f, 1.0f, 2.0f });
	// 2  1  2  1
	// 1  2  1  2
	// 2  1  2  1
	// 1  2  1  2

	auto A_min_B = A - B;
	auto B_min_A = B - A;

	react::mat4f A_min_B_truth({ -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f });
	// -1   1  -1   1
	//  1  -1   1  -1
	// -1   1  -1   1
	//  1  -1   1  -1

	react::mat4f B_min_A_truth({ 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f });
	//  1  -1   1  -1
	// -1   1  -1   1
	//  1  -1   1  -1
	// -1   1  -1   1

	BOOST_TEST(A_min_B == A_min_B_truth);
	BOOST_TEST(B_min_A == B_min_A_truth);
}

BOOST_AUTO_TEST_CASE(matrix_constant_multiplication)
{
	react::mat4f A({ 1.0f, 2.0f, 1.0f, 2.0f, 2.0f, 1.0f, 2.0f, 1.0f, 1.0f, 2.0f, 1.0f, 2.0f, 2.0f, 1.0f, 2.0f, 1.0f });
	// 1  2  1  2
	// 2  1  2  1
	// 1  2  1  2
	// 2  1  2  1

	float constant = 3.0f;

	auto B = A * constant;
	auto C = constant * A;

	react::mat4f truth({ 3.0f, 6.0f, 3.0f, 6.0f, 6.0f, 3.0f, 6.0f, 3.0f, 3.0f, 6.0f, 3.0f, 6.0f, 6.0f, 3.0f, 6.0f, 3.0f });
	// 3  6  3  6
	// 6  3  6  3
	// 3  6  3  6
	// 6  3  6  3

	BOOST_TEST(B == truth);
	BOOST_TEST(C == truth);
}

BOOST_AUTO_TEST_CASE(matrix_constant_division)
{
	react::mat4f A({ 1.0f, 2.0f, 1.0f, 2.0f, 2.0f, 1.0f, 2.0f, 1.0f, 1.0f, 2.0f, 1.0f, 2.0f, 2.0f, 1.0f, 2.0f, 1.0f });
	// 1  2  1  2
	// 2  1  2  1
	// 1  2  1  2
	// 2  1  2  1

	float constant = 3.0f;

	auto B = A / constant;
	auto C = constant / A;

	react::mat4f A_div_const_truth({ 1.0f/3.0f, 2.0f / 3.0f, 1.0f / 3.0f, 2.0f / 3.0f, 2.0f / 3.0f, 1.0f / 3.0f, 2.0f / 3.0f, 1.0f / 3.0f, 1.0f / 3.0f, 2.0f / 3.0f, 1.0f / 3.0f, 2.0f / 3.0f, 2.0f / 3.0f, 1.0f / 3.0f, 2.0f / 3.0f, 1.0f / 3.0f });
	// 1/3  2/3  1/3  2/3
	// 2/3  1/3  2/3  1/3
	// 1/3  2/3  1/3  2/3
	// 2/3  1/3  2/3  1/3

	react::mat4f const_div_A_truth({ 3.0f/1.0f, 3.0f / 2.0f, 3.0f / 1.0f, 3.0f / 2.0f, 3.0f / 2.0f, 3.0f / 1.0f, 3.0f / 2.0f, 3.0f / 1.0f, 3.0f / 1.0f, 3.0f / 2.0f, 3.0f / 1.0f, 3.0f / 2.0f, 3.0f / 2.0f, 3.0f / 1.0f, 3.0f / 2.0f, 3.0f / 1.0f });
	// 1  2  1  2
	// 2  1  2  1
	// 1  2  1  2
	// 2  1  2  1

	BOOST_TEST(B == A_div_const_truth);
	BOOST_TEST(C == const_div_A_truth);
}

BOOST_AUTO_TEST_CASE(matrix_constant_addition)
{
	react::mat4f A({ 1.0f, 2.0f, 1.0f, 2.0f, 2.0f, 1.0f, 2.0f, 1.0f, 1.0f, 2.0f, 1.0f, 2.0f, 2.0f, 1.0f, 2.0f, 1.0f });
	// 1  2  1  2
	// 2  1  2  1
	// 1  2  1  2
	// 2  1  2  1

	float constant = 2.0f;

	auto B = A + constant;
	auto C = constant + A;

	react::mat4f truth({ 3.0f, 4.0f, 3.0f, 4.0f, 4.0f, 3.0f, 4.0f, 3.0f, 3.0f, 4.0f, 3.0f, 4.0f, 4.0f, 3.0f, 4.0f, 3.0f });
	// 3  4  3  4
	// 4  3  4  3
	// 3  4  3  4
	// 4  3  4  3

	BOOST_TEST(B == truth);
	BOOST_TEST(C == truth);
}

BOOST_AUTO_TEST_CASE(matrix_constant_subtraction)
{
	react::mat4f A({ 1.0f, 2.0f, 1.0f, 2.0f, 2.0f, 1.0f, 2.0f, 1.0f, 1.0f, 2.0f, 1.0f, 2.0f, 2.0f, 1.0f, 2.0f, 1.0f });
	// 1  2  1  2
	// 2  1  2  1
	// 1  2  1  2
	// 2  1  2  1

	float constant = 2.0f;

	auto B = A - constant;
	auto C = constant - A;

	react::mat4f A_min_const_truth({ -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, -1.0f });
	// -1   0  -1   0
	//  0  -1   0  -1
	// -1   0  -1   0
	//  0  -1   0  -1

	react::mat4f const_min_A_truth({ 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f });
	// 1  0  1  0
	// 0  1  0  1
	// 1  0  1  0
	// 0  1  0  1

	BOOST_TEST(B == A_min_const_truth);
	BOOST_TEST(C == const_min_A_truth);
}

BOOST_AUTO_TEST_CASE(matrix_at)
{
	react::mat3f A({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f });
	// 1  4  7
	// 2  5  8
	// 3  6  9

	float B = A.at(0, 1); // row 0, col 1
	float C = A.at(2, 0); // row 2, col 0
	float D = A.at(2, 2); // row 2, col 2

	float B_truth = 4.0f;
	float C_truth = 3.0f;
	float D_truth = 9.0f;

	BOOST_TEST(B == B_truth);
	BOOST_TEST(C == C_truth);
	BOOST_TEST(D == D_truth);
}

BOOST_AUTO_TEST_CASE(matrix_row)
{
	react::mat3f A({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f });
	// 1  4  7
	// 2  5  8
	// 3  6  9

	react::mat3f::row_type B = A.row(0);
	// 1  4  7

	react::mat3f::row_type C = A.row(2);
	// 3  6  9

	float B_truth[] = { 1.0f, 4.0f, 7.0f };
	// 1  4  7

	float C_truth[] = { 3.0f, 6.0f, 9.0f };
	// 3  6  9

	BOOST_CHECK_EQUAL_COLLECTIONS(B.m_data, B.m_data + 3, B_truth, B_truth + 3);
	BOOST_CHECK_EQUAL_COLLECTIONS(C.m_data, C.m_data + 3, C_truth, C_truth + 3);
}

BOOST_AUTO_TEST_CASE(matrix_col)
{
	react::mat3f A({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f });
	// 1  4  7
	// 2  5  8
	// 3  6  9

	react::mat3f::col_type B = A.col(0);
	// 1  2  3

	react::mat3f::col_type C = A.col(2);
	// 7  8  9

	float B_truth[] = { 1.0f, 2.0f, 3.0f };
	// 1  2  3

	float C_truth[] = { 7.0f, 8.0f, 9.0f };
	// 7  8  9

	BOOST_CHECK_EQUAL_COLLECTIONS(B.m_data, B.m_data + 3, B_truth, B_truth + 3);
	BOOST_CHECK_EQUAL_COLLECTIONS(C.m_data, C.m_data + 3, C_truth, C_truth + 3);
}

BOOST_AUTO_TEST_CASE(matrix_invertible)
{
	react::mat3f A({ 1.0f, -2.0f, 1.0f, 2.0f, 0.0f, -1.0f, -1.0f, 1.0f, 0.0f });
	//  1   2  -1
	// -2   0   1
	//  1  -1   0

	react::mat4f B({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f });
	// 1  5  9   13
	// 2  6  10  14
	// 3  7  11  15
	// 4  8  12  16

	BOOST_TEST(A.invertible() == true);
	BOOST_TEST(B.invertible() == false);
}

BOOST_AUTO_TEST_CASE(matrix_outer_product)
{
	react::vec3f A({ 3.0f, 2.0f, 1.0f });
	// 3  2  1

	react::vec4f B({ 7.0f, 2.0f, 3.0f, 1.0f });
	// 7  2  3  1

	auto C = react::mat3f::outer_product(A, B);

	react::mat4x3f truth({ 21.0f, 14.0f, 7.0f, 6.0f, 4.0f, 2.0f, 9.0f, 6.0f, 3.0f, 3.0f, 2.0f, 1.0f });
	// 21  6  9  3
	// 14  4  6  2
	//  7  2  3  1

	BOOST_TEST(C == truth);
}

BOOST_AUTO_TEST_CASE(matrix_set_row)
{
	react::mat3f A = react::mat3f::ONE;
	// 1  1  1
	// 1  1  1
	// 1  1  1

	react::mat3f B = react::mat3f::ZERO;
	// 0  0  0
	// 0  0  0
	// 0  0  0

	A.set_row({ 9.0f, 8.0f, 7.0f }, 1);
	B.set_row(react::vec3f(1.0f, 2.0f, 3.0f), 2);

	react::mat3f A_truth({ 1.0f, 9.0f, 1.0f, 1.0f, 8.0f, 1.0f, 1.0f, 7.0f, 1.0f });
	// 1  1  1
	// 9  8  7
	// 1  1  1

	react::mat3f B_truth({ 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 3.0f });
	// 0  0  0
	// 0  0  0
	// 1  2  3

	BOOST_TEST(A == A_truth);
	BOOST_TEST(B == B_truth);
}

BOOST_AUTO_TEST_CASE(matrix_set_col)
{
	react::mat3f A = react::mat3f::ONE;
	// 1  1  1
	// 1  1  1
	// 1  1  1

	react::mat3f B = react::mat3f::ZERO;
	// 0  0  0
	// 0  0  0
	// 0  0  0

	A.set_col({ 9.0f, 8.0f, 7.0f }, 1);
	B.set_col(react::vec3f(1.0f, 2.0f, 3.0f), 2);

	react::mat3f A_truth({ 1.0f, 1.0f, 1.0f, 9.0f, 8.0f, 7.0f, 1.0f, 1.0f, 1.0f });
	// 1  9  1
	// 1  8  1
	// 1  7  1

	react::mat3f B_truth({ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 3.0f });
	// 0  0  1
	// 0  0  2
	// 0  0  3

	BOOST_TEST(A == A_truth);
	BOOST_TEST(B == B_truth);
}

BOOST_AUTO_TEST_SUITE_END()