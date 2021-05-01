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

BOOST_AUTO_TEST_CASE(quat_vec4_constructor)
{
	react::quatf quat(react::vec4f(1.0f, 2.0f, 3.0f, 4.0f));
	// 1  2  3  4

	float truth[] = { 1.0f, 2.0f, 3.0f, 4.0f };
	// 1  2  3  4

	BOOST_CHECK_EQUAL_COLLECTIONS(quat.m_data, quat.m_data + 4, truth, truth + 4);
}

BOOST_AUTO_TEST_CASE(quat_axis_angle_constructor)
{
	react::quatf C(react::vec3f::UP, 90.0f);

	react::quatf truth(0.0f, 0.8509035110473633f, 0.0f, 0.5253219604492188f);

	BOOST_TEST(C == truth);
}

BOOST_AUTO_TEST_CASE(quat_euler_constructor)
{
	react::vec3f A(30.0f, -45.0f, 20.0f);
	// Euler angles in degrees
	// x = 30, y = -45, z = 20

	react::vec3f B(20.0f, -60.0f, 15.0f);
	// Euler angles in degrees
	// x = 20, y = -60, z = 15

	react::quatf C(react::math::radians(A));
	react::quatf D = react::quatf::fromEulers(react::math::radians(B));

	react::quatf C_truth(0.2996729f, -0.3225058f, 0.2525045f, 0.8616424f);
	react::quatf D_truth(0.2133688f, -0.4685623f, 0.197403f, 0.8342393f);

	react::vec3f C_eulers = C.toEulers();
	react::vec3f D_eulers = D.toEulers();

	BOOST_TEST(C == C_truth);
	BOOST_TEST(D == D_truth);

	BOOST_TEST(C_eulers == react::math::radians(A));
	BOOST_TEST(D_eulers == react::math::radians(B));
}

BOOST_AUTO_TEST_CASE(quat_matrix_constructor)
{
	react::mat3f A({ 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f });
	// 90 degree rotation around (0, 1, 0)
	//  0  0  1
	//  0  1  0
	// -1  0  0

	react::mat3f B({ 0.8535534f, 0.1464466f, 0.5000000f, 0.1464466f, 0.8535534f, -0.5000000f, -0.5000000f, 0.5000000f, 0.7071068f });
	// -45 degree rotation around (1, 1, 0)
	// 0.8535534   0.1464466  -0.5000000;
	// 0.1464466   0.8535534   0.5000000;
	// 0.5000000  -0.5000000   0.7071068

	react::quatf C(A);
	react::quatf D = react::quatf::fromMat3(B);

	react::quatf C_truth(0.0f, 0.7071068f, 0.0f, 0.7071068f);
	react::quatf D_truth(-0.2705981f, -0.2705981f, 0.0f, 0.9238795f);

	BOOST_TEST(C == C_truth);
	BOOST_TEST(D == D_truth);
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

BOOST_AUTO_TEST_CASE(quat_to_axis_angle)
{
	react::vec3f A_axis(0.0f, 0.0f, 1.0f);
	float A_angle = react::math::radians(90.0f);
	react::quatf A(A_axis, A_angle);

	react::vec3f A_axis_out;
	float A_angle_out;
	A.toAxisAngle(A_axis_out, A_angle_out);

	BOOST_TEST(A_axis_out == A_axis.normalized()); // axis out is normalized
	BOOST_TEST(A_angle_out == A_angle); // complex axis/angles result in precision errors here
}

BOOST_AUTO_TEST_CASE(quat_to_eulers)
{
	react::quatf A(0.3894179f, -0.1269732f, 0.1454975f, 0.9005898f);
	react::quatf B(0.2133688f, -0.4685623f, 0.197403f, 0.8342393f);

	react::vec3f C = A.toEulers();
	react::vec3f D = B.toEulers();

	react::vec3f C_truth(45.0f, -20.0f, 10.0f); // given in degrees
	react::vec3f D_truth(20.0f, -60.0f, 15.0f); // given in degrees

	BOOST_TEST(C == react::math::radians(C_truth));
	BOOST_TEST(D == react::math::radians(D_truth));
}

BOOST_AUTO_TEST_CASE(quat_to_matrix)
{
	react::quatf A(react::vec3f(0.0f, 1.0f, 0.0f), react::math::radians(90.0f));
	// 90 degree rotation around (0, 1, 0)

	react::quatf B(react::vec3f(1.0f, 1.0f, 0.0f), react::math::radians(-45.0f));
	// -45 degree rotation around (1, 1, 0)

	react::mat3f A_out = A.toMat3();
	react::mat3f B_out = B.toMat3();

	react::mat3f A_truth({ 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f });
	react::mat3f B_truth({ 0.8535534f, 0.1464466f, 0.5000000f, 0.1464466f, 0.8535534f, -0.5000000f, -0.5000000f, 0.5000000f, 0.7071068f });

	BOOST_TEST(A_out == A_truth);
	BOOST_TEST(B_out == B_truth);
}

BOOST_AUTO_TEST_SUITE_END()