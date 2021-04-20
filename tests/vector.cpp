#include <boost/test/unit_test.hpp>

#include <React-Math.h>

constexpr float tolerence = std::numeric_limits<float>::epsilon();

BOOST_AUTO_TEST_SUITE(vector)

BOOST_AUTO_TEST_CASE(vector_default_constructor)
{
	react::vec3f A;
	// 0  0  0

	float A_truth[] = { 0.0f, 0.0f, 0.0f };

	BOOST_CHECK_EQUAL_COLLECTIONS(A.m_data, A.m_data + 3, A_truth, A_truth + 3);
}

BOOST_AUTO_TEST_CASE(vector_constant_constructor)
{
	react::vec3f A(3.0f);
	// 3  3  3

	float A_truth[] = { 3.0f, 3.0f, 3.0f };

	BOOST_CHECK_EQUAL_COLLECTIONS(A.m_data, A.m_data + 3, A_truth, A_truth + 3);
}

BOOST_AUTO_TEST_CASE(vector_one_constructor)
{
	react::vec3f A = react::vec3f::ONE;
	// 1  1  1

	float A_truth[] = { 1.0f, 1.0f, 1.0f };

	BOOST_CHECK_EQUAL_COLLECTIONS(A.m_data, A.m_data + 3, A_truth, A_truth + 3);
}

BOOST_AUTO_TEST_CASE(vector_zero_constructor)
{
	react::vec3f A = react::vec3f::ZERO;
	// 0  0  0

	float A_truth[] = { 0.0f, 0.0f, 0.0f };

	BOOST_CHECK_EQUAL_COLLECTIONS(A.m_data, A.m_data + 3, A_truth, A_truth + 3);
}

BOOST_AUTO_TEST_CASE(vector_inf_constructor)
{
	react::vec3f A = react::vec3f::INF;
	// INF  INF  INF

	float inf = std::numeric_limits<float>::infinity();

	float A_truth[] = { inf, inf, inf };

	BOOST_CHECK_EQUAL_COLLECTIONS(A.m_data, A.m_data + 3, A_truth, A_truth + 3);
}

BOOST_AUTO_TEST_CASE(vector_neg_inf_constructor)
{
	react::vec3f A = react::vec3f::NEG_INF;
	// -INF  -INF  -INF

	float inf = std::numeric_limits<float>::infinity();

	float A_truth[] = { -inf, -inf, -inf };

	BOOST_CHECK_EQUAL_COLLECTIONS(A.m_data, A.m_data + 3, A_truth, A_truth + 3);
}

BOOST_AUTO_TEST_CASE(vector_xyzw_constructor)
{
	react::vec2f A(1.0f, 2.0f);
	// 1  2

	react::vec3f B(1.0f, 2.0f, 3.0f);
	// 1  2  3

	react::vec4f C(1.0f, 2.0f, 3.0f, 4.0f);
	// 1  2  3  4

	float A_truth[] = { 1.0f, 2.0f };
	float B_truth[] = { 1.0f, 2.0f, 3.0f };
	float C_truth[] = { 1.0f, 2.0f, 3.0f, 4.0f };

	BOOST_CHECK_EQUAL_COLLECTIONS(A.m_data, A.m_data + 2, A_truth, A_truth + 2);
	BOOST_CHECK_EQUAL_COLLECTIONS(B.m_data, B.m_data + 3, B_truth, B_truth + 3);
	BOOST_CHECK_EQUAL_COLLECTIONS(C.m_data, C.m_data + 4, C_truth, C_truth + 4);
}

BOOST_AUTO_TEST_CASE(vector_from_vector_constructor)
{
	react::vec3f A(1.0f, 2.0f, 3.0f);
	// 1  2  3

	react::vec2f B(A);
	// 1  2

	react::vec4f C(A);
	// 1  2  3  0

	float B_truth[] = { 1.0f, 2.0f };
	float C_truth[] = { 1.0f, 2.0f, 3.0f, 0.0f };

	BOOST_CHECK_EQUAL_COLLECTIONS(B.m_data, B.m_data + 2, B_truth, B_truth + 2);
	BOOST_CHECK_EQUAL_COLLECTIONS(C.m_data, C.m_data + 4, C_truth, C_truth + 4);
}

