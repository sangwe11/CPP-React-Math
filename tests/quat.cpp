#include <boost/test/unit_test.hpp>

#include <React-Math.h>

BOOST_AUTO_TEST_SUITE(quat)

BOOST_AUTO_TEST_CASE(quat_default_constructor)
{
	react::quatf quat;
	// 0  0  0  1

	float truth[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	// 0  0  0  1

	BOOST_CHECK_EQUAL_COLLECTIONS(quat.m_data, quat.m_data + 4, truth, truth + 4);
}

BOOST_AUTO_TEST_CASE(quat_xyzw_constructor)
{
	react::quatf quat(1.0f, 2.0f, 3.0f, 4.0f);
	// 1  2  3  4

	float truth[] = { 1.0f, 2.0f, 3.0f, 4.0f };
	// 1  2  3  4

	BOOST_CHECK_EQUAL_COLLECTIONS(quat.m_data, quat.m_data + 4, truth, truth + 4);
}

BOOST_AUTO_TEST_CASE(quat_vec3_w_constructor)
{
	react::quatf quat(react::vec3f(1.0f, 2.0f, 3.0f), 4.0f);
	// 1  2  3  4

	float truth[] = { 1.0f, 2.0f, 3.0f, 4.0f };
	// 1  2  3  4

	BOOST_CHECK_EQUAL_COLLECTIONS(quat.m_data, quat.m_data + 4, truth, truth + 4);
}

BOOST_AUTO_TEST_CASE(quat_vec4_constructor)
{
	react::quatf quat(react::vec4f(1.0f, 2.0f, 3.0f, 4.0f));
	// 1  2  3  4

	float truth[] = { 1.0f, 2.0f, 3.0f, 4.0f };
	// 1  2  3  4

	BOOST_CHECK_EQUAL_COLLECTIONS(quat.m_data, quat.m_data + 4, truth, truth + 4);
}

BOOST_AUTO_TEST_CASE(quat_compare)
{
	react::quatf A(1.0f, 2.0f, 3.0f, 4.0f);
	react::quatf B(9.0f, 7.0f, 8.0f, 6.0f);
	react::quatf C(1.0f, 2.0f, 3.0f, 4.0f);

	bool A_eq_B = (A == B); // false
	bool A_eq_C = (A == C); // true
	bool A_neq_B = (A != B); // true
	bool A_neq_C = (A != C); // false

	BOOST_CHECK(A_eq_B == false);
	BOOST_CHECK(A_eq_C == true);
	BOOST_CHECK(A_neq_B == true);
	BOOST_CHECK(A_neq_C == false);
}

BOOST_AUTO_TEST_CASE(quat_xyz)
{
	react::quatf quat(1.0f, 2.0f, 3.0f, 4.0f);

	react::vec3f truth(1.0f, 2.0f, 3.0f);

	BOOST_TEST(quat.xyz() == truth);
}

BOOST_AUTO_TEST_CASE(quat_conjugate)
{
	react::quatf A(1.0f, 2.0f, 3.0f, 4.0f);

	react::quatf truth(-1.0f, -2.0f, -3.0f, 4.0f);

	BOOST_TEST(A.conjugate() == truth);
}

BOOST_AUTO_TEST_CASE(quat_dot)
{
	react::quatf A(1.0f, 2.0f, 3.0f, 4.0f);
	react::quatf B(9.0f, 8.0f, 7.0f, 6.0f);

	float truth = 70.0f;

	BOOST_TEST(A.dot(B) == truth);
}

BOOST_AUTO_TEST_CASE(quat_inverse)
{
	react::quatf A(1.0f, 2.0f, 3.0f, 4.0f);

	react::quatf truth(-0.033333333333333f, -0.066666666666667f, -0.1f, 0.133333333333333f);

	BOOST_TEST(A.inverse() == truth);
}

BOOST_AUTO_TEST_CASE(quat_normalized)
{
	react::quatf A(1.0f, 2.0f, 3.0f, 1.0f);
	react::quatf B(9.0f, 8.0f, 7.0f, 1.0f);

	A.normalize();
	react::quatf C = B.normalized();

	react::quatf A_truth(0.2581988897471611f, 0.5163977794943222f, 0.7745966692414833f, 0.2581988897471611f);
	react::quatf C_truth(0.6445033866354897f, 0.5728918992315464f, 0.5012804118276031f, 0.0716114874039433f);

	BOOST_TEST(A == A_truth);
	BOOST_TEST(C == C_truth);
}

BOOST_AUTO_TEST_CASE(quat_rotate_vec3)
{
	react::vec3f A(1.0f, 0.0f, -1.0f);
	react::quatf B = react::quatf::fromAxisAngle(react::vec3f::UP, 90.0f);

	react::vec3f C = B.rotate(A);

	react::vec3f truth(-1.34207010269165f, 0.0f, -0.4459229707717896f);

	BOOST_TEST(C == truth);
}

BOOST_AUTO_TEST_CASE(quat_axis_angle)
{
	react::quatf C = react::quatf::fromAxisAngle(react::vec3f::UP, 90.0f);

	react::quatf truth(0.0f, 0.8509035110473633f, 0.0f, 0.5253219604492188f);

	BOOST_TEST(C == truth);
}

BOOST_AUTO_TEST_CASE(quat_constant_multiplication)
{
	react::quatf A(1.0f, 2.0f, 3.0f, 4.0f);
	react::quatf B(9.0f, 8.0f, 7.0f, 6.0f);

	B *= 2.0f;
	react::quatf C = A * -2.0f;
	react::quatf D = 3.0f * A;

	react::quatf B_truth(18.0f, 16.0f, 14.0f, 12.0f);
	react::quatf C_truth(-2.0f, -4.0f, -6.0f, -8.0f);
	react::quatf D_truth(3.0f, 6.0f, 9.0f, 12.0f);

	BOOST_TEST(B == B_truth);
	BOOST_TEST(C == C_truth);
	BOOST_TEST(D == D_truth);
}

BOOST_AUTO_TEST_CASE(quat_constant_division)
{
	react::quatf A(1.0f, 2.0f, 3.0f, 4.0f);
	react::quatf B(9.0f, 8.0f, 7.0f, 6.0f);

	B /= 2.0f;
	react::quatf C = A / -2.0f;

	react::quatf B_truth(4.5f, 4.0f, 3.5f, 3.0f);
	react::quatf C_truth(-0.5f, -1.0f, -1.5f, -2.0f);

	BOOST_TEST(B == B_truth);
	BOOST_TEST(C == C_truth);
}

BOOST_AUTO_TEST_CASE(quat_addition)
{
	react::quatf A(1.0f, 2.0f, 3.0f, 4.0f);
	react::quatf B(2.0f, -1.0f, 3.0f, -6.0f);
	react::quatf C(-3.0f, 1.0f, -2.0f, 4.0f);

	C += A;
	react::quatf D = A + B;
	react::quatf E = B + A;

	react::quatf C_truth(-2.0f, 3.0f, 1.0f, 8.0f);
	react::quatf D_truth(3.0f, 1.0f, 6.0f, -2.0f);
	react::quatf E_truth(3.0f, 1.0f, 6.0f, -2.0f);

	BOOST_TEST(C == C_truth);
	BOOST_TEST(D == D_truth);
	BOOST_TEST(E == E_truth);
}

BOOST_AUTO_TEST_CASE(quat_subtraction)
{
	react::quatf A(1.0f, 2.0f, 3.0f, 4.0f);
	react::quatf B(2.0f, -1.0f, 3.0f, -6.0f);
	react::quatf C(-3.0f, 1.0f, -2.0f, 4.0f);

	C -= A;
	react::quatf D = A - B;
	react::quatf E = B - A;

	react::quatf C_truth(-4.0f, -1.0f, -5.0f, 0.0f);
	react::quatf D_truth(-1.0f, 3.0f, 0.0f, 10.0f);
	react::quatf E_truth(1.0f, -3.0f, 0.0f, -10.0f);

	BOOST_TEST(C == C_truth);
	BOOST_TEST(D == D_truth);
	BOOST_TEST(E == E_truth);
}

BOOST_AUTO_TEST_CASE(quat_multiplication)
{
	react::quatf A(1.0f, 2.0f, 3.0f, 4.0f);
	react::quatf B(9.0f, 8.0f, 7.0f, 6.0f);
	react::quatf C(4.0f, 2.0f, 9.0f, 3.0f);

	C *= A;
	react::quatf D = A * B;
	react::quatf E = B * A;

	react::quatf C_truth(7.0f, 11.0f, 51.0f, -23.0f);
	react::quatf D_truth(32.0f, 64.0f, 36.0f, -22.0f);
	react::quatf E_truth(52.0f, 24.0f, 56.0f, -22.0f);

	BOOST_TEST(C == C_truth);
	BOOST_TEST(D == D_truth);
	BOOST_TEST(E == E_truth);
}

BOOST_AUTO_TEST_SUITE_END()