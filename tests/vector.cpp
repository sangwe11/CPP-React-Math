#include <boost/test/unit_test.hpp>

#include <React-Math.h>

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

BOOST_AUTO_TEST_SUITE_END()