BOOST_AUTO_TEST_CASE(vector_compare)
{
	react::vec3f A(1.0f, 2.0f, 3.0f);
	react::vec3f B(9.0f, 7.0f, 6.0f);
	react::vec3f C(1.0f, 2.0f, 3.0f);

	react::vec4f D(A);

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

BOOST_AUTO_TEST_CASE(vector_accessors)
{
	react::vec4f A(1.0f, 2.0f, 3.0f, 4.0f);
	react::vec4f B(9.0f, 8.0f, 7.0f, 6.0f);

	float Ax_truth = 1.0f;
	float Ay_truth = 2.0f;
	float Az_truth = 3.0f;
	float Aw_truth = 4.0f;

	float Br_truth = 9.0f;
	float Bg_truth = 8.0f;
	float Bb_truth = 7.0f;
	float Ba_truth = 6.0f;

	float A0_truth = 1.0f;
	float A2_truth = 3.0f;
	float B1_truth = 8.0f;
	float B3_truth = 6.0f;

	BOOST_TEST(A.x() == Ax_truth);
	BOOST_TEST(A.y() == Ay_truth);
	BOOST_TEST(A.z() == Az_truth);
	BOOST_TEST(A.w() == Aw_truth);

	BOOST_TEST(B.r() == Br_truth);
	BOOST_TEST(B.g() == Bg_truth);
	BOOST_TEST(B.b() == Bb_truth);
	BOOST_TEST(B.a() == Ba_truth);

	BOOST_TEST(A[0] == A0_truth);
	BOOST_TEST(A[2] == A2_truth);
	BOOST_TEST(B[1] == B1_truth);
	BOOST_TEST(B[3] == B3_truth);
}

BOOST_AUTO_TEST_CASE(vector_angle)
{
	react::vec3f A = react::vec3f::UP;
	react::vec3f B = react::vec3f::RIGHT;

	react::vec2f C = react::vec2f::LEFT;
	react::vec2f D = react::vec2f::RIGHT;

	float AB_truth = 90.0f * (react::math::pi<float>() / 180.0f);
	float CD_truth = 180.0f * (react::math::pi<float>() / 180.0f);

	BOOST_TEST(A.angle(B) == AB_truth);
	BOOST_TEST(C.angle(D) == CD_truth);
}

BOOST_AUTO_TEST_CASE(vector_dot)
{
	react::vec3f A(1.0f, 2.0f, 3.0f);
	react::vec3f B(9.0f, 8.0f, 7.0f);

	float truth = 46.0f;

	BOOST_TEST(A.dot(B) == truth);
}

BOOST_AUTO_TEST_CASE(vector_distance, * boost::unit_test::tolerance(tolerence))
{
	react::vec3f A(-5.0f, 2.0f, 7.0f);
	react::vec3f B(3.0f, -4.0f, -1.0f);

	react::vec4f C(-2.0f, 7.0f, 1.0f, -3.0f);
	react::vec4f D(1.0f, -2.0f, 4.0f, 0.0f);

	//  -3      9     -3    -3
	//  9       81     9     9

	float AB_truth = 12.8062484748657f;
	float CD_truth = 10.39230484541326f;

	BOOST_TEST(A.distance(B) == AB_truth);
	BOOST_TEST(C.distance(D) == CD_truth);
}

BOOST_AUTO_TEST_CASE(vector_length, *boost::unit_test::tolerance(tolerence))
{
	react::vec3f A(5.0f, 3.0f, 4.0f);
	react::vec4f B(1.0f, 0.0f, 7.0f, -2.0f);

	float A_truth = 7.071067811865475f;
	float B_truth = 7.348469228349534f;

	BOOST_TEST(A.length() == A_truth);
	BOOST_TEST(B.length() == B_truth);
}

BOOST_AUTO_TEST_CASE(vector_normalize)
{
	react::vec3f A(5.0f, -1.0f, 3.0f);
	react::vec3f B(2.0f, -7.0f, -3.0f);

	A.normalize();
	react::vec3f C = B.normalized();

	react::vec3f A_truth(0.845154254728516f, -0.1690308509457033f, 0.50709255283711f);
	react::vec3f C_truth(0.254000254000381f, -0.8890008890013334f, -0.3810003810005715f);

	BOOST_TEST(A == A_truth);
	BOOST_TEST(C == C_truth);
}

BOOST_AUTO_TEST_CASE(vector_lerp)
{
	react::vec3f A = react::vec3f::UP;
	// 0  1  0

	react::vec3f B = react::vec3f::RIGHT;
	// 1  0  0

	react::vec3f C = A.lerp(B, 0.25f);
	react::vec3f D = A.lerp(B, 0.5f);
	react::vec3f E = A.lerp(B, 0.75f);

	react::vec3f C_truth(0.25f, 0.75f, 0.0f);
	react::vec3f D_truth(0.5f, 0.5f, 0.0f);
	react::vec3f E_truth(0.75f, 0.25f, 0.0f);

	BOOST_TEST(C == C_truth);
	BOOST_TEST(D == D_truth);
	BOOST_TEST(E == E_truth);
}

BOOST_AUTO_TEST_CASE(vector_project)
{
	react::vec3f A = react::vec3f::UP;
	// 0  1  0

	react::vec3f B = react::vec3f::LEFT;
	// -1  0  0

	react::vec3f C(7.0f, 3.0f, -1.0f);

	react::vec3f D = A.project(C);
	react::vec3f E = B.project(C);

	react::vec3f D_truth(0.0f, 3.0f, 0.0f);
	react::vec3f E_truth(7.0f, 0.0f, 0.0f);

	BOOST_TEST(D == D_truth);
	BOOST_TEST(E == E_truth);
}

BOOST_AUTO_TEST_SUITE_END()